#pragma once
#include "SceneBase.h"

/// <summary>
/// オプション画面
/// </summary>
class SceneOption : public SceneBase
{
public:
	SceneOption();
	virtual ~SceneOption();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
};

