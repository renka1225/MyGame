#pragma once
#include "SceneBase.h"

/// <summary>
/// �N���A���
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear() {};
	SceneClear(int time);
	virtual ~SceneClear();

	void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_clearTime;	// �N���A�^�C��
};

