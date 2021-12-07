#ifndef _CAUTION_BOSS_BULLET_UI_H_
#define _CAUTION_BOSS_BULLET_UI_H_
//=====================================================================
//
// ボスの弾の警告UI [caution_boss_bullet_ui.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "scene2d.h"

//=====================================================================
// クラス定義
//=====================================================================
class CCautionBossBulletUi : public CScene2D
{
public:
    CCautionBossBulletUi(PRIORITY priority);  // コンストラクタ
    ~CCautionBossBulletUi();                  // デストラクタ

    static CCautionBossBulletUi * Create();     // インスタンス生成
    HRESULT Init()override;                     // 初期化処理
    void Uninit()override;                      // 終了処理
    void Update()override;                      // 更新処理
    void Draw()override;                        // 描画処理

    inline void SetBulletPos(const D3DXVECTOR3& pos) { m_BulletPos = pos; } // 弾の位置取得

private:
    // private関数
    void Rotate();                                              // 回転
    void CalDistance();                                         // 距離を測る
    void Blinking();                                            // 点滅
    void JudgeAngle(const float& fCamera, const float& fAngle); // 角度の計算

    bool m_bDraw;               // 描画フラグ
    float m_fAngle;             // 角度
    D3DXVECTOR3 m_BulletPos;    // 弾の位置
    bool m_bBlinking;           // 点滅フラグ
};


#endif