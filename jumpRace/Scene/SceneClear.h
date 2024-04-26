#pragma once
#include "SceneBase.h"

/// <summary>
/// クリア画面
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear() {};
	SceneClear(int time);
	virtual ~SceneClear();

	void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	int m_clearTime;	// クリアタイム
};

