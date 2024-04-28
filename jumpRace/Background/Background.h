#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;
class WorldSprite;

/// <summary>
/// �w�i�N���X
/// </summary>
class Background
{
public:
	Background(std::shared_ptr<ManagerModel> pModel);
	~Background();

	void Init();
	void Update();
	void Draw();

private:
	std::shared_ptr<ManagerModel> m_pModel;
	std::shared_ptr<WorldSprite> m_sprite;

	VECTOR m_backgroundPos;		// �w�i�̕\���ʒu
	VECTOR m_treePos;			// �؂̕\���ʒu

	int m_background;	// �w�i�̉摜
	int m_groundModel;	// �n�ʂ�3D���f��
	int m_treeModel;	// �؂�3D���f��

private:	// �萔
	static constexpr int kWidth = 2304;					// �w�i�摜�̉���
	static constexpr int kHeight = 1296;				// �w�i�摜�̏c��
	static constexpr float kBackScele = 100.0f;			// �w�i�摜�̊g�嗦
	static constexpr float kGroundPosY = 100.0f;		// �n�ʂ̈ʒuY
	static constexpr float kGroundPosZ = 0.0f;			// �n�ʂ̈ʒuZ
	static constexpr float kGroundScaleWidth = 300.0f;	// �n�ʉ��̊g�嗦
	static constexpr float kGroundScaleHeight = 20.0f;	// �n�ʍ����̊g�嗦
	static constexpr float kGroundScaleDepth = 700.0f;	// �n�ʉ��s���̊g�嗦
};

