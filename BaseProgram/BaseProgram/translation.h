#ifndef _TRANSLATION_H_
#define _TRANSLATION_H_
//=====================================================================
//
// 操作説明表示処理[gauge.h]
// Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "scene2d.h"

//=====================================================================
// クラス定義
//=====================================================================
class CTranslation : public CScene2D
{
public:
    CTranslation(PRIORITY priority);
    ~CTranslation();

    static CTranslation * Create();
    HRESULT Init();
    void Uninit();
    void Update();
    void Draw();

private:
};


#endif // !_GAUGE_H_
