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
	virtual void Init(LoadData& data);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
};

