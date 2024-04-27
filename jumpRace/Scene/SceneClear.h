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

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

	void UpdateSelect(Input& input);	// 選択状態の更新

private:
	int m_clearTime;	// クリアタイム

	// 選択項目
	enum Select
	{
		kStart,		// スタート
		kTitle,		// タイトルに戻る
		kSelectNum	// 選択数
	};
	int m_select;	// 現在の選択状態

private: // 定数
	static constexpr int kStartTextPosX = 600;	// スタート表示位置X
	static constexpr int kStartTextPosY = 500;	// スタート表示位置Y
	static constexpr int kTitleTextPosX = 600;	// タイトルに戻る表示位置X
	static constexpr int kTitleTextPosY = 600;	// タイトルに戻る表示位置Y
};

