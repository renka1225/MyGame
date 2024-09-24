#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
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
	m_startTime(kStartTime),
	m_noticeDisPlayFrame(0),
	m_noticePos(VGet(Game::kScreenWidth, 0.0f, 0.0f)),
	m_fadeAlpha(kStartFadeAlpha)
{
	// 敵のcsvファイル読み込み
	LoadEnemy();

	m_pModel = std::make_shared<ManagerModel>();
	m_pCamera = std::make_shared<Camera>();
	m_pBackground = std::make_shared<Background>();
	m_pMap = std::make_shared<Map>();
	m_pPlayer = std::make_shared<Player>(m_pModel, m_pSound, m_pMap);

	m_pEnemy.resize(kEnemyNum);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = std::make_shared<Enemy>(m_pModel, m_enemyPos[i]);
	}

	// スタートSE
	PlaySoundMem(m_pSound->GetStartCountSE(), DX_PLAYTYPE_BACK);
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init()
{
	// マップデータ読み込み
 	m_pMap->Load();
}


/// <summary>
/// 更新
/// </summary>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// フェードアウト
	m_fadeAlpha -= kFadeFrame;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	// 背景の更新
	m_pBackground->Update();
	// プレイヤーの更新
	m_pPlayer->Update(input);
	// カメラの更新
	m_pCamera->Update(m_pPlayer);

	// スタート演出を行う
	if (m_startTime > 0)
	{
		m_startTime--;
		return shared_from_this();
	}

	// 敵の更新
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	// nullptrではないチェック
		{
 			m_pEnemy[i]->Update();

			// プレイヤーの当たり判定
			Rect playerRect = m_pPlayer->GetColRect();
			// 敵の当たり判定
			Rect enemyRect = m_pEnemy[i]->GetColRect();
			if (playerRect.IsCollision(enemyRect))
			{
				PlaySoundMem(m_pSound->GetDamageSE(), DX_PLAYTYPE_BACK);
				//ゲームオーバー画面に遷移
				return std::make_shared<SceneGameover>();
			}
		}
	}

	// BGMを鳴らす
	if (!CheckSoundMem(m_pSound->GetPlayBgm()))
	{
		PlaySoundMem(m_pSound->GetPlayBgm(), DX_PLAYTYPE_BACK);
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

	// プレイヤーの描画
	m_pPlayer->Draw();

	// マップの描画
	m_pMap->Draw();

	// 敵の描画
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			m_pEnemy[i]->Draw();
		}
	}

	// 操作説明の表示
	DrawFormatStringToHandle(kNoticeStartPosX, kStartCountPosY, 0xffd700, m_pFont->GetStartCountFont(), "");

	if (m_startTime > 0)
	{
		// フェードインアウト
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x20b2aa, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		// スタート演出の表示
		StartStaging();
	}
	else
	{
		// フレーム数を秒、ミリ秒に変換する
		int milliSec = m_time * 1000 / 60;
		int sec = (milliSec / 1000) % 90;
		milliSec %= 1000;
		// 経過時間の描画
		DrawFormatStringToHandle(kTimePosX, kTimePosY, 0xffd700, m_pFont->GetTimeFont(), "経過時間 %02d:%03d", sec, milliSec);
		// 時間経過の通知を表示
		DrawNotice();
	}

#if _DEBUG
	// MEMO:デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "プレイ画面");
	// MEMO:中心線
	//DrawLine(Game::kScreenWidth * 0.5f, 0, Game::kScreenWidth * 0.5f, Game::kScreenHeight, 0x0000000, 1);
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
/// スタート演出
/// </summary>
void ScenePlaying::StartStaging()
{
	DrawFormatStringToHandle(kTimePosX, kExPosY, 0xffffff, m_pFont->GetTimeFont(), "SPACEでジャンプ！");	// 操作説明

	if (m_startTime >= kStartCount1)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffd700, m_pFont->GetStartCountFont(), "3");
	}
	if (m_startTime < kStartCount1 && m_startTime >= kStartCount2)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffd700, m_pFont->GetStartCountFont(), "2");
	}
	if (m_startTime <= kStartCount2 && m_startTime > kStartCount3)
	{
		DrawFormatStringToHandle(kStartCountPosX, kStartCountPosY, 0xffd700, m_pFont->GetStartCountFont(), "1");
	}
	if (m_startTime < kStartCount3 && m_startTime >= kStartCount4)
	{
		DrawFormatStringToHandle(kNoticeStartPosX, kStartCountPosY, 0xffd700, m_pFont->GetStartCountFont(), "START!");
	}
}


/// <summary>
/// 時間経過の通知を行う
/// </summary>
void ScenePlaying::UpdateNotice()
{
	m_noticeDisPlayFrame--;
	if (m_noticeDisPlayFrame > 0)
	{
		m_noticePos = VGet(Game::kScreenWidth + (-Game::kScreenWidth * kNoticeMove), 0.0f, 0.0f);	// 通知を右から左に移動
	}
	else
	{
		m_noticeDisPlayFrame = 0;
		m_noticePos = VGet(Game::kScreenWidth, 0.0f, 0.0f);
	}

	if (m_time == kNoticeTime1 || m_time == kNoticeTime2 || m_time == kNoticeTime3 || m_time == kNoticeTime4)	// 20秒ごとに実行
	{
		PlaySoundMem(m_pSound->GetNoticeSE(), DX_PLAYTYPE_BACK);	// SEを鳴らす
		m_noticeDisPlayFrame = kNoticeDisPlayFrame;
	}
}


/// <summary>
/// 時間経過の通知を表示
/// </summary>
void ScenePlaying::DrawNotice()
{
	int textPosX = static_cast<int>(m_noticePos.x);	// テキストの表示位置X

	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime1)
	{
		if (m_time <= kNoticeTime1 + kNoticeStopFrame)
		{
			textPosX = kNoticeTimePosX;
			m_noticePos.x = kNoticeTimePosX;
		}
		else
		{
			textPosX = kNoticeTimePosX - static_cast<int>(m_noticePos.x);
		}
		DrawFormatStringToHandle(textPosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "20秒経過！");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime2)
	{
		if (m_time <= kNoticeTime2 + kNoticeStopFrame)
		{
			textPosX = kNoticeTimePosX;
			m_noticePos.x = kNoticeTimePosX;
		}
		else
		{
			textPosX = kNoticeTimePosX - static_cast<int>(m_noticePos.x);
		}
		DrawFormatStringToHandle(textPosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "40秒経過！");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime3)
	{
		if (m_time <= kNoticeTime3 + kNoticeStopFrame)
		{
			textPosX = kNoticeTimePosX;
			m_noticePos.x = kNoticeTimePosX;
		}
		else
		{
			textPosX = kNoticeTimePosX - static_cast<int>(m_noticePos.x);
		}
		DrawFormatStringToHandle(textPosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "60秒経過！");
	}
	if (m_noticeDisPlayFrame > 0 && m_time >= kNoticeTime4)
	{
		if (m_time <= kNoticeTime4 + kNoticeStopFrame)
		{
			textPosX = kNoticeTimePosX;
			m_noticePos.x = kNoticeTimePosX;
		}
		else
		{
			textPosX = kNoticeTimePosX - static_cast<int>(m_noticePos.x);
		}
		DrawFormatStringToHandle(textPosX, kNoticeTimePosY, 0xffd700, m_pFont->GetTimeFont(), "80秒経過！");
	}
}
