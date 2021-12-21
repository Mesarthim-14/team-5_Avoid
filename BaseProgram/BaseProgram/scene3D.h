#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//=============================================================================
//
// 3Dポリゴンクラスヘッダー [scene3D.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene_base.h"

//=========================================================================
// 3Dポリゴンクラス
//=========================================================================
class CScene3D :public CSceneBase
{
public:
    CScene3D(PRIORITY Priority = PRIORITY_EFFECT);  // コンストラクタ
    virtual ~CScene3D();                            // デストラクタ
    
    virtual HRESULT Init();                        // 初期化処理
    virtual void Uninit();                         // 終了処理
    virtual void Update();                         // 更新処理
    virtual void Draw() = 0;                       // 描画処理

protected:
    void SetVertexPos();    // 座標の更新

    // Set関数
    void SubAlpha(const float &fAlphaNum);                                                  // 透明度の減算
    void InitAnimation(const int &nCounterAnim, const int &nPatternAnim, const int &nLoop); // アニメーション情報初期化
    void SetColor(const D3DXCOLOR &color);                                                  // カラーの設定
    void ScaleUp(const float &fScale);                                                      // 拡大処理
    void ScaleDown(const float &fScale);                                                    // 縮小処理
    inline void SetMove(const D3DXVECTOR3 &move)        { m_move = move; }                  // 移動量
    inline void SetAlpha(const bool &bAlpha)            { m_bAlpha = bAlpha; }              // アルファテスト
    inline void SetAlphaNum(const int &nAlphaNum)       { m_nAlphaTestNum = nAlphaNum; }    // アルファテストの値
    inline void SetBlend(const bool &bBlend)            { m_bBlend = bBlend; }              // 加算合成
    inline void SetMtxWorld(const D3DXMATRIX mtxWorld)  { m_mtxWorld = mtxWorld; }          // ワールドマトリクスの設定

    // Get関数
    inline D3DXMATRIX GetMtxWorld()const    { return m_mtxWorld; }      // ワールドマトリクス
    inline int GetAlphaTestNum()const       { return m_nAlphaTestNum; } // アルファテストの値

private:
    // private関数
    void CreateVertex();    // 頂点の設定
    void UpdateAnimation(); // アニメーションの更新

    // メンバ変数
    D3DXMATRIX m_mtxWorld;  // ワールドマトリクス
    D3DXVECTOR3 m_move;     // 移動量
    int m_nLife;            // ライフ
    int m_nAlphaTestNum;    // 透明の値
    float m_fScaleNum;      // 拡大値
    float m_fAlphaNum;      // 透明度
    bool m_bAlpha;          // 透明を使うフラグ
    bool m_bBlend;          // 加算合成
};
#endif