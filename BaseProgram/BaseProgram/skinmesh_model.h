#ifndef _SKINMESH_MODEL_H_
#define _SKINMESH_MODEL_H_
//=============================================================================
//
// スキンメッシュ用モデルクラス [skinmesh_model.h]
// Author : Takahashi Naoyuki
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"
#include "xfile.h"
#include "skinmesh.h"
#include "model_info.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CModelInfo;
class IHighLevelAnimController;

//=============================================================================
// モデルクラス
//=============================================================================
class CSkinmeshModel : public CScene
{
public:

    //モデル名前
    enum MODEL
    {
        MODEL_PLAYER_10 = 0,        //スライム１０％の状態
        MODEL_PLAYER_50,            //スライム５０％の状態
        MODEL_PLAYER_100,           //スライム１００％の状態
        MODEL_ENEMY_KRAKEN_HEAD,    // クラーケン
        MODEL_MAX
    };
    CSkinmeshModel(PRIORITY Priority = PRIORITY_EFFECT);    // コンストラクタ
    ~CSkinmeshModel();

    HRESULT Init();     // 初期化処理
    void Uninit();      // 終了処理
    void Update();      // 更新処理
    void Draw();        // 描画処理
    static CSkinmeshModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL modelNum);    // インスタンス生成
    void SetModelNumber(MODEL model);
    inline IHighLevelAnimController * GetHLcontroller()const    { return m_HLcontroller; };
    inline void SetPos(const D3DXVECTOR3 &pos)                  { m_pModelInfo->SetPos(pos); }  // 現在の座標情報
    inline void SetRot(const D3DXVECTOR3 &rot)                  { m_pModelInfo->SetRot(rot); }  // 角度情報
    inline void IsDraw(bool bIsDraw)                            { m_bIsDraw = bIsDraw; };       // 描画するか
    inline UINT MaxAction()const                                { return m_pAnimetionController->GetMaxNumAnimationSets(); }

protected:
    // Set関数
    inline void SetMove(const D3DXVECTOR3 &move)       { m_move = move; }              // 移動量の設定
    inline void SetSize(const D3DXVECTOR3 &size)       { m_size = size; }              // サイズの設定
    inline void SetTexPattern(const int &TexPattern)   { m_nTexPattern = TexPattern; } // テクスチャのパターン
    inline void SetLife(const int &nLife)              { m_nLife = nLife; }            // ライフの設定
    inline void SetScale(const D3DXVECTOR3 &scale)     { m_scale = scale; }            // 拡大率

    // Get関数
    inline D3DXVECTOR3 &GetMove()              { return m_move; }           // 移動量の情報
    inline D3DXVECTOR3 GetSize()const          { return m_size; }           // サイズの設定
    inline int GetTexPattern()const            { return m_nTexPattern; }    // テクスチャ
    inline int GetLife()const                  { return m_nLife; }          // ライフの設定
    inline CModelInfo* GetModelInfo()const     { return m_pModelInfo; }     // モデルの情報

private:
    // private関数
    void HasPtrDelete();    // 保持ポインタの開放処理
    void CreateInfoPtr();   // 情報のポインタ生成

    // メンバ変数
    CModelInfo* m_pModelInfo;                           // モデルの情報
    D3DXVECTOR3 m_move;                                 // 移動量
    D3DXVECTOR3 m_size;                                 // サイズ
    D3DXVECTOR3 m_scale;                                // 拡大率
    bool m_bIsDraw;                                     // 描画するか
    int m_nTexPattern;                                  // テクスチャのパターン数
    int m_nLife;                                        // ライフ
    ID3DXAnimationController * m_pAnimetionController;  //アニメーションコントローラー
    SkinMesh::SMD3DXFRAME *m_pRootFrame;                // ルートフレーム
    std::vector<SkinMesh::SMD3DXMESHCONTAINER*> m_cont; // SMD3DXMESHCONTAINER(メッシュ)関連の情報を保存用
    std::vector<D3DXBONECOMBINATION*> m_combs;          //ボーンコンビネーションテーブルのポインタ取得
    IHighLevelAnimController * m_HLcontroller;          //ハイレベルアニメーションコントローラー
    static const char* m_aParam[MODEL_MAX];             //モデルパス名
    MODEL m_ModelNum;                                   // モデルの名前
};
#endif 