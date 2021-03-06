#ifndef _ROTATE_BODY_H_
#define _ROTATE_BODY_H_
//=============================================================================
//
// 回転本体クラス [rotate_body.h]
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
class CRotateBody : public CModel
{
public:
    enum
    {
        COL_NUM = 2,
    };

    CRotateBody(PRIORITY Priority);    // コンストラクタ
    ~CRotateBody();                    // デストラクタ

    static CRotateBody *Create(const D3DXVECTOR3 &pos); // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos);               // 初期化処理
    void Uninit();                                      // 終了処理
    void Update();                                      // 更新処理

private:
    void Col();             // 当たり判定
    void Rotate();          // 回転

    float m_fRotateNum;
    CCollisionModelOBB* m_pColModelOBB[COL_NUM]; // 当たり判定ポインタ(OBB)
};

#endif