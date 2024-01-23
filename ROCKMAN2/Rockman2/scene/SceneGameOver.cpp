#include "SceneGameOver.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

SceneGameOver::SceneGameOver():
	m_isSceneRetry(false),
	m_isSceneSelect(false),
	m_isSceneTitle(false)
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
	m_isSceneRetry = false;
	m_isSceneSelect = false;
	m_isSceneTitle = false;
}

void SceneGameOver::Update()
{
	// TODO:���g���C�ł���悤�ɂ���

#ifdef _DEBUG
	// C�L�[����������X�e�[�W�I����ʂɈړ�����
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_isSceneSelect = true;
	}
#endif

}

void SceneGameOver::Draw()
{
	DrawString(Game::kScreenWidth / 2 - 30, Game::kScreenHeight / 2 - 30, "�Q�[���I�[�o�[", 0xff0000);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, "Press C", 0xff0000);
}

void SceneGameOver::End()
{
}

