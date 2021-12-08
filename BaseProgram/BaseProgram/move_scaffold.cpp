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

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS        (D3DXVECTOR3(-30637.0f, 0.0f, 8337.8f))
#define TEST_ROT        (D3DXVECTOR3(0.0f, D3DXToRadian(135.0f), 0.0f))
#define TURN_TIME       (800.0f)    // 反転までのカウント
#define SPEED           (8.0f)
#define COLLISION_SIZE  (D3DXVECTOR3(2000.0f, 100.0f, 5000.0f)) // 当たり判定モデルの大きさ

//=============================================================================
// コンストラクタ
//=============================================================================
CMoveScaffold::CMoveScaffold(PRIORITY Priority) : CModel(Priority)
{
    m_nTime = 0;
    m_fSpeed = SPEED;
    m_pColModelOBB = nullptr;
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
CMoveScaffold * CMoveScaffold::Create()
{
    // メモリ確保
    CMoveScaffold *pTestModel = new CMoveScaffold(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pTestModel)
    {
        // 初期化処理
        pTestModel->Init();

        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMoveScaffold::Init()
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MOVE_SCAFFOLD);
    GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);

    // 当たり判定モデル(OBB)の生成
    if (!m_pColModelOBB)
    {
        m_pColModelOBB = CCollisionModelOBB::Create(TEST_POS, COLLISION_SIZE, TEST_ROT);
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
    // 移動処理
    Move();

    // 更新処理
    CModel::Update();

    // OBB同士の当たり判定
    HitOBBs();

    // 当たり判定モデル情報の設定
    if (m_pColModelOBB)
    {
        m_pColModelOBB->SetInfo(GetPos(), COLLISION_SIZE, TEST_ROT);
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
        }
    }
}

//=============================================================================
// 移動処理
//=============================================================================
void CMoveScaffold::Move()
{
    m_nTime++;
    
    float fAngle = GetModelInfo()->GetRot().y;

    // 移動量設定
    D3DXVECTOR3 move = D3DXVECTOR3(
        cosf(D3DXToRadian(fAngle+45.0f))*m_fSpeed, 
        0.0f, sinf(D3DXToRadian(fAngle + 45.0f))*m_fSpeed);

    // 移動量設定
    SetMove(move);

    // 一定時間で
    if (m_nTime >= TURN_TIME)
    {
        m_nTime = 0;
        m_fSpeed *= -1;
    }
}