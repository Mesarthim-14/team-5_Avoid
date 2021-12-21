//=============================================================================
//
// クラーケン触手クラス [kraken_tentacles.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "kraken_tentacles.h"
#include "animation_skinmesh.h"
#include "skinmesh_model.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SIZE            (D3DXVECTOR3(3200.0f, 7500.0f, 3200.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CKrakenTentacles::CKrakenTentacles(PRIORITY Priority) : CScene(Priority)
{
    m_pSkinmeshModel = nullptr;
    m_pos = ZeroVector3;
    m_rot = ZeroVector3;
}

//=============================================================================
// デストラクタ
//=============================================================================
CKrakenTentacles::~CKrakenTentacles()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CKrakenTentacles * CKrakenTentacles::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // メモリ確保
    CKrakenTentacles *pTentacles = new CKrakenTentacles(PRIORITY_MODEL);
    if (pTentacles)
    {
        pTentacles->SetTentaclesInfo(pos, rot);
        pTentacles->Init();
        return pTentacles;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CKrakenTentacles::Init()
{
    // モデルの生成
    CreateModel();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CKrakenTentacles::Uninit()
{
    if (m_pSkinmeshModel)
    {
        m_pSkinmeshModel->Uninit();
        m_pSkinmeshModel = nullptr;
    }

    Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CKrakenTentacles::Update()
{
    if (m_pSkinmeshModel)
    {
        m_pSkinmeshModel->SetPos(m_pos);
        m_pSkinmeshModel->SetRot(m_rot);
    }
}


//=============================================================================
// モデルの生成
//=============================================================================
void CKrakenTentacles::CreateModel()
{
    m_pSkinmeshModel = CSkinmeshModel::Create(m_pos, m_rot, CSkinmeshModel::MODEL_ENEMY_KRAKEN_TENTACLESD);
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
// 触手の基本情報設定
//=============================================================================
void CKrakenTentacles::SetTentaclesInfo(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & rot)
{
    m_pos = pos;
    m_rot = rot;
}