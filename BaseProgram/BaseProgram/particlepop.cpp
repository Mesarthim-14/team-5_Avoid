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
#include "particlepop.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

float CParticlePop::m_fSize = 0.0f;
//=====================================================================
// マクロ定義
// Author : toshiki
//=====================================================================
#define SIZE		(D3DXVECTOR3(m_fSize, m_fSize, m_fSize))
#define ANGLE		(4.0f)
#define SPEED		(15.0f)
#define RANDOM		(3.14f)
#define LIFE		(90)
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CParticlePop::CParticlePop()
{
    m_fAngle = 0.0f;
    m_nLife = 0;
}

//=====================================================================
// デストラクタ
// Author : toshiki
//=====================================================================
CParticlePop::~CParticlePop()
{

}

//=====================================================================
// 生成処理
// Author : toshiki
//=====================================================================
CParticlePop * CParticlePop::Create(D3DXVECTOR3 pos)
{
    CParticlePop * pParticlePop = new CParticlePop;

    if (pParticlePop)
    {
        m_fSize = CLibrary::Random(100.0f, 150.0f);
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
HRESULT CParticlePop::Init()
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// 更新処理
// Author : toshiki
//=====================================================================
void CParticlePop::Update()
{
    CParticleInfo::Update();
}

//=====================================================================
// 終了処理
// Author : toshiki
//=====================================================================
void CParticlePop::Uninit()
{
    CParticleInfo::Uninit();
}

//=====================================================================
// 描画処理
// Author : toshiki
//=====================================================================
void CParticlePop::Draw()
{
    CParticleInfo::Draw();
}

//=====================================================================
// パーティクルの設定
// Author : toshiki
//=====================================================================
void CParticlePop::SetParticle()
{
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
    // スピードの値を設定
    m_fSpeed = SPEED;
    // パーティクルの出る角度の設定
    m_fAngle = CLibrary::Random(RANDOM);
    // 重力をつける
    CParticleInfo::SetGravity(true);
    // 移動させるための処理
    D3DXVECTOR3 move = D3DXVECTOR3(sinf(m_fAngle) * m_fSpeed, ANGLE, cosf(m_fAngle) * m_fSpeed);
    // 移動情報を設定
    SetMove(move);
    // 色の設定
    SetColor(COLOR);
    // パーティクルが消える時間の設定
    SetLife(LIFE);
}