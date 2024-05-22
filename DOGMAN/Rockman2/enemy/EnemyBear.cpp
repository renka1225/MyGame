#include "EnemyBear.h"
#include "Bg.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	/*�F�̏��*/
	// �ړ����x
	constexpr float kSpeedX = 4.0f;
	constexpr float kSpeedY = 10.0f;
	// �ő�HP
	constexpr float kHp = 10.0f;

	// �_���[�W��
	constexpr int kMiddleDamage = 3; // ���_���[�W
	constexpr int kBigDamage = 5; // ��_���[�W
	// �񕜗�
	constexpr float kRecovery = 0.03f;
	// �񕜎���
	constexpr float kRecoveryFrame = 30.0f;
	// �񕜊Ԋu
	constexpr float kRecoveryIntervalFrame = 120.0f;

	// �G�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
	// �g�嗦
	constexpr float kEnlarge = 8.0f;
	
	// �����蔻��̃T�C�Y
	constexpr float kColWidth = 20.0f * kEnlarge;
	constexpr float kColHeight = 12.0f * 5.0f;

	// �`��ʒu����
	constexpr int kDrawAdjustment = 80;
	// �����蔻��̈ʒu����
	constexpr float kColAdjustmentX = 1.0f;
	constexpr float kColAdjustmentY = 29.0f;

	// �ːi�ʒu
	constexpr float kRunMinPosX = 10.0f;
	constexpr float kRunMaxPosX = 430.0f;

	// �񕜈ʒu
	constexpr float kRecoveryMinPosX = 430.0f;
	constexpr float kRecoveryMaxPosX = 1000.0f;
	constexpr float kRecoveryPosY = 100.0f;


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
	constexpr int kRunAnimFrameNum = 36;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kRunAnimFrameCycle = _countof(kRunUseFrame) * kRunAnimFrameNum;

	/*�񕜃A�j���[�V����*/
	// �A�j���[�V����
	constexpr int kRecUseFrame[] = { 0, 1, 2, 3, 4, 5};
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kRecAnimFrameNum = 40;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kRecAnimFrameCycle = _countof(kRecUseFrame) * kRecAnimFrameNum;

	/*�G�t�F�N�g*/
	// ��
	// �G�t�F�N�g�̃T�C�Y
	constexpr int kRecEffectSize = 256;
	// �G�t�F�N�g�̕\���t���[��
	constexpr int kRecEffectFrame = 30;
	// �G�t�F�N�g�̐�
	constexpr int kRecEffectNum = 35;

	// �_���[�W
	constexpr int kDamageUseFrame[] = { 0, 1, 2, 3 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kEffectFrameNum = 32;
	// �_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;

	// ���S
	// �G�t�F�N�g�̃T�C�Y
	constexpr int kEffectWidth = 32;
	constexpr int kEffectHeight = 32;
	constexpr float kEffectScale = 5.0f;

	// �G�t�F�N�g�̕\���ʒu����
	constexpr int kEffectAdjustmentX = 10;
	constexpr int kEffectAdjustmentY = 50;

	// SE��炷�ʒu
	constexpr float kSoundSE = 6048.0f;
}


EnemyBear::EnemyBear() :
	m_recoveryFrame(kRecoveryFrame),
	m_recoveryIntervalFrame(kRecoveryIntervalFrame),
	m_recoveryEffectFrame(0),
	m_animation(kIdle),
	m_idleAnimFrame(0),
	m_runAnimFrame(0),
	m_recoveryAnimFrame(0)
{
	m_handle = LoadGraph("data/image/Enemy/bear.png");
	m_recoveryEffect = LoadGraph("data/image/Effect/recovery.png");
	m_recoverySE = LoadSoundMem("data/Sound/SE/recovery.mp3");
	assert(m_recoveryEffect);
}

EnemyBear::~EnemyBear()
{
	DeleteGraph(m_handle);
	DeleteGraph(m_recoveryEffect);
	DeleteSoundMem(m_recoverySE);
}

