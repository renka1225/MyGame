#pragma once
#include "Rect.h"
#include "DxLib.h"
#include <memory>

class Input;
class ManagerModel;
class Map;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player(std::shared_ptr<ManagerModel> pModel, std::shared_ptr<Map> pMap);
	virtual ~Player();
	void Init();
	void Update(Input& input);
	void Draw();

	VECTOR GetPos() const { return m_pos; }			// ���݈ʒu���擾
	Rect GetColRect() const { return m_colRect; }	// �����蔻����擾����

private:
	void Jump(Input& input);	// �W�����v����

private:
	std::shared_ptr<ManagerModel> m_pModel;	// ���f���N���X�̃|�C���^
	std::shared_ptr<Map> m_pMap;			// �}�b�v�N���X�̃|�C���^

	VECTOR m_pos;		// �\���ʒu
	VECTOR m_move;		// �ړ���
	Rect m_colRect;		// �����蔻��p�̋�`

	bool m_isJump;		// �W�����v�t���O true:�W�����v��
	int m_jumpFrame;	// �W�����v�t���[��

	int m_modelHandle;	// �v���C���[��3D���f��


private:	// �萔
	static constexpr float kMove = 0.05f;						// �ړ���
	static constexpr float kGravity = 0.5f;						// �d��
	static constexpr float kVelocity = 8.3f;					// �����x
	static constexpr float kDirY = -90.0f * DX_PI_F / 180.0f;	// Y�������̌���
	static constexpr float kScale = 0.3f;						// �v���C���[�̃T�C�Y
	static constexpr int kWidth = 90;							// �v���C���[�̉���
	static constexpr int kHeight = 90;							// �v���C���[�̏c��
	static constexpr float kColPosAdjustment = 5.0f;			// �����蔻��ʒu����
	static constexpr float kInitPosX = 80.0f;					// �����ʒu
	static constexpr float kGroundHeight = 0.0f;				// �n�ʂ̍���

	// �W�����v�t���[��
	static constexpr int kLittleJumpFrame = 10;			// ���W�����v
	static constexpr int kMediumJumpFrame = 30;			// ���W�����v
	// �W�����v�̍���
	static constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
	static constexpr float kMediumJumpHeight = 0.8f;	// ���W�����v
	static constexpr float kBigJumpHeight = 1.0f;		// ��W�����v
};