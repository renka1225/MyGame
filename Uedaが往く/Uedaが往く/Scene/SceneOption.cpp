#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "Sound.h"
#include "Font.h"
#include "Game.h"
#include "UI.h"
#include "SceneOption.h"

// 定数
namespace
{
	constexpr int kBackBoxColor = 0x494949;					 // 四角の色
	const Vec2 kBackBoxPos = { 712.0f, 115.0f };			 // 背景の四角の表示位置
	constexpr float kBackBoxWidth = 1070;					 // 背景の四角の幅
	constexpr float kBackBoxHeight = 800;					 // 背景の四角の高さ

	constexpr int kTextColor = 0xffffff;					 // テキストの色
	const Vec2 kSelectTextPos = { 250.0f, 300.0f };			 // 選択テキスト表示位置
	constexpr float kSelectTextAdj = 30.0f;					 // 選択テキスト表示位置調整
	constexpr float kSelectTextInterval = 120.0f;			 // 選択テキスト表示間隔
	const Vec2 kAfterSelectTextPos = { 800.0f, 310.0f };	 // 選択後テキスト表示位置
	const Vec2 kCursorPos = { 140.0f, 290.0f };				// カーソル表示位置
	const Vec2 kAfterSelectCursorPos = { 780.0f, 300.0f };	// 選択後カーソル表示位置

	// サウンド関連
	const Vec2 kSoundNumTextPos = { 1650.0f, 320.0f };		 // 音量テキスト表示位置
	const Vec2 kSoundBarPos = { 950.0f, 330.0f };			 // 音量バー背景表示位置
	const Vec2 kCurrentSoundBarPos = { 954.0f, 333.0f };	 // 現在の音量バー左上位置
	constexpr float kCurrentSoundBarWidth = 650;			 // 現在の音量バーの最大横幅
	constexpr float kCurrentSoundBarHeight = 23;			 // 現在の音量バーの高さ
	constexpr int kCurrentSoundBarColor = 0xcf2223;			 // 現在の音量バーの色
	const Vec2 kSoundKnobPos = { 1600.0f, 315.0f };			 // つまみ初期表示位置
	constexpr float kSoundKnobMinPosX = 950.0f;				 // つまみ最小表示位置X

	// クレジット表記関連
	const Vec2 kSoundCreditTextPos = { 800.0f, 250.0f }; 	 // サウンドクレジット表記位置
	const Vec2 kModelCreditTextPos = { 800.0f, 540.0f };	 // 3Dモデルクレジット表記位置
	constexpr float kCreditTextAdj = 30.0f;					 // クレジット表記位置調整
	constexpr float kCreditTextIntervel = 60.0f;			 // クレジット表記間隔


	// 画像の種類
	enum class Handle
	{
		kSoundBar,
		kSoundKnob,
		kHandleNum,
	};
}


/// <summary>
/// コンストラクタ
/// </summary>
SceneOption::SceneOption(std::shared_ptr<SceneBase> pScene) :
	m_pPrevScene(pScene),
	m_afterSelect(SelectSound::kBGM),
	m_isSound(false)
{
	m_handle.resize(static_cast<int>(Handle::kHandleNum));
	m_handle[static_cast<int>(Handle::kSoundBar)] = LoadGraph("data/UI/soundBar.png");
	m_handle[static_cast<int>(Handle::kSoundKnob)] = LoadGraph("data/UI/soundKnob.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneOption::~SceneOption()
{
	for (auto& handle : m_handle)
	{
		DeleteGraph(handle);
	}
}


/// <summary>
/// 初期化
/// </summary>
void SceneOption::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input"></param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneOption::Update(Input& input)
{
	//選択状態更新
	if (m_isSound)
	{
		// サウンド更新
		UpdateSound(input);
	}
	else
	{
		UpdateSelect(input, Select::kSelectNum);
	}

	m_pUI->Update();

	if (input.IsTriggered("back"))
	{
		if (m_isSound)
		{
			m_isSound = false;
		}
		else
		{
			return m_pPrevScene;	// 前の画面にもどる
		}
	}
	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kSound)
		{
			m_isSound = true;
			m_afterSelect = SelectSound::kBGM;
		}
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneOption::Draw()
{
	// 背景描画
	m_pUI->DrawMenuBg();
	DrawBoxAA(kBackBoxPos.x, kBackBoxPos.y, kBackBoxPos.x + kBackBoxWidth, kBackBoxPos.y + kBackBoxHeight, kBackBoxColor, true);

	// カーソル表示
	if (!m_isSound)
	{
		m_pUI->DrawCursor(kCursorPos, m_select, kSelectTextInterval);
	}
	else
	{
		m_pUI->DrawCursor(kAfterSelectCursorPos, m_afterSelect, kSelectTextInterval, true);
	}

	// サウンド関連表示
	if (m_select == Select::kSound)
	{
		DrawSound();
	}
	// クレジット表記
	if (m_select == Select::kCredit)
	{
		DrawCredit();
	}
	// キーコンフィグ関連表示
	//else if (m_select == Select::kKeyConfig)
	//{
	//	DrawKeyConfig();
	//}

	// テキスト表示
	DrawStringFToHandle(kSelectTextPos.x + kSelectTextAdj, kSelectTextPos.y + kSelectTextInterval * Select::kSound,
		"サウンド", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kSelectTextPos.x - kSelectTextAdj, kSelectTextPos.y + kSelectTextInterval * Select::kCredit,
		"クレジット表記", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);

	// ボタン画像表示
	m_pUI->DrawButtonText();

	// TODO:キーコンフィグは後ほど行う予定
	//DrawStringFToHandle(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kKeyConfig,
		//"ボタン配置", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "オプション画面", 0xffffff);
#endif
}


/// <summary>
/// サウンド更新
/// </summary>
/// <param name="input">入力状態</param>
void SceneOption::UpdateSound(Input& input)
{
	// 選択状態を1つ下げる
	if (input.IsTriggered("down"))
	{
		m_afterSelect = (m_afterSelect + 1) % SelectSound::kSelectSoundNum;
		m_pUI->Init();
		PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kCursor)], DX_PLAYTYPE_BACK);
	}
	// 選択状態を1つ上げる
	if (input.IsTriggered("up"))
	{
		m_afterSelect = (m_afterSelect + (SelectSound::kSelectSoundNum - 1)) % SelectSound::kSelectSoundNum;
		m_pUI->Init();
		PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kCursor)], DX_PLAYTYPE_BACK);
	}

	// BGM選択中の場合
	if (m_afterSelect == SelectSound::kBGM)
	{
		Sound::ChangeBgmVol(input);
	}
	// SE選択中の場合
	if (m_afterSelect == SelectSound::kSE)
	{
		Sound::ChangeSeVol(input);
	}
}


