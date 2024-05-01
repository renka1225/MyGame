#pragma once
#include "SceneBase.h"

/// <summary>
/// ���ʕ\�����
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

	static constexpr int kTimePosX = 560;		// ���ʕ\���ʒuX
	static constexpr int kTimePosY = 150;		// ���ʕ\���ʒuY
	static constexpr int kIntervalY = 50;		// ���ʕ\���Ԋu
	static constexpr int kDisplayRanking = 10;	// �\�����鏇�ʐ�
};