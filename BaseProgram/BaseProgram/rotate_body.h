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
// クラス定義
//=========================================================================
class CRotateBody : public CModel
{
public:
    CRotateBody(PRIORITY = PRIORITY_MAP);    // コンストラクタ
    ~CRotateBody();                                 // デストラクタ

    static CRotateBody *Create(const D3DXVECTOR3 &pos); // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos);               // 初期化処理
    void Update();                                      // 更新処理

private:
    void Rotate();          // 回転
    float m_fRotateNum;
};

#endif