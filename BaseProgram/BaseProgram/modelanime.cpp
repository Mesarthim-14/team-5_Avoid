//=============================================================================
//
// 階層構造用のモデルクラス [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "modelanime.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "shadow.h"
#include "model_info.h"
#include "library.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CModelAnime::CModelAnime()
{
	//各メンバ変数のクリア
	m_posAnime = ZeroVector3;
	m_rotAnime = ZeroVector3;
	m_pParent = nullptr;
	m_bRotCalculation = false;
	m_pModelInfo = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CModelAnime::~CModelAnime()
{
	// ポインタの開放
	HasPtrDelete();
}

//=============================================================================
// クリエイト処理
//=============================================================================
CModelAnime * CModelAnime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model)
{
	// インスタンス生成
	CModelAnime *pModelAnime = new CModelAnime;

	// !nullcheck
	if (pModelAnime)
	{
		//初期化処理呼び出し
		pModelAnime->Init(pos, rot, model);
		return pModelAnime;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModelAnime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CXfile::MODEL model)
{
	// モデル情報のポインタ作成
	CreateInfoPtr();

	return S_OK;
}

//=============================================================================
// 描画処理
//=============================================================================
void CModelAnime::Draw(D3DXVECTOR3 rot)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxParent, mtxWorld;
	D3DMATERIAL9 matDef;						//現在のマテリアル保持用
	D3DXMATERIAL*pMat;							//マテリアルデータへのポインタ
	D3DXVECTOR3 pos = m_pModelInfo->GetPos();

	// マトリクス計算
	CLibrary::ConfigMatrix(&mtxWorld, pos, m_rotAnime);

	//親が存在する場合
	if (m_pParent)
	{
		//親情報を設定
		mtxParent = m_pParent->GetModelInfo()->GetMtxWorld();
	}
	//親が存在しない場合
	else
	{
		//デバイス情報を設定
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//親のマトリクスと掛け合わせる
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	m_pModelInfo->SetMtxWorld(mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	CXfile::MODEL model = m_pModelInfo->GetModel();
	pMat = (D3DXMATERIAL*)model.pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)model.dwNumMat; nCntMat++)
	{
		//マテリアルのアンビエントにディフューズカラーを設定
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (model.apTexture[nCntMat])
		{
			// テクスチャの設定
			pDevice->SetTexture(0, model.apTexture[nCntMat]);
		}
		else
		{
			// テクスチャ設定
			pDevice->SetTexture(0, nullptr);
		}

		//モデルパーツの描画
		model.pMesh->DrawSubset(nCntMat);

		// 透明度戻す
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	// 影の設定
	CShadow *pShadow = m_pModelInfo->GetShadow();
	if (pShadow)
	{
		D3DXVECTOR3 thisRot = m_pModelInfo->GetRot();

		// 影の縦回転の計算が有効かどうか
		if (m_bRotCalculation)
		{
			pShadow->CreateShadow(thisRot, rot, m_pModelInfo->SetShadowInfo(rot, mtxParent));
		}
		else
		{
			pShadow->CreateShadow(thisRot + rot, mtxWorld);
		}
	}
}

//=============================================================================
// 影の描画
//=============================================================================
void CModelAnime::ShadowDraw(D3DXVECTOR3 rot)
{
	CShadow *pShadow = m_pModelInfo->GetShadow();

	if (pShadow)
	{
		// 影の描画処理
		pShadow->VolumeDraw();
	}
}

//=============================================================================
// 情報ポインタ生成
//=============================================================================
void CModelAnime::CreateInfoPtr(void)
{
	if (!m_pModelInfo)
	{
		m_pModelInfo = CModelInfo::Create(CModelInfo::MODEL_TYPE_NONE);
	}
}

//=============================================================================
// 保持ポインタの開放処理
//=============================================================================
void CModelAnime::HasPtrDelete(void)
{
	if (m_pModelInfo)
	{
		// 影の終了処理
		m_pModelInfo->Uninit();
		m_pModelInfo = nullptr;
	}
}
