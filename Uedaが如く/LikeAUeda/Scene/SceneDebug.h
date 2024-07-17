#pragma once
#include "SceneBase.h"

/// <summary>
/// デバッグ用シーン
/// </summary>
class SceneDebug : public SceneBase
{
public:
	SceneDebug();
	virtual ~SceneDebug() {};
	virtual void Init() {};
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// 選択状態を更新

private:
	// シーンの種類
	enum Select
	{
		kTitle,			// タイトル
		kStageSelect,	// ステージ選択
		kOption,		// オプション
		kStage1,		// ステージ1
		kStage2,		// ステージ2
		kSelectNum		// シーンの数
	};

	int m_select;		// 現在の選択状態
};

