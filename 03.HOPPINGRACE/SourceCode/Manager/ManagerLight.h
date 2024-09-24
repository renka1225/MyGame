#pragma once

/// <summary>
/// ライト管理クラス
/// </summary>
class ManagerLight
{
public:
	ManagerLight();
	void CreateDirLight();	// ディレクショナルタイプのライトハンドルを作成する
	void DeleteDirLight();	// ディレクショナルタイプのライトハンドルを削除

private:
	int m_dirLightHandle;	// ディレクショナルタイプのライト

private:	// 定数
	static constexpr float kDirLightPosX = 0.0f;
	static constexpr float kDirLightPosY = 0.0f;
	static constexpr float kDirLightPosZ = -20.0f;
};

