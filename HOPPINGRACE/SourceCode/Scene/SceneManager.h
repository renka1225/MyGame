#pragma once
#include <memory>

class SceneBase;
class ManagerResult;
class Input;

/// <summary>
/// �V�[���Ǘ��N���X
/// </summary>
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager() {};

	void Init();
	void Update(Input& input);
	void Draw();

private:
	std::shared_ptr<SceneBase> m_pScene;
	std::shared_ptr<ManagerResult> m_pResult;
};