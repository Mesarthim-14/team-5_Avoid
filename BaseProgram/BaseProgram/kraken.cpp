//=============================================================================
//
// クラーケンクラス [kraken.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "kraken.h"
#include "animation_skinmesh.h"
#include "skinmesh_model.h"
#include "boss_bullet.h"
#include "collisionModel_OBB.h"
#include "state.h"
#include "state_kraken_normal.h"
#include "player.h"
#include "manager.h"
#include "library.h"
#include "kraken_tentacles.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POS                 (D3DXVECTOR3(3115.0f, 0.0f, -3267.0f))
#define SIZE                (D3DXVECTOR3(27000.0f, 60000.0f, 27000.0f))
#define BULLET_INTERVAL     (500)                                      // たま発射間隔
#define MAX_LIFE            (5)                                        // ライフ
#define MAX_TENTACLES       (8)                                        // 触手の数
#define TENTACLES_DISTANCE  (30000.0f)                                 // 触手との距離

//=============================================================================
// コンストラクタ
//=============================================================================
CKraken::CKraken(PRIORITY Priority) : CEnemy(Priority)
{
    m_pSkinmeshModel = nullptr;
    m_nBulletCount = 0;
    m_pCollision = nullptr;
    m_nLife = MAX_LIFE;
    m_bDead = false;
    m_pCurrentState = nullptr;
    m_pNextState = nullptr;
    m_apTentacles.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CKraken::~CKraken()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CKraken * CKraken::Create()
{
    CKraken *pKraken = new CKraken;
    if (pKraken)
    {
        pKraken->Init();
        return pKraken;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CKraken::Init()
{
    // モデル情報設定
    SetCharacterInfo(POS, ZeroVector3);
    SetGravityFlag(false);
    CEnemy::Init();

    // モデルの生成
    CreateModel();

    if (!m_pCollision)
    {
        // インスタンス生成
        m_pCollision = CCollisionModelOBB::Create(POS, SIZE, ZeroVector3);
    }

    if (!m_pCurrentState)
    {
        m_pCurrentState = CKrakenStateNormal::Create();
    }

    // 触手の生成
    CreateTentacles();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CKraken::Uninit()
{
    if (m_pSkinmeshModel)
    {
        m_pSkinmeshModel->Uninit();
        m_pSkinmeshModel = nullptr;
    }
    if (m_pCollision)
    {
        m_pCollision->Uninit();
        m_pCollision = nullptr;
    }
    for (auto& pTantacles : m_apTentacles)
    {
        pTantacles->Uninit();
        pTantacles = nullptr;
    }
    m_apTentacles.clear();

    CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CKraken::Update()
{
    CEnemy::Update();
    Attack();
    LookAtPlayer();

    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 rot = GetRot();
    if (m_pCollision)
    {
        m_pCollision->SetInfo(pos, m_pCollision->GetOBB().info.size, rot);
    }

    if (m_pSkinmeshModel)
    {
        m_pSkinmeshModel->SetPos(pos);
        m_pSkinmeshModel->SetRot(rot);
    }

    // 体力が無くなったら
    if (m_nLife <= 0)
    {
        m_bDead = true;
    }
}

//=============================================================================
// 状態の変更
//=============================================================================
void CKraken::ChangeState(CState* pState)
{
    if (!m_pNextState)
    {
        m_pNextState = pState;
    }
    else
    {
        delete m_pNextState;
        m_pNextState = nullptr;
        m_pNextState = pState;
    }
}

//=============================================================================
// モデルの生成
//=============================================================================
void CKraken::CreateModel()
{
    m_pSkinmeshModel = CSkinmeshModel::Create(GetPos(), GetRot(), CSkinmeshModel::MODEL_ENEMY_KRAKEN_HEAD);
    if (m_pSkinmeshModel)
    {
        CTexture* pTexture = GET_TEXTURE_PTR;
        m_pSkinmeshModel->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_KRAKEN));
        m_pSkinmeshModel->IsDraw(true);

        // モデルの情報分からない
        m_pSkinmeshModel->GetHLcontroller()->ChangeAnimation(0);
        m_pSkinmeshModel->GetHLcontroller()->SetLoopTime(0, 60);
        m_pSkinmeshModel->GetHLcontroller()->SetShiftTime(0, 60);
    }
}

//=============================================================================
// 状態の更新
//=============================================================================
void CKraken::UpdateState()
{
    if (m_pNextState)
    {
        delete m_pCurrentState;
        m_pCurrentState = nullptr;

        m_pCurrentState = m_pNextState;
        m_pNextState = nullptr;
    }

    if (m_pCurrentState)
    {
        // 更新処理
        m_pCurrentState->Update();
    }
}

//=============================================================================
// 攻撃
//=============================================================================
void CKraken::Attack()
{
    UpdateState();
}

//=============================================================================
// 触手の生成
//=============================================================================
void CKraken::CreateTentacles()
{
    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 rot = GetRot();
    float fAngle = 360.0f / MAX_TENTACLES;

    for (int nCount = 0; nCount < MAX_TENTACLES; nCount++)
    {
        m_apTentacles.push_back(CKrakenTentacles::Create(D3DXVECTOR3(
            pos.x + sinf(rot.y+D3DXToRadian(fAngle * nCount))*TENTACLES_DISTANCE,
            pos.y,
            pos.z + cosf(rot.y + D3DXToRadian(fAngle * nCount))*TENTACLES_DISTANCE),
            D3DXVECTOR3(rot.x, CLibrary::Random(180.0f), rot.z)));
    }
}
