#pragma once
#include <string>
#include <vector>

/// <summary>
/// �����L���O�����X�V����
/// </summary>
class Ranking
{
public:
	Ranking();
	~Ranking();
	void CreateRanking(int m_stageKind);			  // �����L���O�쐬
	void UpdateRanking(int stageKind, int clearTime); // �����L���O�X�V
	void GetRanking(int stage);						  // �����L���O�擾
	void DrawStageSelectRanking();					  // �X�e�[�W�I���������L���O�`��
	void DrawClearRanking();						  // �N���A�������L���O�`��

private:
	std::string HttpGet(const char* domain, const char* url); // Http�ʐM��Get���߂𑗂�

private:
	std::string uri;
	std::string createRank;
	std::string getRank;

	// �l�b�g���[�N�p�̕ϐ�
	static const int kDataSize = 2560;	// �f�[�^�T�C�Y
	char StrBuf[kDataSize] = "";		// �f�[�^�o�b�t�@
	IPDATA Ip;							// �ڑ��p�h�o�A�h���X�f�[�^
	int NetHandle;						// �l�b�g���[�N�n���h��
	int DataLength;						// ��M�f�[�^�ʕۑ��p�ϐ�
	size_t m_pos;						// �����̒������擾����
	int m_lineCount;					// �\������s�����J�E���g����
	std::vector<int> m_rankingList;		// �N���A�^�C����ۑ�����
};

