#pragma once
#include "SceneBase.h"
#include "DxLib.h"
#include <vector>

class ManagerFont;
class ManagerModel;
class Background;
class Map;
class Player;
class Enemy;
class Camera;

/// <summary>
/// �v���C���̃V�[��
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying() {};

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void LoadEnemy();		// �G���ǂݍ���
	void StartStaging();	// �X�^�[�g���o�̕\��
	void UpdateNotice();	// ���Ԍo�߂̒ʒm���s��
	void DrawNotice();		// ���Ԍo�߂̒ʒm��\��

private:
	// �|�C���^
	std::shared_ptr<ManagerModel> m_pModel;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<Background> m_pBackground;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;

	std::vector<VECTOR> m_enemyPos;	// �G�ʒu

	int m_time;					// ����
	int m_startTime;			// �X�^�[�g���̉��o����
	int m_noticeDisPlayFrame;	// �o�ߎ��Ԃ̒ʒm��\�����鎞��

	VECTOR m_noticePos;			// �ʒm�̕\���ʒu
	int m_fadeAlpha;			// �t�F�[�h�̃��l

private:	// �萔
	static constexpr int kEnemyNum = 100;				// �ő�G��
	static constexpr int kClearTime = 60 * 90;			// �Q�[������

	//�X�^�[�g���ɃJ�E���g��\��
	static constexpr int kStartTime = 60 * 4;			// �X�^�[�g���̉��o����
	static constexpr int kStartCount1 = 60 * 3;			// 1�J�E���g��
	static constexpr int kStartCount2 = 60 * 2;			// 2�J�E���g��
	static constexpr int kStartCount3 = 60;				// 3�J�E���g��
	static constexpr int kStartCount4 = 0;				// start�̕����\��
	static constexpr int kStartCountPosX = 910;			// �J�E���g�\���ʒuX
	static constexpr int kNoticeStartPosX = 670;		// start�̕����\���ʒuX
	static constexpr int kStartCountPosY = 500;			// �J�E���g�\���ʒuY
	static constexpr int kExPosY = 380;					// ��������\���ʒuY

	// 20�b���ƂɎ��Ԍo�߂̒ʒm��\������
	static constexpr int kNoticeTime1 = 20 * 60;
	static constexpr int kNoticeTime2 = 40 * 60;
	static constexpr int kNoticeTime3 = 60 * 60;
	static constexpr int kNoticeTime4 = 80 * 60;
	static constexpr int kNoticeDisPlayFrame = 3 * 60;	// �ʒm��\�����鎞��
	static constexpr int kNoticeMoveFrame = 30;			// �ʒm�̈ړ�����
	static constexpr int kNoticeStopFrame = 160;		// �ʒm�̒�~����
	static constexpr float kNoticeMove = 6.0f;			// �ʒm�\���̈ړ���
	static constexpr int kTimePosX = 620;				// ���ԕ\���ʒuX
	static constexpr int kTimePosY = 100;				// ���ԕ\���ʒuY
	static constexpr int kNoticeTimePosX = 800;			// ���Ԍo�߂̒ʒm�\���ʒuX
	static constexpr int kNoticeTimePosY = 190;			// ���Ԍo�߂̒ʒm�\���ʒuY

	// �t�F�[�h
	static constexpr int kStartFadeAlpha = 150;			// �X�^�[�g���̃t�F�[�h���l
	static constexpr int kFadeFrame = 8;				// �t�F�[�h�ω���
};