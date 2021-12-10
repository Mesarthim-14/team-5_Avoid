#ifndef _MAP_FACTORY_H_
#define _MAP_FACTORY_H_
//=======================================================================================
//
// マップの生成クラスクラス [map_factory.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// ゲームクラス
//=======================================================================================
class CMapFactory
{
public:
    CMapFactory();  // コンストラクタ
    ~CMapFactory(); // デストラクタ

    static CMapFactory *Create();   // インスタンス生成
    HRESULT Init();                     // 初期化処理
    void Uninit();                      // 終了処理
    void Update();                      // 更新処理

private:
};
#endif