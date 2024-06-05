#pragma once
#include "DxLib.h"

/// <summary>
/// クォータニオンの計算を行う
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

// 演算子オーバーロード
Quaternion operator*(Quaternion lQ, Quaternion rQ)
{
	Quaternion tempQ = { tempQ.w, tempQ.x,  tempQ.y,  tempQ.z };

	// クォータニオンの掛け算
	tempQ.w = lQ.w * rQ.w - lQ.x * rQ.x - lQ.y * rQ.y - lQ.z * rQ.z; // 実部
	tempQ.x = lQ.w * rQ.x + lQ.x * rQ.w + lQ.y * rQ.z - lQ.z * rQ.y; // 虚部x
	tempQ.y = lQ.w * rQ.y + lQ.y * rQ.w + lQ.z * rQ.x - lQ.x * rQ.z; // 虚部y
	tempQ.z = lQ.w * rQ.z + lQ.z * rQ.w + lQ.x * rQ.y - lQ.y * rQ.x; // 虚部z

	return tempQ;
}

VECTOR operator*(Quaternion qRot, VECTOR right)
{
	//3次元座標をクオータニオンに変換
	Quaternion qPos = { 1.0f, right.x, right.y, right.z };
	//回転クォータニオンのインバースの作成
	Quaternion qInv = { qRot.w, -qRot.x, -qRot.y, -qRot.z };

	VECTOR vPos = VGet(0.0f, 0.0f, 0.0f);

	//回転後のクオータニオンの作成
	qPos = qRot * qPos * qInv;

	//３次元座標に戻す
	vPos.x = qPos.x;
	vPos.y = qPos.y;
	vPos.z = qPos.z;

	return vPos;
}