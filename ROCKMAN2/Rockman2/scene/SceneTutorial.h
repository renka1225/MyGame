#pragma once
#include "SceneMain.h"

class BgTutorial;

/// <summary>
/// �X�e�[�W1�N���X
/// </summary>
class SceneTutorial : public SceneMain
{
public:
	SceneTutorial();
	virtual ~SceneTutorial();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �e�̍X�V
	virtual void UpdateShot(Rect playerRect) override;
	// �G�̍X�V
	virtual void UpdateEnemy(Rect playerRect) override;
	// �񕜃A�C�e���̍X�V
	virtual void UpdateRecovery(Rect playerRect) override;
	// �V���b�g�̒ǉ�
	virtual bool AddShot(ShotBase* pShot) override;
	// �N���A���o
	virtual void UpdateClearStaging() override;
	//�@�G�̐���
	virtual void CreateEnemy() override;
	// �A�C�e���̐���
	virtual void CreateItem(int enemyIndex) override;
	// �e���A�G�����̕\��
	virtual void DrawInfo() override;
	// ����؂�ւ���ʕ\��
	virtual void DrawShotChange() override;
	// �|�[�Y��ʂ̕\��
	virtual void DrawPause() override;
	// �X�^�[�g���o�̕`��
	virtual void DrawStartStaging() override;
	// �N���A�����o�̕`��
	virtual void DrawClearStaging() override;

	// �A�C�e���h���b�v
	void DropHpSmallRecovery(int enemyIndex);	// HP����
	void DropHpGreatRecovery(int enemyIndex);	// HP���
	void DropShotSmallRecovery(int enemyIndex);	// �e����
	void DropShotGreatRecovery(int enemyIndex);	// �e���
	void DropLifeRecovery(int enemyIndex);		// �c�@��
	void DropFullHpRecovery();					// HP�S��

private:
	// �w�i
	BgTutorial* m_pBg;
};

