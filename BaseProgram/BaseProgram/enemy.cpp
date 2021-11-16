//=============================================================================
//
// �G�N���X [enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(PRIORITY Priority)
{
	m_nAttackInter = 0;
	m_nAttackCount = 0;
	m_nSTR = 0;
	m_fPower = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init()
{
	CCharacter::Init();

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update()
{
	CCharacter::Update();

	m_nAttackCount++;
	if (m_nAttackCount >= m_nAttackInter)
	{
		Attack();
		m_nAttackCount = 0;
	}
}

//=============================================================================
// �U���̏��ݒ�
//=============================================================================
void CEnemy::SetAttackInfo(const int &nInter, const int &nSTR, const float &fPower)
{
	m_nAttackInter = nInter;
	m_nSTR = nSTR;
	m_fPower = fPower;
}

//=============================================================================
// �ړ�
//=============================================================================
void CEnemy::Move()
{

}

//=============================================================================
// ��Ԃ̍X�V
//=============================================================================
void CEnemy::UpdateState()
{
}