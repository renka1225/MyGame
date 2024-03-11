#pragma once
#include "DxLib.h"
#include <memory>

class Input;
class ManagerModel;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	virtual ~Player() {};
	void Init();
	void Update(Input& input);
	void Draw();
	void End();

	VECTOR GetPos() const { return m_pos; }

private:
	// �W�����v����
	void Jump(Input& input);

private:
	// ���f���N���X�̃|�C���^
	std::shared_ptr<ManagerModel> m_pModel;

	// �\���ʒu
	VECTOR m_pos;
	// �ړ���
	VECTOR m_move;

	// �W�����v�t���O true:�W�����v��
	bool m_isJump;
	// �W�����v�t���[��
	int m_jumpFrame;
};