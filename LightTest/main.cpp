#include "DxLib.h"

// 行列を使ったカメラ回転
void CameraRotate()
{
    // カメラ回転
    float Rotate = 0.0f;
    MATRIX Matrix;

    // 左右キーでカメラの回転値を変更
    if (CheckHitKey(KEY_INPUT_LEFT) == 1)
    {
        Rotate -= DX_PI_F / 60.0f;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
    {
        Rotate += DX_PI_F / 60.0f;
    }

    // 回転値を使用してＹ軸の回転行列を作成
    Matrix = MGetRotY(Rotate);

    // 回転行列をビュー行列としてセット
    SetCameraViewMatrix(Matrix);
}

// マテリアル描画
void DrawMaterial(int groundModel)
{
    // マテリアルの自己発光色を暗い青色にする
    MATERIALPARAM Material;
    Material.Diffuse = GetColorF(0.8f, 0.0f, 0.0f, 0.0f);   // 拡散光色
    Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);  // 環境光色
    Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);   // 反射光色
    Material.Emissive = GetColorF(0.9f, 0.0f, 0.0f, 0.0f);  // 自己発光色
    Material.Power = 20.0f;                                 // スペキュラの強さ
    SetMaterialParam(Material);

    Material.Emissive = GetColorF(0.0f, 0.2f, 0.9f, 0.0f);  // 自己発光色
    SetMaterialParam(Material);
    // デフォルトの設定で３Ｄ空間上に球を描画する
    DrawSphere3D(VGet(320.0f, 200.0f, 0.0f), 40.0f, 32, GetColor(128, 0, 0), GetColor(255, 255, 255), true);


    Material.Specular = GetColorF(0.0f, 0.8f, 0.0f, 1.0f);  // 環境光色
    Material.Emissive = GetColorF(0.9f, 0.4f, 0.0f, 0.0f);  // 自己発光色
    Material.Power = 20.0f;                                 // スペキュラの強さ
    SetMaterialParam(Material);
    // デフォルトの設定で３Ｄ空間上に球を描画する
    DrawSphere3D(VGet(480.0f, 200.0f, 0.0f), 40.0f, 32, GetColor(0, 0, 0), GetColor(255, 255, 255), true);

    // 3Dモデル表示
    MV1SetPosition(groundModel, VGet(160.0f, 200.0f, 0.0f));
    MV1SetDifColorScale(groundModel, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
    MV1DrawModel(groundModel);
}

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

    int rabbitModel = MV1LoadModel("data/rabbit.mv1");
    int groundModel = MV1LoadModel("data/tile.mv1");

    // ゲームループ
    while (ProcessMessage() != -1)
    {
        // カメラ回転
        CameraRotate();

       // 描画
        DrawMaterial(groundModel);

        WaitKey();				// キー入力待ち

        MV1DeleteModel(rabbitModel);
    }

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}