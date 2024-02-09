#include "EnemyBear.h"
#include "Bg.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �G�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �G�t�F�N�g�̃T�C�Y
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;

	// �g�嗦
	constexpr float kEnlarge = 8.0f;
	constexpr float kEffectScale = 5.0f;

	// �����蔻��̃T�C�Y
	constexpr float kColWidth = 20.0f * kEnlarge;
	constexpr float kColHeight = 12.0f * kEffectScale;

	// �ړ����x
	constexpr float kSpeedX = 5.0f;
	constexpr float kSpeedY = 10.0f;
	// �ő�HP
	constexpr int kHp = 15;

	/*�ҋ@�A�j���[�V����*/
	// �A�j���[�V����
	constexpr int kIdleUseFrame[] = { 0, 1, 2, 3 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kIdleAnimFrameNum = 20;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kIdleAnimFrameCycle = _countof(kIdleUseFrame) * kIdleAnimFrameNum;

	/*�ːi�A�j���[�V����*/
	// �A�j���[�V����
	constexpr int kRunUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kRunAnimFrameNum = 18;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kRunAnimFrameCycle = _countof(kRunUseFrame) * kRunAnimFrameNum;

	/*�񕜃A�j���[�V����*/
	// �A�j���[�V����
	constexpr int kRecUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kRecAnimFrameNum = 30;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kRecAnimFrameCycle = _countof(kRecUseFrame) * kRecAnimFrameNum;


	/*�G�t�F�N�g*/
	constexpr int kDamageUseFrame[] = { 0, 1, 2, 3 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kEffectFrameNum = 16;
	// �_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;
}


EnemyBear::EnemyBear() :
	m_animation(kIdle),
	m_idleAnimFrame(0),
	m_runAnimFrame(0),
	m_recoveryAnimFrame(0)
{
	m_handle = LoadGraph("data/image/Enemy/bear.png");
}

EnemyBear::~EnemyBear()
{
	DeleteGraph(m_handle);
}

void EnemyBear::Init(Bg* pBg, Player* pPlayer)
{
	m_pBg = pBg;
	m_pPlayer = pPlayer;
	m_hp = kHp;
	m_isDead = false;
	m_animation = kIdle;
	m_dir = kDirLeft;
}

void EnemyBear::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// �}�b�v�`�b�v�Ƃ̓����蔻��
	Rect chipRect; // ���������}�b�v�`�b�v�̋�`
	HitCollision(chipRect);

	/*�ړ�*/
	// ���E�ړ����s��
	if (m_pos.x > m_startPos.x + m_moveRangeX)
	{
		m_vec.x *= -1;
		m_dir = kDirRight;
	}
	else if (m_pos.x < m_startPos.x - m_moveRangeX)
	{
		m_vec.x *= -1;
		m_dir = kDirLeft;
	}

	// �v���C���[�ƌF�̋���
	float kDis = m_pos.x - m_pPlayer->GetPos().x;
	// �v���C���[���߂Â�����ːi����
	if(kDis <= 300.0f && kDis > -0.0f) // �v���C���[��������߂Â����ꍇ
	{
		m_animation = kRun;
		m_dir = kDirLeft;
		m_vec.x = -kSpeedX;
	}
	if (kDis >= -300.0f && kDis < 0.0f)	// �v���C���[���E����߂Â����ꍇ
	{
		m_animation = kRun;
		m_dir = kDirRight;
		m_vec.x = kSpeedX;
	}
	if(fabsf(kDis) > 300.0f)
	{
		m_animation = kIdle;
		m_vec.x = 0.0f;
	}

	/*�A�j���[�V����*/
	UpdateAnim();
}

void EnemyBear::Draw()
{
	// �������W��������W�ɕϊ�
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// �_���[�W���o
	// 10�t���[���Ԋu�ŕ\����\����؂�ւ���
	if (m_damageFrame % 10 >= 5) return;

	// �F�\��
	DrawBear(x, y);

	// ���Ŏ��_���[�W�G�t�F�N�g�\��
	if (m_isDead)
	{
		// �摜�̐؂�o�����W
		int effectFrame = m_damageFrame / kEffectFrameNum;
		int effectSrcX = kDamageUseFrame[effectFrame] * kEffectWidth;
		int effectSrcY = 0;
		if (m_damageFrame > 0)
		{
			DrawRectRotaGraph(x - 10, y, effectSrcX, effectSrcY, kEffectWidth, kEffectHeight, kEffectScale, 0.0f, m_damageEffect, true);
		}
	}

#ifdef _DEBUG
	// �X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �����蔻��̕\��
	m_colRect.Draw(0x00ff00, false);
#endif
}

