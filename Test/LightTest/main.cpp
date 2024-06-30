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
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
//	{
//		return -1;			// エラーが起きたら直ちに終了
//	}
//
//    // Ｚバッファを有効にする
//    SetUseZBuffer3D(TRUE);
//    // Ｚバッファへの書き込みを有効にする
//    SetWriteZBuffer3D(TRUE);
//
//    int rabbitModel = MV1LoadModel("data/rabbit.mv1");
//    int groundModel = MV1LoadModel("data/tile.mv1");
//
//    // ゲームループ
//    while (ProcessMessage() != -1)
//    {
//        // カメラ回転
//        CameraRotate();
//
//       // 描画
//        DrawMaterial(groundModel);
//
//        WaitKey();				// キー入力待ち
//
//        MV1DeleteModel(rabbitModel);
//    }
//
//	DxLib_End();			// ＤＸライブラリ使用の終了処理
//
//	return 0;				// ソフトの終了 
//}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int ModelHandle;
    float Range, Atten0, Atten1, Atten2;

    // ＤＸライブラリの初期化
    if (DxLib_Init() < 0)
    {
        // エラーが発生したら直ちに終了
        return -1;
    }

    // モデルの読み込み
    ModelHandle = MV1LoadModel("data/rabbit.mv1");

    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    // 各パラメータを初期化
    Range = 2000.0f;
    Atten0 = 0.0f;
    Atten1 = 0.0006f;
    Atten2 = 0.0f;

    // ＥＳＣキーが押されるかウインドウが閉じられるまでループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // 画面をクリア
        ClearDrawScreen();

        // ＤＣキーでライトの影響範囲を変更
        if (CheckHitKey(KEY_INPUT_D) == 1)
        {
            Range += 20.0f;
        }
        if (CheckHitKey(KEY_INPUT_C) == 1)
        {
            Range -= 20.0f;
        }

        // ＦＶキーでライトの距離減衰パラメータ０の値を変更
        if (CheckHitKey(KEY_INPUT_F) == 1)
        {
            Atten0 += 0.001f;
        }
        if (CheckHitKey(KEY_INPUT_V) == 1)
        {
            Atten0 -= 0.001f;
        }

        // ＧＢキーでライトの距離減衰パラメータ１の値を変更
        if (CheckHitKey(KEY_INPUT_G) == 1)
        {
            Atten1 += 0.00001f;
        }
        if (CheckHitKey(KEY_INPUT_B) == 1)
        {
            Atten1 -= 0.00001f;
        }

        // ＨＮキーでライトの距離減衰パラメータ２の値を変更
        if (CheckHitKey(KEY_INPUT_H) == 1)
        {
            Atten2 += 0.0000001f;
        }
        if (CheckHitKey(KEY_INPUT_N) == 1)
        {
            Atten2 -= 0.0000001f;
        }

        // 影響距離の値を補正
        if (Range < 0.0f) Range = 0.0f;

        // 距離減衰パラメータの値を補正
        if (Atten0 < 0.0f) Atten0 = 0.0f;
        if (Atten1 < 0.0f) Atten1 = 0.0f;
        if (Atten2 < 0.0f) Atten2 = 0.0f;

        // モデルの上空にポイントライトを設定
        ChangeLightTypePoint(
            VGet(320.0f, 1000.0f, 200.0f),
            Range,
            Atten0,
            Atten1,
            Atten2);

        // モデルをカメラの映る位置に移動
        MV1SetPosition(ModelHandle, VGet(320.0f, 240.0f, 200.0f));

        // モデルを描画
        MV1DrawModel(ModelHandle);

        // パラメータの内容を画面に表示
        DrawFormatString(0, 0, GetColor(255, 255, 255), "Key:D.C  Range  %f", Range);
        DrawFormatString(0, 16, GetColor(255, 255, 255), "Key:F.V  Atten0 %f", Atten0);
        DrawFormatString(0, 32, GetColor(255, 255, 255), "Key:G.B  Atten1 %f", Atten1);
        DrawFormatString(0, 48, GetColor(255, 255, 255), "Key:H.N  Atten2 %f / 100.0f", Atten2 * 100.0f);

        // 裏画面の内容を表画面に反映する
        ScreenFlip();
    }

    // モデルハンドルの削除
    MV1DeleteModel(ModelHandle);

    // ＤＸライブラリの後始末
    DxLib_End();

    // ソフトの終了
    return 0;
}