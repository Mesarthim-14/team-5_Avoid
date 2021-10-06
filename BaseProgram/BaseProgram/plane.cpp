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

//=============================================================================
// 描画処理
//=============================================================================
void CPlane::Draw(void)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DXMATRIX mtxWorld;

	// ライト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテストを有力化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// テクスチャの設定
	pDevice->SetTexture(0, GetTexture());

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// サイズ情報
	D3DXVECTOR3 pos = GetPos();

	// 位置を反映、ワールドマトリクス設定、ポリゴン描画
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	SetMtxWorld(mtxWorld);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ライト有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}