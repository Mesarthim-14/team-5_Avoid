#ifndef _MAP_H_
#define _MAP_H_
//=============================================================================
//
// マップ親クラス [map.h]
// Author : Suzuki Mahiro
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
class CCollisionModelCylinder;
class CCollisionModelPolygon;

//=========================================================================
// クラス定義
//=========================================================================
class CMap : public CModel
{
public:
    CMap(PRIORITY Priority); // コンストラクタ
    ~CMap();                 // デストラクタ

    HRESULT Init();         // 初期化処理
    void Uninit()override;  // 初期化処理
    void Update()override;  // 更新処理
    void Draw()override;    // 描画

    // 当たり判定
    void HitColOBBsPlayer(const CCollisionModelOBB* const* pMapColOBB);             // プレイヤーとの当たり判定関数(直方体同士)
    void HitColOBBsPlayer(const CCollisionModelOBB* const &pMapColOBB);             // プレイヤーとの当たり判定関数(直方体同士)
    void HitColPolygonPlayer(const CCollisionModelPolygon* const &pMapColPolygon);     // プレイヤーとの当たり判定関数(直方体同士)
    void HitColPolygonOnPlayer(const CCollisionModelPolygon* const &pMapColPolygon);  // プレイヤーとの当たり判定関数(直方体同士)
    void HitColOBBsBossBullet(const CCollisionModelOBB* const pMapColOBB);          // ボスバレットとの当たり判定関数(直方体同士)
    void HitColPlayer(const CCollisionModelCylinder* const pMapColCylinder);        // プレイヤーとの当たり判定関数(球体と円柱)
    void HitColBossBullet(const CCollisionModelCylinder* const pMapColCylinder);    // ボスバレットとの当たり判定関数(球体と円柱)

protected:
    void SetHitMap(const bool bHitMap) { m_bHitMap = bHitMap; } // １つ以上マップに当たっているかの判定の設定
    bool GetHitMap()const { return m_bHitMap; }                 // １つ以上マップに当たっているかの判定の取得

private:
    virtual void Col() = 0;

    static bool m_bHitMap; // １つ以上マップに当たっているかの判定
};

#endif