#pragma once

/// <summary>
/// �V�F�[�_�[�̕`��
/// </summary>
class ToonShader
{
public:
	ToonShader();
	virtual ~ToonShader();
	void SetShader(int shaderType);

private:
	int m_graphHandle;	// �摜�n���h��
};