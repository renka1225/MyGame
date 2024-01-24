#pragma once
#include "SceneMain.h"

class BgStage2;
class Player;

/// <summary>
/// ステージ2のクラス
/// </summary>
class SceneStage2 : public SceneMain
{
public:
	SceneStage2();
	virtual ~SceneStage2();

	virtual void Init()  override;
	virtual void End()  override;
	virtual void Update()  override;
	virtual void Draw()  override;
};

