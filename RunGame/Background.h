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
	Background(std::shared_ptr<ManagerModel> pModel);
	~Background();

	void Init();
	void Update();
	void Draw();
	void End();

private:
	// ���f���N���X�̃|�C���^
	std::shared_ptr<ManagerModel> m_pModel;

	// �\���ʒu
	VECTOR m_pos;

	// ���ʂ�3D���f��
	int m_waterHandle;
};

