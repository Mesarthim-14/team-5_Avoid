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
        LPD3DXMESH pMesh;                       // メッシュ情報へのポインタ
        LPD3DXBUFFER pBuffMat;                  // マテリアル情報へのポインタ
        DWORD dwNumMat;                         // マテリアル情報の数
        vector<LPDIRECT3DTEXTURE9> apTexture;   // テクスチャの数
    };
    
    //=============================================================================
    //　モデルファイル情報の構造体
    //=============================================================================
    struct MODELFILE
    {
    	string aFileName;       // ファイルネーム
    	D3DXVECTOR3 offsetPos;  // 位置のオフセット情報
    	D3DXVECTOR3 offsetRot;  // 向きのオフセット情報
    	int nParent;            // 親情報
    };
    
    //=============================================================================
    // Xファイルモデルの番号の列挙型
    //=============================================================================
    enum XFILE_NUM
    {
    
    	XFILE_NUM_NONE = -1,                // 初期値
    	XFILE_NUM_TEST_BLOCK,               // テストブロック
    	XFILE_NUM_MAP,                      // マップ
    	XFILE_NUM_CHECK_FLAG,               // チェックポイントのフラグ
    	XFILE_NUM_PLANE,                    // 平面
    	XFILE_NUM_SKY,                      // 空
    	XFILE_NUM_ENEMY_BOX,                // box
    	XFILE_NUM_MOVE_SCAFFOLD,            // 進む足場
    	XFILE_NUM_MOVE_RUBBLE1,             // 瓦礫
    	XFILE_NUM_MOVE_RUBBLE2,             // 瓦礫
    	XFILE_NUM_ROTATE_FLOOR,             // 回転床
    	XFILE_NUM_ROTATE_BODY,              // 回転本体
    	XFILE_NUM_CYLINDER,                 // 酒樽
    	XFILE_NUM_SLOPE,                    // 坂道
    	XFILE_NUM_RECOVER,                  // 回復ポイント
    	XFILE_NUM_CANNON,                   // 大砲
    	XFILE_NUM_BRIDGE,                   // 橋
    	XFILE_NUM_CANNON_BULLET,            // 大砲の弾
    	XFILE_NUM_SWIRL_SCAFFOLD,           // 渦の足場
        XFILE_NUM_SKY_BLUE,                 // 空
        XFILE_NUM_KRAKEN_BULLET,            // クラーケンの弾
        XFILE_NUM_MAP_FIRST_FLOOR,          // マップ
        XFILE_NUM_MAP_FIRST_FLOOR2,         // マップ
        XFILE_NUM_MAP_CHECK_FLOOR,          // マップ
        XFILE_NUM_MAP_CHECK_FLOOR2,         // マップ
        XFILE_NUM_MAP_SQUARE_FLOOR,         // マップ
        XFILE_NUM_MAP_SQUARE_FLOOR2,        // マップ
        XFILE_NUM_MAP_THIN_FLOOR,           // マップ
        XFILE_NUM_MAP_THIN_FLOOR2,          // マップ
        XFILE_NUM_ENEMY_SHARK,              // サメ
        XFILE_NUM_ENEMY_MARLIN,             // カジキ
        XFILE_NUM_ENEMY_GHOST,            // ゴースト
        XFILE_NUM_GIMMICK_BARREL,           // 酒樽
        XFILE_NUM_GIMMICK_BRIDGE,           // 橋
        XFILE_NUM_GIMMICK_SLOOP,            // 坂
        XFILE_NUM_GIMMICK_SPINFLOOR,        // 回る足場
        XFILE_NUM_GIMMICK_SPINSHIP_MAST,    // 上
        XFILE_NUM_GIMMICK_SPINSHIP_SHIP,    // 下
        XFILE_NUM_GIMMICK_PARTY_BASE,       // ベース
        XFILE_NUM_GIMMICK_PARTY_RUBBLE1,    // 瓦礫
        XFILE_NUM_GIMMICK_PARTY_RUBBLE2,    // 瓦礫
    	XFILE_NUM_MAX
    };
    
    //=============================================================================
    // 階層構造モデルの番号
    //=============================================================================
    enum HIERARCHY_XFILE_NUM
    {
        HIERARCHY_XFILE_NUM_NONE = -1,  // 初期値
        HIERARCHY_XFILE_NUM_TEST,       // プレイヤーモデル
        HIERARCHY_XFILE_NUM_MAX         // 最大数
    };
    
    CXfile();   // コンストラクタ
    ~CXfile();  // デストラクタ
    
    
    static CXfile *Create();    // インスタンス生成
    void LoadAll();             // 全てのロード
    void UnLoadAll();           // 全てのアンロード
    
    // Get関数
    inline MODEL GetXfile(const XFILE_NUM &Tex_Num)                                         { return m_aXfile[Tex_Num]; }					// モデルの情報
    inline MODELFILE GetModelFile(const int &nCount, const HIERARCHY_XFILE_NUM &FileNum)    { return m_apModelFile[FileNum].at(nCount); }	// モデルパーツの情報
    inline int GetModelParts(const HIERARCHY_XFILE_NUM &FileNum)                            { return m_nMaxParts[FileNum]; }				// モデルのパーツ数
    inline string GetModelFileName(const HIERARCHY_XFILE_NUM &FileNum)                      { return m_pFileName[FileNum]; }				// モデルファイルの名前
    inline vector<MODEL> GetHierarchyXfile(const HIERARCHY_XFILE_NUM &FileNum)              { return m_apHierarchyModel[FileNum]; }         // 階層構造モデル
    LPDIRECT3DTEXTURE9 *GetXfileTexture(const XFILE_NUM &TexNum);                                                                           // テクスチャの情報

private:
    // private関数
    HRESULT ModelLoad();            // モデルロード
    void ModelUnLoad();             // モデルアンロード
    HRESULT HierarchyReadFile();    // 階層構造のあるモデル読み込み
    HRESULT HierarchyModelLoad();   // 階層構造のモデルロード
    void HierarchyModelUnLoad();    // 階層構造のモデルアンロード
    void SetHierarchyFileName();    // ファイルの名前を設定

    // メンバ変数
    MODEL m_aXfile[XFILE_NUM_MAX];						// Xファイル情報の構造体
    vector<string> m_aXfileName;						// Xファイルの名前
    
    // 階層構造のモデル用
    vector<MODEL> m_apHierarchyModel[HIERARCHY_XFILE_NUM_MAX];  // 階層構造モデルのポインタ
    vector<MODELFILE> m_apModelFile[HIERARCHY_XFILE_NUM_MAX];   // 階層構造モデルのポインタ
    vector<string> m_aHierarchyXfileName;                       // 階層構造Xファイルの名前
    string m_pFileName[HIERARCHY_XFILE_NUM_MAX];                // ファイルの名前
    int m_nMaxParts[HIERARCHY_XFILE_NUM_MAX];                   // ファイルごとのパーツ数
};
#endif
