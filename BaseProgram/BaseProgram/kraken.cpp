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

#define POS             (D3DXVECTOR3(-16686.5f, 0.0f, -2596.4f))
#define BULLET_INTERVAL (120)                                    // たま発射間隔

//=============================================================================
// コンストラクタ
//=============================================================================
CKraken::CKraken(PRIORITY Priority) : CEnemy(Priority)
{
    m_pSkinmeshModel = nullptr;
    m_nBulletCount = 0;
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

    CEnemy::Init();

    // モデルの生成
    CreateModel();

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

    CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CKraken::Update()
{
    CEnemy::Update();
    Attack();
}

//=============================================================================
// 攻撃処理
//=============================================================================
void CKraken::Attack()
{
    ShotBullet();
}

//=============================================================================
// 弾発射
// Author : hayashikawa sarina
//=============================================================================
void CKraken::ShotBullet()
{
    m_nBulletCount++;
    if (m_nBulletCount == BULLET_INTERVAL)
    {
        CBossBullet::Create(POS, ZeroVector3, D3DXVECTOR3(50.0f, 0.0f, 0.0f));
        m_nBulletCount = 0;
    }
}

//=============================================================================
// モデルの生成
//=============================================================================
void CKraken::CreateModel()
{
    m_pSkinmeshModel = CSkinmeshModel::Create(GetPos(), GetRot(), CSkinmeshModel::MODEL_ENEMY_KRAKEN_HEAD);

    m_pSkinmeshModel->IsDraw(true);
    //SetAction(m_pSkinmeshModel->MaxAction());

    // モデルの情報…分からない
    m_pSkinmeshModel->GetHLcontroller()->ChangeAnimation(0);
    m_pSkinmeshModel->GetHLcontroller()->SetLoopTime(0, 60);
    m_pSkinmeshModel->GetHLcontroller()->SetShiftTime(0, 60);

}