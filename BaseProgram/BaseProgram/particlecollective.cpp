//=====================================================================
//
//	パーティクル処理[particlecollective.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "particlecollective.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define POS			(ZeroVector3)
#define SIZE		(D3DXVECTOR3(50.0f, 50.0f, 50.0f))
#define SPEED		(5.0f)
#define RANDOM		(3.14f)
#define LIFE		(20)
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

#define COLLECTIVE	(D3DXVECTOR3(0.0f,0.0f,400.0f))

//=====================================================================
// コンストラクタ
//=====================================================================
CParticleCollective::CParticleCollective()
{
    m_fAngle = 0.0f;
    m_fSpeed = 0.0f;
}

//=====================================================================
// デストラクタ
//=====================================================================
CParticleCollective::~CParticleCollective()
{

}

//=====================================================================
// 生成処理
//=====================================================================
CParticleCollective * CParticleCollective::Create(void)
{
    CParticleCollective * pParticle = new CParticleCollective;

    if (pParticle != nullptr)
    {
        pParticle->SetSceneInfo(POS, SIZE);

        pParticle->Init();
        return pParticle;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
HRESULT CParticleCollective::Init(void)
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// 更新処理
//=====================================================================
void CParticleCollective::Update(void)
{
    CParticleInfo::Update();
}

//=====================================================================
// 終了処理
//=====================================================================
void CParticleCollective::Uninit(void)
{
    CParticleInfo::Uninit();
}

//=====================================================================
// 描画処理
//=====================================================================
void CParticleCollective::Draw(void)
{
    CParticleInfo::Draw();
}

//=====================================================================
// パーティクルを出す処理
//=====================================================================
void CParticleCollective::SetParticle(void)
{
    //	収束させる場所の座標を設定
    D3DXVECTOR3 CollectivePos = COLLECTIVE;

    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
    // スピードの値を設定
    m_fSpeed = SPEED;
    // パーティクルの出る角度の設定
    m_fAngle = CLibrary::Random(RANDOM);
    // 移動させるための処理
    D3DXVECTOR3 move = D3DXVECTOR3(sinf(m_fAngle)*m_fSpeed, CLibrary::Random(m_fSpeed), cosf(m_fAngle)*m_fSpeed);
    // 移動情報を設定
    SetMove(move);
    // 色の設定
    SetColor(COLOR);
    // パーティクルが消える時間の設定
    SetLife(LIFE);
}