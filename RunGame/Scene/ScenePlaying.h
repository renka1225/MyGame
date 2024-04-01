#pragma once
#include "SceneBase.h"
#include "DxLib.h"
#include <vector>

class ManagerFont;
class ManagerModel;
class Background;
class Map;
class Player;
class Enemy;
class Camera;

/// <summary>
/// �v���C���̃V�[��
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying() {};

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:
	void LoadEnemy();				// �G���ǂݍ���
	void IsCollision(int enemyIdx);	// �v���C���[�ƓG�̓����蔻�菈��

private:
	// �|�C���^
	std::shared_ptr<ManagerFont> m_pFont;
	std::shared_ptr<ManagerModel> m_pModel;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<Background> m_pBackground;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;

	int m_time; // ����

	std::vector<VECTOR> m_enemyPos;	// �G�ʒu

private:	// �萔
	
	static constexpr int kClearTime = 60 * 90;	// �Q�[������
	static constexpr int kIntervalTime = 20;	// �o�ߎ��Ԃ̕\���Ԋu
	static constexpr int kEnemyNum = 10;		// �ő�G��
};