#pragma once
#include "Vec2.h"

/// <summary>
/// �|�[�Y�V�[���N���X
/// </summary>
class ScenePause
{
public:
	ScenePause();
	~ScenePause();
	void Init();
	void Update();
	void Draw();
	// �|�[�Y��ʂ��\������Ă��邩�擾����
	bool IsExist() const { return m_isExist; }

private:
	// �|�[�Y��ʂ̕\���ʒu
	Vec2 m_pos;

	// �|�[�Y��ʂ��\������Ă��邩 true:�\������Ă���
	bool m_isExist;

};

