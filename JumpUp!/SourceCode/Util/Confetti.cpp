#include "DxLib.h"
#include "Game.h"
#include "Confetti.h"

// �萔
namespace
{
    constexpr int kNum = 600;         // ������̍쐬��
    constexpr int kMinSize = 6;       // �ŏ��̃T�C�Y
    constexpr int kRandSize = 15;     // �T�C�Y
    constexpr int kMinSpeed = 1;      // �������x�̍ŏ��l
    constexpr int kRandSpeed = 7;     // �������x
    constexpr int kRandColor = 256;    // �F
}

namespace Confetti
{
    std::vector<ConfettiInfo> confettis;

    /// <summary>
    /// �쐬
    /// </summary>
    void CreateCofetti()
    {
        for (int i = 0; i < kNum; i++)
        {
            ConfettiInfo confettiInfo;
            confettiInfo.x = std::rand() % Game::kScreenWidth;
            confettiInfo.y = std::rand() % Game::kScreenHeight - Game::kScreenHeight;
            confettiInfo.size = kMinSize + std::rand() % kRandSize;
            confettiInfo.speed = kMinSpeed + std::rand() % kRandSpeed;
            confettiInfo.color = GetColor(std::rand() % kRandColor, std::rand() % kRandColor, std::rand() % kRandColor);
            confettis.push_back(confettiInfo);
        }
    }


    /// <summary>
    /// �폜
    /// </summary>
    void DeleteCofetti()
    {
        confettis.clear();
    }


    /// <summary>
    /// �X�V
    /// </summary>
    void UpdateCofetti()
    {
        for (auto& c : confettis)
        {
            c.y += c.speed;

            // ��ʉ��ɏo����Đ�������
            if (c.y > Game::kScreenHeight)
            {
                c.x = std::rand() % Game::kScreenWidth;
                c.y = -c.size;
                c.speed = kMinSize + std::rand() % kRandSize;
                c.color = GetColor(std::rand() % kRandColor, std::rand() % kRandColor, std::rand() % kRandColor);
            }
        }
    }


    /// <summary>
    /// �`��
    /// </summary>
    void DrawCofetti()
    {
        for (const auto& c : confettis)
        {
            DrawBox(c.x, c.y, c.x + c.size, c.y + c.size, c.color, true);
        }
    }
}
