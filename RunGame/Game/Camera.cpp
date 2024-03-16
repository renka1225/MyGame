#include "Camera.h"
#include "Player.h"

/// <summary>
/// �萔
/// </summary>
namespace
{
	// ����p
	constexpr float kFov = (DX_PI_F / 180.0f) * 60.0f;
	// ��O�N���b�v����
	constexpr float kNear = 0.1f;
	// ���N���b�v����
	constexpr float kFar = 1000.0f;
	// �J�����̏��������_
	constexpr float kTargetX = 0.0f;	// X��
	constexpr float kTargetY = 80.0f;	// Y��
	constexpr float kTargetZ = -150.0f;	// Z��

}

Camera::Camera():
	m_pos(VGet(0.0f, 0.0f, 0.0f))
{
	// ����p�̐ݒ�
	SetupCamera_Perspective(kFov);
	// �J�����̕`��͈�
	SetCameraNearFar(kNear, kFar);
	// �J������ݒu
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(0.0f, kTargetY, 0.0f));
}

Camera::~Camera()
{
	// �����Ȃ�
}

/// <summary>
/// ������
/// </summary>
void Camera::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
void Camera::Update(std::shared_ptr<Player> pPlayer)
{
	// �v���C���[�̃|�C���^���擾
	m_pPlayer = pPlayer;

	// �J�����ʒu�̒���
	VECTOR aimPos = VGet(m_pPlayer->GetPos().x, kTargetY, kTargetZ);
	VECTOR posToAim = VSub(aimPos, m_pos);
	m_pos = VAdd(m_pos, posToAim);

	// �J�����ʒu�𔽉f
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(m_pPlayer->GetPos().x, kTargetY, 0.0f));
}