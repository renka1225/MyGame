#pragma once
#include "SceneBase.h"

/// <summary>
/// プレイ画面
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying() {};

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateCommand(Input& input);	// 入力コマンドの更新
	void DrawCommand();					// 入力コマンドの表示

private:
	// 入力コマンドの種類
	enum Command
	{
		A,
		B,
		X,
		Y
	};
	int m_nowCommand;	// 現在のコマンド

	int m_time;			// 経過時間
	int m_pushCount;	// ボタンを押した回数

private:	// 定数
	static constexpr int kMaxPush = 10;		// 50回ボタン入力を行う
};

