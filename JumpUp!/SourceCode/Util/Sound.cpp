#include "DxLib.h"
#include "Sound.h"
#include <cassert>

namespace
{
	// サウンドのデータ
	struct SoundData
	{
		const char* name;	// サウンドのファイル名
		int volumePal;		// 音量
	};
}

namespace Sound
{
	std::vector<int> m_soundHandle;

	SoundData data[] =
	{
		{"data/sound/cursor.mp3", 255},
		{"data/sound/select.mp3", 255},
		{"data/sound/run.mp3", 255},
		{"data/sound/jump.mp3", 255},
		{"data/sound/clear.wav", 255},
		{"data/sound/clearCheers.mp3", 255},
		{"data/sound/titleBGM.mp3", 200},
		{"data/sound/gameBGM.mp3", 200},
		{"data/sound/clearBGM.mp3", 200},
	};

	/// <summary>
	/// ロード
	/// </summary>
	void Sound::Load()
	{
		Sound::m_soundHandle.resize(static_cast<int>(Sound::SoundKind::kNum));

		// サウンドデータ生成
		for (int i = 0; i < m_soundHandle.size(); i++)
		{
			m_soundHandle[i] = LoadSoundMem(data[i].name);
		}
	}


	/// <summary>
	/// アンロード
	/// </summary>
	void Sound::UnLode()
	{
		for (const auto& handle : m_soundHandle)
		{
			DeleteSoundMem(handle);
		}
	}


	/// <summary>
	/// 音量を変更する
	/// </summary>
	void ChangeVol()
	{
		for (int i = 0; i < m_soundHandle.size(); i++)
		{
			ChangeVolumeSoundMem(data[i].volumePal, i);
		}
	}
}
