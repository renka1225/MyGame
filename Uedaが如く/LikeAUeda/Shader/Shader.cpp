#include "DxLib.h"
#include "Game.h"
#include "Shader.h"

// �萔
namespace
{
	const char* kPsHName = "Shader/PixelShader.pso";  // �s�N�Z���V�F�[�_
	const char* kVsHName = "Shader/VertexShader.vso"; // ���_�V�F�[�_
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Shader::Shader():
	m_psH(-1),
	m_vsH(-1),
	m_rt(-1)
{
	m_rt = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	// �V�F�[�_���`����
	MV1SetUseOrigShader(true);
	m_psH = LoadPixelShader(kPsHName);
	m_vsH = LoadPixelShader(kVsHName);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Shader::~Shader()
{
}


/// <summary>
/// ������
/// </summary>
void Shader::Init()
{

}


/// <summary>
/// �X�V
/// </summary>
void Shader::Update()
{
}


/// <summary>
/// �`��
/// </summary>
void Shader::Draw()
{
}
