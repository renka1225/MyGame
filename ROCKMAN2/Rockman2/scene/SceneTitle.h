#pragma once

/// <summary>
///  タイトルシーンのクラス
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	void Draw();
	void End();

	// シーンを終了させるか
	bool IsSceneEnd() const { return m_isSceneEnd; }

private:
	// シーン終了のフラグ true:終了
	bool m_isSceneEnd;

	// ロゴ
	int m_logoHandle;
};

