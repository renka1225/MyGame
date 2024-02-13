#pragma once
#include "Vec2.h"
#include <vector>
#include <list>

/// <summary>
/// �ԉ΃N���X
/// </summary>
class Fireworks
{
public:
	Fireworks(int startX);
	void Update();
	void Draw();
	void Fire();

private:
	/// <summary>
	/// �ł�������
	/// </summary>
	void RiseUpdate();
	void RiseDraw();

	/// <summary>
	/// ����
	/// </summary>
	void ExplodeUpdate();
	void ExplodeDraw();

	/// <summary>
	/// �ҋ@
	/// </summary>
	void WaitUpdate();
	void WaitDraw();

	/*using UpdateFunc_t = void (Fireworks::*)();
	using DrawFunc_t = void (Fireworks::*)();
	UpdateFunc_t updateFunc_;
	UpdateFunc_t drawFunc_;*/

	// �ԉ΂̒��S
	Vec2 m_pos;
	std::list<Vec2> m_historyPos;

	// ��юU�������̉ԉ΂̃p�[�c
	struct FirePart
	{
		Vec2 m_pos;	// ���݂̍��W
		Vec2 m_vec;	// ���x(�d�͂̉e�����󂯂�)
		std::list<Vec2> m_historyPos;
	};
	std::vector<FirePart> m_fireParts;	// �l�������ɎU�炷
	int m_height;
	int m_frame;
};

