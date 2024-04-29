#pragma once
#include "SceneBase.h"

/// <summary>
/// �N���A���
/// </summary>
class SceneClear : public SceneBase
{
public:
	SceneClear() {};
	SceneClear(int time);
	virtual ~SceneClear();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

	void UpdateSelect(Input& input);	// �I����Ԃ̍X�V

private:
	int m_clearTime;	// �N���A�^�C��

	// �I������
	enum Select
	{
		kStart,		// �X�^�[�g
		kTitle,		// �^�C�g���ɖ߂�
		kSelectNum	// �I��
	};
	int m_select;	// ���݂̑I�����

private: // �萔
	static constexpr int kClearTimePosX = 580;	// �N���A�^�C���\���ʒuX
	static constexpr int kClearTimePosY = 100;	// �N���A�^�C���\���ʒuY
	static constexpr int kStartTextPosX = 580;	// �X�^�[�g�\���ʒuX
	static constexpr int kStartTextPosY = 500;	// �X�^�[�g�\���ʒuY
	static constexpr int kTitleTextPosX = 520;	// �^�C�g���ɖ߂�\���ʒuX
	static constexpr int kTitleTextPosY = 600;	// �^�C�g���ɖ߂�\���ʒuY
};

