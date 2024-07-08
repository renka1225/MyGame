#pragma once
#include <memory>

class LoadData;
class SceneBase;
class Input;

/// <summary>
/// �V�[���Ǘ��N���X
/// </summary>
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();
	void Init(LoadData& data);
	void Update(Input& input);
	void Draw();

private:
	std::shared_ptr<SceneBase> m_pScene;
};

