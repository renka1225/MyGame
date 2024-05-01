#include "ScenePlaying.h"
#include "SceneClear.h"
#include "ManagerModel.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "ManagerResult.h"
#include "Player.h"
#include "Camera.h"
#include "Background.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying(): 
	m_nowCommand(A),
	m_startTime(0),
	m_time(0),
	m_pushCount(0)
{
	m_pModel = std::make_shared<ManagerModel>();
	m_pPlayer = std::make_shared<Player>(m_pModel);
	m_pCamera = std::make_shared<Camera>(m_pPlayer);
	m_pBackground = std::make_shared<Background>(m_pModel);
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
	//PlaySoundMem(m_pSound->GetCountSE(), DX_PLAYTYPE_BACK);	// カウントダウン
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// モデルの更新
	m_pModel->Update();
	// 背景の更新
	m_pBackground->Update();
	// プレイヤーの更新
	m_pPlayer->Update(input);
	// カメラの更新
	m_pCamera->Update();

	// スタート演出を行う
	if (m_startTime > 0)
	{
		m_startTime--;
		return shared_from_this();
	}

	// タイム更新
	m_time++;

	// 入力コマンドを更新
	UpdateCommand(input);

	// 50回入力できたらクリア画面に遷移
	if (m_pushCount >= kMaxPush)
	{
		m_pResult->Save(m_time);	// クリアタイムを保存
		return std::make_shared<SceneClear>(m_time);
	}

#ifdef _DEBUG
	// MEMO:デバッグ用
	if (input.IsTriggered("sceneChange"))
	{
		return std::make_shared<SceneClear>(m_time);
	}
#endif

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void ScenePlaying::Draw()
{
	// 背景描画
	m_pBackground->Draw();
	// モデル描画
	m_pModel->Draw();

	// 経過時間の描画
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	DrawFormatStringToHandle(580, 80, 0xffffff, m_pFont->GetTimeFont(), "%02d:%03d", sec, milliSec);

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
		// スタート演出の表示
		StartStaging();
	}
	else
	{
		// 入力コマンドを表示
		DrawCommand();
	}

	// プレイヤーの描画
	m_pPlayer->Draw();
}


/// <summary>
/// スタート演出の表示
/// </summary>
void ScenePlaying::StartStaging()
{
	if (m_startTime >= kStartCount1)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffffff, m_pFont->GetStartCountFont(), "3");
	}
	if (m_startTime < kStartCount1 && m_startTime >= kStartCount2)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffffff, m_pFont->GetStartCountFont(), "2");
	}
	if (m_startTime <= kStartCount2 && m_startTime > kStartCount3)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffffff, m_pFont->GetStartCountFont(), "1");
	}
}


/// <summary>
/// 入力コマンド更新
/// </summary>
void ScenePlaying::UpdateCommand(Input& input)
{
	if (m_nowCommand == A)
	{
		if (input.IsTriggered("A"))
		{
			m_pushCount++;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == B)
	{
		if (input.IsTriggered("B"))
		{
			m_pushCount++;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == X)
	{
		if (input.IsTriggered("X"))
		{
			m_pushCount++;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == Y)
	{
		if (input.IsTriggered("Y"))
		{
			m_pushCount++;
			m_pPlayer->Move();
			m_nowCommand = GetRand(Y);
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