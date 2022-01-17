#ifndef _MOVE_SCAFFOLD_H_
#define _MOVE_SCAFFOLD_H_
//=============================================================================
//
// 動く足場クラス [move_scaffold.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "map.h"
#include "collisionModel_OBB.h"

//=========================================================================
// クラス定義
//=========================================================================
class CMoveScaffold : public CMap
{
public:
    CMoveScaffold(PRIORITY Priority);  // コンストラクタ
    ~CMoveScaffold();                  // デストラクタ

    static CMoveScaffold *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot); // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                 // 初期化処理
    void Uninit()override;                                                        // 初期化処理
    void Update()override;                                                        // 更新処理
    void Draw()override;                                                          // 描画

    void Respawn(); // リスポーン時の処理

private:
    // private関数
    void Move();        // 移動量
    void CarryPlayer(); // プレイヤーを運ぶ
    void OnOBBs();      // 乗っているかの判定
    void Col();         // 当たり判定

    // メンバ変数
    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // 当たり判定モデルポインタ(OBB)
    D3DXVECTOR3 m_StartPos;                                                 // 始まりの位置
    D3DXVECTOR3 m_GoalPos;                                                  // ゴールの位置
    int m_nTime;                                                            // 時間
    float m_fSpeed;                                                         // 速度
    bool m_bMove;                                                           // 移動のフラグ
};

#endif