#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "Bg.h"
#include "SceneStage1.h"
#include "ShotBuster.h"
#include "ShotMetal.h"
#include "ShotFire.h"
#include "ShotLineMove.h"
#include "RecoveryBase.h"
#include <cassert>

// Player�Ŏg�p����萔
namespace
{
	// �ړ����x
	constexpr float kSpeed = 8.0f;
	// �d��
	constexpr float kGravity = 0.5f;
	// �����x
	constexpr float kVelocity = -12.5f;

	// �v���C���[�̏����ʒu
	constexpr float kPosX = 350.0f;
	constexpr float kPosY = 450.0f;

	// �v���C���[�̍ő�HP
	constexpr int kMaxHp = 10;
	// �ő�e�G�l���M�[
	constexpr float kMaxShot = 10;
	// ���^���̍ő�G�l���M�[
	constexpr float kMaxMetalShot = 5;
	// �c�@
	constexpr int kLife = 3;

	// �A�C�e���̉񕜗�
	constexpr float kSmallRecovery = 2;	// ���A�C�e��
	constexpr float kGreatRecovery = 5;	// ��A�C�e��

	// �A�C�e��2���̃T�C�Y
	constexpr int kShotWidth = 52;

	// �}�b�v�`�b�v�̃T�C�Y
	constexpr int kMapWidth = 32;
	constexpr int kMapHeight = 32;

	// �v���C���[�̃T�C�Y
	constexpr float kScale = 0.3f;
	constexpr int kPlayerWidth = 200;
	constexpr int kPlayerHeight = 296;

	// �v���C���[�̓����蔻��̃T�C�Y
	constexpr int kPlayerColX = kPlayerWidth * kScale - 40;
	constexpr int kPlayerColY = kPlayerHeight * kScale;

	// �L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0, 1, 2, 1 };
	// �ҋ@�A�j���[�V����1�R�}�̃t���[����
	constexpr int kIdleAnimFrameNum = 32;
	// �ҋ@�A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kIdleAnimFrameCycle = _countof(kUseFrame) * kIdleAnimFrameNum;
	// �ړ��A�j���[�V����1�R�}�̃t���[����
	constexpr int kWalkAnimFrameNum = 8;
	// �ړ��A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kWalkAnimFrameCycle = _countof(kUseFrame) * kWalkAnimFrameNum;
	// �V���b�g�̃A�j���[�V�����\������
	constexpr int kShotAnimFrame = 30;
	// �_���[�W�̃A�j���[�V�����\������
	constexpr int kDamageAnimFrame = 5;

	// �_���[�W���o�̃t���[����
	constexpr int kDamageFrame = 60;
}


Player::Player() :
	m_pStage1(nullptr),
	m_pBg(nullptr),
	m_pos(kPosX, kPosY),
	m_move(0.0f, 0.0f),
	m_isRight(true),
	m_isGround(false),
	m_isJump(false),
	m_jumpFrame(0),
	m_hp(kMaxHp),
	m_life(kLife),
	m_fullHpRecovery(0),
	m_damageFrame(0),
	m_metalEnergy(kMaxMetalShot),
	m_fireEnergy(kMaxShot),
	m_lineEnergy(kMaxShot),
	m_isBuster(false),
	m_isMetal(false),
	m_isFire(false),
	m_isLineMove(false),
	m_keyState(0),
	m_pressTime(0),
	m_nowPressTime(0),
	m_isSmallFire(false),
	m_isMiddleFire(false),
	m_isBigFire(false),
	m_lineTime(60),
	m_animation(Anim::kIdle),
	m_idleAnimFrame(0),
	m_walkAnimFrame(0),
	m_shotAnimFrame(0),
	m_damageAnimFrame(0)
{
	// �摜�ǂݍ���
	m_idleHandle = LoadGraph("data/image/Player/idle.png");
	m_walkHandle = LoadGraph("data/image/Player/walk.png");
	m_shotHandle = LoadGraph("data/image/Player/shot.png");
	m_jumpHandle = LoadGraph("data/image/Player/jump.png");
	m_damageHandle = LoadGraph("data/image/Player/damage.png");

	// ���ǂݍ���
	m_shotSE = LoadSoundMem("data/sound/SE/shot.mp3");
	m_shotFireSE = LoadSoundMem("data/sound/SE/shotFire.wav");
	m_jumpSE = LoadSoundMem("data/sound/SE/jump.mp3");
	m_damageSE = LoadSoundMem("data/sound/SE/playerDamage.wav");
	m_deadSE = LoadSoundMem("data/sound/SE/playerDead.wav");
}

