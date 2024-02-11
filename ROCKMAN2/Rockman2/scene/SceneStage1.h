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
	/*�|�C���^�ݒ�*/
	// �w�i
	BgStage1* m_pBg;

	// ��
	int m_bgm;			// BGM
	int m_enemyDeadSE;	// �G���S����SE
	int m_recoverySE;	// �񕜎���SE
	int m_lineMoveSE;	// �A�C�e��2������ʓ��ɂ���Ƃ�
	int m_startSE;		// �X�^�[�g����SE
	int m_clearSE;		// �N���A����SE
	int m_fireworksSE;	// �ԉ΂�SE

	// �摜
	int m_gameScreenHandle;	// �Q�[�����
	int m_frameHandle;		// �g
	int m_shotSelectHandle;	// �I�𒆂̕���
	int m_startHandle;		// �X�^�[�g���o�̉摜
	int m_fireworks;		// �ԉ�
};

