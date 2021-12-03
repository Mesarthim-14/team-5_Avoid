//=====================================================================
//
//    パーティクル基礎処理[particle_info.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
// Author : toshiki
//=====================================================================
#include "particle_info.h"
#include "scene3D.h"

#define MOVE    (D3DXVECTOR3(0.0f,0.0f,0.0f))
//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CParticleInfo::CParticleInfo()
{
    m_move = ZeroVector3;
    m_nLife = 0;
    m_bGravitySet = false;
    m_bGravityMiniSet = false;
    m_LifeSet = true;
}

//=====================================================================
// デストラクタ
// Author : toshiki
//=====================================================================
CParticleInfo::~CParticleInfo()
{

}

//=====================================================================
// 初期化処理
// Author : toshiki
//=====================================================================
HRESULT CParticleInfo::Init()
{
    CBillboard::Init();
    return S_OK;
}

//=====================================================================
// 更新処理
// Author : toshiki
//=====================================================================
void CParticleInfo::Update()
{
    // 座標情報を取得
    D3DXVECTOR3 pos = GetPos();
    // 体力情報を取得
    m_nLife = GetLife();
    // 移動量を加算
    pos += m_move;
    // 重力をつけるかつけないかの判別
    if (m_bGravitySet)
    {
        Gravity();
    }
    else if (m_bGravityMiniSet)
    {
        Gravitymini();
    }

    if (m_LifeSet)
    {
        //    ライフが０になったら消す
        m_nLife--;
        if (m_nLife <= 0)
        {
            Erase();
        }
    }
    // 加算した情報を設定
    SetPos(pos);
}

//=====================================================================
// 終了処理
// Author : toshiki
//=====================================================================
void CParticleInfo::Uninit()
{
    CBillboard::Uninit();
}

//=====================================================================
// 描画処理
// Author : toshiki
//=====================================================================
void CParticleInfo::Draw()
{
    CBillboard::Draw();
}

//=====================================================================
// 重力
// Author : toshiki
//=====================================================================
void CParticleInfo::Gravity()
{
    // 座標情報を取得
    D3DXVECTOR3 pos = GetPos();
    m_move.y -= 2.0f;
    // 移動量を加算
    pos.y += m_move.y;
}

//=====================================================================
// 重力
// Author : toshiki
//=====================================================================
void CParticleInfo::Gravitymini()
{
    // 座標情報を取得
    D3DXVECTOR3 pos = GetPos();
    m_move.y -= 0.2f;
    // 移動量を加算
    pos.y += m_move.y;
}

//=====================================================================
// 指定消去処理
// Author : toshiki
//=====================================================================
void CParticleInfo::Erase()
{
    Uninit();
}