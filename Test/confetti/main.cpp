#include "DxLib.h"
#include <vector>
#include <cstdlib> // for std::rand, std::srand
#include <ctime>   // for std::time

// ������̍\����
struct Confetti {
    int x, y;
    int size;
    int speed;
    int color;
};

// ������̃��X�g
std::vector<Confetti> confettis;

// ������̐���
void GenerateConfetti(int num) {
    for (int i = 0; i < num; ++i) {
        Confetti c;
        c.x = std::rand() % 800; // ��ʕ��ɍ��킹�Ē���
        c.y = std::rand() % 600 - 600; // ��ʊO����J�n
        c.size = 5 + std::rand() % 10;
        c.speed = 1 + std::rand() % 5;
        c.color = GetColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
        confettis.push_back(c);
    }
}

// ������̍X�V
void UpdateConfetti() {
    for (auto& c : confettis) {
        c.y += c.speed;
        if (c.y > 600) { // ��ʉ��ɏo����Đ���
            c.x = std::rand() % 800;
            c.y = -c.size;
            c.speed = 1 + std::rand() % 5;
            c.color = GetColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
        }
    }
}

// ������̕`��
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

    std::srand(static_cast<unsigned int>(std::time(0))); // ����������

    GenerateConfetti(100); // ����������̐�

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        ClearDrawScreen();

        UpdateConfetti();
        DrawConfetti();

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}