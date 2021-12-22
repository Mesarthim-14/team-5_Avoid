#ifndef _POLYGON_H_
#define _POLYGON_H_
//=============================================================================
//
// ポリゴン生成クラス処理 [polygon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// ポリゴンクラス
//=============================================================================
class CPolygon
{
public:
    CPolygon();     // コンストラクタ
    ~CPolygon();    // デストラクタ

    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);  // 初期化処理
    void Uninit();                                                  // 終了処理
    void Update();                                                  // 更新処理
    void Draw();                                                    // 描画処理
    void SetColor(const D3DXCOLOR &color);                          // 色の設定
    void SetMove(const D3DXVECTOR3 &move);

    static CPolygon *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);   // インスタンス生成
    inline void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture) { m_pTexture = pTexture; }

    inline void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }

    inline D3DXVECTOR3 GetPos()const { return m_pos; }               // 座標

private:
    LPDIRECT3DTEXTURE9 m_pTexture;      // テクスチャのポインタ
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; // 頂点バッファへのポインタ
    D3DXVECTOR3 m_size;                 // ポリゴンのサイズ
    D3DXVECTOR3 m_pos;                  // ライフの位置
    D3DXVECTOR3 m_move;

};
#endif 