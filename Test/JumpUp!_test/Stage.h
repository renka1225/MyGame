#pragma once
#include "Collidable.h"
#include <memory>

class Player;
class Collidable;
class DrawDebug;

/// <summary>
/// �X�e�[�W�̕`��ƍX�V���s���N���X
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

	// �����蔻������āA�␳��̃|�W�V������Ԃ�
	VECTOR CheckCollision(Player& player, const VECTOR& moveVector);

	// ���ʂ�X�����̌X�΂��擾
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// ���ʂ�Y�����̌X�΂��擾
	VECTOR GetV3Vec2() const { return m_v3Vec2; }
	// �X�e�[�W�̈ʒu���擾
	VECTOR GetStagePos() const { return m_stagePos; }
	// �X�e�[�W���f�����擾
	int GetStageHandle() const { return m_stageHandle; }

private:
	// ���o���ꂽ�|���S�����ǃ|���S�������|���S�����𔻒f���A�ۑ�����
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);
	// �ǃ|���S���Ƃ̓�������`�F�b�N���A�v���C���[�̕␳���ׂ��ړ��x�N�g����Ԃ�
	VECTOR CheckHitWithWall(Player& player, const VECTOR& checkPosition);
	// ���|���S���Ƃ̓�������`�F�b�N���A�v���C���[�̕␳���ׂ��ړ��x�N�g����Ԃ�
	VECTOR CheckHitWithFloor(Player& player, const VECTOR& checkPosition);

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

	// �ǂ̏��
	int m_wallNum;	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
	int	m_floorNum;	// ���|���S���Ɣ��f���ꂽ�|���S���̐�

	static const int MaxHitColl = 2048;			// ��������R���W�����|���S���̍ő吔
	MV1_COLL_RESULT_POLY* m_wall[MaxHitColl];		// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* m_floor[MaxHitColl];	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��

private:	// �萔
	// ���̊g�嗦
	static constexpr float kFloorScaleX = 30.0f;
	static constexpr float kFloorScaleY = 10.0f;
	static constexpr float kFloorScaleZ = 20.0f;
	static constexpr float kHitWidth = 200.0f;	// �����蔻��J�v�Z���̔��a
	static constexpr float kHitHeight = 700.0f;	// �����蔻��J�v�Z���̍���

	// �����蔻��
	static constexpr float kCenterPosY = 5.0f;	// �n�ʂ̒��S�_�𒲐�
	static constexpr int kHitTryNum = 16;		// �ǉ����o�������̍ő厎�s��
};

