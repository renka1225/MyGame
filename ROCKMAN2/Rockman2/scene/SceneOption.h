#pragma once
#include "Vec2.h"

/// <summary>
/// 操作説明クラス
/// </summary>
class SceneOption
{
public:
	SceneOption();
	virtual ~SceneOption();

	void Init();
	void Update();
	void Draw();

	// シーン遷移フラグ
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// シーン遷移のフラグ true:シーンに移動
	bool m_isSceneTitle;
	// フェードイン、アウト
	int m_fadeAlpha;

	// 操作説明画像
	int m_exHandle;
};

