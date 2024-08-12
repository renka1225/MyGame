#pragma once
#include "SceneBase.h"

class SceneStageBase;

/// <summary>
/// ゲームオーバーシーン
/// </summary>
class SceneGameover : public SceneBase
{
public:
	SceneGameover() {};
	SceneGameover(std::shared_ptr<SceneBase> pScene);
	virtual ~SceneGameover();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// 選択状態の更新

private:
	std::shared_ptr<SceneBase> m_pPrevScene;	// 前に実行していたシーン
	int m_textHandle;	// テキストの画像
	int m_cursorHandle;	// カーソルの画像

	// 選択項目
	enum Select
	{
		kRetry,			// リトライ
		kStageSelect,	// ステージ選択
		kTitle,			// タイトル
		kSelectNum,		// 選択数
	};
};

