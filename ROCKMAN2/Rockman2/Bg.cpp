#include "Bg.h"
#include "SceneMain.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	// 背景のスクロール速度
	constexpr int kScrollSpeed = 2;

	// 背景画像をループさせる位置
	constexpr float kLoopPos = 500;

	// マップチップの情報
	constexpr int kChipWidth = 32;
	constexpr int kChipHeight = 32;

	// チップを置く数
	constexpr int kChipNumX = 80;
	constexpr int kChipNumY = 23;

	// マップの広さ
	constexpr int kMapWidth = kChipWidth * kChipNumX;
	constexpr int kMapHeight = kChipHeight * kChipNumY;

	// マップチップの配列情報
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30,  1,  1, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30,  1,  1,  1,  1,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{30, 30, 30, 30, 30,  1, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30,  1,  1,  1,  1,  1,   1, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
		{ 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  30, 30,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1, 30, 30,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1, 30, 30,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{ 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  30, 30,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1, 30, 30,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1, 30, 30,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{ 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  30, 30,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1, 30, 30,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1, 30, 30,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{ 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  30, 30,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1, 30, 30,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1, 30, 30,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{ 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  30, 30,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1, 30, 30,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1, 30, 30,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,  1,  1,  1,  1,  1}
	};
}

Bg::Bg(SceneMain* pMain):
	m_pMain(pMain),
	m_bgPos(0, 0),
	m_bgHandle(-1),
	m_mapHandle(-1),
	m_graphChipNumX(0),
	m_graphChipNumY(0)
{
	for (int x = 0; x < kChipNumX; x++)
	{
		for (int y = 0; y < kChipNumY; y++)
		{
			m_chipData[y][x] = kChipData[y][x];
		}
	}
}

Bg::~Bg()
{
}

void Bg::Init()
{
	// 画像のマップチップ数を数える
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_bgHandle, &graphW, &graphH);

	// 座標の初期化
	m_bgPos.x = 0;
	m_bgPos.y = 0;
	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;
}

void Bg::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (pad & PAD_INPUT_LEFT) // ←を押した
	{
		// 背景を左に移動
		m_bgPos.x -= kScrollSpeed;
		if (m_bgPos.x < 0)
		{
			m_bgPos.x = kLoopPos;
		}
	}
	if (pad & PAD_INPUT_RIGHT) // →を押した
	{
		// 背景を右に移動
		m_bgPos.x += kScrollSpeed;
		if (m_bgPos.x > kLoopPos)
		{
			m_bgPos.x = 0;
		}
	}

	// マップチップの当たり判定を更新
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// 設置するチップ
			int chipNo = m_chipData[y][x];

			// 当たり判定を設定
			m_colRect[y][x].SetCenter(x * kChipWidth + kChipWidth / 2, y * kChipHeight + kChipHeight / 2, kChipWidth, kChipHeight);
		}
	}
}

void Bg::Draw()
{
	// 背景の描画
	DrawRectGraph(0, 0, m_bgPos.x, m_bgPos.y, Game::kScreenWidth, Game::kScreenHeight, m_bgHandle, false);

	// プレイヤーの位置に応じたスクロール量を決定する
	//Vec2 scroll = GetScroll();

	// マップチップの描画
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// マップの表示座標
			//int posX = kChipWidth * x - scroll.x;
			//int posY = kChipHeight * y - scroll.y;

			// 設置するチップ
			int chipNo = m_chipData[y][x];

			// マップチップのグラフィック切り出し座標
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			// 描画
			DrawRectGraph(x * kChipWidth, y * kChipHeight, srcX, srcY, kChipWidth, kChipHeight, m_mapHandle, true);


#ifdef _DEBUG
			if (chipNo == 1)
			{
				// 当たり判定の表示
				m_colRect[y][x].Draw(0xb0e0e6, false);
			}
#endif
		}
	}
}

Vec2 Bg::GetScroll()
{
	// 描画座標の左上位置
	float resultX = static_cast<float>(m_pMain->GetPlayerPos().x - Game::kScreenWidth / 2);
	float resultY = static_cast<float>(m_pMain->GetPlayerPos().y - Game::kScreenHeight / 2);

	if (resultX < 0)
	{
		resultX = 0;
	}
	if (resultX >kMapWidth - Game::kScreenWidth)
	{
		resultX = kMapWidth - Game::kScreenWidth;
	}

	if (resultY < 0)
	{
		resultY = 0;
	}
	if (resultY > kMapHeight - Game::kScreenHeight)
	{
		resultY = kMapHeight - Game::kScreenHeight;
	}

	return { resultX, resultY };
}
