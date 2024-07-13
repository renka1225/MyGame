#pragma once
#include <memory>

class Player;
class UIGauge;

/// <summary>
/// �G�̊��N���X
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();
	virtual void Init() = 0;
	virtual void Update(Player& player) = 0;
	virtual void Draw() = 0;
	virtual void OnDamage(float damage);	// �U�����󂯂��ۂ̏���

	float GetHp() const { return m_hp; }	// �G��HP���擾
	VECTOR GetPos() const { return m_pos; } // �G�̍��W���擾

protected:
	std::shared_ptr<UIGauge> m_pUIGauge;

	VECTOR m_pos;		// �ʒu
	float m_hp;			// HP
	int m_modelHandle;	// �G��3D���f��
};

