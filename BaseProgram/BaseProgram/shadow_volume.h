#ifndef _SHADOW_VOLUME_H_
#define _SHADOW_VOLUME_H_
//=============================================================================
//
// シャドウボリュームクラスヘッダー [shadow_volume.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "main.h"

//=========================================================================
// クラス定義
//=========================================================================
class CShadowVolume
{
public:
    CShadowVolume();    // コンストラクタ
    ~CShadowVolume();   // デストラクタ

    static CShadowVolume *Create(const LPD3DXMESH &pSrcMesh);                   // インスタンス生成
    HRESULT Init(const LPD3DXMESH &pSrcMesh);                                   // 初期化生成処理
    void Uninit();                                                              // 終了処理
    void Draw();                                                                // 描画処理
    HRESULT CreateShadow(const D3DXVECTOR3 &rot, const D3DXVECTOR3 &Rot);       // 影の生成
    HRESULT CreateShadow(const D3DXVECTOR3 &Rot);                               // 影の生成

private:
    // メッシュ情報の構造体
    struct MESHVERTEX
    {
        D3DXVECTOR3 pos, nor;
        FLOAT tu, tv;
    };
    // private関数
    void AddEdge(WORD* pEdges, DWORD& dwNumEdges, const WORD &v0, const WORD &v1);    // エッジの設定
    void CreateVolume(const vector<D3DXVECTOR3> &pos, const D3DXVECTOR3 &Lpos);       // シャドウボリューム

    // メンバ変数
    D3DXVECTOR3 m_LightPos;         // ライトの座標
    DWORD m_dwNumVertices;          // 頂点数
    D3DXVECTOR3 m_pVertice[32000];  // 頂点の配列
    LPD3DXMESH m_pSrcMesh;          // メッシュ情報
    MESHVERTEX *m_MeshVertices;     // メッシュの情報
    WORD *m_pIndices;               // インデックス数
    DWORD m_dwNumFaces;             // メッシュの面の数
    WORD *m_pEdges;                 // エッジの数
};
#endif