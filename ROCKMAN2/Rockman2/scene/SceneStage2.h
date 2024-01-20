#pragma once
#include "SceneMain.h"

// ステージ2のクラス
class SceneStage2 : public SceneMain
{
public:
	SceneStage2();
	virtual ~SceneStage2();

	virtual void Init()  override;;
	virtual void End()  override;;
	virtual void Update()  override;;
	virtual void Draw()  override;;
};

