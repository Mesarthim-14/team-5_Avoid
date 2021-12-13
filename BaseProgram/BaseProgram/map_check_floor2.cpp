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
#define COLLISION_LENGTH (11900.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CMapCheckFloor2::CMapCheckFloor2(PRIORITY Priority) : CModel(Priority)
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
    CMapCheckFloor2 *pModel = new CMapCheckFloor2(PRIORITY_TEST_MODEL);

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
    CModel::Init();

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
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMapCheckFloor2::Update()
{
    CModel::Update();

    // 当たり判定
    HitCol();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMapCheckFloor2::Draw()
{
    CModel::Draw();
}

//=============================================================================
// 当たり判定
//=============================================================================
void CMapCheckFloor2::HitCol()
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
    CCollisionModel::INFO PlayerColModelSphereInfo =
    {
        PlayerColModelCapsuleInfo.P1,
        D3DXVECTOR3(PlayerColModelCapsuleInfo.radius * 2, PlayerColModelCapsuleInfo.radius * 2, PlayerColModelCapsuleInfo.radius * 2),
        PlayerColModelCapsuleInfo.rot
    };

    // 当たり判定モデル(円柱)情報の取得
    CCollisionModel::INFO colCylinderInfo;
    if (m_pColModelCylinder)
    {
        colCylinderInfo = m_pColModelCylinder->GetInfo();
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
            pPlayer->Landing(colCylinderInfo.pos.y + (colCylinderInfo.size.z / 2) + (PlayerColModelCapsuleInfo.length / 2));
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