#pragma once
#include "SceneBase.h"
#include "DxLib.h"

class ManagerModel;
class Background;
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
	// �|�C���^
	std::shared_ptr<ManagerModel> m_pModel;
	std::shared_ptr<Background> m_pBackground;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;

	int m_time; // ����

	VECTOR m_enemyPos;	// �G�ʒu

private:	// �萔
	// �Q�[������
	static constexpr int kClearTime = 60 * 90;
	// �o�ߎ��Ԃ̕\���Ԋu
	static constexpr int kIntervalTime = 20;
};