#pragma once

class DrawDebug;

/// <summary>
/// �X�e�[�W�̍X�V�ƕ`����s���N���X
/// </summary>
class Stage
{
public:
	Stage();
	virtual ~Stage();
	void Init();
	void Update();
	void Draw(DrawDebug& drawDebug);

	// ���ʂ�X�����̌X�΂��擾
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// ���ʂ�Y�����̌X�΂��擾
	VECTOR GetV3Vec2() const { return m_v3Vec2; }
	// �X�e�[�W�̈ʒu���擾
	VECTOR GetStagePos() const { return m_stagePos; }
	// �X�e�[�W���f�����擾
	int GetStageHandle() const { return m_stageHandle; }

private:
	void CreateFloor();	// �����쐬����

private:
	// ���̏��
	VECTOR m_floorPos;	// ���̈ʒu
	int m_floorHandle;	// ���̃��f��
	VECTOR m_v3Vec1;	// X�����̌X��
	VECTOR m_v3Vec2;	// Y�����̌X��
	// ���_�f�[�^
	VERTEX3D m_vertex[4];
	WORD m_index[6];

	// �X�e�[�W�̏��
	// TODO: ��قǕ����ɂ���̂�vector�ɂ���
	VECTOR m_stagePos;		// �X�e�[�W�̈ʒu
	VECTOR m_stageScale;	// �X�e�[�W�̊g�嗦
	float m_angle;			// �X�e�[�W�̊p�x
	int m_stageHandle;		// �X�e�[�W��3D���f��
};

