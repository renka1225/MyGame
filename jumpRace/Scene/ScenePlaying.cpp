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
void ScenePlaying::Init()
{
	m_pBackground->Init();
	m_pResult->Load();
	m_nowCommand = GetRand(Y);
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
		//StartCount();
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
		return std::make_shared<SceneClear>();
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

	// 経過時間の描画
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;

#ifdef _DEBUG
	// MEMO:XYZ軸デバック表示
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0.0f, 0), VGet(lineSize, 0.0f, 0.0f), 0xff0000);
	DrawLine3D(VGet(0.0f, -lineSize, 0.0f), VGet(0.0f, lineSize, 0.0f), 0x00ff00);
	DrawLine3D(VGet(0.0f, 0.0f, -lineSize), VGet(0.0f, 0.0f, lineSize), 0x0000ff);

	// MEMO:デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "プレイ画面");
	DrawFormatString(0, 20, 0xffffff, "入力回数:%d", m_pushCount);
	DrawFormatString(0, 40, 0xffffff, "タイム %02d:%03d", sec, milliSec);
#endif

	// プレイヤーの描画
	m_pPlayer->Draw();
}


/// <summary>
/// スタートカウントを鳴らす
/// </summary>
void ScenePlaying::StartCount()
{
	if (m_startTime >= kStartCount1)
	{
		PlaySoundMem(m_pSound->GetCount3SE(), DX_PLAYTYPE_BACK);
	}
	if (m_startTime < kStartCount1 && m_startTime >= kStartCount2)
	{
		PlaySoundMem(m_pSound->GetCount2SE(), DX_PLAYTYPE_BACK);
	}
	if (m_startTime <= kStartCount2 && m_startTime > kStartCount3)
	{
		PlaySoundMem(m_pSound->GetCount1SE(), DX_PLAYTYPE_BACK);
	}
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
	if (m_nowCommand == A)
	{
		DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5f), 200, 0xff0000, m_pFont->GetFont(), "A");
	}
	if (m_nowCommand == B)
	{
		DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5f), 200, 0x00ff00, m_pFont->GetFont(), "B");
	}
	if (m_nowCommand == X)
	{
		DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5f), 200, 0x0000ff, m_pFont->GetFont(), "X");
	}
	if (m_nowCommand == Y)
	{
		DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5f), 200, 0xff00ff, m_pFont->GetFont(), "Y");
	}
}
