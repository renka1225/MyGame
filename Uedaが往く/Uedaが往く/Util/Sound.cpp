#include "DxLib.h"
#include "Input.h"
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
	std::vector<int> m_bgmHandle;
	std::vector<int> m_seHandle;

	SoundData bgmData[] =
	{
		{"data/sound/BGM/title.mp3", kMaxVolumePal},
		{"data/sound/BGM/stageSelect.mp3", kMaxVolumePal},
		{"data/sound/BGM/stage1.mp3", kMaxVolumePal},
		{"data/sound/BGM/stage2.mp3", kMaxVolumePal},
		{"data/sound/BGM/clear.mp3", kMaxVolumePal},
		{"data/sound/BGM/gameover.mp3", kMaxVolumePal}
	};

	SoundData seData[] =
	{
		{"data/sound/SE/cursor.mp3", kMaxVolumePal},
		{"data/sound/SE/select.mp3", kMaxVolumePal},
		{"data/sound/SE/attack.mp3", kMaxVolumePal},
		{"data/sound/SE/clearCheers.mp3", kMaxVolumePal}
	};


	/// <summary>
	/// ロード
	/// </summary>
	void Sound::Load()
	{
		Sound::m_bgmHandle.resize(static_cast<int>(Sound::BgmKind::kBgmNum));
		Sound::m_seHandle.resize(static_cast<int>(Sound::SeKind::kSeNum));

		// サウンドデータ生成
		for (int i = 0; i < m_bgmHandle.size(); i++)
		{
			m_bgmHandle[i] = LoadSoundMem(bgmData[i].name);
		}
		for (int i = 0; i < m_seHandle.size(); i++)
		{
			m_seHandle[i] = LoadSoundMem(seData[i].name);
		}
	}


	/// <summary>
	/// アンロード
	/// </summary>
	void Sound::UnLode()
	{
		for (const auto& handle : m_bgmHandle)
		{
			DeleteSoundMem(handle);
		}
		for (const auto& handle : m_seHandle)
		{
			DeleteSoundMem(handle);
		}
	}


	/// <summary>
	/// BGMの音量を変更する
	/// </summary>
	void ChangeBgmVol(Input& input)
	{
		// 音量を下げる
		if (input.IsPressing("left"))
		{
			for (int i = 0; i < m_bgmHandle.size(); i++)
			{
				bgmData[i].volumePal--;
				bgmData[i].volumePal = std::max(0, bgmData[i].volumePal);
			}
		}
		// 音量を上げる
		else if (input.IsPressing("right"))
		{
			for (int i = 0; i < m_bgmHandle.size(); i++)
			{
				bgmData[i].volumePal++;
				bgmData[i].volumePal = std::min(bgmData[i].volumePal, kMaxVolumePal);
			}
		}

		for (int i = 0; i < m_bgmHandle.size(); i++)
		{
			ChangeVolumeSoundMem(bgmData[i].volumePal, i);
		}

		printfDx("BGM:%d\n", bgmData[0].volumePal);
	}


	/// <summary>
	/// SEの音量を変更する
	/// </summary>
	void ChangeSeVol(Input& input)
	{
		// 音量を下げる
		if (input.IsPressing("left"))
		{
			for (int i = 0; i < m_seHandle.size(); i++)
			{
				seData[i].volumePal--;
				seData[i].volumePal = std::max(0, seData[i].volumePal);
			}
		}
		// 音量を上げる
		else if (input.IsPressing("right"))
		{
			for (int i = 0; i < m_seHandle.size(); i++)
			{
				seData[i].volumePal++;
				seData[i].volumePal = std::min(seData[i].volumePal, kMaxVolumePal);
			}
		}

		for (int i = 0; i < m_seHandle.size(); i++)
		{
			ChangeVolumeSoundMem(seData[i].volumePal, i);
		}
		printfDx("SE:%d\n", seData[0].volumePal);
	}
}
