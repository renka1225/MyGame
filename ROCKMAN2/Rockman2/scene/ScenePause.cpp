#include "ScenePause.h"
#include "Player.h"
#include "FontManager.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// ポーズ画面のサイズ
	constexpr int kWidth = 280;
	constexpr int kHeight = 480;

	// メニュー画面の表示位置
	constexpr float kPosX = 830.0f;
	constexpr float kPosY = 300.0f;

	// 武器選択中カーソルの初期位置
	constexpr float kInitSelectShotPosY = 394.0f;
	// ポーズ画面の選択中カーソルの初期位置
	constexpr float kPauseInitSelectPosY = 464.0f;
	// 選択カーソルの描画の間隔
	constexpr float kSelectPosY = 70.0f;
}

ScenePause::ScenePause(Player* pPlayer):
	m_shotSelect(SelectShot::kBuster),
	m_pauseSelect(Pause::kBack),
	m_pPlayer(pPlayer),
	m_isChangeMenuExist(false),
	m_isPauseExist(false),
	m_isRetry(false),
	m_isTitle(false)
{
	m_pFont = new FontManager;
	
	// 音読み込み
	m_menuSE = LoadSoundMem("data/sound/SE/menu.mp3");
	m_selectSE = LoadSoundMem("data/sound/SE/select.wav");
	m_cursorSE = LoadSoundMem("data/sound/SE/cursor.mp3");
}

ScenePause::~ScenePause()
{
	delete m_pFont;

	DeleteSoundMem(m_menuSE);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}

void ScenePause::Init()
{
	m_isChangeMenuExist = false;
	m_shotSelect = SelectShot::kBuster;
	m_pauseSelect = Pause::kBack;
	m_selectShotPos.x = 0;
	m_selectShotPos.y = kInitSelectShotPosY;
	m_selectPausePos.x = 0;
	m_selectPausePos.y = kPauseInitSelectPosY;
}

void ScenePause::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*Aキーを押したらメニューを表示、非表示*/
	if (Pad::IsTrigger(pad & PAD_INPUT_4))
	{
		// SEを鳴らす
		PlaySoundMem(m_menuSE, DX_PLAYTYPE_BACK, true);

		if (!m_isChangeMenuExist)
		{
			m_isPauseExist = false;		// ポーズ画面非表示
			m_isChangeMenuExist = true; // メニュー画面表示
		}
		else
		{
			m_isChangeMenuExist = false;
		}
	}

	/*ESCキーを押したらポーズ表示*/
	if (Pad::IsTrigger(pad & PAD_INPUT_9))
	{
		// SEを鳴らす
		PlaySoundMem(m_menuSE, DX_PLAYTYPE_BACK, true);

		if (!m_isPauseExist)
		{
			m_isPauseExist = true;			// ポーズ画面表示
			m_isChangeMenuExist = false;	// メニュー画面非表示
		}
		else
		{
			m_isPauseExist = false;
		}
	}

	// 武器切り替え表示中
	if (m_isChangeMenuExist)
	{
		UpdateChangeShot();
		return;
	}

	// ポーズ表示中
	else if (m_isPauseExist)
	{
		UpdatePause();
		return;
	}
}

void ScenePause::Draw()
{
	// 武器切り替え画面表示
	if (m_isChangeMenuExist)
	{
		// TODO:フェードインアウト
		
		SetDrawBlendMode(DX_BLENDMODE_MULA, 200);
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 表示モードを元に戻す
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0xffffff, false); // 枠を描画
		DrawStringToHandle(kPosX ,350, "MENU", 0xffffff, m_pFont->GetFont());

		// 選択中のカーソルを描画
		DrawBox(kPosX + 5, m_selectShotPos.y, kPosX + 255, m_selectShotPos.y + 30, 0x00bfff, false);
	}

	// ポーズ画面表示
	if (m_isPauseExist)
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 200);
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 表示モードを元に戻す
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0xffffff, false); // 枠を描画
		DrawStringToHandle(kPosX, 350, "PAUSE", 0xffffff,  m_pFont->GetFont());

		// 選択中のカーソルを描画
		DrawBox(kPosX + 5, m_selectPausePos.y, kPosX + 255, m_selectPausePos.y + 30, 0x00bfff, false);
	}
}

