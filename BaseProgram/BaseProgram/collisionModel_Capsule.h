#ifndef _COLLISION_MODEL_CAPSULE_H_
#define _COLLISION_MODEL_CAPSULE_H_
//=============================================================================
//
// 当たり判定モデル(カプセル)の処理 [collisionModel_Capsule.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCollisionModelCapsule :public CScene
{
public:
    // カプセルモデルを作るために使うメッシュとバッファの列挙型
    enum TYPE
    {
        TYPE_NONE = -1,
        TYPE_CYLINDER,
        TYPE_SPHERE_1,
        TYPE_SPHERE_2,
        TYPE_MAX
    };
    
    // 位置/大きさ/角度情報の構造体
    struct INFO
    {
        D3DXVECTOR3 pos;    // 位置
        float radius;       // 半径
        float length;       // 長さ
        D3DXVECTOR3 rot;    // 角度
        D3DXVECTOR3 P0;     // 線分の始点
        D3DXVECTOR3 P1;     // 線分の終点
    };

    CCollisionModelCapsule(PRIORITY = PRIORITY_COLLISION); // コンストラクタ
    ~CCollisionModelCapsule();                             // デストラクタ

    void Load();    // ロード処理
    void Unload();  // アンロード処理

    static CCollisionModelCapsule *Create(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot);    // 生成処理

    HRESULT Init(); // 初期化処理
    void Uninit();  // 終了処理
    void Update();  // 更新処理
    void Draw();    // 描画処理

    inline void SetInfo(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot)
    { m_info.pos = pos; m_info.radius = radius; m_info.length = length; m_info.rot = rot; }     // 位置/半径/長さ/角度の設定

    INFO GetInfo()const { return m_info; }  // 位置/半径/長さ/角度情報の取得

private:
    void SetPos(const int &nCount);  // 位置の設定
    void SetSize(const int &nCount); // 大きさの設定
    void SetRot(const int &nCount);  // 角度の設定

    LPD3DXMESH m_apMesh[TYPE_MAX];      // メッシュ情報のポインタ
    LPD3DXBUFFER m_apBuffMat[TYPE_MAX]; // マテリアル情報のポインタ
    D3DXMATRIX m_mtxWorld;              // 行列計算用
    INFO m_info;        // 位置/大きさ/角度情報
};
#endif