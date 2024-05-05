#pragma once
#include "SceneBase.h"

/// <summary>
/// �N���A���
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear(int time);
	virtual ~SceneClear();

	virtual void Init(std::shared_ptr<ManagerResult> pResult);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateSelect(Input& input);	// �I����Ԃ̍X�V
	void DrawSelect();					// �I�����ڕ\��
	void DrawResult();					// ���ʕ\��

private:
	int m_clearTime;	// �N���A�^�C��

	// �I������
	enum Select
	{
		kStart,		// �X�^�[�g
		kTitle,		// �^�C�g���ɖ߂�
		kSelectNum	// �I��
	};
	int m_select;	// ���݂̑I�����

private: // �萔
	static constexpr int kClearTimePosX = 500;	// �N���A�^�C���\���ʒuX
	static constexpr int kClearTimePosY = 100;	// �N���A�^�C���\���ʒuY
	static constexpr int kTimePosX = 560;		// ���ʕ\���ʒuX
	static constexpr int kTimePosY = 150;		// ���ʕ\���ʒuY
	static constexpr int kIntervalY = 50;		// ���ʕ\���Ԋu
	static constexpr int kDisplayRanking = 5;	// �\�����鏇�ʐ�

	static constexpr int kNowSelectPosX = 534;	// �I�𒆕\���ʒuX
	static constexpr int kNowSelectPosY = 485;	// �I�𒆕\���ʒuY
	static constexpr int kNowSelectWidth = 210;	// �I�𒆕\���̉���
	static constexpr int kNowSelectHeight = 61;	// �I�𒆕\���̏c��
	static constexpr int kFramePosX = 530;		// �g�\���ʒuX
	static constexpr int kFramePosY = 480;		// �g�\���ʒuY
	static constexpr int kSelectMove = 100;		// �I��\���̈ړ���

	static constexpr int kStartTextPosX = 580;	// �X�^�[�g�\���ʒuX
	static constexpr int kStartTextPosY = 500;	// �X�^�[�g�\���ʒuY
	static constexpr int kTitleTextPosX = 540;	// �^�C�g���ɖ߂�\���ʒuX
	static constexpr int kTitleTextPosY = 605;	// �^�C�g���ɖ߂�\���ʒuY

	static constexpr int kStartFadeAlpha = 255;		// �X�^�[�g���̃t�F�[�h���l
};

