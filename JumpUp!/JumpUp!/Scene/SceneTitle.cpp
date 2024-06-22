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
	constexpr int kTitleLogoPosY = 150;		// �^�C�g�����S�ʒuY
	constexpr int kFramePosX = 760;			// �g�\���ʒuX
	constexpr int kFramePosY = 550;			// �g�\���ʒuY
	constexpr int kSelectMove = 200;		// �I��\���̈ړ���
	
	// �e�L�X�g�֘A
	constexpr int kTextColor = 0x000000;	// �e�L�X�g�̐F
	constexpr int kStartPosX = 800;			// �X�^�[�g�\���ʒuX
	constexpr int kStartPosY = 600;			// �X�^�[�g�\���ʒuY
	constexpr int kEndPosX = 1000;			// �Q�[���I���\���ʒuX
	constexpr int kEndPosY = 900;			// �Q�[���I���\���ʒuY

	// �X�e�[�W���f��
	constexpr float kScale = 0.1f;							// �g�嗦
	constexpr float kRotate = 1.0f;							// 3D���f���̉�]��
	const VECTOR kStagePos = VGet(1000.0f, 100.0f, 0.0f);	// �����ʒu
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle() :
	m_select(Select::kStart),
	m_stageRotate(0.0f)
{
	m_titleHandle = LoadGraph("data/UI/titleLogo.png");
	m_frameHandle = LoadGraph("data/UI/frame.png");
	m_selectFrameHandle = LoadGraph("data/UI/selectFrame.png");
	m_stageHandle = MV1LoadModel("data/Model/stage.mv1");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_selectFrameHandle);
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
	m_stageRotate += kRotate;
	MV1SetRotationXYZ(m_stageHandle, VGet(0.0f, m_stageRotate * DX_PI_F / 360.0f, 0.0f));

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
		// �I����Ԃɂ���Ęg�̉摜��ύX����
		int displayHandle = -1;
		if (m_select == i)
		{
			displayHandle = m_selectFrameHandle;
		}
		else
		{
			displayHandle = m_frameHandle;
		}
		DrawGraph(kFramePosX, kFramePosY + kSelectMove * i, displayHandle, true);
	}

	// �����\��
	DrawFormatStringToHandle(kStartPosX, kStartPosY,
		kTextColor, static_cast<int>(Font::FontId::kSize32_4), "START");
	DrawFormatStringToHandle(kEndPosX, kEndPosY,
		kTextColor, static_cast<int>(Font::FontId::kSize32_4), "END");
	//DrawString(kStartPosX, kStartPosY, "Start\n", kTextColor);
	//DrawString(kEndPosX, kEndPosY, "End\n", kTextColor);

#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
	// ���S��
	DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xfffff);
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
		m_select = (m_select + 1) % kSelectNum;	// �I����Ԃ�1������
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// �I����Ԃ�1�グ��
	}
}
