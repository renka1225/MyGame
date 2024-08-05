#pragma once

/// <summary>
/// �o�g�����ɕ\������Q�[�W��UI���Ǘ�����
/// </summary>
class UIGauge
{
public:
	UIGauge(float maxHp);
	~UIGauge();
	void UpdateHpBar();
	void DrawPlayerHP(float currentHp);							// �v���C���[��HP�o�[��\��
	void DrawPlayerGauge(float currentGauge, float MaxGauge);	// �v���C���[�̃Q�[�W�o�[��\��
	void DrawEnemyHp(float currentHp);							// �G��HP�o�[��\��
	void DrawSilhouette(int charType);							// �V���G�b�g��\��

	void SetDamageTimer();			// �_���[�W���󂯂��ۂɃ^�C�}�[���Z�b�g����
	void OnDamage(float damage);	// �󂯂��_���[�W�ʂ��v�Z����

private:
	float m_decreaseHp;				// �_���[�W���󂯂����HP
	float m_currentHp;				// ���݂�HP
	float m_damage;					// �󂯂��_���[�W��
	float m_maxHp;					// �ő�HP
	int m_intervalTime;				// HP�o�[����������܂ł̎���
	int m_gaugeBarHandle;			// �Q�[�W�o�[�̉摜
	int m_silhouetteHandle;			// �L�����N�^�[�̃V���G�b�g�摜
};
