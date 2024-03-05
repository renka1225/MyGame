#include "ScenePause.h"
#include "Player.h"
#include "FontManager.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"


/// <summary>
/// 定数
/// </summary>
namespace
{
	// 最大音量
	constexpr int kVolumeMax = 255;

	// ポーズ画面のサイズ
	constexpr int kWidth = 782;
	constexpr int kHeight = 568;

	// メニュー画面の表示位置
	constexpr float kPosX = Game::kScreenWidth * 0.5f - 400;
	constexpr float kPosY = 230.0f;
	// メニュー文字表示位置調整
	constexpr float kTextPosXAdjustment = 180.0f;
	constexpr float kTextPosYAdjustment = 150.0f;
	// メニュー画面の表示移動量
	constexpr int kMenuMove = 25;

	// 武器選択中カーソルの初期位置
	constexpr float kInitSelectShotPosY = 445.0f;
	// ポーズ画面の選択中カーソルの初期位置
	constexpr float kPauseInitSelectPosY = 485.0f;
	// 選択カーソルのX座標の位置
	constexpr float kCursorX = kPosX + 275;

	// 選択カーソルの移動間隔
	constexpr float kSelectPosY = 70.0f;
}


ScenePause::ScenePause(Player* pPlayer):
	m_shotSelect(SelectShot::kBuster),
	m_pauseSelect(Pause::kBack),
	m_pPlayer(pPlayer),
	m_menuHeight(0),
	m_selectShotPos({ kCursorX, kInitSelectShotPosY }),
	m_isChangeMenuExist(false),
	m_isPauseExist(false),
	m_isRetry(false),
	m_isTitle(false)
{
	m_pFont = new FontManager;

	// 画像読み込み
	m_menuBg = LoadGraph("data/image/UI/menuBg.png");
	m_selectHandle = LoadGraph("data/image/UI/shotSelect.png");

	// 音読み込み
	m_menuSE = LoadSoundMem("data/sound/SE/menu.mp3");
	m_selectSE = LoadSoundMem("data/sound/SE/select.wav");
	m_cursorSE = LoadSoundMem("data/sound/SE/cursor.mp3");
}


ScenePause::~ScenePause()
{
	delete m_pFont;
	DeleteGraph(m_menuBg);
	DeleteGraph(m_selectHandle);
	DeleteSoundMem(m_menuSE);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_cursorSE);
}


/// <summary>
/// 初期化
/// </summary>
void ScenePause::Init()
{
	m_isChangeMenuExist = false;
	m_isPauseExist = false;
	m_isRetry = false;
	m_isTitle = false;
	m_shotSelect = SelectShot::kBuster;
	m_pauseSelect = Pause::kBack;
	m_menuHeight = 0;
	m_menuPos = { kPosX, Game::kScreenHeight * 0.5f };
	m_selectShotPos = { kCursorX, kInitSelectShotPosY };
	m_selectPausePos = { kCursorX, kPauseInitSelectPosY };
	ChangeVolumeSoundMem(kVolumeMax, m_menuSE);
}


/// <summary>
/// 更新
/// </summary>
void ScenePause::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*SキーorLボタンで武器切り替え画面を表示、非表示*/
	if (Pad::IsTrigger(pad & PAD_INPUT_Y))
	{
		// SEを鳴らす
		PlaySoundMem(m_menuSE, DX_PLAYTYPE_BACK, true);

		m_menuHeight = 0;
		m_shotSelect = SelectShot::kBuster;
		m_selectShotPos = { kCursorX, kInitSelectShotPosY };

		// 画面表示非表示切り替え
		if (!m_isChangeMenuExist)
		{
			m_isPauseExist = false;		// ポーズ画面非表示
			m_isChangeMenuExist = true; // 武器切り替え画面表示
		}
		else
		{
			// メニュー非表示演出
			m_menuHeight -= kMenuMove;
			if (m_menuHeight < 0)
			{
				m_menuHeight = 0;
			}
			m_isChangeMenuExist = false;
		}
	}

	/*パッドの三本線部分でポーズ表示切り替え*/
	if (Pad::IsTrigger(pad & PAD_INPUT_R))
	{
		// SEを鳴らす
		PlaySoundMem(m_menuSE, DX_PLAYTYPE_BACK, true);
		m_menuHeight = 0;
		m_shotSelect = Pause::kBack;
		m_selectShotPos = { kCursorX, kPauseInitSelectPosY };

		// 画面表示非表示切り替え
		if (!m_isPauseExist)
		{
			m_isPauseExist = true;			// 武器切り替え画面表示
			m_isChangeMenuExist = false;	// メニュー画面非表示
		}
		else
		{
			// メニュー非表示演出
			m_menuHeight -= kMenuMove;
			if (m_menuHeight < 0)
			{
				m_menuHeight = 0;
			}
			m_isPauseExist = false;
		}
	}

	// 武器切り替え表示中
	if (m_isChangeMenuExist)
	{
		// メニュー表示演出
		m_menuHeight += kMenuMove;
		if (m_menuHeight > kHeight * 0.5)
		{
			m_menuHeight = static_cast<int>(kHeight * 0.5);
		}

		UpdateChangeShot();
		return;
	}

	// ポーズ表示中
	else if (m_isPauseExist)
	{
		// メニュー表示演出
		m_menuHeight += kMenuMove;
		if (m_menuHeight > kHeight * 0.5)
		{
			m_menuHeight = static_cast<int>(kHeight * 0.5);
		}

		UpdatePause();
		return;
	}
}


