//=============================================================================
//
// モデルクラス [model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "shadow.h"
#include "model_info.h"
#include "player.h"
#include "library.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel(PRIORITY Priority) : CScene(Priority)
{
	m_move = ZeroVector3;
	m_size = ZeroVector3;
	m_scale = MODEL_DEFAULT_SIZE;
	m_nTexPattern = 0;
	m_nLife = 0;
	m_pModelInfo = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//モデルクラスのポインタ変数
	CModel *pModel = new CModel(PRIORITY_MODEL);

	// nullcheck
	if (pModel)
	{
		//初期化処理呼び出し
		pModel->Init();
		return pModel;
	}

	return nullptr;
}

//=============================================================================
// プレイヤーとの距離の当たり判定
//=============================================================================
bool CModel::PlayerDisCollision(const float & fDistanse)
{
	// 座標の取得
	D3DXVECTOR3 PPos = CManager::GetInstance()->GetPlayer()->GetPos();
	D3DXVECTOR3 ThisPos = GetModelInfo()->GetPos();

	// 距離の取得
	float fDistance = CLibrary::DistanceCal(PPos, ThisPos);

	// 距離を測る
	if (fDistance <= fDistanse)
	{
		return true;
	}

	return false;
}

//=============================================================================
//モデルクラスの初期化処理
//=============================================================================
HRESULT CModel::Init(void)
{
	// 情報の生成
	CreateInfoPtr();

	return S_OK;
}

//=============================================================================
//モデルクラスの終了処理
//=============================================================================
void CModel::Uninit(void)
{
	// 影の終了処理
	HasPtrDelete();

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// モデルクラスの更新処理
//=============================================================================
void CModel::Update(void)
{
	// 寿命を減らす
	m_nLife--;

	// 座標の更新
	m_pModelInfo->GetPos() += m_move;
}

//=============================================================================
// モデルクラスの描画処理
//=============================================================================
void CModel::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DMATERIAL9 matDef;
	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxWorld;
	D3DXVECTOR3 pos = m_pModelInfo->GetPos();
	D3DXVECTOR3 rot = m_pModelInfo->GetRot();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 拡大率を反映
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	m_pModelInfo->SetMtxWorld(mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	CXfile::MODEL model = m_pModelInfo->GetModel();
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pModelInfo->GetBuffMat()->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)model.dwNumMat; nCntMat++)
	{
		//マテリアルのアンビエントにディフューズカラーを設定
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		if (model.apTexture[nCntMat])
		{
			pDevice->SetTexture(0, model.apTexture[nCntMat]);
		}
		else
		{
			pDevice->SetTexture(0, nullptr);
		}
		
		//モデルパーツの描画
		model.pMesh->DrawSubset(nCntMat);
		pDevice->SetTexture(0, nullptr);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// 影の描画
	m_pModelInfo->ShadowDraw(rot);
}

//=============================================================================
// モデル情報の設定
//=============================================================================
void CModel::HasPtrDelete(void)
{
	if (m_pModelInfo)
	{
		m_pModelInfo->Uninit();
		m_pModelInfo = nullptr;
	}
}

//=============================================================================
// 情報のポインタ生成
//=============================================================================
void CModel::CreateInfoPtr(void)
{
	if (!m_pModelInfo)
	{
		m_pModelInfo = CModelInfo::Create(CModelInfo::MODEL_TYPE_NONE);
	}
}

//=============================================================================
// 座標の情報取得
//=============================================================================
D3DXVECTOR3 CModel::GetPos()
{
	return GetModelInfo()->GetPos();
}

//=============================================================================
// 角度の情報取得
//=============================================================================
D3DXVECTOR3 CModel::GetRot()
{
	return GetModelInfo()->GetRot();
}
