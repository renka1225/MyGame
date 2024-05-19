#include "ManagerSound.h"
#include <DxLib.h>

/// <summary>
/// コンストラクタ
/// </summary>
ManagerSound::ManagerSound()
{
	m_cursorSE = LoadSoundMem("data/sound/cursor.mp3");
	m_selectSE = LoadSoundMem("data/sound/select.mp3");
	m_countSE = LoadSoundMem("data/sound/countdown.wav");
	m_jumpSE = LoadSoundMem("data/sound/jump.wav");
	m_missSE = LoadSoundMem("data/sound/miss.mp3");
	m_clearSE = LoadSoundMem("data/sound/clearSE.mp3");
	m_titleBgm = LoadSoundMem("data/sound/title.mp3");
	m_clearStagingBgm = LoadSoundMem("data/sound/clearStaging.mp3");
	m_playBgm = LoadSoundMem("data/sound/playing.mp3");
	m_clearBgm = LoadSoundMem("data/sound/clear.mp3");
}


/// <summary>
/// デストラクタ
/// </summary>
ManagerSound::~ManagerSound()
{
	DeleteSoundMem(m_cursorSE);
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_countSE);
	DeleteSoundMem(m_jumpSE);
	DeleteSoundMem(m_missSE);
	DeleteSoundMem(m_clearSE);
	DeleteSoundMem(m_titleBgm);
	DeleteSoundMem(m_clearStagingBgm);
	DeleteSoundMem(m_playBgm);
	DeleteSoundMem(m_clearBgm);
}