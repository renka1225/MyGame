#pragma once
#include "SceneBase.h"
#include <memory>

/// <summary>
/// クリアシーン
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear() {};
	SceneClear(std::vector<int> clearTime);
	virtual ~SceneClear();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_textHandle;				// テキストの画像
	int m_totalClearTime;			// トータルのクリアタイム
	std::vector<int> m_clearTime;	// クリアタイム
};
