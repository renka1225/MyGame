#include "Player.h"
#include "MyLib.h"
#include "Stage.h"
#include "DrawDebug.h"
#include "Input.h"


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	Collidable(Tag::Player),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_angle(0.0f),
	m_jumpPower(0.0f),
	m_jumpFrame(0),
	m_isJump(false),
	m_cameraAngle(0.0f),
	m_currentState(State::Idle)
{
	m_modelHandle = MV1LoadModel("data/model/player.mv1");
}


/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
	m_modelHandle = -1;
}


/// <summary>
/// 初期化
/// </summary>
void Player::Init(std::shared_ptr<Physics> physics)
{
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	MV1SetPosition(m_modelHandle, m_pos);
}


/// <summary>
/// 初期化
/// </summary>
void Player::Final(std::shared_ptr<Physics> physics)
{
}


/// <summary>
/// 更新
/// </summary>
void Player::Update(Input& input, Stage& stage)
{
	// プレイヤーの移動処理
	Move(input);
	// 当たり判定をして、新しい座標を保存する
	//m_pos = stage.CheckCollision(*this, m_move);

	// 地面に接地している場合
	if(m_currentState != State::Jump)
	{
		m_jumpFrame = 0;

		// 着地処理を行う
		if (m_pos.y + m_jumpPower < OnHitFloor(stage))
		{
			m_pos = VGet(m_pos.x, OnHitFloor(stage), m_pos.z);
		}
		
		// ボタンを押したらジャンプ状態にする
		if (input.IsTriggered("jump"))
		{
			// y軸方向の速度をセット
			//m_jumpPower = kVelocity;
			m_currentState = State::Jump;
			m_isJump = true;
		}
	}

	// ジャンプ処理を行う
	if (m_currentState == State::Jump)
	{
		Jump(input, stage);
	}

	// プレイヤー位置、角度を更新
	m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_modelHandle, m_pos);

	// プレイヤーの傾きを調整する
	UpdateAngle(stage);

	// ステージとの当たり判定
	if (IsHitStage(stage))
	{
		//OnHit(stage);
	}
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw(DrawDebug& drawDebug)
{
#ifdef _DEBUG	// デバッグ表示
	// プレイヤー位置表示
	drawDebug.DrawPlayerInfo(m_pos);
	// 当たり判定描画
	drawDebug.DrawCubeCol(VGet(m_pos.x, m_pos.y + kCenterPosY, m_pos.z), kWidth, kHeight, kDepth, 0x00ffff);
#endif

	// 3Dモデル表示
	MV1DrawModel(m_modelHandle);
}


/// <summary>
/// 移動処理
/// </summary>
/// <param name="input">入力</param>
void Player::Move(Input& input)
{
	m_move = VGet(0.0f, 0.0f, 0.0f);

	// ボタンを押したら移動
	if (input.IsPressing("up"))
	{
		m_move = VAdd(m_move, VGet(0.0f, 0.0f, kMove));
	}
	if (input.IsPressing("down"))
	{
		m_move = VAdd(m_move, VGet(0.0f, 0.0f, -kMove));
	}
	if (input.IsPressing("left"))
	{
		m_move = VAdd(m_move, VGet(-kMove, 0.0f, 0.0f));
	}
	if (input.IsPressing("right"))
	{
		m_move = VAdd(m_move, VGet(kMove, 0.0f, 0.0f));
	}

	// 斜めの移動速度を一定にする
	if (VSize(m_move) > 0.0f)
	{
		m_move = VNorm(m_move);
		m_move = VScale(m_move, kMove);
	}

	// 移動方向を決定する
	MATRIX mtx = MGetRotY(-m_cameraAngle - DX_PI_F / 2);
	m_move = VTransform(m_move, mtx);

	// 移動方向からプレイヤーの向く方向を決定する
	if (VSquareSize(m_move) > 0.0f)
	{
		m_angle = -atan2f(m_move.z, m_move.x) - DX_PI_F;
	}
}


/// <summary>
/// ジャンプ処理
/// </summary>
/// <param name="input">入力</param>
void Player::Jump(Input& input, Stage& stage)
{
	// 1回だけジャンプする
	if (m_isJump)
	{
		// ジャンプフレームを増やす
		m_jumpFrame++;

		// ジャンプの高さを調整する
		if (input.IsReleased("jump"))
		{
			float jumpHeight = 1.0f;
			if (m_jumpFrame < kLittleJumpFrame)
			{
				jumpHeight = kLittleJumpHeight;
			}
			else if (m_jumpFrame < kMediumJumpFrame)
			{
				jumpHeight = kMediumJumpHeight;
			}
			else
			{
				jumpHeight = kBigJumpHeight;
			}
		}

		// ジャンプ力を決める
		m_jumpPower = kVelocity;
		m_isJump = false;
	}

	// 重力を足す
	m_jumpPower += kGravity;

	// 着地処理を行う
	if (m_pos.y + m_jumpPower < OnHitFloor(stage))
	{
		m_pos.y = OnHitFloor(stage);
		m_currentState = State::Idle;
		m_isJump = false;
	}

	// Y軸方向の移動速度を反映する
	m_move.y = m_jumpPower * 0.5f;
}


