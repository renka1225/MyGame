#pragma once
#include "SceneStageBase.h"
#include <vector>

class Player;
class Camera;
class Stage;
class EnemyBase;
class CharacterBase;

/// <summary>
/// ステージ1
/// </summary>
class SceneStage1 : public SceneStageBase
{
public:
	SceneStage1() {};
	SceneStage1(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage);
	virtual  ~SceneStage1();
	virtual void Init() override;
	virtual std::shared_ptr<SceneBase> Update(Input& input) override;
	virtual void Draw() override;
	void IsSetTuto(bool isTuto) { m_isTuto = isTuto; } // チュートリアル状態を変更

private:
	void UpdateSound();				// サウンド更新
	void UpdateTuto(Input& input);	// チュートリアルの表示状態を更新する
	void DrawTutorial();			// チュートリアル表示

private:
	int m_tutoNum;					// 現在のチュートリアル数
	int m_tutoSelect;				// チュートリアルの選択状態
	bool m_isTuto;					// チュートリアルを表示するか(true:表示する)
	std::string m_tutoText;
	std::vector<int> m_tutoHandle;	// チュートリアル時に表示する画像

	enum Select
	{
		kYes,	// はい
		kNo,	// いいえ
	};
};