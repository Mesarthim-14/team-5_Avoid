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
#include "caution_boss_bullet_ui.h"
#include "collisionModel_Sphere.h"
#include "collisionModel_OBB.h"
#include "kraken.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS            (ZeroVector3)
#define TEST_ROT            (ZeroVector3)
#define COLLISION_RADIUS    (3750.0f)
#define COLLISION_SIZE_OBB  (D3DXVECTOR3(7500.0f, 7500.0f, 7500.0f))
#define SPEED               (400.0f)
#define LIFE                (300)
#define FIX_POS             (-15000.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CBossBullet::CBossBullet(PRIORITY Priority) : CBullet(Priority)
{
    m_pModel = nullptr;
    m_pCaution = nullptr;
    m_bDeath = false;
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
    CBossBullet *pBullet = new CBossBullet(PRIORITY_BULLET);

    // !nullcheck
    if (pBullet)
    {
        // 初期化処理
        pBullet->SetPos(pos);
        pBullet->SetRot(rot);
        pBullet->SetColRadius(COLLISION_RADIUS);
        pBullet->SetColSizeOBB(COLLISION_SIZE_OBB);
        pBullet->FixPos(pos);
        pBullet->Init();
        return pBullet;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBossBullet::Init()
{
    // 初期化処理
    CBullet::Init();

    m_pModel = CModel::Create(GetPos(), GetRot());
    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_KRAKEN_BULLET);
    m_pModel->GetModelInfo()->SetModelStatus(GetPos(), GetRot(), model);
    FollowPlayer();
    SetLife(LIFE);
    if (!m_pCaution)
    {
        m_pCaution = CCautionBossBulletUi::Create();
        m_pCaution->SetBulletPos(GetPos());
    }

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
    if (m_pCaution)
    {
        m_pCaution->Uninit();
        m_pCaution = nullptr;
    }

    CBullet::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBossBullet::Update()
{
    // 破棄判定がtrueのとき
    if (m_bDeath)
    {
        // 終了処理
        Uninit();
        return;
    }

    if (m_pModel)
    {
        m_pModel->GetModelInfo()->SetPos(GetPos());
    }

    // 当たり判定モデルの更新
    if (GetColSpherePtr())
    {
        GetColSpherePtr()->SetInfo(GetPos(), D3DXVECTOR3(COLLISION_RADIUS * 2, COLLISION_RADIUS * 2, COLLISION_RADIUS * 2), GetRot());
    }
    if (GetColOBBPtr())
    {
        GetColOBBPtr()->SetInfo(GetPos(), GetColOBBPtr()->GetOBB().info.size, GetRot());
    }

    // 警告
    if (m_pCaution)
    {
        m_pCaution->SetBulletPos(GetPos());
    }

    // 親クラスの更新処理
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
// 座標の修正
//=============================================================================
void CBossBullet::FixPos(const D3DXVECTOR3& pos)
{
    CKraken* pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    if (pKraken)
    {
        D3DXVECTOR3 rot = pKraken->GetRot();
        D3DXVECTOR3 FixPos = D3DXVECTOR3(
            pos.x +(sinf(rot.y))*FIX_POS,
            pos.y,
            pos.z + (cosf(rot.y))*FIX_POS);

        SetPos(FixPos);
    }
}