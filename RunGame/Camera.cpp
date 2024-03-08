#include "Camera.h"
#include "Player.h"

#define DegreeToRadian (DX_PI_F / 180.0f)
float DegToRad(float degree) { return (DegreeToRadian * degree); }

Camera::Camera(Player* pPlayer):
	m_pPlayer(pPlayer),
	m_pos(VGet(0, 20, -30))
{
	// ����p�̐ݒ�
	SetupCamera_Perspective(DegToRad(60.0f));
	// �J�����̕`��͈�
	SetCameraNearFar(0.1f, 1000.0f);
	// �J������ڒn
	SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));
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
void Camera::Update()
{
}