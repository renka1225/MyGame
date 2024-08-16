#pragma once
#include <vector>

/// <summary>
/// サウンド管理
/// </summary>
namespace Sound
{
	//BGMの種類
	enum class BgmKind
	{
		kTitle,			// タイトルBGM
		kStageSelect,	// ステージ選択BGM
		kStage1,		// ステージ1BGM
		kStage2,		// ステージ2BGM
		kClear,			// クリアBGM
		kGameover,		// ゲームオーバーBGM
		kBgmNum			// BGMの数
	};

	// SEの種類
	enum class SeKind
	{
		kCursor,		// カーソル移動
		kSelect,		// 決定
		kAttack,		// 攻撃
		kClearCheers,	// クリア時の歓声SE
		kSeNum			// SEの数
	};

	void Load();
	void UnLode();
	void ChangeBgmVol(Input& input); // BGMの音量を変更する
	void ChangeSeVol(Input& input);  // SEの音量を変更する
	int GetBgmVol();				 // BGMの音量を取得
	int GetSeVol();					 // SEの音量を取得

	extern std::vector<int> m_bgmHandle;
	extern std::vector<int> m_seHandle;
};

