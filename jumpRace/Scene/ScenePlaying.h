#pragma once
#include "SceneBase.h"
#include "DxLib.h"
#include <memory>

class ManagerModel;
class ManagerLight;
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
	virtual ~ScenePlaying();

	virtual void Init(std::shared_ptr<ManagerResult> pResult);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void StartStaging();				// スタート演出の表示
	void ClearStaging();				// クリア演出の表示
	void UpdateCommand(Input& input);	// 入力コマンドの更新
	void PushCorrect();					// 正しいボタンを押せた際の処理
	void DrawCommand();					// 入力コマンドの表示

private:
	// ポインタ
	std::shared_ptr<ManagerModel> m_pModel;		// 3Dモデル
	std::shared_ptr<ManagerLight> m_pLight;		// ライト
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
	int m_nowCommand;		// 現在のコマンド

	int m_startTime;		// スタート時の演出時間
	int m_clearStagingTime;	// クリア時の演出時間
	int m_time;				// 経過時間
	int m_stopTime;			// 動けない時間
	int m_pushCount;		// ボタンを押した回数
	int m_isPush;			// ボタンを押せる状態か

	int m_startCount3;		// スタートカウントのUI
	int m_startCount2;		// スタートカウントのUI
	int m_startCount1;		// スタートカウントのUI

	int m_shadowMapHandle;		// シャドウマップハンドル
	VECTOR m_shadowMapMinPos;	 // シャドウマップに描画する範囲
	VECTOR m_shadowMapMaxPos;	 // シャドウマップに描画する範囲

private:	// 定数
	static constexpr int kMaxPush = 30;	// 30回ボタン入力を行う

	// スタート演出
	static constexpr int kStartTime = 240;				// スタート時の演出時間
	static constexpr int kStartCount1 = 180;			// 1カウント目
	static constexpr int kStartCount2 = 120;			// 2カウント目
	static constexpr int kStartCount3 = 60;				// 3カウント目
	static constexpr int kStartCount4 = 0;				// startSEを鳴らす
	static constexpr int kStartCountPosX = 600;			// カウント表示位置X
	static constexpr int kStartCountPosY = 250;			// カウント表示位置Y

	// クリア演出
	static constexpr int kClearStagingTime = 300;		// クリア時の演出時間
	static constexpr int kClearSEChangeTime = 270;		// クリアSEを変える時間
	
	static constexpr int kCommandSize = 16;				// 入力コマンドのサイズ
	static constexpr float kCommandScale = 4.0f;		// 入力コマンドの拡大率
	static constexpr int kCommandPosX = 645;			// 入力コマンド表示位置X
	static constexpr int kCommandPosY = 250;			// 入力コマンド表示位置Y
	static constexpr int kTimePosX = 560;				// タイム表示位置X
	static constexpr int kTimePosY = 110;				// タイム表示位置Y
	static constexpr int kTimeEdgePosX = 558;			// タイムのテキスト縁取り位置X
	static constexpr int kTimeEdgePosY = 111;			// タイムのテキスト縁取り位置Y

	static constexpr int kStopTime = 30;				// ミス時に動けなくなる時間
	static constexpr int kNextCommandTime = 5;			// 次のコマンドを表示するまでの時間

	static constexpr int kStartFadeAlpha = 255;			// スタート時のフェードα値

	// シャドウマップ関連
	static constexpr int kMakeShadowMapSize = 1024;			// 作成するシャドウマップのサイズ
	// シャドウマップで想定するライトの方向
	static constexpr float kShadowMapLightDirX = 0.0f;		// X方向
	static constexpr float kShadowMapLightDirY = -10.0f;	// Y方向
	static constexpr float kShadowMapLightDirZ = 30.0f;		// Z方向
	// シャドウマップに描画する最小範囲
	static constexpr float kShadowMapMinPosX = -30.0f;		// X座標
	static constexpr float kShadowMapMinPosY = 0.0f;		// Y座標
	static constexpr float kShadowMapMinPosZ = -20.0f;		// Z座標
	// シャドウマップに描画する最大範囲
	static constexpr float kShadowMapMaxPosX = 30.0f;		// X座標
	static constexpr float kShadowMapMaxPosY = 30.0f;		// Y座標
	static constexpr float kShadowMapMaxPosZ = 20.0f;		// Z座標
};