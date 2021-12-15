//=============================================================================
//
// 大きいオブジェクト [map_big_floor2.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "map.h"
#include "manager.h"
#include "player.h"
#include "collision.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMap::CMap(PRIORITY Priority) : CModel(Priority)
{
    m_bHitOld = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMap::~CMap()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMap::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // 初期化処理
    CModel::Init();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMap::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMap::Update()
{
    CModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMap::Draw()
{
    CModel::Draw();
}

//=============================================================================
// 当たり判定(直方体同士)
//=============================================================================
void CMap::HitColOBBs(CCollisionModelOBB** pMapColOBB)
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

    if (pMapColOBB[CCollisionModelOBB::SURFACE_UP])
    {
        // 上面の当たり判定ポインタの取得
        CCollisionModelOBB::OBB surfaceUpObb = pMapColOBB[CCollisionModelOBB::SURFACE_UP]->GetOBB();

        if (CCollision::ColOBBs(surfaceUpObb, playerObb))
        {
            // 着地の処理
            pPlayer->Landing(surfaceUpObb.info.pos.y + (surfaceUpObb.info.size.y / 2) + (playerObb.info.size.y / 2));
            m_bHitOld = true;
            return;
        }
        else
        {
            if (m_bHitOld)
            {
                // 着地判定の設定
                pPlayer->SetLanding(false);
                m_bHitOld = false;
            }
        }
    }

    if (pMapColOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        // 側面の当たり判定ポインタの取得
        CCollisionModelOBB::OBB surfaceSizeObb = pMapColOBB[CCollisionModelOBB::SURFACE_SIDE]->GetOBB();

        if (CCollision::ColOBBs(surfaceSizeObb, playerObb))
        {
            // 落下の処理
            pPlayer->Fall();
            return;
        }
    }
}

//=============================================================================
// 当たり判定(球体と円柱)
//=============================================================================
void CMap::HitColSphereAndCylinder(CCollisionModelCylinder * pMapColCylinder)
{
    // プレイヤーポインタの取得
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // プレイヤーの当たり判定モデルポインタの取得
    CCollisionModelCapsule* pPlayerColModelCapsule = pPlayer->GetColCapsulePtr();
    if (!pPlayerColModelCapsule)
        return;

    // プレイヤーの当たり判定モデル(カプセル)の情報取得
    CCollisionModelCapsule::INFO PlayerColModelCapsuleInfo = pPlayerColModelCapsule->GetInfo();

    // プレイヤーの当たり判定モデル(カプセル)情報から球体の情報を設定
    CCollisionModelSphere::SPHERE PlayerColModelSphereInfo =
    {
        {
            PlayerColModelCapsuleInfo.detail.sphere2.pos,
            D3DXVECTOR3(PlayerColModelCapsuleInfo.detail.sphere2.radius * 2, PlayerColModelCapsuleInfo.detail.sphere2.radius * 2, PlayerColModelCapsuleInfo.detail.sphere2.radius * 2),
            PlayerColModelCapsuleInfo.detail.sphere2.rot
        },
        PlayerColModelCapsuleInfo.radius
    };

    // 当たり判定モデル(円柱)情報の取得
    CCollisionModelCylinder::CYLINDER colCylinderInfo;
    if (pMapColCylinder)
    {
        colCylinderInfo = pMapColCylinder->GetCylinder();
    }
    else
        return;

    bool bHit = false;                                      // 当たったかの判定
    CCollision::SURFACE surface = CCollision::SURFACE_NONE; // 当たった面

    // 当たり判定(球体と円柱)
    CCollision::ColSphereAndCylinder(bHit, surface, PlayerColModelSphereInfo, colCylinderInfo);

    if (bHit)
    {
        if (surface == CCollision::SURFACE_UP)
        {
            // 着地の処理
            pPlayer->Landing(colCylinderInfo.info.pos.y + (colCylinderInfo.length / 2) + (PlayerColModelCapsuleInfo.length / 2));
            return;
        }
        else if (surface == CCollision::SURFACE_SIDE)
        {
            // 落下の処理
            pPlayer->Fall();
            return;
        }
    }
}