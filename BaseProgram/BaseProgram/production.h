#ifndef _PRODUCTION_H_
#define _PRODUCTION_H_
//=======================================================================================
//
// 演出クラス [production.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "main.h"

//=======================================================================================
// 前方宣言
//=======================================================================================
class CState;
class CStateObject;

//=======================================================================================
// クラス定義
//=======================================================================================
class CProduction
{
public:
    CProduction();          // コンストラクタ
    virtual ~CProduction(); // デストラクタ

    virtual void Init(); // 初期化処理
    virtual void Uninit();  // 終了処理
    virtual void Update();  // 更新処理

    inline bool GetEnd()const { return m_bEnd; }    // 終了フラグ

protected:
    void CreateState(CStateObject* pObj, CState* pState);

    // 終了のカウントをするラムダ式
    function<int (const int)> TimeCounter = [&](const int nLimit)
    {
        m_nCounter++;

        if (m_nCounter >= nLimit)
        {// 時間経過したら
            m_bEnd = true;
        }
        return m_nCounter;
    };

private:
    int m_nCounter; // カウンタ
    bool m_bEnd;    // 終了フラグ
};
#endif