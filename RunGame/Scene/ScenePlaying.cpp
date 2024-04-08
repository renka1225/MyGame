#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "ManagerFont.h"
#include "ManagerModel.h"
#include "Background.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Input.h"
#include "Rect.h"
#include "Game.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>


/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying():
	m_time(0),
	m_noticeDisPlayFrame(0)
{
	m_pModel = std::make_shared<ManagerModel>();
	m_pCamera = std::make_shared<Camera>();
	m_pBackground = std::make_shared<Background>();
	m_pMap = std::make_shared<Map>();
	m_pPlayer = std::make_shared<Player>(m_pModel, m_pMap);

	m_pEnemy.resize(kEnemyNum);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = std::make_shared<Enemy>(m_pModel);
	}
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init()
{
	m_fadeAlpha = kStartFadeAlpha;

	// マップデータ読み込み
	m_pMap->Init("data/file/map.fmf");
	// 敵のcsvファイル読み込み
	LoadEnemy();
	
	m_enemyPos.resize(kEnemyNum);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->Init(m_enemyPos[i]);
	}
}


/// <summary>
/// 更新
/// </summary>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	m_fadeAlpha -= kFadeFrame;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}
	
	// タイム更新
	m_time++;
	// 20秒ごとに時間経過の通知を表示する
	UpdateNotice();

	// クリア画面に遷移
	if (m_time >= kClearTime)
	{
		return std::make_shared<SceneClear>();
	}

	// 背景の更新
	m_pBackground->Update();
	// プレイヤーの更新
	m_pPlayer->Update(input);
	// カメラの更新
	m_pCamera->Update(m_pPlayer);
	// 敵の更新
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// 敵の更新
		if (m_pEnemy[i])
		{
			m_pEnemy[i]->Update();
		}

		// プレイヤーの当たり判定
		Rect playerRect = m_pPlayer->GetColRect();
		// 敵の当たり判定
		Rect enemyRect = m_pEnemy[i]->GetColRect();
		if (playerRect.IsCollision(enemyRect))
		{
			// TODO:ゲームオーバー画面に遷移
			//return std::make_shared<SceneGameover>();

#ifdef _DEBUG
			DrawString(0, 80, "当たった", 0xff0000);
#endif
		}
	}

#if _DEBUG
	// MEMO:デバック用コマンド
	if (input.IsTriggered("debug"))
	{
		return std::make_shared<SceneClear>();
	}
	else if (input.IsTriggered("debug2"))
	{
		return std::make_shared<SceneGameover>();
	}
#endif

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void ScenePlaying::Draw()
{
	// 背景の描画
	m_pBackground->Draw();

	// 敵の描画
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if(m_pEnemy[i])
		{
			m_pEnemy[i]->Draw();
		}
	}

	// プレイヤーの描画
	m_pPlayer->Draw();

	// マップの描画
	//m_pMap->Draw();

	// 経過時間の描画
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	DrawFormatStringToHandle(kTimePosX, kTimePosY, 0xffd700, m_pFont->GetTimeFont(), "経過時間 %02d:%03d", sec, milliSec);
	// 時間経過の通知を表示
	DrawNotice();

	// フェードインアウト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x0e0918, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "プレイ画面");
#endif
}


/// <summary>
/// csvファイル読み込み
/// </summary>
void ScenePlaying::LoadEnemy()
{
	std::ifstream file;
	file.open("data/file/enemy.csv");
	if (!file.is_open())	// ファイル読み込み失敗時
	{
		printfDx("ファイル読み込み失敗\n");
	}
	else
	{
		std::string path;	// 読み取り元
		while (std::getline(file, path))
		{
			std::istringstream istream(path);
			std::string line;
			VECTOR pos = VGet(0.0f, 0.0f, 0.0f);

			if (std::getline(istream, line, ',') &&
				std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.x) &&
				std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.y) &&
				std::getline(istream, line, ',') && sscanf_s(line.c_str(), "%f", &pos.z))
			{
				m_enemyPos.push_back(pos);
			}
		}
	}
	file.close();
}


/// <summary>
/// 時間経過の通知を行う
/// </summary>
void ScenePlaying::UpdateNotice()
{
	m_noticeDisPlayFrame--;
	if (m_noticeDisPlayFrame < 0)
	{
		m_noticeDisPlayFrame = 0;
	}
	if (m_time == kNoticeTime1)
	{
		m_noticeDisPlayFrame = kNoticeDisPlayFrame;
	}
	if (m_time == kNoticeTime2)
	{
		m_noticeDisPlayFrame = kNoticeDisPlayFrame;
	}
	if (m_time == kNoticeTime3)
	{
		m_noticeDisPlayFrame = kNoticeDisPlayFrame;
	}
	if (m_time == kNoticeTime4)
	{
		m_noticeDisPlayFrame = kNoticeDisPlayFrame;
	}
}


/// <summary>
/// 時間経過の通知を表示
/// </summary>
void ScenePlaying::DrawNotice()
{
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime1 && m_time < kNoticeTime2)
	{
		DrawFormatStringToHandle(kNoticeTimePosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "20秒経過！");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime2 && m_time < kNoticeTime3)
	{
		DrawFormatStringToHandle(kNoticeTimePosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "40秒経過！");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime3 && m_time < kNoticeTime4)
	{
		DrawFormatStringToHandle(kNoticeTimePosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "60秒経過！");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime4)
	{
		DrawFormatStringToHandle(kNoticeTimePosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "80秒経過！");
	}
}
