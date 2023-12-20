#include "ScenePause.h"
#include "Player.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �|�[�Y��ʂ̃T�C�Y
	constexpr int kWidth = 280;
	constexpr int kHeight = 480;

	// �|�[�Y��ʂ̈ʒu
	constexpr int kPosX = (Game::kScreenWidth - kWidth) / 2;
	constexpr int kPosY = Game::kScreenHeight / 6;
}

ScenePause::ScenePause():
	m_pPlayer(nullptr),
	m_isExist(false)
{
}

ScenePause::~ScenePause()
{
}

void ScenePause::Init()
{
	m_isExist = false;
}

void ScenePause::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*A�L�[���������烁�j���[��\���A��\��*/
	if (Pad::IsTrigger(pad & PAD_INPUT_4))
	{
		if (!m_isExist)
		{
			m_isExist = true;
		}
		else
		{
			m_isExist = false;
		}
	}
}

void ScenePause::Draw()
{
	if (m_isExist)
	{
		// �|�[�Y��ʂ̎l�p��\��
		SetDrawBlendMode(DX_BLENDMODE_MULA, 200);
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);// �\�����[�h�����ɖ߂�
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0xffffff, false); // �g��`��
		DrawString(kPosX ,150, "�|�[�Y���", 0xffffff);
	}
}
