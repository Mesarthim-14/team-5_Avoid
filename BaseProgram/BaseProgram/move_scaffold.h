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

    static CMoveScaffold *Create(); // インスタンス生成
    HRESULT Init();                 // 初期化処理
    void Uninit();                  // 初期化処理
    void Update();                  // 更新処理
    void Draw();                    // 描画

    void HitOBBs(); // OBB同士の当たり判定

private:
    // private関数
    void Move();    // 移動量

    int m_nTime;
    float m_fSpeed;

    CCollisionModelOBB* m_pColModelOBB; // 当たり判定モデルポインタ(OBB)
};

#endif