Player::~Player()
{
	DeleteGraph(m_idleHandle);
	DeleteGraph(m_walkHandle);
	DeleteGraph(m_shotHandle);
	DeleteGraph(m_jumpHandle);
	DeleteGraph(m_damageHandle);
	DeleteSoundMem(m_shotSE);
	DeleteSoundMem(m_shotFireSE);
	DeleteSoundMem(m_damageSE);
	DeleteSoundMem(m_deadSE);
}

/*����������*/
void Player::Init()
{
	// ���݈ʒu
	m_pos.x = kPosX;
	m_pos.y = kPosY;
	// ����
	m_isRight = true;
	// �W�����v�t���O
	m_isGround = false;
	m_isJump = false;
	// �����x
	m_move.y = 0.0f;
	// �_���[�W�̃t���[����
	m_damageFrame = 0;
	// �J�n���̓o�X�^�[��łĂ�悤�ɂ���
	m_isBuster = true;
	m_isMetal = false;
	m_isFire = false;
	m_isLineMove = false;
	// �t�@�C�A�̏��
	m_isSmallFire = false;
	m_isMiddleFire = false;
	m_isBigFire = false;
	// �A�C�e��2���̑ҋ@����
	m_lineTime = 60;
	// �ҋ@��Ԃɂ���
	m_animation = Anim::kIdle;
	m_idleAnimFrame = 0;
	m_walkAnimFrame = 0;
	m_shotAnimFrame = 0;
	m_damageFrame = 0;

	// �ăv���C��
	if (m_life < 0 || m_pStage1->IsSceneClear() || m_pStage1->IsSceneTitle() || m_pStage1->IsSceneEnd())
	{
		// HP
		m_hp = kMaxHp;
		// �e�G�l���M�[
		m_metalEnergy = kMaxMetalShot;
		m_fireEnergy = kMaxShot;
		m_lineEnergy = kMaxShot;
		// �c�@��
		m_life = kLife;
		// E�ʐ�
		m_fullHpRecovery = 0;
	}
}

