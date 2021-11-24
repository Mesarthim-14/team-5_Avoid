#ifndef _PRODUCTION_CANNON_H_
#define _PRODUCTION_CANNON_H_
//=======================================================================================
//
// 大砲時の演出クラス [production_cannon.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "production.h"

//=======================================================================================
// クラス定義
//=======================================================================================
class CProductionCannon : public CProduction
{
public:
    CProductionCannon();    // コンストラクタ
    ~CProductionCannon();   // デストラクタ

    static CProductionCannon* Create(); // インスタンス生成
    void Init();                        // 初期化処理
    void Update();                      // 更新処理

private:
};
#endif