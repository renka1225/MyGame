#pragma once
#include "Collision3DBox.h"

class Player;
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
	// �����蔻������āA�␳�����ړ���̃|�W�V������Ԃ�
	VECTOR CheckCollision(Player& player, const VECTOR& moveVector);

	// �w�肵�������̂Ɠ������Ă��邩����
	bool IsCollision(Collision3DBox col3DBox, Collision3DBox& col3DMap);

	// ���ʂ�X�����̌X�΂��擾
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// ���ʂ�Y�����̌X�΂��擾
	VECTOR GetV3Vec2() const { return m_v3Vec2; }
	// �X�e�[�W�̈ʒu���擾
	VECTOR GetStagePos() const { return m_stagePos; }
	// �X�e�[�W���f�����擾
	int GetStageHandle() const { return m_stageHandle; }

private:
	// �����쐬����
	void CreateFloor();
	// ���o���ꂽ�|���S�����ǃ|���S�������|���S�����𔻒f���A�ۑ�����
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);
	// �ǃ|���S���Ƃ̓�������`�F�b�N���A�v���C���[�̕␳���ׂ��ړ��x�N�g����Ԃ�
	VECTOR CheckHitWithWall(Player& player, const VECTOR& checkPosition);
	// ���|���S���Ƃ̓�������`�F�b�N���A�v���C���[�̕␳���ׂ��ړ��x�N�g����Ԃ�
	//VECTOR CheckHitWithFloor(Player& player, const VECTOR& checkPosition);

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

	// �ǂ̏��
	int m_wallNum;	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
	int	m_floorNum;	// ���|���S���Ɣ��f���ꂽ�|���S���̐�

	static const int MaxHitColl = 2048;			// ��������R���W�����|���S���̍ő吔
	MV1_COLL_RESULT_POLY* m_wall[MaxHitColl];		// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_floor[MaxHitColl];	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
};

