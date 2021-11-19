//=============================================================================
//
// 当たり判定モデルの処理 [collisionModel.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _COLLISION_MODEL_H_
#define _COLLISION_MODEL_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define AXIS_NUM_OBB (3) //OBBの軸数

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CCollisionModel :public CScene
{
public:
    // 当たり判定タイプの列挙型
    enum TYPE
    {
        TYPE_NONE = 0,
        TYPE_POLYGON,   // ポリゴン
        TYPE_BOX,       // 箱
        TYPE_SPHERE,    // 球
        TYPE_CYLINDER,  // 円柱
        TYPE_MAX
    };

    //OBB情報の構造体
    struct OBB
    {
        D3DXVECTOR3 pos;                    // 位置
        D3DXVECTOR3 size;                   // 大きさ
        D3DXVECTOR3 rot;                    // 角度
        D3DXVECTOR3 DirVect[AXIS_NUM_OBB];  // 方向ベクトル
        TYPE CollisionType;                 // 当たり判定のタイプ
    };

    CCollisionModel(PRIORITY = PRIORITY_COLLISION); // コンストラクタ
    ~CCollisionModel();                             // デストラクタ

    void Load();        //ロード処理
    void Unload();      //アンロード処理

    static CCollisionModel *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const TYPE &type);    // 生成処理

    HRESULT Init();        // 初期化処理
    void Uninit(void);    // 終了処理
    void Update(void);    // 更新処理
    void Draw(void);    // 描画処理

    // 各種設定
    inline void SetPos(const D3DXVECTOR3 &pos)     { m_obb.pos = pos; }            // 位置
    inline void SetSize(const D3DXVECTOR3 &size)   { m_obb.size = size; }          // 大きさ
    inline void SetRot(const D3DXVECTOR3 &rot)     { m_obb.rot = rot; }            // 角度
    inline void SetCollisionType(const TYPE &type) { m_obb.CollisionType = type; } // 種類

    inline OBB GetOBB()const { return m_obb; }    // OBBの取得

private:
    LPD3DXMESH m_pMesh;         // メッシュ情報のポインタ
    LPD3DXBUFFER m_pBuffMat;    // マテリアル情報のポインタ
    D3DXMATRIX m_mtxWorld;      // 行列計算用
    OBB m_obb;                  // OBB情報変数
};
#endif