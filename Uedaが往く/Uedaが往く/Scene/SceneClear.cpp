#include "DxLib.h"
#include "Input.h"
#include "Vec2.h"
#include "Game.h"
#include "ConversionTime.h"
#include "SceneSelectStage.h"
#include "SceneClear.h"

// �萔
namespace
{
	const char* const kSyoriTextPath = "data/UI/syori.png";	// �����̃e�L�X�g�摜�̃t�@�C���ʒu
	const Vec2 kSyoriTextPos = { 650, 100 };				// �����̃e�L�X�g�摜�\���ʒu
}


/// <summary>
/// �����t���R���X�g���N�^
/// </summary>
/// <param name="clearTime">�N���A�^�C��</param>
SceneClear::SceneClear(std::vector<int> clearTime):
	m_totalClearTime(0)
{
	m_textHandle = LoadGraph(kSyoriTextPath);
	m_clearTime = clearTime;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneClear::~SceneClear()
{
	DeleteGraph(m_textHandle);
}


/// <summary>
/// ������
/// </summary>
void SceneClear::Init()
{
	// �g�[�^���̃N���A���Ԃ��v�Z����
	for (int i = 0; i < m_clearTime.size(); i++)
	{
		m_totalClearTime += m_clearTime[i];
	}
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		return std::make_shared<SceneSelectStage>();
	}
	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void SceneClear::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xb3b3b3, true);

	// �����̕�����\��
	DrawGraphF(kSyoriTextPos.x, kSyoriTextPos.y, m_textHandle, true);

#ifdef _DEBUG	// �f�o�b�O�\��
	// ���݂̃V�[��
	DrawString(0, 0, "�N���A���", 0xffffff);
	// ���S��
	DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0x0000ff);

	// �N���A�^�C�����t���[��������b���ɕϊ�
	for (int i = 0; i < m_clearTime.size(); i++)
	{
		int min = Conversion::ChangeMin(m_clearTime[i]);
		int sec = Conversion::ChangeSec(m_clearTime[i]);
		int milliSec = Conversion::ChangeMilliSec(m_clearTime[i]);

		// �N���A�^�C���\��
		DrawFormatString(500, 650 + 100 * i, 0x000000, "%d��� %02d:%02d:%03d", i + 1, min, sec, milliSec);
	}

	// �g�[�^���^�C���\��
	int totalMin = Conversion::ChangeMin(m_totalClearTime);
	int totalSec = Conversion::ChangeSec(m_totalClearTime);
	int totalMilliSec = Conversion::ChangeMilliSec(m_totalClearTime);
	DrawFormatString(500, 550, 0x000000, "TOTAL TIME %02d:%02d:%03d", totalMin, totalSec, totalMilliSec);

	DrawString(1300, 550, "�����L���O", 0x000000);
	DrawString(1300, 600, "1�� 00:00:00", 0x000000);
	DrawString(1300, 650, "2�� 00:00:00", 0x000000);
	DrawString(1300, 700, "3�� 00:00:00", 0x000000);
	DrawString(1300, 750, "4�� 00:00:00", 0x000000);
	DrawString(1300, 800, "5�� 00:00:00", 0x000000);
	DrawString(1600, 1000, "�X�e�[�W�I���ɂ��ǂ�", 0x000000);
#endif
}
