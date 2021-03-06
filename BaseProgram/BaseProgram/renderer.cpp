//=============================================================================
//
// レンダラー処理 [renderer.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "renderer.h"
#include "scene.h"
#include "fade.h"
#include "manager.h"
#include "camera.h"
#include "game.h"
#include "keyboard.h"
#include "polygon.h"
#include "shadow.h"
#include "library.h"
#include "pause.h"
#include "toon_shader.h"
#include "shock_blur.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FOG_COLOR (D3DCOLOR_RGBA(45, 45, 45, 0))

//=============================================================================
// レンダリングクラスのコンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;			// Direct3Dオブジェクト
	m_fillMode = D3DFILL_SOLID;
    m_pToonShader = nullptr;
    m_pShockBlur = nullptr;
    m_bShockBlur = false;

}

//=============================================================================
// レンダリングクラスのデストラクタ
//=============================================================================
CRenderer::~CRenderer()
{

}

//=============================================================================
// レンダリングクラスの初期化処理
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ
	D3DDISPLAYMODE d3ddm;	//ディスプレイモード

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

	m_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3DInterface == nullptr)
	{
		// 作成失敗

		return E_FAIL;
	}


	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,				// D3DDEVTYPE_HAL：ハードウェアでラスタ化とシェーディングを行い、(座標変換と照明計算)を行う
		D3DDEVTYPE_HAL,												// D3DDEVTYPE_REF:リファレンスラスタライザ。ドライバのバグをチェックできる
		hWnd,														// D3DCREATE_PUREDEVICE                :ラスタ化、座標変換、照明計算、シェーディングを指定、上のフラグの修飾子
		D3DCREATE_HARDWARE_VERTEXPROCESSING,						// D3DCREATE_SOFTWARE_VERTEXPROCESSING：ソフトウェアによる頂点処理を指定
		&d3dpp, &m_pD3DDevice)))									// D3DCREATE_HARDWARE_VERTEXPROCESSING：ハードウェアによる頂点処理。
	{																// D3DCREATE_MIXED_VERTEXPROCESSING   ：ミックス(ソフトウェアとハードウェアの両方)による頂点処理を指定します。

		// 上記の設定が失敗したら								
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// 裏面を（左回り）をカリング
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);							// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの設定

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// テクスチャのU値の繰り返し
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// テクスチャのV値の繰り返し
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// テクスチャ拡大時の補完設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// テクスチャ縮小時の補完設定

	//フォグの設定
	float fStart = 1000.0f;
	float fEnd = 3500.0f;
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, FOG_COLOR);					// カラー設定
	m_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);				// 頂点モード
	m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);			// テーブルモード
	m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fStart));			// 開始位置
	m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fEnd));				// 終了位置

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// アルファブレンディング処理
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// 最初のアルファ引数（初期値）
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// 2番目のアルファ引数（初期値）

	//環境光
	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	m_pD3DDevice->SetMaterial(&material);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

    // トゥーンシェーダ
    if (!m_pToonShader)
    {
        m_pToonShader = new CToonShader(m_pD3DDevice);
        m_pToonShader->Init();
    }
    if (!m_pShockBlur)
    {
        m_pShockBlur = new CShockBlur(m_pD3DDevice, SCREEN_WIDTH, SCREEN_HEIGHT);
        m_pShockBlur->Load();
    }
	return S_OK;
}

//=============================================================================
// レンダリングクラスの終了処理
//=============================================================================
void CRenderer::Uninit()
{
    if (m_pToonShader)
    {
        m_pToonShader->Uninit();
        m_pToonShader = nullptr;
    }
    if (m_pShockBlur)
    {
        m_pShockBlur->Uninit();
        m_pShockBlur = nullptr;
    }
	// デバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=============================================================================
// レンダリングクラスの更新処理
//=============================================================================
void CRenderer::Update()
{
#ifdef _DEBUG

	//ImGuiの更新
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

#endif	//DEBUG

	// 全ての更新
	CScene::UpdateAll();
#ifdef _DEBUG

	//情報
//	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
//	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

	//デバッグのコマンド
	CLibrary::ShowDebugInfo();
	//レンダラー関係の終了
//	ImGui::End();

	//ポップの色情報初期化
//	ImGui::PopStyleColor();
//	ImGui::PopStyleColor();

//	ImGui::EndFrame();//更新処理の終わりに

#endif	//DEBUG

	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();
	
	// ポリゴンの表示
	if (pKeyboard->GetTrigger(DIK_M))
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ

		switch (m_fillMode)
		{
		case D3DFILL_SOLID:
			m_fillMode = D3DFILL_WIREFRAME;
			break;
		case D3DFILL_WIREFRAME:
			m_fillMode = D3DFILL_SOLID;
			break;
		}

		pDevice->SetRenderState(D3DRS_FILLMODE, m_fillMode);
	}
}

//=============================================================================
// レンダリングクラスの描画処理
//=============================================================================
void CRenderer::Draw()
{
    m_pD3DDevice->Clear(0,
        nullptr,
        (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
        D3DCOLOR_RGBA(0, 0, 0, 0),
        1.0f,
        0);

    m_pD3DDevice->Clear(0,
        nullptr,
        D3DCLEAR_STENCIL,
        D3DCOLOR_XRGB(0, 0, 0),
        1.0f,
        0);

    // Direct3Dによる描画の開始
    if (SUCCEEDED(m_pD3DDevice->BeginScene()))
    {
        // 射影行列/ビュー/ワールド
        D3DXMATRIX matProj, matView, matWorld;
        D3DXMATRIX trans;

        if (CManager::GetInstance()->GetCamera() != nullptr)
        {
            // カメラのポインタ取得
            CCamera *pCamera = CManager::GetInstance()->GetCamera();

            // カメラが使われていたら
            if (pCamera != nullptr)
            {
                pCamera->SetCamera();
            }
        }


        // フィルタの開始
        CGame::BeginGauss();

        if (m_bShockBlur)
        {
            m_pShockBlur->Begin();
        }

        //オブジェクトクラスの全描画処理呼び出し
        CScene::DrawAll3D();

        if (m_bShockBlur)
        {
            m_pShockBlur->Draw();
        }

        // フィルタの終了
        CGame::EndGauss();

        CScene::DrawAll2D();

        CFade *pFade = CManager::GetInstance()->GetFade();

        if (pFade != nullptr)
        {
            // 描画処理
            pFade->Draw();
        }
        // ポーズ状態の時
        if (CManager::GetInstance()->GetMode() == CManager::MODE_TYPE_GAME&&CManager::GetActivePause())
        {
            // ポーズメニューの表示
            CManager::GetInstance()->GetPause()->Draw();
        }
#ifdef _DEBUG
        //ImGuiの情報表示する時
        if (m_bDispImGuiInfo)
        {
            //通常描画
            m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

            //ImGui描画
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

            //ワイヤーフレーム描画の時は元に戻す
            CLibrary::CheckWireMode();
        }
#endif	//DEBUG


        // Direct3Dによる描画の終了
        m_pD3DDevice->EndScene();
    }

    // バックバッファとフロントバッファの入れ替え
    m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//=============================================================================
// ブラーの設定
//=============================================================================
void CRenderer::SetShockBlur(const bool & bFlag, const float & fPower)
{
    m_bShockBlur = bFlag;
    m_pShockBlur->SetBlurPower(fPower);
}
