#pragma once
#include "DxLib.h"
#include <memory>

class Input;
class ManagerModel;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	virtual ~Player() {};
	void Init();
	void Update(Input& input);
	void Draw();
	void End();

	VECTOR GetPos() const { return m_pos; }

private:
	// ジャンプ処理
	void Jump(Input& input);

private:
	// モデルクラスのポインタ
	std::shared_ptr<ManagerModel> m_pModel;

	// 表示位置
	VECTOR m_pos;
	// 移動量
	VECTOR m_move;

	// ジャンプフラグ true:ジャンプ中
	bool m_isJump;
	// ジャンプフレーム
	int m_jumpFrame;
};