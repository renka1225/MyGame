#pragma once
#include "DxLib.h"
#include <memory>
#include <vector>

class ManagerModel;

/// <summary>
/// �G�N���X
/// </summary>
class Enemy
{
public:
	Enemy(std::shared_ptr<ManagerModel> pModel);
	virtual ~Enemy();
	void Init();
	void Update();
	void Draw();
	void End();
	
private:
	// ���f���N���X�̃|�C���^
	std::shared_ptr<ManagerModel> m_pModel;

	// �G�̈ʒu
	std::vector<VECTOR> m_pos;

	// 3D���f��
	int m_modelHandle;

private:	// �萔
	// �g�嗦
	static constexpr float kScale = 0.15f;
	// Y�������̌���
	static constexpr float kDirY = 180.0f * DX_PI_F / 180.0f;
	
	// �G��
	static constexpr int kEnemyNum = 5;
};