#include "DxLib.h"
#include "Game.h"
#include "Confetti.h"

// 定数
namespace
{
    constexpr int kNum = 600; // 紙吹雪の作成数
}

namespace Confetti
{
    std::vector<ConfettiInfo> confettis;

    /// <summary>
    /// 紙吹雪の作成
    /// </summary>
    /// <param name="num">紙吹雪の数</param>
    void CreateCofetti()
    {
        for (int i = 0; i < kNum; i++)
        {
            confettiInfo.x = std::rand() % 800;
            confettiInfo.y = std::rand() % 600 - 600;
            confettiInfo.size = 6 + std::rand() % 10;
            confettiInfo.speed = 1 + std::rand() % 5;
            confettiInfo.color = GetColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
            confettis.push_back(confettiInfo);
        }
    }


    /// <summary>
    /// 更新
    /// </summary>
    void UpdateCofetti()
    {
        for (auto& c : confettis)
        {
            c.y += c.speed;

            // 画面下に出たら再生成する
            if (c.y > Game::kScreenHeight)
            {
                c.x = std::rand() % 800;
                c.y = -c.size;
                c.speed = 1 + std::rand() % 5;
                c.color = GetColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
            }
        }
    }


    /// <summary>
    /// 描画
    /// </summary>
    void DrawCofetti()
    {
        for (const auto& c : confettis)
        {
            DrawBox(c.x, c.y, c.x + c.size, c.y + c.size, c.color, true);
        }
    }
}
