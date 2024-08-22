#pragma once
#include "SceneBase.h"

/// <summary>
/// オプション画面
/// </summary>
class SceneOption : public SceneBase
{
public:
	SceneOption() {};
	SceneOption(std::shared_ptr<SceneBase> pScene);
	virtual ~SceneOption();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSound(Input& input);		// サウンド更新
	//void UpdateKeyConfig(Input& input); // キー更新
	void DrawSound();					// サウンド部分表示
	void DrawCredit();					// クレジット表記
	void DrawKeyConfig();				// キーコンフィグ部分表示

private:
	std::shared_ptr<SceneBase> m_pPrevScene;	// 前に実行していたシーン
	int m_afterSelect;							// 選択後の状態
	bool m_isSound;								// サウンドが選択中か(true:選択中)
	bool m_isCredit;							// キーコンフィグが選択中か(true:選択中)
	std::vector<int> m_handle;					// サウンドバーに使用する画像

	// 選択肢
	enum Select
	{
		kSound,			// サウンド
		kCredit,		// クレジット表記
		kSelectNum		// 選択数
	};

	// サウンド選択肢
	enum SelectSound
	{
		kBGM,			// BGM
		kSE,			// SE
		kSelectSoundNum	// 選択数
	};

	// キーコンフィグ選択肢
	enum SelectKeyConfig
	{
		kXButton,		// Xボタン
		kYButton,		// Yボタン
		kSelectKeyNum	// 選択数
	};
};

