#include "DxLib.h"
#include "Game.h"
#include "Shader.h"

// 定数
namespace
{
	const char* kPsHName = "Shader/PixelShader.pso";  // ピクセルシェーダ
	const char* kVsHName = "Shader/VertexShader.vso"; // 頂点シェーダ
}

/// <summary>
/// コンストラクタ
/// </summary>
Shader::Shader():
	m_psH(-1),
	m_vsH(-1),
	m_rt(-1)
{
	m_rt = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	// シェーダを定義する
	MV1SetUseOrigShader(true);
	m_psH = LoadPixelShader(kPsHName);
	m_vsH = LoadPixelShader(kVsHName);
}


/// <summary>
/// デストラクタ
/// </summary>
Shader::~Shader()
{
}


/// <summary>
/// 初期化
/// </summary>
void Shader::Init()
{

}


/// <summary>
/// 更新
/// </summary>
void Shader::Update()
{
}


/// <summary>
/// 描画
/// </summary>
void Shader::Draw()
{
}
