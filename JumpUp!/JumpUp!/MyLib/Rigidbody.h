#pragma once

/// <summary>
/// 物理・衝突判定に必要なデータを管理するクラス
/// </summary>
class Rigidbody
{
public:
	Rigidbody();
	void Init();

	// 現在位置を取得
	VECTOR GetPos() const { return m_pos; }
	VECTOR GetDir() const { return m_dir; }
	VECTOR Getvelocity() const { return m_velocity; }

	void SetPos(const VECTOR& set) { m_pos = set; }
	void SetVelocity(const VECTOR& set);

private:
	VECTOR m_pos;		// 表示位置
	VECTOR m_dir;		// 方向
	VECTOR m_velocity;	// 速度
};

