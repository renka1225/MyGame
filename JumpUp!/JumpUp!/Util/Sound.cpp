#include "DxLib.h"
#include "Sound.h"
#include <cassert>

namespace
{
	// サウンドのデータ
	struct SoundData
	{
		const char* name;	// サウンドのファイル名
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
		{"data/sound/clearCheers.mp3"},
		{"data/sound/titleBGM.mp3"},
		{"data/sound/gameBGM.mp3"},
		{"data/sound/clearBGM.mp3"},
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
}
