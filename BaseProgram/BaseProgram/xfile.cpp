//=============================================================================
//
// Xファイルの管理クラス [xfile.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "xfile.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CXfile::CXfile()
{
    memset(m_aXfile, 0, sizeof(m_aXfile));
    memset(m_pFileName, 0, sizeof(m_pFileName));
    memset(m_nMaxParts, 0, sizeof(m_nMaxParts));

    // 階層構造モデル初期化
    for (int nCount = 0; nCount < HIERARCHY_XFILE_NUM_MAX; nCount++)
    {
        m_apHierarchyModel[nCount].clear();
    }

    // モデルファイル初期化
    for (int nCount = 0; nCount < HIERARCHY_XFILE_NUM_MAX; nCount++)
    {
        // 初期化処理
        m_apModelFile[nCount].clear();
    }

    // Xファイルネームを取得
    m_aXfileName =
    {
        { "data/Model/Normal/block.x" },                        // テストブロック
        { "data/Model/Normal/mapmapmap3.x" },                   // マップ
        { "data/Model/Normal/Map/checkpoint.x" },                    // チェックポイント
        { "data/Model/Normal/plane.x" },                        // 平面
        { "data/Model/Normal/sky.x" },                          // 空
        { "data/Model/Normal/enemy_box.x" },                    // 仮エネミー
        { "data/Model/Normal/susumuashiba.x" },                 // 進む足場
        { "data/Model/Normal/Rubble1.x" },                      // 瓦礫
        { "data/Model/Normal/Rubble2.x" },                      // 瓦礫
        { "data/Model/Normal/kaitenyuka_shita.x" },             // 回転床
        { "data/Model/Normal/kaitenyuka_ue.x" },                // 回転床
        { "data/Model/Normal/Cylinder.x" },                     // 酒樽
        { "data/Model/Normal/Slope.x" },                        // 坂道
        { "data/Model/Normal/HeelPoint.x" },                    // 回復ポイント
        { "data/Model/Normal/Cannon.x" },                       // 大砲
        { "data/Model/Normal/hashiwatashi.x" },                 // 橋
        { "data/Model/Normal/CannonBullet.x" },                 // 大砲の弾
        { "data/Model/Normal/ugokuashiba.x" },                  // 渦の足場
        { "data/Model/Normal/sky_blue5.x" },                    // お空
        { "data/Model/Normal/Kraken_Bullet.x" },                // クラーケンの弾
        { "data/Model/Normal/Map/06_floor_thin.x" },            // マップ長方形
        { "data/Model/Normal/Map/01_floor_big_2f.x" },          // マップ最初の床
        { "data/Model/Normal/Map/02_floor_checkpoint.x" },      // マップ最初の床
        { "data/Model/Normal/Map/03_floor_checkpoint_2f.x" },   // マップ最初の床
        { "data/Model/Normal/Map/04_floor_sq.x" },              // マップ正方形
        { "data/Model/Normal/Map/05_floor_sq_2f.x" },           // マップ正方形
        { "data/Model/Normal/Map/00_floor_big.x" },             // マップ最初の床
        { "data/Model/Normal/Map/07_floor_thin_2f.x" },         // マップ長方形
    };
    
    // 階層構造モデル
    m_aHierarchyXfileName =
    {
        { "data/Text/Test/motion_test.txt"},        // プレイヤー
    };
}

//=============================================================================
// デストラクタ
//=============================================================================
CXfile::~CXfile()
{
    m_aXfileName.clear();
    m_aHierarchyXfileName.clear();
}

//=============================================================================
// インスタンス生成
//=============================================================================
CXfile * CXfile::Create()
{
    // メモリ確保
    CXfile *pXfile = new CXfile;
    if (pXfile)
    {
    return pXfile;
    }

    return nullptr;
}

//=============================================================================
// Xファイルロード
//=============================================================================
HRESULT CXfile::ModelLoad()
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    size_t size = m_aXfileName.size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        // Xファイルの読み込み
        D3DXLoadMeshFromX(m_aXfileName.at(nCount).data(),
            D3DXMESH_SYSTEMMEM,
            pDevice,
            nullptr,
            &m_aXfile[nCount].pBuffMat,
            nullptr,
            &m_aXfile[nCount].dwNumMat,
            &m_aXfile[nCount].pMesh);
    }
    
    for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
    {
        //マテリアル情報の解析
        D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[nCount].pBuffMat->GetBufferPointer();

        for (int nCntMat = 0; nCntMat < (int)m_aXfile[nCount].dwNumMat; nCntMat++)
        {
            LPDIRECT3DTEXTURE9 pTexture = nullptr;
            
            // ファイルネームの取得
            char cData[256] = {};
            sprintf(cData, "data/Texture/%s", materials[nCntMat].pTextureFilename);
            
            // テクスチャの読み込み
            D3DXCreateTextureFromFile(pDevice, cData, &pTexture);
            
            // テクスチャ情報取得
            m_aXfile[nCount].apTexture.push_back(pTexture);
        }
    }

    return S_OK;
}

