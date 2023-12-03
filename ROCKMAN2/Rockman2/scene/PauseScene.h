#pragma once
#include "Scene.h"

/// <summary>
/// ポーズ時のシーンクラス
/// </summary>
class PauseScene:public Scene
{
public:
	PauseScene(SceneManager& manager);
	void Update(Pad& pad);
	void Draw();

private:
	// フレーム数
	int m_frame;

	// 更新メンバ関数ポインタ
	using UpdateFunc_t = void (PauseScene::*)(Pad& pad);
	UpdateFunc_t updateFunc_;
	// 描画メンバ関数ポインタ
	using DrawFunc_t = void (PauseScene::*)();
	DrawFunc_t drawFunc_;

	// 更新関数
	void AppearUpdate(Pad&);// 登場状態
	void NormalUpdate(Pad& pad);// 通常状態
	void DisappearUpdate(Pad&);// 退場状態

	// 描画関数
	void ExpandDraw();// 拡張縮小描画
	void NormalDraw();// 通常描画
};

