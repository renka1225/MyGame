#pragma once
#include "SceneMain.h"

class BgStage2;
class Player;

/// <summary>
/// �X�e�[�W2�̃N���X
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

