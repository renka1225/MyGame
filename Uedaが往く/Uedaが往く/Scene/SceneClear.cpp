#include "DxLib.h"
#include "Input.h"
#include "Vec2.h"
#include "Game.h"
#include "Sound.h"
#include "Font.h"
#include "UI.h"
#include "Ranking.h"
#include "ConversionTime.h"
#include "SceneSelectStage.h"
#include "SceneClear.h"

// �萔
namespace
{
	const char* const kSyoriTextPath = "data/UI/syori.png";	// �����̃e�L�X�g�摜�̃t�@�C���ʒu
	const Vec2 kSyoriTextPos = { 650, 100 };				// �����̃e�L�X�g�摜�\���ʒu
	const Vec2 kTimeTextPos = { 600, 550 };					// ���ԕ\���ʒu
	const Vec2 kRankingTextPos = { 1250, 460 };				// "�����L���O"�\���ʒu
	constexpr float kTimeTextInterval = 100.0f;				// �e�L�X�g�\���Ԋu
	constexpr float kTotalTimeTextAdj = 350.0f;				// �e�L�X�g�\���ʒu����
	constexpr float kTimeTextAdj = 250.0f;					// �e�L�X�g�\���ʒu����
	constexpr int kTextColor = 0xffffff;					// �e�L�X�g�̐F
	constexpr int kTextColorRed = 0xb50d0d;					// �e�L�X�g�̐F(��)

	constexpr int kStartFadeAlpha = 255; // �X�^�[�g���̃t�F�[�h�l
	constexpr int kFadeFrame = 4;		 // �t�F�[�h�ω���
}


/// <summary>
/// �����t���R���X�g���N�^
/// </summary>
/// <param name="clearTime">�N���A�^�C��</param>
SceneClear::SceneClear(int stageKind, std::vector<int> clearTime):
	m_totalClearTime(0)
{
	m_fadeAlpha = kStartFadeAlpha;
	m_clearTime = clearTime;
	m_stageKind = stageKind;
	m_textHandle = LoadGraph(kSyoriTextPath);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneClear::~SceneClear()
{
	StopSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kClear)]);
	DeleteGraph(m_textHandle);
}


/// <summary>
/// ������
/// </summary>
/// <param name="stage">�N���A�����X�e�[�W</param>
void SceneClear::Init()
{
	// �g�[�^���̃N���A���Ԃ��v�Z����
	for (int i = 0; i < m_clearTime.size(); i++)
	{
		m_totalClearTime += m_clearTime[i];
	}

	// �����L���O�̍X�V�A�擾
	m_pRank->UpdateRanking(m_stageKind, m_totalClearTime);
	m_pRank->GetRanking(m_stageKind);
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns>�J�ڐ�</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	FadeOut(kFadeFrame); // �t�F�[�h�A�E�g

	// BGM��炷
	if (!CheckSoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kClear)]))
	{
		PlaySoundMem(Sound::m_bgmHandle[static_cast<int>(Sound::BgmKind::kClear)], DX_PLAYTYPE_LOOP);
	}

	if (input.IsTriggered("OK"))
	{
		FadeIn(kFadeFrame); // �t�F�[�h�C��
		return std::make_shared<SceneSelectStage>();
	}
	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneClear::Draw()
{
	// �w�i�\��
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xb3b3b3, true);

	// �����̕�����\��
	DrawGraphF(kSyoriTextPos.x, kSyoriTextPos.y, m_textHandle, true);

	// �g�[�^���^�C���\��
	int totalMin = Conversion::ChangeMin(m_totalClearTime);
	int totalSec = Conversion::ChangeSec(m_totalClearTime);
	int totalMilliSec = Conversion::ChangeMilliSec(m_totalClearTime);
	DrawStringToHandle(kTimeTextPos.x - kTotalTimeTextAdj, kTimeTextPos.y, "TOTAL TIME", kTextColorRed, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearTime)]);
	DrawFormatStringFToHandle(kTimeTextPos.x, kTimeTextPos.y,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearTime)], "%02d:%02d:%03d", totalMin, totalSec, totalMilliSec);


	// �N���A�^�C����\��
	for (int i = 0; i < m_clearTime.size(); i++)
	{
		// �N���A�^�C�����t���[��������b���ɕϊ�
		int min = Conversion::ChangeMin(m_clearTime[i]);
		int sec = Conversion::ChangeSec(m_clearTime[i]);
		int milliSec = Conversion::ChangeMilliSec(m_clearTime[i]);

		DrawFormatStringToHandle(kTimeTextPos.x - kTimeTextAdj, kTimeTextPos.y + kTimeTextInterval * (i + 1),
			kTextColorRed, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearTime)], "%d��� ", i + 1);
		DrawFormatStringFToHandle(kTimeTextPos.x, kTimeTextPos.y + kTimeTextInterval * (i + 1),
			kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearTime)], "%02d:%02d:%03d", min, sec, milliSec);
	}

	// �����L���O�\��
	DrawStringFToHandle(kRankingTextPos.x, kRankingTextPos.y,
		"�����L���O", kTextColorRed, Font::m_fontHandle[static_cast<int>(Font::FontId::kRankingText)]);
	m_pRank->DrawClearRanking();

	// �e�L�X�g�\��
	m_pUI->DrawClearButtonText();

	DrawFade();	// �t�F�[�h�C���A�E�g�`��

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�N���A���", 0xffffff);
	// ���S��
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);
#endif
}
