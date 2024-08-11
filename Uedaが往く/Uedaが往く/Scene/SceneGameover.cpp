#include "Dxlib.h"
#include "Input.h"
#include "Vec2.h"
#include "Game.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneTitle.h"
#include "SceneSelectStage.h"
#include "SceneStage2.h"
#include "SceneGameover.h"

// 定数
namespace
{
	const char* const kHaibokuTextPath = "data/UI/haiboku.png";	// 敗北のテキスト画像のファイル位置
	const char* const kCursorPath = "data/UI/cursor.png";		// カーソル画像のファイル位置
	const Vec2 kHaibokuTextPos = { 670, 100 };					// 敗北のテキスト画像表示位置
	const Vec2 kRetryTextPos = { 650, 600 };					// "リトライ"表示位置
	const Vec2 kStageTextPos = { 650, 700 };					// "ステージ選択にもどる"表示位置
	const Vec2 kTitleTextPos = { 650, 800 };					// "タイトルにもどる"表示位置
	const Vec2 kCursorPos = { 600, 590 };						// カーソル表示位置
	constexpr float kCursorMove = 100.0f;						// カーソルの移動量
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
	UpdateSelect(input);	// 選択状態更新

	if (input.IsTriggered("OK"))
	{
		if (m_select == kRetry)
		{
			std::shared_ptr<Player> pPlayer = std::make_shared<Player>();
			std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();
			std::shared_ptr<Stage> pStage = std::make_shared<Stage>();
			return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage);	// プレイ画面に移動
			//return m_pPrevScene;
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
	DrawGraphF(kCursorPos.x, kCursorPos.y + kCursorMove * m_select, m_cursorHandle, true);

	// 選択項目を表示
	DrawStringF(kRetryTextPos.x, kRetryTextPos.y, "リトライ", 0xffffff);
	DrawStringF(kStageTextPos.x, kStageTextPos.y, "ステージ選択にもどる", 0xffffff);
	DrawStringF(kTitleTextPos.x, kTitleTextPos.y, "タイトルにもどる", 0xffffff);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ゲームオーバー画面", 0xffffff);
	// 中心線
	DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);
#endif
}


/// <summary>
/// 選択状態を更新する
/// </summary>
/// <param name="input">入力状態</param>
void SceneGameover::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// 選択状態を1つ下げる
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// 選択状態を1つ上げる
	}
}
