#ifndef _STATE_KRAKEN_NORMAL_H_
#define _STATE_KRAKEN_NORMAL_H_
//=====================================================================
//
// クラーケン状態管理クラス [state_kraken_normal.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_kraken.h"

//=====================================================================
// 前方宣言
//=====================================================================
class CKraken;

//=====================================================================
// クラス定義
//=====================================================================
class CKrakenStateNormal : public CKrakenState
{
public:
    CKrakenStateNormal();                   // コンストラクタ
    ~CKrakenStateNormal();                  // デストラクタ
    static CKrakenStateNormal* Create();    // インスタンス生成

    void Init();            // 初期化処理
    void Update()override;  // 更新処理

private:
    // private関数
    void ShotBullet(CKraken* &pKraken); // 弾発射
    void ShotEnemy(CKraken* &pKraken);  // 敵発射

    // メンバ変数
    int m_nBulletCount;
};
#endif