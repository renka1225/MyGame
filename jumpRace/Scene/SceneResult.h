#pragma once
#include "SceneBase.h"

/// <summary>
/// Œ‹‰Ê•\Ž¦‰æ–Ê
/// </summary>
class SceneResult : public SceneBase
{
public:
	SceneResult();
	virtual ~SceneResult();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
};

