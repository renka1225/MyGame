#include "ManagerSound.h"
#include <DxLib.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
ManagerSound::ManagerSound()
{
	m_startCountSE = LoadSoundMem("data/sound/countdown.mp3");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ManagerSound::~ManagerSound()
{
	DeleteSoundMem(m_startCountSE);
}
