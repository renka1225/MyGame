#include "Camera.h"
#include "Player.h"

#define DegreeToRadian (DX_PI_F / 180.0f)
float DegToRad(float degree) { return (DegreeToRadian * degree); }

Camera::Camera():
	m_pos(VGet(0, 20, -30))
{
	// ����p�̐ݒ�
	SetupCamera_Perspective(DegToRad(60.0f));
	// �J�����̕`��͈�
	SetCameraNearFar(0.1f, 1000.0f);
	// �J������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(0, 50, -100), VGet(0.0f, 17.0f, 0.0f));
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
	VECTOR aimPos = VGet(m_pPlayer->GetPos().x, 0.0f, -200.0f);
	VECTOR posToAim = VSub(aimPos, m_pos);
	VECTOR scaledPosToAim = VScale(posToAim, 0.1f);
	m_pos = VAdd(m_pos, scaledPosToAim);

	// �J�����ʒu�𔽉f
	SetCameraPositionAndTarget_UpVecY(m_pos, m_pPlayer->GetPos());
}