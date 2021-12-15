//=============================================================================
//
// 立方体の床クラス [map_square_floor2.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "map_square_floor2.h"
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
#define COLLISION_SIZE (D3DXVECTOR3(8000.0f,11900.0f,8000.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CMapSquareFloor2::CMapSquareFloor2(PRIORITY Priority) : CMap(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CMapSquareFloor2::~CMapSquareFloor2()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CMapSquareFloor2 * CMapSquareFloor2::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // メモリ確保
    CMapSquareFloor2 *pModel = new CMapSquareFloor2(PRIORITY_TEST_MODEL);

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
HRESULT CMapSquareFloor2::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MAP_SQUARE_FLOOR2);
    GetModelInfo()->SetModelStatus(pos, rot, model);
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //当たり判定モデル(OBB)の生成
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(pos, COLLISION_SIZE, rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COLLISION_SIZE.y / 2 + 100.0f), pos.z), D3DXVECTOR3(COLLISION_SIZE.x - 100.0f, 100.0f, COLLISION_SIZE.z - 100.0f), rot);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMapSquareFloor2::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMapSquareFloor2::Update()
{
    CModel::Update();

    // 当たり判定
    if (m_pColModelOBB)
    {
        HitColOBBs(m_pColModelOBB);
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CMapSquareFloor2::Draw()
{
    CModel::Draw();
}