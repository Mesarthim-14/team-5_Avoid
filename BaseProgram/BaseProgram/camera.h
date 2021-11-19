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

    HRESULT Init();             // 初期化処理
    virtual void Uninit();      // 終了処理
    virtual void Update();      // 更新処理
    virtual void SetCamera();   // カメラの描画設定
    void ShowInfo();            // imguiの設定

    // Set関数
    inline void SetDistance(const float &fDistance)     { m_fDistance = fDistance; }
    inline void SetVartical(const float &fVartical)     { m_fVartical = fVartical; }
    inline void SetHorizontal(const float &fHorizontal) { m_fHorizontal = fHorizontal; }
    inline void SetposV(const D3DXVECTOR3 &posV)        { m_posV = posV; };
    inline void SetposR(const D3DXVECTOR3 &posR)        { m_posR = posR; };
    inline void Setrot(const D3DXVECTOR3 &rot)          { m_rot = rot; };

    // Get関数
    inline D3DXVECTOR3 &GetposV()       { return m_posV; }              // カメラ座標
    inline D3DXVECTOR3 &GetposR()       { return m_posR; }              // カメラ角度
    inline D3DXVECTOR3 &GetposU()       { return m_posU; }              // 上方向ベクトル
    inline D3DXVECTOR3 &GetposVDest()   { return m_posVDest; }          // 目的の座標
    inline D3DXVECTOR3 &GetposRDest()   { return m_posRDest; }          // 目的の角度
    inline D3DXVECTOR3 &GetRot()        { return m_rot; }               // 向き
    inline D3DXMATRIX GetMtxView()const { return m_mtxView; }           // マトリクスビュー
    inline D3DXMATRIX GetMtxProj()const { return m_mtxProjection; }     // プロジェクト
    inline float GetVartical()const     { return m_fVartical; }         // 縦の回転
    inline float GetHorizontal()const   { return m_fHorizontal; }       // 横の回転
    inline float GetDistance()const     { return m_fDistance; }         // 距離

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
	float m_fVartical;						// 縦回転角度
	float m_fHorizontal;					// 横回転角
	float m_fDistance;						// 視点～注視点の距離
	float m_fMove;							// 移動量
};
#endif 