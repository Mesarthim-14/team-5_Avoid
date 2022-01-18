//=============================================================================
//
// 操作方法クラス [control_ui.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "control_ui.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POS     (D3DXVECTOR3(1100.0f, 650.0f, 0.0f))
#define SIZE    (D3DXVECTOR3(230.0f, 100.0f, 0.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CControlUi::CControlUi(PRIORITY Priority) : CScene2D(Priority)
{
    m_bDraw = false;
    m_bTex = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlUi::~CControlUi()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CControlUi * CControlUi::Create()
{
    // メモリ確保
    CControlUi *pPolygon = new CControlUi(PRIORITY_UI);

    // !nullcheck
    if (pPolygon)
    {
        // 初期化処理
        pPolygon->Init();
        return pPolygon;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlUi::Init()
{
    // 初期化処理
    SetSceneInfo(POS, SIZE);
    CScene2D::Init();

    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CONTROL_UI));

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlUi::Uninit()
{
    CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CControlUi::Update()
{
    CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CControlUi::Draw()
{
    if (m_bDraw)
    {
        CScene2D::Draw();
    }
}

//=============================================================================
// テクスチャの切り替え
//=============================================================================
void CControlUi::SwitchTexture(const bool& bFlag)
{
    CTexture *pTexture = GET_TEXTURE_PTR;

    if (bFlag)
    {
        BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CONTROL_UI));
        m_bTex = false;
    }
    else
    {
        BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CONTROL_UI_2));
        m_bTex = true;
    }
}
