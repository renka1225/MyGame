#pragma once
#include "SceneBase.h"
#include <memory>

/// <summary>
/// クリアシーン
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear();
	virtual ~SceneClear();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

	//void SetClearTime(std::vector<int> clearTime) { m_clearTime = clearTime; };

private:
	int m_textHandle;				// テキストの画像
	std::vector<int> m_clearTime;	// クリアタイム
};
