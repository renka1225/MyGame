#include "SceneResult.h"
#include "SceneTitle.h"
#include "ManagerFont.h"
#include "ManagerResult.h"
#include "ConversionTime.h"
#include "Input.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneResult::SceneResult()
{
}


/// <summary>
/// デストラクタ
/// </summary>
SceneResult::~SceneResult()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneResult::Init(std::shared_ptr<ManagerResult> pResult)
{
	m_pResult = pResult;
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneResult::Update(Input& input)
{
	if (input.IsTriggered("sceneChange"))
	{
		return std::make_shared<SceneTitle>();		//タイトル画面に移動
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneResult::Draw()
{
#ifdef _DEBUG
	// MEMO:デバッグ表示
	DrawString(0, 0, "結果確認画面", 0xffffff);
#endif

	DrawRanking();	// ランキング表示
}


/// <summary>
/// ランキング表示
/// </summary>
void SceneResult::DrawRanking()
{
	for (int i = 0; i < kDisplayRanking; i++)
	{
		auto ranking = m_pResult->GetRanking(); // ランキングを取得
		m_pConversionTime->Change(ranking[i]);  // タイム変換
		DrawFormatStringToHandle(kTimePosX, kTimePosY + kIntervalY * i, 0xffffff, m_pFont->GetResultTimeFont(),
			"%02d位:%02d:%03d\n", (i + 1), m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
	}
}