/*�v���C���[�̍X�V*/
void Player::Update()
{
	// �p�b�h���g�p����
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*������������E�Ɉړ�*/
	if (pad & PAD_INPUT_RIGHT)
	{
		m_isRight = true;
		m_move.x = kSpeed;
		m_animation = Anim::kWalk;
	}
	/*�����������獶�Ɉړ�*/
	else if (pad & PAD_INPUT_LEFT)
	{
		m_isRight = false;
		m_move.x = -kSpeed;
		m_animation = Anim::kWalk;
	}
	else
	{
		m_move.x = 0;
		m_animation = Anim::kIdle;
	}

	/*�v���C���[�����ɗ��������ꍇ*/
	if ((m_pos.y - kPlayerHeight * 0.5f) > Stage::kMapHeight)
	{
		// HP��0�ɂ���
		m_hp -= kMaxHp;
		if (m_hp <= 0)
		{
			m_hp = 0;
		}
		StopSoundMem(m_shotFireSE);
	}

	/*HP��0�ȉ��ɂȂ�����c�@��1���炷*/
	if (m_hp <= 0)
	{
		// �c�@�����邲�Ƃ�SE��炷
		PlaySoundMem(m_deadSE, DX_PLAYTYPE_NORMAL, true);

		// �c�@��0�ȏゾ�����珉��������
		if (m_life >= 0)
		{
			Init();
		}

		m_life--;
		m_hp = kMaxHp;	// HP�S��
	}

	/*�n�ʂɐڂ��Ă���*/
	if (m_isGround)
	{
		m_jumpFrame = 0;
		m_isJump = false;

		/*Z�L�[orA�{�^���ŃW�����v*/
		if (Pad::IsTrigger(PAD_INPUT_A))
		{
			m_isGround = false;
			m_isJump = true;
			m_move.y = kVelocity;

			// �W�����vSE��炷
			PlaySoundMem(m_jumpSE, DX_PLAYTYPE_BACK, true);
		}

		/*�}�b�v�`�b�v�Ƃ̓����蔻��*/
		Rect chipRect; // ���������}�b�v�`�b�v�̋�`
		CheckHitMap(chipRect);
		// ���Ȃǂɗ����Ă���Ƃ��������ɂ�����
		if(!(m_pBg->IsCollision(m_colRect, chipRect)))
		{
			m_isGround = false;
		}
	}
	/*�n�ʂɐڒn���Ă��Ȃ�*/
	else
	{
		// �W�����v��Ԃɂ���
		m_animation = Anim::kJump;

		if (m_isJump)
		{
			m_jumpFrame++;	// �W�����v�t���[���̍X�V

			//�{�^���𗣂����u�ԂɃW�����v����
			if (Pad::IsRelease(PAD_INPUT_B))
			{
				// �W�����v�̍��������߂�
				float jumpHeight;

				if (m_jumpFrame < 10) // ����������10�t���[���ȉ�
				{
					jumpHeight = 0.5f;
				}
				else if (m_jumpFrame < 30) // 30�t���[���ȉ�
				{
					jumpHeight = 0.8f;
				}
				else	// 30�t���[���ȏ�
				{
					jumpHeight = 1.0f;
				}
				m_move.y *= jumpHeight;
			}
		}
		m_move.y += kGravity; // �����x�ɏd�͂𑫂�

		/*�}�b�v�`�b�v�Ƃ̓����蔻��*/
		Rect chipRect; // ���������}�b�v�`�b�v�̋�`
		CheckHitMap(chipRect);
	}

#ifdef  _DEBUG
	// MEMO:�ړ��ʊm�F
	// printfDx("moveY:(%f)\n", m_move.y);
#endif

	/*�o�X�^�[����*/
	if (m_isBuster)
	{
		if (Pad::IsTrigger(PAD_INPUT_B))
		{
			m_animation = Anim::kShot;
			m_shotAnimFrame = kShotAnimFrame;

			ShotBuster* pShot = new ShotBuster;
			// �V�����e�𐶐�����
			pShot->Init();
			pShot->SetMain(m_pStage1);
			pShot->SetPlayer(this);
			pShot->Start(m_pos);
			// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
			m_pStage1->AddShot(pShot);

			// �e���˂�SE��炷
			PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);
		}
	}

	/*���^������*/
	if (m_isMetal)
	{
		if (Pad::IsTrigger(PAD_INPUT_B))
		{
			m_animation = Anim::kShot;
			m_shotAnimFrame = kShotAnimFrame;

			if (m_metalEnergy > 0)
			{
				ShotMetal* pShot = new ShotMetal;
				// �V�����e�𐶐�����
				pShot->Init();
				pShot->SetMain(m_pStage1);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
				m_pStage1->AddShot(pShot);

				// �e���˂�SE��炷
				PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);

				if (pShot->IsExist())
				{
					// �e�G�l���M�[��0.25���炷
					m_metalEnergy -= 0.25f;
				}
			}
			else
			{
				m_metalEnergy = 0;
			}
		}
	}

	/*�t�@�C���[����*/
	if (m_isFire)
	{
		// �L�[�������ꂽ�u�Ԃ��擾
		if (Pad::IsTrigger(PAD_INPUT_B))
		{
			m_pressTime = GetNowCount();
		}
		// �L�[��������Ă��邩����
		if (Pad::IsPress(PAD_INPUT_B))
		{
			m_animation = Anim::kShot;
			m_shotAnimFrame = kShotAnimFrame;

			if (m_fireEnergy >= 0)
			{
				// ��������SE�𗬂�
				if (CheckSoundMem(m_shotFireSE) == 0)
				{
					PlaySoundMem(m_shotFireSE, DX_PLAYTYPE_LOOP, true);
				}
			}

			m_nowPressTime = GetNowCount() - m_pressTime; // �{�^���������ė����܂ł̎���
		}
		// �L�[�������ꂽ�u�Ԃ𔻒�
		if (Pad::IsRelease(PAD_INPUT_B))
		{
			// SE��~
			StopSoundMem(m_shotFireSE);

			if (m_fireEnergy > 0) // �e�G�l���M�[��0�ȏ�
			{
				// �e���˂�SE��炷
				PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);

				if (m_nowPressTime < 2000) // ���������Ԃ�2�b�ȉ�
				{
					m_fireEnergy--; // �e�G�l���M�[��1���炷
					m_isSmallFire = true;
					m_isMiddleFire = false;
					m_isBigFire = false;
					
				}
				else if (m_nowPressTime < 5000) // ���������Ԃ�5�b�ȉ�
				{
					if (m_fireEnergy - 3 < 0) // �e�G�l���M�[������Ȃ��ꍇ
					{
						m_fireEnergy--; // �e�G�l���M�[��1���炷
						m_isSmallFire = true;
						m_isMiddleFire = false;
						m_isBigFire = false;
					}
					else
					{
						m_fireEnergy -= 3; // �e�G�l���M�[��3���炷
						m_isSmallFire = false;
						m_isMiddleFire = true;
						m_isBigFire = false;
					}
				}
				else // ���������Ԃ�5�b�ȏ�
				{
					if (m_fireEnergy - 5 < 0) // �e�G�l���M�[������Ȃ��ꍇ
					{
						m_fireEnergy--; // �e�G�l���M�[��1���炷
						m_isSmallFire = true;
						m_isMiddleFire = false;
						m_isBigFire = false;
					}
					else
					{
						m_fireEnergy -= 5; // �e�G�l���M�[��5���炷
						m_isSmallFire = false;
						m_isMiddleFire = false;
						m_isBigFire = true;
					}
				}

				// �V�����e�𐶐�����
				ShotFire* pShot = new ShotFire;
				pShot->Init();
				pShot->SetMain(m_pStage1);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
				m_pStage1->AddShot(pShot);
			}
			else // �e�G�l���M�[��0�ȉ�
			{
				m_fireEnergy = 0; // ���݂̒e�G�l���M�[��0�ɂ���
			}
		}
	}
	
	/*�A�C�e��2������*/
	if (m_isLineMove)
	{
		// �{�^�����������甭��
		if (Pad::IsTrigger(PAD_INPUT_B))
		{
			m_animation = Anim::kShot;
			m_shotAnimFrame = kShotAnimFrame;

			if (!m_pStage1->GetIsExistLineMove() && m_lineEnergy > 0)
			{
				ShotLineMove* pShot = new ShotLineMove;
				// �V�����e�𐶐�����
				pShot->Init();
				pShot->SetMain(m_pStage1);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
				m_pStage1->AddShot(pShot);

				// �e���˂�SE��炷
				PlaySoundMem(m_shotSE, DX_PLAYTYPE_BACK, true);

				m_lineTime = 60;
			}
		}

		// ��ʓ��ɂ���ꍇ
		if (m_pStage1->GetIsExistLineMove())
		{
			m_lineTime--;
			m_lineEnergy -= 0.03f; // �G�l���M�[�����炷
		}
	}

	/*�_���[�W���o*/
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}

	/*�A�j���[�V����*/
	//�ҋ@���
	if(m_animation == Anim::kIdle)
	{
		m_idleAnimFrame++;
		if (m_idleAnimFrame >= kIdleAnimFrameCycle)
		{
			m_idleAnimFrame = 0;
		}
	}
	//�ړ����
	else if (m_animation == Anim::kWalk)
	{
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kWalkAnimFrameCycle)
		{
			m_walkAnimFrame = 0;
		}
	}
	// �V���b�g
	m_shotAnimFrame--;
	if (m_shotAnimFrame < 0)
	{
		m_shotAnimFrame = 0;
	}

	// �_���[�W
	m_damageAnimFrame--;
	if (m_damageAnimFrame < 0)
	{
		m_damageAnimFrame = 0;
	}
}

