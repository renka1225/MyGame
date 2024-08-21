#include "EffekseerForDXLib.h"
#include "Input.h"
#include "Player.h"
#include "EnemyBase.h"
#include "EffectManager.h"

// 定数
namespace
{
	constexpr float kEffectScale = 5.0f; // 拡大率
	constexpr int kEffectNum = 2;		 // エフェクトの種類数
}


/// <summary>
/// コンストラクタ
/// </summary>
EffectManager::EffectManager():
	m_isGuardEffect(false)
{
	emitter.emitterHandle.resize(kEffectNum);
	emitter.emitterHandle[EffectKind::kAttack] = LoadEffekseerEffect("data/Effect/attack.efk");
	emitter.emitterHandle[EffectKind::kGuard] = LoadEffekseerEffect("data/Effect/guard.efk");
}


/// <summary>
/// デストラクタ
/// </summary>
EffectManager::~EffectManager()
{
	for (auto& handle : emitter.emitterHandle)
	{
		DeleteEffekseerEffect(handle);
	}
}


/// <summary>
/// 初期化
/// </summary>
void EffectManager::Init()
{
	Effekseer_InitDistortion();	// エフェクトの歪みを適用する
	ClearEffect();
}


///// <summary>
///// 更新
///// </summary>
void EffectManager::Update()
{
	Effekseer_Sync3DSetting();	// 3Dの情報をDxLibとEffekseerで合わせる
	UpdateEffekseer3D();

	// ガードエフェクトが再生されていない場合
	if (m_isGuardEffect && !IsEffekseer3DEffectPlaying(emitter.emitterHandle[EffectKind::kGuard]))
	{
		m_isGuardEffect = false;
	}
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


/// <summary>
/// 攻撃エフェクトを再生する
/// </summary>
/// <param name="pos">エフェクト位置</param>
void EffectManager::PlayDamageEffect(const VECTOR& pos)
{
	emitter.effects.push_back({ PlayEffekseer3DEffect(emitter.emitterHandle[EffectKind::kAttack]), {}});
	auto& effect = emitter.effects.back();

	// エフェクトの表示位置を設定
	SetPosPlayingEffekseer3DEffect(effect.handle, pos.x, pos.y, pos.z);
	SetScalePlayingEffekseer3DEffect(effect.handle, kEffectScale, kEffectScale, kEffectScale);
}


/// <summary>
/// ガードエフェクトを再生する
/// </summary>
/// <param name="pos">エフェクト位置</param>
void EffectManager::PlayGuardEffect(const VECTOR& pos)
{
	// TODO:ガード中1回のみ表示されるようにする

	if (m_isGuardEffect) return;

	m_isGuardEffect = true;
	emitter.effects.push_back({ PlayEffekseer3DEffect(emitter.emitterHandle[EffectKind::kGuard]), {} });
	auto& effect = emitter.effects.back();

	// エフェクトの表示位置を設定
	SetPosPlayingEffekseer3DEffect(effect.handle, pos.x, pos.y, pos.z);
	SetScalePlayingEffekseer3DEffect(effect.handle, kEffectScale, kEffectScale, kEffectScale);
}
