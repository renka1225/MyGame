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

	virtual void Init(std::shared_ptr<ManagerResult> pResult);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

	void UpdateSelect(Input& input);	// �I����Ԃ̍X�V
	void DrawSelect();					// �I�����ڂ�\��

private:
	// �I������
	enum Select
	{
		kStart,		// �X�^�[�g
		kResult,	// �X�R�A�m�F
		kEnd,		// �Q�[���I��
		kSelectNum	// �I��
	};

	int m_select;		// ���݂̑I�����

	int m_titleLogo;	// �^�C�g�����S

private: // �萔
	static constexpr int kTitleLogoPosX = 350;	// �^�C�g���\���ʒuX
	static constexpr int kTitleLogoPosY = 100;	// �^�C�g���\���ʒuY

	static constexpr int kNowSelectPosX = 534;	// �I�𒆕\���ʒuX
	static constexpr int kNowSelectPosY = 445;	// �I�𒆕\���ʒuY
	static constexpr int kNowSelectWidth = 210;	// �I�𒆕\���̉���
	static constexpr int kNowSelectHeight = 61;	// �I�𒆕\���̏c��
	static constexpr int kFramePosX = 530;		// �g�\���ʒuX
	static constexpr int kFramePosY = 440;		// �g�\���ʒuY
	static constexpr int kSelectMove = 80;		// �I��\���̈ړ���

	static constexpr int kStartTextPosX = 580;	// �X�^�[�g�\���ʒuX
	static constexpr int kStartTextPosY = 460;	// �X�^�[�g�\���ʒuY
	static constexpr int kResultTextPosX = 560;	// ���U���g�\���ʒuX
	static constexpr int kResultTextPosY = 540;	// ���U���g�\���ʒuY
	static constexpr int kEndTextPosX = 600;	// �Q�[���I���\���ʒuX
	static constexpr int kEndTextPosY = 620;	// �Q�[���I���\���ʒuY
};