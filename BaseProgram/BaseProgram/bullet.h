#ifndef _BULLET_H_
#define _BULLET_H_
//=============================================================================
//
// 弾クラス [boss_bullet.h]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CCollisionModelSphere;
class CCollisionModelOBB;

//=========================================================================
// クラス定義
//=========================================================================
class CBullet : public CScene
{
public:
	CBullet(PRIORITY Priority);    // コンストラクタ
	~CBullet();                    // デストラクタ

	virtual HRESULT Init();     // 初期化処理
	virtual void Uninit();      // 終了処理
	virtual void Update();      // 更新処理
	virtual void Draw();        // 描画

    void Hit();						// 衝突判定
    
    // Set関数
    inline void SetPos(const D3DXVECTOR3 &pos)          { m_pos = pos; }            // 座標設定
    inline void SetMove(const D3DXVECTOR3 &move)        { m_move = move; }          // 移動量設定
    inline void SetRot(const D3DXVECTOR3 &rot)          { m_rot = rot; }            // 角度設定
    inline void SetColRadius(const float &radius)       { m_ColRadius = radius; }   // 当たり判定の半径設定
    inline void SetColSizeOBB(const D3DXVECTOR3 &size)  { m_colSizeOBB = size; }    // 当たり判定サイズ(OBB)設定
    inline void SetLife(const int &nLife)               { m_nLife = nLife; }        // 体力設定

    // Get関数
    inline D3DXVECTOR3 GetPos()const    { return m_pos; }       // 座標情報
    inline D3DXVECTOR3 GetMove()const   { return m_move; }      // 移動量情報
    inline D3DXVECTOR3 GetRot()const    { return m_rot; }       // 角度情報
    inline float GetColRadius()const    { return m_ColRadius; } // 当たり判定の半径情報
    inline int GetLife()const           { return m_nLife; }     // 体力情報
    inline CCollisionModelSphere* GetColSpherePtr()const { return m_pCollisionModelSphere; }    // 当たり判定モデルのポインタ(カプセル)
    inline CCollisionModelOBB* GetColOBBPtr()const { return m_pColModelOBB; }                   // 当たり判定モデルのポインタ(カプセル)

private:
	D3DXVECTOR3 m_pos;          // 座標
	D3DXVECTOR3 m_move;         // 移動量
	D3DXVECTOR3 m_rot;          // 現在の回転
	float m_ColRadius;          // 当たり判定の半径(球体)
    D3DXVECTOR3 m_colSizeOBB;   // 当たり判定サイズ(OBB)
	int m_nLife;                // 生存時間
	float m_fSpeed;             // スピード
	int m_nDamage;              // ダメージ量

    CCollisionModelSphere* m_pCollisionModelSphere;   // 当たり判定モデル(球体)のポインタ
    CCollisionModelOBB* m_pColModelOBB;               // 当たり判定モデル(OBB)のポインタ
};

#endif