#pragma once
#include <vector>

class Player;
class EnemyBase;

/// <summary>
/// �G�t�F�N�g�Ǘ��N���X
/// </summary>
class EffectManager
{
public:
	EffectManager();
	~EffectManager();
	void Init();
	void Update();
	void Draw();
	void ClearEffect();											// ��ʏ�̃G�t�F�N�g���~����
	void PlayDamageEffect(const VECTOR& pos);					// �U���G�t�F�N�g���Đ�����
	void PlayGuardEffect(const VECTOR& pos);					// �K�[�h�G�t�F�N�g���Đ�����
	bool IsPlayGuardEffect() const { return m_isGuardEffect; }	// �K�[�h�G�t�F�N�g���Đ�����

private:
	bool m_isGuardEffect;	// �K�[�h�G�t�F�N�g���Đ�����Ă��邩�ǂ���

	struct Effect
	{
		int handle;
		VECTOR pos;
	};

	// �p�[�e�B�N���𐶂ݏo������
	struct EffectEmitter
	{
		std::vector<int> emitterHandle;
		std::vector<Effect> effects;
	};
	EffectEmitter emitter;

	// �G�t�F�N�g�̎��
	enum EffectKind
	{
		kAttack,	// �U��
		kGuard,		// �K�[�h
	};
};