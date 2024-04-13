#pragma once
#include <memory>

class Input;
class ManagerFont;
class ManagerSound;

/// <summary>
/// シーン基底クラス
/// </summary>
class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Init() = 0;
	virtual std::shared_ptr<SceneBase> Update(Input& input) = 0;
	virtual void Draw() = 0;

protected:
	std::shared_ptr<ManagerFont> m_pFont;
	std::shared_ptr<ManagerSound> m_pSound;

	int m_cursorPosY;	// カーソル位置Y
	int m_cursorHandle;	// カーソルの画像
};