#pragma once
#include "SceneMain.h"

class BgStage1;

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
	// �V���b�g�̒ǉ�
	virtual bool AddShot(ShotBase* pShot) override;
	//�@�G�̐���
	virtual void CreateEnemy() override;
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
	// �w�i�̃|�C���^
	BgStage1* m_pBg;
};

