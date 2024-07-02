#include "DxLib.h"
#include "Game.h"
#include "Confetti.h"

// 定数
namespace
{
    constexpr int kNum = 600;         // 紙吹雪の作成数
    constexpr int kMinSize = 6;       // 最小のサイズ
    constexpr int kRandSize = 15;     // サイズ
    constexpr int kMinSpeed = 1;      // 落下速度の最小値
    constexpr int kRandSpeed = 7;     // 落下速度
    constexpr int kRandColor = 256;    // 色
}

namespace Confetti
{
    std::vector<ConfettiInfo> confettis;

    /// <summary>
    /// 作成
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
    /// 削除
    /// </summary>
    void DeleteCofetti()
    {
        confettis.clear();
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
                c.x = std::rand() % Game::kScreenWidth;
                c.y = -c.size;
                c.speed = kMinSize + std::rand() % kRandSize;
                c.color = GetColor(std::rand() % kRandColor, std::rand() % kRandColor, std::rand() % kRandColor);
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
