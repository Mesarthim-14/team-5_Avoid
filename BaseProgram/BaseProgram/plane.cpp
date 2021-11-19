//=============================================================================
//
// 3Dポリゴンクラス [plane.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "plane.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//=============================================================================
// 描画処理
//=============================================================================
void CPlane::Draw()
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);			// ライト無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);	// アルファテストを有力化

	// マトリクス計算
	D3DXMATRIX mtxWorld;
	CLibrary::ConfigMatrix(&mtxWorld, GetPos(), GetRot());

	// ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	SetMtxWorld(mtxWorld);

	// テクスチャの設定
	pDevice->SetTexture(0, GetTexture());

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ライト有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}