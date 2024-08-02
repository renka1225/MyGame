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
/// �R���X�g���N�^
/// </summary>
SceneClear::SceneClear()
{
	m_textHandle = LoadGraph(kSyoriTextPath);
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
	//for (const auto& time : m_clearTime)
	//{
	//	int min = Conversion::ChangeMin(time);
	//	int sec = Conversion::ChangeSec(time);
	//	int milliSec = Conversion::ChangeMilliSec(time);

	//	DrawFormatString(500, 650 + 100 * time, 0xffffff, "%d��� %02d:%02d:%03d", time, min, sec, milliSec);
	//	DrawFormatString(500, 650 + 100 * time, 0xffffff, "%d��� %02d:%02d:%03d", time, min, sec, milliSec);
	//	DrawFormatString(500, 650 + 100 * time, 0xffffff, "%d��� %02d:%02d:%03d", time, min, sec, milliSec);
	//}

	// TODO:���ŃN���A�^�C�������\��
	DrawString(480, 550, "TotalTime 00:00:00", 0x000000);
	//DrawString(500, 600, "1��� 00:00:00", 0x000000);

	DrawString(1300, 550, "�����L���O", 0x000000);
	DrawString(1300, 600, "1�� 00:00:00", 0x000000);
	DrawString(1300, 650, "2�� 00:00:00", 0x000000);
	DrawString(1300, 700, "3�� 00:00:00", 0x000000);
	DrawString(1300, 750, "4�� 00:00:00", 0x000000);
	DrawString(1300, 800, "5�� 00:00:00", 0x000000);
	DrawString(1600, 1000, "�X�e�[�W�I���ɂ��ǂ�", 0x000000);
#endif
}
