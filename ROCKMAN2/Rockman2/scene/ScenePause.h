#pragma once
#include "Vec2.h"

class FontManager;
class Player;

/// <summary>
/// �|�[�Y�V�[���N���X
/// </summary>
class ScenePause
{
public:
	ScenePause(Player* pPlayer);
	~ScenePause();
	void Init();
	void Update();
	void Draw();
	// ����؂�ւ��̍X�V
	void UpdateChangeShot();
	// �|�[�Y��ʑI����ԍX�V
	void UpdatePause();

	// ����؂�ւ���ʂ��\������Ă��邩�擾
	bool IsSelectShotExist() const { return  m_isChangeMenuExist; }
	// �|�[�Y��ʂ��\������Ă��邩�擾
	bool IsPause() const { return m_isPauseExist; }

	// �|�[�Y��ʂ̑I����Ԃ��擾����
	bool IsSelectBack() const { return m_isBack; }
	bool IsSelectRetry() const { return m_isRetry; }
	bool IsSelectTitle() const { return m_isTitle; }

private:
	// ����؂�ւ��I������
	enum SelectShot
	{
		kBuster,// �o�X�^�[
		kMetal, // ���^��
		kFire,	// �t�@�C�A�[
		kLine,	// 2��
		kFullRecovery,	// E��
		kShotSelectNum // ���ڐ�
	};

	// �|�[�Y��ʑI������
	enum Pause
	{
		kBack,	// �Q�[���ɖ߂�
		kRetry,	// ���g���C
		kTitle,	// �^�C�g���ɖ߂�
		kSelectNum // ���ڐ�
	};

	// ���݂̕���I�����
	int m_shotSelect;
	// ���݂̃|�[�Y�I�����
	int m_pauseSelect;

private:
	// �t�H���g�Ǘ�
	FontManager* m_pFont;
	// �v���C���[�̃|�C���^
	Player* m_pPlayer;

	// �|�[�Y��ʂ̕\���ʒu
	Vec2 m_pos;
	// �I�𒆂̎l�p�̕\���ʒu
	Vec2 m_selectPos;
	// ����؂�ւ���ʂ��\������Ă��邩 true:�\������Ă���
	bool m_isChangeMenuExist;
	// �|�[�Y��ʂ��\������Ă��邩
	bool m_isPauseExist;

	// �|�[�Y��ʂ̑I�����
	bool m_isBack;	// �Q�[���ɖ߂�
	bool m_isRetry;	// ���g���C
	bool m_isTitle;	// �^�C�g���ɖ߂�
};

