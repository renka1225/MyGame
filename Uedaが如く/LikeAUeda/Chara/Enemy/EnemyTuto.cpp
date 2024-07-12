#include "DxLib.h"
#include "Player.h"
#include "UIGauge.h"
#include "EnemyTuto.h"

// �萔
namespace
{
	const char* const kfileName = "data/Model/enemy.mv1";	// �G�̃t�@�C����
	constexpr float kScale = 0.25f;							// �g�嗦
	constexpr float kMaxHp = 1000.0f;						// �ő�HP
	const VECTOR kInitPos = VGet(0.0f, 10.0f, 5.0f);		// �����ʒu
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyTuto::EnemyTuto()
{
	m_hp = kMaxHp;
	m_modelHandle = MV1LoadModel(kfileName);
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyTuto::~EnemyTuto()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// ������
/// </summary>
void EnemyTuto::Init()
{
	MV1SetPosition(m_modelHandle, kInitPos);
}


/// <summary>
/// �X�V
/// </summary>
void EnemyTuto::Update(Player& player)
{
	// �v���C���[�Ƃ̓����蔻����`�F�b�N����
	player.CheckCollision(*this, m_pos);
}


/// <summary>
/// �`��
/// </summary>
void EnemyTuto::Draw()
{
	// �G���f���`��
	MV1DrawModel(m_modelHandle);

	// HP�Q�[�W��\��
	m_pUIGauge->DrawEnemyHp(m_hp, kMaxHp);

#ifdef _DEBUG
	// �G���W�f�o�b�O�\��
	DrawFormatString(0, 60, 0xffffff, "�G���W(x:%f, y:%f, z:%f)", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 80, 0xffffff, "hp:%f", m_hp);
#endif

}
