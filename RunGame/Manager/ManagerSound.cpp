#include "ManagerSound.h"
#include <DxLib.h>

/// <summary>
/// コンストラクタ
/// </summary>
ManagerSound::ManagerSound()
{
	m_selectSE = LoadSoundMem("data/sound/select.mp3");
	m_determineSE = LoadSoundMem("data/sound/determine.mp3");
	m_startCountSE = LoadSoundMem("data/sound/countdown.mp3");
}


/// <summary>
/// デストラクタ
/// </summary>
ManagerSound::~ManagerSound()
{
	DeleteSoundMem(m_selectSE);
	DeleteSoundMem(m_determineSE);
	DeleteSoundMem(m_startCountSE);
}
