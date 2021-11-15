//=============================================================================
//
// チェックポイントクラス [check_point.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "check_point.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "check_flag.h"
#include "library.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CCheckPoint::CCheckPoint()
{
	m_apChackFlag.clear();
	m_nPointNum = -1;
	m_PointPos = {ZeroVector3};
}

//=============================================================================
// デストラクタ
//=============================================================================
CCheckPoint::~CCheckPoint()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CCheckPoint * CCheckPoint::Create(void)
{
	// メモリ確保
	CCheckPoint *pCheckPoint = new CCheckPoint;

	// !nullcheck
	if (pCheckPoint)
	{
		// 初期化処理
		pCheckPoint->Init();
		return pCheckPoint;
	}

	return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCheckPoint::Init(void)
{
	// 旗の生成
	CreateFlag();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCheckPoint::Uninit(void)
{
	if (m_apChackFlag.size() > 0)
	{
		for (auto &ChackFlag : m_apChackFlag)
		{
			// 終了処理
			ChackFlag->Uninit();
		}

		m_apChackFlag.clear();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CCheckPoint::Update(void)
{
	size_t size = m_apChackFlag.size();
	for (size_t nCount = m_nPointNum+1; nCount < size; nCount++)
	{
		// フラッグの当たり判定
		if (m_apChackFlag.at(nCount)->Collision())
		{
			m_PointPos = m_apChackFlag.at(nCount)->GetPos();
			m_nPointNum = nCount;
			break;
		}
	}

}

//=============================================================================
// 旗の生成
//=============================================================================
void CCheckPoint::CreateFlag()
{
	// 旗の生成
	m_apChackFlag.push_back(CCheckFlag::Create(ZeroVector3));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-3861.5f, 101.4f, -12821.2f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-18772.6f, 1030.4f, -18250.0f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-34715.7f, 981.2f, -13988.7f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-32843.1f, 960.5f, 5418.3f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-24373.2f, 107.3f, 14578.4f)));
}