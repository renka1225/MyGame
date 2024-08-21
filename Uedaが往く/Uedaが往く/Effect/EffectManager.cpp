#include "EffekseerForDXLib.h"
#include "Input.h"
#include "Player.h"
#include "EnemyBase.h"
#include "EffectManager.h"

// �萔
namespace
{
	constexpr float kEffectScale = 5.0f; // �g�嗦
	constexpr int kEffectNum = 2;		 // �G�t�F�N�g�̎�ސ�
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectManager::EffectManager():
	m_isGuardEffect(false)
{
	emitter.emitterHandle.resize(kEffectNum);
	emitter.emitterHandle[EffectKind::kAttack] = LoadEffekseerEffect("data/Effect/attack.efk");
	emitter.emitterHandle[EffectKind::kGuard] = LoadEffekseerEffect("data/Effect/guard.efk");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectManager::~EffectManager()
{
	for (auto& handle : emitter.emitterHandle)
	{
		DeleteEffekseerEffect(handle);
	}
}


/// <summary>
/// ������
/// </summary>
void EffectManager::Init()
{
	Effekseer_InitDistortion();	// �G�t�F�N�g�̘c�݂�K�p����
	ClearEffect();
}


///// <summary>
///// �X�V
///// </summary>
void EffectManager::Update()
{
	Effekseer_Sync3DSetting();	// 3D�̏���DxLib��Effekseer�ō��킹��
	UpdateEffekseer3D();

	// �K�[�h�G�t�F�N�g���Đ�����Ă��Ȃ��ꍇ
	if (m_isGuardEffect && !IsEffekseer3DEffectPlaying(emitter.emitterHandle[EffectKind::kGuard]))
	{
		m_isGuardEffect = false;
	}
}


/// <summary>
/// �`��
/// </summary>
void EffectManager::Draw()
{
	DrawEffekseer3D();
}


/// <summary>
/// ��ʏ�̃G�t�F�N�g���폜����
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
/// �U���G�t�F�N�g���Đ�����
/// </summary>
/// <param name="pos">�G�t�F�N�g�ʒu</param>
void EffectManager::PlayDamageEffect(const VECTOR& pos)
{
	emitter.effects.push_back({ PlayEffekseer3DEffect(emitter.emitterHandle[EffectKind::kAttack]), {}});
	auto& effect = emitter.effects.back();

	// �G�t�F�N�g�̕\���ʒu��ݒ�
	SetPosPlayingEffekseer3DEffect(effect.handle, pos.x, pos.y, pos.z);
	SetScalePlayingEffekseer3DEffect(effect.handle, kEffectScale, kEffectScale, kEffectScale);
}


/// <summary>
/// �K�[�h�G�t�F�N�g���Đ�����
/// </summary>
/// <param name="pos">�G�t�F�N�g�ʒu</param>
void EffectManager::PlayGuardEffect(const VECTOR& pos)
{
	// TODO:�K�[�h��1��̂ݕ\�������悤�ɂ���

	if (m_isGuardEffect) return;

	m_isGuardEffect = true;
	emitter.effects.push_back({ PlayEffekseer3DEffect(emitter.emitterHandle[EffectKind::kGuard]), {} });
	auto& effect = emitter.effects.back();

	// �G�t�F�N�g�̕\���ʒu��ݒ�
	SetPosPlayingEffekseer3DEffect(effect.handle, pos.x, pos.y, pos.z);
	SetScalePlayingEffekseer3DEffect(effect.handle, kEffectScale, kEffectScale, kEffectScale);
}
