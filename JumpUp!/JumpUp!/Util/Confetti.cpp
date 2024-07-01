#include "DxLib.h"
#include "Game.h"
#include "Confetti.h"

// ’è”
namespace
{
    constexpr int kNum = 600; // †á‚Ìì¬”
}

namespace Confetti
{
    std::vector<ConfettiInfo> confettis;

    /// <summary>
    /// †á‚Ìì¬
    /// </summary>
    /// <param name="num">†á‚Ì”</param>
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
    /// XV
    /// </summary>
    void UpdateCofetti()
    {
        for (auto& c : confettis)
        {
            c.y += c.speed;

            // ‰æ–Ê‰º‚Éo‚½‚çÄ¶¬‚·‚é
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
    /// •`‰æ
    /// </summary>
    void DrawCofetti()
    {
        for (const auto& c : confettis)
        {
            DrawBox(c.x, c.y, c.x + c.size, c.y + c.size, c.color, true);
        }
    }
}
