#include "RecoveryGreatHp.h"
#include "EnemyBase.h"
#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// アイテムのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// 落下速度
	constexpr int kSpeed = 5;
}


RecoveryGreatHp::RecoveryGreatHp()
{
	m_handle = LoadGraph("data/image/Recovery/GreatHp.png");
}

RecoveryGreatHp::~RecoveryGreatHp()
{
	DeleteGraph(m_handle);
}

void RecoveryGreatHp::Init(Bg* pBg)
{
	m_pBg = pBg;
	m_frame = 0;
}

void RecoveryGreatHp::Update()
{
	// 存在しないアイテムの処理はしない
	if (!m_isExist) return;

	// 現在位置の更新
	m_pos += m_vec;

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
	Rect chipRect; // 当たったマップチップの矩形
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_vec.y > 0.0f)
		{
			// 地面に落ちるようにする
			m_pos.y = chipRect.GetTop() - kHeight * 0.5f - 1;
		}
	}

	// 5秒以上たったらアイテムを消す
	m_frame++;
	if (m_frame > 300)
	{
		m_isExist = false;
		m_frame = 0;
	}

	// 画面外に出た処理
	bool isOut = false;	// チェック中の座標が画面外かどうかフラグ
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // 画面左端
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // 画面右端

	// 画面内ならここで終了
	if (!isOut) return;

	// 画面外に出たらアイテムを消す
	m_isExist = false;
}

void RecoveryGreatHp::Draw()
{
	// 中央座標を左上座標に変換
	int x = m_pos.x - kWidth * 0.5f;
	int y = m_pos.y - kHeight * 0.5f;

	// スクロール量を反映する
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	DrawRotaGraph(x, y, 1.0, 0.0, m_handle, true, false);
}

void RecoveryGreatHp::Start(Vec2 pos)
{
	m_isExist = true;

	// 初期位置の設定
	// 倒した敵の現在地を取得する
	m_pos = pos;

	// アイテムを下に落とす
	m_vec.y += kSpeed;
}
