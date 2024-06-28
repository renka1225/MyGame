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
		kCursorSE,	// カーソル移動
		kSelectSE,	// 決定
		kJumpSE,	// ジャンプ
		kClearSE,	// クリア時のSE
		kTitleBGM,	// タイトル
		kPlayBGM,	// プレイ中
		kClearBGM,	// クリア
		kNum		// サウンドの数
	};

	void Load();
	void UnLode();

	extern std::vector<int> m_soundHandle;
};

