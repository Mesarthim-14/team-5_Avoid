//=============================================================================
//
// テストモデルクラス [test_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
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
// マクロ定義
//=============================================================================
#define TEST_POS        (ZeroVector3)
#define TEST_ROT        (ZeroVector3)

//=============================================================================
// コンストラクタ
//=============================================================================
CTestModel::CTestModel(PRIORITY Priority) : CModel(Priority)
{
    m_pCollisionModelOBB = nullptr;
    m_pSqu1Back = nullptr;
    m_pGaussFilter = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTestModel::~CTestModel()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTestModel * CTestModel::Create()
{
    // メモリ確保
    CTestModel *pTestModel = new CTestModel(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pTestModel)
    {
        // 初期化処理
        pTestModel->Init();

        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTestModel::Init()
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP);
    GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //当たり判定モデルの生成
    if (!m_pCollisionModelOBB)
    {
        m_pCollisionModelOBB = CCollisionModelOBB::Create(GetModelInfo()->GetPos(), D3DXVECTOR3(5000.0f, 100.0f, 4200.0f), TEST_ROT);
    }

    // ガウスフィルター
    if (!m_pGaussFilter)
    {
    //    m_pGaussFilter = new CGaussFilter(pDevice);
    //    m_pGaussFilter->Load();
    //    m_pGaussFilter->Restore();
    }

    return S_OK;
}

//=============================================================================
// 終了処理
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
// 更新処理
//=============================================================================
void CTestModel::Update()
{
    CModel::Update();

    if (m_pGaussFilter)
    {
//        m_pGaussFilter->UpdateWeight();
    }
    // 衝突判定
//    Hit();
}

//=============================================================================
// 描画処理
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
// 衝突判定
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
            //下方向
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
                // 着地の処理
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
// OBB衝突判定
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
                // 着地の処理
                pPlayer->Landing(pPlayer->GetPos().y);
            }
            else
            {
                // 着地処理
                pPlayer->SetLanding(false);
            }
        }
    }
}