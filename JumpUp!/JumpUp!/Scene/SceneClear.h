#pragma once
#include "SceneBase.h"

/// <summary>
/// クリア画面クラス
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear();
	virtual ~SceneClear();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// 選択状態を更新

private:
	// 選択項目の種類
	enum Select
	{
		kStart,		// 再プレイ
		kTitle,		// タイトルに戻る
		kSelectNum	// 選択数
	};

	int m_select;	// 現在の選択状態
};

