#include "Input.h"
#include "DxLib.h"
#include <string>
#include <algorithm>

/// <summary>
/// ���͏��̍X�V
/// </summary>
void Input::Update()
{
	// ���O�̓��͂��R�s�[
	m_lastInputData = m_inputData;

	/*�n�[�h�E�F�A���̓`�F�b�N*/
	// �p�b�h���̎擾
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);
	// ���݂̃L�[�{�[�h���͂��擾
	char keystate[256];
	GetHitKeyStateAll(keystate);

	// m_inputData�̓��e���X�V
	for (const auto& cmd : m_commandTable)
	{
		auto& input = m_inputData[cmd.first];	// �R�}���h�̖��O������̓f�[�^�����
		for (const auto& hardIO : cmd.second)
		{
			// �L�[�{�[�h�̃`�F�b�N
			input = false;
			if (hardIO.first == InputType::keybd)
			{
				if (keystate[hardIO.second])
				{
					input = true;
					break;
				}
			}
			// �p�b�h�̃`�F�b�N
			else if (hardIO.first == InputType::pad)
			{
				if (padstate & hardIO.second)
				{
					input = true;
					break;
				}
			}
		}
	}
}


/// <summary>
/// �����ꂽ�u�Ԃ��擾
/// </summary>
/// <param name="command">�R�}���h������</param>
/// <returns>ture:�����ꂽ�u��</returns>
bool Input::IsTriggered(const char* command) const
{
	auto it = m_inputData.find(command);

	// �v�f���Ȃ��ꍇ
	if (it == m_inputData.end())
	{
		return false;
	}

	return(m_inputData.at(command) && !m_lastInputData.at(command));
}


/// <summary>
/// �������Ă��邩���擾
/// </summary>
/// <param name="command">�R�}���h������</param>
/// <returns>true:������Ă���</returns>
bool Input::IsPressing(const char* command) const
{
	auto it = m_inputData.find(command);

	// �v�f���Ȃ��ꍇ
	if (it == m_inputData.end()	)
	{
		return false;
	}

	return m_inputData.at(command);
}


/// <summary>
/// �����ꂽ�u�Ԃ��擾
/// </summary>
/// <param name="command">�R�}���h������</param>
/// <returns>true:�����ꂽ�u��</returns>
bool Input::IsReleased(const char* command) const
{
	auto it = m_inputData.find(command);

	// �v�f���Ȃ��ꍇ
	if (it == m_inputData.end())
	{
		return false;
	}

	return(!m_inputData.at(command) && m_lastInputData.at(command));
}


/// <summary>
/// �R�}���h�̎��
/// </summary>
Input::Input()
{
	m_commandTable["OK"] = { {InputType::keybd, KEY_INPUT_RETURN},
							{InputType::pad, PAD_INPUT_A} };

	m_commandTable["A"] = { {InputType::keybd, KEY_INPUT_RIGHT},
						   {InputType::pad, PAD_INPUT_A} };

	m_commandTable["B"] = { {InputType::keybd, KEY_INPUT_DOWN},
							   {InputType::pad, PAD_INPUT_B} };

	m_commandTable["X"] = { {InputType::keybd, KEY_INPUT_UP},
							   {InputType::pad, PAD_INPUT_C} };

	m_commandTable["Y"] = { {InputType::keybd, KEY_INPUT_LEFT},
							   {InputType::pad, PAD_INPUT_X} };

	m_commandTable["pause"] = { {InputType::keybd, KEY_INPUT_P},
						   {InputType::pad, PAD_INPUT_R} };

	m_commandTable["end"] = { {InputType::keybd, KEY_INPUT_ESCAPE},
						{InputType::pad, PAD_INPUT_C} };

	m_commandTable["sceneChange"] = { {InputType::keybd, KEY_INPUT_Z},
						   {InputType::pad, PAD_INPUT_Y} };

	m_commandTable["debug"] = { {InputType::keybd, KEY_INPUT_X},
							   {InputType::pad, PAD_INPUT_R} };
}