//=============================================================================
//
// シーンベースクラス [scene_base.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene_base.h"
#include "texture_animation.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSceneBase::CSceneBase(PRIORITY Priority):CScene(Priority)
{
	m_pos = ZeroVector3;
	m_size = ZeroVector3;
	m_col = WhiteColor;
	m_rot = ZeroVector3;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_pTextureAnimation = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneBase::~CSceneBase()
{
	// !nullcheck
	if (m_pVtxBuff)
	{
		//頂点バッファの開放
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// テクスチャアニメーションの終了処理
	if (m_pTextureAnimation)
	{
		delete m_pTextureAnimation;
		m_pTextureAnimation = nullptr;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneBase::Uninit()
{
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneBase::Update()
{
	// テクスチャアニメーションの更新処理
	if (m_pTextureAnimation)
	{
		// アニメーション更新
		m_pTextureAnimation->Update();

		// アニメーション座標に更新があったら
		if (m_pTextureAnimation->GetUpdate())
		{
			// テクスチャ座標の更新
			this->UpdateAnimation();
			m_pTextureAnimation->SetUpdateFlag(false);
		}
	}
}

//=============================================================================
// シーン情報の設定
//=============================================================================
void CSceneBase::SetSceneInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	m_pos = pos;
	m_size = size;
}
