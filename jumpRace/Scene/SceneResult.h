#pragma once
#include "SceneBase.h"

/// <summary>
/// 結果表示画面
/// </summary>
class SceneResult : public SceneBase
{
public:
	SceneResult();
	virtual ~SceneResult();

	virtual void Init(std::shared_ptr<ManagerResult> pResult);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void DrawRanking();

private:	// 定数
	static constexpr int kTimePosX = 560;		// 順位表示位置X
	static constexpr int kTimePosY = 150;		// 順位表示位置Y
	static constexpr int kIntervalY = 50;		// 順位表示間隔
	static constexpr int kDisplayRanking = 10;	// 表示する順位数

	static constexpr int kStartFadeAlpha = 200;		// スタート時のフェードα値
};