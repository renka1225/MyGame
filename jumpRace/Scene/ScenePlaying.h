#pragma once
#include "SceneBase.h"
#include <memory>

class Player;
class Camera;
class Background;

/// <summary>
/// プレイ画面
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying() {};

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void StartCount();					// スタートカウントを鳴らす
	void StartStaging();				// スタート演出の表示
	void UpdateCommand(Input& input);	// 入力コマンドの更新
	void DrawCommand();					// 入力コマンドの表示

private:
	// ポインタ
	std::shared_ptr<Player> m_pPlayer;			// プレイヤー
	std::shared_ptr<Camera> m_pCamera;			// カメラ
	std::shared_ptr<Background> m_pBackground;	// 背景

	// 入力コマンドの種類
	enum Command
	{
		A,
		B,
		X,
		Y
	};
	int m_nowCommand;	// 現在のコマンド

	int m_startTime;	// スタート時の演出時間
	int m_time;			// 経過時間
	int m_pushCount;	// ボタンを押した回数

private:	// 定数
	static constexpr int kMaxPush = 10;		// 50回ボタン入力を行う

	// スタート演出
	static constexpr int kStartTime = 60 * 4;		// スタート時の演出時間
	static constexpr int kStartCount1 = 60 * 3;		// 1カウント目
	static constexpr int kStartCount2 = 60 * 2;		// 2カウント目
	static constexpr int kStartCount3 = 60;			// 3カウント目
	static constexpr int kStartCount4 = 0;			// startSEを鳴らす
	static constexpr int kStartCountPosX = 500;		// カウント表示位置X
	static constexpr int kStartCountPosY = 400;		// カウント表示位置Y
};