//=============================================================================
//
// チェックポイントのオブジェ [map_check_floor2.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "map_check_floor2.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel_Cylinder.h"
#include "collision.h"
#include "blur_filter.h"
#include "gauss_filter.h"
#include "library.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define COLLISION_RADIUS (5000.0f)
#define COLLISION_LENGTH (12100.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CMapCheckFloor2::CMapCheckFloor2(PRIORITY Priority) : CMap(Priority)
{
    m_pColModelCylinder = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMapCheckFloor2::~CMapCheckFloor2()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CMapCheckFloor2 * CMapCheckFloor2::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // メモリ確保
    CMapCheckFloor2 *pModel = new CMapCheckFloor2(PRIORITY_MAP);

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
HRESULT CMapCheckFloor2::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // 初期化処理
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_CHECK_FLOOR2);
    GetModelInfo()->SetModelStatus(pos, rot, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // 当たり判定モデル(円柱)の生成
    m_pColModelCylinder = CCollisionModelCylinder::Create(pos, COLLISION_RADIUS, COLLISION_LENGTH, rot);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMapCheckFloor2::Uninit()
{
    // 当たり判定モデルの終了処理
    if (m_pColModelCylinder)
    {
        m_pColModelCylinder->Uninit();
        m_pColModelCylinder = nullptr;
    }

    // 終了処理
    CMap::Uninit();
}

//=============================================================================
// 当たり判定
//=============================================================================
void CMapCheckFloor2::Col()
{
    // 当たり判定
    if (m_pColModelCylinder)
    {
        HitColPlayer(m_pColModelCylinder);
        HitColBossBullet(m_pColModelCylinder);
    }
}