//=============================================================================
// Xファイルアンロード
//=============================================================================
void CXfile::ModelUnLoad()
{
    for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
    {
        //メッシュの破棄
        if (m_aXfile[nCount].pMesh)
        {
            m_aXfile[nCount].pMesh->Release();
            m_aXfile[nCount].pMesh = nullptr;
        }
        //マテリアルの破棄
        if (m_aXfile[nCount].pBuffMat)
        {
            m_aXfile[nCount].pBuffMat->Release();
            m_aXfile[nCount].pBuffMat = nullptr;
        }
        
        // テクスチャの破棄
        size_t size = m_aXfile[nCount].apTexture.size();
        for (size_t nCntTexture = 0; nCntTexture < size; nCntTexture++)
        {
            if (m_aXfile[nCount].apTexture.at(nCntTexture))
            {
                m_aXfile[nCount].apTexture.at(nCntTexture)->Release();
                m_aXfile[nCount].apTexture.at(nCntTexture) = nullptr;
            }
        }
        
        // テクスチャの配列クリア
        m_aXfile[nCount].apTexture.clear();
    }
}

//=============================================================================
// 階層構造のモデルファイル読み込み
//=============================================================================
HRESULT CXfile::HierarchyReadFile()
{
    FILE *pFile = nullptr;        //FILEポインタ
    
    // ファイルの名前を設定
    SetHierarchyFileName();
    
    for (int nModelCnt = 0; nModelCnt < HIERARCHY_XFILE_NUM_MAX; nModelCnt++)
    {
        // ファイルオープン
        pFile = fopen(m_pFileName[nModelCnt].c_str(), "r");
        
        string aHeadData;
        string aModeName;
        
        int nModelIndex = 0;    // モデルのインデックス
        int nMotionType = 0;    // モーションのタイプ
        int nKeyNum = 0;        // キー番号
        int nMotionNum = 0;        // モーション番号
        
        if (pFile)
        {
            do
            {
                // 文字列をクリアする
                aHeadData.clear();
                
                //一列読み込んでモード情報を抽出
                getline((ifstream)pFile, aHeadData);
                
                aModeName = aHeadData;
                
                if (aHeadData.find("MODEL_FILENAME") != string::npos)
                {
                    // モデルファイルの構造体
                    MODELFILE aModelFile = {};
                
                    aModelFile.aFileName = CLibrary::split(aHeadData, ' ', 2);
                
                    if (aModelFile.aFileName.c_str() != NULL)
                    {
                        // ファイル情報確保
                        m_apModelFile[nModelCnt].push_back(aModelFile);
                
                        //インデックスを１つ進める
                        nModelIndex++;
                    }
                }
                
                if (aModeName.compare(string("CHARACTERSET")) == 0)
                {
                    //インデックスを最初に戻す
                    nModelIndex = 0;
                    
                    //END_MOTIONSETを読み込むまで繰り返す
                    while (aModeName.compare(string("END_CHARACTERSET")) != 0)
                    {
                        //一列読み込んでモード情報を抽出
                        getline((ifstream)pFile, aHeadData);
                    
                        // 文字の分解
                        aModeName = CLibrary::split(aHeadData, ' ', 0);
                    
                        if (aModeName.compare(string("PARTSSET")) == 0)
                        {
                            //END_PARTSSETを読み込むまで繰り返す
                            while (aModeName.compare(string("END_PARTSSET")) != 0)
                            {
                                //一列読み込んでモード情報を抽出
                                getline((ifstream)pFile, aHeadData);
                                aModeName = CLibrary::split(aHeadData, ' ', 0);
                    
                                if (aModeName.find(string("PARENT")) == 0)
                                {
                                    //親子情報の設定
                                    sscanf(aHeadData.c_str(), "%*s %*s %d", &m_apModelFile[nModelCnt].at(nModelIndex).nParent);
                    
                                }
                                //if (strcmp(aModeName, "POS") == 0)
                                if (aModeName.find(string("POS")) == 0)
                                {
                                    //位置の設定
                                    sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.x,
                                        &m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.y, &m_apModelFile[nModelCnt].at(nModelIndex).offsetPos.z);
                                }
                                //if (strcmp(aModeName, "ROT") == 0)
                                if (aModeName.find(string("ROT")) == 0)
                                {
                                    //向きの設定
                                    sscanf(aHeadData.c_str(), "%*s %*s %f %f %f", &m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.x,
                                        &m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.y, &m_apModelFile[nModelCnt].at(nModelIndex).offsetRot.z);
                                }
                            }
                    
                            //インデックスを１つ進める
                            nModelIndex++;
                    
                            // パーツ数を数える
                            m_nMaxParts[nModelCnt]++;
                    
                        }
                    }
                }
            
            } while (aModeName.find("END_SCRIPT") == string::npos);
            
            // ファイルクローズ
            ::fclose(pFile);
        }
        else
        {
            // 失敗した場合メッセージボックスを表示
            MessageBox(nullptr, "ヒエラルキーファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);
        
            return    E_FAIL;
        }
    }
    
    return S_OK;
}

