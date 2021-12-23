#ifndef _COLLISION_MODEL_H_
#define _COLLISION_MODEL_H_
//=============================================================================
//
// 当たり判定モデルの親クラス処理 [collisionModel.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
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
        TYPE_NONE = -1,
        TYPE_POLYGON,   // ポリゴン
        TYPE_OBB,       // 直方体
        TYPE_SPHERE,    // 球体
        TYPE_CAPSULE,   // カプセル
        TYPE_CYLINDER,  // 円柱
        TYPE_MAX
    };

    // 位置/大きさ/角度情報の構造体
    struct INFO
    {
        D3DXVECTOR3 pos;    // 位置
        D3DXVECTOR3 size;   // 大きさ
        D3DXVECTOR3 rot;    // 角度
    };

    CCollisionModel(PRIORITY Priority); // コンストラクタ
    ~CCollisionModel();                 // デストラクタ

    void Load();    // ロード処理
    void Unload();  // アンロード処理

    HRESULT Init(); // 初期化処理
    void Uninit();  // 終了処理
    void Update();  // 更新処理
    void Draw();    // 描画処理

    inline void SetInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot)
    { m_info.pos = pos; m_info.size = size; m_info.rot = rot; }     // 位置/大きさ/角度の設定

protected:
    inline INFO GetInfo()const { return m_info; }               // 位置/大きさ/角度情報
    inline void SetType(const TYPE &type) { m_type = type; }    // 当たり判定タイプの設定

private:
    void SetMtx();  // ワールドマトリックスの設定

    LPD3DXMESH m_pMesh;         // メッシュ情報のポインタ
    LPD3DXBUFFER m_pBuffMat;    // マテリアル情報のポインタ
    D3DXMATRIX m_mtxWorld;      // 行列計算用
    INFO m_info;                // 位置/大きさ/角度情報
    TYPE m_type;                // 当たり判定タイプ
};
#endif