void EnemyBear::Init(Bg* pBg, Player* pPlayer)
{
	m_pBg = pBg;
	m_pPlayer = pPlayer;
	m_hp = kHp;
	m_isDead = false;
	m_dir = kDirLeft;
	m_recoveryFrame = kRecoveryFrame;
	m_recoveryIntervalFrame = kRecoveryIntervalFrame;
	m_recoveryEffectFrame = 0;
	m_animation = kIdle;
	m_idleAnimFrame = 0;
	m_runAnimFrame = 0;
	m_recoveryAnimFrame = 0;
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
	float kDisX = m_pos.x - m_pPlayer->GetPos().x;
	float kDisY = m_pos.y - m_pPlayer->GetPos().y;
	// �v���C���[���߂Â�����ːi����
	if(kDisX <= kRunMaxPosX && kDisX > kRunMinPosX) // �v���C���[��������߂Â����ꍇ
	{
		m_animation = kRun;
		m_dir = kDirLeft;
		m_vec.x = -kSpeedX;
	}
	else if (kDisX >= -kRunMaxPosX && kDisX < -kRunMinPosX)	// �v���C���[���E����߂Â����ꍇ
	{
		m_animation = kRun;
		m_dir = kDirRight;
		m_vec.x = kSpeedX;
	}
	// �v���C���[�����ꂽ��񕜂���
	else if (fabsf(kDisX) > kRecoveryMinPosX && fabsf(kDisX) < kRecoveryMaxPosX || fabsf(kDisY) > kRecoveryPosY)
	{
		m_animation = kRecovery;
		m_vec.x = 0.0f;
		UpdateRecovery();
	}
	else
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
	int x = static_cast<int>(m_pos.x - kWidth * 0.5);
	int y = static_cast<int>(m_pos.y - kHeight * 0.5);

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// �_���[�W���o
	// 10�t���[���Ԋu�ŕ\����\����؂�ւ���
	if (m_damageFrame % 10 >= 5) return;

	// �F�\��
	DrawBear(x, y);

	// �G�t�F�N�g�\��
	DrawEffect(x, y);

#ifdef _DEBUG
	// �X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �����蔻��̕\��
	//m_colRect.Draw(0x00ff00, false);

	// MEMO:�F�̏��m�F
	//printfDx("�F��HP:%f\n", m_hp);
	//printfDx("�F�̃A�j���[�V����:%d\n", m_animation);
#endif // _DEBUG
}

/// <summary>
/// �G�o��
/// </summary>
/// <param name="posX">�����ʒuX���W</param>
/// <param name="posY">�����ʒuY���W</param>
/// <param name="moveRangeX">�ړ���</param>
void EnemyBear::Start(float posX, float posY, float moveRangeX)
{
	m_isExist = true;

	m_pos = { posX, posY };
	m_startPos = { posX, posY };
	m_vec = {kSpeedX, kSpeedY};
	m_moveRangeX = moveRangeX;
}


