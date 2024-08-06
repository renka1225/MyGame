#pragma once
#include "SceneBase.h"

/// <summary>
/// �I�v�V�������
/// </summary>
class SceneOption : public SceneBase
{
public:
	SceneOption() {};
	SceneOption(std::shared_ptr<SceneBase> pScene);
	virtual ~SceneOption();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	std::shared_ptr<SceneBase> m_pPrevScene;	// �O�Ɏ��s���Ă����V�[��

	enum Select
	{
		kSound,			// �T�E���h
		kBrightness,	// ���邳
		kKyeConfig,		// �L�[�R���t�B�O
		kSelectNum		// �I��
	};
};

