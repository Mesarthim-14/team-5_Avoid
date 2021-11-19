#ifndef _SWIRL_SCAFFOLD_H_
#define _SWIRL_SCAFFOLD_H_
//=============================================================================
//
// 渦の足場クラス [swirl_scaffold.h]
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
class CSwirlScaffold : public CModel
{
public:
    CSwirlScaffold(PRIORITY = PRIORITY_TEST_MODEL); // コンストラクタ
    ~CSwirlScaffold();                              // デストラクタ

    static CSwirlScaffold *Create(const D3DXVECTOR3 &pos);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos);                   // 初期化処理
    void Update();                                          // 更新処理

private:
    void Rotate();  // 回転
    float m_fRotateNum;
};

#endif