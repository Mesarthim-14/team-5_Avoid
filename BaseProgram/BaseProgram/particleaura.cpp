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

float CParticleAura::m_fSize = 0.0f;
//=====================================================================
// マクロ定義
// Author : toshiki
//=====================================================================
#define SIZE        (D3DXVECTOR3(m_fSize, m_fSize, m_fSize))
#define ANGLE        (3.0f)
#define SPEED        (10.0f)
#define RANDOM        (3.14f)
#define LIFE        (90)
#define COLOR        (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CParticleAura::CParticleAura()
{
    m_fAngle = 0.0f;
    m_nLife = 0;
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
CParticleAura * CParticleAura::Create(const D3DXVECTOR3 &pos)
{
    CParticleAura * pParticlePop = new CParticleAura;

    if (pParticlePop)
    {
        pParticlePop->SetSceneInfo(pos, SIZE);

        pParticlePop->Init();
        return pParticlePop;
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
    // 色の設定
    SetColor(COLOR);
}