#ifndef _CHECK_POINT_H_
#define _CHECK_POINT_H_
//=============================================================================
//
// クラス [check_point.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "main.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CCheckFlag;

//=========================================================================
// クラス定義
//=========================================================================
class CCheckPoint
{
public:
	CCheckPoint();		// コンストラクタ
	~CCheckPoint();		// デストラクタ

	static CCheckPoint *Create();							// インスタンス生成
	HRESULT Init();											// 初期化処理
	void Uninit();											// 終了処理
	void Update();											// 更新処理
	D3DXVECTOR3 GetPointPos()		{ return m_PointPos; }	// チェックポイントの座標
	inline int GetPointNum()const	{ return m_nPointNum; }	// チェックポイントの値
private:
	// private関数
	void CreateFlag();					// 旗の生成

	D3DXVECTOR3 m_PointPos;				// 座標の取得
	vector<CCheckFlag*> m_apChackFlag;	// 旗のポインタ
	int m_nPointNum;					// 現在の番号
};

#endif