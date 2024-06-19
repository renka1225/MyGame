#pragma once
#include "SceneBase.h"

/// <summary>
/// �N���A��ʃN���X
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear();
	virtual ~SceneClear();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// �I����Ԃ��X�V

private:
	// �I�����ڂ̎��
	enum Select
	{
		kStart,		// �ăv���C
		kTitle,		// �^�C�g���ɖ߂�
		kSelectNum	// �I��
	};

	int m_select;	// ���݂̑I�����
};

