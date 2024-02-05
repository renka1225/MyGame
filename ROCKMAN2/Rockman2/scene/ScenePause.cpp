#include "ScenePause.h"
#include "Player.h"
#include "FontManager.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �|�[�Y��ʂ̃T�C�Y
	constexpr int kWidth = 782;
	constexpr int kHeight = 568;

	// ���j���[��ʂ̕\���ʒu
	constexpr float kPosX = Game::kScreenWidth * 0.5f - 400;
	constexpr float kPosY = 230.0f;

	// ���j���[��ʂ̕\���ړ���
	constexpr int kMenuMove = 25.0f;

	// ����I�𒆃J�[�\���̏����ʒu
	constexpr float kInitSelectShotPosY = 445.0f;
	// �|�[�Y��ʂ̑I�𒆃J�[�\���̏����ʒu
	constexpr float kPauseInitSelectPosY = 485.0f;

	// �I���J�[�\����X���W�̈ʒu
	constexpr float kCursorX = kPosX + 275;

	// �I���J�[�\���̈ړ��Ԋu
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

	// �摜�ǂݍ���
	m_menuBg = LoadGraph("data/image/UI/menuBg.png");
	m_selectHandle = LoadGraph("data/image/UI/shotSelect.png");

	// ���ǂݍ���
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
	ChangeVolumeSoundMem(255, m_menuSE);
}

void ScenePause::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*S�L�[orL�{�^���ŕ���؂�ւ���ʂ�\���A��\��*/
	if (Pad::IsTrigger(pad & PAD_INPUT_Y))
	{
		// SE��炷
		PlaySoundMem(m_menuSE, DX_PLAYTYPE_BACK, true);

		m_menuHeight = 0;
		m_shotSelect = SelectShot::kBuster;
		m_selectShotPos = { kCursorX, kInitSelectShotPosY };

		// ��ʕ\����\���؂�ւ�
		if (!m_isChangeMenuExist)
		{
			m_isPauseExist = false;		// �|�[�Y��ʔ�\��
			m_isChangeMenuExist = true; // ����؂�ւ���ʕ\��
		}
		else
		{
			// ���j���[��\�����o
			m_menuHeight -= kMenuMove;
			if (m_menuHeight < 0)
			{
				m_menuHeight = 0;
			}
			m_isChangeMenuExist = false;
		}
	}

	/*�p�b�h�̎O�{�������Ń|�[�Y�\���؂�ւ�*/
	if (Pad::IsTrigger(pad & PAD_INPUT_R))
	{
		// SE��炷
		PlaySoundMem(m_menuSE, DX_PLAYTYPE_BACK, true);
		m_menuHeight = 0;
		m_shotSelect = Pause::kBack;
		m_selectShotPos = { kCursorX, kPauseInitSelectPosY };

		// ��ʕ\����\���؂�ւ�
		if (!m_isPauseExist)
		{
			m_isPauseExist = true;			// ����؂�ւ���ʕ\��
			m_isChangeMenuExist = false;	// ���j���[��ʔ�\��
		}
		else
		{
			// ���j���[��\�����o
			m_menuHeight -= kMenuMove;
			if (m_menuHeight < 0)
			{
				m_menuHeight = 0;
			}
			m_isPauseExist = false;
		}
	}

	// ����؂�ւ��\����
	if (m_isChangeMenuExist)
	{
		// ���j���[�\�����o
		m_menuHeight += kMenuMove;
		if (m_menuHeight > kHeight * 0.5)
		{
			m_menuHeight = kHeight * 0.5;
		}

		UpdateChangeShot();
		return;
	}

	// �|�[�Y�\����
	else if (m_isPauseExist)
	{
		// ���j���[�\�����o
		m_menuHeight += kMenuMove;
		if (m_menuHeight > kHeight * 0.5)
		{
			m_menuHeight = kHeight * 0.5;
		}

		UpdatePause();
		return;
	}
}

void ScenePause::Draw()
{
	// ����؂�ւ���ʕ\��
	if (m_isChangeMenuExist)
	{
		// ���j���[��ʕ\�����o
		DrawExtendGraph(m_menuPos.x, m_menuPos.y - m_menuHeight, m_menuPos.x + kWidth, m_menuPos.y + m_menuHeight, m_menuBg, true);
		// change�̕����\��
		DrawStringToHandle(m_menuPos.x + 200 , m_menuPos.y - 150, "SHOT", 0xffffff, m_pFont->GetFont2());
		// �I�𒆂̃J�[�\����`��
		DrawGraph(m_selectShotPos.x, m_selectShotPos.y, m_selectHandle, true);
	}

	// �|�[�Y��ʕ\��
	if (m_isPauseExist)
	{
		// ���j���[��ʕ\�����o
		DrawExtendGraph(m_menuPos.x, m_menuPos.y - m_menuHeight, m_menuPos.x + kWidth, m_menuPos.y + m_menuHeight, m_menuBg, true);
		// PAUSE�̕����\��
		DrawStringToHandle(m_menuPos.x + 200, m_menuPos.y - 150, "PAUSE", 0xffffff, m_pFont->GetFont2());
		// �I�𒆂̃J�[�\����`��
		DrawGraph(m_selectPausePos.x , m_selectPausePos.y, m_selectHandle, true);
	}
}

/*����I����Ԃ��X�V*/
void ScenePause::UpdateChangeShot()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ���L�[����������I����Ԃ�1������
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		// SE��炷
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_shotSelect = (m_shotSelect + 1) % SelectShot::kShotSelectNum;
		m_selectShotPos.y += kSelectPosY; // �I�𒆃J�[�\�������Ɉړ�

		// �I���J�[�\������ԉ��ɂ�������l�p����ԏ�ɖ߂�
		if (m_selectShotPos.y > kInitSelectShotPosY + kSelectPosY * 4)
		{
			m_selectShotPos.y = kInitSelectShotPosY;
		}
	}
	// ���L�[����������I����Ԃ�1�グ��
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		// SE��炷
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_shotSelect = (m_shotSelect + (SelectShot::kShotSelectNum - 1)) % SelectShot::kShotSelectNum;
		m_selectShotPos.y -= kSelectPosY;	// �I�𒆃J�[�\������Ɉړ�

		if (m_selectShotPos.y < kInitSelectShotPosY)
		{
			m_selectShotPos.y = kInitSelectShotPosY + kSelectPosY * (SelectShot::kShotSelectNum - 1);
		}
	}

	//  Z�L�[orA�{�^���Ō��ݑI�𒆂̕���ɕύX����
	if (Pad::IsTrigger(pad & PAD_INPUT_A))
	{
		// SE��炷
		PlaySoundMem(m_selectSE, DX_PLAYTYPE_NORMAL, true);

		// �I�𒆂̕�����擾
		bool isBuster = false;
		bool isMetal = false;
		bool isFire = false;
		bool isLineMove = false;
		// ���j���[����邩�ǂ���	true:����
		bool isCloseMenu = true;

		switch (m_shotSelect)
		{
		case SelectShot::kBuster:
			// �o�X�^�[�ɐ؂�ւ���
			isBuster = true;
			break;
		case SelectShot::kMetal:
			// ���^���ɐ؂�ւ���
			isMetal = true;
			break;
		case SelectShot::kFire:
			// �t�@�C�A�ɐ؂�ւ���
			isFire = true;
			break;
		case SelectShot::kLine:
			// 2���ɐ؂�ւ���
			isLineMove = true;
			break;
		case SelectShot::kFullRecovery:
			// E�ʂ�1�ł������Ă�����HP�S��
			if (m_pPlayer->GetFullHpRecovery() > 0)
			{
				m_pPlayer->HpFullRecovery();
			}
			isCloseMenu = false; // �|�[�Y��ʂ���Ȃ��悤�ɂ���
			break;
		default:
			break;
		}

		// �v���C���[�̕����ύX����
		if (m_shotSelect != SelectShot::kFullRecovery)
		{
			m_pPlayer->ChangeShot(isBuster, isMetal, isFire, isLineMove);
		}
		// �|�[�Y��ʂ����
		if (isCloseMenu)
		{
			m_isChangeMenuExist = false;
		}
	}
}

