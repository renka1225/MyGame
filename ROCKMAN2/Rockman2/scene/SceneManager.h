#pragma once

class SceneMain;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	SceneMain* m_pMain;
};

