#include "ManagerSound.h"
#include <DxLib.h>

/// <summary>
/// コンストラクタ
/// </summary>
ManagerSound::ManagerSound()
{
	//m_selectSE = LoadSoundMem("data/sound/select.mp3");
	//m_determineSE = LoadSoundMem("data/sound/determine.mp3");
	//m_noticeSE = LoadSoundMem("data/sound/notice.mp3");
	//m_jumpSE = LoadSoundMem("data/sound/jump.wav");
	//m_titleBgm = LoadSoundMem("data/sound/title.mp3");
	//m_playBgm = LoadSoundMem("data/sound/play.mp3");
	//m_gameoverBgm = LoadSoundMem("data/sound/gameover.mp3");
	//m_clearBgm = LoadSoundMem("data/sound/clear.mp3");

	m_count3SE = LoadSoundMem("data/sound/count/san.wav");
	m_count2SE = LoadSoundMem("data/sound/count/ni.wav");
	m_count1SE = LoadSoundMem("data/sound/count/ichi.wav");
}


/// <summary>
/// デストラクタ
/// </summary>
ManagerSound::~ManagerSound()
{
	//DeleteSoundMem(m_selectSE);
	//DeleteSoundMem(m_determineSE);
	//DeleteSoundMem(m_noticeSE);
	//DeleteSoundMem(m_jumpSE);
	//DeleteSoundMem(m_titleBgm);
	//DeleteSoundMem(m_playBgm);
	//DeleteSoundMem(m_gameoverBgm);
	//DeleteSoundMem(m_clearBgm);

	DeleteSoundMem(m_count3SE);
	DeleteSoundMem(m_count2SE);
	DeleteSoundMem(m_count1SE);
}