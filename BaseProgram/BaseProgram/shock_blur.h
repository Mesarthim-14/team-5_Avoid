#ifndef _SHOCK_BLUR_H_
#define _SHOCK_BLUR_H_
//=============================================================================
//
// 爆発用ブラークラス [shock_filter.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "shader_square.h"

//=============================================================================
// クラス定義
//=============================================================================
class CShockBlur : public CShaderSquare
{
public:
    CShockBlur(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height);  // コンストラクタ
    ~CShockBlur();                                                      // デストラクタ

    void Uninit();                                  // 終了処理
    void Invalidate();                              // デバイスの削除
    void Restore();                                 // リストラ
    HRESULT Load();                                 // ロード
    void TextureLoad();                             // テクスチャロード
    void SetCenterTexel(float TU, float TV);        // テクセルの中心座標を送る
    void SetBlurPower(const float &fBlurPower);     // ブラーの強さ
    void BlurRender();                              // 描画処理
    void Begin();                                   // 開始
    void Draw();                                    // 描画処理
    void EndSurface();                              // サーフェス終了

    void SubPower(const float& fSub);
    inline LPD3DXEFFECT GetEffect()const { return m_pEffect; };

private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique, m_pCenterTexel, m_pTU, m_pTV, m_pBlurPower;
    LPDIRECT3DDEVICE9 m_pd3dDevice;
    //レンダーターゲットサーフェイス
    LPDIRECT3DTEXTURE9 m_pFullScreenTexture;
    LPDIRECT3DSURFACE9 m_pFullScreenSurface;
    D3DVIEWPORT9 m_OldViewport;
    LPDIRECT3DSURFACE9 m_OldSurface;
    float m_fPower;
};

#endif