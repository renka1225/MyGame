#pragma once
#include "DxLib.h"

// 定数
namespace
{
	/*ディレクショナルライト*/
	const VECTOR kDirLightPos = VGet(0.0f, 1000.0f, 0.0f);	 // 位置
	const VECTOR kDirLightDir = VGet(0.0f, -1.0f, 0.0f);	 // 方向

	/*ポイントライト*/
	const VECTOR kPointLightPos = VGet(0.0f, 100.0f, 0.0f);  // 位置
	constexpr float kPointLightRange = 1000.0f;				 // 有効距離
	constexpr float kPointLightAtten0 = 0.0f;				 // 距離減衰パラメータ0
	constexpr float kPointLightAtten1 = 0.002f;				 // 距離減衰パラメータ1
	constexpr float kPointLightAtten2 = 0.0f;				 // 距離減衰パラメータ2

	/*スポットライト*/
	const VECTOR kSpotLightPos = VGet(0.0f, 100.0f, 0.0f);	 // 位置
	const VECTOR kSpotLightDir = VGet(0.0f, -1.0f, 0.0f);	 // 向き
	constexpr float kSpotLightOutAngle = 0.0f;				 // スポットライトコーンの外側の角度
	constexpr float kSpotLightInAngle = 180.0f;				 // スポットライトコーンの内側の角度
	constexpr float kSpotLightRange = 1000.0f;				 // 有効距離
	constexpr float kSpotLighAtten0 = 0.0f;					 // 距離減衰パラメータ0
	constexpr float kSpotLighAtten1 = 0.002f;				 // 距離減衰パラメータ1
	constexpr float kSpotLighAtten2 = 0.0f;					 // 距離減衰パラメータ2
}

/// <summary>
/// ライト調整
/// </summary>
namespace Light
{
	/// <summary>
	///	ライトセット
	/// </summary>
	void SetLight()
	{
		// ライト位置調整
		SetLightPosition(kDirLightPos);
		SetLightDirection(kDirLightDir);

		// ポイントライト作成
		int pointLight = CreatePointLightHandle(kPointLightPos, kPointLightRange, kPointLightAtten0, kPointLightAtten1, kPointLightAtten2);
	
		// スポットライト作成
		int spotLight = CreateSpotLightHandle(kSpotLightPos, kSpotLightDir, kSpotLightOutAngle, kSpotLightInAngle,
			kSpotLightRange, kSpotLighAtten0, kSpotLighAtten1, kSpotLighAtten2);
	};

	/// <summary>
	/// ライト削除
	/// </summary>
	void DeleteLight()
	{
		DeleteLightHandleAll();
	}
}