//=====================================================================
//
//	パーティクル処理[particle.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "particleshrink.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

float CParticleShrink::m_fAngleX = 0.0f;
float CParticleShrink::m_fAngleZ = 0.0f;
//=====================================================================
// マクロ定義
//=====================================================================
#define PARTICLE_POS	((D3DXVECTOR3(m_fAngleX, 5.0f, m_fAngleZ)))
#define SIZE			(D3DXVECTOR3(25.0f, 25.0f, 25.0f))
#define SPEED			(5.0f)
#define RANDOM			(3.14f)
#define LIFE			(60)
#define COLOR			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// コンストラクタ
//=====================================================================
CParticleShrink::CParticleShrink()
{
	m_fSpeed = 0.0f;
	ShrinkPos = ZeroVector3;
}

//=====================================================================
// デストラクタ
//=====================================================================
CParticleShrink::~CParticleShrink()
{

}

//=====================================================================
// 生成処理
//=====================================================================
CParticleShrink * CParticleShrink::Create(void)
{
	CParticleShrink * pParticle = new CParticleShrink;

	if (pParticle != nullptr)
	{
		m_fAngleX = CLibrary::Random(300.0f);
		m_fAngleZ = CLibrary::Random(300.0f);
		pParticle->SetSceneInfo(PARTICLE_POS, SIZE);

		pParticle->Init();
		return pParticle;
	}
	return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
HRESULT CParticleShrink::Init(void)
{
	CParticleInfo::Init();
	SetParticle();
	return S_OK;
}

//=====================================================================
// 更新処理
//=====================================================================
void CParticleShrink::Update(void)
{
	CParticleInfo::Update();
}

//=====================================================================
// 終了処理
//=====================================================================
void CParticleShrink::Uninit(void)
{
	CParticleInfo::Uninit();
}

//=====================================================================
// 描画処理
//=====================================================================
void CParticleShrink::Draw(void)
{
	CParticleInfo::Draw();
}

//=====================================================================
// パーティクルを出す処理
//=====================================================================
void CParticleShrink::SetParticle(void)
{
	// テクスチャの設定
	CTexture *pTexture = GET_TEXTURE_PTR;
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
	// スピードの値を設定
	m_fSpeed = SPEED;
	float fTangent = atan2f(ShrinkPos.z - m_fAngleX, ShrinkPos.x - m_fAngleZ);
	// 移動させるための処理
	D3DXVECTOR3 move = D3DXVECTOR3(sinf(fTangent), 0.2f, cosf(fTangent));
	// 移動情報を設定
	SetMove(move);
	// 色の設定
	SetColor(COLOR);
	// パーティクルが消える時間の設定
	SetLife(LIFE);
}
