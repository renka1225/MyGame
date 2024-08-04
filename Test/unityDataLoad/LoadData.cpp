#include "DxLib.h"
#include "LoadData.h"

// MEMO:�t�@�C������f�[�^��ǂݍ���
// FileRead_read(void* Buffer, int ReadSize, int FileHandle);
// �f�[�^��ǂݍ��ރo�b�t�@�̐擪�A�h���X,�ǂݏo���T�C�Y(�o�C�g��),�t�@�C���n���h��

LoadData::LoadData()
{
	m_handle = FileRead_open("City/city.loc");
	// �f�[�^��
	int dataCnt = 0;
	FileRead_read(&dataCnt, sizeof(dataCnt), m_handle);
	m_locationData.resize(dataCnt);

	for (auto& loc : m_locationData)
	{
		// �I�u�W�F�N�g�������[�h
		byte nameCnt = 0;
		FileRead_read(&nameCnt, sizeof(nameCnt), m_handle);
		loc.name.resize(nameCnt);

		// MEMO:loc.name.data()�̕�����C++20���ƃG���[�ɂȂ�Ȃ�
		FileRead_read(loc.name.data(), sizeof(char) * loc.name.size(), m_handle);

		// �^�O�����[�h
		byte tagCnt = 0;
		FileRead_read(&tagCnt, sizeof(tagCnt), m_handle);
		loc.tag.resize(tagCnt);
		FileRead_read(loc.tag.data(), sizeof(char) * loc.tag.size(), m_handle);

		// ���W���
		FileRead_read(&loc.pos, sizeof(loc.pos), m_handle);
		// ��]���
		FileRead_read(&loc.rot, sizeof(loc.rot), m_handle);
		// �X�P�[�����
		FileRead_read(&loc.scale, sizeof(loc.scale), m_handle);
	}
	FileRead_close(m_handle);

	// ���f���̃p�X��ݒ�
	for (auto& loc : m_locationData)
	{
		if (m_model.find(loc.name) == m_model.end())
		{
			std::string modelPath = "City/mv1/" + loc.name + ".mv1"; // ���f���̃p�X��ݒ�
			int modelHandle = MV1LoadModel(modelPath.c_str());
			m_model[loc.name] = modelHandle;
		}
	}
}

LoadData::~LoadData()
{
	for (auto& pair : m_model)
	{
		MV1DeleteModel(pair.second);
	}
}

void LoadData::Init()
{
	// MEMO:�T�C�Y��ʒu�̒���
	for (const auto& loc : m_locationData)
	{
		MV1SetScale(m_model[loc.name], VGet(0.3f, 0.3f, 0.3f));
		MV1SetPosition(m_model[loc.name], VGet(-200.0f, loc.pos.y, -100.0f));
	}
}

void LoadData::Update()
{
}

void LoadData::Draw()
{
	int y = 40;
	for (const auto& loc : m_locationData)
	{
		DrawFormatString(0, y, 0xffffff, "name:%s, tag:%s, pos(%2.2f:%2.2f:%2.2f), rot(%2.2f:%2.2f:%2.2f), scale(%2.2f:%2.2f:%2.2f)", 
			loc.name.c_str(), loc.tag.c_str(), loc.pos.x, loc.pos.y, loc.pos.z, loc.rot.x, loc.rot.y, loc.rot.z, loc.scale.x, loc.scale.y, loc.scale.z);
		y += 20;

		MV1DrawModel(m_model[loc.name]);
	}
}
