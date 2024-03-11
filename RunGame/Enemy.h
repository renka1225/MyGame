#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;

/// <summary>
/// �G�N���X
/// </summary>
class Enemy
{
public:
	Enemy();
	virtual ~Enemy();
	void Init();
	void Update();
	void Draw();
	void End();
	
private:
	// ���f���N���X�̃|�C���^
	std::shared_ptr<ManagerModel> m_pModel;

	// �\���ʒu
	VECTOR m_pos;
	// �ړ���
	VECTOR m_move;
};