/// <summary>
/// 描画
/// </summary>
void ScenePause::Draw()
{
	// 武器切り替え画面表示
	if (m_isChangeMenuExist)
	{
		// メニュー画面表示演出
		DrawExtendGraph(static_cast<int>(m_menuPos.x), static_cast<int>(m_menuPos.y - m_menuHeight), 
			static_cast<int>(m_menuPos.x + kWidth), static_cast<int>(m_menuPos.y + m_menuHeight), 
			m_menuBg, true);
		// changeの文字表示
		DrawStringToHandle(static_cast<int>(m_menuPos.x + kTextPosXAdjustment), static_cast<int>(m_menuPos.y - kTextPosYAdjustment), 
			"Menu", 
			0xffffff, m_pFont->GetFont3());
		// 選択中のカーソルを描画
		DrawGraph(static_cast<int>(m_selectShotPos.x), static_cast<int>(m_selectShotPos.y), m_selectHandle, true);
	}

	// ポーズ画面表示
	if (m_isPauseExist)
	{
		// メニュー画面表示演出
		DrawExtendGraph(static_cast<int>(m_menuPos.x), static_cast<int>(m_menuPos.y - m_menuHeight),
			static_cast<int>(m_menuPos.x + kWidth), static_cast<int>(m_menuPos.y + m_menuHeight), 
			m_menuBg, true);
		// PAUSEの文字表示
		DrawStringToHandle(static_cast<int>(m_menuPos.x + kTextPosXAdjustment), static_cast<int>(m_menuPos.y - kTextPosYAdjustment), 
			"Pause",
			0xffffff, m_pFont->GetFont3());
		// 選択中のカーソルを描画
		DrawGraph(static_cast<int>(m_selectPausePos.x), static_cast<int>(m_selectPausePos.y), m_selectHandle, true);
	}
}


/// <summary>
/// 武器選択状態更新
/// </summary>
void ScenePause::UpdateChangeShot()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ↓キーを押したら選択状態を1つ下げる
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		// SEを鳴らす
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_shotSelect = (m_shotSelect + 1) % SelectShot::kShotSelectNum;
		m_selectShotPos.y += kSelectPosY; // 選択中カーソルを下に移動

		// 選択カーソルが一番下にだったら四角を一番上に戻す
		if (m_selectShotPos.y > kInitSelectShotPosY + kSelectPosY * 4)
		{
			m_selectShotPos.y = kInitSelectShotPosY;
		}
	}
	// ↑キーを押したら選択状態を1つ上げる
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		// SEを鳴らす
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_shotSelect = (m_shotSelect + (SelectShot::kShotSelectNum - 1)) % SelectShot::kShotSelectNum;
		m_selectShotPos.y -= kSelectPosY;	// 選択中カーソルを上に移動

		if (m_selectShotPos.y < kInitSelectShotPosY)
		{
			m_selectShotPos.y = kInitSelectShotPosY + kSelectPosY * (SelectShot::kShotSelectNum - 1);
		}
	}

	//  ZキーorAボタンで現在選択中の武器に変更する
	if (Pad::IsTrigger(pad & PAD_INPUT_A))
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


/// <summary>
/// ポーズ画面選択状態更新
/// </summary>
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

	// ZキーorAボタンで決定
	if (Pad::IsTrigger(pad & PAD_INPUT_A))
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