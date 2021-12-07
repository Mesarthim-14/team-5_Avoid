#ifndef _CAUTION_WIMP_ATTACK_H_
#define _CAUTION_WIMP_ATTACK_H_
//=====================================================================
//
// 雑魚敵の攻撃警告 [caution_wimp_attack.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "billboard.h"

//=====================================================================
// クラス定義
//=====================================================================
class CCautionWimpAttack : public CBillboard
{
public:
    CCautionWimpAttack(PRIORITY priority);  // コンストラクタ
    ~CCautionWimpAttack();                  // デストラクタ

    static CCautionWimpAttack * Create(const D3DXVECTOR3& pos); // インスタンス生成
    HRESULT Init()override;                                     // 初期化処理
    void Uninit()override;                                      // 終了処理
    void Update()override;                                      // 更新処理
    void Draw()override;                                        // 描画処理

private:
    D3DXVECTOR3 FixPos(const D3DXVECTOR3& pos);  // 座標の修正
};


#endif