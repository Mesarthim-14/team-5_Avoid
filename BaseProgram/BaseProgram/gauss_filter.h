#ifndef _GAUSS_FILTER_H_
#define _GAUSS_FILTER_H_
//=============================================================================
//
// モザイク処理 [gauss_filter.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "shader_square.h"
#include "xfile.h"

//=============================================================================
// クラス定義
//=============================================================================
class CGaussFilter
{
public:
    enum
    {
        WEIGHT_MUN = 8, // 重みを計算する個数
    };
    //-------------------------------------------------------------
    // 頂点の構造体
    //-------------------------------------------------------------
    struct TVERTEX
    {
        FLOAT p[4];
        FLOAT tu, tv;
    };

    CGaussFilter(LPDIRECT3DDEVICE9 pd3dDevice);
    ~CGaussFilter();
    void Uninit();
    void Restore();
    HRESULT Load();
    inline LPD3DXEFFECT GetEffect()const { return m_pEffect; };

    void UpdateWeight();                                // 高さの計算
    void BeginSurface();                                // サーフェスの開始
    void DrawPolygon();                                 // ポリゴンの描画
    void FadeOut();                                     // モザイクを消す
    inline void SetFade(const bool& bFlag)  { m_bFade = bFlag; }
    inline bool GetUse()const               { return m_bUse; }

private:
    void ShowInfo();    // imgui情報
    void SetAlphaNum(); // 透明度設定
    void GaussShader(); // ガウスシェーダ設定
    void EndSurface();  // サーフェスを戻す

    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_hTechnique, m_hafWeight, m_htSrcMap, m_AlphaNum;
    LPDIRECT3DDEVICE9 m_pd3dDevice;

    // 通常の座標変換行列
    D3DXMATRIX m_mWorld;
    D3DXMATRIX m_mView;
    D3DXMATRIX m_mProj;

    LPDIRECT3DSURFACE9 m_pMapZ;             // 深度バッファ
    LPDIRECT3DTEXTURE9 m_pOriginalMap;      // テクスチャ
    LPDIRECT3DSURFACE9 m_pOriginalMapSurf;  // サーフェス
    LPDIRECT3DTEXTURE9 m_pXMap;             // テクスチャ
    LPDIRECT3DSURFACE9 m_pXMapSurf;	        // サーフェス
    LPDIRECT3DTEXTURE9 m_pXYMap;            // テクスチャ
    LPDIRECT3DSURFACE9 m_pXYMapSurf;        // サーフェス
    LPDIRECT3DTEXTURE9 m_pAllMap;           // テクスチャ
    LPDIRECT3DSURFACE9 m_pAllMapSurf;       // サーフェス
    LPDIRECT3DTEXTURE9 m_pScreenMap;        // テクスチャ
    LPDIRECT3DSURFACE9 m_pOldBackBuffer, m_pOldZBuffer;
    D3DVIEWPORT9 m_oldViewport;
    float m_dispersion_sq;                  // 分散の平方根
    float m_tbl[WEIGHT_MUN];                // 重みの配列
    float m_fAlphaNum;                      // 透明度
    bool m_bFade;                           // フェードのフラグ
    bool m_bUse;                           // 使用されているかどうか
};
#endif