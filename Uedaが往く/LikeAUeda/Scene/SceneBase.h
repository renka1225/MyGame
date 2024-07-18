#pragma once
#include <memory>

class Input;
class Shader;

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
	void UpdateSelect(Input& input, int selectNum);	// 選択状態を更新

protected:
	std::shared_ptr<Shader> m_pShader;
	int m_select;	// 現在の選択状態

#ifdef _DEBUG
	// デバッグ状況
	enum class DebugState
	{
		Normal,	// 通常
		Pause	// ポーズ
	};
	DebugState m_debugState = DebugState::Normal;
#endif
};

