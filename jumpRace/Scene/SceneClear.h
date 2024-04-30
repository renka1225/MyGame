#pragma once
#include "SceneBase.h"

/// <summary>
/// �N���A���
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear() {};
	SceneClear(std::shared_ptr<ManagerResult> pResult, int time);
	virtual ~SceneClear();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

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
	static constexpr int kHighScorePosY = 150;	// �n�C�X�R�A�\���ʒuY
	static constexpr int kSecondPosY = 200;		// 2�ʕ\���ʒuY
	static constexpr int kThirdPosY = 250;		// 3�ʕ\���ʒuY

	static constexpr int kNowSelectPosX = 534;	// �I�𒆕\���ʒuX
	static constexpr int kNowSelectPosY = 485;	// �I�𒆕\���ʒuY
	static constexpr int kNowSelectWidth = 210;	// �I�𒆕\���̉���
	static constexpr int kNowSelectHeight = 61;	// �I�𒆕\���̏c��
	static constexpr int kFramePosX = 530;		// �g�\���ʒuX
	static constexpr int kFramePosY = 480;		// �g�\���ʒuY
	static constexpr int kSelectMove = 100;		// �I��\���̈ړ���

	static constexpr int kStartTextPosX = 580;	// �X�^�[�g�\���ʒuX
	static constexpr int kStartTextPosY = 500;	// �X�^�[�g�\���ʒuY
	static constexpr int kTitleTextPosX = 520;	// �^�C�g���ɖ߂�\���ʒuX
	static constexpr int kTitleTextPosY = 600;	// �^�C�g���ɖ߂�\���ʒuY
};

