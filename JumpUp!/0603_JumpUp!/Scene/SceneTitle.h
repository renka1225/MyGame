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
};