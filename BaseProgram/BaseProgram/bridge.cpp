//=============================================================================
//
// 橋クラス [bridge.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "bridge.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collision.h"
#include "collisionModel_OBB.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define COLLISION_SIZE (D3DXVECTOR3(12000.0f, 500.0f, 800.0f))   // 当たり判定の大きさ

//=============================================================================
// コンストラクタ
//=============================================================================
CBridge::CBridge(PRIORITY Priority) : CMap(Priority)
{
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
}

//=============================================================================
// デストラクタ
//=============================================================================
CBridge::~CBridge()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CBridge * CBridge::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // メモリ確保
    CBridge *pTestModel = new CBridge(PRIORITY_MAP);

    // !nullcheck
    if (pTestModel)
    {
        // 初期化処理
        pTestModel->Init(pos, rot);
        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBridge::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // 初期化処理
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_BRIDGE);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // 当たり判定(OBB)の生成
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COLLISION_SIZE.y / 2) + 670.0f, pos.z), D3DXVECTOR3(COLLISION_SIZE.x, 1.0f, COLLISION_SIZE.z), rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f + 670.0f, pos.z), COLLISION_SIZE, rot);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBridge::Uninit()
{
    // 当たり判定モデルの終了処理
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]->Uninit();
        m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = nullptr;
    }
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_UP])
    {
        m_pColModelOBB[CCollisionModelOBB::SURFACE_UP]->Uninit();
        m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = nullptr;
    }

    // 終了処理
    CMap::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBridge::Update()
{
    // 更新処理
    CMap::Update();
}

//=============================================================================
// OBB同士の当たり判定
//=============================================================================
void CBridge::Col()
{
    // 当たり判定
    if (m_pColModelOBB)
    {
        HitColOBBsPlayer(m_pColModelOBB);
        HitColOBBsBossBullet(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
    }
}