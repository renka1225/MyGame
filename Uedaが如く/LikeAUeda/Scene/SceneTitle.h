#pragma once
#include "SceneBase.h"

/// <summary>
/// タイトル画面
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual  ~SceneTitle();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_titleLogo;	// タイトルロゴの画像
};

