//=============================================================================
//
// �e�X�g���f���N���X [test_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "test_model.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel_OBB.h"
#include "collision.h"
#include "blur_filter.h"
#include "gauss_filter.h"
#include "library.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS        (ZeroVector3)
#define TEST_ROT        (ZeroVector3)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTestModel::CTestModel(PRIORITY Priority) : CModel(Priority)
{
    m_pCollisionModelOBB = nullptr;
    m_pSqu1Back = nullptr;
    m_pGaussFilter = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTestModel::~CTestModel()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTestModel * CTestModel::Create()
{
    // �������m��
    CTestModel *pTestModel = new CTestModel(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pTestModel)
    {
        // ����������
        pTestModel->Init();

        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTestModel::Init()
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP);
    GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //�����蔻�胂�f���̐���
    if (!m_pCollisionModelOBB)
    {
        m_pCollisionModelOBB = CCollisionModelOBB::Create(GetModelInfo()->GetPos(), D3DXVECTOR3(5000.0f, 100.0f, 4200.0f), TEST_ROT);
    }

    // �K�E�X�t�B���^�[
    if (!m_pGaussFilter)
    {
    //    m_pGaussFilter = new CGaussFilter(pDevice);
    //    m_pGaussFilter->Load();
    //    m_pGaussFilter->Restore();
    }

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTestModel::Uninit()
{
    if (m_pGaussFilter)
    {
        m_pGaussFilter->Uninit();
        m_pGaussFilter = nullptr;
    }
    CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTestModel::Update()
{
    CModel::Update();

    if (m_pGaussFilter)
    {
//        m_pGaussFilter->UpdateWeight();
    }
    // �Փ˔���
//    Hit();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTestModel::Draw()
{
    if (m_pGaussFilter)
    {
     //   m_pGaussFilter->BeginSurface();
     //   m_pGaussFilter->Render(GetModelInfo()->GetModel(), mtxWorld);
     //   m_pGaussFilter->DrawPolygon();
    }
    CModel::Draw();
}

//=============================================================================
// �Փ˔���
//=============================================================================
void CTestModel::Hit()
{
    CPlayer* pPlayer = nullptr;
    pPlayer = (CPlayer*)GetTop(PRIORITY_CHARACTER);

    if (pPlayer)
    {
        D3DXVECTOR3 RayDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
        BOOL bHit = FALSE;
        FLOAT fDistance = 0.0f;

        for (int nCount = 0; nCount < (int)GetModelInfo()->GetMesh()->GetNumFaces(); nCount++)
        {
            //������
            D3DXIntersect(
                GetModelInfo()->GetMesh(),
                &pPlayer->GetPos(),
                &RayDir,
                &bHit,
                nullptr,
                nullptr,
                nullptr,
                &fDistance,
                nullptr,
                nullptr);

            if (bHit && fDistance < 80.0f)
            {
                // ���n�̏���
                pPlayer->Landing(pPlayer->GetPos().y + fDistance);

                break;
            }
            else if (!bHit)
            {
                pPlayer->SetLanding(false);
            }
        }
    }
}

//=============================================================================
// OBB�Փ˔���
//=============================================================================
void CTestModel::OBBs()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();

    if (pPlayer)
    {
        if (m_pCollisionModelOBB && pPlayer->GetColOBBPtr())
        {
            if (CCollision::ColOBBs(m_pCollisionModelOBB->GetOBB(), pPlayer->GetColOBBPtr()->GetOBB()))
            {
                // ���n�̏���
                pPlayer->Landing(pPlayer->GetPos().y);
            }
            else
            {
                // ���n����
                pPlayer->SetLanding(false);
            }
        }
    }
}