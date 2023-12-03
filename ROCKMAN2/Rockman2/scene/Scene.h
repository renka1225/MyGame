#pragma once

class Pad;
class SceneManager;

/// <summary>
/// シーン基底クラス
/// </summary>
class Scene
{
protected:
	SceneManager& m_manager; // シーン管理クラスの参照

public:
	// 生成時にSceneManagerの参照を受け取る
	Scene(SceneManager& manager);

	// シーンの更新
	virtual void Update(Pad& pad) = 0;

	// シーンの描画
	virtual void Draw() = 0;
};

