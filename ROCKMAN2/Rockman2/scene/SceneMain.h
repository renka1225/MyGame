#pragma once
#include <vector>
#include "Vec2.h"
#include "Rect.h"

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

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �e�̍X�V
	virtual void UpdateShot(Rect playerRect) = 0;
	// �G�̍X�V
	virtual void UpdateEnemy(Rect playerRect) = 0;
	// �񕜃A�C�e���̍X�V
	virtual void UpdateRecovery(Rect playerRect) = 0;
	// �V���b�g�̒ǉ�
	virtual bool AddShot(ShotBase* pShot) = 0;
	// �N���A���o
	virtual void UpdateClearStaging() = 0;
	//�@�G�̐���
	virtual void CreateEnemy() = 0;
	// �A�C�e���̐���
	virtual void CreateItem(int enemyIndex) = 0;
	// �e���A�G�����̕\��
	virtual void DrawInfo() = 0;
	// ����؂�ւ���ʕ\��
	virtual void DrawShotChange() = 0;
	// �|�[�Y��ʂ̕\��
	virtual void DrawPause() = 0;;
	// �X�^�[�g���o�̕`��
	virtual void DrawStartStaging() = 0;
	// �N���A�����o�̕`��
	virtual void DrawClearStaging() = 0;

	// �A�C�e���h���b�v
	virtual void DropHpSmallRecovery(int enemyIndex) = 0;	// HP����
	virtual void DropHpGreatRecovery(int enemyIndex) = 0;	// HP���
	virtual void DropShotSmallRecovery(int enemyIndex) = 0;	// �e����
	virtual void DropShotGreatRecovery(int enemyIndex) = 0;	// �e���
	virtual void DropLifeRecovery(int enemyIndex) = 0;		// �c�@��
	virtual void DropFullHpRecovery() = 0;					// HP�S��

	// �A�C�e��2���̕\����Ԃ��擾
	bool GetIsExistLineMove() const {return m_isExistLineMove; }
	// ���j���[���J����Ă��邩�擾����
	bool GetIsExistMenu() const {return m_isExistMenu; }
	// �V�[���ړ��̎擾
	bool IsSceneGameOver() const { return m_isSceneGameOver; }	// �Q�[���I�[�o�[���
	bool IsSceneClear() const { return m_isSceneClear; }		// �N���A���
	bool IsSceneTitle() const { return m_isSceneTitle; }		// �^�C�g�����
	bool IsSceneEnd() const { return m_isSceneEnd; }			// ���g���C

protected:
	/*�|�C���^���擾*/
	// �t�H���g�Ǘ�
	FontManager* m_pFont;
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
	// �ԉ΂̕\���ʒu
	Vec2 m_fireworks1Pos;	// �ԉ�1
	Vec2 m_fireworks2Pos;	// �ԉ�2
	Vec2 m_fireworks3Pos;	// �ԉ�3

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
	// ���j���[�A����؂�ւ���ʂ��\������Ă��邩
	bool m_isExistMenu;

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
	int m_fireworks1Frame;			// �ԉ�1�̕\���t���[�� 
	int m_fireworks2Frame;			// �ԉ�2�̕\���t���[�� 
	int m_fireworks3Frame;			// �ԉ�3�̕\���t���[�� 

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
	int m_frameHandle;		// �g
	int m_fullHpRecHandle;  // E�ʂ̉摜	
	int m_shotSelectHandle;	// �I�𒆂̕���
	int m_startHandle;		// �X�^�[�g���o�̉摜
	int m_fireworks1;		// �ԉ�1
	int m_fireworks2;		// �ԉ�2
	int m_fireworks3;		// �ԉ�3
};

