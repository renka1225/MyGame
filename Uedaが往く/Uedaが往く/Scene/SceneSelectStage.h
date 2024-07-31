#pragma once
#include "SceneBase.h"

/// <summary>
/// ステージ選択画面
/// </summary>
class SceneSelectStage : public SceneBase
{
public:
	SceneSelectStage();
	virtual ~SceneSelectStage();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	// シーンの種類
	enum SelectScene
	{
		kStage1,	// ステージ1
		kStage2,	// ステージ2
		kTitle,		// タイトルにもどる
		kSelectNum	// シーンの数
	};
};

