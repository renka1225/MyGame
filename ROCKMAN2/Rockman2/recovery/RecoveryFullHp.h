#pragma once

class SceneMain;

/// <summary>
/// HP全回復アイテムクラス
/// </summary>
class RecoveryFullHp
{
public:
	RecoveryFullHp();
	virtual ~RecoveryFullHp();

	void Init();
	void Update();
	void Draw();

	// 回復アイテムの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

private:
	// メインシーンのポインタ
	SceneMain* m_pMain;
	// グラフィックのハンドル
	int m_handle;
	// 画面内に存在しているか
	bool m_isExist;

	// 表示位置
	Vec2 m_pos;
	// 当たり判定用の矩形
	Rect m_colRect;
};

