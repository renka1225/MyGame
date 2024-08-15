#include "DxLib.h"
#include "Input.h"
#include "Game.h"
#include "UI.h"
#include "Sound.h"
#include "SceneBase.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneBase::SceneBase():
	m_select(0)
{
	m_pUI = std::make_shared<UI>();
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneBase::~SceneBase()
{
}


/// <summary>
/// �I����Ԃ��X�V
/// </summary>
/// <param name="input">���͏��</param>
/// <param name="selectNum">�I�����̐�</param>
void SceneBase::UpdateSelect(Input& input, int selectNum)
{
	// �I����Ԃ�1������
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % selectNum;
		m_pUI->Init();
		PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kCursor)], DX_PLAYTYPE_BACK);
	}
	// �I����Ԃ�1�グ��
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (selectNum - 1)) % selectNum;
		m_pUI->Init();
		PlaySoundMem(Sound::m_seHandle[static_cast<int>(Sound::SeKind::kCursor)], DX_PLAYTYPE_BACK);
	}
}