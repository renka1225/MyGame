#pragma once
#include "SceneMain.h"

class BgStage1;
class Player;

/// <summary>
/// �X�e�[�W1�N���X
/// </summary>
class SceneStage1 : public SceneMain
{
public:
	SceneStage1();
	virtual ~SceneStage1();

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
	// �e���A�G�����̕\��
	virtual void DrawInfo() override;

	// �A�C�e���h���b�v
	void DropHpSmallRecovery(int enemyIndex);		// HP����
	void DropHpGreatRecovery(int enemyIndex);		// HP���
	void DropShotSmallRecovery(int enemyIndex);		// �e����
	void DropShotGreatRecovery(int enemyIndex);		// �e���
	void DropLifeRecovery(int enemyIndex);			// �c�@��
	void DropFullHpRecovery();						// HP�S��

private:
	/*�|�C���^�ݒ�*/
	// �w�i
	BgStage1* m_pBg;
};

