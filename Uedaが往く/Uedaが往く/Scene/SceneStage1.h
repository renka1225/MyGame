#pragma once
#include "SceneStageBase.h"
#include <vector>

class Player;
class Camera;
class Stage;
class EnemyBase;
class CharacterBase;

/// <summary>
/// �X�e�[�W1
/// </summary>
class SceneStage1 : public SceneStageBase
{
public:
	SceneStage1() {};
	SceneStage1(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage);
	virtual  ~SceneStage1();
	virtual void Init() override;
	virtual std::shared_ptr<SceneBase> Update(Input& input) override;
	virtual void Draw() override;
	void IsSetTuto(bool isTuto) { m_isTuto = isTuto; } // �`���[�g���A����Ԃ�ύX

private:
	void UpdateSound();				// �T�E���h�X�V
	void UpdateTuto(Input& input);	// �`���[�g���A���̕\����Ԃ��X�V����
	void DrawTutorial();			// �`���[�g���A���\��

private:
	int m_tutoNum;					// ���݂̃`���[�g���A����
	int m_tutoSelect;				// �`���[�g���A���̑I�����
	bool m_isTuto;					// �`���[�g���A����\�����邩(true:�\������)
	std::string m_tutoText;
	std::vector<int> m_tutoHandle;	// �`���[�g���A�����ɕ\������摜

	enum Select
	{
		kYes,	// �͂�
		kNo,	// ������
	};
};