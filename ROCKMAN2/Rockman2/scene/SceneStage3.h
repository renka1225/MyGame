#pragma once
#include "SceneMain.h"

/// <summary>
/// �X�e�[�W3�̃N���X
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

