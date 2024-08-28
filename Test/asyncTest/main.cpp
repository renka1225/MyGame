#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int m_handle;

    // ＤＸライブラリの初期化
    if (DxLib_Init() < 0) return -1;

    // 非同期読み込み設定に変更
    SetUseASyncLoadFlag(true);

    // モデルを読み込む
    m_handle = MV1LoadModel("data/city.mv1");

    // 同期読み込み設定に変更
    SetUseASyncLoadFlag(false);

    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    while (ProcessMessage() == 0 && CheckHitKeyAll() == 0)
    {
        // 画面のクリア
        ClearDrawScreen();

        // CheckHandleASyncLoad(int Handle)  ハンドルの非同期読み込みが完了しているかどうかを取得する
        if (CheckHandleASyncLoad(m_handle))
        {
            DrawString(0, 40, "読み込み中\n", 0xffffff);
        }
        else
        {
            DrawString(0, 40, "読み込み終了\n", 0xffffff);
            MV1SetScale(m_handle, VGet(10.0f, 10.0f, 10.0f));
            MV1DrawModel(m_handle);
        }

        // 非同期読み込みの数を描画
        DrawFormatString(0, 0, GetColor(255, 255, 255), "非同期読み込みの数 %d", GetASyncLoadNum());

        // 裏画面の内容を表画面に反映
        ScreenFlip();

        //WaitKey();
    }

    // 読み込んだ画像のグラフィックハンドルを削除する
    MV1DeleteModel(m_handle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}