///// <summary>
///// キー更新
///// </summary>
///// <param name="input">入力状態</param>
//void SceneOption::UpdateKeyConfig(Input& input)
//{
//}


/// <summary>
/// サウンド部分表示
/// </summary>
void SceneOption::DrawSound()
{
	// サウンドバー表示
	DrawGraphF(kSoundBarPos.x, kSoundBarPos.y + kSelectTextInterval * SelectSound::kBGM, m_handle[static_cast<int>(Handle::kSoundBar)], true);
	DrawGraphF(kSoundBarPos.x, kSoundBarPos.y + kSelectTextInterval * SelectSound::kSE, m_handle[static_cast<int>(Handle::kSoundBar)], true);

	// 音量に合わせて四角の長さを更新する
	float bgmBarWidth = kCurrentSoundBarWidth * (Sound::GetBgmVol() / 100.0f);
	float seBarWidth = kCurrentSoundBarWidth * (Sound::GetSeVol() / 100.0f);
	DrawBoxAA(kCurrentSoundBarPos.x, kCurrentSoundBarPos.y + kSelectTextInterval * SelectSound::kBGM,
		kCurrentSoundBarPos.x + bgmBarWidth, kCurrentSoundBarPos.y + kCurrentSoundBarHeight + kSelectTextInterval * SelectSound::kBGM,
		kCurrentSoundBarColor, true);
	DrawBoxAA(kCurrentSoundBarPos.x, kCurrentSoundBarPos.y + kSelectTextInterval * SelectSound::kSE,
		kCurrentSoundBarPos.x + seBarWidth, kCurrentSoundBarPos.y + kCurrentSoundBarHeight + kSelectTextInterval * SelectSound::kSE,
		kCurrentSoundBarColor, true);

	// 音量によってつまみの位置を更新する
	float bgmKnobPosX = kSoundKnobMinPosX + (kSoundKnobPos.x - kSoundKnobMinPosX) * (Sound::GetBgmVol() / 100.0f);
	float seKnobPosX = kSoundKnobMinPosX + (kSoundKnobPos.x - kSoundKnobMinPosX) * (Sound::GetSeVol() / 100.0f);
	DrawGraphF(bgmKnobPosX, kSoundKnobPos.y + kSelectTextInterval * SelectSound::kBGM, m_handle[static_cast<int>(Handle::kSoundKnob)], true);
	DrawGraphF(seKnobPosX, kSoundKnobPos.y + kSelectTextInterval * SelectSound::kSE, m_handle[static_cast<int>(Handle::kSoundKnob)], true);

	// テキスト表示
	DrawStringFToHandle(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kSelectTextInterval * SelectSound::kBGM,
		"BGM", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kSelectTextInterval * SelectSound::kSE,
		"SE", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawFormatStringFToHandle(kSoundNumTextPos.x, kSoundNumTextPos.y + kSelectTextInterval * SelectSound::kBGM,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)], "%d", Sound::GetBgmVol());
	DrawFormatStringFToHandle(kSoundNumTextPos.x, kSoundNumTextPos.y + kSelectTextInterval * SelectSound::kSE,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)], "%d", Sound::GetSeVol());

}


/// <summary>
/// クレジット表記
/// </summary>
void SceneOption::DrawCredit()
{
	// テキスト表示
	DrawStringFToHandle(kSoundCreditTextPos.x, kSoundCreditTextPos.y,
		"・サウンド", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kSoundCreditTextPos.x + kCreditTextAdj, kSoundCreditTextPos.y + kCreditTextIntervel,
		"効果音ラボ\nOtoLogic\n魔王魂", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kModelCreditTextPos.x, kModelCreditTextPos.y,
		"・3Dモデル", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
	DrawStringFToHandle(kModelCreditTextPos.x + kCreditTextAdj, kModelCreditTextPos.y + kCreditTextIntervel,
		"Mixamo\nZENRIN City Asset SeriesTM", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOption)]);
}


/// <summary>
/// キーコンフィグ部分表示
/// </summary>
void SceneOption::DrawKeyConfig()
{
}
