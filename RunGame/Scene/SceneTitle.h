#pragma once
#include "SceneBase.h"


/// <summary>
/// タイトル画面
/// </summary>
class SceneTitle :  public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textFrame;	// テキスト表示時間
	int m_titleLogo;	// タイトルロゴの画像

private:	// 定数
	static constexpr int kTextPosX = 650;	// テキスト表示位置X
	static constexpr int kTextPosY = 700;	// テキスト表示位置Y
};

