//=============================================================================
//
// クラス [swirl_scaffold.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "swirl_scaffold.h"
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
#define TEST_ROT    (D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))   // 角度
#define ROTATE_NUM  (D3DXToRadian(1.0f))                            // 回転の値

//=============================================================================
// コンストラクタ
//=============================================================================
CSwirlScaffold::CSwirlScaffold(PRIORITY Priority) : CModel(Priority)
{
    m_fRotateNum = ROTATE_NUM;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSwirlScaffold::~CSwirlScaffold()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CSwirlScaffold * CSwirlScaffold::Create(const D3DXVECTOR3 &pos)
{
    // メモリ確保
    CSwirlScaffold *pRotatebody = new CSwirlScaffold(PRIORITY_TEST_MODEL);

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
HRESULT CSwirlScaffold::Init(const D3DXVECTOR3 &pos)
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
void CSwirlScaffold::Update()
{
    // 回転させる
    Rotate();

    CModel::Update();
}

//=============================================================================
// 回転
//=============================================================================
void CSwirlScaffold::Rotate()
{
    D3DXVECTOR3 rot = GetModelInfo()->GetRot();
    rot.y += m_fRotateNum;
    CLibrary::RotFix(rot.y);
    GetModelInfo()->SetRot(rot);
}