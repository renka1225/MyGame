#include "SceneResult.h"
#include "SceneTitle.h"
#include "ManagerFont.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Input.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneResult::SceneResult()
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneResult::~SceneResult()
{
}


/// <summary>
/// ������
/// </summary>
void SceneResult::Init(std::shared_ptr<ManagerResult> pResult)
{
	m_pResult = pResult;
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">�{�^������</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> SceneResult::Update(Input& input)
{
	if (input.IsTriggered("sceneChange"))
	{
		return std::make_shared<SceneTitle>();		//�^�C�g����ʂɈړ�
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneResult::Draw()
{
#ifdef _DEBUG
	// MEMO:�f�o�b�O�\��
	DrawString(0, 0, "���ʊm�F���", 0xffffff);
#endif

	DrawRanking();	// �����L���O�\��
}


/// <summary>
/// �����L���O�\��
/// </summary>
void SceneResult::DrawRanking()
{
	for (int i = 0; i < kDisplayRanking; i++)
	{
		auto ranking = m_pResult->GetRanking(); // �����L���O���擾
		m_pConversionTime->Change(ranking[i]);  // �^�C���ϊ�
		DrawFormatStringToHandle(kTimePosX, kTimePosY + kIntervalY * i, 0xffffff, m_pFont->GetResultTimeFont(),
			"%02d��:%02d:%03d\n", (i + 1), m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
	}
}