/// <summary>
/// �G�o��
/// </summary>
/// <param name="posX">���ݒn</param>
/// <param name="posY">���ݒn</param>
/// <param name="moveRangeX">�ړ���</param>
void EnemyBear::Start(float posX, float posY, float moveRangeX)
{
	// �G�L�����N�^�[��o�ꂳ����
	m_isExist = true;

	m_pos = { posX, posY };
	m_startPos = { posX, posY };
	m_vec = {kSpeedX, kSpeedY};
	m_moveRangeX = moveRangeX;
}

/// <summary>
/// �}�b�v�`�b�v�Ƃ̓����蔻��
/// </summary>
/// <param name="chipRect"></param>
void EnemyBear::HitCollision(Rect chipRect)
{
	// �����瓖���������`�F�b�N����
	m_pos.x += m_vec.x;	// ���݈ʒu�̍X�V
	m_colRect.SetCenter(m_pos.x , m_pos.y, kColWidth, kColHeight); // �����蔻��𐶐�
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.x > 0.0f) // �E�Ɉړ���
		{
			m_pos.x = chipRect.GetLeft() - kColWidth - 1.0f;
			m_vec.x *= -1;
			m_dir = kDirLeft;

		}
		else if (m_vec.x < 0.0f) // ���Ɉړ���
		{
			m_pos.x = chipRect.GetRight() + kColWidth + 1.0f;
			m_vec.x *= -1;
			m_dir = kDirRight;
		}
	}

	// �c���瓖���������`�F�b�N����
	m_pos.y += m_vec.y; 	// ���݈ʒu�̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y , kColWidth, kColHeight); // �����蔻��𐶐�
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kColHeight + 30.0f - 1.0f;
		}
	}
}

/// <summary>
/// �_���[�W��
/// </summary>
void EnemyBear::OnDamage()
{
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0) return;
	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

	// ���݂�HP�����炷
	if (m_pPlayer->IsMiddleFire())
	{
		m_hp -= 3;
	}
	else if (m_pPlayer->IsBigFire())
	{
		m_hp -= 5;
	}
	else
	{
		m_hp--;
	}

	// SE��炷
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_BACK, true);

	// HP��0�ȉ��ɂȂ����瑶�݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;
		m_isDead = true;
	}
}

/// <summary>
/// �A�j���[�V�����̏���
/// </summary>
void EnemyBear::UpdateAnim()
{
	// �ړ��A�j���[�V����
	m_idleAnimFrame++;
	if (m_idleAnimFrame >= kIdleAnimFrameCycle)
	{
		m_idleAnimFrame = 0;
	}
	// �ːi�A�j���[�V����
	m_runAnimFrame++;
	if (m_runAnimFrame >= kRunAnimFrameCycle)
	{
		m_runAnimFrame = 0;
	}
	// �񕜃A�j���[�V����
	m_idleAnimFrame++;
	if (m_recoveryAnimFrame >= kRecAnimFrameCycle)
	{
		m_recoveryAnimFrame = 0;
	}
	// �_���[�W�G�t�F�N�g
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}
}

/// <summary>
/// �F�̕`��
/// </summary>
void EnemyBear::DrawBear(int x, int y)
{
	// �摜�̐؂�o�����W
	// �ҋ@���
	int idleAnimFrame = m_idleAnimFrame / kIdleAnimFrameNum;
	int idleSrcX = kIdleUseFrame[idleAnimFrame] * kWidth;
	int idleSrcY = kHeight * m_dir;
	// �ːi���
	int runAnimFrame = m_runAnimFrame / kRunAnimFrameNum;
	int runSrcX = kRunUseFrame[runAnimFrame] * kWidth;
	int runSrcY = kHeight * (2 + m_dir);
	// �񕜏��
	int recAnimFrame = m_recoveryAnimFrame / kRecAnimFrameNum;
	int recSrcX = kRecUseFrame[recAnimFrame] * kWidth;
	int recSrcY = kHeight * (4 + m_dir);

	// �ҋ@���
	if (m_animation == Anim::kIdle)
	{
		DrawRectRotaGraph(x, y - 80, idleSrcX, idleSrcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);
	}
	// �ːi���
	else if (m_animation == Anim::kRun)
	{
		DrawRectRotaGraph(x, y - 80, runSrcX, runSrcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);
	}
	// �񕜏��
	else if (m_animation == Anim::kRecovery)
	{
		DrawRectRotaGraph(x, y - 80, recSrcX, recSrcY, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);
	}

}