#pragma once
#include <vector>
#include "Vec2.h"

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
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

	// �V���b�g�̒ǉ�
	bool AddShot(ShotBase* pShot);

	// �A�C�e���h���b�v
	void DropHpSmallRecovery(int enemyIndex);	// HP����
	void DropHpGreatRecovery(int enemyIndex);	// HP���
	void DropShotSmallRecovery(int enemyIndex);	// �e����
	void DropShotGreatRecovery(int enemyIndex);	// �e���
	void DropLifeRecovery(int enemyIndex);		// �c�@��

	// �V�[�����I�������邩
	bool IsSceneEnd() const { return m_isSceneEnd; }

private:
	// �G�L�����N�^�[�̐���
	void CreateMatasaburo(); // �܂����Ԃ낤�̐���

private:
	// �O���t�B�b�N�̃n���h��
	int m_bgHandle;			// �w�i
	int m_mapHandle;		// �}�b�v�`�b�v
	int m_playerHandle;		// �v���C���[
	int m_enemyHandle;		// �G

	int m_drawValue; // HP�̉񕜃o�[�̒���

	// �V�[�����I��������t���O true:�I��
	bool m_isSceneEnd;

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
};

