#pragma once
#include "SceneBase.h"


/// <summary>
/// �^�C�g�����
/// </summary>
class SceneTitle :  public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textFrame;	// �e�L�X�g�\������
	int m_fadeAlpha;	// �t�F�[�h�̃��l

	int m_titleLogo;	// �^�C�g�����S�̉摜

private:	// �萔
	static constexpr int kTextPosX = 840;	// �e�L�X�g�\���ʒuX
	static constexpr int kTextPosY = 700;	// �e�L�X�g�\���ʒuY
	static constexpr int kText2PosX = 870;	// �e�L�X�g2�\���ʒuX
	static constexpr int kText2PosY = 850;	// �e�L�X�g2�\���ʒuY

	static constexpr int kMaxFade = 255;	// �t�F�[�h���ő�l
	static constexpr int kFadeFrame = 8;	// �t�F�[�h�ω���
};

