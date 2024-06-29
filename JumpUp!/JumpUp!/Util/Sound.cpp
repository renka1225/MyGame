#include "DxLib.h"
#include "Sound.h"
#include <cassert>

namespace
{
	// �T�E���h�̃f�[�^
	struct SoundData
	{
		const char* name;	// �T�E���h�̃t�@�C����
	};
}

namespace Sound
{
	std::vector<int> m_soundHandle;

	SoundData data[] =
	{
		{"data/sound/cursor.mp3"},
		{"data/sound/select.mp3"},
		{"data/sound/jump.mp3"},
		{"data/sound/clear.wav"},
		{"data/sound/titleBGM.mp3"},
		{"data/sound/gameBGM.mp3"},
		{"data/sound/clearBGM.mp3"},
	};

	/// <summary>
	/// ���[�h
	/// </summary>
	void Sound::Load()
	{
		Sound::m_soundHandle.resize(static_cast<int>(Sound::SoundKind::kNum));

		// �T�E���h�f�[�^����
		for (int i = 0; i < m_soundHandle.size(); i++)
		{
			m_soundHandle[i] = LoadSoundMem(data[i].name);
		}
	}


	/// <summary>
	/// �A�����[�h
	/// </summary>
	void Sound::UnLode()
	{
		for (const auto& handle : m_soundHandle)
		{
			DeleteSoundMem(handle);
		}
	}
}