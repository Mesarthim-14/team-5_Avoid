//=============================================================================
//
// 回転床クラス [rotate_floor.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "rotate_floor.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "collision.h"
#include "collisionModel_Cylinder.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS    (D3DXVECTOR3(-34328.4f, 0.0f, -6081.8f))
#define TEST_ROT    (D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))
#define ROTATE_NUM  (D3DXToRadian(2.0f))                                    // 回転の値
#define COLLISION_RADIUS    (1500.0f)                                       // 当たり判定モデル(円柱)の半径の大きさ
#define COLLISION_LENGTH    (400.0f)                                        // 当たり判定モデル(円柱)の縦の大きさ
#define COLLISION_ROT       (D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f))  // 当たり判定モデル(円柱)の角度

//=============================================================================
// コンストラクタ
//=============================================================================
CRotateFloor::CRotateFloor(PRIORITY Priority) : CModel(Priority)
{
    m_pColModelCylinder = nullptr;
}

//=============================================================================
// インスタンス生成
//=============================================================================
CRotateFloor * CRotateFloor::Create(const D3DXVECTOR3 &pos)
{
    // メモリ確保
    CRotateFloor *pTestModel = new CRotateFloor(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pTestModel)
    {
        // 初期化処理
        pTestModel->Init(pos);

        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRotateFloor::Init(const D3DXVECTOR3 &pos)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ROTATE_FLOOR);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    // 当たり判定モデル(円柱)の生成
    if (!m_pColModelCylinder)
    {
        m_pColModelCylinder = CCollisionModelCylinder::Create(pos, COLLISION_RADIUS, COLLISION_LENGTH, COLLISION_ROT);
    }

    return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CRotateFloor::Update()
{
    // 更新処理
    CModel::Update();

    if (m_pColModelCylinder)
    {
        // 当たり判定モデル(円柱)の情報取得
        CCollisionModelCylinder::CYLINDER ColModelCylinderInfo = m_pColModelCylinder->GetCylinder();

        // 当たり判定モデル(円柱)の設定
        m_pColModelCylinder->SetInfo(GetPos(),
            ColModelCylinderInfo.info.size,
            D3DXVECTOR3(ColModelCylinderInfo.info.rot.x, GetRot().y, ColModelCylinderInfo.info.rot.z));
    }

    // 円柱と球体の当たり判定
    HitCylinderAndSphere();
}

//=============================================================================
// 円柱と球体の当たり判定
//=============================================================================
void CRotateFloor::HitCylinderAndSphere()
{
    // プレイヤーポインタの取得
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // プレイヤーの当たり判定モデルポインタの取得
    CCollisionModelCapsule* pPlayerColModelCapsule = pPlayer->GetColCapsulePtr();

    // プレイヤーの当たり判定モデル(カプセル)の情報取得
    CCollisionModelCapsule::INFO PlayerColModelCapsuleInfo = pPlayerColModelCapsule->GetInfo();

    if (m_pColModelCylinder && pPlayerColModelCapsule)
    {
        CCollisionModelSphere::SPHERE PlayerColModelSphereInfo =
        {
            {
                PlayerColModelCapsuleInfo.P1,
                D3DXVECTOR3(PlayerColModelCapsuleInfo.radius * 2, PlayerColModelCapsuleInfo.radius * 2, PlayerColModelCapsuleInfo.radius * 2),
                PlayerColModelCapsuleInfo.rot
            },
            PlayerColModelCapsuleInfo.radius
        };

        // 当たり判定モデル(円柱)の情報取得
        CCollisionModelCylinder::CYLINDER ColModelCylinderInfo = m_pColModelCylinder->GetCylinder();

        // 当たり判定用変数
        bool bHit = false;                                      // 衝突判定
        CCollision::SURFACE surface = CCollision::SURFACE_NONE; // 衝突面

        // 円柱と球体の当たり判定
        CCollision::ColSphereAndCylinder(bHit, surface, PlayerColModelSphereInfo, ColModelCylinderInfo);

        if (bHit)
        { // 当たっているとき

            if (surface == CCollision::SURFACE_UP)
            {
                // 着地の処理
                pPlayer->Landing(ColModelCylinderInfo.info.pos.y + (ColModelCylinderInfo.length / 2) + (PlayerColModelCapsuleInfo.length / 2));
            }
            else
            {
                D3DXVECTOR3 playerOldPos = pPlayer->GetOldPos();
                pPlayer->SetPos(D3DXVECTOR3(playerOldPos.x, pPlayer->GetPos().y, playerOldPos.z));
            }
        }
    }
}