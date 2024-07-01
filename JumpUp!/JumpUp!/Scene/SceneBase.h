#pragma once
#include <memory>

class Input;
class DrawDebug;

/// <summary>
/// シーン基底クラス
/// </summary>
class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	SceneBase();
	virtual ~SceneBase() {};
	virtual void Init() = 0;
	virtual std::shared_ptr<SceneBase> Update(Input& input) = 0;
	virtual void Draw() = 0;

protected:
	virtual void FadeIn();	// フェードインの処理
	virtual void FadeOut();	// フェードアウトの処理
	void DrawFade(); // フェードインアウトの描画

	int m_fadeAlpha; // フェードのα値
};

