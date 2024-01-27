#include "Bg.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	// 背景のサイズ
	constexpr int kBgWidth = 576;
	constexpr int kBgHeight = 324;
	// 背景画像の拡大率
	constexpr int kBgScale = 10.0f;

	// マップチップ1つのサイズ
	constexpr int kChipWidth = 18;
	constexpr int kChipHeight = 18;
	// マップチップ拡大率
	constexpr int kChipScale = 3.0f;

	// チップを置く数
	constexpr int kChipNumX = 142;
	constexpr int kChipNumY = 20;

	// マップの広さ
	constexpr int kMapWidth = kChipWidth * kChipScale * kChipNumX;
	constexpr int kMapHeight = kChipHeight * kChipScale * kChipNumY;

	// マップチップの配列情報
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},

		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,    0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
		{ 10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10, 10,   10, 10, 10, 10,  0,   0, 10, 10, 10, 10},
	};
}

Bg::Bg():
	m_pPlayer(nullptr),
	m_bgPos(0, 0),
	m_graphChipNumX(0),
	m_graphChipNumY(0)
{
	m_bgHandle = LoadGraph("data/image/BackGround/stage1.png");
	m_mapHandle = LoadGraph("data/image/map.png");
}

Bg::~Bg()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_mapHandle);
}

void Bg::Init()
{
	// 画像のマップチップ数を数える
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_mapHandle, &graphW, &graphH);

	// 座標の初期化
	m_bgPos.x = 0;
	m_bgPos.y = 0;
	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;
}

void Bg::Update()
{
}

void Bg::Draw()
{
	// 背景の描画
	DrawRectRotaGraph(0, 0, 
		0, 0, 
		kBgWidth, kBgHeight, 
		kBgScale, 0.0f,
		m_bgHandle, false);

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
			DrawRectRotaGraph(posX, posY, srcX, srcY, 
				kChipWidth, kChipHeight, 
				kChipScale, 0.0f,
				m_mapHandle, true);
		}
	}
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
