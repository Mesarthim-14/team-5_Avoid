#ifndef _KRAKEN_TENTACLES_H_
#define _KRAKEN_TENTACLES_H_
//=============================================================================
//
// クラーケンの触手 [kraken_tentacles.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"
#include "state_object.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CSkinmeshModel;
class CCollisionModelOBB;

//=============================================================================
// クラス定義
//=============================================================================
class CKrakenTentacles : public CScene
{
public:
    CKrakenTentacles(PRIORITY Priority = PRIORITY_MODEL);    // コンストラクタ
    ~CKrakenTentacles();                                         // デストラクタ

    static CKrakenTentacles *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);    // インスタンス生成
    HRESULT Init();                                                                     // 初期化処理
    void Uninit();                                                                      // 終了処理
    void Update();                                                                      // 更新処理
    void Draw() {}                                                                      // 描画処理

private:
    // private関数
    void CreateModel();     // モデルの生成
    void SetTentaclesInfo(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

    // メンバ変数
    CSkinmeshModel *m_pSkinmeshModel;   // スキンメッシュモデルポインタ
    D3DXVECTOR3 m_pos;                  // 座標
    D3DXVECTOR3 m_rot;                  // 角度
};
#endif