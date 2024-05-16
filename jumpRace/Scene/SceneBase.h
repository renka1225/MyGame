#pragma once
#include <memory>

class Input;
class ManagerFont;
class ManagerSound;
class ManagerResult;
class ConversionTime;

/// <summary>
/// �V�[�����N���X
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
	void FadeIn();		// �t�F�[�h�C���̏���
	void FadeOut();		// �t�F�[�h�A�E�g�̏���
	void DrawFade();	// �t�F�[�h�C���A�E�g�̕`��

protected:
	std::shared_ptr<ManagerFont> m_pFont;
	std::shared_ptr<ManagerSound> m_pSound;
	std::shared_ptr<ManagerResult> m_pResult;
	std::shared_ptr<ConversionTime> m_pConversionTime;

	int m_fadeAlpha;	// �t�F�[�h�̃��l
	int m_soundPal;		// BGM�̉���

	int m_frameHandle;	// �g�̉摜
	int m_buttonHandle;	// �R���g���[���[�̃{�^���̉摜

private:
	static constexpr int kStartSoundPal = 20;	// �X�^�[�g����BGM�̉���
	static constexpr int kMaxFade = 255;		// �t�F�[�h�̃��ő�l
	static constexpr int kFadeFrame = 8;		// �t�F�[�h�ω���
};