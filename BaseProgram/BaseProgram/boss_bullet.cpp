//=============================================================================
//
// ボスの発射弾 [boss_bullet.cpp]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "boss_bullet.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "collision.h"
#include "collisionModel_Sphere.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS            (ZeroVector3)
#define TEST_ROT            (ZeroVector3)
#define COLLISION_RADIUS    (900.0f)
#define SPEED               (150.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CBossBullet::CBossBullet(PRIORITY Priority) : CBullet(Priority)
{
    m_pModel = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBossBullet::~CBossBullet()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CBossBullet * CBossBullet::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // メモリ確保
    CBossBullet *pBullet = new CBossBullet(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pBullet)
    {
        // 初期化処理
        pBullet->Init(pos, rot);
        return pBullet;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBossBullet::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    SetPos(pos);
    SetRot(rot);
    SetSize(D3DXVECTOR3(COLLISION_RADIUS * 2, COLLISION_RADIUS * 2, COLLISION_RADIUS * 2));

    // 初期化処理
    CBullet::Init();

    m_pModel = CModel::Create(pos, rot);
    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_KRAKEN_BULLET);
    m_pModel->GetModelInfo()->SetModelStatus(pos, rot, model);
    FollowPlayer();
    SetLife(200);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBossBullet::Uninit()
{
    if (m_pModel)
    {
        m_pModel->Uninit();
        m_pModel = nullptr;
    }
    CBullet::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBossBullet::Update()
{
    if (m_pModel)
    {
        m_pModel->GetModelInfo()->SetPos(GetPos());
    }
     
    CBullet::Update();

    // 衝突判定
    Hit();
}

//=============================================================================
// 描画処理
//=============================================================================
void CBossBullet::Draw()
{
    CBullet::Draw();
}

//=============================================================================
// 衝突判定
//=============================================================================
void CBossBullet::Hit()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    //CPlayer* pPlayer = nullptr;
    //pPlayer = (CPlayer*)GetTop(PRIORITY_CHARACTER);

    if (pPlayer)
    {
        if (GetColSpherePtr() && pPlayer->GetColCapsulePtr())
        {
            if (CCollision::ColSphereAndCapsule(GetColSpherePtr()->GetInfo(), pPlayer->GetColCapsulePtr()->GetInfo()))
            {
                Uninit();
            }
        }
    }
}

//=============================================================================
// 移動量設定
//=============================================================================
void CBossBullet::FollowPlayer()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        D3DXVECTOR3 This = GetPos();
        D3DXVECTOR3 Target = pPlayer->GetPos();
        // 2点間のベクトルを求める（終点[目標地点] - 始点[自身の位置]）
        D3DXVECTOR3 Vector = Target - This;
        Vector = *D3DXVec3Normalize(&Vector, &Vector);
        Vector *= SPEED;

        // 移動量設定
        SetMove(Vector);
    }
}

//=============================================================================
// 情報のポインタ生成
//=============================================================================
void CBossBullet::Move()
{
}