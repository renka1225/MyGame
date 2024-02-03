#pragma once
#include "Vec2.h"

class FontManager;

/// <summary>
/// �X�^�[�g���o�A�N���A���o���̊Ǘ��N���X
/// </summary>
class SceneStaging
{
public:
	SceneStaging();
	virtual ~SceneStaging();
	void Init();
	void Update();
	void Draw();
	// �X�^�[�g���o
	void Start();
	// �N���A���o
	void Clear();

	// �\����Ԃ��擾
	bool IsStart() const { return m_isStart; }
	bool IsClear() const { return m_isClear; }

private:
	/*�|�C���^���擾*/
	// �t�H���g�Ǘ�
	FontManager* m_pFont;

	// �X�^�[�g���o���\������ true:�\����
	bool m_isStart;
	// �N���A���o���\������
	bool m_isClear;

	// ���o
	float m_startTime;		// �X�^�[�g���o�̎���
	float m_clearTime;		// �N���A���o����
	float m_gameoverTime;	// �Q�[���I�[�o�[���o����

	// �X�^�[�g���o�̕\���ʒu
	Vec2 m_startDis;
	// �N���A���o�̕\���ʒu
	Vec2 m_clearDis;

	// ��
	int m_startSE;		// �X�^�[�g����SE
	int m_clearSE;		// �N���A����SE
};

