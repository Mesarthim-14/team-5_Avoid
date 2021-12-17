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
#include "model.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CCollisionModelOBB;

//=========================================================================
// クラス定義
//=========================================================================
class CMoveScaffold : public CModel
{
public:
    CMoveScaffold(PRIORITY = PRIORITY_TEST_MODEL);  // コンストラクタ
    ~CMoveScaffold();                               // デストラクタ

    static CMoveScaffold *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot); // インスタンス生成
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                 // 初期化処理
    void Uninit()override;                                                        // 初期化処理
    void Update()override;                                                        // 更新処理
    void Draw()override;                                                          // 描画

    void HitOBBs(); // OBB同士の当たり判定
    void Respawn(); // リスポーン時の処理

private:
    // private関数
    void Move();    // 移動量

    int m_nTime;
    float m_fSpeed;

    CCollisionModelOBB* m_pColModelOBB; // 当たり判定モデルポインタ(OBB)
    D3DXVECTOR3 m_StartPos;             // 始まりの位置
    D3DXVECTOR3 m_GoalPos;              // ゴールの位置
    bool m_bMove;                       // 移動のフラグ
};

#endif