#pragma once
#include "SceneBase.h"

/// <summary>
/// タイトル画面
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual  ~SceneTitle();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void UpdateDisplay();

private:
	int m_time;					// 現在の時間
	int m_textDisplayTime;		// テキストを表示する時間
	int m_titleLogo;			// タイトルロゴの画像
	int m_titleLogoBack;		// タイトルロゴの後ろに表示する画像
	float m_titleLogoScale;		// タイトルロゴの拡大率
	float m_titleLogoRot;		// タイトルロゴの回転率
	int m_textHandle;			// テキストの画像
	int m_textAlpha;			// テキストのアルファ値
};