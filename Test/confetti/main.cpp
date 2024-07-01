#include "DxLib.h"
#include <vector>
#include <cstdlib> // for std::rand, std::srand
#include <ctime>   // for std::time

// 紙吹雪の構造体
struct Confetti {
    int x, y;
    int size;
    int speed;
    int color;
};

// 紙吹雪のリスト
std::vector<Confetti> confettis;

// 紙吹雪の生成
void GenerateConfetti(int num) {
    for (int i = 0; i < num; ++i) {
        Confetti c;
        c.x = std::rand() % 800; // 画面幅に合わせて調整
        c.y = std::rand() % 600 - 600; // 画面外から開始
        c.size = 5 + std::rand() % 10;
        c.speed = 1 + std::rand() % 5;
        c.color = GetColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
        confettis.push_back(c);
    }
}

// 紙吹雪の更新
void UpdateConfetti() {
    for (auto& c : confettis) {
        c.y += c.speed;
        if (c.y > 600) { // 画面下に出たら再生成
            c.x = std::rand() % 800;
            c.y = -c.size;
            c.speed = 1 + std::rand() % 5;
            c.color = GetColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
        }
    }
}

// 紙吹雪の描画
void DrawConfetti() {
    for (const auto& c : confettis) {
        DrawBox(c.x, c.y, c.x + c.size, c.y + c.size, c.color, TRUE);
    }
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    SetMainWindowText("Confetti");

    ChangeWindowMode(TRUE);
    SetGraphMode(800, 600, 32);
    if (DxLib_Init() == -1) {
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);

    std::srand(static_cast<unsigned int>(std::time(0))); // 乱数初期化

    GenerateConfetti(100); // 初期紙吹雪の数

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        ClearDrawScreen();

        UpdateConfetti();
        DrawConfetti();

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}