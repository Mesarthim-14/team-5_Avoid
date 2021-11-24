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
#include "particlenormal.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

//=====================================================================
// マクロ定義
// Author : toshiki
//=====================================================================
#define POS         (ZeroVector3)
#define SIZE        (D3DXVECTOR3(50.0f, 50.0f, 50.0f))
#define SPEED       (5.0f)
#define RANDOM      (3.14f)
#define LIFE        (60)
#define COLOR       (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CParticleNormal::CParticleNormal()
{
    m_fAngle = 0.0f;
    m_fSpeed = 0.0f;
}

//=====================================================================
// デストラクタ
// Author : toshiki
//=====================================================================
CParticleNormal::~CParticleNormal()
{

}

//=====================================================================
// 生成処理
// Author : toshiki
//=====================================================================
CParticleNormal * CParticleNormal::Create(const D3DXVECTOR3 &pos)
{
    CParticleNormal * pParticle = new CParticleNormal;

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
HRESULT CParticleNormal::Init(void)
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// 更新処理
// Author : toshiki
//=====================================================================
void CParticleNormal::Update(void)
{
    CParticleInfo::Update();
}

//=====================================================================
// 終了処理
// Author : toshiki
//=====================================================================
void CParticleNormal::Uninit(void)
{
    CParticleInfo::Uninit();
}

//=====================================================================
// 描画処理
// Author : toshiki
//=====================================================================
void CParticleNormal::Draw(void)
{
    CParticleInfo::Draw();
}

//=====================================================================
// パーティクルを出す処理
// Author : toshiki
//=====================================================================
void CParticleNormal::SetParticle(void)
{
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
    // スピードの値を設定
    m_fSpeed = SPEED;
    // パーティクルの出る角度の設定
    m_fAngle = CLibrary::Random(RANDOM);
    // 移動させるための処理
    D3DXVECTOR3 move = D3DXVECTOR3(sinf(m_fAngle)*m_fSpeed, CLibrary::Random(4.0f, m_fSpeed), cosf(m_fAngle)*m_fSpeed);
    // 移動情報を設定
    SetMove(move);
    // 色の設定
    SetColor(COLOR);
    // パーティクルが消える時間の設定
    SetLife(LIFE);
}
