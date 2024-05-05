#pragma once
#include "SceneBase.h"

/// <summary>
/// ���ʕ\�����
/// </summary>
class SceneResult : public SceneBase
{
public:
	SceneResult();
	virtual ~SceneResult();

	virtual void Init(std::shared_ptr<ManagerResult> pResult);
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();

private:
	void DrawRanking();

private:
	int m_rankingTextHandle;	// �����L���O�̃e�L�X�g�摜

private:	// �萔
	static constexpr int kButtonPosX = 70;			// �{�^���摜�\���ʒuX
	static constexpr int kButtonPosY = 645;			// �{�^���摜�\���ʒuY
	static constexpr int kButtonSize = 16;			// �{�^���摜�؂�o���T�C�Y
	static constexpr float kButtonScale = 3.0f;		// �{�^���摜�g�嗦
	static constexpr int kRankingTextPosX = 340;	// �����L���O�̕����\���ʒuX
	static constexpr int kRankingTextPosY = 100;	// �����L���O�̕����\���ʒuY
	static constexpr int kTextPosX = 87;			// �e�L�X�g�\���ʒuX
	static constexpr int kTextPosY = 630;			// �e�L�X�g�\���ʒuY

	static constexpr int kRankPosX = 370;			// 1�ʁ`5�ʕ\���ʒuX
	static constexpr int kRank2PosX = 680;			// 6�ʁ`10�ʕ\���ʒuX
	static constexpr int kRankPosY = 280;			// ���ʕ\���ʒuY
	static constexpr int kTimePosX = 480;			// 1�ʁ`5�ʃ^�C���\���ʒuX
	static constexpr int kTime2PosX = 790;			// 6�ʁ`10�ʃ^�C���\���ʒuX
	static constexpr int kTimePosY = 285;			// �^�C���\���ʒuY
	static constexpr int kIntervalY = 70;			// ���ʕ\���Ԋu
	static constexpr int kDisplayRanking = 10;		// �\�����鏇�ʐ�

	static constexpr int kStartFadeAlpha = 255;		// �X�^�[�g���̃t�F�[�h���l
};