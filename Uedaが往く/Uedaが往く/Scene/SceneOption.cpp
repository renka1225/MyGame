#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "Sound.h"
#include "Game.h"
#include "UI.h"
#include "SceneOption.h"

// 定数
namespace
{
	constexpr int kBackColor = 0xdddddd;				 // 背景の色
	constexpr int kBackBoxColor = 0x494949;				 // 四角の色
	constexpr int kBackBoxLTPos = 140;					 // 四角の左上位置
	constexpr int kBackBoxWidth = 490;					 // 四角の幅
	const Vec2 kSelectTextPos = { 200, 300 };			 // 選択テキスト表示位置
	constexpr float kSelectTextInterval = 100.0f;		 // 選択テキスト表示間隔
	const Vec2 kCursorPos = { 140, 290 };				 // カーソル表示位置
	const Vec2 kAfterSelectTextPos = { 800, 310 };		 // 選択後テキスト表示位置
	constexpr float kAfterSelectTextInterval = 100.0f;	 // 選択後テキスト表示間隔
	const Vec2 kAfterSelectCursorPos = { 800, 300 };	 // 選択後カーソル表示位置
}


/// <summary>
/// コンストラクタ
/// </summary>
SceneOption::SceneOption(std::shared_ptr<SceneBase> pScene) :
	m_pPrevScene(pScene),
	m_afterSelect(SelectSound::kBGM),
	m_isSound(false),
	m_isKeyConfig(false)
{
}


/// <summary>
/// デストラクタ
/// </summary>
SceneOption::~SceneOption()
{
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
	else if (m_isKeyConfig)
	{
		UpdateSelect(input, SelectKeyConfig::kSelectKeyNum);
	}
	else
	{
		UpdateSelect(input, Select::kSelectNum);
	}

	m_pUI->Update();

	if (input.IsTriggered("back"))
	{
		if (m_isSound || m_isKeyConfig)
		{
			m_isSound = false;
			m_isKeyConfig = false;
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
			m_isKeyConfig = false;
			m_afterSelect = SelectSound::kBGM;
		}
		else if (m_select == Select::kKeyConfig)
		{
			m_isSound = false;
			m_isKeyConfig = true;
			m_afterSelect = SelectKeyConfig::kXButton;
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
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBackColor, true);
	// 背景の四角部分表示
	DrawBox(kBackBoxLTPos, 0, kBackBoxLTPos + kBackBoxWidth, Game::kScreenHeight, kBackBoxColor, true);

	// カーソル表示
	if (!m_isSound && !m_isKeyConfig)
	{
		m_pUI->DrawCursor(kCursorPos, m_select, kSelectTextInterval);
	}
	else
	{
		m_pUI->DrawCursor(kAfterSelectCursorPos, m_afterSelect, kAfterSelectTextInterval);
	}

	// テキスト表示
	DrawDispText();

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "オプション画面", 0xffffff);
	DrawFormatString(0, 100, 0xffffff, "状態:%d", m_afterSelect);
	DrawFormatString(0, 120, 0xffffff, "状態:%d", m_select);
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
		//// 音量を下げる
		//if (input.IsPressing("left"))
		//{
		//	printfDx("BGM:-1\n");
		//}
		//// 音量を上げる
		//else if (input.IsPressing("right"))
		//{
		//	printfDx("BGM:+1\n");
		//}

		Sound::ChangeBgmVol(input);
	}
	// SE選択中の場合
	if (m_afterSelect == SelectSound::kSE)
	{
		//// 音量を下げる
		//if (input.IsPressing("left"))
		//{
		//	printfDx("SE:-1\n");
		//}
		//// 音量を上げる
		//else if (input.IsPressing("right"))
		//{
		//	printfDx("SE:+1\n");
		//}

		Sound::ChangeSeVol(input);
	}
}


/// <summary>
/// キー更新
/// </summary>
/// <param name="input">入力状態</param>
void SceneOption::UpdateKeyConfig(Input& input)
{
}


/// <summary>
/// テキスト表示
/// </summary>
void SceneOption::DrawDispText()
{
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kSound, "サウンド", 0xffffff);
	DrawStringF(kSelectTextPos.x, kSelectTextPos.y + kSelectTextInterval * Select::kKeyConfig, "ボタン配置", 0xffffff);

	if (m_isSound)
	{
		DrawStringF(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kAfterSelectTextInterval * SelectSound::kBGM, "BGM", 0xffffff);
		DrawStringF(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kAfterSelectTextInterval * SelectSound::kSE, "SE", 0xffffff);
	}
	else if (m_isKeyConfig)
	{
		DrawStringF(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kAfterSelectTextInterval * SelectKeyConfig::kXButton, "X", 0xffffff);
		DrawStringF(kAfterSelectTextPos.x, kAfterSelectTextPos.y + kAfterSelectTextInterval * SelectKeyConfig::kYButton, "Y", 0xffffff);
	}
}