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

//=========================================================================
// クラス定義
//=========================================================================
class CBullet : public CScene
{
public:
	CBullet(PRIORITY = PRIORITY_TEST_MODEL);	// コンストラクタ
	~CBullet();								// デストラクタ

	static CBullet *Create(void);	// インスタンス生成
	virtual HRESULT Init(void);					// 初期化処理
	virtual void Uninit(void);					// 初期化処理
	virtual void Update(void);					// 更新処理
	virtual void Draw(void);					// 描画

protected:
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_move;						// 移動量
	D3DXVECTOR3 m_rot;						// 現在の回転
	D3DXVECTOR3 m_size;						// サイズ
	int m_nLife;							// 生存時間
	float m_fSpeed;							// スピード
	int m_nDamage;							// ダメージ量

    CCollisionModelSphere* m_pCollisionModelSphere;   // 当たり判定モデルのポインタ
};

#endif