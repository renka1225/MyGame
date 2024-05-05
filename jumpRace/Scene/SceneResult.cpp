#include "SceneResult.h"
#include "SceneTitle.h"
#include "ManagerFont.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneResult::SceneResult()
{
	m_fadeAlpha = kStartFadeAlpha;
	m_rankingTextHandle = LoadGraph("data/UI/ranking.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneResult::~SceneResult()
{
	DeleteGraph(m_rankingTextHandle);
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
	FadeOut();	// �t�F�[�h�A�E�g

	if (input.IsTriggered("back"))
	{
		FadeIn();	// �t�F�[�h�C��
		return std::make_shared<SceneTitle>();		//�^�C�g����ʂɈړ�
	}

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneResult::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x456889, true);	// �w�i�\��
	DrawGraph(kRankingTextPosX, kRankingTextPosY, m_rankingTextHandle, true);		// �����L���O�̕����\��
	DrawRectRotaGraph(kButtonPosX, kButtonPosY, kButtonSize, kButtonSize, kButtonSize, kButtonSize, kButtonScale, 0.0f, m_buttonHandle, true);	// �{�^���摜�\��
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffffff, m_pFont->GetTextFont(), "�ł��ǂ�");	// �����\��

	DrawRanking();	// �����L���O�\��

	DrawFade();		// �t�F�[�h

#ifdef _DEBUG
	// MEMO:�f�o�b�O�\��
	DrawString(0, 0, "�����L���O���", 0xffffff);
	// ���S��
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xfffff);
#endif
}


/// <summary>
/// �����L���O�\��
/// </summary>
void SceneResult::DrawRanking()
{
	for (int i = 0; i < kDisplayRanking; i++)
	{
		auto ranking = m_pResult->GetRanking()[i]; // �����L���O���擾
		m_pConversionTime->Change(ranking);		   // �^�C���ϊ�
		if (i < 5)
		{
			DrawFormatStringToHandle(kRankPosX, kRankPosY + kIntervalY * i, 0xffffff, m_pFont->GetResultTimeFont(),
				"%02d��:%02d:%03d\n", (i + 1), m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
		}
		else
		{
			DrawFormatStringToHandle(kRank2PosX, kRankPosY + kIntervalY * (i % 5), 0xffffff, m_pFont->GetResultTimeFont(),
				"%02d��:%02d:%03d\n", (i + 1), m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
		}
	}
}