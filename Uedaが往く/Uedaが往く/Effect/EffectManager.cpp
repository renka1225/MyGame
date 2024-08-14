#include "EffekseerForDXLib.h"
#include "Input.h"
#include "Player.h"
#include "EnemyBase.h"
#include "EffectManager.h"

// 定数
namespace
{
	constexpr float kEffectScale = 5.0f; // 拡大率
}


/// <summary>
/// コンストラクタ
/// </summary>
EffectManager::EffectManager()
{
	emitter.emitterHandle = LoadEffekseerEffect("data/Effect/test.efk");
}


/// <summary>
/// デストラクタ
/// </summary>
EffectManager::~EffectManager()
{
	DeleteEffekseerEffect(emitter.emitterHandle);
}


/// <summary>
/// 初期化
/// </summary>
void EffectManager::Init()
{
	Effekseer_InitDistortion();	// エフェクトの歪みを適用する
	ClearEffect();
}


/// <summary>
/// 更新
/// </summary>
void EffectManager::Update(Input& input, Player& player, EnemyBase& enemy)
{
	Effekseer_Sync3DSetting();	// 3Dの情報をDxLibとEffekseerで合わせる

	// TODO:攻撃が当たったらエフェクトを出す
	if (input.IsTriggered("punch"))
	{
		emitter.effects.push_back({PlayEffekseer3DEffect(emitter.emitterHandle), {}});
		auto& effect = emitter.effects.back();

		// エフェクトの表示位置を更新
		// MEMO:プレイヤーの腕の先端部分にエフェクトを表示
		VECTOR armPos = player.GetCol().armEndPos;

		// エフェクト位置と角度を調整
		SetPosPlayingEffekseer3DEffect(effect.handle, armPos.x, armPos.y, armPos.z);
		SetScalePlayingEffekseer3DEffect(effect.handle, kEffectScale, kEffectScale, kEffectScale);
	}

	UpdateEffekseer3D();
}


/// <summary>
/// 描画
/// </summary>
void EffectManager::Draw()
{
	DrawEffekseer3D();
}


/// <summary>
/// 画面上のエフェクトを削除する
/// </summary>
void EffectManager::ClearEffect()
{
	for (auto& e : emitter.effects)
	{
		StopEffekseer3DEffect(e.handle);
	}
	emitter.effects.clear();
}
