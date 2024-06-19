#pragma once
#include "SceneBase.h"

/// <summary>
/// タイトル画面クラス
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// 選択状態を更新

private:
	// 選択項目の種類
	enum Select
	{
		kStart,		// ゲームスタート
		kEnd,		// ゲーム終了
		kSelectNum	// 選択数
	};

	int m_select;	// 現在の選択状態

};