/*武器選択状態を更新*/
void ScenePause::UpdateChangeShot()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ↓キーを押したら選択状態を1つ下げる
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		m_shotSelect = (m_shotSelect + 1) % SelectShot::kShotSelectNum;
		m_selectShotPos.y += kSelectPosY; // 選択中の四角を下に移動

		// 選択中の四角が一番下にだったら四角を一番上に戻す
		if (m_selectShotPos.y > kInitSelectShotPosY + kSelectPosY * 4)
		{
			m_selectShotPos.y = kInitSelectShotPosY;
		}
	}
	// ↑キーを押したら選択状態を1つ上げる
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		m_shotSelect = (m_shotSelect + (SelectShot::kShotSelectNum - 1)) % SelectShot::kShotSelectNum;
		m_selectShotPos.y -= kSelectPosY;	// 選択中カーソルを上に移動

		if (m_selectShotPos.y < kInitSelectShotPosY)
		{
			m_selectShotPos.y = kInitSelectShotPosY + kSelectPosY * (SelectShot::kShotSelectNum - 1);
		}
	}

	// Xキーを押したら現在選択中の武器に変更する
	if (Pad::IsTrigger(pad & PAD_INPUT_2))
	{
		// SEを鳴らす
		PlaySoundMem(m_selectSE, DX_PLAYTYPE_NORMAL, true);

		// 選択中の武器を取得
		bool isBuster = false;
		bool isMetal = false;
		bool isFire = false;
		bool isLineMove = false;
		// メニューを閉じるかどうか	true:閉じる
		bool isCloseMenu = true;

		switch (m_shotSelect)
		{
		case SelectShot::kBuster:
			// バスターに切り替える
			isBuster = true;
			break;
		case SelectShot::kMetal:
			// メタルに切り替える
			isMetal = true;
			break;
		case SelectShot::kFire:
			// ファイアに切り替える
			isFire = true;
			break;
		case SelectShot::kLine:
			// 2号に切り替える
			isLineMove = true;
			break;
		case SelectShot::kFullRecovery:
			// E缶を1つでも持っていたらHP全回復
			if (m_pPlayer->GetFullHpRecovery() > 0)
			{
				m_pPlayer->HpFullRecovery();
			}
			isCloseMenu = false; // ポーズ画面を閉じないようにする
			break;
		default:
			break;
		}

		// プレイヤーの武器を変更する
		if (m_shotSelect != SelectShot::kFullRecovery)
		{
			m_pPlayer->ChangeShot(isBuster, isMetal, isFire, isLineMove);
		}
		// ポーズ画面を閉じる
		if (isCloseMenu)
		{
			m_isChangeMenuExist = false;
		}
	}
}

/*ポーズ画面選択状態を更新*/
void ScenePause::UpdatePause()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ↓キーを押したら選択状態を1つ下げる
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		// SEを鳴らす
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_pauseSelect = (m_pauseSelect + 1) % Pause::kSelectNum;
		m_selectPausePos.y += kSelectPosY; // 選択中カーソルを下に移動

		// 選択中カーソルが一番下にだったらカーソルを一番上に戻す
		if (m_selectPausePos.y > kPauseInitSelectPosY + kSelectPosY * (Pause::kSelectNum - 1))
		{
			m_selectPausePos.y = kPauseInitSelectPosY;
		}
	}
	// ↑キーを押したら選択状態を1つ上げる
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		// SEを鳴らす
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_pauseSelect = (m_pauseSelect + (Pause::kSelectNum - 1)) % Pause::kSelectNum;
		m_selectPausePos.y -= kSelectPosY;	// 選択中カーソルを上に移動

		if (m_selectPausePos.y < kPauseInitSelectPosY)
		{
			m_selectPausePos.y = kPauseInitSelectPosY + kSelectPosY * (Pause::kSelectNum - 1);
		}
	}

	// Xキーで決定
	if (Pad::IsTrigger(pad & PAD_INPUT_2))
	{
		// SEを鳴らす
		PlaySoundMem(m_selectSE, DX_PLAYTYPE_NORMAL, true);

		switch (m_pauseSelect)
		{
		case kBack:
			m_isPauseExist = false;
			break;
		case kRetry:
			m_isRetry = true;
			break;
		case kTitle:
			m_isTitle = true;
			break;
		default:
			break;
		}
	}
}
