#include "BgTutorial.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	// �w�i�̃T�C�Y
	constexpr int kBgWidth = 576;
	constexpr int kBgHeight = 324;
	// �w�i�摜�̊g�嗦
	constexpr float kBgScale = 10.0f;
	constexpr float kBg2Scale = 2.5f;
	// �w�i�摜�̈ړ���
	constexpr float kBgMove = -1.2f;

	// �����摜�̃T�C�Y
	constexpr int kExWidth = 186;
	constexpr int kExHeight = 126;

	// �����摜�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0, 1 };
	constexpr int kFireUseFrame[] = { 0, 1, 2 };
	// �����摜�̃A�j���[�V����1�R�}�̃t���[����
	constexpr int kExAnimFrameNum = 60;
	// �����摜�̃A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kExAnimFrameCycle = _countof(kUseFrame) * kExAnimFrameNum;
	constexpr int kExFireAnimFrameCycle = _countof(kFireUseFrame) * kExAnimFrameNum;

	// �}�b�v�`�b�v1�̃T�C�Y
	constexpr int kChipWidth = 18;
	constexpr int kChipHeight = 18;
	// �}�b�v�`�b�v�g�嗦
	constexpr float kChipScale = 3.0f;

	// �`�b�v��u����
	constexpr int kChipNumX = 140;
	constexpr int kChipNumY = 20;

	// �}�b�v�̍L��
	constexpr int kMapWidth = static_cast<int>(kChipWidth * kChipScale * kChipNumX);
	constexpr int kMapHeight = static_cast<int>(kChipHeight * kChipScale * kChipNumY);

	// �}�b�v�`�b�v�̔z����
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		//0                                          //11                                       //21                                       //31                                       //41                                       //51                                        //61                                      //71                                       //81                                       //91                                       //101                                       //111                                      // 121                                     //131                                   
		{  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1,    1,  1,  1,  1,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},

		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  2,  2,  2,    2,  2,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  2,  2,  2,   2,  2,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  2,  2,  2,  2,    2,  2,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  2,  2,  2,   2,  2,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   2,  2,  2,  2,  2,    2,  2,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  2,  2,  2,   2,  2,  2,  2,  2,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  0,  0,   0,  0,  0,  0,  0,    0,  0,  2,  2,  2,   2,  2,  2,  2,  2,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  0,  0,   0,  0,  0,  0,  0,    0,  0,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  2,    2,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    2,  2,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  0,   0,  0,  0,  0,  0,    0,  0,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  2,    2,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    2,  2,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  0,   0,  0,  0,  0,  0,    0,  0,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    0,  0,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    0,  0,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  1,   1,  1,  1,  1,  1},
		{  1,  1,  1,  1,  1,   1,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    0,  0,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  2,   2,  2,  2,  2,  2,    2,  2,  2,  2,  1,   1,  1,  1,  1,  1}
	};
}

BgTutorial::BgTutorial():
m_exAnimFrame(0),
m_exFireAnimFrame(0)
{
	m_bgHandle = LoadGraph("data/image/BackGround/Stage1/1.png");
	m_bg2Handle = LoadGraph("data/image/BackGround/Stage1/2.png");
	m_bg3Handle = LoadGraph("data/image/BackGround/Stage1/3.png");
	m_bg4Handle = LoadGraph("data/image/BackGround/Stage1/4.png");
	m_mapHandle = LoadGraph("data/image/map.png");

	// ��������̉摜
	m_walkHandle = LoadGraph("data/image/UI/ex/exWalk.png");
	m_jumpHandle = LoadGraph("data/image/UI/ex/exJump.png");
	m_shotHandle = LoadGraph("data/image/UI/ex/exShot.png");
	m_metalHandle = LoadGraph("data/image/UI/ex/exMetal.png");
	m_fireHandle = LoadGraph("data/image/UI/ex/exFire.png");
	m_lineHandle = LoadGraph("data/image/UI/ex/exLine.png");
	m_menuHandle = LoadGraph("data/image/UI/ex/exMenu.png");
	m_recoveryHandle = LoadGraph("data/image/UI/ex/exRecovery.png");
}

BgTutorial::~BgTutorial()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_bg4Handle);
	DeleteGraph(m_mapHandle);
	DeleteGraph(m_walkHandle);
	DeleteGraph(m_jumpHandle);
	DeleteGraph(m_shotHandle);
	DeleteGraph(m_metalHandle);
	DeleteGraph(m_fireHandle);
	DeleteGraph(m_lineHandle);
	DeleteGraph(m_menuHandle);
	DeleteGraph(m_recoveryHandle);
}

