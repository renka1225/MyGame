#pragma once
#include <vector>

class Player;
class EnemyBase;

/// <summary>
/// エフェクト管理クラス
/// </summary>
class EffectManager
{
public:
	EffectManager();
	~EffectManager();
	void Init();
	void Update(Input& input, Player& player, EnemyBase& enemy);
	void Draw();

private:
	struct Effect
	{
		int handle;
		VECTOR pos;
	};

	// パーティクルを生み出すもの
	struct EffectEmitter
	{
		int emitterHandle;
		std::vector<Effect> effects;
	};
	EffectEmitter emitter;
};