#pragma once
#include "Bg.h"

/// <summary>
/// チュートリアルの背景クラス
/// </summary>
class BgTutorial : public Bg
{
public:
	BgTutorial();
	virtual ~BgTutorial();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// プレイヤーの位置からスクロール量を決定する
	virtual int GetScrollX() override;
	virtual int GetScrollY() override;
	// プレイヤーと当たっているか判定する
	virtual bool IsColPlayer() override;
	// 指定した矩形と当たっているか判定する
	virtual bool IsCollision(Rect rect, Rect& chipRect) override;

	// 背景描画
	void DrawBg();
	// 操作説明の表示
	void DrawEx(int scrollX, int scrollY);

private:
	// 操作説明の画像
	int m_walkHandle;		// 移動
	int m_jumpHandle;		// ジャンプ
	int m_shotHandle;		// ショット
	int m_metalHandle;		// メタル
	int m_fireHandle;		// ファイア
	int m_lineHandle;		// 2号
	int m_menuHandle;		// メニュー
	int m_recoveryHandle;	// 回復アイテム

	// 説明画像のアニメーション
	int m_exAnimFrame;
	int m_exFireAnimFrame;
};

