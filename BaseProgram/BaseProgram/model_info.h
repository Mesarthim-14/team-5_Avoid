#ifndef _MODEL_INFO_H_
#define _MODEL_INFO_H_
//=============================================================================
//
// モデルの情報クラス[model_info.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "xfile.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CShadow;

//=============================================================================
//階層モデルクラス
//=============================================================================
class CModelInfo
{
public:
    // モデルの種類
    enum MODEL_TYPE
    {
        MODEL_TYPE_NONE = 0,    // 設定なし
        MODEL_TYPE_CHARACTER,   // キャラクター
        MODEL_TYPE_OBJECT,      // オブジェクト
        MODEL_TYPE_MAX          // 最大値
    };

    CModelInfo(const MODEL_TYPE &type); // コンストラクタ
    ~CModelInfo();                      // デストラクタ

    static CModelInfo *Create(const MODEL_TYPE &type);    // インスタンス生成

    HRESULT Init();                             // 初期化処理
    void Uninit();                              // 終了処理
    void Draw(const D3DXVECTOR3 &rot);          // 描画処理
    void ShadowDraw(const D3DXVECTOR3 &rot);    // 影の描画
    void CreateShadowPtr();                     // 影の生成

    // Set関数
    inline void SetPos(const D3DXVECTOR3 &pos)              { m_posOld = m_pos;  m_pos = pos; }           // 座標
    inline void SetRot(const D3DXVECTOR3 &rot)              { m_rot = rot; }                            // 向き設定
    inline void SetModel(const CXfile::MODEL &model)        { m_model = model; }                        // モデル情報の設定
    inline void SetMtxWorld(const D3DXMATRIX &mtxWorld)     { m_mtxWorld = mtxWorld; }                  // マトリクスワールド設定
    void SetModelStatus(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const CXfile::MODEL &model);    // モデル情報の設定
    D3DXMATRIX SetShadowInfo(const D3DXVECTOR3 &rot, const D3DXMATRIX &pParent);                        // 影の情報の設定

    // Get情報
    inline D3DXVECTOR3 &GetPos()       { return m_pos; }                // 座標情報
    inline D3DXVECTOR3 &GetPosOld()    { return m_posOld; }             // 過去の座標情報
    inline D3DXVECTOR3 &GetRot()       { return m_rot; }                // 角度の情報
    inline D3DXMATRIX GetMtxWorld()    { return m_mtxWorld; }           // ワールドマトリクス情報
    inline D3DXMATRIX GetOldMtxWorld() { return m_OldMtxWorld; }        // 古いワールドマトリクスの情報
    inline LPD3DXMESH GetMesh()        { return m_model.pMesh; }        // モデル情報取得
    inline LPD3DXBUFFER GetBuffMat()   { return m_model.pBuffMat; }     // バッファ情報
    inline DWORD GetNumMat()           { return m_model.dwNumMat; }     // マトリクスの数
    inline CXfile::MODEL GetModel()    { return m_model; }              // モデルの情報
    inline CShadow* GetShadow()        { return m_pShadow; }            // 影のポインタ
    D3DXVECTOR3 GetMtxPos();                                            // マトリクス座標

private:
    // private関数
    void HasPtrDelete();            // 保持ポインタの開放処理

    // メンバ変数
    D3DXVECTOR3 m_pos;          // 位置
    D3DXVECTOR3 m_posOld;       // 過去の位置
    D3DXVECTOR3 m_rot;          // 向き
    D3DXMATRIX m_mtxWorld;      // ワールドマトリックス
    D3DXMATRIX m_OldMtxWorld;   // 古いワールド座標
    CXfile::MODEL m_model;      // モデル情報
    MODEL_TYPE m_type;          // 種類

    // 影の生成用
    CShadow *m_pShadow; // 影のポインタ
    bool m_bUseShadow;  // 影の使用フラグ

    // モデルの情報リスト
    static list<CModelInfo*> m_ModelInfoList[MODEL_TYPE_MAX];
};

#endif 