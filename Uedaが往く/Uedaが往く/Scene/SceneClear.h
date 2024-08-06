#pragma once
#include "SceneBase.h"
#include <memory>

/// <summary>
/// クリアシーン
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear():m_textHandle(-1),m_totalClearTime(0) {};
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
