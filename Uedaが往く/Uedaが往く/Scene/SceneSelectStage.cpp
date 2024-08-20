#include "EffekseerForDXLib.h"
#include "DxLib.h"
#include "Vec2.h"
#include "Game.h"
#include "Input.h"
#include "UI.h"
#include "Sound.h"
#include "Font.h"
#include "Ranking.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneOption.h"
#include "SceneTitle.h"
#include "SceneSelectStage.h"

// 定数
namespace
{
	constexpr int kBackColor = 0xdddddd;			// 背景の色
	constexpr int kBackBoxColor = 0x494949;			// 四角の色
	constexpr int kBackBoxLTPos = 140;				// 四角の左上位置
	constexpr int kBackBoxWidth = 490;				// 四角の幅
	const Vec2 kSelectTextPos = { 260, 300 };		// 選択テキスト表示位置
	constexpr float kSelectTextInterval = 120.0f;	// 選択テキスト表示間隔
	constexpr float kSelectTextAdj = 40.0f;			// テキスト表示位置調整
	const Vec2 kCursorLTPos = { 140, 290 };			// カーソル左上位置
	constexpr int kTextColor = 0xffffff;			// テキストの色
}


/// <summary>
/// コンストラクタ
/// </summary>
SceneSelectStage::SceneSelectStage()
{
	m_select = SelectScene::kStage1;
}


/// <summary>
/// デストラクタ
/// </summary>
SceneSelectStage::~SceneSelectStage()
{
	StopSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kStageSelect)]);
}


/// <summary>
/// 初期化
/// </summary>
void SceneSelectStage::Init()
{
	// ランキング取得
	m_pRank->GetRanking();
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力処理</param>
/// <returns>遷移先のシーン</returns>
std::shared_ptr<SceneBase> SceneSelectStage::Update(Input& input)
{
	//選択状態更新
	UpdateSelect(input, kSelectNum);
	m_pUI->Update();

	// BGMを鳴らす
	if (!CheckSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kStageSelect)]))
	{
		PlaySoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kStageSelect)], DX_PLAYTYPE_LOOP);
	}

	// シーン遷移
	if (input.IsTriggered("OK"))
	{
		PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kSelect)], DX_PLAYTYPE_BACK); // SEを鳴らす

		std::shared_ptr<Player> pPlayer = std::make_shared<Player>();
		std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();
		std::shared_ptr<Stage> pStage = std::make_shared<Stage>();

		if (m_select == SelectScene::kStage1)
		{
			return std::make_shared<SceneStage1>(pPlayer, pCamera, pStage);
		}
		else if (m_select == SelectScene::kStage2)
		{
			return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage);
		}
		else if (m_select == kOption)
		{
			return std::make_shared<SceneOption>(shared_from_this());
		}
		else if (m_select == kEnd)
		{
			Effkseer_End();	// Effekseerの終了処理
			DxLib_End();
		}
	}
	if (input.IsTriggered("back"))
	{
		return std::make_shared<SceneTitle>();
	}

	return shared_from_this();
}


/// <summary>
/// 描画
/// </summary>
void SceneSelectStage::Draw()
{
	// 背景描画
	m_pUI->DrawMenuBg();
	// カーソル表示
	m_pUI->DrawCursor(kCursorLTPos, m_select, kSelectTextInterval);
	m_pUI->DrawButtonText();

	// テキスト表示
	DrawStringFToHandle(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * SelectScene::kStage1,
		"練習へ往く", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kSelectStage)]);
	DrawStringFToHandle(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * SelectScene::kStage2,
		"闘いへ往く", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kSelectStage)]);
	DrawStringFToHandle(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * SelectScene::kOption,
		"オプション", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kSelectStage)]);
	DrawStringFToHandle(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * SelectScene::kEnd,
		"ゲームを終わる", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kSelectStage)]);

	// ランキング表示
	if (m_select == SelectScene::kStage2)
	{
		m_pRank->DrawRanking();
	}

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ステージ選択画面", 0xffffff);
#endif
}


