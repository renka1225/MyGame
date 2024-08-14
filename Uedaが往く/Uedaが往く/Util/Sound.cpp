#include "DxLib.h"
#include "Sound.h"
#include <cassert>

namespace
{
	// �T�E���h�̃f�[�^
	struct SoundData
	{
		const char* name;	// �T�E���h�̃t�@�C����
		int volumePal;		// ����
	};
	constexpr int kMaxVolumePal = 255; // �ő剹��
}

namespace Sound
{
	std::vector<int> m_soundHandle;

	SoundData data[] =
	{
		{"data/sound/SE/cursor.mp3", kMaxVolumePal},
		{"data/sound/SE/select.mp3", kMaxVolumePal},
		{"data/sound/SE/attack.mp3", kMaxVolumePal},
		{"data/sound/SE/clearCheers.mp3", kMaxVolumePal},
		{"data/sound/BGM/title.mp3", kMaxVolumePal},
		{"data/sound/BGM/stageSelect.mp3", kMaxVolumePal},
		{"data/sound/BGM/stage1.mp3", kMaxVolumePal},
		{"data/sound/BGM/stage2.mp3", kMaxVolumePal},
		{"data/sound/BGM/clear.mp3", kMaxVolumePal},
		{"data/sound/BGM/gameover.mp3", kMaxVolumePal},
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


	/// <summary>
	/// ���ʂ�ύX����
	/// </summary>
	void ChangeVol()
	{
		for (int i = 0; i < m_soundHandle.size(); i++)
		{
			ChangeVolumeSoundMem(data[i].volumePal, i);
		}
	}
}
