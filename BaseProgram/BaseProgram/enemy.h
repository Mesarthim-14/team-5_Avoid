#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// 敵クラスヘッダー [enemy.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"

//=============================================================================
// クラス定義
//=============================================================================
class CEnemy : public CCharacter
{
public:
    CEnemy(PRIORITY Priority = PRIORITY_CHARACTER); // コンストラクタ
    virtual ~CEnemy();                              // デストラクタ

    virtual HRESULT Init(); // 初期化処理
    virtual void Update();  // 更新処理

protected:
    void SetAttackInfo(const int &nInter, 
        const int &nSTR, const float &fPower);  // 攻撃の情報設定
private:
    // private関数
    virtual void Move();            // 移動処理
    virtual void UpdateState();     // キャラクター状態
    virtual void CreateModel() = 0; // モデル生成関数
    virtual void Attack() = 0;      // 攻撃

    int m_nAttackInter; // 攻撃の間隔
    int m_nAttackCount; // 攻撃のカウンター
    int m_nSTR;         // 攻撃力
    float m_fPower;     // 吹っ飛ばす力
};
#endif