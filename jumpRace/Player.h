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
	void Init();
	void Update(Input& input);
	void Draw();

	void Move();			// �v���C���[���ړ�������
	void ClearStaging();	// �N���A���̉��o

	VECTOR GetPos() const { return m_pos; }

private:
	std::shared_ptr<ManagerModel> m_pModel;

	VECTOR m_pos;	// �ʒu
	int m_model;	// 3D���f��

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
};