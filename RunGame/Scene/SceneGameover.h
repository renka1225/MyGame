#pragma once
#include "SceneBase.h"

/// <summary>
/// ゲームオーバーシーン
/// </summary>
class SceneGameover : public SceneBase
{
public:
	SceneGameover();
	virtual ~SceneGameover();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textFrame;	// テキスト表示時間

private:	// 定数
	static constexpr int kTextPosX = 750;	// テキスト表示位置X
	static constexpr int kTextPosY = 700;	// テキスト表示位置Y
	static constexpr int kText2PosX = 720;	// テキスト表示位置X
	static constexpr int kText2PosY = 850;	// テキスト表示位置Y
};