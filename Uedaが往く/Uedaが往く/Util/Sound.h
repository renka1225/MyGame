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
		kAttackSE,		// 攻撃
		kClearCheersSE, // クリア時の歓声SE
		kTitleBGM,		// タイトルBGM
		kStageSelectBGM,// ステージ選択BGM
		kStage1BGM,		// ステージ1BGM
		kStage2BGM,		// ステージ2BGM
		kClearBGM,		// クリアBGM
		kGameoverBGM,	// ゲームオーバーBGM
		kNum			// サウンドの数
	};

	void Load();
	void UnLode();
	void ChangeVol(); // 音量を変更する

	extern std::vector<int> m_soundHandle;
};

