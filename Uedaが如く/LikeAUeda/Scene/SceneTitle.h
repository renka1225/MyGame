#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class Stage;

/// <summary>
/// タイトル画面
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual  ~SceneTitle();
	virtual void Init(LoadData& data);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
};

