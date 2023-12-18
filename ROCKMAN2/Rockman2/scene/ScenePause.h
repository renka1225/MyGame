#pragma once
#include "Vec2.h"

/// <summary>
/// ポーズシーンクラス
/// </summary>
class ScenePause
{
public:
	ScenePause();
	~ScenePause();
	void Init();
	void Update();
	void Draw();
	// ポーズ画面が表示されているか取得する
	bool IsExist() const { return m_isExist; }

private:
	// ポーズ画面の表示位置
	Vec2 m_pos;

	// ポーズ画面が表示されているか true:表示されている
	bool m_isExist;

};

