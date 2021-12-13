#ifndef _CANVAS_H_
#define _CANVAS_H_
//=============================================================================
//
// 線画調シェーダクラス [canvas.h]
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
class CCanvas : public CShaderSquare
{
public:
    CCanvas(LPDIRECT3DDEVICE9 pd3dDevice, D3DPRESENT_PARAMETERS* pd3dParameters);
    CCanvas(LPDIRECT3DDEVICE9 pd3dDevice, UINT Width, UINT Height);				// コンストラクタ
    ~CCanvas();
    void Invalidate();
    void Restore();
    HRESULT Load();
    void Render(LPDIRECT3DTEXTURE9 pBackBuffer, LPDIRECT3DTEXTURE9 pMaterial, LPDIRECT3DTEXTURE9 pCanvas, bool isTex);
    BOOL IsOK();
    inline LPD3DXEFFECT GetEffect()const { return m_pEffect; };

private:
    LPD3DXEFFECT m_pEffect;
    D3DXHANDLE m_pTechnique;
    LPDIRECT3DDEVICE9 m_pd3dDevice;
};
#endif