#ifndef _SHADOW_H_
#define _SHADOW_H_
//=============================================================================
//
// シャドウクラスヘッダー [shadow.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CShadowVolume;
class CShadowPolygon;

//=========================================================================
// クラス定義
//=========================================================================
class CShadow
{
public:
    CShadow();        // コンストラクタ
    ~CShadow();        // デストラクタ

    static CShadow *Create(const LPD3DXMESH pSrcMesh);                                                          // インスタンス生成
    HRESULT Init(const LPD3DXMESH pSrcMesh);                                                                    // 初期化生成処理
    void Uninit();                                                                                              // 終了処理
    void VolumeDraw();                                                                                          // 影描画処理
    void CreateShadow(const D3DXVECTOR3 &rot, const D3DXVECTOR3 &ShipRot, const D3DXMATRIX &ModelMtxWorld);     // 影の生成
    void CreateShadow(const D3DXVECTOR3 &rot, const D3DXMATRIX &ModelMtxWorld);                                 // 影の生成

    static void SetShadowStateStencil();    // ステンシルの設定
    static void SetShadowStencilTest();     // ステンシルテスト設定
    static void ReSetShadowStateStencil();  // ステンシル情報リセット
    static void PolygonUninit();            // 描画処理

private:
    CShadowVolume *m_pShadowVolume;     // シャドウボリュームのポインタ
    D3DXMATRIX m_ModelMtxWorld;         // モデルのワールド座標取得
    static CShadowPolygon *m_pPolygon;  // ポリゴンのポインタ
};
#endif