#ifndef _CANNON_BULLETH_
#define _CANNON_BULLETH_
//=============================================================================
//
// 大砲の弾クラス [cannon_bullet.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CCollisionModelOBB;

//=========================================================================
// クラス定義
//=========================================================================
class CCannonBullet : public CModel
{
public:
    CCannonBullet(PRIORITY Priority);  // コンストラクタ
    ~CCannonBullet();                  // デストラクタ

    static CCannonBullet *Create(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot);   // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot);                   // 初期化処理
    void Update();                                                                              // 更新処理
private:
    // private関数
    void CalDistance();                                             // 距離計算
    void SetBulletInfo(D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);   // 弾の情報を設定
    void Collision();                                               // 当たり判定

    // メンバ変数
    float m_fDistanceToKraken;          // 距離
    D3DXVECTOR3 m_KrakenPos;            // クラーケンの座標
    CCollisionModelOBB* m_pCollision;   // 当たり判定
    bool m_bHit;                        // 当たったかのフラグ
};

#endif