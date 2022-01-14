//=====================================================================
//
//    パーティクル処理[particlepop.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
// Author : toshiki
//=====================================================================
#include "particleaura.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"
#include "ghost.h"
#include "player.h"

//=====================================================================
// マクロ定義
// Author : toshiki
//=====================================================================
#define SIZE         (D3DXVECTOR3(1500.0f, 1500.0f, 1500.0f))
#define ANGLE        (3.0f)
#define SPEED        (5.0f)
#define RANDOM       (3.14f)
#define LIFE         (90)
#define COLOR        (D3DXCOLOR(1.0f,1.0f,1.0f,0.4f))

#define FOLLOW_END_DISTANCE (800.0f)                                // 追従を切る
#define RISE_SPEED          (30.0f)                                 // 上昇速度
#define RISE_TIME           (120)                                   // 終了までの時間
#define END_TIME            (250)                                   // 終了までの時間
#define PLAYER_ADD_HEIGHT   (500.0f)                                // プレイヤーを適当に量増し

//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CParticleAura::CParticleAura()
{
    m_fAngle = 0.0f;
    m_nLife = 0;
    m_bFollow = false;
    m_bEnd = false;
    m_bCaution = false;
    m_nEndCount = 0;
}

//=====================================================================
// デストラクタ
// Author : toshiki
//=====================================================================
CParticleAura::~CParticleAura()
{

}

//=====================================================================
// 生成処理
// Author : toshiki
//=====================================================================
CParticleAura * CParticleAura::Create()
{
    CParticleAura * pParticle = new CParticleAura;

    if (pParticle)
    {
        pParticle->SetSceneInfo(D3DXVECTOR3(0.0f, 5000.0f, 0.0f), SIZE);
        pParticle->Init();
        return pParticle;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
// Author : toshiki
//=====================================================================
HRESULT CParticleAura::Init()
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// 更新処理
// Author : toshiki
//=====================================================================
void CParticleAura::Update()
{
    CParticleInfo::Update();
    //// プレイヤーを探す処理
    //Tracking();
    //// 移動処理
    //Move();
}

//=====================================================================
// 終了処理
// Author : toshiki
//=====================================================================
void CParticleAura::Uninit()
{
    CParticleInfo::Uninit();
}

//=====================================================================
// 描画処理
// Author : toshiki
//=====================================================================
void CParticleAura::Draw()
{
    CParticleInfo::Draw();
}

//=====================================================================
// パーティクルの設定
// Author : toshiki
//=====================================================================
void CParticleAura::SetParticle()
{
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
    SetLife(false);
    // 色の設定
    SetColor(COLOR);
}

//=====================================================================
// パーティクルの移動
// Author : toshiki
//=====================================================================
void CParticleAura::Move()
{
    // 追従フラグ
    if (m_bFollow)
    {
        // 追従
        if (Follow())
        {
            // 一定の距離に近づいたら
            if (CLibrary::CalDistance(
                CManager::GetInstance()->GetPlayer()->GetPos(), GetPos()) <= FOLLOW_END_DISTANCE)
            {
                m_bFollow = false;
                m_bEnd = true;
            }
        }
    }

    if (m_bEnd)
    {
        m_nEndCount++;
        if (m_nEndCount >= RISE_TIME)
        {
            // 上昇
            Rise();
            if (m_nEndCount >= END_TIME)
            {
                // 消える
                Uninit();
                return;
            }
        }
    }

}

//=====================================================================
// パーティクルの上昇
// Author : toshiki
//=====================================================================
void CParticleAura::Rise()
{
    D3DXVECTOR3 move = ZeroVector3;
    move.y = RISE_SPEED;
    SetMove(move);
}

//=====================================================================
// パーティクルの追従設定
// Author : toshiki
//=====================================================================
void CParticleAura::Attack()
{
    if (!m_bFollow && !m_bEnd)
    {
        m_bFollow = true;
    }
}

//=====================================================================
// パーティクルの追従設定
// Author : toshiki
//=====================================================================
void CParticleAura::Tracking()
{
    if (Search())
    {
        if (!m_bCaution)
        {
            m_bCaution = true;
            m_nCautionCounter = 0;
        }
    }
    // 警告が出てるとき
    if (m_bCaution)
    {
        m_nCautionCounter++;
        if (m_nCautionCounter == 60)
        {
            m_bCaution = false;
            Attack();
        }
    }
}