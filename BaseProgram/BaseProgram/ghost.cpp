//=============================================================================
//
// 幽霊クラス [ghost.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "ghost.h"
#include "ghost_model.h"
#include "library.h"
#include "manager.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ATTACK_INTER        (150)                                   // 攻撃間隔
#define ATTACK_STR          (20)                                    // 攻撃力
#define ATTACK_POWER        (2.0f)                                  // 吹っ飛ばし力
#define SPEED               (30.0f)                                 // スピード
#define RISE_SPEED          (15.0f)                                 // 上昇速度
#define POS                 (D3DXVECTOR3(-3500.0f, -200.0f, 0.0f))  // 座標
#define FOLLOW_END_DISTANCE (800.0f)                                // 追従を切る
#define RISE_TIME           (120)                                   // 終了までの時間
#define END_TIME            (250)                                   // 終了までの時間
#define COLLISION_SIZE  (D3DXVECTOR3(m_fCollisionSize, m_fCollisionSize, m_fCollisionSize))

const float CGhost::m_fCollisionSize = 500.0f;

//=============================================================================
// コンストラクタ
//=============================================================================
CGhost::CGhost(PRIORITY Priority) : CWimpEnemy(Priority)
{
    m_pGhostModel = nullptr;
    m_bFollow = false;
    m_bEnd = false;
    m_nEndCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGhost::~CGhost()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CGhost * CGhost::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // メモリ確保
    CGhost *pGhost = new CGhost;
    if (pGhost)
    {
        pGhost->Init(pos, rot);
        return pGhost;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGhost::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    CWimpEnemy::Init(pos, COLLISION_SIZE, rot);
    SetAttackInfo(ATTACK_INTER, ATTACK_STR, ATTACK_POWER);
    SetCharacterInfo(pos, rot);
    SetSpeed(SPEED);

    CreateModel();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGhost::Uninit()
{
    // モデル更新処理
    if (m_pGhostModel)
    {
        m_pGhostModel->Uninit();
    }
    CWimpEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGhost::Update()
{
    CWimpEnemy::Update();

    // モデル更新処理
    if (m_pGhostModel)
    {
        m_pGhostModel->SetPos(GetPos());
    }

    // 移動処理
    Move();

    // 当たり判定
    Collision();

}

//=============================================================================
// モデルの生成
//=============================================================================
void CGhost::CreateModel()
{
    // モデル生成
    if (!m_pGhostModel)
    {
        m_pGhostModel = CGhostModel::Create(GetPos());
    }
}

//=============================================================================
// 攻撃
//=============================================================================
void CGhost::Attack()
{
    if (!m_bFollow && !m_bEnd)
    {
        m_bFollow = true;
    }
}

//=============================================================================
// 移動
//=============================================================================
void CGhost::Move()
{
    // 追従フラグ
    if (m_bFollow)
    {
        // 追従
        if (Follow())
        {

            // 一定の距離に近づいたら
            if (CLibrary::CalDistance(
                CManager::GetInstance()->GetPlayer()->GetPos(), GetPos()) <= FOLLOW_END_DISTANCE)
            {
                m_bFollow = false;
                m_bEnd = true;
            }
        }
    }

    if (m_bEnd)
    {
        m_nEndCount++;
        if (m_nEndCount >= RISE_TIME)
        {
            // 上昇
            Rise();
            if (m_nEndCount >= END_TIME)
            {
                // 消える
                Uninit();
                return;
            }
        }
    }
}

//=============================================================================
// 上昇
//=============================================================================
void CGhost::Rise()
{
    D3DXVECTOR3 move = ZeroVector3;
    move.y = RISE_SPEED;
    SetMove(move);
}