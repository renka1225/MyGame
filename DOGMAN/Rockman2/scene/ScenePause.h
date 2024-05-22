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
	virtual ~ScenePause();
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

	// ���j���[��ʂ̍���
	int m_menuHeight;
	// �|�[�Y��ʂ̕\���ʒu
	Vec2 m_menuPos;
	// ����I�𒆃J�[�\���̕\���ʒu
	Vec2 m_selectShotPos;
	// �|�[�Y��ʑI�𒆂̃J�[�\���\���ʒu
	Vec2 m_selectPausePos;
	// ����؂�ւ���ʂ��\������Ă��邩 true:�\������Ă���
	bool m_isChangeMenuExist;
	// �|�[�Y��ʂ��\������Ă��邩
	bool m_isPauseExist;

	// �|�[�Y��ʂ̑I�����
	bool m_isRetry;	// ���g���C
	bool m_isTitle;	// �^�C�g���ɖ߂�

	// �摜
	int m_menuBg;		// ���j���[��ʂ̔w�i
	int m_selectHandle; // �I���J�[�\���̉摜

	// ��
	int m_menuSE;		// ���j���[��ʂ��J�����ۂ�SE
	int m_selectSE;		// �I������SE
	int m_cursorSE;		// �J�[�\���ړ�����SE
};
