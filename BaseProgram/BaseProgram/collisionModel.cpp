//=============================================================================
//
// 当たり判定モデルの処理 [collisionModel.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "collisionModel.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCollisionModel::CCollisionModel(PRIORITY Priority) :CScene(Priority)
{
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	memset(&m_obb, 0, sizeof(m_obb));
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCollisionModel::~CCollisionModel()
{
}

//*****************************************************************************
// ロード
//*****************************************************************************
void CCollisionModel::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	switch (m_obb.CollisionType)
	{
	case TYPE_POLYGON:

		//ポリゴンの作成
		D3DXCreatePolygon(
			pDevice,						//デバイス情報
			10.0f,							//辺の長さ
			4,								//辺の数
			&m_pMesh,		//メッシュ情報
			&m_pBuffMat);	//バッファ情報

		break;

	case TYPE_BOX:

		//箱の作成
		D3DXCreateBox(
			pDevice,					//デバイス情報
			1.0f,						//横幅
			1.0f,						//立幅
			1.0f,						//奥幅
			&m_pMesh,		//メッシュ情報
			&m_pBuffMat);	//バッファ情報

		break;

	case TYPE_SPHERE:

		//球の作成
		D3DXCreateSphere(
			pDevice,					//デバイス情報
			1.0f,						//手前の円の半径
			10,							//スライスの数
			10,							//スタック数
			&m_pMesh,		//メッシュ情報
			&m_pBuffMat);	//バッファ情報

		break;

	case TYPE_CYLINDER:

		//円柱の作成
		D3DXCreateCylinder(
			pDevice,						//デバイス情報
			1.0f,							//手前の円の半径
			1.0f,							//奥の円の半径
			1.0f,							//円柱の長さ
			10,								//スライス(円の超点数)
			1,								//スタック(円柱の分割数)
			&m_pMesh,		//メッシュ情報
			&m_pBuffMat);	//バッファ情報

		break;

	default:

		break;
	}
}

//*****************************************************************************
// アンロード
//*****************************************************************************
void CCollisionModel::Unload(void)
{
	if (m_pMesh != nullptr)
	{
		//メッシュの破棄
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pBuffMat != nullptr)
	{
		//バッファの破棄
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
}

//*****************************************************************************
// 当たり判定モデルの生成
//*****************************************************************************
CCollisionModel * CCollisionModel::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const TYPE &type)
{
	CCollisionModel *pCollision = new CCollisionModel;

	if (pCollision != NULL)
	{
		//当たり判定モデル情報の設定
		pCollision->m_obb.pos = pos;
		pCollision->m_obb.size = size;
		pCollision->m_obb.rot = rot;
		pCollision->m_obb.CollisionType = type;

		//当たり判定モデルの初期化処理
		pCollision->Init();

		return pCollision;
	}

	return nullptr;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CCollisionModel::Init(void)
{
	//ロード処理
	Load();

	//各軸の回転前座標の設定(回転していないXYZ軸に大きさだけを適応)
	m_obb.DirVect[0] = D3DXVECTOR3(m_obb.size.x / 2, 0.0f, 0.0f);
	m_obb.DirVect[1] = D3DXVECTOR3(0.0f, m_obb.size.y / 2, 0.0f);
	m_obb.DirVect[2] = D3DXVECTOR3(0.0f, 0.0f, m_obb.size.z / 2);

	//各軸の方向ベクトルの計算
	for (int nCount = 0; nCount < 3; nCount++)
	{
		CLibrary::Rotate3D(m_obb.DirVect[nCount], m_obb.rot);
	}

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CCollisionModel::Uninit(void)
{
	//アンロード処理
	Unload();

	//ワールドマトリックスの初期化
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));

	//単数リリース
	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CCollisionModel::Update(void)
{
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CCollisionModel::Draw(void)
{
#ifdef _DEBUG
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//色の設定
	D3DXMATERIAL* mat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	mat->MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	//ワイヤーフレームで描画
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;	//現在のマテリアル保持用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 拡大率を反映
	D3DXMatrixScaling(&mtxScale, m_obb.size.x, m_obb.size.y, m_obb.size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_obb.rot.y, m_obb.rot.x, m_obb.rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_obb.pos.x, m_obb.pos.y, m_obb.pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタ
	D3DXMATERIAL*pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//マテリアルのアンビエントにディフューズカラーを設定
	pMat->MatD3D.Ambient = pMat->MatD3D.Diffuse;

	//マテリアルの設定
	pDevice->SetMaterial(&pMat->MatD3D);

	if (m_pMesh != NULL)
	{
		//モデルパーツの描画
		m_pMesh->DrawSubset(0);
	}

	pDevice->SetTexture(0, nullptr);

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//ワイヤーフレームをもどす
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif
}