void Player::Draw()
{
// �_���[�W���o
// 2�t���[���Ԋu�ŕ\����\����؂�ւ���
	if (m_damageFrame % 10 >= 8) return;

	// �v���C���[�̕`��
	DrawPlayer();

#ifdef _DEBUG
	// MEMO:�X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �����蔻��̕\��
	// m_colRect.Draw(0x0000ff, false);
#endif
}

/// <summary>
/// �v���C���[�̕`��
/// </summary>
void Player::DrawPlayer()
{
	// �X�N���[���ʂ𔽉f����
	int x = m_pos.x;
	int y = m_pos.y;
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	// �摜�؂�o���ʒu���v�Z
	// �ҋ@���
	int idleAnimFrame = m_idleAnimFrame / kIdleAnimFrameNum;
	int idleSrcX = kUseFrame[idleAnimFrame] * kPlayerWidth;
	int idleSrcY = kPlayerHeight;
	// �ړ����
	int walkAnimFrame = m_walkAnimFrame / kWalkAnimFrameNum;
	int walkSrcX = kUseFrame[walkAnimFrame] * kPlayerWidth;
	int walkSrcY = kPlayerHeight;

	if (m_isRight)
	{
		idleSrcY = kPlayerHeight * 0;
		walkSrcY = kPlayerHeight * 0;
	}
	else
	{
		idleSrcY = kPlayerHeight * 1;
		walkSrcY = kPlayerHeight * 1;
	}

	// �ҋ@���
	if (m_animation == Anim::kIdle && m_shotAnimFrame <= 0 && m_damageAnimFrame <= 0)
	{
		if (m_isRight) // �E�������Ă���ꍇ
		{
			DrawRectRotaGraph(x, y, idleSrcX, idleSrcY, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_idleHandle, true);
		}
		else
		{
			DrawRectRotaGraph(x, y, idleSrcX, idleSrcY, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_idleHandle, true);
		}
	}
	// �ړ����
	else if (m_animation == Anim::kWalk && m_shotAnimFrame <= 0 && m_damageAnimFrame <= 0)
	{
		if (m_isRight) // �E�������Ă���ꍇ
		{
			DrawRectRotaGraph(x, y, walkSrcX, walkSrcY, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_walkHandle, true);
		}
		else
		{
			DrawRectRotaGraph(x, y, walkSrcX, walkSrcY, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_walkHandle, true);
		}
	}
	// �e���ˏ��
	else if (m_animation == Anim::kShot || m_shotAnimFrame > 0 && m_damageAnimFrame <= 0)
	{
		if (m_isRight) // �E�������Ă���ꍇ
		{
			if (m_isGround) // �ڒn��
			{
				DrawRectRotaGraph(x, y, 0, 0, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_shotHandle, true);
			}
			else
			{
				DrawRectRotaGraph(x, y, kPlayerWidth, 0, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_shotHandle, true);
			}
		}
		else
		{
			if (m_isGround) // �ڒn��
			{
				DrawRectRotaGraph(x, y, 0, kPlayerHeight, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_shotHandle, true);
			}
			else
			{
				DrawRectRotaGraph(x, y, kPlayerWidth, kPlayerHeight, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_shotHandle, true);
			}
		}
	}
	// �W�����v���
	else if (m_animation == Anim::kJump && m_shotAnimFrame <= 0 && m_damageAnimFrame <= 0)
	{
		if (m_isRight) // �E�������Ă���ꍇ
		{
			DrawRectRotaGraph(x, y, 0, 0, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_jumpHandle, true);
		}
		else
		{
			DrawRectRotaGraph(x, y, 0, kPlayerHeight + 1, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_jumpHandle, true);
		}
	}
	// �_���[�W���
	else if (m_animation == Anim::kDamage && m_shotAnimFrame <= 0 && m_damageAnimFrame > 0)
	{
		if (m_isRight) // �E�������Ă���ꍇ
		{
			DrawRectRotaGraph(x, y, 0, 0, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_damageHandle, true);
		}
		else
		{
			DrawRectRotaGraph(x, y, 0, kPlayerHeight, kPlayerWidth, kPlayerHeight, kScale, 0.0f, m_damageHandle, true);
		}
	}
}

