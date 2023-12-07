#pragma once

/// <summary>
/// ゲームオーバーのクラス
/// </summary>
class SceneGameOver
{
public:
	SceneGameOver();
	~SceneGameOver();

	void Init();
	void Update();
	void Draw();
	void End();

	// シーンを終了させるか
	bool IsSceneEnd() const { return m_isSceneEnd; }

private:
	// シーンを終了させるフラグ true:終了
	bool m_isSceneEnd;
};

