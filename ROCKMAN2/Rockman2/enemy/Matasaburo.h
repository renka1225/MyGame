#pragma once
#include "EnemyBase.h"
#include "Vec2.h"

/// <summary>
/// �܂����Ԃ낤�̃N���X
/// </summary>
class Matasaburo : public EnemyBase
{
public:
	Matasaburo();
	virtual ~Matasaburo();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start() override;
	virtual void OnDamage() override;
	//virtual void DropItem() override;

private:
	// ���C���V�[���̃|�C���^
	SceneMain* m_pMain;

	int m_handle;
	int m_hp;
};

