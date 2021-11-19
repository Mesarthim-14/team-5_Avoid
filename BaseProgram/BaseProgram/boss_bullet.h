#ifndef _BOSS_BULLET_H_
#define _BOSS_BULLET_H_
//=============================================================================
//
// ボスの弾クラス [boss_bullet.h]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"
#include "bullet.h"
//=========================================================================
// クラス定義
//=========================================================================
class CBossBullet : public CBullet
{
public:
	CBossBullet(PRIORITY = PRIORITY_TEST_MODEL);	// コンストラクタ
	~CBossBullet();								// デストラクタ

	static CBossBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);	// インスタンス生成
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 初期化処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画
	void Hit(void);						// 衝突判定

private:
	void Move();
	// メンバ変数
	CModel * m_pModel;					// モデルポインタ
};

#endif