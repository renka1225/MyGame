#pragma once

/// <summary>
/// �X�e�[�W�̕`�擙���s���N���X
/// </summary>
class Stage
{
public:
	Stage();
	~Stage();
	void Init();
	void Update();
	void Draw();

	// ���ʂ�X�����̌X�΂��擾
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// ���ʂ�Y�����̌X�΂��擾
	VECTOR GetV3Vec2() const { return m_v3Vec2; }

private:
	// ���̏��
	VECTOR m_floorPos;
	int m_floorHandle;	// ����3D���f��

	// ���_�f�[�^
	VERTEX3D Vertex[4];
	WORD Index[6];

	// X�����̌X��
	VECTOR m_v3Vec1;
	// Y�����̌X��
	VECTOR m_v3Vec2;

	// �o�ߎ���
	int m_time;
	// �\���摜
	int m_handle;

private:	// �萔
	// ���̊g�嗦
	static constexpr float kFloorScaleX = 50.0f;
	static constexpr float kFloorScaleY = 1.0f;
	static constexpr float kFloorScaleZ = 50.0f;
};

