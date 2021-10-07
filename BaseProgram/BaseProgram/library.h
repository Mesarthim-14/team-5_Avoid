#ifndef _LIBRARY_H_
#define _LIBRARY_H_
//=============================================================================
//
// ライブラリ処理 [library.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 当たり判定クラス
//=============================================================================
class CLibrary
{
public:
	static string split(string str, char del, int nNum);											// 文字列を分割し、取り出す関数
	static void ConfigMatrix(D3DXMATRIX *pMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot);	// マトリクスの設定
	static void RotFix(float &fRot);																// 角度の修正
	static int Random(int nNum);																	// ランダム変数
	static int Random(int nMin, int nMax);															// ランダム変数
	static float Random(float fNum);																// ランダム変数
	static float Random(float fMin, float fMax);													// ランダム変数

private:
};

#endif