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
// static�錾������
//=============================================================================
list<CModelInfo*> CModelInfo::m_ModelInfoList[MODEL_TYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelInfo::CModelInfo(const MODEL_TYPE &type)
{
    //�e�����o�ϐ��̃N���A
    memset(&m_model, 0, sizeof(m_model));
    m_pos = ZeroVector3;
    m_rot = ZeroVector3;
    ZeroMemory(m_OldMtxWorld, sizeof(m_OldMtxWorld));
    ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
    m_pShadow = nullptr;
    m_type = type;

    // ���X�g�֒ǉ�
    m_ModelInfoList[type].push_back(this);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelInfo::~CModelInfo()
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CModelInfo * CModelInfo::Create(const MODEL_TYPE &type)
{
    //�K�w���f���N���X�̃|�C���^�ϐ�
    CModelInfo *pModelInfo = new CModelInfo(type);

    // nullcheck
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
HRESULT CModelInfo::Init()
{

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModelInfo::Uninit()
{
    // �|�C���^�̊J��
    HasPtrDelete();
    int nCount = 0;

    // ���g��
    for (auto &itr = m_ModelInfoList[m_type].begin(); itr != m_ModelInfoList[m_type].end(); ++itr)
    {
        if (*itr == this)
        {
            itr = m_ModelInfoList[m_type].erase(itr);
            break;
        }
    }

    delete this;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModelInfo::Draw(const D3DXVECTOR3 &rot)
{
}

//=============================================================================
// �e�̕`��
//=============================================================================
void CModelInfo::ShadowDraw(const D3DXVECTOR3 &rot)
{
    if (m_pShadow)
    {
        // �e�̐���
        m_pShadow->CreateShadow(m_rot, m_mtxWorld);

        // �e�̕`�揈��
        m_pShadow->VolumeDraw();
    }
}

//=============================================================================
// �e�̃|�C���^����
//=============================================================================
void CModelInfo::CreateShadowPtr()
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
D3DXMATRIX CModelInfo::SetShadowInfo(const D3DXVECTOR3 &rot, const D3DXMATRIX &pParent)
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
void CModelInfo::HasPtrDelete()
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
void CModelInfo::SetModelStatus(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXfile::MODEL &model)
{
    m_pos = pos;
    m_rot = rot;
    m_model = model;
}

//=============================================================================
// ���[���h�}�g���N�X���W
//=============================================================================
D3DXVECTOR3 CModelInfo::GetMtxPos()
{
    return D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
}