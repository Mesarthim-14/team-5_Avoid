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
#include "state_player_jump.h"
#include "control_ui.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TURN_TIME       (800.0f)    // 反転までのカウント
#define SPEED           (100.0f)
#define COLLISION_SIZE  (D3DXVECTOR3(6600.0f, 700.0f, 4100.0f)) // 当たり判定モデルの大きさ
#define STOP_DISTANCE   (2000.0f)                               // 止まる距離

//=============================================================================
// コンストラクタ
//=============================================================================
CMoveScaffold::CMoveScaffold(PRIORITY Priority) : CMap(Priority)
{
    m_nTime = 0;
    m_fSpeed = SPEED;
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
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
    CMoveScaffold *pTestModel = new CMoveScaffold(PRIORITY_MAP);

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
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_PARTY_BASE);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // 当たり判定モデル(OBB)の生成
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COLLISION_SIZE.y / 2.0f), pos.z), D3DXVECTOR3(COLLISION_SIZE.x, 1.0f, COLLISION_SIZE.z), rot);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, pos.z), COLLISION_SIZE, rot);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMoveScaffold::Uninit()
{
    for (int nCount = 0; nCount < CCollisionModelOBB::SURFACE_MAX; nCount++)
    {
        // 当たり判定モデルの終了処理
        if (m_pColModelOBB[nCount])
        {
            m_pColModelOBB[nCount]->Uninit();
            m_pColModelOBB[nCount] = nullptr;
        }
    }

    CMap::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMoveScaffold::Update()
{
    // 更新処理
    CMap::Update();

    // 当たり判定モデル情報の設定
    for (int nCount = 0; nCount < CCollisionModelOBB::SURFACE_MAX; nCount++)
    {
        if (m_pColModelOBB[nCount])
        {
            m_pColModelOBB[nCount]->SetPos(m_pColModelOBB[nCount]->GetOBB().info.pos + GetMove());
        }
    }

    if (m_bMove)
    {
        // 移動処理
        Move();
    }
}

//=============================================================================
// 描画処理
//=============================================================================
void CMoveScaffold::Draw()
{
    CMap::Draw();
}

//=============================================================================
// リスポーン
//=============================================================================
void CMoveScaffold::Respawn()
{
    m_bMove = false;
    SetPos(m_StartPos);
    SetMove(ZeroVector3);

    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        pPlayer->SetBoolJump(true);
        CManager::GetInstance()->GetGame()->GetControlUi()->SwitchTexture(true);
    }

    for (int nCount = 0; nCount < CCollisionModelOBB::SURFACE_MAX; nCount++)
    {
        if (m_pColModelOBB[nCount])
        {
            m_pColModelOBB[nCount]->SetPos(D3DXVECTOR3(m_StartPos.x, m_pColModelOBB[nCount]->GetOBB().info.pos.y, m_StartPos.z));
        }
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

        CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
        if (pPlayer)
        {
            pPlayer->SetBoolJump(true);
            CManager::GetInstance()->GetGame()->GetControlUi()->SwitchTexture(true);
        }
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
        if (pPlayer->GetMove().y == 0.0f)
        {
            pPlayer->SetPos(pPlayer->GetPos() + GetMove());
        }
        else
        {
            m_bMove = false;
        }
    }
}

//=============================================================================
// 乗っているかの判定
//=============================================================================
void CMoveScaffold::OnOBBs()
{
    // プレイヤーポインタの取得
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    if (pPlayer->GetState() == CPlayer::JUMP)
    { // ジャンプ状態のとき
        CPlayerStateJump* pStateJump = (CPlayerStateJump*)pPlayer->GetCurrentState();
        if (pStateJump->GetJumpCheck())
        { // ジャンプし始めているとき
            if (pStateJump->GetJumpTimeCount() < NOT_COLLISION_TIME)
            { // 当たり判定を行わない時間より少ないとき
                return;
            }
        }
    }

    // プレイヤーの当たり判定モデルポインタの取得
    CCollisionModelOBB* pPlayerColModelOBB = pPlayer->GetColOBBPtr();

    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] && pPlayerColModelOBB)
    {
        // 上面の当たり判定ポインタの取得
        CCollisionModelOBB::OBB surfaceUpObb = m_pColModelOBB[CCollisionModelOBB::SURFACE_UP]->GetOBB();

        if (CCollision::ColOBBs(surfaceUpObb, pPlayerColModelOBB->GetOBB()))
        {
            // 着地の処理
            pPlayer->Landing(surfaceUpObb.info.pos.y + (surfaceUpObb.info.size.y / 2.0f) + (pPlayerColModelOBB->GetOBB().info.size.y / 2.0f));
            SetHitMap(true);
            m_bMove = true;
            pPlayer->SetBoolJump(false);
            CManager::GetInstance()->GetGame()->GetControlUi()->SwitchTexture(false);
        }
        else
        {
            if (!GetHitMap())
            {
                // 着地判定の設定
                pPlayer->SetLanding(false);
            }
        }
    }
}

//=============================================================================
// 当たり判定
//=============================================================================
void CMoveScaffold::Col()
{
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_UP])
    {
        OnOBBs();
    }
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        HitColOBBsPlayer(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
        HitColOBBsBossBullet(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
    }
}