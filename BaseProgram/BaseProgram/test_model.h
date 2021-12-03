#ifndef _TEST_MODEL_H_
#define _TEST_MODEL_H_
//=============================================================================
//
// テストモデルクラス [test_model.h]
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
class CBlurFilter;
class CShaderSquare;
class CGaussFilter;

//=========================================================================
// クラス定義
//=========================================================================
class CTestModel : public CModel
{
public:

    CTestModel(PRIORITY = PRIORITY_TEST_MODEL); // コンストラクタ
    ~CTestModel();                              // デストラクタ

    static CTestModel *Create();    // インスタンス生成
    HRESULT Init();                 // 初期化処理
    void Uninit();                  // 初期化処理
    void Update();                  // 更新処理
    void Draw();                    // 描画
    void Hit();                     // 衝突判定
    void OBBs();                    // OBB衝突判定

private:
    CCollisionModelOBB* m_pCollisionModelOBB;   //当たり判定モデルのポインタ
    //2Dオブジェクト(表面化散乱(Subsurface Scattering) ページ参照)
    CShaderSquare* m_pSqu1Back;
    CGaussFilter* m_pGaussFilter;
};

#endif