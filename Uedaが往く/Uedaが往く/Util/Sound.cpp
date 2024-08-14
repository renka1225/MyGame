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
	constexpr int kMaxVolumePal = 255; // 最大音量
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
