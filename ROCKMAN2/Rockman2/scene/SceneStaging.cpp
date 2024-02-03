#include "SceneStaging.h"
#include "Game.h"
#include "FontManager.h"
#include "DxLib.h"

namespace 
{
	/*���o����*/
	constexpr float kStartTime = 600.0f;	// �X�^�[�g���o
	constexpr float kClearTime = 180.0f;	// �N���A���o
	constexpr float kGameoverTime = 300.0f;
}

SceneStaging::SceneStaging():
	m_isStart(true),
	m_isClear(false),
	m_startTime(0.0f),
	m_clearTime(0.0f),
	m_gameoverTime(0.0f)
{
	m_startSE = LoadSoundMem("data/sound/BGM/start.mp3");
	m_clearSE = LoadSoundMem("data/sound/SE/clear.wav");
}

SceneStaging::~SceneStaging()
{
	DeleteSoundMem(m_startSE);
	DeleteSoundMem(m_clearSE);
}

void SceneStaging::Init()
{
	m_isStart = true;
	m_isClear = false;
	m_startTime = kStartTime;
	m_clearTime = kClearTime;
	m_gameoverTime = kGameoverTime;

}

void SceneStaging::Update()
{
	// �X�^�[�g���o
	m_startTime--;

	if (m_startTime <= 0)
	{
		m_isStart = false;
	}

}

void SceneStaging::Draw()
{
	if (m_isStart)
	{
		DrawBox(0, Game::kScreenHeight * 0.5f - 200, Game::kScreenWidth, Game::kScreenHeight * 0.5f + 200, 0xdda0dd, true);
		DrawStringToHandle(Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.5f - 100, "�G�����ׂĂ������I\n", 0xffffff, m_pFont->GetFontStaging());
		//DrawFormatStringToHandle(Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.5f + 100, 0xffffff, m_pFont->GetFontStaging(), "%d / %d\n", m_enemyTotalNum, m_enemyTotalNum);
	}

#ifdef _DEBUG
	// MEMO:�X�^�[�g���o�̕\���m�F
	printfDx("�X�^�[�g���o��\n");
#endif

}

void SceneStaging::Start()
{
	PlaySoundMem(m_startSE, DX_PLAYTYPE_BACK, true);
}

void SceneStaging::Clear()
{
	PlaySoundMem(m_clearSE, DX_PLAYTYPE_BACK, true);
}
