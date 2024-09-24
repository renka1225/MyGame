#include "BgStage1.h"
#include "Bg.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{
	// �w�i�摜�̃T�C�Y
	constexpr int kBgWidth = 576;
	constexpr int kBgHeight = 324;
	// �w�i�摜�̊g�嗦
	constexpr float kBgScale = 10.0f;
	constexpr float kBg2Scale = 5.0f;
	// �w�i�摜�̈ړ���
	constexpr float kBgMove = -1.2f;

	// �}�b�v�`�b�v1�̃T�C�Y
	constexpr int kChipWidth = 18;
	constexpr int kChipHeight = 18;
	// �}�b�v�`�b�v�g�嗦
	constexpr float kChipScale = 3.0f;

	// �`�b�v��u����
	constexpr int kChipNumX = 110;
	constexpr int kChipNumY = 50;

	// �}�b�v�̍L��
	constexpr int kMapWidth = static_cast<int>(kChipWidth * kChipScale * kChipNumX);
	constexpr int kMapHeight = static_cast<int>(kChipHeight * kChipScale * kChipNumY);

	// �}�b�v�`�b�v�̔z����
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		// 0                                        // 11                                     // 21                                     // 31                                      // 41                                    // 51                                     // 61                                     // 71                                     // 81                                     // 91                                     // 101
		{ 1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },

		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  2,  2,  2,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  0,  0,  1,   1,  0,  0,  0,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  2,  2,  2,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  0,  0,  1,   1,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  2,  2,  2,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  0,  0,  1,   1,  1,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  2,  2,  2,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  0,  0,  1,   1,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  2,  2,  2,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  0,  0,  1,   1,  0,  0,  0,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  2,  2,  2,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  0,  0,  1,   1,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  2,  2,  2,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  0,  0,  1,   1,  1,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   0,  0,  0,  0,  0,	  0,  0,  0,  0,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  2,  2,  2,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  0,  0,  1,   1,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  0,  0,  0,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  1,  1,  1,  1 },

		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  1,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  0,  0,   0,  0,  0,  0,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  0,  0,  0,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  1,   1,  1,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   1,  1,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  0,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   1,  1,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  0,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },

		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  1,   1,  1,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  0,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   1,  1,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  0,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   1,  1,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  0,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   1,  1,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  0,  0,  0,  0,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   0,  0,  0,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  2,  0,   0,  0,  0,  0,  0,   2,  0,  0,  0,  0,   0,  0,  0,  0,  2,   0,  0,  0,  0,  0,   0,  0,  0,  0,  2,   0,  0,  0,  0,  2,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },

		{ 1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  2,   0,  0,  0,  0,  0,   0,  0,  0,  0,  2,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  2,  0,  0,  0,   0,  0,  2,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  2,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  2,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  2,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
		{ 1,  1,  1,  1,  1,   1,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   2,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  2,   2,  2,  2,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1,  1,  1 },
	};

}

BgStage1::BgStage1()
{
	m_bgHandle = LoadGraph("data/image/BackGround/Stage2/1.png");
	m_bg2Handle = LoadGraph("data/image/BackGround/Stage2/2.png");
	m_bg3Handle = LoadGraph("data/image/BackGround/Stage2/3.png");
	m_bg4Handle = LoadGraph("data/image/BackGround/Stage2/4.png");
	m_mapHandle = LoadGraph("data/image/map2.png");
}

BgStage1::~BgStage1()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_bg4Handle);
	DeleteGraph(m_mapHandle);
}

void BgStage1::Init()
{
	// �摜�̃}�b�v�`�b�v���𐔂���
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_mapHandle, &graphW, &graphH);

	// ���W�̏�����
	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;
	m_bgPos = { 0, 0 };
	m_bgMove = kBgMove;
}

void BgStage1::Update()
{
	// �w�i�̕\���ʒu�̍X�V
	m_bgMove += kBgMove;
}

void BgStage1::Draw()
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
			if (posY < 0 - kChipHeight * 3) continue;
			if (posY > Game::kScreenHeight) continue;

			// �ݒu����`�b�v
			int chipNo = kChipData[y][x];

			// �}�b�v�`�b�v�̃O���t�B�b�N�؂�o�����W
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumY);

			// �`��
			DrawRectRotaGraph(static_cast<int>(posX + kChipWidth * kChipScale * 0.5), static_cast<int>(posY + kChipHeight * kChipScale * 0.5), srcX, srcY,
				kChipWidth, kChipHeight,
				kChipScale, 0.0f,
				m_mapHandle, true);

#ifdef _DEBUG
			// MEMO:�����蔻��`��
			//DrawBox(posX, posY, posX + kChipWidth * kChipScale, posY + kChipWidth * kChipScale, 0xff0000, false);
#endif
		}
	}
}

/// <summary>
/// �w�i�\��
/// </summary>
void BgStage1::DrawBg()
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

	SetDrawBlendMode(DX_BLENDMODE_ADD, 10);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xdb66ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/// <summary>
/// ���X�N���[��
/// </summary>
/// <returns>�X�N���[����</returns>
int BgStage1::GetScrollX()
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
int BgStage1::GetScrollY()
{
	int result = static_cast<int>(m_pPlayer->GetPos().y - Game::kScreenHeight * 0.5);
	if (result < 0)
	{
		result = 0;
	}
	if (result > kMapHeight - Game::kScreenHeight)
	{
		result = kMapHeight - Game::kScreenHeight;
	}

	return result;
}

/// <summary>
/// �v���C���[�Ɠ������Ă��邩����
/// </summary>
/// <returns></returns>
bool BgStage1::IsColPlayer()
{
	float playerLeft = m_pPlayer->GetColRect().GetLeft();
	float playerRight = m_pPlayer->GetColRect().GetRight();
	float playerTop = m_pPlayer->GetColRect().GetTop();
	float playerBottom = m_pPlayer->GetColRect().GetBottom();

	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// �n�ʈȊO�͓�����Ȃ�
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
bool BgStage1::IsCollision(Rect rect, Rect& chipRect)
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