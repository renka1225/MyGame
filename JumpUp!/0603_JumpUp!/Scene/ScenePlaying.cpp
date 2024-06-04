#include "DxLib.h"
#include "MyLib.h"
#include "ScenePlaying.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying()
{
	m_pPhysics = std::make_shared<Physics>();
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
	m_pStage = std::make_shared<Stage>();
}


/// <summary>
/// デストラクタ
/// </summary>
ScenePlaying::~ScenePlaying()
{
	// 処理なし
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init()
{
	m_pPlayer->Init(m_pPhysics);
	m_pCamera->Init();
	m_pStage->Init(m_pPhysics);
}


/// <summary>
/// 終了処理
/// </summary>
void ScenePlaying::Final()
{
	m_pPlayer->Final(m_pPhysics);
	m_pStage->Final(m_pPhysics);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
#ifdef _DEBUG
	// デバッグモード
	// Pキーでポーズ、ポーズ中にPでコマ送り
	if (debugState == DebugState::Normal && input.IsPressing("debug_pause"))
	{
		debugState = DebugState::Pause;
	}
	if (debugState == DebugState::Pause && input.IsPressing("debug_enter"))
	{
		debugState = DebugState::Normal;
	}
	if(debugState != DebugState::Pause || input.IsPressing("debug_pause"))
	{
#endif

		// カメラ更新
		m_pCamera->Update(input, *m_pPlayer);

		// ステージ更新
		m_pStage->Update();

		// プレイヤー更新
		m_pPlayer->SetCameraAngle(m_pCamera->GetAngle());
		m_pPlayer->Update(input, *m_pStage);

		// 物理挙動更新
		m_pPhysics->Update();
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void ScenePlaying::Draw()
{
#ifdef _DEBUG		// デバッグ表示
	// 現在のシーン
	DrawFormatString(0, 0, 0xffffff, "プレイ画面");
	// グリッド表示
	m_pDrawDebug.DrawGrid();
#endif

	// ステージ描画
	m_pStage->Draw(m_pDrawDebug);

	// プレイヤー描画
	m_pPlayer->Draw(m_pDrawDebug);
}
