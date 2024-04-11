#pragma once
#include "SceneBase.h"

/// <summary>
/// �Q�[���I�[�o�[�V�[��
/// </summary>
class SceneGameover : public SceneBase
{
public:
	SceneGameover();
	virtual ~SceneGameover() {};

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textFrame;	// �e�L�X�g�\������
	int m_fadeAlpha;	// �t�F�[�h�̃��l

	// �I������
	enum Select
	{
		kStart,		// �X�^�[�g
		kTitle,		// �^�C�g���ɖ߂�
		kSelectNum	// ���ڐ�
	};
	int m_select;	// ���݂̑I�����

private:	// �萔
	static constexpr int kTextPosX = 750;			// �e�L�X�g�\���ʒuX
	static constexpr int kTextPosY = 700;			// �e�L�X�g�\���ʒuY
	static constexpr int kText2PosX = 720;			// �e�L�X�g2�\���ʒuX
	static constexpr int kText2PosY = 850;			// �e�L�X�g2�\���ʒuY

	// �t�F�[�h
	static constexpr int kMaxFade = 255;			// �t�F�[�h���ő�l
	static constexpr int kStartFadeAlpha = 150;		// �X�^�[�g���̃t�F�[�h���l
	static constexpr int kFadeFrame = 8;			// �t�F�[�h�ω���
};