//=============================================================================
// 階層構造のモデルロード
//=============================================================================

HRESULT CXfile::HierarchyModelLoad()
{
    //デバイス情報の取得

    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
    {
        for (int nCount = 0; nCount < m_nMaxParts[nXFileNumCnt]; nCount++)
        {
            MODEL Hierarchy = { nullptr, nullptr, 0, {} };

            //モデルの読み込み
            D3DXLoadMeshFromX(m_apModelFile[nXFileNumCnt].at(nCount).aFileName.c_str(),
                D3DXMESH_SYSTEMMEM,
                pDevice,
                nullptr,
                &Hierarchy.pBuffMat,
                nullptr,
                &Hierarchy.dwNumMat,
                &Hierarchy.pMesh);

            //マテリアル情報の解析
            D3DXMATERIAL *materials = (D3DXMATERIAL*)Hierarchy.pBuffMat->GetBufferPointer();

            for (int nCntMat = 0; nCntMat < (int)Hierarchy.dwNumMat; nCntMat++)
            {
                LPDIRECT3DTEXTURE9 pTexture = nullptr;

                if (materials[nCntMat].pTextureFilename)
                {
                    // ファイルネームの取得
                    char cData[256] = {};
                    sprintf(cData, "data/Texture/%s", materials[nCntMat].pTextureFilename);

                    // テクスチャの読み込み
                    D3DXCreateTextureFromFile(pDevice, cData, &pTexture);
                }

                // テクスチャ情報を取得
                Hierarchy.apTexture.push_back(pTexture);
            }

            // モデル情報を取得
            m_apHierarchyModel[nXFileNumCnt].push_back(Hierarchy);
        }
    }

    return S_OK;
}

//=============================================================================
// 階層構造のアンモデルロード
//=============================================================================

void CXfile::HierarchyModelUnLoad()
{
    for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
    {
        size_t size = m_apHierarchyModel[nXFileNumCnt].size();
        for (size_t nCount = 0; nCount < size; nCount++)
        {
            //マテリアル情報の破棄
            if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat)
            {
                m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat->Release();
                m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat = nullptr;
            }

            //メッシュ情報の破棄
            if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh)
            {
                m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh->Release();
                m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh = nullptr;
            }

            // テクスチャの開放
            for (size_t nCntTexture = 0; nCntTexture < m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.size(); nCntTexture++)
            {
                if (m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture))
                {
                    m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture)->Release();
                    m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.at(nCntTexture) = nullptr;
                }
            }

            // テクスチャの配列クリア
            m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture.clear();
        }

        // 階層構造の配列クリア
        m_apHierarchyModel[nXFileNumCnt].clear();
    }
}

//=============================================================================
// ファイルの名前を設定
//=============================================================================

void CXfile::SetHierarchyFileName()
{
    size_t size = m_aHierarchyXfileName.size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        // 名前を入れる
        m_pFileName[nCount] = m_aHierarchyXfileName.at(nCount);
    }
}

//=============================================================================
// 全てのロード
//=============================================================================

void CXfile::LoadAll()
{
    // モデルロード
    ModelLoad();

    // 階層構造のファイル読み込み
    HierarchyReadFile();

    // 階層構造のモデル読み込み
    HierarchyModelLoad();
}

//=============================================================================
// 全てのアンロード
//=============================================================================

void CXfile::UnLoadAll()
{
    ModelUnLoad();
    HierarchyModelUnLoad();
}

//=============================================================================
// モデルに使用するテクスチャ情報
//=============================================================================

LPDIRECT3DTEXTURE9 *CXfile::GetXfileTexture(const XFILE_NUM &TexNum)
{
    if (TexNum < XFILE_NUM_MAX)
    {
        if (m_aXfile[TexNum].apTexture.data())
        {
            return m_aXfile[TexNum].apTexture.data();
        }
    }

    return nullptr;
}