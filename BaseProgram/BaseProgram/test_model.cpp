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

    //�����蔻�胂�f���̐���
    if (!m_pCollisionModelOBB)
    {
        //m_pCollisionModelOBB = CCollisionModelOBB::Create(GetModelInfo()->GetPos(), D3DXVECTOR3(5000.0f, 100.0f, 4200.0f), TEST_ROT);
    }

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTestModel::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTestModel::Update()
{
    CModel::Update();

    // �Փ˔���
    HitOBBs();
    Hit();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTestModel::Draw()
{
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
// OBB���m�̓����蔻��
//=============================================================================
void CTestModel::HitOBBs()
{
    // �v���C���[�|�C���^�̎擾
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // �v���C���[�̓����蔻�胂�f���|�C���^�̎擾
    CCollisionModelOBB* pPlayerColModelOBB = pPlayer->GetColOBBPtr();

    if (m_pCollisionModelOBB && pPlayerColModelOBB)
    {
        if (CCollision::ColOBBs(m_pCollisionModelOBB->GetOBB(), pPlayerColModelOBB->GetOBB()))
        {
            // ���n�̏���
            pPlayer->Landing(m_pCollisionModelOBB->GetOBB().info.pos.y + (m_pCollisionModelOBB->GetOBB().info.size.y / 2) + (pPlayerColModelOBB->GetOBB().info.size.y / 2));
        }
    }
}