#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class Stage;
class EnemyBase;
class UIProduction;

/// <summary>
/// �v���C�V�[���̊��N���X
/// </summary>
class SceneStageBase : public SceneBase
{
public:
	SceneStageBase();
	SceneStageBase(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage);
	virtual ~SceneStageBase();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input) = 0;
	virtual void Draw();

protected:
	std::shared_ptr<Player> m_pPlayer;				// �v���C���[
	std::shared_ptr<Camera> m_pCamera;				// �J����
	std::shared_ptr<Stage> m_pStage;				// �X�e�[�W
	std::shared_ptr<EnemyBase> m_pEnemy;			// �G
	std::shared_ptr<UIProduction> m_pUIProduction;	// ���oUI
	int m_battleNum;				// ���݂̃o�g����
	int m_nextBattleTime;			// ���̎������n�܂�܂ł̎���
	int m_elapsedTime;				// �o�ߎ���
	std::vector<int> m_clearTime;	// �e�������Ƃ̃N���A�^�C��
};

