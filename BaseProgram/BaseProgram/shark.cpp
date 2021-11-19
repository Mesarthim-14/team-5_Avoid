//=============================================================================
//
// サメクラス [shark.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "shark.h"
#include "shark_model.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ATTACK_INTER	(150)									// 攻撃間隔
#define ATTACK_STR		(20)									// 攻撃力
#define ATTACK_POWER	(2.0f)									// 吹っ飛ばし力
#define SPEED			(130.0f)								// スピード
#define POS				(D3DXVECTOR3(-3500.0f, -200.0f, 0.0f))	// 座標

//=============================================================================
// コンストラクタ
//=============================================================================
CShark::CShark(PRIORITY Priority) : CWimpEnemy(Priority)
{
	m_pSharkModel = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CShark::~CShark()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CShark * CShark::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // メモリ確保
    CShark *pShark = new CShark;
    if (pShark)
    {
        // 初期化処理
        pShark->Init(pos, rot);
        return pShark;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShark::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    CWimpEnemy::Init();
    SetAttackInfo(ATTACK_INTER, ATTACK_STR, ATTACK_POWER);
    SetCharacterInfo(pos, rot);
    SetSpeed(SPEED);

    // モデル生成
    CreateModel();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CShark::Uninit()
{
	// モデル更新処理
	if (m_pSharkModel)
	{
		m_pSharkModel->Uninit();
	}
	CWimpEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CShark::Update()
{
	CWimpEnemy::Update();

	// モデル更新処理
	if (m_pSharkModel)
	{
		m_pSharkModel->SetPos(GetPos());
	}
}

//=============================================================================
// モデルの生成
//=============================================================================
void CShark::CreateModel()
{
	// モデル生成
	if (!m_pSharkModel)
	{
		m_pSharkModel = CSharkModel::Create(GetPos());
	}
}

//=============================================================================
// 攻撃関数
//=============================================================================
void CShark::Attack()
{
	// 追従攻撃
	Rush();
}