/// <summary>
/// �}�b�v�`�b�v�̓����蔻��
/// </summary>
/// <param name="chipRect"></param>
void Player::CheckHitMap(Rect chipRect)
{
	// �����瓖���������`�F�b�N����
	m_pos.x += m_move.x;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kPlayerColX), static_cast<float>(kPlayerColY));
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_move.x > 0.0f)
		{
			m_pos.x = chipRect.GetLeft() - kPlayerWidth * kScale * 0.5f + 15 - 1;
		}
		else if (m_move.x < 0.0f)
		{
			m_pos.x = chipRect.GetRight() + kPlayerWidth * kScale * 0.5f - 15 + 1;
		}
	}

	// �c���瓖���������`�F�b�N����
	m_pos.y += m_move.y;
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kPlayerColX), static_cast<float>(kPlayerColY));
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_move.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kPlayerHeight * kScale  * 0.5f - 1 ;
			m_isGround = true;
		}
		else if (m_move.y < 0.0f)
		{
			m_pos.y = chipRect.GetBottom() + kPlayerHeight * kScale * 0.5f + 1;
			m_move.y *= -1.0f;
		}
	}
}

/// <summary>
/// �e�̑I����Ԃ��X�V
/// </summary>
/// <param name="isBuster"></param>
/// <param name="isMetal"></param>
/// <param name="isFire"></param>
/// <param name="isLineMove"></param>
void Player::ChangeShot(bool isBuster, bool isMetal, bool isFire, bool isLineMove)
{
	// �o�X�^�[�̑I����Ԃ��X�V
	m_isBuster = isBuster;

	// ���^���̑I����Ԃ��X�V
	m_isMetal = isMetal;

	// �t�@�C�A�̑I����Ԃ��X�V
	m_isFire = isFire;

	// 2���̑I����Ԃ��X�V
	m_isLineMove = isLineMove;
}

