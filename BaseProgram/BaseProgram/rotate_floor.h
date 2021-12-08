#ifndef _ROTATE_FLOOR_H_
#define _ROTATE_FLOOR_H_
//=============================================================================
//
// 回転床クラス [rotate_floor.h]
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
class CCollisionModelCylinder;

//=========================================================================
// クラス定義
//=========================================================================
class CRotateFloor : public CModel
{
public:
    CRotateFloor(PRIORITY = PRIORITY_TEST_MODEL);   // コンストラクタ
    ~CRotateFloor() {}                              // デストラクタ

    static CRotateFloor *Create(const D3DXVECTOR3 &pos);    // インスタンス生成
    HRESULT Init(const D3DXVECTOR3 &pos);                   // 初期化処理
    void Update();                                          // 更新処理

    void HitCylinderAndSphere(); // 円柱と球体の当たり判定

private:
    CCollisionModelCylinder* m_pColModelCylinder;   // 当たり判定ポインタ(円柱)
};

#endif
