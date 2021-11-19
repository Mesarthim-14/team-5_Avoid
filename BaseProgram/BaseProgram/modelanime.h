#ifndef _MODELANIME_H_
#define _MODELANIME_H_
//=============================================================================
//
// 階層構造用のモデルクラス [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "xfile.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CModelInfo;

//=============================================================================
//階層モデルクラス
//=============================================================================
class CModelAnime
{
public:
    CModelAnime();  // コンストラクタ
    ~CModelAnime(); // デストラクタ

    static CModelAnime *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXfile::MODEL &model); // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXfile::MODEL &model);               // 初期化処理
    void Draw(const D3DXVECTOR3 &rot);                                                                      // 描画処理
    void ShadowDraw(const D3DXVECTOR3 &rot);                                                                // 影の描画

    // Set関数
    inline void SetParent(CModelAnime *pParent)             { m_pParent = pParent; }        // 親の設定
    inline void SetPosAnime(const D3DXVECTOR3& posAnime)    { m_posAnime = posAnime; }      // アニメーションパーツの座標
    inline void SetRotAnime(const D3DXVECTOR3& rotAnime)    { m_rotAnime = rotAnime; }      // パーツの角度
    inline void SetRotCalculation(const bool &bFlag)        { m_bRotCalculation = bFlag; }  // 角度の計算フラグの設定

    // Get情報
    inline CModelAnime* GetParent()const    { return m_pParent; }       // 親情報の取得
    inline D3DXVECTOR3 GetPosAnime()const   { return m_posAnime; }      // アニメーション座標情報
    inline D3DXVECTOR3 GetRotAnime()const   { return m_rotAnime; }      // アニメーション角度情報
    inline CModelInfo* GetModelInfo()const  { return m_pModelInfo; }    // モデルの情報

private:
    // private関数
    void CreateInfoPtr();   // 情報生成
    void HasPtrDelete();    // 保持ポインタの開放処理

    // メンバ変数
    CModelInfo *m_pModelInfo;   // モデル情報
    D3DXVECTOR3 m_posAnime;     // アニメーション用の位置
    D3DXVECTOR3 m_rotAnime;     // アニメーション用の向き
    CModelAnime *m_pParent;     // 親情報のポインタ

    // 影の生成用
    bool m_bRotCalculation; // 角度の計算フラグ
};

#endif 