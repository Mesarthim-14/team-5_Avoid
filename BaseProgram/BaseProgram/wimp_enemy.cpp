//=============================================================================
//
// サメクラス [wimp_enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "wimp_enemy.h"
#include "manager.h"
#include "player.h"
#include "library.h"
#include "collisionModel_OBB.h"
#include "collision.h"
#include "state_player_knockback.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PERCEPTION_DISTANCE (6000.0f)   // 感知できる距離
#define FOLLOW_TIME         (50)        // 重力がかからない時間
#define PLAYER_ADD_HEIGHT   (500.0f)    // プレイヤーを適当に量増し
#define HIT_TIME_INTER      (300)       // 当たった後の間隔

//=============================================================================
// コンストラクタ
//=============================================================================
CWimpEnemy::CWimpEnemy(PRIORITY Priority) : CEnemy(Priority)
{
    isRush = false;
    m_nRushCount = 0;
    m_pCollision = nullptr;
    m_nHitInter = 0;
    m_bHit = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CWimpEnemy::~CWimpEnemy()
{
    if (m_pCollision)
    {
        m_pCollision->Uninit();
        m_pCollision = nullptr;
    }
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWimpEnemy::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot)
{
    CEnemy::Init();
    SetGravityFlag(false);

    if (!m_pCollision)
    {
        m_pCollision = CCollisionModelOBB::Create(pos, size, rot);
    }

    return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CWimpEnemy::Update()
{
    CEnemy::Update();
    if (isRush)
    {
        // 当たり判定
        Collision();

        // 重力の切り替え
        GravitySwitch();
    }
}

//=============================================================================
// 突進
//=============================================================================
void CWimpEnemy::Rush()
{
    // 突進
    if (Follow())
    {
        isRush = true;
    }
}

//=============================================================================
// 重力をかける
//=============================================================================
void CWimpEnemy::GravitySwitch()
{
    m_nRushCount++;
    if (m_nRushCount >= FOLLOW_TIME)
    {
        m_nRushCount = 0;
        SetGravityFlag(true);
    }
}

//=============================================================================
// 追従
//=============================================================================
bool CWimpEnemy::Follow()
{
    // メモリ取得
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        D3DXVECTOR3 Ppos = pPlayer->GetPos();
        Ppos.y += PLAYER_ADD_HEIGHT;
        D3DXVECTOR3 Epos = GetPos();
        float fSpeed = GetSpeed();

        // 2点間のベクトルを求める（終点[目標地点] - 始点[自身の位置]）
        D3DXVECTOR3 Vector = Ppos - Epos;
        Vector = *D3DXVec3Normalize(&Vector, &Vector);
        Vector *= fSpeed;

        //自機を取得する
        float fAngle = atan2f((Epos.x - Ppos.x), (Epos.z - Ppos.z));    // 角度
        float fDistance = CLibrary::CalDistance(Ppos, Epos);
        if (fDistance <= PERCEPTION_DISTANCE)
        {
            // 透明な敵の移動
            D3DXVECTOR3 FollowMove = D3DXVECTOR3(
                (sinf(fAngle)*-fSpeed),
                0.0f, cosf(fAngle)*-fSpeed);

            // 移動量の設定
            SetMove(Vector);
            return true;
        }
    }

    return false;
}

//=============================================================================
// 当たり判定
//=============================================================================
void CWimpEnemy::Collision()
{
    // 情報の更新
    if (m_pCollision)
    {
        m_pCollision->SetInfo(GetPos(), m_pCollision->GetInfo().size, GetRot());
    }

    if (m_bHit)
    {
        m_nHitInter++;

        // 当たった状態を戻す
        if (m_nHitInter >= HIT_TIME_INTER)
        {
            m_bHit = false;
            m_nHitInter = 0;
        }
    }
    else
    {
        // プレイヤーとの当たり判定
        CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
        if (pPlayer)
        {
            if (m_pCollision && pPlayer->GetCollisionPtr())
            {
                if (CCollision::ColOBBs(m_pCollision->GetOBB(), pPlayer->GetCollisionPtr()->GetOBB()))
                {
                    // プレイヤーへの影響
                    AffectPlayer(pPlayer);
                    m_bHit = true;
                }
            }
        }
    }
}

//=============================================================================
// プレイヤーに影響を与える
//=============================================================================
void CWimpEnemy::AffectPlayer(CPlayer* &pPlayer)
{
    // プレイヤーにダメージ
    pPlayer->SubLife(20);

    D3DXVECTOR3 move = GetMove();
    move.x *= 0.8f;
    move.x *= 1.5f;
    move.z *= 0.8f;
    pPlayer->ChangeState(CPlayerStateKnockback::Create(move));
}