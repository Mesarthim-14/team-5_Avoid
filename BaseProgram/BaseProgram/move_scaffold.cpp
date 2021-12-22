//=============================================================================
//
// 動く足場クラス [move_scaffold.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "move_scaffold.h"
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
#include "library.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TURN_TIME       (800.0f)    // 反転までのカウント
#define SPEED           (20.0f)
#define COLLISION_SIZE  (D3DXVECTOR3(2000.0f, 100.0f, 5000.0f)) // 当たり判定モデルの大きさ
#define STOP_DISTANCE   (2000.0f)                               // 止まる距離

//=============================================================================
// コンストラクタ
//=============================================================================
CMoveScaffold::CMoveScaffold(PRIORITY Priority) : CModel(Priority)
{
    m_nTime = 0;
    m_fSpeed = SPEED;
    m_pColModelOBB = nullptr;
    m_StartPos = D3DXVECTOR3(-53522.5f, 0.0f, -12396.5f);
    m_GoalPos = D3DXVECTOR3(-2309.0f, 0.0f, 60403.7f);
    m_bMove = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMoveScaffold::~CMoveScaffold()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CMoveScaffold * CMoveScaffold::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // メモリ確保
    CMoveScaffold *pTestModel = new CMoveScaffold(PRIORITY_TEST_MODEL);

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
HRESULT CMoveScaffold::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_PARTY_BASE);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // 当たり判定モデル(OBB)の生成
    if (!m_pColModelOBB)
    {
        m_pColModelOBB = CCollisionModelOBB::Create(pos, COLLISION_SIZE, rot);
    }

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMoveScaffold::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMoveScaffold::Update()
{
    if (m_bMove)
    {
        // 移動処理
        Move();
    }

    // 更新処理
    CModel::Update();

    // OBB同士の当たり判定
    HitOBBs();

    // 当たり判定モデル情報の設定
    if (m_pColModelOBB)
    {
        m_pColModelOBB->SetInfo(GetPos(), COLLISION_SIZE, GetRot());
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CMoveScaffold::Draw()
{
    CModel::Draw();
}

//=============================================================================
// OBB同士の当たり判定
//=============================================================================
void CMoveScaffold::HitOBBs()
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
            pPlayer->Landing(m_pColModelOBB->GetOBB().info.pos.y + (m_pColModelOBB->GetOBB().info.size.y / 2) + (pPlayerColModelOBB->GetOBB().info.size.y / 2));
            if (!m_bMove)
            {
                m_bMove = true;
            }
        }
    }
}

//=============================================================================
// リスポーン
//=============================================================================
void CMoveScaffold::Respawn()
{
    if (m_bMove)
    {
        m_bMove = false;
        SetPos(m_StartPos);
        SetMove(ZeroVector3);
    }
}

//=============================================================================
// 移動処理
//=============================================================================
void CMoveScaffold::Move()
{
    D3DXVECTOR3 pos = GetPos();
    SetMove(CLibrary::FollowMoveXZ(pos, m_GoalPos, SPEED));

    if (CLibrary::CalDistance(m_GoalPos, pos) <= STOP_DISTANCE)
    {
        m_bMove = false;
        SetMove(ZeroVector3);
    }

    // プレイヤーを運ぶ処理
    CarryPlayer();
}

//=============================================================================
// プレイヤーを運ぶ
//=============================================================================
void CMoveScaffold::CarryPlayer()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        D3DXVECTOR3 move = pPlayer->GetPos() + GetMove();
        pPlayer->SetPos(move);
    }
}
