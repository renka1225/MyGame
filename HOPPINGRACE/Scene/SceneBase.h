#pragma once
#include <memory>

class Input;
class ManagerFont;
class ManagerSound;
class ManagerResult;
class ConversionTime;

/// <summary>
/// シーン基底クラス
/// </summary>
class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Init(std::shared_ptr<ManagerResult> pResult) = 0;
	virtual std::shared_ptr<SceneBase> Update(Input& input) = 0;
	virtual void Draw() = 0;

protected:
	void FadeIn();		// フェードインの処理
	void FadeOut();		// フェードアウトの処理
	void DrawFade();	// フェードインアウトの描画

protected:
	std::shared_ptr<ManagerFont> m_pFont;
	std::shared_ptr<ManagerSound> m_pSound;
	std::shared_ptr<ManagerResult> m_pResult;
	std::shared_ptr<ConversionTime> m_pConversionTime;

	int m_fadeAlpha;	// フェードのα値
	int m_soundPal;		// BGMの音量

	int m_frameHandle;	// 枠の画像
	int m_buttonHandle;	// コントローラーのボタンの画像

private:
	static constexpr int kStartSoundPal = 20;	// スタート時のBGMの音量
	static constexpr int kMaxFade = 255;		// フェードのα最大値
	static constexpr int kFadeFrame = 8;		// フェード変化量
};