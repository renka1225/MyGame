#include "DxLib.h"
#include "CharacterBase.h"
#include "LoadData.h"
#include <fstream>
#include <sstream>

// �萔
namespace
{
	const char* const kCharStatusFileName = "data/csv/charStatus.csv";	// �L�����N�^�[�f�[�^�̃t�@�C����
	const char* const kAnimSpeedFileName = "data/csv/animSpeed.csv";	// �A�j���[�V�������x�f�[�^�̃t�@�C����

	constexpr int kAnimNum = 14;	// 1�L�����N�^�[�̃A�j���[�V�����̐�
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="data">�L�����N�^�[�Q��</param>
/// <param name="charType">�L�����N�^�[�̎��</param>
LoadData::LoadData(CharacterBase& data, int charType)
{
	LoadCharaData(data, charType);
	LoadAnimSpeedData(data, charType);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
LoadData::~LoadData()
{
}


/// <summary>
/// �`��
/// </summary>
void LoadData::Draw()
{
#ifdef _DEBUG
	// �ǂݍ��񂾃f�[�^��\������
	int y = 0;
	for (const auto& data : m_charData)
	{
		DrawFormatString(0, 100+y, 0xffffff, "%f:", data);
		y += 20;
	}
#endif
}


/// <summary>
/// �L�����N�^�[�̃f�[�^��ǂݍ���
/// </summary>
/// <param name="data">�L�����N�^�[�Q��</param>
/// <param name="charCharType">�L�����N�^�[�̎��</param>
void LoadData::LoadCharaData(CharacterBase& data, int charType)
{
	std::ifstream file(kCharStatusFileName);
	m_charData.clear();
	std::string line;

	// �t�@�C���̓��͎擾
	// std::getline(�ǂݎ��t�@�C���̕ϐ�, ���͕�������i�[����ϐ�);
	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string field;

		// �����񕪊�
		// getline(istringstream�^�̕ϐ�, ����������������i�[����ϐ�, ',�ŕ���')
		while (getline(stream, field, ','))
		{
			try
			{
				// �������float�ɕϊ�����m_data�ɒǉ�����
				m_charData.push_back(std::stof(field));
			}
			catch (const std::invalid_argument& e)
			{
				// �����ȕ�������X�L�b�v
			}
		}
	}

	// �v���C���[
	if (charType == static_cast<int>(CharacterBase::CharaType::kPlayer))
	{
		data.m_status.maxHp = m_charData[0];
		data.m_status.punchPower = m_charData[1];
		data.m_status.kickPower = m_charData[2];
		data.m_status.maxMoveSpeed = m_charData[3];
	}
	// �`���[�g���A���G
	else if (charType == static_cast<int>(CharacterBase::CharaType::kEnemyTuto))
	{
		data.m_status.maxHp = m_charData[4];
		data.m_status.punchPower = m_charData[5];
		data.m_status.kickPower = m_charData[6];
		data.m_status.maxMoveSpeed = m_charData[7];
	}
}


/// <summary>
/// �A�j���[�V�������x�̃f�[�^��ǂݍ���
/// </summary>
/// <param name="data">�L�����N�^�[�Q��</param>
/// <param name="charType">�L�����N�^�[�̎��</param>
void LoadData::LoadAnimSpeedData(CharacterBase& data, int charType)
{
	std::ifstream file(kAnimSpeedFileName);
	m_animSpeedData.clear();
	std::string line;

	// �t�@�C���̓��͎擾
	// std::getline(�ǂݎ��t�@�C���̕ϐ�, ���͕�������i�[����ϐ�);
	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string field;

		// �����񕪊�
		// getline(istringstream�^�̕ϐ�, ����������������i�[����ϐ�, ',�ŕ���')
		while (getline(stream, field, ','))
		{
			try
			{
				// �������float�ɕϊ�����m_data�ɒǉ�����
				m_animSpeedData.push_back(std::stof(field));
			}
			catch (const std::invalid_argument& e)
			{
				// �����ȕ�������X�L�b�v
			}
		}
	}

	// �v���C���[
	if (charType == static_cast<int>(CharacterBase::CharaType::kPlayer))
	{
		data.m_animSpeed.none = m_animSpeedData[0 + charType * kAnimNum];
		data.m_animSpeed.avoid = m_animSpeedData[1 + charType * kAnimNum];
		data.m_animSpeed.down = m_animSpeedData[2 + charType * kAnimNum];
		data.m_animSpeed.fightIdle = m_animSpeedData[3 + charType * kAnimNum];
		data.m_animSpeed.gettingUp = m_animSpeedData[4 + charType * kAnimNum];
		data.m_animSpeed.grab = m_animSpeedData[5 + charType * kAnimNum];
		data.m_animSpeed.guard = m_animSpeedData[6 + charType * kAnimNum];
		data.m_animSpeed.kick = m_animSpeedData[7 + charType * kAnimNum];
		data.m_animSpeed.punch = m_animSpeedData[8 + charType * kAnimNum];
		data.m_animSpeed.comboPunch = m_animSpeedData[9 + charType * kAnimNum];
		data.m_animSpeed.receive = m_animSpeedData[10 + charType * kAnimNum];
		data.m_animSpeed.run = m_animSpeedData[11 + charType * kAnimNum];
		data.m_animSpeed.stand = m_animSpeedData[12 + charType * kAnimNum];
		data.m_animSpeed.Stumble = m_animSpeedData[13 + charType * kAnimNum];
	}
	// �`���[�g���A���G
	else if (charType == static_cast<int>(CharacterBase::CharaType::kEnemyTuto))
	{
		data.m_animSpeed.none = m_animSpeedData[0 + charType * kAnimNum];
		data.m_animSpeed.avoid = m_animSpeedData[1 + charType * kAnimNum];
		data.m_animSpeed.down = m_animSpeedData[2 + charType * kAnimNum];
		data.m_animSpeed.fightIdle = m_animSpeedData[3 + charType * kAnimNum];
		data.m_animSpeed.gettingUp = m_animSpeedData[4 + charType * kAnimNum];
		data.m_animSpeed.grab = m_animSpeedData[5 + charType * kAnimNum];
		data.m_animSpeed.guard = m_animSpeedData[6 + charType * kAnimNum];
		data.m_animSpeed.kick = m_animSpeedData[7 + charType * kAnimNum];
		data.m_animSpeed.punch = m_animSpeedData[8 + charType * kAnimNum];
		data.m_animSpeed.comboPunch = m_animSpeedData[9 + charType * kAnimNum];
		data.m_animSpeed.receive = m_animSpeedData[10 + charType * kAnimNum];
		data.m_animSpeed.run = m_animSpeedData[11 + charType * kAnimNum];
		data.m_animSpeed.stand = m_animSpeedData[12 + charType * kAnimNum];
		data.m_animSpeed.Stumble = m_animSpeedData[13 + charType * kAnimNum];
	}
}
