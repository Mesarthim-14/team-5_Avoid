//=============================================================================
//
// �{�X�̔��˒e [boss_bullet.cpp]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "boss_bullet.h"
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
CBossBullet::CBossBullet(PRIORITY Priority) : CBullet(Priority)
{
	m_pModel = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBossBullet::~CBossBullet()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBossBullet * CBossBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	// �������m��
	CBossBullet *pTestModel = new CBossBullet(PRIORITY_TEST_MODEL);

	// !nullcheck
	if (pTestModel)
	{
		pTestModel->m_pos = pos;
		pTestModel->m_rot = rot;
		pTestModel->m_move = move;
		// ����������
		pTestModel->Init();

		return pTestModel;
	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossBullet::Init(void)
{
	// ����������
	CBullet::Init();

	m_pModel = CModel::Create(m_pos, m_rot);
	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CANNON_BULLET);
	m_pModel->GetModelInfo()->SetModelStatus(m_pos, m_rot, model);

	m_nLife = 200;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBossBullet::Uninit(void)
{
	if (m_pModel != nullptr)
	{
		m_pModel->Uninit();
		m_pModel = nullptr;
	}
	CBullet::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossBullet::Update(void)
{
	// �Փ˔���
	Hit();
	if (m_pModel != nullptr)
	{
		m_pModel->GetModelInfo()->SetPos(m_pos);
	}
 	
	CBullet::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossBullet::Draw(void)
{
	CBullet::Draw();
}

//=============================================================================
// �Փ˔���
//=============================================================================
void CBossBullet::Hit(void)
{
	//CPlayer* pPlayer = nullptr;
	//pPlayer = (CPlayer*)GetTop(PRIORITY_CHARACTER);

	//if (pPlayer != nullptr)
	//{
	//	D3DXVECTOR3 RayDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//	BOOL bHit = FALSE;
	//	FLOAT fDistance = 0.0f;

	//	for (int nCount = 0; nCount < (int)GetModelInfo()->GetMesh()->GetNumFaces(); nCount++)
	//	{
	//		//������
	//		D3DXIntersect(
	//			GetModelInfo()->GetMesh(),
	//			&pPlayer->GetPos(),
	//			&RayDir,
	//			&bHit,
	//			nullptr,
	//			nullptr,
	//			nullptr,
	//			&fDistance,
	//			nullptr,
	//			nullptr);

	//		if (bHit && fDistance < 80.0f)
	//		{
	//			// ���n�̏���
	//			pPlayer->Landing(pPlayer->GetPos().y + fDistance);

	//			break;
	//		}
	//		else if (!bHit)
	//		{
	//			pPlayer->SetLanding(false);
	//		}
	//	}
	//}
}

//=============================================================================
// ���̃|�C���^����
//=============================================================================
void CBossBullet::Move()
{
}