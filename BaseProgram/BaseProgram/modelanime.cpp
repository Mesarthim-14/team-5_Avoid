//=============================================================================
//
// �K�w�\���p�̃��f���N���X [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "modelanime.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "shadow.h"
#include "model_info.h"
#include "library.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelAnime::CModelAnime()
{
    //�e�����o�ϐ��̃N���A
    m_posAnime = ZeroVector3;
    m_rotAnime = ZeroVector3;
    m_pParent = nullptr;
    m_bRotCalculation = false;
    m_pModelInfo = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelAnime::~CModelAnime()
{
    // �|�C���^�̊J��
    HasPtrDelete();
}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CModelAnime * CModelAnime::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXfile::MODEL &model)
{
    // �C���X�^���X����
    CModelAnime *pModelAnime = new CModelAnime;

    // !nullcheck
    if (pModelAnime)
    {
        //�����������Ăяo��
        pModelAnime->Init(pos, rot, model);
        return pModelAnime;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CModelAnime::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXfile::MODEL &model)
{
    // ���f�����̃|�C���^�쐬
    CreateInfoPtr();

    return S_OK;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModelAnime::Draw(const D3DXVECTOR3 &rot)
{
    //�f�o�C�X���̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    D3DXMATRIX mtxParent, mtxWorld;
    D3DMATERIAL9 matDef;                        //���݂̃}�e���A���ێ��p
    D3DXMATERIAL*pMat;                            //�}�e���A���f�[�^�ւ̃|�C���^
    D3DXVECTOR3 pos = m_pModelInfo->GetPos();

    // �}�g���N�X�v�Z
    CLibrary::ConfigMatrix(&mtxWorld, pos, m_rotAnime);

    //�e�����݂���ꍇ
    if (m_pParent)
    {
        //�e����ݒ�
        mtxParent = m_pParent->GetModelInfo()->GetMtxWorld();
    }
    //�e�����݂��Ȃ��ꍇ
    else
    {
        //�f�o�C�X����ݒ�
        pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
    }

    //�e�̃}�g���N�X�Ɗ|�����킹��
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

    //���[���h�}�g���N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
    m_pModelInfo->SetMtxWorld(mtxWorld);

    //���݂̃}�e���A�����擾����
    pDevice->GetMaterial(&matDef);

    //�}�e���A���f�[�^�ւ̃|�C���^���擾
    CXfile::MODEL model = m_pModelInfo->GetModel();
    pMat = (D3DXMATERIAL*)model.pBuffMat->GetBufferPointer();
    for (int nCntMat = 0; nCntMat < (int)model.dwNumMat; nCntMat++)
    {
        //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
        pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

        //�}�e���A���̐ݒ�
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

        if (model.apTexture[nCntMat])
        {
            // �e�N�X�`���̐ݒ�
            pDevice->SetTexture(0, model.apTexture[nCntMat]);
        }
        else
        {
            // �e�N�X�`���ݒ�
            pDevice->SetTexture(0, nullptr);
        }

        //���f���p�[�c�̕`��
        model.pMesh->DrawSubset(nCntMat);

        // �����x�߂�
        pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
    }

    //�ێ����Ă����}�e���A����߂�
    pDevice->SetMaterial(&matDef);

    // �e�̐ݒ�
    CShadow *pShadow = m_pModelInfo->GetShadow();
    if (pShadow)
    {
        D3DXVECTOR3 thisRot = m_pModelInfo->GetRot();

        // �e�̏c��]�̌v�Z���L�����ǂ���
        if (m_bRotCalculation)
        {
            pShadow->CreateShadow(thisRot, rot, m_pModelInfo->SetShadowInfo(rot, mtxParent));
        }
        else
        {
            pShadow->CreateShadow(thisRot + rot, mtxWorld);
        }
    }
}

//=============================================================================
// �e�̕`��
//=============================================================================
void CModelAnime::ShadowDraw(const D3DXVECTOR3 &rot)
{
    CShadow *pShadow = m_pModelInfo->GetShadow();

    if (pShadow)
    {
        // �e�̕`�揈��
        pShadow->VolumeDraw();
    }
}

//=============================================================================
// ���|�C���^����
//=============================================================================
void CModelAnime::CreateInfoPtr()
{
    if (!m_pModelInfo)
    {
        m_pModelInfo = CModelInfo::Create(CModelInfo::MODEL_TYPE_NONE);
    }
}

//=============================================================================
// �ێ��|�C���^�̊J������
//=============================================================================
void CModelAnime::HasPtrDelete()
{
    if (m_pModelInfo)
    {
        // �e�̏I������
        m_pModelInfo->Uninit();
        m_pModelInfo = nullptr;
    }
}
