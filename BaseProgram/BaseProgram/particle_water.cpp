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
#include "particle_water.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

float CParticleWater::m_fSize = 0.0f;
//=====================================================================
// マクロ定義
// Author : toshiki
//=====================================================================
#define SIZE		(D3DXVECTOR3(m_fSize, m_fSize, m_fSize))
#define ANGLE		(70.0f)
#define SPEED		(80.0f)
#define RANDOM		(3.14f)
#define LIFE		(90)
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// コンストラクタ
// Author : toshiki
//=====================================================================
CParticleWater::CParticleWater()
{
    m_fAngle = 0.0f;
    m_nLife = 0;
}

//=====================================================================
// デストラクタ
// Author : toshiki
//=====================================================================
CParticleWater::~CParticleWater()
{

}

//=====================================================================
// 生成処理
// Author : toshiki
//=====================================================================
CParticleWater * CParticleWater::Create(const D3DXVECTOR3 &pos)
{
    CParticleWater * pParticleWater = new CParticleWater;

    if (pParticleWater)
    {
        m_fSize = CLibrary::Random(50.0f, 100.0f);
        pParticleWater->SetSceneInfo(pos, SIZE);

        pParticleWater->Init();
        return pParticleWater;
    }
    return nullptr;
}

//=====================================================================
// 初期化処理
// Author : toshiki
//=====================================================================
HRESULT CParticleWater::Init()
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// 更新処理
// Author : toshiki
//=====================================================================
void CParticleWater::Update()
{
    CParticleInfo::Update();
}

//=====================================================================
// 終了処理
// Author : toshiki
//=====================================================================
void CParticleWater::Uninit()
{
    CParticleInfo::Uninit();
}

//=====================================================================
// 描画処理
// Author : toshiki
//=====================================================================
void CParticleWater::Draw()
{
    CParticleInfo::Draw();
}

//=====================================================================
// パーティクルの設定
// Author : toshiki
//=====================================================================
void CParticleWater::SetParticle()
{
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_WATER));
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