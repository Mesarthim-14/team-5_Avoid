//=============================================================================
//
// 水クラス [test_model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "water_fresnel.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "wave.h"
#include "shader_square.h"
#include "parallax_mapping2.h"
#include "camera.h"
#include "light.h"
#include "library.h"
#include "blur_filter.h"
#include "fresnel_lambert.h"
#include "mask.h"
#include "reflect.h"
#include "player.h"
#include "modelanime.h"
#include "skinmesh_model.h"
#include "reflect.h"
#include "kraken.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define WATER_POS               (ZeroVector3)
#define WATER_ROT               (ZeroVector3)

// 波の設定
// マテリアルを設定する
#define HEIGHT                  (0.2f)          // 波の高さ     
#define ADD_WAVE_TEX_POS        (0.0f, 1.0f)    // 波の出現座標
#define Z_DISTANCE              (2286.0f)       // 最遠近距離

// Reflect
#define REFLECT_HEIGHT          (300.0f)                                 // 反射の高さ
#define REFLECT_PLAYER_AMBIENT  (0.1f)                                  // 反射の色
#define REFLECT_SKY_AMBIENT     (D3DXVECTOR4(0.3f, 0.0f, 1.0f, 1.0f))   // 反射の色

// Wave 
#define WAVE_SPEED              (0.2f)                                  // 波の速度

// Lambert
#define LAMBERT_PLAYER_AMBIENT  (0.1f)                                  // 反射光の色
#define LAMBERT_SKY_AMBIENT     (D3DXVECTOR4(0.5f, 0.0f, 1.0f, 1.0f))   // 反射光の色

// Parallax
#define PARALLAX_AMBIENT        (D3DXVECTOR4(1.0f, 1.0f, 0.6f, 0.1f))
#define PARALLAX_SPECULAR       (0.8f)              // 広さ
#define PARALLAX_SPECULARPOWER  (0.2f)              // 強さ
#define PARALLAX_HEIGHT         (0.5f)              // 高さ
#define PARALLAX_REFRACTION     (256.2f)            // 適応度

