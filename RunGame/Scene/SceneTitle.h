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
	virtual void End();

private:
	int m_textFrame;	// �e�L�X�g�\������

private:	// �萔
	static constexpr int kTextPosX = 750;	// �e�L�X�g�\���ʒuX
	static constexpr int kTextPosY = 800;	// �e�L�X�g�\���ʒuY
};