/// <summary>
/// �}�b�v�`�b�v�Ƃ̓����蔻��
/// </summary>
/// <param name="chipRect">�}�b�v�`�b�v�̓����蔻��</param>
void EnemyBear::HitCollision(Rect chipRect)
{
	// �����瓖���������`�F�b�N����
	m_pos.x += m_vec.x;
	m_colRect.SetCenter(m_pos.x , m_pos.y, kColWidth, kColHeight); // �����蔻��𐶐�
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.x > 0.0f) // �E�Ɉړ���
		{
			m_pos.x = chipRect.GetLeft() - kColWidth - kColAdjustmentX;
			m_vec.x *= -1;
			m_dir = kDirLeft;
			m_animation = kIdle;

		}
		else if (m_vec.x < 0.0f) // ���Ɉړ���
		{
			m_pos.x = chipRect.GetRight() + kColWidth + kColAdjustmentX;
			m_vec.x *= -1;
			m_dir = kDirRight;
			m_animation = kIdle;
		}
	}

	// �c���瓖���������`�F�b�N����
	m_pos.y += m_vec.y;
	m_colRect.SetCenter(m_pos.x, m_pos.y , kColWidth, kColHeight); // �����蔻��𐶐�
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kColHeight + kColAdjustmentY;
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
		m_hp -= kMiddleDamage;
	}
	else if (m_pPlayer->IsBigFire())
	{
		m_hp -= kBigDamage;
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
/// �񕜏���
/// </summary>
void EnemyBear::UpdateRecovery()
{
	m_recoveryIntervalFrame--;

	if (m_recoveryIntervalFrame < 0.0f)
	{
		m_recoveryFrame--;

		// �񕜂���
		if (m_recoveryFrame > 0.0f)
		{
			m_hp += kRecovery;
			if (m_hp >= kHp)
			{
				m_hp = kHp;
			}
			// �񕜃G�t�F�N�g
			m_recoveryEffectFrame += kRecEffectSize;
			if (m_recoveryEffectFrame >= kRecEffectSize * kRecEffectNum)
			{
				m_recoveryEffectFrame = 0;
			}
			//	��SE
			if (CheckSoundMem(m_recoverySE) == 0 && m_pPlayer->GetPos().x > kSoundSE)
			{
				PlaySoundMem(m_recoverySE, DX_PLAYTYPE_BACK, true);
			}
		}
		else
		{
			m_recoveryFrame = kRecoveryFrame;
			m_recoveryIntervalFrame = kRecoveryIntervalFrame;
			m_animation = kIdle;
		}
	}
}


/// <summary>
/// �A�j���[�V�����̏���
/// </summary>
void EnemyBear::UpdateAnim()
{
	// �ړ��A�j���[�V����
	m_idleAnimFrame++;
	if (m_idleAnimFrame >= kIdleAnimFrameCycle) m_idleAnimFrame = 0;
	
	// �ːi�A�j���[�V����
	m_runAnimFrame++;
	if (m_runAnimFrame >= kRunAnimFrameCycle) m_runAnimFrame = 0;
	
	// �񕜃A�j���[�V����
	m_recoveryAnimFrame++;
	if (m_recoveryAnimFrame >= kRecAnimFrameCycle) m_recoveryAnimFrame = 0;

	// �_���[�W�G�t�F�N�g
	m_damageFrame--;
	if (m_damageFrame < 0) 	m_damageFrame = 0;
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
		DrawRectRotaGraph(x, y - kDrawAdjustment,
			idleSrcX, idleSrcY, 
			kWidth, kHeight, 
			kEnlarge, 0.0f, 
			m_handle, true);
	}
	// �ːi���
	else if (m_animation == Anim::kRun)
	{
		DrawRectRotaGraph(x, y - kDrawAdjustment,
			runSrcX, runSrcY, 
			kWidth, kHeight, 
			kEnlarge, 0.0f, 
			m_handle, true);
	}
	// �񕜏��
	else if (m_animation == Anim::kRecovery)
	{
		DrawRectRotaGraph(x, y - kDrawAdjustment,
			recSrcX, recSrcY, 
			kWidth, kHeight, 
			kEnlarge, 0.0f, 
			m_handle, true);
	}

}


/// <summary>
/// �G�t�F�N�g�̕`��
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void EnemyBear::DrawEffect(int x, int y)
{
	// �񕜃G�t�F�N�g
	if (m_animation == kRecovery && m_recoveryFrame > 0.0f)
	{
		DrawRectRotaGraph(x , y - kEffectAdjustmentY,
			m_recoveryEffectFrame, 0, 
			kRecEffectSize, kRecEffectSize, 
			1.0f, 0.0f, 
			m_recoveryEffect, true);
	}

	// ���S�G�t�F�N�g
	if (m_isDead)
	{
		// �摜�̐؂�o�����W
		int effectFrame = m_damageFrame / kEffectFrameNum;
		int effectSrcX = kDamageUseFrame[effectFrame] * kEffectWidth;
		int effectSrcY = 0;
		if (m_damageFrame > 0)
		{
			DrawRectRotaGraph(x - kEffectAdjustmentX, y,
				effectSrcX, effectSrcY, 
				kEffectWidth, kEffectHeight, 
				kEffectScale, 0.0f,
				m_damageEffect, true);
		}
	}
}