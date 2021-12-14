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

D3DXVECTOR3 CParticleNormal::m_Rot = ZeroVector3;
//=====================================================================
// マクロ定義
// Author : toshiki
//=====================================================================
#define POS         (ZeroVector3)
#define SIZE        (D3DXVECTOR3(650.0f, 400.0f, 400.0f))
#define SPEED       (7.0f)
#define RANDOM      (3.14f)
#define LIFE        (200)
#define COLOR       (D3DXCOLOR(1.0f,1.0f,1.0f,m_fColor))

//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CParticleNormal::CParticleNormal()
{
    m_fAngle = 0.0f;
    m_fSpeed = 0.0f;
    m_fColor = 0.5f;
    m_nCnt = 0;
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
CParticleNormal * CParticleNormal::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    CParticleNormal * pParticle = new CParticleNormal;

    if (pParticle != nullptr)
    {
        pParticle->SetSceneInfo(D3DXVECTOR3(pos.x, pos.y - 100.0f, pos.z), SIZE);
        m_Rot = rot;
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
    SetParticleColor();
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
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_SMOKE));
    // スピードの値を設定
    m_fSpeed = SPEED;
    // パーティクルの出る角度の設定
    m_fAngle = CLibrary::Random(RANDOM);
    // 移動させるための処理
    D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
    // 移動情報を設定
    SetMove(move);
    // パーティクルが消える時間の設定
    SetLife(LIFE);
}

//=====================================================================
// パーティクルを徐々に消す処理
// Author : toshiki
//=====================================================================
void CParticleNormal::SetParticleColor(void)
{
    m_nCnt++;
    // 徐々に消えていく処理
    if (m_nCnt >= 5)
    {
        m_fColor -= 0.01f;
        m_nCnt = 0;
    }
    SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColor));
}
