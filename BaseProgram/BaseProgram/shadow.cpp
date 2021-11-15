//=============================================================================CShadow
//
// シャドウクラス [shadow.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "light.h"
#include "shadow_volume.h"
#include "shadow_polygon.h"

//=============================================================================
// static初期化
//=============================================================================
CShadowPolygon *CShadow::m_pPolygon = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CShadow::CShadow()
{
	m_pShadowVolume = nullptr;
	D3DXMatrixIdentity(&m_ModelMtxWorld);
}

//=============================================================================
// デストラクタ
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CShadow * CShadow::Create(const LPD3DXMESH pSrcMesh)
{
	// メモリ確保
	CShadow *pShadow = new CShadow;

	// !nullcheck
	if (pShadow)
	{
		// 初期化処理
		pShadow->Init(pSrcMesh);
	}

	return pShadow;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShadow::Init(const LPD3DXMESH pSrcMesh)
{
	// nullcheck
	if (!m_pShadowVolume)
	{
		// 影の生成
		m_pShadowVolume = CShadowVolume::Create(pSrcMesh);
	}

	// nullcheck
	if (!m_pPolygon)
	{
		m_pPolygon = CShadowPolygon::Create();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CShadow::Uninit(void)
{
	if (m_pShadowVolume)
	{
		// シャドウボリューム終了処理
		m_pShadowVolume->Uninit();
		delete m_pShadowVolume;
		m_pShadowVolume = nullptr;
	}
}

//=============================================================================
// 影の描画処理
//=============================================================================
void CShadow::VolumeDraw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	// レンダラーポインタ取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelMtxWorld);

	// シャドウの描画
	if (m_pShadowVolume)
	{
		// ステンシル設定
		SetShadowStateStencil();

		// シャドウボリュームの描画
		m_pShadowVolume->Draw();

		// 状態を元に戻す
		// ステンシルテストは常に合格にする
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	//	pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		// レンダリングターゲットに書き込みはしない
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	}
}

//=============================================================================
// 影の生成処理
//=============================================================================
void CShadow::CreateShadow(const D3DXVECTOR3 rot, const D3DXVECTOR3 ShipRot, const D3DXMATRIX ModelMtxWorld)
{
	// ワールド座標を受け取る
	m_ModelMtxWorld = ModelMtxWorld;

	// 影の生成
	if (m_pShadowVolume)
	{
		m_pShadowVolume->CreateShadow(rot, ShipRot);
	}
}

//=============================================================================
// 影の生成処理
//=============================================================================
void CShadow::CreateShadow(const D3DXVECTOR3 rot, const D3DXMATRIX ModelMtxWorld)
{
	// 影の生成
	if (m_pShadowVolume)
	{
		m_pShadowVolume->CreateShadow(rot);
	}

	// ワールド座標を受け取る
	m_ModelMtxWorld = ModelMtxWorld;
}

//=============================================================================
// ステンシルの設定
// Author : Konishi Yuuto
//=============================================================================
void CShadow::SetShadowStateStencil(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;


	//------------------------------------------------------------
	// パス1:影ボリュームの描画
	//------------------------------------------------------------
	// 深度バッファに書き込みはしない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// レンダリングターゲットに書き込みはしない
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, FALSE);

	// 両面描く
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 両面ステンシルを使用する
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, TRUE);

	// ステンシルテストは常に合格にする
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	// 表面は深度テストに合格したらステンシルバッファの内容を+1する
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

	// 裏面は深度テストに合格したらステンシルバッファの内容を-1する
	pDevice->SetRenderState(D3DRS_CCW_STENCILPASS, D3DSTENCILOP_DECR);
}

//=============================================================================
// ステンシルテスト設定
// Author : Konishi Yuuto
//=============================================================================
void CShadow::SetShadowStencilTest(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	// 状態を元に戻す
	pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);

	//--------------------------------------------------------------
	// パス2:影の描画
	//--------------------------------------------------------------
	// アルファブレンディングは線型に掛ける
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// ステンシルバッファの値が1以上の時に書き込む
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);

	// 透過あり
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ステンシル設定リセット
// Author : Konishi Yuuto
//=============================================================================
void CShadow::ReSetShadowStateStencil(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

	// 状態を元に戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CShadow::PolygonUninit(void)
{
	if (m_pPolygon)
	{
		// ポリゴン終了処理
		m_pPolygon->Uninit();
		m_pPolygon = nullptr;
	}
}