void BgTutorial::Init()
{
	// �摜�̃}�b�v�`�b�v���𐔂���
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_mapHandle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;
	m_bgPos = { 0, 0 };
	m_bgMove = kBgMove;
	m_exAnimFrame = 0;
}

void BgTutorial::Update()
{
	// �w�i�̕\���ʒu�̍X�V
	m_bgMove += kBgMove;

	// �����摜�\���̍X�V
	m_exAnimFrame++;
	if (m_exAnimFrame >= kExAnimFrameCycle)
	{
		m_exAnimFrame = 0;
	}
	m_exFireAnimFrame++;
	if (m_exFireAnimFrame >= kExFireAnimFrameCycle)
	{
		m_exFireAnimFrame = 0;
	}
}

void BgTutorial::Draw()
{
	// �w�i�\��
	DrawBg();

	// �v���C���[�̈ʒu�ɉ������X�N���[���ʂ����肷��
	int scrollX = GetScrollX();
	int scrollY = GetScrollY();

	// �}�b�v�`�b�v�̕`��
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			int posX = static_cast<int>(x * kChipWidth * kChipScale - scrollX);
			int posY = static_cast<int>(y * kChipHeight * kChipScale - scrollY);

			// ��ʊO�͕`�悵�Ȃ�
			if (posX < 0 - kChipWidth) continue;
			if (posX > Game::kScreenWidth) continue;
			if (posY < 0 - kChipHeight) continue;
			if (posY > Game::kScreenHeight) continue;

			// �ݒu����`�b�v
			int chipNo = kChipData[y][x];

			// �}�b�v�`�b�v�̃O���t�B�b�N�؂�o�����W
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumY);

			// �`��
			DrawRectRotaGraph(
				static_cast<int>(posX + kChipWidth * kChipScale * 0.5f), 
				static_cast<int>(posY + kChipHeight * kChipScale * 0.5), 
				srcX, srcY,
				kChipWidth, kChipHeight,
				kChipScale, 0.0f,
				m_mapHandle, true);

#ifdef _DEBUG
			// MEMO:�����蔻��`��
			//DrawBox(posX, posY, posX + kChipWidth * kChipScale, posY + kChipWidth * kChipScale, 0xff0000, false);
#endif
		}
	}

	// ��������̕\��
	DrawEx(scrollX, scrollY);
}

/// <summary>
/// �w�i�\��
/// </summary>
void BgTutorial::DrawBg()
{
	// �摜�T�C�Y���擾
	Size bg3Size;
	Size bg4Size;
	GetGraphSize(m_bg3Handle, &bg3Size.width, &bg3Size.height);
	GetGraphSize(m_bg4Handle, &bg4Size.width, &bg4Size.height);

	// �X�N���[���ʂ��v�Z����
	int scrollBg3 = static_cast<int>(m_bgMove * 0.1f) % static_cast<int>(bg3Size.width * kBgScale);
	int scrollBg4 = static_cast<int>(m_bgMove * 0.3f) % static_cast<int>(bg4Size.width * kBgScale);


	// �w�i�`��
	DrawRectRotaGraph(0, 0,
		0, 0,
		kBgWidth, kBgHeight,
		kBgScale, 0.0f,
		m_bgHandle, true);

	DrawRectRotaGraph(0, 0,
		0, 0,
		kBgWidth, kBgHeight,
		kBgScale, 0.0f,
		m_bg2Handle, true);

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			static_cast<int>(scrollBg3 + index * bg3Size.width * kBg2Scale),
			static_cast<int>(Game::kScreenHeight - bg3Size.height * kBg2Scale),
			0, 0,
			kBg2Scale, 0.0f,
			m_bg3Handle, true);
	}

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			static_cast<int>(scrollBg4 + index * bg4Size.width * kBg2Scale),
			static_cast<int>(Game::kScreenHeight - bg4Size.height * kBg2Scale),
			0, 0,
			kBg2Scale, 0.0f,
			m_bg4Handle, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 40);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xff674d, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/// <summary>
/// ��������̕\��
/// </summary>
void BgTutorial::DrawEx(int scrollX, int scrollY)
{
	int animFrame = m_exAnimFrame / kExAnimFrameNum;
	int fireAnimFrame = m_exFireAnimFrame / kExAnimFrameNum;
	int srcX = kExWidth * kUseFrame[animFrame];
	int fireSrcX = kExWidth * kFireUseFrame[fireAnimFrame];
	int srcY = 0;

	//�ړ�
	DrawGraph(400 - scrollX, 650 - scrollY, m_walkHandle, true);
	// �W�����v
	DrawGraph(850 - scrollX, 650 - scrollY, m_jumpHandle, true);
	// �o�X�^�[
	DrawGraph(2100 - scrollX, 650 - scrollY, m_shotHandle, true);
	// ����؂�ւ�
	DrawGraph(3000 - scrollX, 650 - scrollY, m_menuHandle, true);
	// ���^��
	DrawRectGraph(3500 - scrollX, 650 - scrollY, srcX, srcY, kExWidth, kExHeight, m_metalHandle, true);
	// ��
	DrawGraph(4100 - scrollX, 500 - scrollY, m_recoveryHandle, true);
	// �A�C�e��2��
	DrawRectGraph(5200 - scrollX, 400 - scrollY, srcX, srcY, kExWidth, kExHeight, m_lineHandle, true);
	// �t�@�C�A
	DrawRectGraph(6200 - scrollX, 670 - scrollY, fireSrcX, srcY, kExWidth, kExHeight, m_fireHandle, true);
}

