#include "Camera.h"
#include "Player.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
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
void Camera::Update(std::shared_ptr<Player> pPlayer)
{
	//// �v���C���[�̃|�C���^���擾
	//m_pPlayer = pPlayer;

	//// �J�����ʒu�̒���
	//VECTOR aimPos = VGet(m_pPlayer->GetPos().x, kTargetY, kTargetZ);
	//VECTOR posToAim = VSub(aimPos, m_pos);
	//m_pos = VAdd(m_pos, posToAim);

	//// �J�����ʒu�𔽉f
	//SetCameraScreenCenter(m_pPlayer->GetPos().x + kScreenCenterX, kScreenCenterY);
	//SetCameraPositionAndTarget_UpVecY(m_pos, VGet(m_pPlayer->GetPos().x, kTargetY, 0.0f));
}