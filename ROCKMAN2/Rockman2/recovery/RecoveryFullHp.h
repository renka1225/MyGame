#pragma once

class SceneMain;

/// <summary>
/// HP�S�񕜃A�C�e���N���X
/// </summary>
class RecoveryFullHp
{
public:
	RecoveryFullHp();
	virtual ~RecoveryFullHp();

	void Init();
	void Update();
	void Draw();

	// �񕜃A�C�e���̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

private:
	// ���C���V�[���̃|�C���^
	SceneMain* m_pMain;
	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// ��ʓ��ɑ��݂��Ă��邩
	bool m_isExist;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��p�̋�`
	Rect m_colRect;
};