/// <summary>
/// ���X�N���[��
/// </summary>
/// <returns>�X�N���[����</returns>
int BgTutorial::GetScrollX()
{
	int result = static_cast<int>(m_pPlayer->GetPos().x - Game::kScreenWidth * 0.5);
	if (result < 0)
	{
		result = 0;
	}
	if (result > kMapWidth - Game::kScreenWidth)
	{
		result = kMapWidth - Game::kScreenWidth;
	}

	return result;
}

/// <summary>
/// �c�X�N���[��
/// </summary>
/// <returns>�X�N���[����</returns>
int BgTutorial::GetScrollY()
{
	int result = static_cast<int>(m_pPlayer->GetPos().y);
	if (result < 0)
	{
		result = 0;
	}
	if (result > kMapHeight - Game::kScreenHeight)
	{
		result = 0;
	}

	return result;
}

/// <summary>
/// �v���C���[�Ɠ������Ă��邩����
/// </summary>
/// <returns></returns>
bool BgTutorial::IsColPlayer()
{
	float playerLeft = m_pPlayer->GetColRect().GetLeft();
	float playerRight = m_pPlayer->GetColRect().GetRight();
	float playerTop = m_pPlayer->GetColRect().GetTop();
	float playerBottom = m_pPlayer->GetColRect().GetBottom();

	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// �n�ʁA���ȊO�͓�����Ȃ�
			if (kChipData[y][x] == 0) continue;

			int chipLeft = static_cast<int>(x * kChipWidth * kChipScale);
			int chipRight = static_cast<int>(chipLeft + kChipWidth * kChipScale);
			int chipTop = static_cast<int>(y * kChipHeight * kChipScale);
			int chipBottom = static_cast<int>(chipTop + kChipHeight * kChipScale);

			// ��΂ɓ�����Ȃ��ꍇ
			if (chipLeft > playerRight) continue;
			if (chipTop > playerBottom) continue;
			if (chipRight < playerRight) continue;
			if (chipBottom < playerTop) continue;

			// �����ꂩ�̃`�b�v�ɓ������Ă�����I������
			return true;
		}
	}
	// �S�Ẵ`�b�v���`�F�b�N����1���������Ă��Ȃ���Γ������Ă��Ȃ�
	return false;
}

/// <summary>
/// �w�肵���}�b�v�`�b�v�̋�`�Ɠ������Ă��邩����
/// </summary>
/// <param name="rect">�v���C���[�̓����蔻��</param>
/// <param name="chipRect">�`�b�v�̓����蔻��</param>
/// <returns></returns>
bool BgTutorial::IsCollision(Rect rect, Rect& chipRect)
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// �n�ʁA�ǈȊO������Ȃ�
			if (kChipData[y][x] == 0) continue;

			int chipLeft = static_cast<int>(x * kChipWidth * kChipScale);
			int chipRight = static_cast<int>(chipLeft + kChipWidth * kChipScale);
			int chipTop = static_cast<int>(y * kChipHeight * kChipScale);
			int chipBottom = static_cast<int>(chipTop + kChipHeight * kChipScale);

			// ��΂ɓ�����Ȃ��ꍇ
			if (chipLeft > rect.GetRight()) continue;
			if (chipTop > rect.GetBottom()) continue;
			if (chipRight < rect.GetLeft()) continue;
			if (chipBottom < rect.GetTop()) continue;

			// �Ԃ������}�b�v�`�b�v�̋�`��ݒ肷��
			chipRect.m_left = static_cast<float>(chipLeft);
			chipRect.m_right = static_cast<float>(chipRight);
			chipRect.m_top = static_cast<float>(chipTop);
			chipRect.m_bottom = static_cast<float>(chipBottom);

			// �����ꂩ�̃`�b�v�ɓ������Ă�����I������
			return true;
		}
	}
	// �S�Ẵ`�b�v���`�F�b�N����1���������Ă��Ȃ���Γ������Ă��Ȃ�
	return false;
}