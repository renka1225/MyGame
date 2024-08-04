#pragma once
#include <string>
#include <vector>
#include <unordered_map>

/// <summary>
/// �t�@�C����ǂݍ���
/// </summary>
class LoadData
{
public:
	LoadData();
	~LoadData();
	void Init();
	void Update();
	void Draw();

private:
	int m_handle; // �ǂݍ��ރf�[�^
	std::unordered_map<std::string, int> m_model; // ���f���f�[�^

	// �z�u���f�[�^
	struct LocationData
	{
		std::string name;	// ���O
		std::string tag;	// �^�O
		VECTOR pos;			// ���W
		VECTOR rot;			// ��]
		VECTOR scale;		// �X�P�[��
	};
	std::vector<LocationData> m_locationData;
};

