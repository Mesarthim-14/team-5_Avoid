//=====================================================================
//
//	渦のエフェクト(小さいほう)処理[plane_vortex2.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
// Author : toshiki
//=====================================================================
#include "plane_vortex2.h"
#include "manager.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define SIZE    (D3DXVECTOR3(10500.0f, 8000.0f, 8000.0f))
#define COLOR   (D3DXCOLOR(1.0f,1.0f,1.0f,0.7f))

//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CPlaneVortex2::CPlaneVortex2()
{
    m_fRot = 0.0f;
}

//=====================================================================
// デストラクタ
// Author : toshiki
//=====================================================================
CPlaneVortex2::~CPlaneVortex2()
{
}

//=====================================================================
// 生成処理
// Author : toshiki
//=====================================================================
CPlaneVortex2 * CPlaneVortex2::Create(const D3DXVECTOR3 & pos)
{
    CPlaneVortex2 * pPlaneVortex = new CPlaneVortex2;
    if (pPlaneVortex != nullptr)
    {
        pPlaneVortex->SetSceneInfo(pos, SIZE);
        pPlaneVortex->Init();
        return pPlaneVortex;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
// Author : toshiki
//=====================================================================
HRESULT CPlaneVortex2::Init()
{
    CPlane::Init();
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_SWIRL2));
    SetColor(COLOR);
    return S_OK;
}

//=====================================================================
// 更新処理
// Author : toshiki
//=====================================================================
void CPlaneVortex2::Update()
{
    CPlane::Update();
    m_fRot += 0.01f;
    SetRot(D3DXVECTOR3(0.8f, m_fRot, 0.0f));
}

//=====================================================================
// 終了処理
// Author : toshiki
//=====================================================================
void CPlaneVortex2::Uninit()
{
    CPlane::Uninit();
}

//=====================================================================
// 描画処理
// Author : toshiki
//=====================================================================
void CPlaneVortex2::Draw()
{
    CPlane::Draw();
}