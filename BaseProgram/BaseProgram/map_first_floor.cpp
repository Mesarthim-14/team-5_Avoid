//=============================================================================
//
// テストモデルクラス [map_first_floor.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "map_first_floor.h"
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
#define COLLISION_SIZE (D3DXVECTOR3(10500.0f,3100.0f,15350.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CMapFirstFloor::CMapFirstFloor(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CMapFirstFloor::~CMapFirstFloor()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CMapFirstFloor * CMapFirstFloor::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // メモリ確保
    CMapFirstFloor *pModel = new CMapFirstFloor(PRIORITY_TEST_MODEL);

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
HRESULT CMapFirstFloor::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_FIRST_FLOOR);
    GetModelInfo()->SetModelStatus(pos, rot, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //当たり判定モデル(OBB)の生成
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(pos, COLLISION_SIZE, rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COLLISION_SIZE.y / 2 + 50.0f), pos.z), D3DXVECTOR3(COLLISION_SIZE.x - 100.0f, 1.0f, COLLISION_SIZE.z - 100.0f), rot);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMapFirstFloor::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMapFirstFloor::Update()
{
    CModel::Update();

    // 当たり判定
    HitCol();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMapFirstFloor::Draw()
{
    CModel::Draw();
}

//=============================================================================
// 当たり判定
//=============================================================================
void CMapFirstFloor::HitCol()
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