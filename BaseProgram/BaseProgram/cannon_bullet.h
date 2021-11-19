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
// クラス定義
//=========================================================================
class CCannonBullet : public CModel
{
public:
    CCannonBullet(PRIORITY = PRIORITY_TEST_MODEL);  // コンストラクタ
    ~CCannonBullet();                               // デストラクタ

    static CCannonBullet *Create(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot);   // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot);                   // 初期化処理
    void Update();                                                                              // 更新処理
private:
    void CalDistance();                                             // 距離計算
    void SetBulletInfo(D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);   // 弾の情報を設定

    float m_fDistanceToKraken;  // 距離
    D3DXVECTOR3 m_KrakenPos;    // クラーケンの座標
};

#endif