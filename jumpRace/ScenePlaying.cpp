#include "ScenePlaying.h"
#include "SceneClear.h"
#include "ManagerFont.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying():
	m_nowCommand(A),
	m_time(0),
	m_pushCount(0)
{
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init()
{
	m_nowCommand = GetRand(Y);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// タイム更新
	m_time++;

	// 入力コマンドを更新
	UpdateCommand(input);

	// 50回入力できたらクリア画面に遷移
	if (m_pushCount >= kMaxPush)
	{
		return std::make_shared<SceneClear>();
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
	// 入力コマンドを表示
	DrawCommand();

	// 経過時間の描画
	int milliSec = m_time * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;

#ifdef _DEBUG
	// MEMO:デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "プレイ画面");
	DrawFormatString(0, 20, 0xffffff, "入力回数:%d", m_pushCount);
	DrawFormatString(0, 40, 0xffffff, "タイム %02d:%03d", sec, milliSec);
#endif
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
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == B)
	{
		if (input.IsTriggered("B"))
		{
			m_pushCount++;
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == X)
	{
		if (input.IsTriggered("X"))
		{
			m_pushCount++;
			m_nowCommand = GetRand(Y);
		}
	}
	if (m_nowCommand == Y)
	{
		if (input.IsTriggered("Y"))
		{
			m_pushCount++;
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
		DrawFormatStringToHandle(Game::kScreenWidth * 0.5f, 200, 0xff0000, m_pFont->GetFont(), "A");
	}
	if (m_nowCommand == B)
	{
		DrawFormatStringToHandle(Game::kScreenWidth * 0.5f, 200, 0x00ff00, m_pFont->GetFont(), "B");
	}
	if (m_nowCommand == X)
	{
		DrawFormatStringToHandle(Game::kScreenWidth * 0.5f, 200, 0x0000ff, m_pFont->GetFont(), "X");
	}
	if (m_nowCommand == Y)
	{
		DrawFormatStringToHandle(Game::kScreenWidth * 0.5f, 200, 0xff00ff, m_pFont->GetFont(), "Y");
	}
}
