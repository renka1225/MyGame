#pragma once
#include "SceneBase.h"
#include "DxLib.h"
#include <vector>

class ManagerFont;
class ManagerModel;
class Background;
class Map;
class Player;
class Enemy;
class Camera;

/// <summary>
/// プレイ中のシーン
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
	void LoadEnemy();		// 敵情報読み込み
	void StartStaging();	// スタート演出の表示
	void UpdateNotice();	// 時間経過の通知を行う
	void DrawNotice();		// 時間経過の通知を表示

private:
	// ポインタ
	std::shared_ptr<ManagerModel> m_pModel;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<Background> m_pBackground;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;

	std::vector<VECTOR> m_enemyPos;	// 敵位置

	int m_time;					// 時間
	int m_startTime;			// スタート時の演出時間
	int m_noticeDisPlayFrame;	// 経過時間の通知を表示する時間

	VECTOR m_noticePos;			// 通知の表示位置
	int m_fadeAlpha;			// フェードのα値

private:	// 定数
	static constexpr int kEnemyNum = 100;				// 最大敵数
	static constexpr int kClearTime = 60 * 90;			// ゲーム時間

	//スタート時にカウントを表示
	static constexpr int kStartTime = 60 * 4;			// スタート時の演出時間
	static constexpr int kStartCount1 = 60 * 3;			// 1カウント目
	static constexpr int kStartCount2 = 60 * 2;			// 2カウント目
	static constexpr int kStartCount3 = 60;				// 3カウント目
	static constexpr int kStartCount4 = 0;				// startの文字表示
	static constexpr int kStartCountPosX = 910;			// カウント表示位置X
	static constexpr int kNoticeStartPosX = 670;		// startの文字表示位置X
	static constexpr int kStartCountPosY = 500;			// カウント表示位置Y
	static constexpr int kExPosY = 380;					// 操作説明表示位置Y

	// 20秒ごとに時間経過の通知を表示する
	static constexpr int kNoticeTime1 = 20 * 60;
	static constexpr int kNoticeTime2 = 40 * 60;
	static constexpr int kNoticeTime3 = 60 * 60;
	static constexpr int kNoticeTime4 = 80 * 60;
	static constexpr int kNoticeDisPlayFrame = 3 * 60;	// 通知を表示する時間
	static constexpr int kNoticeMoveFrame = 30;			// 通知の移動時間
	static constexpr int kNoticeStopFrame = 160;		// 通知の停止時間
	static constexpr float kNoticeMove = 6.0f;			// 通知表示の移動量
	static constexpr int kTimePosX = 620;				// 時間表示位置X
	static constexpr int kTimePosY = 100;				// 時間表示位置Y
	static constexpr int kNoticeTimePosX = 800;			// 時間経過の通知表示位置X
	static constexpr int kNoticeTimePosY = 190;			// 時間経過の通知表示位置Y

	// フェード
	static constexpr int kStartFadeAlpha = 150;			// スタート時のフェードα値
	static constexpr int kFadeFrame = 8;				// フェード変化量
};