/*�|�[�Y��ʑI����Ԃ��X�V*/
void ScenePause::UpdatePause()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ���L�[����������I����Ԃ�1������
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		// SE��炷
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_pauseSelect = (m_pauseSelect + 1) % Pause::kSelectNum;
		m_selectPausePos.y += kSelectPosY; // �I�𒆃J�[�\�������Ɉړ�

		// �I�𒆃J�[�\������ԉ��ɂ�������J�[�\������ԏ�ɖ߂�
		if (m_selectPausePos.y > kPauseInitSelectPosY + kSelectPosY * (Pause::kSelectNum - 1))
		{
			m_selectPausePos.y = kPauseInitSelectPosY;
		}
	}
	// ���L�[����������I����Ԃ�1�グ��
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		// SE��炷
		PlaySoundMem(m_cursorSE, DX_PLAYTYPE_BACK, true);

		m_pauseSelect = (m_pauseSelect + (Pause::kSelectNum - 1)) % Pause::kSelectNum;
		m_selectPausePos.y -= kSelectPosY;	// �I�𒆃J�[�\������Ɉړ�

		if (m_selectPausePos.y < kPauseInitSelectPosY)
		{
			m_selectPausePos.y = kPauseInitSelectPosY + kSelectPosY * (Pause::kSelectNum - 1);
		}
	}

	// Z�L�[orA�{�^���Ō���
	if (Pad::IsTrigger(pad & PAD_INPUT_A))
	{
		// SE��炷
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
