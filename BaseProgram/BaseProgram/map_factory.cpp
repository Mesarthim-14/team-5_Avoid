//=======================================================================================
//
// マップ生成クラス [map_factory.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "map_factory.h"
#include "manager.h"
#include "resource_manager.h"
#include "map_first_floor.h"
#include "map_thin_floor.h"
#include "map_square_floor.h"
#include "map_thin_floor2.h"
#include "map_square_floor2.h"
#include "map_check_floor2.h"
#include "map_big_floor2.h"
#include "map_check_floor.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define HEIGHT  (-300.0f)
#define HEIGHT2 (-1000.0f)

//=======================================================================================
// コンストラクタ
//=======================================================================================
CMapFactory::CMapFactory()
{
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CMapFactory::~CMapFactory()
{
}

//=======================================================================================
// インスタンス生成
//=======================================================================================
CMapFactory * CMapFactory::Create()
{
    // メモリ確保
    CMapFactory *pGimmickFactory = new CMapFactory;
    if (pGimmickFactory)
    {
        // 初期化処理
        pGimmickFactory->Init();
        return pGimmickFactory;
    }
    return nullptr;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CMapFactory::Init()
{
    // 最初の床
    CMapFirstFloor::Create(D3DXVECTOR3(54500.0f, HEIGHT, 25500.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
    CMapThinFloor::Create(D3DXVECTOR3(60758.3f, HEIGHT, 13071.7f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
    CMapThinFloor::Create(D3DXVECTOR3(50158.7f, HEIGHT, 13185.8f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
    CMapSquareFloor::Create(D3DXVECTOR3(54771.6f, HEIGHT, 1259.0f), D3DXVECTOR3(0.0f, D3DXToRadian(100.0f), 0.0f));
    CMapSquareFloor::Create(D3DXVECTOR3(52679.7f, HEIGHT, -8746.0f), D3DXVECTOR3(0.0f, D3DXToRadian(105.0f), 0.0f));
    CMapThinFloor2::Create(D3DXVECTOR3(40043.3f, HEIGHT2, -42639.8f), D3DXVECTOR3(0.0f, D3DXToRadian(-25.0f), 0.0f));
    CMapSquareFloor2::Create(D3DXVECTOR3(30960.8f, HEIGHT2, -47462.7f), D3DXVECTOR3(0.0f, D3DXToRadian(66.0f), 0.0f));
    CMapSquareFloor2::Create(D3DXVECTOR3(23527.2f, HEIGHT2, -51002.5f), D3DXVECTOR3(0.0f, D3DXToRadian(65.0f), 0.0f));
    CMapCheckFloor2::Create(D3DXVECTOR3(5185.7f, HEIGHT2, -48747.7f), D3DXVECTOR3(0.0f, D3DXToRadian(65.0f), 0.0f));
    CMapSquareFloor::Create(D3DXVECTOR3(1451.0f, HEIGHT, -76855.2f), D3DXVECTOR3(0.0f, D3DXToRadian(95.0f), 0.0f));
    CMapThinFloor2::Create(D3DXVECTOR3(-27489.5f, HEIGHT2, -72072.8f), D3DXVECTOR3(0.0f, D3DXToRadian(10.0f), 0.0f));
    CMapBigFloor2::Create(D3DXVECTOR3(-30507.4f, HEIGHT2, -54503.3f), D3DXVECTOR3(0.0f, D3DXToRadian(30.0f), 0.0f));
    CMapThinFloor2::Create(D3DXVECTOR3(-48309.2f, HEIGHT2, -63000.0f), D3DXVECTOR3(0.0f, D3DXToRadian(31.0f), 0.0f));
    CMapThinFloor2::Create(D3DXVECTOR3(-58031.0f, HEIGHT2, -53933.0f), D3DXVECTOR3(0.0f, D3DXToRadian(49.0f), 0.0f));
    CMapSquareFloor2::Create(D3DXVECTOR3(-65041.0f, HEIGHT2, -45465.4f), D3DXVECTOR3(0.0f, D3DXToRadian(154.0f), 0.0f));
    CMapSquareFloor2::Create(D3DXVECTOR3(-67832.1f, HEIGHT2, -36745.1f), D3DXVECTOR3(0.0f, D3DXToRadian(168.0f), 0.0f));
    CMapSquareFloor2::Create(D3DXVECTOR3(-68313.5f, HEIGHT2, -27618.3f), D3DXVECTOR3(0.0f, D3DXToRadian(-178.0f), 0.0f));
    CMapThinFloor2::Create(D3DXVECTOR3(-58829.5f, HEIGHT2, -19673.2f), D3DXVECTOR3(0.0f, D3DXToRadian(-53.0f), 0.0f));
    CMapSquareFloor2::Create(D3DXVECTOR3(-32034.4f, HEIGHT2, -39649.5f), D3DXVECTOR3(0.0f, D3DXToRadian(128.0f), 0.0f));
    CMapThinFloor2::Create(D3DXVECTOR3(-40395.8f, HEIGHT2, -31879.8f), D3DXVECTOR3(0.0f, D3DXToRadian(39.0f), 0.0f));
    CMapThinFloor2::Create(D3DXVECTOR3(-49920.0f, HEIGHT2, -23829.7f), D3DXVECTOR3(0.0f, D3DXToRadian(39.0f), 0.0f));
    CMapCheckFloor::Create(D3DXVECTOR3(-300.0f, HEIGHT2, 64653.9f), D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f));
    CMapSquareFloor2::Create(D3DXVECTOR3(22745.2f, HEIGHT2, 51353.1f), D3DXVECTOR3(0.0f, D3DXToRadian(-60.0f), 0.0f));
    CMapThinFloor::Create(D3DXVECTOR3(14218.3f, HEIGHT, 45689.1f), D3DXVECTOR3(0.0f, D3DXToRadian(-58.5f+90.0f), 0.0f));
    CMapThinFloor::Create(D3DXVECTOR3(25132.5f, HEIGHT, 38889.2f), D3DXVECTOR3(0.0f, D3DXToRadian(-58.5f+90.0f), 0.0f));
    CMapThinFloor::Create(D3DXVECTOR3(37173.7f, HEIGHT, 31628.6f), D3DXVECTOR3(0.0f, D3DXToRadian(-58.5f+90.0f), 0.0f));

    return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CMapFactory::Uninit()
{
    delete this;
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CMapFactory::Update()
{

}