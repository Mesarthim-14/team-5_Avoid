//=============================================================================
//
// 渦ギミックの床クラス [swirl_scaffold.object.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "swirl_scaffold_object.h"
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
#include "state_player_jump.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_ROT    (D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f))   // 角度
#define COL_SIZE    (D3DXVECTOR3(3850.0f, 500.0f, 2050.0f))   // 当たり判定サイズ

//=============================================================================
// コンストラクタ
//=============================================================================
CSwirlScaffoldObject::CSwirlScaffoldObject(PRIORITY Priority) : CMap(Priority)
{
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
    m_bMove = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSwirlScaffoldObject::~CSwirlScaffoldObject()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CSwirlScaffoldObject * CSwirlScaffoldObject::Create(const D3DXVECTOR3 &pos)
{
    // メモリ確保
    CSwirlScaffoldObject *pRotatebody = new CSwirlScaffoldObject(PRIORITY_MAP);

    // !nullcheck
    if (pRotatebody)
    {
        // 初期化処理
        pRotatebody->Init(pos);
        return pRotatebody;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSwirlScaffoldObject::Init(const D3DXVECTOR3 &pos)
{
    // 初期化処理
    CMap::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_SPINFLOOR);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    // 当たり判定モデルの生成(OBB)
    m_pColModelOBB[CCollisionModelOBB::SURFACE_UP] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x, pos.y + (COL_SIZE.y / 2) + 50.0f, pos.z), D3DXVECTOR3(COL_SIZE.x, 1.0f, COL_SIZE.z), TEST_ROT);
    m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE] = CCollisionModelOBB::Create(pos, COL_SIZE, TEST_ROT);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSwirlScaffoldObject::Uninit()
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
void CSwirlScaffoldObject::Update()
{
    CMap::Update();

    // 当たり判定モデルの更新
    for (int nCount = 0; nCount < CCollisionModelOBB::SURFACE_MAX; nCount++)
    {
        if (m_pColModelOBB[nCount])
        {
            m_pColModelOBB[nCount]->SetPos(D3DXVECTOR3(GetPos().x, m_pColModelOBB[nCount]->GetOBB().info.pos.y, GetPos().z));
        }
    }

    // プレイヤーを運ぶ処理
    CarryPlayer();
}

//=============================================================================
// 当たり判定
//=============================================================================
void CSwirlScaffoldObject::Col()
{
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_UP])
    {
        // 乗っているかの判定
        OnOBBs();
    }
    if (m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE])
    {
        HitColOBBsPlayer(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
        HitColOBBsBossBullet(m_pColModelOBB[CCollisionModelOBB::SURFACE_SIDE]);
    }
}

//=============================================================================
// 乗っているかの判定
//=============================================================================
void CSwirlScaffoldObject::OnOBBs()
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

            if (!m_bMove)
            {
                m_bMove = true;
            }
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
// プレイヤーを運ぶ
//=============================================================================
void CSwirlScaffoldObject::CarryPlayer()
{
    if (m_bMove)
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
}