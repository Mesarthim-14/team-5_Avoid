//=============================================================================
//
// カジキクラス [marlin.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "marlin.h"
#include "marlin_model.h"
#include "pause.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ATTACK_INTER    (150)                                   // 攻撃間隔
#define ATTACK_STR      (20)                                    // 攻撃力
#define ATTACK_POWER    (2.0f)                                  // 吹っ飛ばし力
#define SPEED           (350.0f)                                // スピード
#define POS             (D3DXVECTOR3(-3500.0f, -200.0f, 0.0f))  // 座標
#define COLLISION_SIZE  (D3DXVECTOR3(m_fCollisionSize, m_fCollisionSize, m_fCollisionSize))

const float CMarlin::m_fCollisionSize = 500.0f;

//=============================================================================
// コンストラクタ
//=============================================================================
CMarlin::CMarlin(PRIORITY Priority) : CWimpEnemy(Priority)
{
    m_pMarlinModel = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMarlin::~CMarlin()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CMarlin * CMarlin::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    CMarlin *pMarlin = new CMarlin;
    if (pMarlin)
    {
        pMarlin->Init(pos, rot);
        return pMarlin;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMarlin::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
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
void CMarlin::Uninit()
{
    // モデル更新処理
    if (m_pMarlinModel)
    {
        m_pMarlinModel->Uninit();
    }

    CWimpEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMarlin::Update()
{
    bool bPause = CManager::GetInstance()->GetActivePause();

    if (!bPause)
    {
        // モデル更新処理
        if (m_pMarlinModel)
        {
            m_pMarlinModel->SetPos(GetPos());
            m_pMarlinModel->SetRot(GetRot());
        }
        CWimpEnemy::Update();
    }
}

//=============================================================================
// モデルの生成
//=============================================================================
void CMarlin::CreateModel()
{
    // モデル生成
    if (!m_pMarlinModel)
    {
        m_pMarlinModel = CMarlinModel::Create(GetPos());
    }
}

//=============================================================================
// 攻撃関数
//=============================================================================
void CMarlin::Attack()
{
    // 追従攻撃
    Rush();
}
