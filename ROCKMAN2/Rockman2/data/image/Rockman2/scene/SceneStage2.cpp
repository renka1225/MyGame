#include "SceneStage2.h"
#include "DxLib.h"
#include "Pad.h"
#include "BgStage2.h"
#include "Player.h"

SceneStage2::SceneStage2()
{
	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };

	// �w�i�̃������m��
	m_pBg = new BgStage2;
	m_pBg->SetPlayer(m_pPlayer);
	m_pPlayer->SetBg(m_pBg);
}

SceneStage2::~SceneStage2()
{
	// �w�i�̃��������
	delete m_pBg;
	m_pBg = nullptr;

	// �v���C���[�̃��������
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void SceneStage2::Init()
{
	// ��ʑJ�ڂ̏�����
	m_isSceneGameOver = false;
	m_isSceneClear = false;

	// �v���C���[�̏�����
	m_pPlayer->Init();

	// �w�i�̏�����
	m_pBg->Init();
}

void SceneStage2::End()
{
}

void SceneStage2::Update()
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

void SceneStage2::Draw()
{
	// �w�i�̕`��
	m_pBg->Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

#ifndef _DEGUG
	DrawString(8, 8, "�X�e�[�W2", 0xffffff);
#endif

}
