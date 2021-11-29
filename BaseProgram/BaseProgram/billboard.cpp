//=====================================================
//
// ビルボードクラス [billboard.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

//=====================================================
// コンストラクタ
//=====================================================
CBillboard::CBillboard(PRIORITY Priority) : CScene3D(Priority)
{
    m_bBlend = false;
}

//=====================================================
// 描画処理
//=====================================================
void CBillboard::Draw()
{
    // デバイス情報取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //計算用のマトリクス
    D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxWorld;

    // ライト無効
    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    // アルファテストを有力化
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    // 加算合成
    if (m_bBlend)
    {
        // 加算合成を行う
        pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);     // aデスティネーションカラー
    }

    // アルファテスト
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ALPHAREF, GetAlphaTestNum());
    pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

    // テクスチャの設定
    pDevice->SetTexture(0, GetTexture());
    
    // 頂点バッファをデバイスのデータストリームに設定
    pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

    // 頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_3D);

    //ワールドマトリクスの初期化
    D3DXMatrixIdentity(&mtxWorld);

    // サイズ取得
    D3DXVECTOR3 size = GetSize();

    // サイズを反映
    D3DXMatrixScaling(&mtxScale, size.x, size.y, 1.0f);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

    // 回転の逆行列の生成
    pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
    D3DXMatrixInverse(&mtxWorld, nullptr, &mtxRot);
    mtxWorld._41 = 0;
    mtxWorld._42 = 0;
    mtxWorld._43 = 0;

    // サイズ情報
    D3DXVECTOR3 pos = GetPos();

    // 位置を反映、ワールドマトリクス設定、ポリゴン描画
    D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

    // ワールドマトリクスの設定
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

    // ポリゴンの描画
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    // 加算合成を行う処理
    if (m_bBlend)
    {
        pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);    // aデスティネーションカラー
    }

    // アルファテスト無効化
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

    // ライト有効
    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

    // テクスチャの設定
    pDevice->SetTexture(0, nullptr);

}