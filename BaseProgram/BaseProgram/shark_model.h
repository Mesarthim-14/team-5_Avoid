#ifndef _SHARK_MODEL_H_
#define _SHARK_MODEL_H_
//=============================================================================
//
// サメモデルクラス [shark_model.h]
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
class CSharkModel : public CModel
{
public:
    CSharkModel(PRIORITY = PRIORITY_TEST_MODEL);    // コンストラクタ
    ~CSharkModel();                                 // デストラクタ

    static CSharkModel *Create(const D3DXVECTOR3 pos);  // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos);               // 初期化処理
    void Update();                                      // 更新処理
    void Draw();                                        // 描画

    void SetPos(const D3DXVECTOR3 &pos);
private:
};

#endif