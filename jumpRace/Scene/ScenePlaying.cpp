#include "ScenePlaying.h"
#include "SceneClear.h"
#include "ManagerModel.h"
#include "ManagerLight.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Player.h"
#include "Camera.h"
#include "Background.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying() :
	m_nowCommand(A),
	m_startTime(kStartTime),
	m_clearStagingTime(kClearStagingTime),
	m_time(0),
	m_stopTime(0),
	m_pushCount(0),
	m_isPush(true)
{
	m_pModel = std::make_shared<ManagerModel>();
	m_pLight = std::make_shared<ManagerLight>();
	m_pPlayer = std::make_shared<Player>(m_pModel);
	m_pCamera = std::make_shared<Camera>(m_pPlayer);
	m_pBackground = std::make_shared<Background>(m_pModel);

	m_startCount3 = LoadGraph("data/UI/3.png");
	m_startCount2 = LoadGraph("data/UI/2.png");
	m_startCount1 = LoadGraph("data/UI/1.png");

	m_fadeAlpha = kStartFadeAlpha;
	m_pLight->CreateDirLight();	// ディレクショナルライトを作成
}


/// <summary>
/// デストラクタ
/// </summary>
ScenePlaying::~ScenePlaying()
{
	m_pLight->DeleteDirLight();
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init(std::shared_ptr<ManagerResult> pResult)
{
	m_pResult = pResult;
	m_pBackground->Init();
	m_pResult->Load();
	m_nowCommand = GetRand(Y);
	PlaySoundMem(m_pSound->GetCountSE(), DX_PLAYTYPE_BACK);	// カウントダウン
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	FadeOut();		// フェードアウト

	m_pModel->Update();			// モデル更新
	m_pBackground->Update();	// 背景更新
	m_pCamera->Update();		// カメラ更新
	m_pPlayer->Update(input);	// プレイヤー更新

	// スタート演出を行う
	if (m_startTime > 0)
	{
		m_startTime--;
		return shared_from_this();
	}

	// クリア演出後、クリア画面に移動
	if (m_clearStagingTime < 0)
	{
		m_pResult->Save(m_time);	// クリアタイムを保存
		FadeIn();	// フェードイン
		return std::make_shared<SceneClear>(m_time);
	}

	// クリアしたらクリア演出を行う
	if (m_pushCount >= kMaxPush)
	{
		StopSoundMem(m_pSound->GetPlayBgm());
		ClearStaging();
		return shared_from_this();
	}

	// BGMを鳴らす
	if (!CheckSoundMem(m_pSound->GetPlayBgm()))
	{
		PlaySoundMem(m_pSound->GetPlayBgm(), DX_PLAYTYPE_LOOP);
	}

	// タイム更新
	m_time++;
	m_stopTime--;
	if (m_stopTime <= 0)
	{
		m_stopTime = 0;
		m_isPush = true;
	}

	// 入力コマンドを更新
	UpdateCommand(input);

#ifdef _DEBUG
	// MEMO:デバッグ用
	if (input.IsTriggered("sceneChange"))
	{
		m_pushCount = kMaxPush;
	}
#endif

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void ScenePlaying::Draw()
{
	m_pBackground->Draw(); // 背景描画
	m_pModel->Draw();	   // モデル描画

	// 経過時間の描画
	m_pConversionTime->Change(m_time);	// タイム変換
	DrawFormatStringToHandle(kTimeEdgePosX, kTimeEdgePosY, 0x2e3b40, m_pFont->GetTimeFontEdge(),
		"%02d:%03d", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());	// 縁取り表示
	DrawFormatStringToHandle(kTimePosX, kTimePosY, 0xffffff, m_pFont->GetTimeFont(),
		"%02d:%03d", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

#ifdef _DEBUG
	// MEMO:XYZ軸デバック表示
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0.0f, 0), VGet(lineSize, 0.0f, 0.0f), 0xff0000);
	DrawLine3D(VGet(0.0f, -lineSize, 0.0f), VGet(0.0f, lineSize, 0.0f), 0x00ff00);
	DrawLine3D(VGet(0.0f, 0.0f, -lineSize), VGet(0.0f, 0.0f, lineSize), 0x0000ff);

	// MEMO:デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "プレイ画面");
	DrawFormatString(0, 20, 0xffffff, "入力回数:%d", m_pushCount);
#endif

	if (m_startTime > 0)
	{
		DrawFade();		// フェード
		StartStaging();	// スタート演出の表示
	}
	else if(m_pushCount < kMaxPush)
	{
		DrawCommand();	// 入力コマンドを表示
	}

	m_pPlayer->Draw();	// プレイヤーの描画
}


/// <summary>
/// スタート演出の表示
/// </summary>
void ScenePlaying::StartStaging()
{
	if (m_startTime >= kStartCount1)
	{
		DrawGraph(kStartCountPosX, kStartCountPosY, m_startCount3, true);
	}
	if (m_startTime < kStartCount1 && m_startTime >= kStartCount2)
	{
		DrawGraph(kStartCountPosX, kStartCountPosY, m_startCount2, true);
	}
	if (m_startTime <= kStartCount2 && m_startTime > kStartCount3)
	{
		DrawGraph(kStartCountPosX, kStartCountPosY, m_startCount1, true);
	}
}


/// <summary>
/// クリア演出の表示
/// </summary>
void ScenePlaying::ClearStaging()
{
	m_clearStagingTime--;

	//m_pPlayer->ClearStaging();	// プレイヤーの演出

	if (!CheckSoundMem(m_pSound->GetClearSE()) && m_clearStagingTime >= kClearSEChangeTime)
	{
		PlaySoundMem(m_pSound->GetClearSE(), DX_PLAYTYPE_BACK);
	}
	if (!CheckSoundMem(m_pSound->GetClearStagingBgm()) && m_clearStagingTime <= kClearSEChangeTime)
	{
		PlaySoundMem(m_pSound->GetClearStagingBgm(), DX_PLAYTYPE_BACK);
	}
}


/// <summary>
/// 入力コマンド更新
/// </summary>
void ScenePlaying::UpdateCommand(Input& input)
{
	if (m_nowCommand == A)
	{
		if (input.IsTriggered("A") && m_isPush)
		{
			PlaySoundMem(m_pSound->GetJumpSE(), DX_PLAYTYPE_BACK);
			m_pushCount++;
			m_stopTime = kNextCommandTime;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
		else if ((input.IsTriggered("B") || input.IsTriggered("X") || input.IsTriggered("Y")))
		{
			m_isPush = false;

		}
	}
	if (m_nowCommand == B)
	{
		if (input.IsTriggered("B") && m_isPush)
		{
			PlaySoundMem(m_pSound->GetJumpSE(), DX_PLAYTYPE_BACK);
			m_pushCount++;
			m_stopTime = kNextCommandTime;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
		else if ((input.IsTriggered("A") || input.IsTriggered("X") || input.IsTriggered("Y")))
		{
			m_isPush = false;
		}
	}
	if (m_nowCommand == X)
	{
		if (input.IsTriggered("X") && m_isPush)
		{
			PlaySoundMem(m_pSound->GetJumpSE(), DX_PLAYTYPE_BACK);
			m_pushCount++;
			m_stopTime = kNextCommandTime;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
		else if (input.IsTriggered("A") || input.IsTriggered("B") || input.IsTriggered("Y"))
		{
			m_isPush = false;
		}
	}
	if (m_nowCommand == Y)
	{
		if (input.IsTriggered("Y") && m_isPush)
		{
			PlaySoundMem(m_pSound->GetJumpSE(), DX_PLAYTYPE_BACK);
			m_pushCount++;
			m_stopTime = kNextCommandTime;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
		else if((input.IsTriggered("A") || input.IsTriggered("B") || input.IsTriggered("X")))
		{
			m_isPush = false;
		}
	}

	// ボタンを押し間違えた場合
	if (!m_isPush && m_stopTime <= 0)
	{
		m_stopTime = kStopTime;
		if (!CheckSoundMem(m_pSound->GetMissSE()))
		{
			PlaySoundMem(m_pSound->GetMissSE(), DX_PLAYTYPE_BACK);
		}
	}
}


/// <summary>
/// 入力コマンドを表示
/// </summary>
void ScenePlaying::DrawCommand()
{
	int srcX = 0;	// 画像の切り出し位置X
	int srcY = 0;	// 画像の切り出し位置Y

	if (m_nowCommand == A)
	{
		srcY = kCommandSize * A;
		DrawRectRotaGraph(kCommandPosX, kCommandPosY, srcX, srcY, kCommandSize, kCommandSize, kCommandScale, 0.0f, m_buttonHandle, true);
	}
	if (m_nowCommand == B)
	{
		srcY = kCommandSize * B;
		DrawRectRotaGraph(kCommandPosX, kCommandPosY, srcX, srcY, kCommandSize, kCommandSize, kCommandScale, 0.0f, m_buttonHandle, true);
	}
	if (m_nowCommand == X)
	{
		srcY = kCommandSize * X;
		DrawRectRotaGraph(kCommandPosX, kCommandPosY, srcX, srcY, kCommandSize, kCommandSize, kCommandScale, 0.0f, m_buttonHandle, true);
	}
	if (m_nowCommand == Y)
	{
		srcY = kCommandSize * Y;
		DrawRectRotaGraph(kCommandPosX, kCommandPosY, srcX, srcY, kCommandSize, kCommandSize, kCommandScale, 0.0f, m_buttonHandle, true);
	}
}