#pragma once
#include "DxLib.h"
#include <memory>

class Player;

/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
public:
	Camera();
	virtual ~Camera();
	void Init();
	void Update(std::shared_ptr<Player> pPlayer);

	VECTOR GetPos() const { return m_pos; }		// �J�����ʒu���擾

private:
	std::shared_ptr<Player> m_pPlayer;

	VECTOR m_pos;
};