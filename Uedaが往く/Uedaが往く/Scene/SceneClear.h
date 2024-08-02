#pragma once
#include "SceneBase.h"
#include <memory>

/// <summary>
/// �N���A�V�[��
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear();
	virtual ~SceneClear();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

	//void SetClearTime(std::vector<int> clearTime) { m_clearTime = clearTime; };

private:
	int m_textHandle;				// �e�L�X�g�̉摜
	std::vector<int> m_clearTime;	// �N���A�^�C��
};
