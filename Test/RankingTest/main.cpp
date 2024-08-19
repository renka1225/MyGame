#include "DxLib.h"
#include <iostream>
#include<string>


/// <summary>
/// Http�ʐM�ł�Get���߂𑗂鎖���ł��閽��
/// </summary>
/// <param name="domain">�h���C���������</param>
/// <param name="uri">URI�����</param>
/// <returns>string�^�Ŏ��s���ʂ𓾂�(�\��ł܂�����Ă܂���)</returns>
std::string HttpGet(const char* domain, const char* uri)
{
	/*�K���ȕϐ�*/
	std::string ans;
	int i = 12;//�����̕\���ʒu�p

	/*�����֌W*/
	unsigned int Cr = GetColor(255, 255, 255);	 // ���F�̒l���擾
	SetFontSize(12);                             //�T�C�Y�ύX
	SetFontThickness(4);                         //������ύX

	/*�l�b�g���[�N�p�̕ϐ�*/
	const int DATA_SIZE = 2560;		//8bit�̂ł�����(char�ő�v�f����268435455)
	char StrBuf[DATA_SIZE] = "";    // �f�[�^�o�b�t�@
	IPDATA Ip;						// �ڑ��p�h�o�A�h���X�f�[�^
	int NetHandle;					// �l�b�g���[�N�n���h��
	int DataLength;					// ��M�f�[�^�ʕۑ��p�ϐ�

	/*Http�ʐM���쐬���邽�߂̕ϐ�*/
	char HttpCmd[128] = "";

	//DxLib�̗]�v�ȋ@�\��؂�B
	SetUseDXNetWorkProtocol(false);

	//DNS����h���C������IP�A�h���X�擾
	int test = GetHostIPbyName(domain, &Ip);
	DrawFormatString(0, 0, 0xffffff, "GetDomain:%d", test);//0�Ȃ琳��

	//�擾����IP�A�h���X�̊m�F
	DrawFormatString(0, 20, 0xffffff, "IpAdress;%d,%d,%d,%d", Ip.d1, Ip.d2, Ip.d3, Ip.d4);

	// �ʐM���m��
	NetHandle = ConnectNetWork(Ip, 80);
	DrawFormatString(0, 40, 0xffffff, "NetHandle:%d", NetHandle);

	// �m�������������ꍇ�̂ݒ��̏���������
	if (NetHandle != -1)
	{
		//Http���߂̍쐬
		sprintf_s(HttpCmd, "GET %s HTTP/1.1\nHost: %s\n\n", uri, domain);
		DrawFormatString(0, 60, 0xffffff, "HttpCmd:\n%s", HttpCmd);

		// �f�[�^���M(http���߂𑗂�)
		NetWorkSend(NetHandle, HttpCmd, strlen(HttpCmd));

		// �f�[�^������̂�҂�
		while (!ProcessMessage())
		{
			// �擾���Ă��Ȃ���M�f�[�^�ʂ𓾂�
			DataLength = GetNetWorkDataLength(NetHandle);

			// �擾���ĂȂ���M�f�[�^�ʂ�-1����Ȃ��ꍇ�̓��[�v�𔲂���
			if (DataLength != -1)
			{
				break;
			}
		}

		// �f�[�^��M
		NetWorkRecv(NetHandle, StrBuf, DATA_SIZE);    // �f�[�^���o�b�t�@�Ɏ擾

		// ��M�����f�[�^��`��
		DrawString(0, 120, StrBuf, 0xffffff);

		// �L�[���͑҂�
		WaitKey();

		// �ڑ���f��
		CloseNetWork(NetHandle);
	}

	return ans;
}

int m_time = 0;

/*Main*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//window���[�h
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;
	}

	char KeyBuf[256];

	while (ProcessMessage() == 0)
	{
		// ��ʂ̃N���A
		ClearDrawScreen();

		// ���ׂẴL�[�̏�Ԃ𓾂�
		GetHitKeyStateAll(KeyBuf);

		if (KeyBuf[KEY_INPUT_Z] == 1)
		{
			break;
		}

		m_time++;
		m_time %= 1000;
		DrawFormatString(0, 150, 0x0000ff, "%d", m_time);
	}
	
	/*Http�ʐM��Get���߂��w��̃A�h���X�ɍs���Ă���*/
	// �����L���O�̃f�[�^�x�[�X���쐬
	// MEMO:�Q�[���J�n���ŏ���1�񂾂��Ă�
	//std::string createRank = HttpGet("rueda.zombie.jp", "/Ranking/createRanking.php");
	// ��ʃN���A
	ClearDrawScreen();
	// �����L���O�̍X�V
	// �o�߂������Ԃ�V���ɒǉ�����
	std::string uri = "/Ranking/updateRanking.php?clearTime=" + std::to_string(m_time);
	std::string updateRank = HttpGet("rueda.zombie.jp", uri.c_str());
	// ��ʃN���A
	ClearDrawScreen();
	//�����L���O�̎擾
	std::string getRank = HttpGet("rueda.zombie.jp", "/Ranking/getRanking.php");


	WaitKey();// �L�[���͑҂�
	DxLib_End();// �c�w���C�u�����g�p�̏I������
	return 0;// �\�t�g�̏I�� 
}