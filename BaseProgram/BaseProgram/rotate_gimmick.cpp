//=============================================================================CRotateGimmick
//
// 回転床のギミッククラス [rotate_gimmick.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "rotate_gimmick.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "check_point.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "rotate_body.h"
#include "rotate_floor.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FIX_POS_Y		(150.0f)	// 高さの修正

//=============================================================================
// インスタンス生成
//=============================================================================
CRotateGimmick * CRotateGimmick::Create(const D3DXVECTOR3 &pos)
{
	// メモリ確保
	CRotateGimmick *pRotateGimmick = new CRotateGimmick;

	// !nullcheck
	if (pRotateGimmick)
	{
		// 初期化処理
		pRotateGimmick->CreateGimmick(pos);
		return pRotateGimmick;
	}

	return nullptr;
}

//=============================================================================
// ギミックの生成
//=============================================================================
void CRotateGimmick::CreateGimmick(const D3DXVECTOR3 &pos)
{
	CRotateFloor::Create(pos);
	CRotateBody::Create(D3DXVECTOR3(pos.x, pos.y + FIX_POS_Y, pos.z));
}