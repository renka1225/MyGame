#pragma once
#include "SceneBase.h"

/// <summary>
/// タイトル画面
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	virtual void FadeIn() override;		// フェードインの処理
	virtual void FadeOut() override;	// フェードアウトの処理
	void UpdateSelect(Input& input);	// 選択状態を更新

private:
	// 選択項目の種類
	enum Select
	{
		kStart,		// ゲームスタート
		kEnd,		// ゲーム終了
		kSelectNum	// 選択数
	};
	int m_select;	// 現在の選択状態

	float m_stageRotate;	// ステージの回転量
	float m_frameAnimTime;	// 枠のアニメーション時間

	int m_titleHandle;		 // タイトルロゴの画像
	int m_frameHandle;		 // 枠の画像
	int m_stageHandle;		 // ステージの3Dモデル
};