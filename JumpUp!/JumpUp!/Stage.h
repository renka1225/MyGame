#pragma once
#include "Collidable.h"
#include <memory>

class Collidable;
class DrawDebug;

/// <summary>
/// �X�e�[�W�̕`�擙���s���N���X
/// </summary>
class Stage : public Collidable
{
public:
	Stage();
	virtual ~Stage();
	void Init(std::shared_ptr<Physics> physics);
	void Final(std::shared_ptr<Physics> physics);
	void Update();
	void Draw(DrawDebug& drawDebug);
	virtual void OnCollide()override;	// �Փ˂����Ƃ�

	// ���ʂ�X�����̌X�΂��擾
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// ���ʂ�Y�����̌X�΂��擾
	VECTOR GetV3Vec2() const { return m_v3Vec2; }
	// �X�e�[�W�̈ʒu���擾
	VECTOR GetStagePos() const { return m_stagePos; }
	// �X�e�[�W���f�����擾
	int GetStageHandle() const { return m_stageHandle; }

private:
	// ���̏��
	VECTOR m_floorPos;	// ���̈ʒu
	int m_floorHandle;	// ���̃��f��

	// ���_�f�[�^
	VERTEX3D Vertex[4];
	WORD Index[6];

	// X�����̌X��
	VECTOR m_v3Vec1;
	// Y�����̌X��
	VECTOR m_v3Vec2;

	// �X�e�[�W�̏��
	VECTOR m_stagePos;		// �X�e�[�W�̈ʒu
	VECTOR m_stageScale;	// �X�e�[�W�̊g�嗦
	int m_stageHandle;		// �X�e�[�W��3D���f��

private:	// �萔
	// ���̊g�嗦
	static constexpr float kFloorScaleX = 30.0f;
	static constexpr float kFloorScaleY = 10.0f;
	static constexpr float kFloorScaleZ = 20.0f;

	// �����蔻��
	static constexpr float kCenterPosY = 5.0f;	// �n�ʂ̒��S�_�𒲐�
};

