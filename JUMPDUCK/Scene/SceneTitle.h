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

	virtual void Init() {};
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textFrame;	// �e�L�X�g�\������
	int m_fadeAlpha;	// �t�F�[�h�̃��l

	int m_titleLogo;	// �^�C�g�����S�̉摜

	// �I������
	enum Select
	{
		kStart,		// �X�^�[�g
		kEnd,		// �Q�[���I��
		kSelectNum	// ���ڐ�
	};
	int m_select;	// ���݂̑I�����

private:	// �萔
	static constexpr int kLogoPosX = 610;		// �^�C�g�����S�\���ʒuX
	static constexpr int kLogoPosY = 100;		// �^�C�g�����S�\���ʒuY
	static constexpr int kCursorPosX = 700;		// �J�[�\���\���ʒuX
	static constexpr int kTextPosX = 840;		// �e�L�X�g�\���ʒuX
	static constexpr int kTextPosY = 700;		// �e�L�X�g�\���ʒuY
	static constexpr int kText2PosX = 870;		// �e�L�X�g2�\���ʒuX
	static constexpr int kText2PosY = 850;		// �e�L�X�g2�\���ʒuY
	static constexpr int kTextFrame = 30;		// �e�L�X�g�\���t���[��
	static constexpr int kCreditTextPosX = 1500;// �N���W�b�g�\���ʒuX
	static constexpr int kCreditTextPosY = 950;	// �N���W�b�g�\���ʒuY

	static constexpr int kMaxFade = 255;		// �t�F�[�h���ő�l
	static constexpr int kFadeFrame = 8;		// �t�F�[�h�ω���
};