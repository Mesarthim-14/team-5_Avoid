#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//=============================================================================
//
// メッシュフィールドクラス [meshfield.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "mesh_3d.h"

//=============================================================================
// メッシュフィールドクラス
//=============================================================================
class CMeshField : public CMesh3d
{
public:
	CMeshField(PRIORITY = PRIORITY_0);	// コンストラクタ
	~CMeshField();						// デストラクタ

	virtual HRESULT Init(void);			// 初期化処理
	virtual void Update(void);			// 更新処理
	virtual void Draw(void);			// 描画処理
	static CMeshField*Create(void);		// メッシュフィールド

protected:
	void SetInfo(const D3DXVECTOR3 &size, const INT_VERTEX_2D &PieceNum);			// 情報の設定

private:
	// private関数
	void CreateVerterx(void);										// 頂点の生成
	void InitAnimation(int nPatternNum, int nSpeed, int nLoop) {}	// アニメーション情報初期化
	void UpdateAnimation(void) {}									// アニメーション更新
};

#endif