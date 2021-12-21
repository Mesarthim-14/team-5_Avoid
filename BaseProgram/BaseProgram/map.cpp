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
#include "game.h"
#include "kraken.h"
#include "state_kraken_normal.h"
#include "boss_bullet.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CMap::m_bHitMap = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CMap::CMap(PRIORITY Priority) : CModel(Priority)
{
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
HRESULT CMap::Init()
{
    // モデルの初期化処理
    CModel::Init();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMap::Uninit()
{
    // モデルの終了処理
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMap::Update()
{
    // モデルの更新処理
    CModel::Update();

    // 当たり判定処理
    Col();

    // 次のオブジェクト(プライオリティ：マップ)がないとき
    if (!GetNext())
    {
        // １つ以上マップに当たっているかの判定を初期化
        m_bHitMap = false;
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CMap::Draw()
{
    // モデルの描画処理
    CModel::Draw();
}

//=============================================================================
// プレイヤーとの当たり判定(直方体同士)
//=============================================================================
void CMap::HitColOBBsPlayer(const CCollisionModelOBB* const* pMapColOBB)
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
            m_bHitMap = true;
            return;
        }
        else
        {
            if (!m_bHitMap)
            {
                // 着地判定の設定
                pPlayer->SetLanding(false);
            }
        }
    }

    if (pMapColOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        // 側面の当たり判定ポインタの取得
        CCollisionModelOBB::OBB surfaceSideObb = pMapColOBB[CCollisionModelOBB::SURFACE_SIDE]->GetOBB();

        if (CCollision::ColOBBs(surfaceSideObb, playerObb))
        {
            // 落下の処理
            pPlayer->Fall();
            return;
        }
    }
}

//=============================================================================
// ボスバレットとの当たり判定(直方体同士)
//=============================================================================
void CMap::HitColOBBsBossBullet(const CCollisionModelOBB* const* pMapColOBB)
{
    // 弾のポインタの取得
    CBossBullet* pBossBullet = (CBossBullet*)GetTop(PRIORITY_BULLET);
    if (!pBossBullet)
        return;

    if (pMapColOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        // 側面の当たり判定ポインタの取得
        CCollisionModelOBB::OBB surfaceSideObb = pMapColOBB[CCollisionModelOBB::SURFACE_SIDE]->GetOBB();

        while (pBossBullet)
        {
            // 当たり判定(球体とOBB)がtrue かつ 弾の破棄判定がfalseのとき
            if (CCollision::ColOBBs(pBossBullet->GetColOBBPtr()->GetOBB(), surfaceSideObb) && !pBossBullet->GetDeath())
            {
                // 弾の破棄判定をtrueにする
                pBossBullet->SetDeath();
                return;
            }

            pBossBullet = (CBossBullet*)pBossBullet->GetNext();
        }
    }
}

//=============================================================================
// プレイヤーとの当たり判定関数(球体と円柱)
//=============================================================================
void CMap::HitColPlayer(const CCollisionModelCylinder* const pMapColCylinder)
{
    // 当たり判定モデル(円柱)情報の取得
    CCollisionModelCylinder::CYLINDER colCylinderInfo;
    if (pMapColCylinder)
    {
        colCylinderInfo = pMapColCylinder->GetCylinder();
    }
    else
        return;

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
            m_bHitMap = true;
            return;
        }
        else if (surface == CCollision::SURFACE_SIDE)
        {
            // 落下の処理
            pPlayer->Fall();
            m_bHitMap = true;
            return;
        }
    }
    else
    {
        if (!m_bHitMap)
        {
            // 着地判定の設定
            pPlayer->SetLanding(false);
        }
    }
}

//=============================================================================
// ボスバレットとの当たり判定関数(球体と円柱)
//=============================================================================
void CMap::HitColBossBullet(const CCollisionModelCylinder* const pMapColCylinder)
{
    // 当たり判定モデル(円柱)情報の取得
    CCollisionModelCylinder::CYLINDER colCylinderInfo;
    if (pMapColCylinder)
    {
        colCylinderInfo = pMapColCylinder->GetCylinder();
    }
    else
        return;

    // 弾のポインタの取得
    CBossBullet* pBossBullet = (CBossBullet*)GetTop(PRIORITY_BULLET);
    if (!pBossBullet)
        return;

    bool bHit = false;                                      // 当たったかの判定
    CCollision::SURFACE surface = CCollision::SURFACE_NONE; // 当たった面

    while (pBossBullet)
    {
        // 当たり判定用変数の初期化
        bHit = false;
        surface = CCollision::SURFACE_NONE;

        // 当たり判定(球体と円柱)
        CCollision::ColSphereAndCylinder(bHit, surface, pBossBullet->GetColSpherePtr()->GetSphere(), colCylinderInfo);

        if (bHit && !pBossBullet->GetDeath())
        {
            // 弾の破棄判定をtrueにする
            pBossBullet->SetDeath();
            return;
        }

        pBossBullet = (CBossBullet*)pBossBullet->GetNext();
    }
}