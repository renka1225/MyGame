#include "SceneStage3.h"
#include "DxLib.h"
#include "Pad.h"
#include "BgStage3.h"
#include "Player.h"

SceneStage3::SceneStage3()
{
	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };

	// �w�i�̃������m��
	m_pBg = new BgStage3;
	m_pBg->SetPlayer(m_pPlayer);
	m_pPlayer->SetBg(m_pBg);
}

SceneStage3::~SceneStage3()
{
	// �w�i�̃��������
	delete m_pBg;
	m_pBg = nullptr;

	// �v���C���[�̃��������
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void SceneStage3::Init()
{
	// ��ʑJ�ڂ̏�����
	m_isSceneGameOver = false;
	m_isSceneClear = false;

	// �v���C���[�̏�����
	m_pPlayer->Init();

	// �w�i�̏�����
	m_pBg->Init();
}

void SceneStage3::End()
{
}

void SceneStage3::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �w�i�̍X�V
	m_pBg->Update();

	// �v���C���[�̍X�V
	m_pPlayer->Update();

#ifdef _DEBUG
	// C�L�[�ŃN���A��ʂɈړ�����悤�ɂ���
	if (Pad::IsTrigger(pad & PAD_INPUT_3))
	{
		m_isSceneClear = true; // �N���A��ʂɑJ��
	}
#endif
}

void SceneStage3::Draw()
{
	// �w�i�̕`��
	m_pBg->Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

#ifndef _DEGUG
	DrawString(8, 8, "�X�e�[�W3", 0xffffff);
#endif

}
