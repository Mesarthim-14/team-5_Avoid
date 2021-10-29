#ifndef _SKINMESH_MODEL_H_
#define _SKINMESH_MODEL_H_
//=============================================================================
//
// スキンメッシュ用モデルクラス [skinmesh_model.h]
// Author : Takahashi Naoyuki
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"
#include "xfile.h"
#include "skinmesh.h"
#include "model_info.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CModelInfo;
class IHighLevelAnimController;

//=============================================================================
// モデルクラス
//=============================================================================
class CSkinmeshModel : public CScene
{
public:

	typedef enum
	{
		MODEL_PLAYER_100 = 0,//スライム１００％の状態
		MODEL_MAX
	}MODEL;//モデル名前
	CSkinmeshModel(PRIORITY Priority = PRIORITY_EFFECT);	// コンストラクタ
	~CSkinmeshModel();

	HRESULT Init(void);								// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理
	static CSkinmeshModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// インスタンス生成
	IHighLevelAnimController * GetHLcontroller(void) { return m_HLcontroller; };
	void SetModelNumber(MODEL model);
	void SetPos(D3DXVECTOR3 pos) { m_pModelInfo->SetPos(pos); }						// 現在の座標情報
	void SetRot(D3DXVECTOR3 rot){ m_pModelInfo->SetRot(rot); }						// 角度情報

protected:
	// Set関数
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }				// 移動量の設定
	void SetSize(D3DXVECTOR3 size) { m_size = size; }					// サイズの設定
	void SetTexPattern(int TexPattern) { m_nTexPattern = TexPattern; }	// テクスチャのパターン
	void SetLife(int nLife) { m_nLife = nLife; }						// ライフの設定
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }				// 拡大率

	// Get関数
	D3DXVECTOR3 &GetMove(void) { return m_move; }			// 移動量の情報
	D3DXVECTOR3 GetSize(void)const { return m_size; }		// サイズの設定
	int GetTexPattern(void) { return m_nTexPattern; }		// テクスチャ
	int GetLife(void) { return m_nLife; }					// ライフの設定
	CModelInfo* GetModelInfo(void) { return m_pModelInfo; }	// モデルの情報

private:
	// private関数
	void HasPtrDelete(void);	// 保持ポインタの開放処理
	void CreateInfoPtr(void);	// 情報のポインタ生成

	// メンバ変数
	CModelInfo* m_pModelInfo;									// モデルの情報
	D3DXVECTOR3 m_move;											// 移動量
	D3DXVECTOR3 m_size;											// サイズ
	D3DXVECTOR3 m_scale;										// 拡大率
	int m_nTexPattern;											// テクスチャのパターン数
	int m_nLife;												// ライフ
	ID3DXAnimationController * m_pAnimetionController;			//アニメーションコントローラー
	SkinMesh::SMD3DXFRAME				 * m_pRootFrame;		// ルートフレーム
	std::vector<SkinMesh::SMD3DXMESHCONTAINER*> m_cont;			// SMD3DXMESHCONTAINER(メッシュ)関連の情報を保存用
	std::vector<D3DXBONECOMBINATION*> m_combs;					//ボーンコンビネーションテーブルのポインタ取得
	IHighLevelAnimController * m_HLcontroller;					//ハイレベルアニメーションコントローラー
	static const char* m_aParam[MODEL_MAX];						//モデルパス名
	MODEL			   m_ModelNum;								// モデルの名前
};
#endif 