//=============================================================================
// コンストラクタ
//=============================================================================
CWaterFresnel::CWaterFresnel(PRIORITY Priority) : CModel(Priority)
{
    m_pWave = nullptr;
    m_pParallax = nullptr;
    m_WaterMesh = nullptr;
    m_pBlurFilter = nullptr;
    m_pLambert = nullptr;
    m_pSquObj = nullptr;
    m_pMask = nullptr;
    m_pReflect = nullptr;
    m_pColorTexture = nullptr;
    m_pColorSurface = nullptr;
    m_pReflectTexture = nullptr;
    m_pReflectSurface = nullptr;
    m_pWaterTexture = nullptr;
    m_pWaterSurface = nullptr;
    m_pBlurFilterTexture = nullptr;
    m_pBlurFilterSurface = nullptr;

    m_fWaveSpeed = WAVE_SPEED;
    m_ReflectPlayerAmbiend = { REFLECT_PLAYER_AMBIENT, REFLECT_PLAYER_AMBIENT, REFLECT_PLAYER_AMBIENT, 1.0f };
    m_ReflectSkyAmbiend = REFLECT_SKY_AMBIENT;
    m_fReflectHeight = REFLECT_HEIGHT;
    m_LambertPlayerAmbiend = { LAMBERT_PLAYER_AMBIENT, LAMBERT_PLAYER_AMBIENT, LAMBERT_PLAYER_AMBIENT, 1.0f };
    m_LambertSkyAmbiend = LAMBERT_SKY_AMBIENT;
    m_ParallaxAmbiend = PARALLAX_AMBIENT;
    m_fParallaxSpecular = PARALLAX_SPECULAR;            // 広さ
    m_fParallaxSpecularPower = PARALLAX_SPECULARPOWER;  // 強さ
    m_fParallaxHeight = PARALLAX_HEIGHT;                // 高さ
    m_fParallaxRefraction = PARALLAX_REFRACTION;        // 適応度
    m_fZdistance = Z_DISTANCE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CWaterFresnel::~CWaterFresnel()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CWaterFresnel * CWaterFresnel::Create()
{
    // メモリ確保
    CWaterFresnel *pWater = new CWaterFresnel(PRIORITY_0);

    // nullcheck
    if (pWater)
    {
        // 初期化処理
        pWater->Init();
        return pWater;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWaterFresnel::Init()
{
    // 初期化処理
    CModel::Init();
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
    CXfile *pXfile = GET_XFILE_PTR;
    //BindModel(pXfile->GetXfile(CXfile::XFILE_NUM_TEST_BLOCK));
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_PLANE);
    GetModelInfo()->SetModelStatus(WATER_POS, WATER_ROT, model);

    // 波
    if (!m_pWave)
    {
        //波マップのサイズ
        D3DXVECTOR2 WaveMapSize = D3DXVECTOR2(512.0f, 512.0f);    // 512
        m_pWave = new CWave(pDevice, (UINT)WaveMapSize.x, (UINT)WaveMapSize.y);
        m_pWave->Load();
    }
    // 反射光
    if (!m_pLambert)
    {
        m_pLambert = new CFrenelLambert(pDevice);
        m_pLambert->Load();
    }
    // 反射
    if (!m_pReflect)
    {
        m_pReflect = new CReflect(pDevice);
        m_pReflect->Load();
    }
    // ブラー
    if (!m_pBlurFilter)
    {
        m_pBlurFilter = new CBlurFilter(pDevice, (UINT)(SCREEN_WIDTH), (UINT)(SCREEN_HEIGHT));
        m_pBlurFilter->Load();
    }
    // 水面マスク
    if (!m_pMask)
    {
        m_pMask = new CMask(pDevice);
        m_pMask->Load();
    }
    // 視差マップ
    if (!m_pParallax)
    {
        m_pParallax = new CParallaxMapping2(pDevice);
        m_pParallax->Load();
    }
    if (!m_pSquObj)
    {
        //2Ｄオブジェクトのロード
        m_pSquObj = new CShaderSquare(pDevice, (UINT)(SCREEN_WIDTH), (UINT)(SCREEN_HEIGHT));
        m_pSquObj->Load();
    }

    D3DVERTEXELEMENT9 decl[] =
    {
        { 0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        { 0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
        { 0, 24, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
        { 0, 36, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
        { 0, 48, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
        D3DDECL_END()
    };
    m_pWave->SetVertexDecl(pDevice, decl, m_WaterMesh, model.pMesh);
    m_pWave->Restore();
    m_pParallax->Restore();
    m_pBlurFilter->Restore();
    m_pLambert->Restore();
    m_pMask->Restore();
    m_pReflect->Restore();
    //シーンのレンダリングイメージ
    pDevice->CreateTexture(SCREEN_WIDTH,
        SCREEN_HEIGHT,
        1,
        D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        &m_pColorTexture,
        NULL);
    m_pColorTexture->GetSurfaceLevel(0, &m_pColorSurface);

    //反射マップ(縮小サーフェイス)
    pDevice->CreateTexture(m_pBlurFilter->GetWidth(),
        m_pBlurFilter->GetHeight(),
        1,
        D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        &m_pReflectTexture,
        NULL);
    m_pReflectTexture->GetSurfaceLevel(0, &m_pReflectSurface);

    //ブラーフィルター適応後サーフェイス(これも縮小サーフェイス)
    pDevice->CreateTexture(m_pBlurFilter->GetWidth(),
        m_pBlurFilter->GetHeight(),
        1,
        D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        &m_pBlurFilterTexture,
        NULL);
    m_pBlurFilterTexture->GetSurfaceLevel(0, &m_pBlurFilterSurface);

    //水面のマスクマップ
    pDevice->CreateTexture(SCREEN_WIDTH,
        SCREEN_HEIGHT,
        1,
        D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        &m_pWaterTexture,
        NULL);
    m_pWaterTexture->GetSurfaceLevel(0, &m_pWaterSurface);
    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CWaterFresnel::Uninit()
{
    if (m_pWave)
    {
        m_pWave->Uninit();
        delete m_pWave;
        m_pWave = nullptr;
    }
    if (m_pParallax)
    {
        m_pParallax->Invalidate();
        delete m_pParallax;
        m_pParallax = nullptr;
    }
    if (m_pBlurFilter)
    {
        m_pBlurFilter->Uninit();
        delete m_pBlurFilter;
        m_pBlurFilter = nullptr;
    }
    if (m_pLambert)
    {
        m_pLambert->Invalidate();
        delete m_pLambert;
        m_pLambert = nullptr;
    }
    if (m_pSquObj)
    {
        m_pSquObj->Uninit();
        delete m_pSquObj;
        m_pSquObj = nullptr;
    }
    if (m_pMask)
    {
        m_pMask->Invalidate();
        delete m_pMask;
        m_pMask = nullptr;
    }
    if (m_pReflect)
    {
        m_pReflect->Invalidate();
        delete m_pReflect;
        m_pReflect = nullptr;
    }
    if (m_pColorTexture)
    {
        m_pColorTexture->Release();
        m_pColorTexture = nullptr;
    }
    if (m_pColorSurface)
    {
        m_pColorSurface->Release();
        m_pColorSurface = nullptr;
    }

    if (m_pReflectTexture)
    {
        m_pReflectTexture->Release();
        m_pReflectTexture = nullptr;
    }    
    if (m_pReflectSurface)
    {
        m_pReflectSurface->Release();
        m_pReflectSurface = nullptr;
    }    
    if (m_pWaterTexture)
    {
        m_pWaterTexture->Release();
        m_pWaterTexture = nullptr;
    }    
    if (m_pWaterSurface)
    {
        m_pWaterSurface->Release();
        m_pWaterSurface = nullptr;
    }    
    if (m_pBlurFilterTexture)
    {
        m_pBlurFilterTexture->Release();
        m_pBlurFilterTexture = nullptr;
    }    
    if (m_pBlurFilterSurface)
    {
        m_pBlurFilterSurface->Release();
        m_pBlurFilterSurface = nullptr;
    }    

    // 終了処理
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CWaterFresnel::Update()
{
    // 更新処理
    CModel::Update();

    ShowInfo();
}

//=============================================================================
// 描画処理
//=============================================================================
void CWaterFresnel::Draw()
{
    if (m_pWave)
    {
        LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
        CTexture *pTexture = GET_TEXTURE_PTR;
        D3DXMATRIX matView, mtxRot, mtxTrans, mtxScale, matWorld, matReflect;
        D3DXMATRIX matProj = CManager::GetInstance()->GetCamera()->GetMtxProj();
        D3DXVECTOR3 CameraPos = CManager::GetInstance()->GetCamera()->GetposV();
        D3DXVECTOR4 EyePos = D3DXVECTOR4(CameraPos, 1.0f);
        D3DXVECTOR4 LightDir = D3DXVECTOR4(CManager::GetInstance()->GetLight()->GetLightDir(), 0.0f);
        CModelInfo *pModelInfo = GetModelInfo();
        CXfile::MODEL map = GET_XFILE_PTR->GetXfile(CXfile::XFILE_NUM_MAP);
        CXfile::MODEL sky = GET_XFILE_PTR->GetXfile(CXfile::XFILE_NUM_SKY);
        D3DXVECTOR3 ObjPos = { 0.0f, -0.0f, 0.0f };
        D3DXVECTOR3 PlayerPos = { 0.0f, -150.0f, 0.0f };
        D3DXVECTOR3 ObjSize = { 1.0f, 1.0f, 1.0f };
        CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
        list<CModelInfo*> pModelList = CModelInfo::GetInfoList();

        //太陽の位置ベクトル
        D3DXVECTOR4 LightPos = D3DXVECTOR4(-72.0f, -100.0f, -620.0f, 0.0f);
        D3DXVec3Normalize((D3DXVECTOR3*)&LightPos, (D3DXVECTOR3*)&LightPos);

        //マテリアルデータへのポインタを取得
        D3DMATERIAL9 matDef;
        CXfile::MODEL model = pModelInfo->GetModel();
        D3DXMATERIAL* pMat = (D3DXMATERIAL*)pModelInfo->GetBuffMat()->GetBufferPointer();

        //現在のマテリアルを取得する
        pDevice->GetMaterial(&matDef);

        // テクスチャ加工
        pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        pDevice->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        pDevice->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(2, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        pDevice->SetSamplerState(3, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(3, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(3, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        pDevice->SetSamplerState(4, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(4, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(4, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

        //****************************************************************
        //ステップ１：波マップの更新
        //****************************************************************
        //WAVEクラス内で浮動小数点フォーマットを使用している
        //浮動小数点フォーマットはビデオカードによっては「LINEAR」がきかないのでここでは「POINT」に設定しておく
        pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        //2Dスプライトオブジェクトを使用してレンダリングするのでＺバッファへの書き込みを無効にする
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        //ばね係数を設定
        m_pWave->SetWaveSpeed(m_fWaveSpeed);

        int nNum = CLibrary::Random(0, 1);
        D3DXVECTOR2 texpos = ZeroVector2;
        switch (nNum)
        {
        case 0:// 上
            texpos.x = CLibrary::Random(-0.0f, 1.0f);
            texpos.y = 0.0f;
            break;
         case 1:// 左
            texpos.x = 0.0f;
            texpos.y = CLibrary::Random(-0.0f, 1.0f);
            break;
        default:
            break;
        }
        //m_pWave->AddWave(texpos.x, texpos.y, CLibrary::Random(HEIGHT));

        //適当に波を新規作成する
        //追加する波の高さを設定できるように修正. 詳細は波シェーダーページを参照
        m_pWave->AddWave(CLibrary::Random(ADD_WAVE_TEX_POS), CLibrary::Random(ADD_WAVE_TEX_POS), CLibrary::Random(HEIGHT));

        //更新した波マップを取得
        LPDIRECT3DTEXTURE9 BumpMap = m_pWave->Draw();
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

        //****************************************************************
        // ステップ２ : 反射マップの作成
        //****************************************************************
        pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

        D3DVIEWPORT9 OldViewport, NewViewport;
        //縮小サーフェイスを使用するため、ビューポートを反射マップのサイズに合わせる
        pDevice->GetViewport(&OldViewport);
        CopyMemory(&NewViewport, &OldViewport, sizeof(D3DVIEWPORT9));
        NewViewport.Width = m_pBlurFilter->GetWidth();
        NewViewport.Height = m_pBlurFilter->GetHeight();
        NewViewport.MinZ = 0.0f;
        NewViewport.MaxZ = 1.0f;
        pDevice->SetViewport(&NewViewport);

        // サーフェス取得
        LPDIRECT3DSURFACE9 OldSurface = nullptr;
        pDevice->GetRenderTarget(0, &OldSurface);

        // サーフェス設定
        pDevice->SetRenderTarget(0, m_pReflectSurface);
        // サーフェスクリア
        pDevice->Clear(0L,
            nullptr,
            D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
            BlackColor,
            1.0f,
            0L);

        //Y 方向に反転してレンダリングするのでレンダリング面も反転させる
        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

        // ここから水面で Y 方向に反転させる行列を作成処理
        D3DXPLANE Plane;
        D3DXVECTOR3 Point, Normal;
        D3DXVECTOR4 LightDirReflect = LightDir;
        LightDirReflect.y *= -1.0f;

        //水面の任意一点の座標
        Point = D3DXVECTOR3(0.0f, m_fReflectHeight, 0.0f);
        //水面の法線ベクトル
        Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
        //水面の平面を定義
        D3DXPlaneFromPointNormal(&Plane, &Point, &Normal);
        //定義から反射行列を取得
        D3DXMatrixReflect(&matReflect, &Plane);

        // ここから背景レンダリング開始
        // 水面の高さをセット
        m_pReflect->SetHeight(Point.y);
        m_pReflect->Begin();

        D3DXMatrixIdentity(&matWorld);
        // 拡大率を反映
        D3DXMatrixScaling(&mtxScale, ObjSize.x, ObjSize.y, ObjSize.z);
        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxScale);
        //位置を反映
        D3DXMatrixTranslation(&mtxTrans, ObjPos.x, ObjPos.y, ObjPos.z);
        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxTrans);
        pDevice->SetTransform(D3DTS_WORLD, &matWorld);

        // ワールド行列を作成し、Y 方向に反転する行列を作成
        matWorld = matWorld * matReflect;
        m_pReflect->SetMatrix(&matWorld, &LightDirReflect);

        // box
        pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));
        m_pReflect->SetAmbient(&m_ReflectPlayerAmbiend);
        m_pReflect->BeginPass(0);

//        for (auto& pPtr : pModelList)
//        {
//            LPD3DXMESH mesh = pPtr->GetMesh();
//            DWORD numMat = pPtr->GetNumMat();
//            for (int nCount = 0; nCount < numMat; nCount++)
//            {
//                mesh->DrawSubset(0);
//            }
//        }
        //        map.pMesh->DrawSubset(0);
        m_pReflect->EndPass();
//        D3DXVECTOR3 playerPos = pPlayer->GetPos();
//        D3DXVECTOR3 playerRot = pPlayer->GetRot();

    //    size_t size = pPlayer->GetModelAnimeVec().size();
        m_pReflect->SetAmbient(&m_ReflectPlayerAmbiend);

    //    for (size_t nCount = 0; nCount < size; nCount++)
    //    {
    //        D3DXVECTOR3 AnimeModelPos = pPlayer->GetModelAnime(nCount)->GetPosAnime();
    //        D3DXVECTOR3 AnimeModelRot = pPlayer->GetModelAnime(nCount)->GetRotAnime();
    //        CModelAnime *pParent = pPlayer->GetModelAnime(nCount)->GetParent();
    //        D3DXMATRIX mtxParent, mtxPlayer;
    //        D3DXMatrixIdentity(&matWorld);
    //        D3DXMatrixIdentity(&mtxParent);
    //
    //        // 回転を反映
    //        D3DXMatrixRotationYawPitchRoll(&mtxRot, AnimeModelRot.y, AnimeModelRot.x, AnimeModelRot.z);
    //        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxRot);
    //
    //        D3DXVECTOR3 Pos = pPlayer->GetModelAnime(nCount)->GetModelInfo()->GetPos();
    //        D3DXVECTOR3 TextPos = pPlayer->GetModelAnime(nCount)->GetPosAnime();
    //
    //        //位置を反映
    //        D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
    //
    //        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxTrans);
    //
    //        //親が存在する場合
    //        if (pParent)
    //        {
    //            //親情報を設定
    //            mtxParent = pParent->GetModelInfo()->GetMtxWorld();
    //        }
    //        //親が存在しない場合
    //        else
    //        {
    //            //デバイス情報を設定
    //            mtxParent = pPlayer->GetMtxWorld();
    //        }
    //        
    //        //親のマトリクスと掛け合わせる
    //        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxParent);
    //        pDevice->SetTransform(D3DTS_WORLD, &matWorld);
    //
    //        // ワールド行列を作成し、Y 方向に反転する行列を作成
    //        matWorld = matWorld * matReflect;
    //        m_pReflect->SetMatrix(&matWorld, &LightDir);
    //        pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));
    //
    //        // プレイヤーの描画
    //        LPD3DXMESH mesh = pPlayer->GetModelAnime(nCount)->GetModelInfo()->GetMesh();
    //        size_t size = pPlayer->GetModelAnime(nCount)->GetModelInfo()->GetNumMat();
    //        for (size_t nCntMat = 0; nCntMat < size; nCntMat++)
    //        {
    //            m_pReflect->BeginPass();
    //            mesh->DrawSubset(nCntMat);
    //            m_pReflect->EndPass();
    //        }
    //    }

        // 全てのモデル
        for (auto& pPtr : pModelList)
        {
            LPD3DXMESH mesh = pPtr->GetMesh();
            DWORD numMat = pPtr->GetNumMat();
            D3DXMATRIX mtxWorld = pPtr->GetMtxWorld();
            matWorld = mtxWorld * matReflect;
            m_pReflect->SetMatrix(&matWorld, &LightDir);

            for (DWORD nCount = 0; nCount < numMat; nCount++)
            {
                pDevice->SetTexture(0, pPtr->GetTexture(nCount));
                m_pReflect->BeginPass(0);
                mesh->DrawSubset(nCount);
                m_pReflect->EndPass();
            }
        }

        // スキンメッシュ
        CSkinmeshModel* pSkinmeshModel = pPlayer->GetCurrentSkinMeshPtr();
//        pSkinmeshModel->Draw(this, matReflect);
        CKraken* pKraken = CManager::GetInstance()->GetGame()->GetKraken();
        pSkinmeshModel = pKraken->GetSkinMesh();
        pSkinmeshModel->Draw(this, matReflect);

        //Zバッファ書込み禁止
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        //空レンダリング
        pDevice->SetTexture(0, sky.apTexture[0]);
        D3DXMatrixIdentity(&matWorld);
        matWorld = matWorld * matReflect;
        m_pReflect->SetMatrix(&matWorld, &LightDirReflect);
        m_pReflect->SetAmbient(&m_ReflectSkyAmbiend);
        m_pReflect->BeginPass(0);
        sky.pMesh->DrawSubset(0);
        m_pReflect->EndPass();
        pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        pDevice->SetTexture(0, nullptr);
        m_pReflect->End();

        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
        pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

        //****************************************************************
        // ステップ３ : 反射マップをぼかす
        //****************************************************************
        // ブラーをかけるのでCLAMPにする
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

        // ターゲット変更
        pDevice->SetRenderTarget(0, m_pBlurFilterSurface);
        pDevice->SetTexture(0, m_pReflectTexture);
        m_pBlurFilter->Render(0);
        pDevice->SetTexture(0, nullptr);

        // 設定をもどす
        pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

        // ビューポートをもどす
        pDevice->SetViewport(&OldViewport);
        //****************************************************************
        // ステップ４ : シーンのレンダリング
        //****************************************************************
        // ターゲット変更
        pDevice->SetRenderTarget(0, m_pColorSurface);
        // クリア
        pDevice->Clear(0L,
            nullptr,
            D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
            BlackColor,
            1.0f,
            0L
        );

        // 背景レンダリング
        m_pLambert->Begin();
        D3DXMatrixIdentity(&matWorld);

        // 拡大率を反映
        D3DXMatrixScaling(&mtxScale, ObjSize.x, ObjSize.y, ObjSize.z);
        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxScale);

        //位置を反映
        D3DXMatrixTranslation(&mtxTrans, ObjPos.x, -ObjPos.y, ObjPos.z);
        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxTrans);
        pDevice->SetTransform(D3DTS_WORLD, &matWorld);

        m_pLambert->SetMatrix(&matWorld, &LightDir, m_fZdistance);
        pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));
        m_pLambert->SetAmbient(&m_LambertPlayerAmbiend);
        m_pLambert->SetZEnable(false);
        m_pLambert->BeginPass(0);
//        map.pMesh->DrawSubset(0);
        m_pLambert->EndPass();
//
//        //空レンダリング
//        //Zバッファ書込み禁止
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        pDevice->SetTexture(0, sky.apTexture[0]);
        D3DXMatrixIdentity(&matWorld);
        m_pLambert->SetMatrix(&matWorld, &LightDir, m_fZdistance);
        m_pLambert->SetAmbient(&m_LambertSkyAmbiend);
        m_pLambert->SetZEnable(true);
        m_pLambert->BeginPass(0);
        sky.pMesh->DrawSubset(0);
        m_pLambert->EndPass();
        pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        m_pLambert->End();

//        //αブレンドを有効にする
        //****************************************************************
        // ステップ５ : 水面のマスクマップをレンダリング
        //****************************************************************

        //Zバッファに書き込みしない
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

        // サーフェス変更
        pDevice->SetRenderTarget(0, m_pWaterSurface);
        pDevice->SetTexture(0, nullptr);

        //Zバッファはステップ４の結果を使用するため初期化しない
        pDevice->Clear(0L,
            nullptr,
            D3DCLEAR_TARGET ,
            BlackColor,
            1.0f,
            0L
        );

        // 水面モデル
        m_pMask->Begin();
        D3DXMatrixIdentity(&matWorld);
        m_pMask->SetMatrix(&matWorld);
        m_pMask->BeginPass(0);
        model.pMesh->DrawSubset(0);
        m_pMask->EndPass();
        m_pMask->End();

        //****************************************************************
        // ステップ６ : シーンのレンダリングイメージをバックバッファにレンダリングする
        //****************************************************************
        // サーフェスをバックバッファに戻す
        pDevice->SetRenderTarget(0, OldSurface);
        if (OldSurface)
        {
            OldSurface->Release();
            OldSurface = nullptr;
        }

        pDevice->SetTexture(0, m_pColorTexture);

        // 平面ポリゴン描画
    //    m_pSquObj->Draw();
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

        //****************************************************************
        // ステップ７ : 合成
        //****************************************************************
        //ステージ２と３はゆがみ処理を行うためCLAMPにする
        pDevice->SetSamplerState(2, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        pDevice->SetSamplerState(2, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        pDevice->SetSamplerState(3, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        pDevice->SetSamplerState(3, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        pDevice->SetSamplerState(4, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(4, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

        pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));
        pDevice->SetTexture(1, BumpMap);                // バンプマップ
        pDevice->SetTexture(2, m_pColorTexture);        // シーンレンダリング
        pDevice->SetTexture(3, m_pBlurFilterTexture);    // 反射マップのぼかし
        pDevice->SetTexture(4, m_pWaterTexture);        // 水面マスクマップ

        // 視差マッピング
        m_pParallax->Begin();
        m_pParallax->SetAmbient(&m_ParallaxAmbiend);
        m_pParallax->SetSpecular(m_fParallaxSpecular);                    // 5.0f
        m_pParallax->SetSpecularPower(m_fParallaxSpecularPower);        // 0.75f
        m_pParallax->SetHeight(m_fParallaxHeight);                        // 0.16f
        m_pParallax->SetRefraction(m_fParallaxRefraction);                // 80.0f

        // 水面モデルの描画
        D3DXMatrixIdentity(&matWorld);
        //位置を反映
        D3DXMatrixTranslation(&mtxTrans, ObjPos.x, -150.0f, ObjPos.z);
        D3DXMatrixMultiply(&matWorld, &matWorld, &mtxTrans);

        m_pParallax->SetMatrix(&matWorld, &EyePos, &LightDir, m_fZdistance);
        m_pParallax->BeginPass(0);
        model.pMesh->DrawSubset(0);
        m_pParallax->EndPass();
        m_pParallax->End();

        // テクスチャ情報クリア
        pDevice->SetTexture(0, nullptr);
        pDevice->SetTexture(1, nullptr);
        pDevice->SetTexture(2, nullptr);
        pDevice->SetTexture(3, nullptr);
        pDevice->SetTexture(4, nullptr);

        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(2, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(2, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(3, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(3, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(4, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(4, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
        pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    }
}

//=============================================================================
// Imgui情報
//=============================================================================
void CWaterFresnel::ShowInfo()
{
#ifdef _DEBUG

    //レンダラーで管理してるやつの情報
    ImGui::Begin("DebugInfo");

    if (ImGui::CollapsingHeader("WaterFresnelInfo"))
    {
        LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();    // デバイスの取得

        if (ImGui::TreeNode("Wave"))
        {
            // 移動量
            ImGui::SliderFloat("WaveSpeed", &m_fWaveSpeed, 0.0f, 2.0f);
            ImGui::SliderFloat("Zdistance", &m_fZdistance, 0.0f, 5000.0f);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Reflect"))
        {
            ImGui::SliderFloat4("PlayerAmbient", m_ReflectPlayerAmbiend, 0.0f, 1.0f);
            ImGui::SliderFloat4("SkyAmbient", m_ReflectSkyAmbiend, 0.0f, 1.0f);
            ImGui::SliderFloat("Height", &m_fReflectHeight, 0.0f, 30.0f);
            ImGui::TreePop();

        }
        if (ImGui::TreeNode("Lambert"))
        {
            ImGui::SliderFloat4("PlayerAmbient", m_LambertPlayerAmbiend, 0.0f, 1.0f);
            ImGui::SliderFloat4("SkyAmbient", m_LambertSkyAmbiend, 0.0f, 1.0f);
            ImGui::TreePop();

        }
        if (ImGui::TreeNode("Parallax"))
        {
            // 移動量
            ImGui::SliderFloat4("Ambient", m_ParallaxAmbiend, 0.0f, 1.0f);
            ImGui::SliderFloat("Specular", &m_fParallaxSpecular, 0.0f, 10.0f);
            ImGui::SliderFloat("SpecularPower", &m_fParallaxSpecularPower, 0.0f, 5.0f);
            ImGui::SliderFloat("Height", &m_fParallaxHeight, 0.0f, 5.0f);
            ImGui::SliderFloat("Refraction", &m_fParallaxRefraction, 0.0f, 1000.0f);
            ImGui::TreePop();
        }
    }

    ImGui::End();
#endif // !_DEBUG
}