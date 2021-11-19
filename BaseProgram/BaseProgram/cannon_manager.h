#ifndef _CANNON_MANAGER_H_
#define _CANNON_MANAGER_H_
//=============================================================================
//
// 大砲管理クラス [cannon_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "main.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CCannon;
class CKeyE;
class CProductionCannon;

//=========================================================================
// クラス定義
//=========================================================================
class CCannonManager
{
public:
    CCannonManager();   // コンストラクタ
    ~CCannonManager();  // デストラクタ

    static CCannonManager *Create();                        // インスタンス生成
    HRESULT Init();                                         // 初期化処理
    void Uninit();                                          // 終了処理
    void Update();                                          // 更新処理
    inline int GetAttackNum()const { return m_nAttackNum; } // チェックポイントの値

    // Get関数
    inline CCannon* GetCurrentCannon()const { return m_apCannon.at(m_nTargetCannon); }
private:
    // private関数
    void CreateCannon();        // 旗の生成
    void CreateUi();            // Ui生成
    void CannonCollision();     // それぞれの大砲の当たり判定
    void InputJudge();          // ボタンの判定
    void CreateBullet();        // 大砲の弾生成
    void SetProductionMode();   // 大砲の演出モードへ以降

    vector<CCannon*> m_apCannon;        // 大砲のポインタ
    int m_nAttackNum;                   // 攻撃した回数
    CKeyE *m_pKeyE;                     // EキーのUIポインタ
    int m_nTargetCannon;                // 対象となる大砲の番号
    CProductionCannon *m_pProduction;   // 演出のポインタ
};

#endif