/// <summary>
/// �v���C���[�̃_���[�W���o
/// </summary>
void Player::OnDamage()
{
	// �_���[�W���o���͖��G��ԂɂȂ�
	if (m_damageFrame > 0) return;

	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;
	m_damageAnimFrame = kDamageAnimFrame;
	m_animation = Anim::kDamage;

	// �_���[�WSE��炷
	PlaySoundMem(m_damageSE, DX_PLAYTYPE_BACK, true);

	// HP�����炷
	m_hp--;
	if (m_hp <= 0)
	{
		m_life--;		// �c�@��1���炷
		m_hp = kMaxHp;	// HP�S��
	}

	// TODO:�m�b�N�o�b�N
	/*m_pos.y -= 50;
	if (m_isRight)
	{
		m_pos.x -= 50;
	}
	else
	{
		m_pos.x += 50;
	}*/
}

/// <summary>
/// E�ʎ擾
/// </summary>
void Player::GetHpFullRecovery()
{
	m_fullHpRecovery += 1;
}

/// <summary>
/// ��
/// </summary>
void Player::HpSmallRecovery() // HP����
{
	m_hp += kSmallRecovery;
	if (m_hp > kMaxHp) // �ő�HP�𒴂����ꍇ
	{
		m_hp = kMaxHp;
	}
}

