#pragma once
#include "Vec2.h"

class FontManager;

/// <summary>
/// スタート演出、クリア演出等の管理クラス
/// </summary>
class SceneStaging
{
public:
	SceneStaging();
	virtual ~SceneStaging();
	void Init();
	void Update();
	void Draw();
	// スタート演出
	void Start();
	// クリア演出
	void Clear();

	// 表示状態を取得
	bool IsStart() const { return m_isStart; }
	bool IsClear() const { return m_isClear; }

private:
	/*ポインタを取得*/
	// フォント管理
	FontManager* m_pFont;

	// スタート演出が表示中か true:表示中
	bool m_isStart;
	// クリア演出が表示中か
	bool m_isClear;

	// 演出
	float m_startTime;		// スタート演出の時間
	float m_clearTime;		// クリア演出時間
	float m_gameoverTime;	// ゲームオーバー演出時間

	// スタート演出の表示位置
	Vec2 m_startDis;
	// クリア演出の表示位置
	Vec2 m_clearDis;

	// 音
	int m_startSE;		// スタート時のSE
	int m_clearSE;		// クリア時のSE
};

