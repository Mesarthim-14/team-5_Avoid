#ifndef _CAMERA_H_
#define _CAMERA_H_
//=============================================================================
//
// カメラクラスヘッダー [camera.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// カメラクラス
//=============================================================================
class CCamera
{
public:
	CCamera();				// コンストラクタ
	virtual ~CCamera();		// デストラクタ

	HRESULT Init(void);									// 初期化処理
	virtual void Uninit(void);							// 終了処理
	virtual void Update(void);							// 更新処理
	virtual void SetCamera(void);						// カメラの描画設定
	void ShowInfo(void);								// imguiの設定
	virtual void NomalUpdate(void) = 0;					// 通常の更新処理
	virtual void MouseUpdate(void) = 0;					// マウスで視点変更の際の更新処理

	// Set関数
	void SetTarget(const bool Target)			{ m_bTarget = Target; }
	void SetDistance(const float fDistance)		{ m_fDistance = fDistance; }
	void SetVartical(const float fVartical)		{ m_fVartical = fVartical; }
	void SetHorizontal(const float fHorizontal)	{ m_fHorizontal = fHorizontal; }
	void SetposV(const D3DXVECTOR3 posV)		{ m_posV = posV; };
	void SetposR(const D3DXVECTOR3 posR)		{ m_posR = posR; };
	void Setrot(const D3DXVECTOR3 rot)			 { m_rot = rot; };
	// Get関数
	D3DXVECTOR3 &GetposV(void)		{ return m_posV; }				// カメラ座標
	D3DXVECTOR3 &GetposR(void)		{ return m_posR; }				// カメラ角度
	D3DXVECTOR3 &GetposU(void)		{ return m_posU; }				// 上方向ベクトル
	D3DXVECTOR3 &GetposVDest(void)	{ return m_posVDest; }			// 目的の座標
	D3DXVECTOR3 &GetposRDest(void)	{ return m_posRDest; }			// 目的の角度
	D3DXVECTOR3 &GetRot(void)		{ return m_rot; }				// 向き
	D3DXMATRIX GetMtxView(void)		{ return m_mtxView; }			// マトリクスビュー
	D3DXMATRIX GetMtxProj(void)		{ return m_mtxProjection; }		// プロジェクト
	bool GetTargetBool(void)		{ return m_bTarget; }			// ターゲットカメラのフラグ
	float GetVartical(void)			{ return m_fVartical; }			// 縦の回転
	float GetHorizontal(void)		{ return m_fHorizontal; }		// 横の回転
	float GetDistance(void)			{ return m_fDistance; }			// 距離

private:
	//=========================================================================
	// メンバ変数宣言
	//=========================================================================
	D3DXVECTOR3 m_posV;						// カメラの座標
	D3DXVECTOR3 m_posVDest;					// カメラの座標（目的地）
	D3DXVECTOR3 m_posVRot;					// カメラの座標（）
	D3DXVECTOR3 m_posR;						// 注視点
	D3DXVECTOR3 m_posRDest;					// 注視点（目的地）
	D3DXVECTOR3 m_posRRot;					// 注視点（）
	D3DXVECTOR3 m_posU;						// 上方向ベクトル
	D3DXMATRIX m_mtxProjection;				// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;					// ビューマトリックス
	D3DXVECTOR3 m_rot;						// 向き
	bool m_bTarget;							// ターゲット使用フラグ
	float m_fVartical;						// 縦回転角度
	float m_fHorizontal;					// 横回転角
	float m_fDistance;						// 視点～注視点の距離
	float m_fMove;							// 移動量
	bool m_bMouseCountrol;					// マウス視点コントロールを使うか
};
#endif 