#pragma once
#include "SceneBase.h"

/// <summary>
/// �^�C�g�����
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual  ~SceneTitle();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_titleTime;			// �^�C�g����\������܂ł̎���
	int m_textTime;				// �e�L�X�g��\������܂ł̎���
	int m_textDisplayTime;		// �e�L�X�g��\�����鎞��
	int m_titleLogo;			// �^�C�g�����S�̉摜
	int m_titleLogoBack;		// �^�C�g�����S�̌��ɕ\������摜
	float m_titleLogoScale;		// �^�C�g�����S�̊g�嗦
	int m_textHandle;			// �e�L�X�g�̉摜
	int m_textAlpha;			// �e�L�X�g�̃A���t�@�l
};