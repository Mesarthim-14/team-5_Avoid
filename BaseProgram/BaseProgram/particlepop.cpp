//=====================================================================
//
//	パーティクル処理[particlepop.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
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
//=====================================================================
#define POS			(ZeroVector3)
#define SIZE		(D3DXVECTOR3(m_fSize, m_fSize, m_fSize))
#define ANGLE		(4.0f)
#define SPEED		(10.0f)
#define RANDOM		(3.14f)
#define LIFE		(90)
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// コンストラクタ
//=====================================================================
CParticlePop::CParticlePop()
{
	m_fAngle = 0.0f;
	m_nLife = 0;
}

//=====================================================================
// デストラクタ
//=====================================================================
CParticlePop::~CParticlePop()
{

}

//=====================================================================
// 生成処理
//=====================================================================
CParticlePop * CParticlePop::Create(void)
{
	CParticlePop * pParticlePop = new CParticlePop;

	if (pParticlePop)
	{
		m_fSize = CLibrary::Random(20.0f, 60.0f);
		pParticlePop->SetSceneInfo(POS, SIZE);

		pParticlePop->Init();
		return pParticlePop;
	}
	return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
HRESULT CParticlePop::Init(void)
{
	CParticleInfo::Init();
	SetParticle();
	return S_OK;
}

//=====================================================================
// 更新処理
//=====================================================================
void CParticlePop::Update(void)
{
	CParticleInfo::Update();
}

//=====================================================================
// 終了処理
//=====================================================================
void CParticlePop::Uninit(void)
{
	CParticleInfo::Uninit();
}

//=====================================================================
// 描画処理
//=====================================================================
void CParticlePop::Draw(void)
{
	CParticleInfo::Draw();
}

//=====================================================================
// パーティクルの設定
//=====================================================================
void CParticlePop::SetParticle(void)
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