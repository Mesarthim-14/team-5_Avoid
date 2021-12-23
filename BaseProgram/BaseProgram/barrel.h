#ifndef _BARREL_H_
#define _BARREL_H_
//=============================================================================
//
// 樽クラス [barrel.h]
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
class CBarrel : public CModel
{
public:
    CBarrel(PRIORITY Priority);    // コンストラクタ
    ~CBarrel();                    // デストラクタ

    static CBarrel *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot); // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // 初期化処理
    void Update();                                                          // 更新処理
private:
    void Rotate();

    float m_fRotateNum;
};

#endif