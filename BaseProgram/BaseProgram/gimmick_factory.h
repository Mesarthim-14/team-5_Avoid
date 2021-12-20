#ifndef _GIMMICK_FACTORY_H_
#define _GIMMICK_FACTORY_H_
//=======================================================================================
//
// ゲームクラス [game.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// 前方宣言
//=======================================================================================
class CCheckPoint;
class CBarrelFactory;
class CHeel;
class CCannonManager;
class CMoveScaffold;

//=======================================================================================
// ゲームクラス
//=======================================================================================
class CGimmickFactory
{
public:
    CGimmickFactory();  // コンストラクタ
    ~CGimmickFactory(); // デストラクタ

    static CGimmickFactory *Create();   // インスタンス生成
    HRESULT Init();                     // 初期化処理
    void Uninit();                      // 終了処理
    void Update();                      // 更新処理

    // Get関数
    inline CCheckPoint *GetCheckPoint()const        { return m_pCheckPoint; }       // チェックポイント
    inline CCannonManager* GetCannonManager()const  { return m_pCannonManager; }    // 大砲管理クラス
    inline CMoveScaffold* GetMoveScaffold()const    { return m_pMoveScaffold; }     // 移動する床

private:
    // private関数
    void CreateCheckPoint();    // チェックポイントの設置
    void CreateGimmick();       // マップ生成
    void CreateEffect();        // エフェクト生成
    void CreateMoveScaffold();  // 動く床ギミック
    void CreateRotateGimmick(); // 回転ギミック
    void CreateSlope();         // 坂道
    void CreateCannon();        // 大砲
    void CreateBridge();        // 橋
    void CreateSwirl();         // 渦
    void CreateSwirlEffect();   // 渦の下のエフェクト


    // メンバ変数
    CCheckPoint *m_pCheckPoint;         // チェックポイントのフラグ
    CBarrelFactory *m_pBarrelFactory;   // 樽の生成
    CHeel *m_pHeel;                     // 回復クラス
    CCannonManager *m_pCannonManager;   // 大砲管理クラス
    CMoveScaffold* m_pMoveScaffold;       // 移動する床
};
#endif