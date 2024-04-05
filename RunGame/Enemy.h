#pragma once
#include "Rect.h"
#include "DxLib.h"
#include <memory>
#include <vector>

class ManagerModel;

/// <summary>
/// �G�N���X
/// </summary>
class Enemy
{
public:
	Enemy(std::shared_ptr<ManagerModel> pModel);
	virtual ~Enemy();
	void Init(VECTOR pos);
	void Update();
	void Draw();
	void End();

	Rect GetColRect() const { return m_colRect; }	// �����蔻����擾����
	
private:
	// ���f���N���X�̃|�C���^
	std::shared_ptr<ManagerModel> m_pModel;

	// �G�̈ʒu
	VECTOR m_pos;
	// �����蔻��p�̋�`
	Rect m_colRect;

	// ���݃t���O
	bool m_isExist;

	// 3D���f��
	int m_modelHandle;

private:	// �萔

	static constexpr float kMove = -10.0f;						// �ړ���
	static constexpr float kScale = 0.05f;						// �g�嗦
	static constexpr int kWidth = 140;							// �G�̉���
	static constexpr int kHeight = 50;							// �G�̏c��
	static constexpr float kDirY = 180.0f * DX_PI_F / 180.0f;	// ����
};