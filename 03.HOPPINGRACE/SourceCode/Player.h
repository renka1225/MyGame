#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;
class WorldSprite;
class Input;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player(std::shared_ptr<ManagerModel> pModel);
	~Player();
	void Init() {};
	void Update(Input& input);
	void Draw();

	void Move();			// �v���C���[���ړ�������
	void ClearStaging();	// �N���A���̉��o

	VECTOR GetPos() const { return m_pos; }		// �v���C���[�̈ʒu���擾
	VECTOR GetMove() const { return m_move; }	// �v���C���[�̈ړ��ʂ��擾

private:
	std::shared_ptr<ManagerModel> m_pModel;

	// �v���C���[���
	VECTOR m_pos;	// �v���C���[�ʒu
	VECTOR m_move;	// �ړ���

	int m_model;	// 3D���f��

	// �N���A���̏��
	int m_isClear;			// �N���A�������̃t���O
	int m_clearStagingTime;	// �N���A���o�̎���
	float m_angle;			// �v���C���[�������Ă������

private:	// �萔
	static constexpr float kScale = 0.3f;		// �v���C���[�̃T�C�Y
	static constexpr float kJumpHeight = 40.0f;	// �W�����v�̍���
	static constexpr float kMoveZ = -3.0f;		// Z���̈ړ���
	static constexpr float kGravity = -3.5f;	// �d��
	static constexpr float kInitPosX = 10.0f;	// �����ʒuX
	static constexpr float kInitPosY = 10.0f;	// �����ʒuY
	static constexpr float kInitPosZ = 20.0f;	// �����ʒuZ

	static constexpr int kShadowPosX = 640;		// �e�̕\���ʒuX
	static constexpr int kShadowPosY = 600;		// �e�̕\���ʒuY
	static constexpr int kShadowRadius = 25;	// �e�̔��a

	// �N���A���o��
	static constexpr int kClearStagingStartTime = 60;	// �N���A���o�J�n����
	static constexpr float kClearInitPosX = 0.0f;		// �N���A����X���W
	static constexpr float kClearInitPosZ = -80.0f;		// �N���A����Z���W
	static constexpr float kClearMoveX = 0.5f;			// X�����̈ړ���
	static constexpr float kClearMoveZ = 0.1f;			// Z�����̈ړ���
	static constexpr float kRotRad = 6.0f;				// ���t���[���̉�]�p�x
	static constexpr int kJumpFrame = 20;				// �W�����v�t���[��
};