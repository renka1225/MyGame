#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;

/// <summary>
/// �w�i�N���X
/// </summary>
class Background
{
public:
	Background();
	~Background() {};

	void Init();
	void Update();
	void Draw();
	void End();

private:
	// ���f���N���X�̃|�C���^
	std::shared_ptr<ManagerModel> m_pModel;

	// �\���ʒu
	VECTOR m_pos;
	VECTOR m_pos2;

	// �w�i
	int m_background;
	int m_background2;

private:	// �萔
	static constexpr float kBgSize = 300.0f;	// �w�i�摜�̃T�C�Y
	static constexpr float kBgMove = -0.005f;	// �w�i�̈ړ���
};

