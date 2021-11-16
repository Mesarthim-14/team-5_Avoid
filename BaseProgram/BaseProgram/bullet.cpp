//=============================================================================
//
// ���˒e [bullet.cpp]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "bullet.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS		(ZeroVector3)
#define TEST_ROT		(ZeroVector3)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet(PRIORITY Priority) : CScene(Priority)
{
	m_pos = ZeroVector3;						// ���W
	m_move = ZeroVector3;						// �ړ���
	m_rot = ZeroVector3;						// ���݂̉�]
	m_size = ZeroVector3;						// �T�C�Y
	m_nLife = 0;							    // ��������
	m_fSpeed = 0.0f;							// �X�s�[�h
	m_nDamage = 0;							        // �_���[�W��
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBullet * CBullet::Create(void)
{
	// �������m��
	CBullet *pBullet = new CBullet(PRIORITY_TEST_MODEL);

	// !nullcheck
	if (pBullet)
	{
		// ����������
		pBullet->Init();

		return pBullet;
	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{
	// �ʒu�X�V
	m_pos += m_move;

	m_nLife--;

	if (m_nLife < 0)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{

}