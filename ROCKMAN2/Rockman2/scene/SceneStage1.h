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
	virtual void End() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �V���b�g�̒ǉ�
	bool AddShot(ShotBase* pShot);

	// �A�C�e���h���b�v
	void DropHpSmallRecovery(int enemyIndex);	// HP����
	void DropHpGreatRecovery(int enemyIndex);	// HP���
	void DropShotSmallRecovery(int enemyIndex);	// �e����
	void DropShotGreatRecovery(int enemyIndex);	// �e���
	void DropLifeRecovery(int enemyIndex);		// �c�@��
	void DropFullHpRecovery();					// HP�S��

	// �A�C�e��2���̕\����Ԃ��擾
	bool GetIsExistLineMove() const { return m_isExistLineMove; }

	// �V�[���ړ��̎擾
	bool IsSceneGameOver() const { return m_isSceneGameOver; }	// �Q�[���I�[�o�[���
	bool IsSceneClear() const { return m_isSceneClear; }		// �N���A���
	bool IsSceneTitle() const { return m_isSceneTitle; }		// �^�C�g�����
	bool IsSceneEnd() const { return m_isSceneEnd; }			// �v���C��ʂ��I��

private:
	//�@�G�̐���
	void CreateEnemy();
	// �A�C�e���̐���
	void CreateItem(int enemyIndex);
	// �e���A�G�����̕\��
	void DrawInfo();
	// ����؂�ւ���ʕ\��
	void DrawShotChange();
	// �|�[�Y��ʂ̕\��
	void DrawPause();
	// �X�^�[�g���o�̕`��
	void DrawStartStaging();
	// �N���A�����o�̕`��
	void DrawClearStaging();

private:
	// �t�H���g�Ǘ�
	FontManager * m_pFont;
	// �w�i
	Bg* m_pBg;
	// �|�[�Y���
	ScenePause* m_pPause;
	// �v���C���[
	Player* m_pPlayer;
	// �V���b�g
	std::vector<ShotBase*> m_pShot;
	// �G
	std::vector<EnemyBase*> m_pEnemy;
	// �񕜃A�C�e��
	std::vector<RecoveryBase*> m_pRecovery;

	// �X�^�[�g���o�̕\���ʒu
	Vec2 m_startDis;
	// �N���A���o�̕\���ʒu
	Vec2 m_clearDis;

	// �v���C���[�̌��ݒn
	Vec2 m_playerPos;
	// �v���C���[��E�ʂ��擾������ true:�擾����
	bool m_isGetFullHpRecovery;

	// ���݂̓G��
	int m_enemyTotalNum;
	// ���݂̃^�C��
	float m_time;

	// �A�C�e��2������ʏ�ɑ��݂��邩
	bool m_isExistLineMove;

	// HP�̉񕜃o�[�̒���
	int m_drawValue;

	// �V�[���ړ����邩 true:�V�[���ړ�����
	bool m_isSceneGameOver;	// �Q�[���I�[�o�[��ʂɈړ�
	bool m_isSceneClear;	// �N���A��ʂɈړ�
	bool m_isSceneTitle;	// �^�C�g����ʂɈړ�
	bool m_isSceneEnd;		// �Q�[����ʂ��I��
	bool m_isRetry;			// ���g���C����

	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;
	int m_stagingFade; // �X�^�[�g���o���̃t�F�[�h

	// ���o
	float m_startStagingTime;		// �X�^�[�g���o�̎���
	float m_clearStagingTime;		// �N���A���o����
	float m_gameoverStagingTime;	// �Q�[���I�[�o�[���o����
	// Ready�̕\���J�E���g
	int m_readyCount;
	// ��ʗh�ꉉ�o
	int m_shakeFrame;
	float m_ampFrame;

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

