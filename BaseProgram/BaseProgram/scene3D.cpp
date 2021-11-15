//=============================================================================
//
// シーン3Dクラス [scene3D.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture_animation.h"
#include "library.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScene3D::CScene3D(PRIORITY Priority) : CSceneBase(Priority)
{
	m_fScaleNum = 0.0f;
	m_nAlphaTestNum = 0;
	m_bAlpha = false;
	m_fAlphaNum = 0.0f;
	m_move = ZeroVector3;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(void)
{
	// 頂点の生成
	CreateVertex();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3D::Uninit(void)
{
	CSceneBase::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{
	// 移動量加算
	GetPos() += m_move;
}

//=============================================================================
// 頂点の生成
//=============================================================================
void CScene3D::CreateVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;							// 頂点バッファ変数の宣言

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	VERTEX_3D*pVtx = nullptr;

	//頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3(-(size.x / 2), (size.y / 2), (size.z / 2));
	pVtx[1].pos = D3DXVECTOR3((size.x / 2), (size.y / 2), (size.z / 2));
	pVtx[2].pos = D3DXVECTOR3(-(size.x / 2), -(size.y / 2), -(size.z / 2));
	pVtx[3].pos = D3DXVECTOR3((size.x / 2), -(size.y / 2),	-(size.z / 2));

	//各頂点の法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//各頂点の法線の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	pVtxBuff->Unlock();

	// バッファの設定
	BindVtxBuff(pVtxBuff);
}

//=============================================================================
// 座標設定(座標更新用)
//=============================================================================
void CScene3D::SetVertexPos(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx = nullptr;
	D3DXVECTOR3 size = GetSize();

	// バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3(-(size.x / 2), +(size.y / 2),(size.z / 2));
	pVtx[1].pos = D3DXVECTOR3(+(size.x / 2), +(size.y / 2),(size.z / 2));
	pVtx[2].pos = D3DXVECTOR3(-(size.x / 2), -(size.y / 2),-(size.z / 2));
	pVtx[3].pos = D3DXVECTOR3(+(size.x / 2), -(size.y / 2),-(size.z / 2));

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//=============================================================================
// 色の設定
//=============================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	// 色を変える
	CSceneBase::SetColor(col);

	// バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D*pVtx = nullptr;

	//頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定（0～255の数値で設定）
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファのアンロック
	pVtxBuff->Unlock();
}

//=============================================
// アニメーション情報取得
//=============================================
void CScene3D::InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop)
{
	// バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D *pVtx = nullptr;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / nPatternAnim)*(float)nPatternAnim, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / nPatternAnim)*(float)nPatternAnim + (float)(1.0f / nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / nPatternAnim)*(float)nPatternAnim, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / nPatternAnim)*(float)nPatternAnim + (float)(1.0f / nPatternAnim), 1.0f);

	// テクスチャ座標を渡す
	D3DXVECTOR2 tex[NUM_VERTEX] = {};
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		tex[nCount] = pVtx[nCount].tex;
	}

	// テクスチャアニメーション生成
	CTextureAnimation *pTextureAnimation = CTextureAnimation::Create(tex);
	pTextureAnimation->InitAnimationInfo(nCounterAnim, nPatternAnim, nLoop);
	SetTextureAnimationPtr(pTextureAnimation);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//=============================================
// アニメーション更新関数
//=============================================
void CScene3D::UpdateAnimation(void)
{
	// テクスチャポインタ取得
	CTextureAnimation *pTextureAnimation = GetTextureAnimationPtr();
	if (pTextureAnimation)
	{
		// テクスチャが更新されていたら
		if (pTextureAnimation->GetUpdate())
		{
			// バッファ取得
			LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
			VERTEX_3D *pVtx = nullptr;

			// 頂点バッファをロックし、頂点情報へのポインタを取得
			pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// テクスチャ座標の設定
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				pVtx[nCount].tex = pTextureAnimation->GetTex(nCount);
			}

			// 頂点バッファをアンロックする
			pVtxBuff->Unlock();
		}
	}
}

//======================================================
// 拡大関数
//======================================================
void CScene3D::ScaleUp(float fScaleUp)
{
	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	m_fScaleNum += fScaleUp;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	// バッファ取得
	VERTEX_3D *pVtx = nullptr;							//頂点情報へのポインタ

	//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-(size.x * m_fScaleNum), +(size.y * m_fScaleNum), (size.z * m_fScaleNum));
	pVtx[1].pos = D3DXVECTOR3(+(size.x * m_fScaleNum), +(size.y * m_fScaleNum), (size.z * m_fScaleNum));
	pVtx[2].pos = D3DXVECTOR3(-(size.x * m_fScaleNum), -(size.y * m_fScaleNum), -(size.z * m_fScaleNum));
	pVtx[3].pos = D3DXVECTOR3(+(size.x * m_fScaleNum), -(size.y * m_fScaleNum), -(size.z * m_fScaleNum));

	//頂点データをアンロック
	pVtxBuff->Unlock();
}

//=============================================================================
// 透明度の減算
//=============================================================================
void CScene3D::SubAlpha(float fAlphaNum)
{
	// 色の情報
	D3DXCOLOR col = GetColor();

	m_fAlphaNum = fAlphaNum;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	// バッファ取得
	VERTEX_3D*pVtx;	//頂点情報へのポインタ

	//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//頂点カラーの設定（0～255の数値で設定）
		pVtx[nCount].col = D3DXCOLOR(col.r, col.g, col.b, col.a - m_fAlphaNum);
	}

	//頂点データをアンロック
	pVtxBuff->Unlock();
}