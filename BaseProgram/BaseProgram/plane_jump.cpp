//=====================================================================
//
//	ジャンプエフェクト処理[plane_jump.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
// Author : toshiki
//=====================================================================
#include "plane_jump.h"
#include "manager.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"
#include "player.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define SIZE    (D3DXVECTOR3(1000.0f, 800.0f, 800.0f))
#define COLOR   (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CPlaneJump::CPlaneJump()
{
    m_pos = ZeroVector3;
    m_move = ZeroVector3;
    m_fSize = 0.0f;
    m_fColor = 1.0f;
    m_fRot = 0.0f;
    m_nCnt = 0;
}

//=====================================================================
// デストラクタ
// Author : toshiki
//=====================================================================
CPlaneJump::~CPlaneJump()
{
}

//=====================================================================
// 生成処理
// Author : toshiki
//=====================================================================
CPlaneJump * CPlaneJump::Create(const D3DXVECTOR3 & pos)
{
    CPlaneJump * pPlaneJump = new CPlaneJump;
    if (pPlaneJump != nullptr)
    {
        pPlaneJump->SetSceneInfo(pos, SIZE);
        pPlaneJump->Init();
        return pPlaneJump;
    }

    return nullptr;
}

//=====================================================================
// 初期化処理
// Author : toshiki
//=====================================================================
HRESULT CPlaneJump::Init()
{
    CPlane::Init();
    return S_OK;
}

//=====================================================================
// 更新処理
// Author : toshiki
//=====================================================================
void CPlaneJump::Update()
{
    CPlane::Update();
    CPlayer * pPlayer = CManager::GetInstance()->GetPlayer();
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JUMP));
    m_nCnt++;
    // 表示させる角度を設定
    SetRot(D3DXVECTOR3(0.8f, m_fRot, 0.0f));

    m_fSize = 0.08f;
    ScaleUp(m_fSize);
    if (m_nCnt >= 30)
    {
        // 徐々に透明にしていく
        m_fColor -= 0.05f;
        SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColor));
        // 完全に透明になったら消す
        if (m_fColor <= 0.0f)
        {
            m_nCnt = 0;
            Uninit();
        }
    }
}

//=====================================================================
// 終了処理
// Author : toshiki
//=====================================================================
void CPlaneJump::Uninit()
{
    CPlane::Uninit();
}

//=====================================================================
// 描画処理
// Author : toshiki
//=====================================================================
void CPlaneJump::Draw()
{
    CPlane::Draw();
}