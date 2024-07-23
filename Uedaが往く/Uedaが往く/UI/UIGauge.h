#pragma once

/// <summary>
/// �o�g�����ɕ\������Q�[�W��UI���Ǘ�����
/// </summary>
class UIGauge
{
public:
	UIGauge();
	~UIGauge();
	void UpdatePlayerHp();
	void DrawPlayerHP(float currentHp, float MaxHp);			// �v���C���[��HP�o�[��\��
	void DrawPlayerGauge(float currentGauge, float MaxGauge);	// �v���C���[�̃Q�[�W�o�[��\��
	void DrawEnemyHp(float currentHp, float MaxHp);				// �G��HP�o�[��\��
	void SetDamageTimer();										// �_���[�W���󂯂��ۂɃ^�C�}�[���Z�b�g����

private:
	int m_hpBarDecreaseTime;	// HP�o�[����������܂ł̎���
	float m_decreaseHp;			// ��������HP��
};
