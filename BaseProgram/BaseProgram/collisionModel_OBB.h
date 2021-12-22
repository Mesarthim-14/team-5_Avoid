#ifndef _COLLISION_MODEL_OBB_H_
#define _COLLISION_MODEL_OBB_H_
//=============================================================================
//
// 当たり判定モデル(直方体)の処理 [collisionModel_OBB.h]
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
class CCollisionModelOBB :public CCollisionModel
{
public:
    //OBB情報の構造体
    struct OBB
    {
        INFO info;
        D3DXVECTOR3 DirVect[AXIS_NUM_OBB];  // 方向ベクトル
    };

    // 当たった面の列挙型
    enum SURFACE
    {
        SURFACE_NONE = -1,
        SURFACE_UP,         // 上面
        SURFACE_SIDE,       // 側面
        SURFACE_MAX
    };

    CCollisionModelOBB(PRIORITY Priority); // コンストラクタ
    ~CCollisionModelOBB();                 // デストラクタ

    static CCollisionModelOBB *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot);    // 生成処理

    HRESULT Init(); // 初期化処理
    void Uninit();  // 終了処理
    void Update();  // 更新処理
    void Draw();    // 描画処理

    inline OBB GetOBB()const { return{ GetInfo(), {m_DirVect[0], m_DirVect[1], m_DirVect[2] } }; }    // OBBの取得

private:
    D3DXVECTOR3 m_DirVect[AXIS_NUM_OBB];  // 方向ベクトル
};
#endif