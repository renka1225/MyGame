#pragma once
#include "SceneBase.h"

/// <summary>
/// �v���C���̃V�[��
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();
};
