#pragma once
#include "SceneBase.h"

/// <summary>
/// タイトル画面
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

	void UpdateSelect(Input& input);	// 選択状態の更新

private:
	// 選択項目
	enum Select
	{
		kStart,		// スタート
		kEnd,		// ゲーム終了
		kSelectNum	// 選択数
	};

	// MEMO:スコア確認画面に遷移できるようにする

	int m_select;	// 現在の選択状態

private: // 定数
	static constexpr int kStartTextPosX = 600;	// スタート表示位置X
	static constexpr int kStartTextPosY = 500;	// スタート表示位置Y
	static constexpr int kEndTextPosX = 600;	// ゲーム終了表示位置X
	static constexpr int kEndTextPosY = 600;	// ゲーム終了表示位置Y
};