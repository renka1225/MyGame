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

	// �g�̕\���ʒu
	int m_wavePosX;

	// �w�i
	int m_background;

private:	// �萔
	static constexpr float kBackgroundSize = 300.0f;	// �w�i�摜�̃T�C�Y

	static constexpr int kWaveAmplitude = 10;	// �g�̐U��
	static constexpr int kWaveFrequency = 100;	// �g�̎��g��
	static constexpr int kWaveRange = 1000;		// �g�̕`��͈�
	static constexpr int kDrawWaveY = 450;		// �g�̕`��ʒuY���W
};

