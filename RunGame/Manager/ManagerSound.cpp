#include "ManagerSound.h"
#include <DxLib.h>

/// <summary>
/// コンストラクタ
/// </summary>
ManagerSound::ManagerSound()
{
	m_startCountSE = LoadSoundMem("data/sound/countdown.mp3");
}


/// <summary>
/// デストラクタ
/// </summary>
ManagerSound::~ManagerSound()
{
	DeleteSoundMem(m_startCountSE);
}
