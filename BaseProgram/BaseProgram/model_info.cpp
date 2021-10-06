//=============================================================================
//
// �K�w�\���p�̃��f���N���X���� [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "model_info.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "shadow.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelInfo::CModelInfo()
{
	//�e�����o�ϐ��̃N���A
	memset(&m_model, 0, sizeof(m_model));
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	ZeroMemory(m_OldMtxWorld, sizeof(m_OldMtxWorld));
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
	m_pShadow = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelInfo::~CModelInfo()
{
	// �|�C���^�̊J��
	HasPtrDelete();
}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CModelInfo * CModelInfo::Create(void)
{
	//�K�w���f���N���X�̃|�C���^�ϐ�
	CModelInfo *pModelInfo = new CModelInfo;

	// !nullcheck
	if (pModelInfo)
	{
		//�����������Ăяo��
		pModelInfo->Init();

		return pModelInfo;
	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CModelInfo::Init(void)
{

	return S_OK;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModelInfo::Draw(D3DXVECTOR3 rot)
{
}

//=============================================================================
// �e�̕`��
//=============================================================================
void CModelInfo::ShadowDraw(D3DXVECTOR3 rot)
{
	if (m_pShadow)
	{
		// �e�̕`�揈��
		m_pShadow->VolumeDraw();
	}
}

//=============================================================================
// �e�̃|�C���^����
//=============================================================================
void CModelInfo::CreateShadowPtr(void)
{
	if (m_bUseShadow)
	{
		// nullcheck
		if (!m_pShadow)
		{
			// �e�̐���
			m_pShadow = CShadow::Create(m_model.pMesh);
		}
	}
}

//=============================================================================
// �e�̏��̐ݒ�
//=============================================================================
D3DXMATRIX CModelInfo::SetShadowInfo(D3DXVECTOR3 rot, D3DXMATRIX pParent)
{
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxWorld;                            // ���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &pParent);

	return mtxWorld;
}

//=============================================================================
// �ێ��|�C���^�̊J������
//=============================================================================
void CModelInfo::HasPtrDelete(void)
{
	if (m_pShadow)
	{
		// �e�̏I������
		m_pShadow->Uninit();
		delete m_pShadow;
		m_pShadow = nullptr;
	}
}

//=============================================================================
// ���f���̏��ݒ�
//=============================================================================
void CModelInfo::SetModelStatus(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model)
{
	m_pos = pos;
	m_rot = rot;
	m_model = model;
}

//=============================================================================
// ���[���h�}�g���N�X���W
//=============================================================================
D3DXVECTOR3 CModelInfo::GetMtxPos(void)
{
	D3DXMATRIX mtxWorld = GetMtxWorld();
	return D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
}