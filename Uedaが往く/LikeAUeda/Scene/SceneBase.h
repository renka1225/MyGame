#pragma once
#include <memory>

class Input;
class Shader;

/// <summary>
/// �V�[�����N���X
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
	void UpdateSelect(Input& input, int selectNum);	// �I����Ԃ��X�V

protected:
	std::shared_ptr<Shader> m_pShader;
	int m_select;	// ���݂̑I�����

#ifdef _DEBUG
	// �f�o�b�O��
	enum class DebugState
	{
		Normal,	// �ʏ�
		Pause	// �|�[�Y
	};
	DebugState m_debugState = DebugState::Normal;
#endif
};

