#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//=====================================================
//
// ビルボードクラスヘッダー [billboard.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "scene3D.h"

//=====================================================
// ビルボードクラス
//=====================================================
class CBillboard : public CScene3D
{
public:
    explicit CBillboard(PRIORITY Priority = PRIORITY_EFFECT);   // コンストラクタ
    virtual ~CBillboard() {}                                    // デストラクタ
    virtual void Draw();                                        // 描画処理


private:
    bool m_bBlend;                // 加算合成
};

#endif