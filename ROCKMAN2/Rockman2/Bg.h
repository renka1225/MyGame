#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Game.h"

class SceneMain;
/// <summary>
/// �w�i�N���X
/// </summary>
class Bg
{
public:
	Bg(SceneMain* pMain);
	~Bg();

	void Init();
	void Update();
	void Draw();

	// �O���t�B�b�N�̐ݒ�
	void SetHandle(int bgHandle) { m_bgHandle = bgHandle; }
	void SetMapHandle(int mapHandle) { m_mapHandle = mapHandle; }
	// �}�b�v�`�b�v�ԍ��̎擾
	int GetChipData(int x, int y) const { return m_chipData[y][x]; }
	// �}�b�v�̓����蔻����擾����
 	Rect GetColRect(int x, int y) const { return m_colRect[y][x]; }

private:
	// �}�b�v�`�b�v�̏��
	static constexpr int kChipWidth = 32;
	static constexpr int kChipHeight = 32;

	// �`�b�v��u����
	static constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	static constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

private:
	// �V�[�����C���̃|�C���^
	SceneMain* m_pMain;

	// �w�i�̃O���t�B�b�N
	int m_bgHandle;
	// �}�b�v�`�b�v�̃O���t�B�b�N
	int m_mapHandle;

	// �w�i�̕\���ʒu
	Vec2 m_bgPos;
	// �}�b�v�`�b�v�̕\���ʒu
	Vec2 m_mapChipPos;

	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;
	// �}�b�v�`�b�v�̔z�u���
	int m_chipData[kChipNumY][kChipNumX];

	// �e�}�b�v�`�b�v���Ƃ̓����蔻��p�̋�`
	Rect m_colRect[kChipNumY][kChipNumX];
};