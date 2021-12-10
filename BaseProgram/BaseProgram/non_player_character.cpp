//=============================================================================
//
// NPCクラス [non_player_character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "non_player_character.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "player.h"
#include "key_e.h"
#include "npc_text_enemy.h"
#include "production_npc_talk.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DISTANCE    (800.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CNonPlayerCharacter::CNonPlayerCharacter(PRIORITY Priority) : CScene(Priority)
{
    m_pos = ZeroVector3;
    m_rot = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);
    m_pSkinmeshModel = nullptr;
    m_pKeyE = nullptr;
    m_pText = nullptr;
    m_bDead = false;
    m_pProduction = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CNonPlayerCharacter::~CNonPlayerCharacter()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNonPlayerCharacter::Init()
{
    // モデル生成
    CreateModel();

    if (!m_pKeyE)
    {
        m_pKeyE = CKeyE::Create();
    }
    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNonPlayerCharacter::Uninit()
{
    //オブジェクトの破棄
    Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CNonPlayerCharacter::Update()
{
    //モデル位置向き反映(いずれcharacterに移動させたい）
    m_pSkinmeshModel->SetPos(m_pos);
    m_pSkinmeshModel->SetRot(m_rot);

    if (m_bDead)
    {
        return;
    }

    if (m_pText)
    {
        // テキストの終了なら
        if (m_pText->GetEnd())
        {
            EndProduction();
            m_pText->Uninit();
            m_pText = nullptr;
            m_bDead = true;
            m_pKeyE->SetDrawFlag(false);
            return;
        }
    }
    Collision();
}

//=============================================================================
// 描画処理
//=============================================================================
void CNonPlayerCharacter::Draw()
{
    //デバイス情報の取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // マトリクスの設定
    CLibrary::ConfigMatrix(&m_mtxWorld, m_pos, m_rot);

    //ワールドマトリックスの設定
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

}

//=============================================================================
// モデル生成
//=============================================================================
void CNonPlayerCharacter::CreateModel()
{
    m_pSkinmeshModel = CSkinmeshModel::Create(m_pos, m_rot, CSkinmeshModel::MODEL_PLAYER_50);
    
    m_pSkinmeshModel->GetHLcontroller()->ChangeAnimation(0);
    m_pSkinmeshModel->GetHLcontroller()->SetLoopTime(0, 60);
    m_pSkinmeshModel->GetHLcontroller()->SetShiftTime(0, 60);
}

//=============================================================================
// 当たり判定
//=============================================================================
void CNonPlayerCharacter::Collision()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    float fAngle = CLibrary::CalAngleXZ(m_pos, pPlayer->GetPos());
    // 近づいたらEボタンを出す
    if (CLibrary::CalDistance(m_pos, pPlayer->GetPos()) <= DISTANCE
        && fAngle <= m_rot.y + D3DXToRadian(-60.0f) && fAngle >= m_rot.y + D3DXToRadian(-135.0f))
    {
        m_pKeyE->SetDrawFlag(true);

        // 入力されたら
        if (CLibrary::KeyboardTrigger(DIK_E))
        {
            // 話す
            Talk();

            // 演出スタート
            BebinProduction(m_pos, m_rot);
        }
    }
    else
    {
        m_pKeyE->SetDrawFlag(false);
    }
}

//=============================================================================
// 状態の開始
//=============================================================================
void CNonPlayerCharacter::BebinProduction(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    if (!m_pProduction)
    {
        m_pProduction = CProductionNpcTalk::Create(pos, rot);
    }
}

//=============================================================================
// 状態の終了
//=============================================================================
void CNonPlayerCharacter::EndProduction()
{
    if (m_pProduction)
    {
        // 終了処理
        m_pProduction->Uninit();
        m_pProduction = nullptr;
    }
}
