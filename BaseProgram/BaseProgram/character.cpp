//=============================================================================
//
// キャラクタークラス [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "motion.h"
#include "model_info.h"
#include "library.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GRAVITY_POWAR			(1.0f)						// 重力の強さ
#define GROUND_RIMIT			(0.0f)						// 地面の制限

//=============================================================================
// コンストラクタ
//=============================================================================
CCharacter::CCharacter(PRIORITY Priority) : CScene(Priority)
{
	m_pos = ZeroVector3;
	m_posOld = ZeroVector3;
	m_move = ZeroVector3;
	m_rot = ZeroVector3;
	m_size = ZeroVector3;
	m_fSpeed = 0.0f;
	m_nStateCounter = 0;
	m_pMotion = nullptr;
	m_nParts = 0;
	m_apModelAnime.clear();
	m_bLanding = false;
	m_State = STATE_NORMAL;
	m_bUseShadow = false;
	m_bGravity = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCharacter::~CCharacter()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCharacter::Init(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCharacter::Uninit()
{
	for (auto &ModelAnime : m_apModelAnime)
	{
		// nullcheck
		if (ModelAnime)
		{
			//メモリの削除
			delete ModelAnime;
			ModelAnime = nullptr;
		}
	}

	// クリア
	m_apModelAnime.clear();

	// nullcheck
	if (m_pMotion)
	{
		//メモリの削除
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCharacter::Update()
{
	// 重力
	Gravity();

	// 移動量加算
	m_pos += m_move;

	// カウンターを進める
	m_nStateCounter++;
}

//=============================================================================
// 描画処理
//=============================================================================
void CCharacter::Draw()
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// マトリクスの設定
	CLibrary::ConfigMatrix(&m_mtxWorld, m_pos, m_rot);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルの描画
	for (auto &model : m_apModelAnime)
	{
		if (model)
		{
			model->Draw(m_rot);
		}
	}

	// 影の描画
	if (m_bUseShadow)
	{
		for (auto &shadow : m_apModelAnime)
		{
			if (shadow)
			{
				shadow->ShadowDraw(m_rot);
			}
		}
	}
}

//=============================================================================
// モデルの生成
//=============================================================================
void CCharacter::ModelCreate(const CXfile::HIERARCHY_XFILE_NUM &FileNum)
{
	// XFileのポインタ取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// nullcheck
	if (pXfile)
	{
		// モデルパーツの設定
		m_nParts = pXfile->GetModelParts(FileNum);

		//モデルパーツ数分繰り返す
		for (int nCntModel = 0; nCntModel < m_nParts; nCntModel++)
		{
			// ローカル変数取得
			CModelAnime *pModelAnime = nullptr;
			CXfile::MODELFILE ModelFile = pXfile->GetModelFile(nCntModel, FileNum);
			vector<CXfile::MODEL> model = pXfile->GetHierarchyXfile(FileNum);

			// nullcheck
			if (!pModelAnime)
			{
				// インスタンス生成
				pModelAnime = CModelAnime::Create(ModelFile.offsetPos, ModelFile.offsetRot, model.at(nCntModel));

				// nullcheck
				if (pModelAnime)
				{
					// モデル情報の設定
					pModelAnime->GetModelInfo()->SetModelStatus(ModelFile.offsetPos, ModelFile.offsetRot, model.at(nCntModel));
					if (m_bUseShadow)
					{
						// 影の生成
						pModelAnime->GetModelInfo()->CreateShadowPtr();
					}

					//親モデルの場合
					if (nCntModel == 0)
					{
						pModelAnime->SetParent(nullptr);
					}
					//子モデルの場合
					else
					{
						//自分の親情報を設定する
						pModelAnime->SetParent(m_apModelAnime.at(ModelFile.nParent));
					}
				}

				// 情報を入れる
				m_apModelAnime.push_back(pModelAnime);
			}
		}
		// nullcheck
		if (!m_pMotion)
		{
			// モーション情報のインスタンス生成
			m_pMotion = CMotion::Create(pXfile->GetModelFileName(FileNum));
		}
	}
}

//=============================================================================
// モデルアニメーション
//=============================================================================
void CCharacter::ModelAnimeUpdate(void)
{
	// モーションの更新処理
	if (m_pMotion)
	{
		// モーションの更新
		m_pMotion->UpdateMotion(m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// 重力の処理
//=============================================================================
void CCharacter::Gravity(void)
{
	// 重力をかける
	m_move.y -= CGame::GetGravity();
	m_pos.y += m_move.y;		// 落下

	// 地面の判定
	if (m_pos.y <= GROUND_RIMIT)
	{
		Landing(GROUND_RIMIT);
	}
	else
	{
		m_bLanding = false;
	}
}

//=============================================================================
// 着地の処理
//=============================================================================
void CCharacter::Landing(float fHeight)
{
	m_move.y = 0.0f;
	m_pos.y = fHeight;

	// 着地の状態
	if (!m_bLanding)
	{
		m_bLanding = true;
	}
}

//=============================================================================
// モーションの設定
//=============================================================================
void CCharacter::SetMotion(int nMotionState)
{
	// nullcheck
	if (m_pMotion)
	{
		// モーションの更新
		m_pMotion->SetMotion(nMotionState, m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// 影の回転を反映させるか
//=============================================================================
void CCharacter::SetShadowRotCalculation(void)
{
	// モデルの描画
	for (auto &model : m_apModelAnime)
	{
		if (model)
		{
			model->SetRotCalculation(true);
		}
	}
}

//=============================================================================
// キャラクターの情報
//=============================================================================
void CCharacter::SetCharacterInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	m_pos = pos;
	m_rot = rot;
}