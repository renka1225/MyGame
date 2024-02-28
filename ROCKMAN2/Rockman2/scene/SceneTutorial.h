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

	// �A�C�e���h���b�v
	virtual void DropHpSmallRecovery(int enemyIndex) override;		// HP����
	virtual void DropHpGreatRecovery(int enemyIndex) override;		// HP���
	virtual void DropShotSmallRecovery(int enemyIndex) override;	// �e����
	virtual void DropShotGreatRecovery(int enemyIndex) override;	// �e���
	virtual void DropLifeRecovery(int enemyIndex) override;			// �c�@��
	virtual void DropFullHpRecovery() override;						// HP�S��

private:
	// �w�i
	BgTutorial* m_pBg;
};

