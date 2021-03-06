//=============================================================================
//
// サメクラス [shark.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "shark.h"
#include "shark_model.h"
#include "manager.h"
#include "pause.h"
#include "library.h"
#include "player.h"
#include "kraken.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ATTACK_INTER    (150)                                   // 攻撃間隔
#define ATTACK_STR      (20)                                    // 攻撃力
#define ATTACK_POWER    (2.0f)                                  // 吹っ飛ばし力
#define SPEED           (500.0f)                                // スピード
#define POS             (D3DXVECTOR3(-3500.0f, -200.0f, 0.0f))  // 座標
#define COLLISION_SIZE  (D3DXVECTOR3(m_fCollisionSize, m_fCollisionSize, m_fCollisionSize))

const float CShark::m_fCollisionSize = 500.0f;
constexpr float DISTANCE = -20000.0f;
constexpr float DISTANCE_Y = 4000.0f;
constexpr float PLAYER_ADD_HEIGHT = 500.0f;

//=============================================================================
// コンストラクタ
//=============================================================================
CShark::CShark(PRIORITY Priority) : CWimpEnemy(Priority)
{
    m_pSharkModel = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CShark::~CShark()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CShark * CShark::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // メモリ確保
    CShark *pShark = new CShark;
    if (pShark)
    {
        // 初期化処理
        pShark->Init(pos, rot);
        return pShark;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShark::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    float frotY = 0.0f;
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        frotY = CLibrary::LookTarget(pos, pPlayer->GetPos());
    }
    D3DXVECTOR3 Prot = D3DXVECTOR3(rot.x, frotY, rot.z);

    // 大砲の中心が違うので、座標をずらす
    D3DXVECTOR3 Ppos = D3DXVECTOR3(
        pos.x + (sinf(rot.y)*DISTANCE),
        pos.y + DISTANCE_Y,
        pos.z + (cos(rot.y)*DISTANCE));

    CWimpEnemy::Init(Ppos, COLLISION_SIZE, Prot);

    SetAttackInfo(ATTACK_INTER, ATTACK_STR, ATTACK_POWER);
    SetCharacterInfo(Ppos, Prot);
    SetSpeed(SPEED);

    // モデル生成
    CreateModel();

    // 追従攻撃
    Rush();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CShark::Uninit()
{
    // モデル更新処理
    if (m_pSharkModel)
    {
        m_pSharkModel->Uninit();
    }
    CWimpEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CShark::Update()
{
    bool bPause = CManager::GetInstance()->GetActivePause();

    if (!bPause)
    {
        // モデル更新処理
        if (m_pSharkModel)
        {
            m_pSharkModel->SetPos(GetPos());
            m_pSharkModel->SetRot(GetRot());
        }

        CWimpEnemy::Update();
    }
}

//=============================================================================
// モデルの生成
//=============================================================================
void CShark::CreateModel()
{
    // モデル生成
    if (!m_pSharkModel)
    {
        m_pSharkModel = CSharkModel::Create(GetPos());
    }
}

//=============================================================================
// 攻撃関数
//=============================================================================
void CShark::Attack()
{
    // 追従攻撃
//    Rush();
}