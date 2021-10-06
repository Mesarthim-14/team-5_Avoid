//=============================================================================
//
// 階層構造用のモデルクラス処理 [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "model_info.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "shadow.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CModelInfo::CModelInfo()
{
	//各メンバ変数のクリア
	memset(&m_model, 0, sizeof(m_model));
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	ZeroMemory(m_OldMtxWorld, sizeof(m_OldMtxWorld));
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
	m_pShadow = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CModelInfo::~CModelInfo()
{
	// ポインタの開放
	HasPtrDelete();
}

//=============================================================================
// クリエイト処理
//=============================================================================
CModelInfo * CModelInfo::Create(void)
{
	//階層モデルクラスのポインタ変数
	CModelInfo *pModelInfo = new CModelInfo;

	// !nullcheck
	if (pModelInfo)
	{
		//初期化処理呼び出し
		pModelInfo->Init();

		return pModelInfo;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModelInfo::Init(void)
{

	return S_OK;
}

//=============================================================================
// 描画処理
//=============================================================================
void CModelInfo::Draw(D3DXVECTOR3 rot)
{
}

//=============================================================================
// 影の描画
//=============================================================================
void CModelInfo::ShadowDraw(D3DXVECTOR3 rot)
{
	if (m_pShadow)
	{
		// 影の描画処理
		m_pShadow->VolumeDraw();
	}
}

//=============================================================================
// 影のポインタ生成
//=============================================================================
void CModelInfo::CreateShadowPtr(void)
{
	if (m_bUseShadow)
	{
		// nullcheck
		if (!m_pShadow)
		{
			// 影の生成
			m_pShadow = CShadow::Create(m_model.pMesh);
		}
	}
}

//=============================================================================
// 影の情報の設定
//=============================================================================
D3DXMATRIX CModelInfo::SetShadowInfo(D3DXVECTOR3 rot, D3DXMATRIX pParent)
{
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxWorld;                            // ワールドマトリックス
	D3DXMatrixIdentity(&mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &pParent);

	return mtxWorld;
}

//=============================================================================
// 保持ポインタの開放処理
//=============================================================================
void CModelInfo::HasPtrDelete(void)
{
	if (m_pShadow)
	{
		// 影の終了処理
		m_pShadow->Uninit();
		delete m_pShadow;
		m_pShadow = nullptr;
	}
}

//=============================================================================
// モデルの情報設定
//=============================================================================
void CModelInfo::SetModelStatus(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model)
{
	m_pos = pos;
	m_rot = rot;
	m_model = model;
}

//=============================================================================
// ワールドマトリクス座標
//=============================================================================
D3DXVECTOR3 CModelInfo::GetMtxPos(void)
{
	D3DXMATRIX mtxWorld = GetMtxWorld();
	return D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
}