#pragma once
#include "SceneBase.h"

/// <summary>
/// オプション画面
/// </summary>
class SceneOption : public SceneBase
{
public:
	SceneOption() {};
	SceneOption(std::shared_ptr<SceneBase> pScene);
	virtual ~SceneOption();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	std::shared_ptr<SceneBase> m_pPrevScene;	// 前に実行していたシーン

	enum Select
	{
		kSound,			// サウンド
		kBrightness,	// 明るさ
		kKyeConfig,		// キーコンフィグ
		kSelectNum		// 選択数
	};
};

