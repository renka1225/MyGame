#include "Camera.h"
#include "Player.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera(std::shared_ptr<Player> pPlayer):
	m_pPlayer(pPlayer),
	m_pos(VGet(0.0f, 0.0f, m_pPlayer->GetPos().z + kTargetZ))
{
	// ����p�̐ݒ�
	SetupCamera_Perspective(kFov);
	// �J�����̕`��͈�
	SetCameraNearFar(kNear, kFar);
	// �J������ݒu
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(0.0f, kTargetY, 0.0f));
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
	// �����Ȃ�
}


/// <summary>
/// ������
/// </summary>
void Camera::Init()
{
	// �����Ȃ�
}


/// <summary>
/// �X�V
/// </summary>
void Camera::Update()
{
	// �J�����ʒu�̒���
	VECTOR aimPos = VGet(kTargetX, kTargetY, m_pPlayer->GetPos().z + kTargetZ);
	VECTOR posToAim = VSub(aimPos, m_pos);
	m_pos = VAdd(m_pos, posToAim);

	// �J�����ʒu�𔽉f
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(kTargetX, kTargetY, 0.0f));
}
