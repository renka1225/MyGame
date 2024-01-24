#pragma once
#include "SceneMain.h"

/// <summary>
/// ステージ3のクラス
/// </summary>
class SceneStage3 : public SceneMain
{
public:
	SceneStage3();
	virtual ~SceneStage3();

	virtual void Init()  override;
	virtual void End()  override;
	virtual void Update()  override;
	virtual void Draw()  override;
};

