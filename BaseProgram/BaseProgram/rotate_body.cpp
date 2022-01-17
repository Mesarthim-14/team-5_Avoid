//=============================================================================
//
// 回転本体クラス [rotate_body.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "rotate_body.h"
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
#include "collisionModel_OBB.h"
#include "state_player_knockback.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS            (D3DXVECTOR3(-34328.4f, 200.0f, -6081.8f))
#define TEST_ROT            (D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))
#define ROTATE_NUM          (D3DXToRadian(2.0f))                            // 回転の値

//=============================================================================
// コンストラクタ
//=============================================================================
CRotateBody::CRotateBody(PRIORITY Priority) : CModel(Priority)
{
    m_fRotateNum = ROTATE_NUM;
    memset(m_pColModelOBB, 0, sizeof(m_pColModelOBB));
}

//=============================================================================
// デストラクタ
//=============================================================================
CRotateBody::~CRotateBody()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CRotateBody * CRotateBody::Create(const D3DXVECTOR3 &pos)
{
    // メモリ確保
    CRotateBody *pRotatebody = new CRotateBody(PRIORITY_GIMMICK);

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
HRESULT CRotateBody::Init(const D3DXVECTOR3 &pos)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_SPINSHIP_MAST);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    D3DXVECTOR3 rot = GetRot();
    m_pColModelOBB[0] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x + 2000.0f, pos.y + 6000.0f, pos.z), D3DXVECTOR3(3200.f, 6000.0f, 1.0f), rot);
    m_pColModelOBB[1] = CCollisionModelOBB::Create(D3DXVECTOR3(pos.x - 2000.0f, pos.y + 6000.0f, pos.z), D3DXVECTOR3(3200.f, 5400.0f, 1.0f), rot);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRotateBody::Uninit()
{
    for (int nCount = 0; nCount < COL_NUM; nCount++)
    {
        // 当たり判定モデルの終了処理
        if (m_pColModelOBB[nCount])
        {
            m_pColModelOBB[nCount]->Uninit();
            m_pColModelOBB[nCount] = nullptr;
        }
    }

    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRotateBody::Update()
{
    // 更新処理
    CModel::Update();

    // 回転させる
    Rotate();

    // 当たり判定
    Col();
}

//=============================================================================
// 当たり判定
//=============================================================================
void CRotateBody::Col()
{
    // プレイヤーポインタの取得
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
        return;

    // プレイヤーの当たり判定情報の取得
    CCollisionModelOBB::OBB playerObb = pPlayer->GetColOBBPtr()->GetOBB();

    for (int nCount = 0; nCount < COL_NUM; nCount++)
    {
        if (m_pColModelOBB[nCount])
        {
            if (CCollision::ColOBBs(m_pColModelOBB[nCount]->GetOBB(), playerObb))
            {
                D3DXVECTOR3 norDirVect = ZeroVector3;
                D3DXVec3Normalize(&norDirVect, &m_pColModelOBB[nCount]->GetOBB().DirVect[CCollisionModelOBB::AXIS_Z]);

                if (nCount == 0)
                {
                    // ノックバック状態にする
                    pPlayer->ChangeState(CPlayerStateKnockback::Create(D3DXVECTOR3(-norDirVect.x * 200.0f, 50.0f, -norDirVect.z * 200.0f)));
                }
                else
                {
                    // ノックバック状態にする
                    pPlayer->ChangeState(CPlayerStateKnockback::Create(D3DXVECTOR3(norDirVect.x * 200.0f, 50.0f, norDirVect.z * 200.0f)));
                }

                // 体力を減らす
                pPlayer->SubLife(20);

                return;
            }
        }
    }
}

//=============================================================================
// 回転
//=============================================================================
void CRotateBody::Rotate()
{
    D3DXVECTOR3 rot = GetModelInfo()->GetRot();
    rot.y += m_fRotateNum;
    CLibrary::RotFix(rot.y);
    GetModelInfo()->SetRot(rot);

    if (m_pColModelOBB[0] && m_pColModelOBB[1])
    {
        m_pColModelOBB[0]->SetRot(rot);
        m_pColModelOBB[1]->SetRot(rot);

        D3DXVECTOR3 pos = GetPos();
        m_pColModelOBB[0]->SetPos(D3DXVECTOR3((2000.0f * cosf(rot.y)) + pos.x, m_pColModelOBB[0]->GetOBB().info.pos.y, (2000.0f * -sinf(rot.y)) + pos.z));
        m_pColModelOBB[1]->SetPos(D3DXVECTOR3((-2000.0f * cosf(rot.y)) + pos.x, m_pColModelOBB[0]->GetOBB().info.pos.y, (-2000.0f * -sinf(rot.y)) + pos.z));
    }
}