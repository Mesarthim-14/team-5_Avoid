//=============================================================================
//
// 大砲の弾クラス [cannon_bullet.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "cannon_bullet.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "kraken.h"
#include "library.h"
#include "collisionModel_OBB.h"
#include "kraken.h"
#include "particlecannon.h"
#include "collision.h"
#include "particlenormal.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SPEED       (100.0f)
#define SPEED_Y     (50.0f)
#define POS_FIX     (1000.0f)
#define POS_FIX_Y   (700.0f)
#define GRAVITY_NUM (0.65f)

#define SIZE (D3DXVECTOR3(200.0f, 200.0f, 200.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CCannonBullet::CCannonBullet(PRIORITY Priority) : CModel(Priority)
{
    m_fDistanceToKraken = 0.0f;
    m_KrakenPos = ZeroVector3;
    m_pCollision = nullptr;
    m_bHit = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCannonBullet::~CCannonBullet()
{
    if (m_pCollision)
    {
        m_pCollision->Uninit();
        m_pCollision = nullptr;
    }
}

//=============================================================================
// インスタンス生成
//=============================================================================
CCannonBullet * CCannonBullet::Create(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot)
{
    // メモリ確保
    CCannonBullet *pCannonBullet = new CCannonBullet(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pCannonBullet)
    {
        // 初期化処理
        pCannonBullet->Init(CannonPos, CannonRot);
        return pCannonBullet;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCannonBullet::Init(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot)
{
    D3DXVECTOR3 pos = CannonPos;

    // バレットの情報設定
    SetBulletInfo(pos, CannonRot);

    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CANNON_BULLET);
    GetModelInfo()->SetModelStatus(pos, ZeroVector3, model);

    // エフェクト表示
    CParticleNormal::Create(pos, CannonRot);
    
    if (!m_pCollision)
    {
        m_pCollision = CCollisionModelOBB::Create(pos, SIZE, ZeroVector3);
    }
    return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CCannonBullet::Update()
{
    CModel::Update();
    
    // 距離計算
    CalDistance();

    if (m_pCollision)
    {
        m_pCollision->SetInfo(GetPos(), m_pCollision->GetOBB().info.size, GetRot());
    }

    Collision();
}

//=============================================================================
// 距離の計算
//=============================================================================
void CCannonBullet::CalDistance()
{
    float fCurDistance = CLibrary::CalDistance(GetPos(), m_KrakenPos);
    if (fCurDistance * 0.5f <= m_fDistanceToKraken)
    {
        GetMove().y -= GRAVITY_NUM;
    }
}

//=============================================================================
// 弾の情報
//=============================================================================
void CCannonBullet::SetBulletInfo(D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // 大砲の中心が違うので、座標をずらす
    pos = D3DXVECTOR3(
        pos.x + (sinf(rot.y)*POS_FIX),
        pos.y + POS_FIX_Y,
        pos.z + (cos(rot.y)*POS_FIX));

    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken(); // ボスのポインタ
    m_KrakenPos = pKraken->GetPos();                                    // 座標取得
    m_fDistanceToKraken = CLibrary::CalDistance(pos, m_KrakenPos);      // 距離の取得
    D3DXVECTOR3 move = CLibrary::FollowMoveXZ(pos, m_KrakenPos, SPEED); // XZの移動量
    move.y = SPEED_Y;                                                   // 高さ追加
    SetMove(move);                                                      // 移動量設定
}

//=============================================================================
// 更新処理
//=============================================================================
void CCannonBullet::Collision()
{
    CKraken* pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    D3DXVECTOR3 pos = CCannonBullet::GetPos();
    if (!pKraken)
    {
        return;
    }

    if (!m_bHit)
    {
        if (CCollision::ColOBBs(m_pCollision->GetOBB(), pKraken->GetCollosion()->GetOBB()))
        {
            pKraken->SubLife();
            m_bHit = true;
            for (int nCnt = 0; nCnt <= 20; nCnt++)
            {
                CParticleCannon::Create(pos);
            }
            Uninit();
        }
    }
}