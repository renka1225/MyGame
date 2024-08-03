#pragma once
#include "SceneBase.h"
#include <memory>

/// <summary>
/// �N���A�V�[��
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear() {};
	SceneClear(std::vector<int> clearTime);
	virtual ~SceneClear();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textHandle;				// �e�L�X�g�̉摜
	int m_totalClearTime;			// �g�[�^���̃N���A�^�C��
	std::vector<int> m_clearTime;	// �N���A�^�C��
};
