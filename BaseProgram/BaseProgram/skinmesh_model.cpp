//=============================================================================
//
// モデルクラス [model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "skinmesh_model.h"
#include "manager.h"
#include "renderer.h"
#include "shadow.h"
#include "model_info.h"
#include "skinmesh.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSkinmeshModel::CSkinmeshModel(PRIORITY Priority) : CScene(Priority)
{
	m_move = ZeroVector3;
	m_size = ZeroVector3;
	m_scale = MODEL_DEFAULT_SIZE;
	m_nTexPattern = 0;
	m_nLife = 0;
	m_pModelInfo = nullptr;
	m_pAnimetionController = 0;
	m_pRootFrame = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSkinmeshModel::~CSkinmeshModel()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CSkinmeshModel * CSkinmeshModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//モデルクラスのポインタ変数
	CSkinmeshModel *pModel = new CSkinmeshModel;

	// nullcheck
	if (pModel)
	{
		//初期化処理呼び出し
		pModel->Init();
		pModel->GetModelInfo()->SetPos(pos);
		return pModel;
	}

	return nullptr;
}

//=============================================================================
//モデルクラスの初期化処理
//=============================================================================
HRESULT CSkinmeshModel::Init(void)
{
	// 情報の生成
	CreateInfoPtr();

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// スキンメッシュ情報をXファイル保存用
	SkinMesh::AllocateHierarchy allocater;

	//エラー確認用
	HRESULT model = D3DERR_WRONGTEXTUREFORMAT;
	//仮モデル
	model = D3DXLoadMeshHierarchyFromX(("data/Model/Hierarchy/test_slime_model01.x"), D3DXMESH_MANAGED, pDevice, &allocater, 0, (D3DXFRAME**)&m_pRootFrame, &m_pAnimetionController);

	if (model == D3DERR_INVALIDCALL)
	{
		return 0;
	}

	//メッシュコンテナ取得関数
	SkinMesh::getMeshContainer(m_pRootFrame, &m_cont);

	for (int i = 0; i < m_cont.size(); i++)
	{
		m_combs.push_back((D3DXBONECOMBINATION*)m_cont[i]->boneCombinationTable->GetBufferPointer());

		// フレーム内にボーンIDとオフセット行列を埋め込む
		SkinMesh::setFrameId(m_pRootFrame, m_cont[i]->pSkinInfo);
	}

	return S_OK;
}

//=============================================================================
//モデルクラスの終了処理
//=============================================================================
void CSkinmeshModel::Uninit(void)
{
	// 影の終了処理
	HasPtrDelete();

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// モデルクラスの更新処理
//=============================================================================
void CSkinmeshModel::Update(void)
{
	// 寿命を減らす
	m_nLife--;

	// 座標の更新
	m_pModelInfo->GetPos() += m_move;
}

//=============================================================================
// モデルクラスの描画処理
//=============================================================================
void CSkinmeshModel::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DMATERIAL9 matDef;
	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxWorld;
	D3DXVECTOR3 pos = m_pModelInfo->GetPos();
	D3DXVECTOR3 rot = m_pModelInfo->GetRot();

	//現在フレーム(fps)のワールド変換行列
	std::map<DWORD, D3DXMATRIX> combMatrixMap;
		
	// 時間を進めて姿勢更新
	m_pAnimetionController->AdvanceTime(0.0001f, 0);
	m_pAnimetionController->SetTrackAnimationSet(0, 0);

	SkinMesh::updateCombMatrix(combMatrixMap, m_pRootFrame);

	for (DWORD BCombiId = 0; BCombiId < m_cont.size(); BCombiId++)
	{
		for (DWORD AttribId = 0; AttribId < m_cont[BCombiId]->numBoneCombinations; AttribId++)
		{
			DWORD boneCount = 0;

			for (DWORD Count = 0; Count < m_cont[BCombiId]->maxFaceInfl; Count++)
			{
				//ボーンコンビネーションテーブルからボーンIDを抽出
				DWORD BoneId = m_combs[BCombiId][AttribId].BoneId[Count];

				//ボーンIDが存在している
				if (BoneId != UINT_MAX)
				{
					// インデックス付きワールドマトリックスの設定
					pDevice->SetTransform(D3DTS_WORLDMATRIX(Count), &combMatrixMap[BoneId]);
					boneCount++;
				}
			}

			pDevice->SetRenderState(D3DRS_VERTEXBLEND, boneCount - 1);

			//メッシュコンテナ内のメッシュデータ
			m_cont[BCombiId]->MeshData.pMesh->DrawSubset(AttribId);
		}
	}

	
	//
	////ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&mtxWorld);

	//// 拡大率を反映
	//D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	////位置を反映
	//D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &combMatrixMap[0]);
	//m_pModelInfo->SetMtxWorld(mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	////マテリアルデータへのポインタを取得
	//CXfile::MODEL model = m_pModelInfo->GetModel();
	//D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pModelInfo->GetBuffMat()->GetBufferPointer();
	//for (int nCntMat = 0; nCntMat < (int)model.dwNumMat; nCntMat++)
	//{
	//	//マテリアルのアンビエントにディフューズカラーを設定
	//	pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

	//	//マテリアルの設定
	//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

	//	// テクスチャの設定
	//	if (model.apTexture[nCntMat])
	//	{
	//		pDevice->SetTexture(0, model.apTexture[nCntMat]);
	//	}
	//	else
	//	{
	//		pDevice->SetTexture(0, nullptr);
	//	}

	//	//モデルパーツの描画
	//	model.pMesh->DrawSubset(nCntMat);
	//	pDevice->SetTexture(0, nullptr);
	//}

	//保持していたマテリアルを戻す
	//pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// 影の描画
	m_pModelInfo->ShadowDraw(rot);
}

//=============================================================================
// モデル情報の設定
//=============================================================================
void CSkinmeshModel::HasPtrDelete(void)
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
void CSkinmeshModel::CreateInfoPtr(void)
{
	if (!m_pModelInfo)
	{
		m_pModelInfo = CModelInfo::Create(CModelInfo::MODEL_TYPE_NONE);
	}
}