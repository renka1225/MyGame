#include "ScenePlaying.h"
#include "Player.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScenePlaying::ScenePlaying()
{
	m_pPlayer = std::make_shared<Player>();
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ScenePlaying::~ScenePlaying()
{
}


/// <summary>
/// ������
/// </summary>
void ScenePlaying::Init()
{
	m_pPlayer->Init();
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="input">����</param>
/// <returns>�J�ڐ�̃|�C���^</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// �v���C���[�X�V
	m_pPlayer->Update(input);

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}


/// <summary>
/// �`��
/// </summary>
void ScenePlaying::Draw()
{
	// �v���C���[�`��
	m_pPlayer->Draw();

#ifdef _DEBUG
	// �f�o�b�O�\��
	DrawFormatString(0, 0, 0xffffff, "�v���C���");
#endif

}
