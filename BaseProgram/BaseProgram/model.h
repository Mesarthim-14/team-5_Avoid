#ifndef _MODEL_H_
#define _MODEL_H_
//=============================================================================
//
// モデルクラス [model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"
#include "xfile.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CModelInfo;

//=============================================================================
// モデルクラス
//=============================================================================
class CModel : public CScene
{
public:
    CModel(PRIORITY Priority);  // コンストラクタ
    virtual ~CModel();          // デストラクタ

    virtual HRESULT Init();                                                 // 初期化処理
    virtual void Uninit();                                                  // 終了処理
    virtual void Update();                                                  // 更新処理
    virtual void Draw();                                                    // 描画処理
    static CModel *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // インスタンス生成

    // Get関数
    D3DXVECTOR3 GetPos()const;
    D3DXVECTOR3 GetRot()const;
    inline CModelInfo* GetModelInfo()const { return m_pModelInfo; } // モデルの情報

protected:
    bool PlayerDisCollision(const float &fDistanse);    // プレイヤーとの距離の当たり判定

    // Set関数
    inline void SetMove(const D3DXVECTOR3 &move)        { m_move = move; }              // 移動量の設定
    inline void SetSize(const D3DXVECTOR3 &size)        { m_size = size; }              // サイズの設定
    inline void SetTexPattern(const int &TexPattern)    { m_nTexPattern = TexPattern; } // テクスチャのパターン
    inline void SetLife(const int &nLife)               { m_nLife = nLife; }            // ライフの設定
    inline void SetScale(const D3DXVECTOR3 &scale)      { m_scale = scale; }            // 拡大率

    inline D3DXVECTOR3 &GetMove()       { return m_move; }          // 移動量の情報
    inline D3DXVECTOR3 GetSize()const   { return m_size; }          // サイズの設定
    inline int GetTexPattern()const     { return m_nTexPattern; }   // テクスチャ
    inline int GetLife()const           { return m_nLife; }         // ライフの設定

private:
    // private関数
    void HasPtrDelete();    // 保持ポインタの開放処理
    void CreateInfoPtr();   // 情報のポインタ生成

    // メンバ変数
    CModelInfo* m_pModelInfo;   // モデルの情報
    D3DXVECTOR3 m_move;         // 移動量
    D3DXVECTOR3 m_size;         // サイズ
    D3DXVECTOR3 m_scale;        // 拡大率
    int m_nTexPattern;          // テクスチャのパターン数
    int m_nLife;                // ライフ
};
#endif 