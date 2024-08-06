#pragma once
#include "SceneBase.h"

/// <summary>
/// オプション画面
/// </summary>
class SceneOption : public SceneBase
{
public:
	SceneOption();
	virtual ~SceneOption();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	enum Select
	{
		kBGM,			// BGM音量調整
		kSE,			// SE音量調整
		kKyeConfig,		// キーコンフィグ
		kSelectNum		// 選択数
	};
};

