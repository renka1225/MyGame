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
	Player(std::shared_ptr<ManagerModel> pModel);
	virtual ~Player();
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

	// 3D���f��
	int m_modelHandle;


private:	// �萔
	static constexpr float kMove = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);	// �ړ���
	static constexpr float kGravity = 0.5f;											// �d��
	static constexpr float kVelocity = 10.0f;											// �����x
	static constexpr float kDirY = -90.0f * DX_PI_F / 180.0f;							// Y�������̌���
	static constexpr float kScale = 0.5f;												// �v���C���[�̃T�C�Y
	static constexpr float kGroundHeight = 0.0f;										// �n�ʂ̍���

	// �W�����v�t���[��
	static constexpr int kLittleJumpFrame = 10;		// ���W�����v
	static constexpr int kMediumJumpFrame = 30;		// ���W�����v
	// �W�����v�̍���
	static constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
	static constexpr float kMediumJumpHeight = 0.8f;	// ���W�����v
	static constexpr float kBigJumpHeight = 1.0f;		// ��W�����v
};