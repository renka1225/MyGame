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
	void Update(Input& input, Player& player, EnemyBase& enemy);
	void Draw();
	void ClearEffect(); // ��ʏ�̃G�t�F�N�g���~����

private:
	struct Effect
	{
		int handle;
		VECTOR pos;
	};

	// �p�[�e�B�N���𐶂ݏo������
	struct EffectEmitter
	{
		int emitterHandle;
		std::vector<Effect> effects;
	};
	EffectEmitter emitter;
};