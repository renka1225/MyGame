#pragma once
#include "DxLib.h"

/// <summary>
/// �N�H�[�^�j�I���̌v�Z���s��
/// </summary>
class Quaternion
{
public:
	float w;
	float x;
	float y;
	float z;

public:
	Quaternion(float w, float x, float y, float z) :
		w(w),
		x(x),
		y(y),
		z(z)
	{};
};

// ���Z�q�I�[�o�[���[�h
Quaternion operator*(Quaternion lQ, Quaternion rQ)
{
	Quaternion tempQ = { tempQ.w, tempQ.x,  tempQ.y,  tempQ.z };

	// �N�H�[�^�j�I���̊|���Z
	tempQ.w = lQ.w * rQ.w - lQ.x * rQ.x - lQ.y * rQ.y - lQ.z * rQ.z; // ����
	tempQ.x = lQ.w * rQ.x + lQ.x * rQ.w + lQ.y * rQ.z - lQ.z * rQ.y; // ����x
	tempQ.y = lQ.w * rQ.y + lQ.y * rQ.w + lQ.z * rQ.x - lQ.x * rQ.z; // ����y
	tempQ.z = lQ.w * rQ.z + lQ.z * rQ.w + lQ.x * rQ.y - lQ.y * rQ.x; // ����z

	return tempQ;
}

VECTOR operator*(Quaternion qRot, VECTOR right)
{
	//3�������W���N�I�[�^�j�I���ɕϊ�
	Quaternion qPos = { 1.0f, right.x, right.y, right.z };
	//��]�N�H�[�^�j�I���̃C���o�[�X�̍쐬
	Quaternion qInv = { qRot.w, -qRot.x, -qRot.y, -qRot.z };

	VECTOR vPos = VGet(0.0f, 0.0f, 0.0f);

	//��]��̃N�I�[�^�j�I���̍쐬
	qPos = qRot * qPos * qInv;

	//�R�������W�ɖ߂�
	vPos.x = qPos.x;
	vPos.y = qPos.y;
	vPos.z = qPos.z;

	return vPos;
}