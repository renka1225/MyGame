#pragma once

/// <summary>
/// シェーダーの描画
/// </summary>
class ToonShader
{
public:
	ToonShader();
	virtual ~ToonShader();
	void SetShader(int shaderType);

private:
	int m_graphHandle;	// 画像ハンドル
};