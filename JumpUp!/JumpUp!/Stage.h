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
	int m_floorHandle;	// ���̃��f��

	// ���_�f�[�^
	VERTEX3D Vertex[4];
	WORD Index[6];

	// X�����̌X��
	VECTOR m_v3Vec1;
	// Y�����̌X��
	VECTOR m_v3Vec2;

	// �X�e�[�W�̏��
	VECTOR m_stagePos;
	// �X�e�[�W��3D���f��
	int m_stageHandle;

private:	// �萔
	// ���̊g�嗦
	static constexpr float kFloorScaleX = 30.0f;
	static constexpr float kFloorScaleY = 10.0f;
	static constexpr float kFloorScaleZ = 20.0f;
};

