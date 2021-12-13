#ifndef _TOON_SHADER_H_
#define _TOON_SHADER_H_
//=============================================================================
//
// トゥーンシェーダクラス [toon_shader.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "main.h"
#include "xfile.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CEdgeFilter;
class CCanvas;

//=========================================================================
// クラス定義
//=========================================================================
class CToonShader
{
public:
    enum TOON_PASS
    {
        TOON_PASS_NONE = -1,        // 初期値
        TOON_PASS_SKINMESH_TEX,     // スキンメッシュ(テクスチャあり)
        TOON_PASS_EDGE_FILTER,      // アウトライン
        TOON_PASS_MODEL,            // モデル
        TOON_PASS_SKINMESH_DIFFUSE, // スキンメッシュ(テクスチャ無し)
    };

    CToonShader(LPDIRECT3DDEVICE9 pd3dDevice);  // コンストラクタ
    ~CToonShader();                             // デストラクタ

    void Invalidate();
    void Restore();
    void Init();            // 初期化処理
    void Uninit();          // 終了処理
    void Draw();            // 描画処理
    HRESULT Load();         // シェーダロード
    void TextureLoad();     // テクスチャロード[
    void BeginSurface();    // サーフェスの入れ替え
    void DrawEdgeFilter();  // エッジの描画
    void EndSurface();      // サーフェスの終了

    void Begin();
    void Begin(int nNum, D3DXMATRIX& mtxWorld, CXfile::MODEL model);      // 通常シェーダ
    void Begin(int nNum, D3DXMATRIX& mtxWorld, D3DXVECTOR4* LightDir);    // スキンメッシュシェーダ開始
    void BeginPass(int nNum);                                   // パスの開始
    void SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pLightDir, D3DXVECTOR4* pCameraPos);
    void SetAmbient(float Ambient);
    void SetAmbient(D3DXVECTOR4* pAmbient);
    void CommitChanges();
    void EndPass();
    void End();
    inline LPD3DXEFFECT GetEffect()const { return m_pEffect; };
    void Render(LPDIRECT3DTEXTURE9 pBackBuffer, LPDIRECT3DTEXTURE9 pZBuffer);
    void SetParameters(D3DXVECTOR2* pTexel, float pLimit);
    void SetDiffuse(D3DXVECTOR4 Diffuse);
    void SetVertexBlendInfo(D3DXMATRIX *pMtxWorld[4], D3DXMATRIX pMtxView, D3DXMATRIX pMtxProj, int nNum);

private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique, m_pWVP, m_pLightDir, m_pTexel, m_pLimit, m_pEyePos, m_pMtxWorld, m_Diffuse;
    D3DXHANDLE matWorld[4], matView, matProj, nBlendNum;
    D3DXMATRIX m_matView, m_matProj;
    LPDIRECT3DDEVICE9 m_pd3dDevice;

    CEdgeFilter *m_pEdgeFilter;
    //トーンマップテクスチャー
    LPDIRECT3DTEXTURE9 m_pToonMap;
    //シーンのカラー情報を格納するサーフェイスの宣言
    LPDIRECT3DTEXTURE9 m_pColorTexture;
    LPDIRECT3DSURFACE9 m_pColorSurface;
    //シーンのＺ値情報を格納するサーフェイスの宣言
    LPDIRECT3DTEXTURE9 m_pZMapTexture;
    LPDIRECT3DSURFACE9 m_pZMapSurface;
    //シーンのＺ値情報を格納するサーフェイスの宣言
    LPDIRECT3DTEXTURE9 m_pDiffuseTexture;
    LPDIRECT3DSURFACE9 m_pDiffuseSurface;
    //線画テクスチャー
    LPDIRECT3DTEXTURE9 m_pCanvasTexture;

    LPDIRECT3DSURFACE9 m_OldSurface;
    float m_fLimit;
    CCanvas* m_pCanvas;
};

#endif