#include "DxLib.h"
#include "CharacterBase.h"
#include "LoadData.h"
#include <fstream>
#include <sstream>

// �萔
namespace
{
	const char* const kFileName = "data/data.csv";
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="data">�L�����N�^�[�Q��</param>
/// <param name="charType">�L�����N�^�[�̎��</param>
LoadData::LoadData(CharacterBase& data, int charType)
{
	LoadCharaData(data, charType);
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
	for (const auto& data : m_data)
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
	std::ifstream file(kFileName);
	m_data.clear();
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
				m_data.push_back(std::stof(field));
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
		data.m_status.maxHp = m_data[0];
		data.m_status.punchPower = m_data[1];
		data.m_status.kickPower = m_data[2];
		data.m_status.maxMoveSpeed = m_data[3];
	}
	// �`���[�g���A���G
	else if (charType == static_cast<int>(CharacterBase::CharaType::kEnemyTuto))
	{
		data.m_status.maxHp = m_data[4];
		data.m_status.punchPower = m_data[5];
		data.m_status.kickPower = m_data[6];
		data.m_status.maxMoveSpeed = m_data[7];
	}
}
