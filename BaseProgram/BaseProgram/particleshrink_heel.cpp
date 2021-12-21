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
#include "particleshrink_heel.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

float CParticleHeel::m_fAngleX = 0.0f;
float CParticleHeel::m_fAngleZ = 0.0f;
float CParticleHeel::m_fSize = 0.0f;
//=====================================================================
// マクロ定義
// Author : toshiki
//=====================================================================
#define PARTICLE_POS    ((D3DXVECTOR3(m_fAngleX, 5.0f, m_fAngleZ)))
#define SIZE            (D3DXVECTOR3(m_fSize, m_fSize, m_fSize))
#define SPEED           (5.0f)
#define RANDOM          (3.14f)
#define LIFE            (40)
#define COLOR           (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define TANGENT         (7.0f)

//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CParticleHeel::CParticleHeel()
{
    m_fSpeed = 0.0f;
    ShrinkPos = ZeroVector3;
}

//=====================================================================
// デストラクタ
// Author : toshiki
//=====================================================================
CParticleHeel::~CParticleHeel()
{

}

//=====================================================================
// 生成処理
// Author : toshiki
//=====================================================================
CParticleHeel * CParticleHeel::Create(const D3DXVECTOR3 &pos)
{
    CParticleHeel * pParticle = new CParticleHeel;

    if (pParticle != nullptr)
    {
        m_fAngleX = CLibrary::Random(600.0f);
        m_fAngleZ = CLibrary::Random(600.0f);
        m_fSize = CLibrary::Random(30.0f, 100.0f);
        pParticle->SetSceneInfo(D3DXVECTOR3(pos.x + m_fAngleX, pos.y, pos.z + m_fAngleZ), SIZE);

        pParticle->Init();
        return pParticle;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
// Author : toshiki
//=====================================================================
HRESULT CParticleHeel::Init(void)
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// 更新処理
// Author : toshiki
//=====================================================================
void CParticleHeel::Update(void)
{
    CParticleInfo::Update();
}

//=====================================================================
// 終了処理
// Author : toshiki
//=====================================================================
void CParticleHeel::Uninit(void)
{
    CParticleInfo::Uninit();
}

//=====================================================================
// 描画処理
// Author : toshiki
//=====================================================================
void CParticleHeel::Draw(void)
{
    CParticleInfo::Draw();
}

//=====================================================================
// パーティクルを出す処理
// Author : toshiki
//=====================================================================
void CParticleHeel::SetParticle(void)
{
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_HEEL));
    // スピードの値を設定
    m_fSpeed = SPEED;
    // 移動させるための処理
    D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 8.0f, 0.0f);
    // 移動情報を設定
    SetMove(move);
    // 色の設定
    SetColor(COLOR);
    // パーティクルが消える時間の設定
    SetLife(LIFE);
}