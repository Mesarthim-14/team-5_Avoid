//=====================================================================
//
//	パーティクル処理[particle.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
// Author : toshiki
//=====================================================================
#include "particle_explosion.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"
#include "texture_animation.h"

D3DXVECTOR3 CParticleExplosion::m_Rot = ZeroVector3;
//=====================================================================
// マクロ定義
// Author : toshiki
//=====================================================================
#define POS         (ZeroVector3)
#define SIZE        (D3DXVECTOR3(1600.0f, 1600.0f, 0.0f))
#define SPEED       (7.0f)
#define RANDOM      (3.14f)
#define LIFE        (200)
#define COLOR       (D3DXCOLOR(1.0f,1.0f,1.0f,m_fColor))

//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CParticleExplosion::CParticleExplosion()
{
    m_fAngle = 0.0f;
    m_fSpeed = 0.0f;
    m_fColor = 1.0f;
    m_nCnt = 0;
}

//=====================================================================
// デストラクタ
// Author : toshiki
//=====================================================================
CParticleExplosion::~CParticleExplosion()
{

}

//=====================================================================
// 生成処理
// Author : toshiki
//=====================================================================
CParticleExplosion * CParticleExplosion::Create(const D3DXVECTOR3 &pos)
{
    CParticleExplosion * pParticle = new CParticleExplosion;

    if (pParticle != nullptr)
    {
        pParticle->SetSceneInfo(pos, SIZE);
        pParticle->Init();
        return pParticle;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
// Author : toshiki
//=====================================================================
HRESULT CParticleExplosion::Init(void)
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// 更新処理
// Author : toshiki
//=====================================================================
void CParticleExplosion::Update(void)
{
    CParticleInfo::Update();
    SetParticleColor();
    SetEffect();
}

//=====================================================================
// 終了処理
// Author : toshiki
//=====================================================================
void CParticleExplosion::Uninit(void)
{
    CParticleInfo::Uninit();
}

//=====================================================================
// 描画処理
// Author : toshiki
//=====================================================================
void CParticleExplosion::Draw(void)
{
    CParticleInfo::Draw();
}

//=====================================================================
// パーティクルを出す処理
// Author : toshiki
//=====================================================================
void CParticleExplosion::SetParticle(void)
{
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_SMOKE));
    CScene3D::InitAnimation(8, 10, 0);
    // パーティクルが消える時間の設定
    SetLife(LIFE);
}

//=====================================================================
// パーティクルを徐々に消す処理
// Author : toshiki
//=====================================================================
void CParticleExplosion::SetParticleColor(void)
{
    m_nCnt++;
    // 徐々に消えていく処理
    if (m_nCnt >= 10)
    {
        m_fColor -= 0.1f;
        m_nCnt = 0;
    }
    SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColor));
}

//=====================================================================
// エフェクト更新
// Author : toshiki
//=====================================================================
void CParticleExplosion::SetEffect(void)
{
    CTextureAnimation *pAnimation = GetTextureAnimationPtr();
    pAnimation->Update();
}