void Player::HpGreatRecovery() // HP���
{
	m_hp += kGreatRecovery;
	if (m_hp > kMaxHp) // �ő�HP�𒴂����ꍇ
	{
		m_hp = kMaxHp;
	}
}

void Player::ShotSmallRecovery() // �e����
{
	if (m_isMetal) // ���^��
	{
		m_metalEnergy += kSmallRecovery;
		if (m_metalEnergy > kMaxMetalShot)
		{
			m_metalEnergy = kMaxMetalShot;
		}
	}
	else if (m_isFire) // �t�@�C�A
	{
		m_fireEnergy += kSmallRecovery;
		if (m_fireEnergy > kMaxMetalShot)
		{
			m_fireEnergy = kMaxMetalShot;
		}
	}
	else if (m_isLineMove) // 2��
	{
		m_isLineMove += kSmallRecovery;
		if (m_isLineMove > kMaxShot)
		{
			m_isLineMove = kMaxShot;
		}
	}
}

void Player::ShotGreatRecovery() // �e���
{
	if (m_isMetal) // ���^��
	{
		m_metalEnergy += kGreatRecovery;
		if (m_metalEnergy > kMaxMetalShot)
		{
			m_metalEnergy = kMaxMetalShot;
		}
	}
	else if (m_isFire) // �t�@�C�A
	{
		m_fireEnergy += kGreatRecovery;
		if (m_fireEnergy > kMaxShot)
		{
			m_fireEnergy = kMaxShot;
		}
	}
	else if (m_isLineMove) // 2��
	{
		m_isLineMove += kSmallRecovery;
		if (m_isLineMove > kMaxShot)
		{
			m_isLineMove = kMaxShot;
		}
	}
}

void Player::LifeRecovery() // �c�@��
{
	m_life += 1;	// �c�@��1���₷
	if (m_life > 99)
	{
		m_life = 99;
	}
}

void Player::HpFullRecovery() // HP�S��
{
	if (m_fullHpRecovery > 0)
	{
		if (m_hp < kMaxHp) // ���݂�HP���ő�HP����
		{
			m_hp += kMaxHp;	// HP���ő�܂ŉ�
			if (m_hp > kMaxHp) // �ő�HP�𒴂����ꍇ
			{
				m_hp = kMaxHp;
			}
			m_fullHpRecovery--; // ��������1���炷
		}
	}
	else
	{
		m_fullHpRecovery = 0;
	}
}

/// <summary>
/// �A�C�e��2���ɏ�����ۂ̏���
/// </summary>
/// <param name="shotRect">�A�C�e��2���̓����蔻��</param>
void Player::RideLineMove(Rect shotRect)
{
 	Rect lineMoveRect = shotRect; // �A�C�e��2���̓����蔻��

	// �����蔻��X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kPlayerColX), static_cast<float>(kPlayerColY));

	// �A�C�e��2���ɏ�����ꍇ
	if (m_colRect.IsCollision(lineMoveRect))
	{
		if (m_lineTime <= 0)
		{
			if (m_isRight)
			{
				m_pos.x += 10.0f;
			}
			else
			{
				m_pos.x -= 10.0f;
			}
		}
		m_pos.y = lineMoveRect.GetTop() - kPlayerHeight * kScale * 0.5f;
		m_isGround = true;
		m_animation = Anim::kIdle;
	}
}