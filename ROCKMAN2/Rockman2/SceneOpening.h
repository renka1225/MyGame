#pragma once

/// <summary>
/// オープニング再生クラス
/// </summary>
class SceneOpening
{
public:
	SceneOpening();
	~SceneOpening();
	void Init();
	void Update();

	// シーン遷移のフラグ
	bool IsSceneStart() const { return m_isSceneStart; }

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneStart;

	// 動画再生時間
	int m_moveFrame;

	// 動画ファイル
	int m_opMove;
};

