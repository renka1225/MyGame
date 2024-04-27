#pragma once
#include "SceneBase.h"

/// <summary>
/// �^�C�g�����
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

	void UpdateSelect(Input& input);	// �I����Ԃ̍X�V

private:
	// �I������
	enum Select
	{
		kStart,		// �X�^�[�g
		kEnd,		// �Q�[���I��
		kSelectNum	// �I��
	};

	// MEMO:�X�R�A�m�F��ʂɑJ�ڂł���悤�ɂ���

	int m_select;	// ���݂̑I�����

private: // �萔
	static constexpr int kStartTextPosX = 600;	// �X�^�[�g�\���ʒuX
	static constexpr int kStartTextPosY = 500;	// �X�^�[�g�\���ʒuY
	static constexpr int kEndTextPosX = 600;	// �Q�[���I���\���ʒuX
	static constexpr int kEndTextPosY = 600;	// �Q�[���I���\���ʒuY
};