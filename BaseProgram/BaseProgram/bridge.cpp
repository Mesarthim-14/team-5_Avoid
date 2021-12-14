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
#define COLLISION_SIZE (D3DXVECTOR3(6000.0f, 80.0f, 500.0f))   // 当たり判定の大きさ

//=============================================================================
// コンストラクタ
//=============================================================================
CBridge::CBridge(PRIORITY Priority) : CModel(Priority)
{
    m_pColModelOBB = nullptr;
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
    CBridge *pTestModel = new CBridge(PRIORITY_TEST_MODEL);

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
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_BRIDGE);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // 当たり判定(OBB)の生成
    if (!m_pColModelOBB)
    {
        m_pColModelOBB = CCollisionModelOBB::Create(pos, COLLISION_SIZE, rot);
    }

    return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CBridge::Update()
{
    // 更新処理
    CModel::Update();

    // OBB同士の当たり判定
    HitOBBs();
}

//=============================================================================
// OBB同士の当たり判定
//=============================================================================
void CBridge::HitOBBs()
{
    // プレイヤーポインタの取得
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // プレイヤーの当たり判定モデルポインタの取得
    CCollisionModelOBB* pPlayerColModelOBB = pPlayer->GetColOBBPtr();

    if (m_pColModelOBB && pPlayerColModelOBB)
    {
        if (CCollision::ColOBBs(m_pColModelOBB->GetOBB(), pPlayerColModelOBB->GetOBB()))
        {
            // 着地の処理
            pPlayer->Landing(m_pColModelOBB->GetOBB().info.pos.y + (m_pColModelOBB->GetOBB().info.size.y / 2) + (pPlayerColModelOBB->GetInfo().size.y / 2));
        }
    }
}