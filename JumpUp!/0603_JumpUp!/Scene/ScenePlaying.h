#pragma once
#include "SceneBase.h"
#include "DrawDebug.h"

class Physics;
class Player;
class Camera;
class Stage;
class DrawDebug;

/// <summary>
/// プレイ中のシーンクラス
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying();
	virtual void Init();
	void Final();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	std::shared_ptr<Physics> m_pPhysics;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Stage> m_pStage;
	DrawDebug m_pDrawDebug;

#ifdef _DEBUG
	// デバッグ状況
	enum class DebugState
	{
		Normal,	// 通常
		Pause	// ポーズ
	};
	DebugState debugState = DebugState::Normal;
#endif
};
