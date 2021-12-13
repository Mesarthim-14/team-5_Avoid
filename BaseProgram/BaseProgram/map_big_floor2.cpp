//=============================================================================
//
// 大きいオブジェクト [map_big_floor2.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "map_big_floor2.h"
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
// コンストラクタ
//=============================================================================
CMapBigFloor2::CMapBigFloor2(PRIORITY Priority) : CModel(Priority)
{
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
}

//=============================================================================
// デストラクタ
//=============================================================================
CMapBigFloor2::~CMapBigFloor2()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CMapBigFloor2 * CMapBigFloor2::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // メモリ確保
    CMapBigFloor2 *pModel = new CMapBigFloor2(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pModel)
    {
        // 初期化処理
        pModel->Init(pos, rot);
        return pModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMapBigFloor2::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_FIRST_FLOOR2);
    GetModelInfo()->SetModelStatus(pos, rot, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //当たり判定モデル(OBB)の生成
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(pos, D3DXVECTOR3(8800.0f, 11900.0f, 31500.0f), rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + 6000.0f, pos.z), D3DXVECTOR3(8500.0f, 100.0f, 31400.0f), rot);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMapBigFloor2::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMapBigFloor2::Update()
{
    CModel::Update();

    // 当たり判定
    HitCol();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMapBigFloor2::Draw()
{
    CModel::Draw();
}

//=============================================================================
// 当たり判定
//=============================================================================
void CMapBigFloor2::HitCol()
{
    // プレイヤーポインタの取得
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // プレイヤーの当たり判定モデルポインタの取得
    CCollisionModelOBB* pPlayerColModelOBB = pPlayer->GetColOBBPtr();

    // プレイヤーの当たり判定ポインタの取得
    CCollisionModelOBB::OBB playerObb;
    if (pPlayerColModelOBB)
    {
        playerObb = pPlayerColModelOBB->GetOBB();
    }
    else
        return;

    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_UP])
    {
        // 上面の当たり判定ポインタの取得
        CCollisionModelOBB::OBB surfaceUpObb = m_pColModelOBB[CCollisionModelOBB::SURFACE_UP]->GetOBB();

        if (CCollision::ColOBBs(surfaceUpObb, playerObb))
        {
            // 着地の処理
            pPlayer->Landing(surfaceUpObb.info.pos.y + (surfaceUpObb.info.size.y / 2) + (playerObb.info.size.y / 2));
            return;
        }
        else
        {
            // 着地判定の設定
            pPlayer->SetLanding(false);
        }
    }

    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        // 側面の当たり判定ポインタの取得
        CCollisionModelOBB::OBB surfaceSizeObb = m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]->GetOBB();

        if (CCollision::ColOBBs(surfaceSizeObb, playerObb))
        {
            // 落下の処理
            pPlayer->Fall();
            return;
        }
    }
}