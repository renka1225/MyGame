#include "DxLib.h"
#include "Game.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Font.h"
#include "Input.h"

// �萔
namespace
{
	// UI�\���֘A
	constexpr int kTitleLogoPosX = 510;		// �^�C�g�����S�ʒuX
	constexpr int kTitleLogoPosY = 130;		// �^�C�g�����S�ʒuY
	constexpr int kSelectMove = 200;		// �I��\���̈ړ���
	constexpr int kFramePosX = 1250;		// �g�\���ʒuX
	constexpr int kFramePosY = 550;			// �g�\���ʒuY
	constexpr float kFrameAnim = 0.05f;		// �g�̊g��k���A�j���[�V�����Đ�����
	constexpr float kFrameScale = 1.0f;		// ���̘g�̃T�C�Y
	constexpr float kFrameChange = 0.1f;	// �g�̃T�C�Y�̕ω���
	
	// �e�L�X�g�֘A
	constexpr int kTextColor = 0x000000;	// �e�L�X�g�̐F
	constexpr int kStartPosX = 1350;		// �X�^�[�g�\���ʒuX
	constexpr int kStartPosY = 590;			// �X�^�[�g�\���ʒuY
	constexpr int kEndPosX = 1350;			// �Q�[���I���\���ʒuX
	constexpr int kEndPosY = 780;			// �Q�[���I���\���ʒuY

	// �X�e�[�W���f��
	constexpr float kScale = 0.1f;						// �g�嗦
	constexpr float kRotate = 1.0f;						// 3D���f���̉�]��
	const VECTOR kStagePos = VGet(0.0f,0.0f, 0.0f);		// �����ʒu
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle() :
	m_select(Select::kStart),
	m_stageRotate(0.0f),
	m_frameAnimTime(0.0f)
{
	m_titleHandle = LoadGraph("data/UI/titleLogo.png");
	m_frameHandle = LoadGraph("data/UI/frame.png");
	m_stageHandle = MV1LoadModel("data/Model/stage.mv1");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_stageHandle);
}


/// <summary>
/// ������
/// </summary>
void SceneTitle::Init()
{
	// �X�e�[�W���f���̒���
	MV1SetPosition(m_stageHandle, kStagePos);
	MV1SetScale(m_stageHandle, VGet(kScale, kScale, kScale));
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃N���X</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	// �X�e�[�W����]������
	MV1SetPosition(m_stageHandle, kStagePos);
	MV1SetScale(m_stageHandle, VGet(kScale, kScale, kScale));
	m_stageRotate += kRotate;
	MV1SetRotationXYZ(m_stageHandle, VGet(0.0f, m_stageRotate * DX_PI_F / 360.0f, 0.0f));

	m_frameAnimTime += kFrameAnim;

	// �I����Ԃ��X�V
	UpdateSelect(input);

	// �V�[���؂�ւ�
	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kStart)
		{
			return std::make_shared<ScenePlaying>(); // �Q�[���V�[���Ɉړ�
		}
		else if (m_select == Select::kEnd)
		{
			DxLib_End(); // �Q�[���I��
		}
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneTitle::Draw()
{
	// �w�i�\��
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x2d6676, true);

	// �X�e�[�W�\��
	MV1DrawModel(m_stageHandle);

	// �^�C�g���\��
	DrawGraph(kTitleLogoPosX, kTitleLogoPosY, m_titleHandle, true);

	// �g�\��
	for (int i = 0; i < kSelectNum; i++)
	{
		// �I�𒆂̃{�^�����g��k��������
		if (m_select == i)
		{
			// �g�̃T�C�Y��1.0�`1.1�ŕω�������
			float scale = kFrameScale + kFrameChange * sin(m_frameAnimTime);

			int width, height;
			int size = GetGraphSize(m_frameHandle, &width, &height);
			int scaleWidth = static_cast<int>(width * scale);
			int scaleHeight = static_cast<int>(height * scale);

			DrawExtendGraph(
				kFramePosX - static_cast<int>((scaleWidth - width) * 0.5f),
				kFramePosY + kSelectMove * i - static_cast<int>((scaleHeight - height) * 0.5f),
				kFramePosX + static_cast<int>((scaleWidth - width) * 0.5f) + width,
				kFramePosY + static_cast<int>(kSelectMove * i + (scaleHeight - height) * 0.5f) + height,
				m_frameHandle, true);
		}
		else
		{
			DrawGraph(kFramePosX, kFramePosY + kSelectMove * i, m_frameHandle, true);
		}
	}

	// �����\��
	DrawFormatStringToHandle(kStartPosX, kStartPosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kTitleMenu)], "START");
	DrawFormatStringToHandle(kEndPosX, kEndPosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kTitleMenu)], "END");

#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
	// ���S��
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xfffff);
#endif
}


/// <summary>
/// �I����Ԃ��X�V����
/// </summary>
/// <param name="input">���͏��</param>
void SceneTitle::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1���ɂ���
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// �I����Ԃ�1��ɂ���
	}
}
