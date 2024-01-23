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
	bool IsSceneSelect() const { return m_isSceneSelect; }
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneRetry;	// リトライ
	bool m_isSceneSelect;	// ステージ選択
	bool m_isSceneTitle;	// タイトル 
};