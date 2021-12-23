#ifndef _COLLISION_MODEL_POLYGON_H_
#define _COLLISION_MODEL_POLYGON_H_
//=============================================================================
//
// 当たり判定モデル(ポリゴン)の処理 [collisionModel_Polygon.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "collisionModel.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCollisionModelPolygon :public CCollisionModel
{
public:
    // ポリゴン情報の構造体
    struct POLYGON
    {
        INFO info;                          // 基本情報
        D3DXVECTOR3 norVec;                 // 法線ベクトル
        D3DXVECTOR3 DirVect[AXIS_NUM_OBB];  // 方向ベクトル
    };

    CCollisionModelPolygon(PRIORITY Priority); // コンストラクタ
    ~CCollisionModelPolygon();                 // デストラクタ

    static CCollisionModelPolygon *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR2 &size, const D3DXVECTOR3 &rot);    // 生成処理

    HRESULT Init(); // 初期化処理
    void Uninit();  // 終了処理
    void Update();  // 更新処理
    void Draw();    // 描画処理

    inline POLYGON GetPolygon()const { return{ GetInfo(), m_norVec,{ m_DirVect[0], m_DirVect[1], m_DirVect[2] } }; }   // ポリゴン情報の取得

private:
    D3DXVECTOR3 m_norVec;                   // 法線ベクトル
    D3DXVECTOR3 m_DirVect[AXIS_NUM_OBB];    // 方向ベクトル
};
#endif