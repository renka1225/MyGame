#include "ScenePause.h"
#include "Player.h"
#include "FontManager.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �|�[�Y��ʂ̃T�C�Y
	constexpr int kWidth = 280;
	constexpr int kHeight = 480;

	// ���j���[��ʂ̕\���ʒu
	constexpr float kPosX = 830.0f;
	constexpr float kPosY = 300.0f;

	// �I�𒆃J�[�\����Y���W�̏����ʒu
	constexpr float kInitSelectPosY = 394.0f;
	// �I���J�[�\���̕`��̊Ԋu
	constexpr float kSelectPosY = 70.0f;
}

ScenePause::ScenePause(Player* pPlayer):
	m_shotSelect(SelectShot::kBuster),
	m_pauseSelect(Pause::kBack),
	m_pPlayer(pPlayer),
	m_isChangeMenuExist(false),
	m_isPauseExist(false),
	m_isBack(false),
	m_isRetry(false),
	m_isTitle(false)
{
	m_pFont = new FontManager;
}

ScenePause::~ScenePause()
{
	delete m_pFont;
}

void ScenePause::Init()
{
	m_isChangeMenuExist = false;
	m_shotSelect = SelectShot::kBuster;
	m_pauseSelect = Pause::kBack;
	m_selectPos.x = 0;
	m_selectPos.y = kInitSelectPosY;
}

void ScenePause::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*A�L�[���������烁�j���[��\���A��\��*/
	if (Pad::IsTrigger(pad & PAD_INPUT_4))
	{
		if (!m_isChangeMenuExist)
		{
			m_isPauseExist = false;		// �|�[�Y��ʔ�\��
			m_isChangeMenuExist = true; // ���j���[��ʕ\��
		}
		else
		{
			m_isChangeMenuExist = false;
		}
	}

	/*ESC�L�[����������|�[�Y�\��*/
	if (Pad::IsTrigger(pad & PAD_INPUT_9))
	{
		if (!m_isPauseExist)
		{
			m_isPauseExist = true;			// �|�[�Y��ʕ\��
			m_isChangeMenuExist = false;	// ���j���[��ʔ�\��
		}
		else
		{
			m_isPauseExist = false;
		}
	}

	// ����؂�ւ��\����
	if (m_isChangeMenuExist)
	{
		UpdateChangeShot();
		return;
	}

	// �|�[�Y�\����
	else if (m_isPauseExist)
	{
		UpdatePause();
		return;
	}
}

void ScenePause::Draw()
{
	// ����؂�ւ���ʕ\��
	if (m_isChangeMenuExist)
	{
		// TODO:�t�F�[�h�C���A�E�g
		
		SetDrawBlendMode(DX_BLENDMODE_MULA, 200);
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �\�����[�h�����ɖ߂�
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0xffffff, false); // �g��`��
		DrawStringToHandle(kPosX ,350, "MENU", 0xffffff, m_pFont->GetFont());

		// �I�𒆂̃J�[�\����`��
		DrawBox(kPosX + 5, m_selectPos.y, kPosX + 255, m_selectPos.y + 30, 0x00bfff, false);
	}

	// �|�[�Y��ʕ\��
	if (m_isPauseExist)
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 200);
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �\�����[�h�����ɖ߂�
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0xffffff, false); // �g��`��
		DrawStringToHandle(kPosX, 350, "PAUSE", 0xffffff,  m_pFont->GetFont());

		// �I�𒆂̃J�[�\����`��
		DrawBox(kPosX + 5, m_selectPos.y, kPosX + 255, m_selectPos.y + 30, 0x00bfff, false);
	}
}

/*����I����Ԃ��X�V*/
void ScenePause::UpdateChangeShot()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ���L�[����������I����Ԃ�1������
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		m_shotSelect = (m_shotSelect + 1) % SelectShot::kShotSelectNum;
		m_selectPos.y += kSelectPosY; // �I�𒆂̎l�p�����Ɉړ�

		// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
		if (m_selectPos.y > kInitSelectPosY + kSelectPosY * 4)
		{
			m_selectPos.y = kInitSelectPosY;
		}
	}
	// ���L�[����������I����Ԃ�1�グ��
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		m_shotSelect = (m_shotSelect + (kSelectNum - 1)) % SelectShot::kShotSelectNum;
		m_selectPos.y -= kSelectPosY;	// �I�𒆂̎l�p����Ɉړ�

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectPosY * 4;
		}
	}

	// X�L�[���������猻�ݑI�𒆂̕���ɕύX����
	if (Pad::IsTrigger(pad & PAD_INPUT_2))
	{
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
		m_pauseSelect = (m_pauseSelect + 1) % Pause::kSelectNum;
		m_selectPos.y += kSelectPosY; // �I�𒆂̎l�p�����Ɉړ�

		// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
		if (m_selectPos.y > kInitSelectPosY + kSelectPosY * 2)
		{
			m_selectPos.y = kInitSelectPosY;
		}
	}
	// ���L�[����������I����Ԃ�1�グ��
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		m_pauseSelect = (m_pauseSelect + (Pause::kSelectNum - 1)) % Pause::kSelectNum;
		m_selectPos.y -= kSelectPosY;	// �I�𒆂̎l�p����Ɉړ�

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectPosY * 2;
		}
	}

	// X�L�[�Ō���
	switch (m_pauseSelect)
	{
	case kBack:
		if (Pad::IsTrigger(pad & PAD_INPUT_2))
		{
			m_isBack = true;
		}
		break;
	case kRetry:
		if (Pad::IsTrigger(pad & PAD_INPUT_2))
		{
			m_isRetry = true;
		}
		break;
	case kTitle:
		if (Pad::IsTrigger(pad & PAD_INPUT_2))
		{
			m_isTitle = true;
		}
		break;
	default:
		break;
	}

	// �|�[�Y��ʂ����
	if (m_isBack)
	{
		m_isPauseExist = false;
	}
}