/// <summary>
/// プレイヤーの傾きを調整する
/// </summary>
void Player::UpdateAngle(Stage& stage)
{
	// ジャンプ中は傾きを更新しない
	if (m_currentState == State::Jump) return;

	// プレイヤーを地面に沿って傾ける
	// 基底ベクトルを作成
	// y軸
	VECTOR v3Up = VCross(stage.GetV3Vec1(), stage.GetV3Vec2());
	v3Up = VNorm(v3Up);

	// z軸
	VECTOR v3Forward = VGet(cosf(-m_angle), 0.0f, sinf(-m_angle));

	// x軸
	VECTOR v3Side = VCross(v3Up, v3Forward);
	v3Side = VNorm(v3Side);

	// ベクトルを直交させる
	v3Forward = VCross(v3Side, v3Up);
	v3Forward = VNorm(v3Forward);

	// z軸とy軸の方向をセットする
	if (IsHitStage(stage))
	{
		// 平面部分に当たった場合はプレイヤーを傾けない
		v3Up = VGet(0.0f, 1.0f, 0.0f);
	}
	else
	{
		// 斜面に当たった場合はプレイヤーを斜面に沿って傾ける
		// 上下反転させる
		v3Up = VScale(v3Up, -1);
	}

	MV1SetRotationZYAxis(m_modelHandle, v3Forward, v3Up, 0.0f);
}


/// <summary>
/// 地面の位置からプレイヤーのY座標を求める
/// </summary>
/// <returns>地面の高さ</returns>
float Player::OnHitFloor(Stage& stage)
{
	// 地面の傾斜の外積を計算する
	VECTOR v3Normal = VCross(stage.GetV3Vec1(), stage.GetV3Vec2());
	if (IsHitStage(stage)) // ステージの上面に当たった場合
	{
		return stage.GetStagePos().y + MV1GetScale(stage.GetStageHandle()).y - m_jumpPower;
	}
	else // 地面に当たった場合
	{
		return (-v3Normal.x * m_pos.x - v3Normal.z * m_pos.z) / v3Normal.y - m_jumpPower;
	}
}


/// <summary>
/// ステージとの衝突判定を行う
/// </summary>
bool Player::IsHitStage(Stage& stage)
{
	/*プレイヤーと地面の当たり判定*/
	// 相対ベクトルを求める
	VECTOR v3SubAbs = VSub(m_pos, stage.GetStagePos());
	v3SubAbs = VGet(abs(v3SubAbs.x), abs(v3SubAbs.y), abs(v3SubAbs.z));

	// 衝突距離を求める
	// 衝突距離はそれぞれの対応した辺の長さを足して2で割ったもの
	VECTOR v3AddScale = VScale(VAdd(MV1GetScale(m_modelHandle), MV1GetScale(stage.GetStageHandle())), 0.5f);
	// TODO;当たり判定の範囲を広げる(仮実装)
	v3AddScale = VAdd(v3AddScale, VGet(0.0f, 20.0f, 0.0f));

	// 各成分の当たり判定
	bool isXHit = v3SubAbs.x < v3AddScale.x;
	bool isYHit = v3SubAbs.y < v3AddScale.y;
	bool isZHit = v3SubAbs.z < v3AddScale.z;

	if (isXHit && isYHit && isZHit) return true;
	
	return false;
}


/// <summary>
/// 衝突したときの処理
/// </summary>
void Player::OnHit(Stage& stage)
{
#ifdef _DEBUG
	DrawString(0, 40, "当たった", 0xffffff);
#endif

	// TODO:当たった場所によって位置を変える

	// ステージ位置を取得する
	VECTOR stagePos = stage.GetStagePos();

	// 横から当たったかチェックする
	m_pos.x += m_move.x;
	if (m_move.x > 0.0f)
	{
		m_pos.x = stagePos.x - MV1GetScale(stage.GetStageHandle()).x * 0.5f;
	}
	else if (m_move.x < 0.0f)
	{
		m_pos.x = stagePos.x + MV1GetScale(stage.GetStageHandle()).x * 0.5f;
	}

	// 縦から当たったかチェックする
	/*m_pos.y += m_move.y;
	if (m_move.y > 0.0f)
	{
		m_pos.y = stagePos.y - MV1GetScale(stage.GetStageHandle()).y * 0.5f;
		m_move.y *= -1.0f;
	}
	else if (m_move.y < 0.0f)
	{
		m_pos.y = stagePos.y + MV1GetScale(stage.GetStageHandle()).y * 0.5f;
	}*/
}


/// <summary>
/// 天井に当たった時
/// </summary>
void Player::OnHitRoof()
{
	// Y軸方向の速度を反転
	m_move.y = -m_move.y;
}


/// <summary>
/// 床に当たった時
/// </summary>
void Player::OnHitFloor()
{
	m_move.y = 0.0f;
	// ジャンプ中だった場合着地状態にする
	if (m_currentState == State::Jump)
	{

	}
}


/// <summary>
/// 落下中
/// </summary>
void Player::OnFall()
{
	if (m_currentState != State::Jump)
	{
		// ジャンプ中(落下中）にする
		m_currentState = State::Jump;
	}
}
