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
#include "plane_jumpreservoir.h"
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
CPlaneJumpReservoir::CPlaneJumpReservoir()
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
CPlaneJumpReservoir::~CPlaneJumpReservoir()
{
}

//=====================================================================
// 生成処理
// Author : toshiki
//=====================================================================
CPlaneJumpReservoir * CPlaneJumpReservoir::Create(const D3DXVECTOR3 & pos)
{
    CPlaneJumpReservoir * pPlaneJump = new CPlaneJumpReservoir;
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
HRESULT CPlaneJumpReservoir::Init()
{
    CPlane::Init();
    SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
    return S_OK;
}

//=====================================================================
// 更新処理
// Author : toshiki
//=====================================================================
void CPlaneJumpReservoir::Update()
{
    CPlane::Update();
    CPlayer * pPlayer = CManager::GetInstance()->GetPlayer();
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JUMP));
    // 表示させる角度を設定
    SetRot(D3DXVECTOR3(0.8f, m_fRot, 0.0f));

    // プレイヤーの位置情報を持ってくる
    m_pos = pPlayer->GetPos();
    // プレイヤーの位置に追従
    m_pos += m_move;
    m_nCnt++;
    m_fSize = 0.07f;
    ScaleDown(m_fSize);
    if (m_nCnt >= 10)
    {
        // 徐々に透明にしていく
        m_fColor -= 0.1f;
        SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColor));
        // 完全に透明になったら消す
        if (m_fColor <= 0.0f)
        {
            m_nCnt = 0;
            Uninit();
        }
    }
    // 位置情報を設定
    SetPos(D3DXVECTOR3(m_pos.x, m_pos.y - 200.0f, m_pos.z));
}

//=====================================================================
// 終了処理
// Author : toshiki
//=====================================================================
void CPlaneJumpReservoir::Uninit()
{
    CPlane::Uninit();
}

//=====================================================================
// 描画処理
// Author : toshiki
//=====================================================================
void CPlaneJumpReservoir::Draw()
{
    CPlane::Draw();
}
