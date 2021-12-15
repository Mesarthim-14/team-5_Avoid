#ifndef _SWIRL_SCAFFOLD_OBJECT_H_
#define _SWIRL_SCAFFOLD_OBJECT_H_
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
class CSwirlScaffoldObject : public CModel
{
public:
    CSwirlScaffoldObject(PRIORITY = PRIORITY_TEST_MODEL); // コンストラクタ
    ~CSwirlScaffoldObject();                              // デストラクタ

    static CSwirlScaffoldObject *Create(const D3DXVECTOR3 &pos);    // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos);                           // 初期化処理
    void Update();                                                  // 更新処理

private:
};

#endif