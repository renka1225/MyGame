#include "DxLib.h"
#include "Input.h"
#include "UI.h"
#include "Game.h"
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
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % selectNum;	// �I����Ԃ�1������
		m_pUI->Init();
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (selectNum - 1)) % selectNum;	// �I����Ԃ�1�グ��
		m_pUI->Init();
	}
}