#pragma once
#include "SceneBase.h"

/// <summary>
/// �Q�[���I�[�o�[�V�[��
/// </summary>
class SceneGameover : public SceneBase
{
public:
	SceneGameover();
	virtual ~SceneGameover();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textFrame;	// �e�L�X�g�\������

private:	// �萔
	static constexpr int kTextPosX = 750;	// �e�L�X�g�\���ʒuX
	static constexpr int kTextPosY = 700;	// �e�L�X�g�\���ʒuY
	static constexpr int kText2PosX = 720;	// �e�L�X�g�\���ʒuX
	static constexpr int kText2PosY = 850;	// �e�L�X�g�\���ʒuY
};