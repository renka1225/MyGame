#pragma once
#include "SceneBase.h"

/// <summary>
/// クリアシーン
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear();
	virtual ~SceneClear();
	virtual void Init(LoadData& data);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

};

