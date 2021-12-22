//=============================================================================
//
// 渦ギミックの床クラス [swirl_scaffold.object.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "swirl_scaffold_object.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_ROT    (D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f))   // 角度

//=============================================================================
// コンストラクタ
//=============================================================================
CSwirlScaffoldObject::CSwirlScaffoldObject(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSwirlScaffoldObject::~CSwirlScaffoldObject()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CSwirlScaffoldObject * CSwirlScaffoldObject::Create(const D3DXVECTOR3 &pos)
{
    // メモリ確保
    CSwirlScaffoldObject *pRotatebody = new CSwirlScaffoldObject(PRIORITY_MAP);

    // !nullcheck
    if (pRotatebody)
    {
        // 初期化処理
        pRotatebody->Init(pos);
        return pRotatebody;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSwirlScaffoldObject::Init(const D3DXVECTOR3 &pos)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_SPINFLOOR);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CSwirlScaffoldObject::Update()
{
    CModel::Update();
}