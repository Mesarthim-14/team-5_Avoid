//=============================================================================
//
// 空クラス [sky.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "sky.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS        (ZeroVector3)
#define TEST_ROT        (ZeroVector3)

//=============================================================================
// コンストラクタ
//=============================================================================
CSky::CSky(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CSky::~CSky()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CSky * CSky::Create()
{
    // メモリ確保
    CSky *pTestModel = new CSky(PRIORITY_GIMMICK);

    // !nullcheck
    if (pTestModel)
    {
        // 初期化処理
        pTestModel->Init();
        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSky::Init()
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_SKY_BLUE);
    GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);
    SetShaderFlag(false);
    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSky::Uninit()
{
    CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSky::Update()
{
    CModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CSky::Draw()
{
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;
    pDevice->SetRenderState(D3DRS_LIGHTING, false);

    CModel::Draw();

    // ライト効果を付ける
   pDevice->SetRenderState(D3DRS_LIGHTING, true);
}