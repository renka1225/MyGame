#include "EffekseerForDXLib.h"
#include "Input.h"
#include "Player.h"
#include "EnemyBase.h"
#include "EffectManager.h"

// �萔
namespace
{
	constexpr float kEffectScale = 5.0f; // �g�嗦
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectManager::EffectManager()
{
	emitter.emitterHandle = LoadEffekseerEffect("data/Effect/test.efk");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectManager::~EffectManager()
{
	DeleteEffekseerEffect(emitter.emitterHandle);
}


/// <summary>
/// ������
/// </summary>
void EffectManager::Init()
{
	Effekseer_InitDistortion();	// �G�t�F�N�g�̘c�݂�K�p����
	ClearEffect();
}


/// <summary>
/// �X�V
/// </summary>
void EffectManager::Update(Input& input, Player& player, EnemyBase& enemy)
{
	Effekseer_Sync3DSetting();	// 3D�̏���DxLib��Effekseer�ō��킹��

	// TODO:�U��������������G�t�F�N�g���o��
	if (input.IsTriggered("punch"))
	{
		emitter.effects.push_back({PlayEffekseer3DEffect(emitter.emitterHandle), {}});
		auto& effect = emitter.effects.back();

		// �G�t�F�N�g�̕\���ʒu���X�V
		// MEMO:�v���C���[�̘r�̐�[�����ɃG�t�F�N�g��\��
		VECTOR armPos = player.GetCol().armEndPos;

		// �G�t�F�N�g�ʒu�Ɗp�x�𒲐�
		SetPosPlayingEffekseer3DEffect(effect.handle, armPos.x, armPos.y, armPos.z);
		SetScalePlayingEffekseer3DEffect(effect.handle, kEffectScale, kEffectScale, kEffectScale);
	}

	UpdateEffekseer3D();
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
