#include "DxLib.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"

// �萔
namespace
{
	constexpr int kTitleLogoPosX = 350;	// �^�C�g�����S�ʒuX
	constexpr int kTitleLogoPosY = 100;	// �^�C�g�����S�ʒuY

	constexpr int kTextColor = 0xffffff; // �e�L�X�g�̐F
	constexpr int kStartPosX = 1000;	 // �X�^�[�g�\���ʒuX
	constexpr int kStartPosY = 700;		 // �X�^�[�g�\���ʒuY
	constexpr int kEndPosX = 1000;		 // �Q�[���I���\���ʒuX
	constexpr int kEndPosY = 900;		 // �Q�[���I���\���ʒuY

	constexpr int kSelectColor = 0xffffff;		// �I�𒆃J�[�\���̐F
	static constexpr int kNowSelectPosX = 900;	// �I�𒆕\���ʒuX
	static constexpr int kNowSelectPosY = 690;	// �I�𒆕\���ʒuY
	static constexpr int kNowSelectWidth = 210;	// �I�𒆕\���̉���
	static constexpr int kNowSelectHeight = 61;	// �I�𒆕\���̏c��
	static constexpr int kSelectMove = 80;		// �I��\���̈ړ���
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneTitle::SceneTitle() :
	m_select(Select::kStart)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneTitle::~SceneTitle()
{
}


/// <summary>
/// ������
/// </summary>
void SceneTitle::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃N���X</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
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
#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�^�C�g�����");
#endif

	// �I�𒆂̍��ڂɐF������
	int nowSelectPosY = kNowSelectPosY + kSelectMove * m_select;
	DrawBox(kNowSelectPosX, nowSelectPosY, kNowSelectPosX + kNowSelectWidth, nowSelectPosY + kNowSelectHeight,
		kSelectColor, true);

	// �I�����ڕ\��
	DrawString(kStartPosX, kStartPosY, "Start\n", kTextColor);
	DrawString(kEndPosX, kEndPosY, "End\n", kTextColor);
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
		m_select = (m_select - 1) % 1;	// �I����Ԃ�1�グ��
	}
}
