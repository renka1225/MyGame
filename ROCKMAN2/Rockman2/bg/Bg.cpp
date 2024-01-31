#include "Bg.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{
	// 背景のサイズ
	constexpr int kBgWidth = 576;
	constexpr int kBgHeight = 324;
	// 背景画像の拡大率
	constexpr float kBgScale = 10.0f;
	constexpr float kBg2Scale = 2.5f;
	// 背景画像の移動量
	constexpr float kBgMove = -1.2f;

	// マップチップ1つのサイズ
	constexpr int kChipWidth = 18;
	constexpr int kChipHeight = 18;
	// マップチップ拡大率
	constexpr int kChipScale = 3.0f;

	// チップを置く数
	constexpr int kChipNumX = 120;
	constexpr int kChipNumY = 20;

	// マップの広さ
	constexpr int kMapWidth = kChipWidth * kChipScale * kChipNumX;
	constexpr int kMapHeight = kChipHeight * kChipScale * kChipNumY;

	// マップチップの配列情報
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{ 10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0, 10, 10, 10,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},

		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0,  0, 10,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,   0,  0,  0, 10, 10,    0,  0, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,    0,  0, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,    0,  0, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,    0,  0, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10},
	};
}

Bg::Bg():
	m_pPlayer(nullptr),
	m_bgPos(0, 0),
	m_bgMove(kBgMove),
	m_graphChipNumX(0),
	m_graphChipNumY(0)
{
	m_bgHandle = LoadGraph("data/image/BackGround/Stage1/1.png");
	m_bg2Handle = LoadGraph("data/image/BackGround/Stage1/2.png");
	m_bg3Handle = LoadGraph("data/image/BackGround/Stage1/3.png");
	m_bg4Handle = LoadGraph("data/image/BackGround/Stage1/4.png");
	m_mapHandle = LoadGraph("data/image/map.png");

	assert(m_bgHandle != -1);
	assert(m_bg2Handle != -1);
	assert(m_bg3Handle != -1);
	assert(m_bg4Handle != -1);
}

Bg::~Bg()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_bg4Handle);
	DeleteGraph(m_mapHandle);
}

void Bg::Init()
{
	// 画像のマップチップ数を数える
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_mapHandle, &graphW, &graphH);

	// 座標の初期化
	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;
	m_bgPos = { 0, 0 };
	m_bgMove = kBgMove;
}

void Bg::Update()
{
	// 背景の表示位置の更新
	m_bgMove += kBgMove;
}

void Bg::Draw()
{
	// 背景表示
	DrawBg();

	// プレイヤーの位置に応じたスクロール量を決定する
	int scrollX = GetScrollX();
	int scrollY = GetScrollY();

	// マップチップの描画
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			int posX = x * kChipWidth * kChipScale - scrollX;
			int posY = y * kChipHeight * kChipScale - scrollY;

			// 画面外は描画しない
			if (posX < 0 - kChipWidth) continue;
			if (posX > Game::kScreenWidth) continue;
			if (posY < 0 - kChipHeight) continue;
			if(posY > Game::kScreenHeight) continue;

			// 設置するチップ
			int chipNo = kChipData[y][x];

			// マップチップのグラフィック切り出し座標
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumY);

			// 描画
			DrawRectRotaGraph(posX + kChipWidth * kChipScale * 0.5f , posY + kChipHeight * kChipScale * 0.5f, srcX, srcY,
				kChipWidth, kChipHeight,
				kChipScale, 0.0f,
				m_mapHandle, true);

#ifdef _DEBUG
			// MEMO:当たり判定描画
			//DrawBox(posX, posY, posX + kChipWidth * kChipScale, posY + kChipWidth * kChipScale, 0xff0000, false);
#endif
		}
	}
}

/*背景表示*/
void Bg::DrawBg()
{
	// 画像サイズを取得
	Size bg3Size;
	Size bg4Size;
	GetGraphSize(m_bg3Handle, &bg3Size.width, &bg3Size.height);
	GetGraphSize(m_bg4Handle, &bg4Size.width, &bg4Size.height);

	// スクロール量を計算する
	int scrollBg3 = static_cast<int>(m_bgMove * 0.1f) % static_cast<int>(bg3Size.width * kBgScale);
	int scrollBg4 = static_cast<int>(m_bgMove * 0.3f) % static_cast<int>(bg4Size.width * kBgScale);


	// 背景描画
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
			scrollBg3 + index * bg3Size.width * kBg2Scale,
			Game::kScreenHeight - bg3Size.height * kBg2Scale,
			0, 0,
			kBg2Scale, 0.0f,
			m_bg3Handle, true);
	}

	for (int index = 0; index < 2; index++)
	{
		DrawRotaGraph2(
			scrollBg4 + index * bg4Size.width * kBg2Scale,
			Game::kScreenHeight - bg4Size.height * kBg2Scale,
			0, 0,
			kBg2Scale, 0.0f,
			m_bg4Handle, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 40);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xff674d, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 横スクロール
int Bg::GetScrollX()
{
	int result = m_pPlayer->GetPos().x - Game::kScreenWidth / 2;
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

// 縦スクロール量
int Bg::GetScrollY()
{
	int result = m_pPlayer->GetPos().y;
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

/*プレイヤーと当たっているか判定*/
bool Bg::IsColPlayer()
{
	float playerLeft = m_pPlayer->GetColRect().GetLeft();
	float playerRight = m_pPlayer->GetColRect().GetRight();
	float playerTop = m_pPlayer->GetColRect().GetTop();
	float playerBottom = m_pPlayer->GetColRect().GetBottom();

	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// 地面以外は当たらない
			if (kChipData[y][x] != 10) continue;

			int chipLeft = x * kChipWidth * kChipScale;
			int chipRight = chipLeft + kChipWidth * kChipScale;
			int chipTop = y * kChipHeight * kChipScale;
			int chipBottom = chipTop + kChipHeight * kChipScale;

			// 絶対に当たらない場合
			if (chipLeft > playerRight) continue;
			if (chipTop > playerBottom) continue;
			if (chipRight < playerRight) continue;
			if (chipBottom < playerTop) continue;

			// いずれかのチップに当たっていたら終了する
			return true;
		}
	}
	// 全てのチップをチェックして1つも当たっていなければ当たっていない
	return false;
}

/*指定したマップチップの矩形と当たっているか判定*/
bool Bg::IsCollision(Rect rect, Rect& chipRect)
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// 地面、壁以外当たらない
			if (kChipData[y][x] != 10) continue;

			int chipLeft = x * kChipWidth * kChipScale;
			int chipRight = chipLeft + kChipWidth * kChipScale;
			int chipTop = y * kChipHeight * kChipScale;
			int chipBottom = chipTop + kChipHeight * kChipScale;

			// 絶対に当たらない場合
			if (chipLeft > rect.GetRight()) continue;
			if (chipTop > rect.GetBottom()) continue;
			if (chipRight < rect.GetLeft()) continue;
			if (chipBottom < rect.GetTop()) continue;

			// ぶつかったマップチップの矩形を設定する
			chipRect.m_left = chipLeft;
			chipRect.m_right = chipRight;
			chipRect.m_top = chipTop;
			chipRect.m_bottom = chipBottom;

			// いずれかのチップに当たっていたら終了する
			return true;
		}
	}
	// 全てのチップをチェックして1つも当たっていなければ当たっていない
	return false;
}
