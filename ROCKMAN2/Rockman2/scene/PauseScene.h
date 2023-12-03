#pragma once
#include "Scene.h"

/// <summary>
/// �|�[�Y���̃V�[���N���X
/// </summary>
class PauseScene:public Scene
{
public:
	PauseScene(SceneManager& manager);
	void Update(Pad& pad);
	void Draw();

private:
	// �t���[����
	int m_frame;

	// �X�V�����o�֐��|�C���^
	using UpdateFunc_t = void (PauseScene::*)(Pad& pad);
	UpdateFunc_t updateFunc_;
	// �`�惁���o�֐��|�C���^
	using DrawFunc_t = void (PauseScene::*)();
	DrawFunc_t drawFunc_;

	// �X�V�֐�
	void AppearUpdate(Pad&);// �o����
	void NormalUpdate(Pad& pad);// �ʏ���
	void DisappearUpdate(Pad&);// �ޏ���

	// �`��֐�
	void ExpandDraw();// �g���k���`��
	void NormalDraw();// �ʏ�`��
};

