#include "DxLib.h"
#include "Input.h"
#include "Game.h"
#include "UI.h"
#include "UIBattle.h"
#include "Sound.h"
#include "Light.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStageBase.h"

namespace
{
	const char* kClearBackHandlePath = "data/UI/clearBack.png";	  // 画像のパス
	const VECTOR kPlayerInitPos = VGet(2600.0f, 69.0f, 4240.0f);  // プレイヤーの初期位置
	const VECTOR kEnemyInitPos = VGet(2660, 69.0f, 4280.0f);	  // 敵の初期位置
	constexpr int kChangeColorTime = 220;						  // 画面の表示を変更する時間
	constexpr int kClearStagingTime = 240;						  // クリア演出の時間
	constexpr int kNextBattleTime = 150;						  // 次の試合が始まるまでの時間
	constexpr int kBattleEndSoundTime = 60;						  // コングのSEを鳴らす時間
	constexpr int kClearBackColor = 0x0f2699;					  // クリア時の背景色
	constexpr int kMULAPal = 200;								  // 乗算ブレンド値
	constexpr int kAddPal = 80;									  // 加算ブレンド値

	constexpr int kStartFadeAlpha = 255; // スタート時のフェード値
	constexpr int kFadeFrame = 8;		 // フェード変化量
}


/// <summary>
/// コンストラクタ
/// </summary>
SceneStageBase::SceneStageBase() :
	m_battleNum(0),
	m_nextBattleTime(kNextBattleTime),
	m_clearStagingTime(kClearStagingTime),
	m_elapsedTime(0),
	m_isPause(false)
{
	m_fadeAlpha = kStartFadeAlpha;
	m_pUIBattle = std::make_shared<UIBattle>();
	Light::SetLight();
	m_clearBackHandle = LoadGraph(kClearBackHandlePath);
}


/// <summary>
/// 引数つきコンストラクタ
/// </summary>
/// <param name="pPlayer">プレイヤー参照</param>
/// <param name="pCamera">カメラ参照</param>
/// <param name="pStage">ステージ参照</param>
SceneStageBase::SceneStageBase(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage):
	m_pPlayer(pPlayer),
	m_pCamera(pCamera),
	m_pStage(pStage),
	m_pEnemy(nullptr),
	m_battleNum(0),
	m_clearStagingTime(0),
	m_nextBattleTime(0),
	m_elapsedTime(0),
	m_isPause(false),
	m_clearBackHandle(-1)
{
}


/// <summary>
/// デストラクタ
/// </summary>
SceneStageBase::~SceneStageBase()
{
	Light::DeleteLight();
	DeleteGraph(m_clearBackHandle);
}


/// <summary>
/// 初期化
/// </summary>
void SceneStageBase::Init()
{
	if (!m_isPause)
	{
		m_pPlayer->Init(kPlayerInitPos);
		m_pCamera->Init();
		m_pEnemy->Init(kEnemyInitPos);
	}

	m_isPause = false;
}


/// <summary>
/// 描画
/// </summary>
void SceneStageBase::Draw()
{
	m_pStage->Draw();			  // ステージ描画

	m_pPlayer->Draw();			  // プレイヤー描画
	m_pEnemy->Draw();			  // 敵描画

	m_pUIBattle->DrawOperation(); // 操作説明を表示

	// クリア時画面の色味を変える
	if (m_clearStagingTime < kClearStagingTime && m_clearStagingTime >= 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, kMULAPal);
		DrawGraph(0, 0, m_clearBackHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBlendMode(DX_BLENDMODE_ADD, kAddPal);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kClearBackColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawFade();	// フェードインアウト描画
}


/// <summary>
/// クリア演出を行う
/// </summary>
void SceneStageBase::ClearStaging()
{
	// SEを鳴らす
	if (m_clearStagingTime >= kClearStagingTime - kBattleEndSoundTime)
	{
		if (!CheckSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kBattleEnd)]))
		{
			PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kBattleEnd)], DX_PLAYTYPE_BACK);
		}
	}
	else
	{
		if (!CheckSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)]))
		{
			PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)], DX_PLAYTYPE_BACK);
		}
	}

	if (m_clearStagingTime >= kClearStagingTime - kChangeColorTime)
	{
		// 画面の色を変える
		//SetLightDifColor(GetColorF(0.0f, 0.3f, 0.5f, 0.0f));

		m_clearStagingTime--;
		return;
	}

	// クリア演出をリセット
	m_clearStagingTime = 0;
	//SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
	StopSoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kClearCheers)]);
}


/// <summary>
/// 敵を倒して次試合が始まる前の処理
/// </summary>
void SceneStageBase::UpdateNextBattle()
{
	m_nextBattleTime = kNextBattleTime;
	m_clearStagingTime = kClearStagingTime;
	// プレイヤーの位置、カメラ位置を最初の状態に戻す
	m_pPlayer->Recovery();
	Init();

	FadeIn(kFadeFrame); // フェードイン
}