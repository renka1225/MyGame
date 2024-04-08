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
	int m_titleLogo;	// �^�C�g�����S�̉摜

private:	// �萔
	static constexpr int kTextPosX = 650;	// �e�L�X�g�\���ʒuX
	static constexpr int kTextPosY = 700;	// �e�L�X�g�\���ʒuY
};

