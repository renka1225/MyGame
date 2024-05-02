#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

    // Ｚバッファを有効にする
    SetUseZBuffer3D(TRUE);

    // Ｚバッファへの書き込みを有効にする
    SetWriteZBuffer3D(TRUE);

    // マテリアルの自己発光色を暗い青色にする
    MATERIALPARAM Material;
    Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);   // 拡散光色
    Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);  // 環境光色
    Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);   // 反射光色
    Material.Emissive = GetColorF(0.5f, 0.0f, 0.0f, 0.0f);  // 自己発光色
    Material.Power = 20.0f;                                 // スペキュラの強さ
    SetMaterialParam(Material);
    // デフォルトの設定で３Ｄ空間上に球を描画する
    DrawSphere3D(VGet(160.0f, 200.0f, 0.0f), 40.0f, 32, GetColor(128, 0, 0), GetColor(255, 255, 255), true);


    Material.Emissive = GetColorF(0.0f, 0.2f, 0.9f, 0.0f);  // 自己発光色
    SetMaterialParam(Material);
    // デフォルトの設定で３Ｄ空間上に球を描画する
    DrawSphere3D(VGet(320.0f, 200.0f, 0.0f), 40.0f, 32, GetColor(128, 0, 0), GetColor(255, 255, 255), true);


    Material.Specular = GetColorF(0.0f, 0.8f, 0.0f, 1.0f);  // 環境光色
    Material.Emissive = GetColorF(0.0f, 0.4f, 0.0f, 0.0f);  // 自己発光色
    Material.Power = 10.0f;                                 // スペキュラの強さ
    SetMaterialParam(Material);
    // デフォルトの設定で３Ｄ空間上に球を描画する
    DrawSphere3D(VGet(480.0f, 200.0f, 0.0f), 40.0f, 32, GetColor(0, 0, 0), GetColor(255, 255, 255), true);


	WaitKey();				// キー入力待ち

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}