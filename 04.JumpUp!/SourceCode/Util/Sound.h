#pragma once
#include <vector>

/// <summary>
/// サウンド管理
/// </summary>
namespace Sound
{
	// サウンドの種類
	enum class SoundKind
	{
		kCursorSE,		// カーソル移動
		kSelectSE,		// 決定
		kRunSE,			// 移動
		kJumpSE,		// ジャンプ
		kClearSE,		// クリア時のSE
		kClearCheersSE, // クリア時の歓声のSE
		kTitleBGM,		// タイトル
		kPlayBGM,		// プレイ中
		kClearBGM,		// クリア
		kNum			// サウンドの数
	};

	void Load();
	void UnLode();
	void ChangeVol(); // 音量を変更する

	extern std::vector<int> m_soundHandle;
};

