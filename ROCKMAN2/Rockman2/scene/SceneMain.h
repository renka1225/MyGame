#pragma once
#include <vector>
#include "Vec2.h"

class FontManager;
class Bg;
class ScenePause;
class Player;
class ShotBase;
class EnemyBase;
class RecoveryBase;

/// <summary>
/// �Q�[����ʂ̃N���X
/// </summary>
class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	virtual void Init();
	virtual void End();
	virtual void Update();
	virtual void Draw();

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
	bool GetIsExistLineMove() const {return m_isExistLineMove; }

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

protected:
	/*�|�C���^���擾*/
	// �t�H���g�Ǘ�
	FontManager* m_pFont;
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

	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;
	// ���o
	float m_startStagingTime;		// �X�^�[�g���o�̎���
	float m_clearStagingTime;		// �N���A���o����
	float m_gameoverStagingTime;	// �Q�[���I�[�o�[���o����

	// ��
	int m_bgm;			// BGM
	int m_startSE;		// �X�^�[�g����SE
	int m_clearSE;		// �N���A����SE
	int m_enemyDeadSE;	// �G���S����SE
	int m_recoverySE;	// �񕜎���SE
	int m_lineMoveSE;	// �A�C�e��2������ʓ��ɂ���Ƃ�

	// �摜
	int m_frameHandle;	// �g
};

