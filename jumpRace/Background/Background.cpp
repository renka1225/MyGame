#include "Background.h"
#include "WorldSprite.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Background::Background():
	m_pos(VGet(0.0f, 0.0f, 0.0f))
{
	m_background = LoadGraph("data/Background/5.png");

	m_sprite = std::make_shared<WorldSprite>();
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Background::~Background()
{
	DeleteGraph(m_background);
}


/// <summary>
/// ������
/// </summary>
void Background::Init()
{
	m_sprite->Init(m_background, kWidth, kHeight, 0);
	m_sprite->SetTransform(m_pos, kScele);
}


/// <summary>
/// �X�V
/// </summary>
void Background::Update()
{
}


/// <summary>
/// �`��
/// </summary>
void Background::Draw()
{
	m_sprite->Draw();
}
