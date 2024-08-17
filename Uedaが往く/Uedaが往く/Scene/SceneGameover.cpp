#include "Dxlib.h"
#include "Input.h"
#include "Vec2.h"
#include "Game.h"
#include "UI.h"
#include "Sound.h"
#include "Font.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneTitle.h"
#include "SceneSelectStage.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneGameover.h"

// 定数
namespace
{
	const char* const kHaibokuTextPath = "data/UI/haiboku.png";	// 敗北のテキスト画像のファイル位置
	const char* const kCursorPath = "data/UI/cursor.png";		// カーソル画像のファイル位置
	constexpr int kTextColor = 0xffffff;						// テキストの色
	const Vec2 kHaibokuTextPos = { 670, 100 };					// 敗北のテキスト画像表示位置
	const Vec2 kRetryTextPos = { 860, 600 };					// "リトライ"表示位置
	const Vec2 kStageTextPos = { 720, 720 };					// "ステージ選択にもどる"表示位置
	const Vec2 kTitleTextPos = { 760, 840 };					// "タイトルにもどる"表示位置
	const Vec2 kCursorPos = { 750, 590 };						// カーソル表示位置
	constexpr float kCursorMove = 120.0f;						// カーソルの移動量
}


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pScene">前に実行していたシーン</param>
SceneGameover::SceneGameover(std::shared_ptr<SceneBase> pScene)
{
	m_select = Select::kRetry;
	m_pPrevScene = pScene;
	m_textHandle = LoadGraph(kHaibokuTextPath);
	m_cursorHandle = LoadGraph(kCursorPath);
}


/// <summary>
/// デストラクタ
/// </summary>
SceneGameover::~SceneGameover()
{
	StopSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kGameover)]);
	DeleteGraph(m_textHandle);
	DeleteGraph(m_cursorHandle);
}


/// <summary>
/// 初期化
/// </summary>
void SceneGameover::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneGameover::Update(Input& input)
{
	// 選択状態更新
	UpdateSelect(input, Select::kSelectNum);
	m_pUI->Update();

	// BGMを鳴らす
	if (!CheckSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kGameover)]))
	{
		PlaySoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kGameover)], DX_PLAYTYPE_LOOP);
	}

	if (input.IsTriggered("OK"))
	{
		if (m_select == kRetry)
		{
			std::shared_ptr<Player> pPlayer = std::make_shared<Player>();
			std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();
			std::shared_ptr<Stage> pStage = std::make_shared<Stage>();

			// MEMO:typeidでクラスを取得する
			if (typeid(*m_pPrevScene) == typeid(SceneStage1))
			{
				return std::make_shared<SceneStage1>(pPlayer, pCamera, pStage); // ステージ1に移動
			}
			if (typeid(*m_pPrevScene) == typeid(SceneStage2))
			{
				return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage); // ステージ2に移動
			}

		}
		else if (m_select == kStageSelect)
		{
			return std::make_shared<SceneSelectStage>(); // ステージ選択画面に移動
		}
		else if (m_select == kTitle)
		{
			return std::make_shared<SceneTitle>();	// タイトル画面に移動
		}
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneGameover::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x1a1a1a, true);

	// 敗北の文字を表示
	DrawGraphF(kHaibokuTextPos.x, kHaibokuTextPos.y, m_textHandle, true);

	// カーソル表示
	m_pUI->DrawCursor(kCursorPos, m_select, kCursorMove);

	// 選択項目を表示
	DrawStringFToHandle(kRetryTextPos.x, kRetryTextPos.y,
		"リトライ", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kGameover)]);
	DrawStringFToHandle(kStageTextPos.x, kStageTextPos.y,
		"ステージ選択にもどる", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kGameover)]);
	DrawStringFToHandle(kTitleTextPos.x, kTitleTextPos.y,
		"タイトルにもどる", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kGameover)]);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ゲームオーバー画面", 0xffffff);
	// 中心線
	DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);
#endif
}