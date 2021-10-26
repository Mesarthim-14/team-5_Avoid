#ifndef _XFILE_H_
#define _XFILE_H_
//=============================================================================
//
// Xファイル管理ヘッダー [xfile.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
//クラス宣言
//=============================================================================
class CXfile
{
public:
	//=============================================================================
	//　モデル情報の構造体
	//=============================================================================
	struct MODEL
	{
		LPD3DXMESH pMesh;							// メッシュ情報へのポインタ
		LPD3DXBUFFER pBuffMat;						// マテリアル情報へのポインタ
		DWORD dwNumMat;								// マテリアル情報の数
		vector<LPDIRECT3DTEXTURE9> apTexture;		// テクスチャの数
	};

	//=============================================================================
	//　モデルファイル情報の構造体
	//=============================================================================
	struct MODELFILE
	{
		string aFileName;			// ファイルネーム
		D3DXVECTOR3 offsetPos;		// 位置のオフセット情報
		D3DXVECTOR3 offsetRot;		// 向きのオフセット情報
		int nParent;				// 親情報
	};

	//=============================================================================
	// Xファイルモデルの番号の列挙型
	//=============================================================================
	enum XFILE_NUM
	{
		XFILE_NUM_NONE = -1,	// 初期値
		XFILE_NUM_TEST_BLOCK,	// テストブロック
		XFILE_NUM_MAP,
		XFILE_NUM_MAX
	};

	//=============================================================================
	// 階層構造モデルの番号
	//=============================================================================
	enum HIERARCHY_XFILE_NUM
	{
		HIERARCHY_XFILE_NUM_NONE = -1,			// 初期値
		HIERARCHY_XFILE_NUM_TEST,				// プレイヤーモデル
		HIERARCHY_XFILE_NUM_MAX					// 最大数
	};

	CXfile();							// コンストラクタ
	~CXfile();							// デストラクタ

	static CXfile *Create(void);		// インスタンス生成
	void LoadAll(void);					// 全てのロード
	void UnLoadAll(void);				// 全てのアンロード

	// Get関数
	MODEL GetXfile(const XFILE_NUM Tex_Num)										{ return m_aXfile[Tex_Num]; }					// モデルの情報
	MODELFILE GetModelFile(const int nCount, const HIERARCHY_XFILE_NUM FileNum) { return m_apModelFile[FileNum].at(nCount); }	// モデルパーツの情報
	int GetModelParts(const HIERARCHY_XFILE_NUM FileNum)						{ return m_nMaxParts[FileNum]; }				// モデルのパーツ数
	string GetModelFileName(const HIERARCHY_XFILE_NUM FileNum)					{ return m_pFileName[FileNum]; }				// モデルファイルの名前
	vector<MODEL> GetHierarchyXfile(const HIERARCHY_XFILE_NUM FileNum)			{ return m_apHierarchyModel[FileNum]; }
	LPDIRECT3DTEXTURE9 *GetXfileTexture(const XFILE_NUM TexNum);

private:
	// private関数
	HRESULT ModelLoad(void);			// モデルロード
	void ModelUnLoad(void);				// モデルアンロード
	HRESULT HierarchyReadFile(void);	// 階層構造のあるモデル読み込み
	HRESULT HierarchyModelLoad(void);	// 階層構造のモデルロード
	void HierarchyModelUnLoad(void);	// 階層構造のモデルアンロード
	void SetHierarchyFileName(void);	// ファイルの名前を設定

	// メンバ変数
	MODEL m_aXfile[XFILE_NUM_MAX];						// Xファイル情報の構造体
	vector<string> m_aXfileName;						// Xファイルの名前

	// 階層構造のモデル用
	vector<MODEL> m_apHierarchyModel[HIERARCHY_XFILE_NUM_MAX];			// 階層構造モデルのポインタ
	vector<MODELFILE> m_apModelFile[HIERARCHY_XFILE_NUM_MAX];			// 階層構造モデルのポインタ
	vector<string> m_aHierarchyXfileName;								// 階層構造Xファイルの名前
	string m_pFileName[HIERARCHY_XFILE_NUM_MAX];						// ファイルの名前
	int m_nMaxParts[HIERARCHY_XFILE_NUM_MAX];							// ファイルごとのパーツ数
};
#endif
