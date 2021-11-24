#ifndef _PRODUCTION_CANNON_MANAGER_H_
#define _PRODUCTION_CANNON_MANAGER_H_
//=======================================================================================
//
// 演出クラス [.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "production.h"

//=======================================================================================
// 前方宣言
//=======================================================================================
class CProduction;

//=======================================================================================
// クラス定義
//=======================================================================================
class CProductionCannonManager
{
public:
    CProductionCannonManager();    // コンストラクタ
    ~CProductionCannonManager();   // デストラクタ

    static CProductionCannonManager* Create();      // インスタンス生成
    void Init();                                    // 初期化処理
    void Uninit();                                  // 終了処理
    void Update();                                  // 更新処理
    inline bool GetEnd()const { return m_bEnd; }    // 終了フラグ

private:
    void CreateProductionCannonShot();              // 演出の生成
    void CreateProductionAngry();                   // 演出の生成

    CProduction *m_pProduction; // 演出のポインタ
    bool m_bEnd;                // 終了フラグ
    int m_nStep;                // 演出のステップ

    typedef void(CProductionCannonManager::*SENTENCE_FUNC)();
    vector<SENTENCE_FUNC> m_CreateProduction =
    { &CProductionCannonManager::CreateProductionCannonShot ,
        &CProductionCannonManager::CreateProductionAngry };

};
#endif