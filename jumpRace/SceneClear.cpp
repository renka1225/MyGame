#include "SceneClear.h"
#include "SceneTitle.h"
#include "ManagerResult.h"
#include "Input.h"
#include "Game.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneClear::SceneClear(int time):
	m_clearTime(time)
{
}


/// <summary>
/// デストラクタ
/// </summary>
SceneClear::~SceneClear()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneClear::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	if (input.IsTriggered("sceneChange"))
	{
		return std::make_shared<SceneTitle>();
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneClear::Draw()
{
	// クリアタイム表示
	int milliSec = m_clearTime * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	DrawFormatString(Game::kScreenWidth * 0.5f, 100, 0xffffff, "クリアタイム:%02d:%03d", sec, milliSec);

#ifdef _DEBUG
	// デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "クリア画面");
#endif
}
