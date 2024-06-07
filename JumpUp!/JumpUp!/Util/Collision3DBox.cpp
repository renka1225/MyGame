#include "DxLib.h"
#include "Collision3DBox.h"
#include <utility>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Collision3DBox::Collision3DBox():
	m_minPos(VGet(0.0f, 0.0f, 0.0f)),
	m_maxPos(VGet(0.0f, 0.0f, 0.0f)),
	m_centerPos(VGet(0.0f, 0.0f, 0.0f)),
	m_left(0.0f),
	m_bottom(0.0f),
	m_front(0.0f),
	m_right(0.0f),
	m_top(0.0f),
	m_back(0.0f)
{
}


/// <summary>
/// �`��
/// </summary>
/// <param name="color">�����蔻��̐F</param>
/// <param name="pos">���f���̍��W</param>
/// <param name="size">���f���̓����蔻��̃T�C�Y</param>
void Collision3DBox::Draw(unsigned int color, VECTOR pos, VECTOR size)
{
	// �����蔻���`��
	//������O����E����O
	DrawLine3D(VGet(m_left, m_bottom, m_front), VGet(m_right, m_bottom, m_front), color);
	// ������O���獶���O
	DrawLine3D(VGet(m_left, m_bottom, m_front), VGet(m_left, m_top, m_front), color);
	// ������O���獶����
	DrawLine3D(VGet(m_left, m_bottom, m_front), VGet(m_left, m_bottom, m_back), color);
	// �E���O����E����O
	DrawLine3D(VGet(m_right, m_top, m_front), VGet(m_right, m_bottom, m_front), color);
	// �E���O���獶���O
	DrawLine3D(VGet(m_right, m_top, m_front), VGet(m_left, m_top, m_front), color);
	// �E���O����E�㉜
	DrawLine3D(VGet(m_right, m_top, m_front), VGet(m_right, m_top, m_back), color);
	// ���㉜���獶���O
	DrawLine3D(VGet(m_left, m_top, m_back), VGet(m_left, m_top, m_front), color);
	// ���㉜���獶����
	DrawLine3D(VGet(m_left, m_top, m_back), VGet(m_left, m_bottom, m_back), color);
	// ���㉜����E�㉜
	DrawLine3D(VGet(m_left, m_top, m_back), VGet(m_right, m_top, m_back), color);
	// �E�������獶����
	DrawLine3D(VGet(m_right, m_bottom, m_back), VGet(m_right, m_bottom, m_back), color);
	// �E��������E����O
	DrawLine3D(VGet(m_right, m_bottom, m_back), VGet(m_right, m_bottom, m_front), color);	
	// �E��������E�㉜
	DrawLine3D(VGet(m_right, m_bottom, m_back), VGet(m_right, m_top, m_front), color);
}

/// <summary>
/// ���S�_�ƕ��������s���w��
/// </summary>
/// <param name="pos"></param>
/// <param name="size"></param>
void Collision3DBox::SetCenter(VECTOR pos, VECTOR size)
{
	m_left = pos.x - size.x * 0.5f;
	m_top = pos.y - size.y * 0.5f;
	m_front = pos.z - size.z * 0.5f;
	m_right = pos.x + size.x * 0.5f;
	m_top = pos.y + size.y * 0.5f;
	m_back = pos.z + size.z * 0.5f;
}

/// <summary>
/// �o�E�f�B���O�{�b�N�X���쐬����
/// </summary>
/// <param name="handle">���f���n���h��</param>
void Collision3DBox::CreateBoundingBox(int handle)
{
	// ���b�V���̐����擾
	auto meshNum = MV1GetMeshNum(handle);
	for (int i = 0; i < meshNum; i++)
	{
		VECTOR modelMinPos = MV1GetMeshMinPosition(handle, i);
		VECTOR modelMaxPos = MV1GetMeshMaxPosition(handle, i);

		m_minPos.x = std::min(m_minPos.x, modelMinPos.x);
		m_minPos.y = std::min(m_minPos.y, modelMinPos.y);
		m_minPos.z = std::min(m_minPos.z, modelMinPos.z);

		m_maxPos.x = std::max(m_maxPos.x, modelMaxPos.x);
		m_maxPos.y = std::max(m_maxPos.y, modelMaxPos.y);
		m_maxPos.z = std::max(m_maxPos.z, modelMaxPos.z);
	}
	m_centerPos = VScale(VAdd(m_minPos, m_maxPos), 0.5f);
}


/// <summary>
/// �����̓��m�̓����蔻��̏���
/// </summary>
/// <param name="col3DBox">������s��3D���f��</param>
/// <returns>����������</returns>
bool Collision3DBox::IsCollision(const Collision3DBox& col3DBox)
{	
	//// ���΃x�N�g�������߂�
	//VECTOR v3SubAbs = VSub(m_centerPos, col3DBox.m_centerPos);
	//v3SubAbs = VGet(abs(v3SubAbs.x), abs(v3SubAbs.y), abs(v3SubAbs.z));

	//// �Փˋ��������߂�
	//// �Փˋ����͂��ꂼ��̑Ή������ӂ̒����𑫂���2�Ŋ���������
	//VECTOR v3AddScale = VScale(VAdd((VGet(kScale, kScale, kScale), MV1GetScale(stage.GetStageHandle())), 0.5f);
	//// TODO;�����蔻��͈̔͂��L����(������)
	//v3AddScale = VAdd(v3AddScale, VGet(0.0f, 20.0f, 0.0f));

	//// �e�����̓����蔻��
	//bool isXHit = v3SubAbs.x < v3AddScale.x;
	//bool isYHit = v3SubAbs.y < v3AddScale.y;
	//bool isZHit = v3SubAbs.z < v3AddScale.z;

	//if (isXHit && isYHit && isZHit) return true;

	//return false;

	// ��΂ɓ�����Ȃ��p�^�[�����͂����Ă���
	if (m_left > col3DBox.m_right) return false;
	if (m_top > col3DBox.m_bottom) return false;
	if (m_front > col3DBox.m_back) return false;
	if (m_right < col3DBox.m_left) return false;
	if (m_bottom < col3DBox.m_top) return false;
	if (m_back < col3DBox.m_front) return false;

	// ������Ȃ��p�^�[���ȊO�͓������Ă���
	return true;
}
