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

private:
	// ���̏��
	VECTOR m_floorPos;
	int m_floorHandle;	// ����3D���f��

private:	// �萔
	// ���̊g�嗦
	static constexpr float kFloorScaleX = 50.0f;
	static constexpr float kFloorScaleY = 1.0f;
	static constexpr float kFloorScaleZ = 50.0f;
};

