//=============================================================================
//
// メイン処理 [main.h]
// Author : Takahashi Naoyuki
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "skinmesh.h"
#include "animation.h"

TCHAR gName[] = _T("XFile Skin Mesh Animation");//windowネーム

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	if (mes == WM_DESTROY) { PostQuitMessage(0); return 0; }
	return DefWindowProc(hWnd, mes, wParam, lParam);
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// アプリケーションの初期化
	MSG msg; HWND hWnd;
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, NULL, NULL, (HBRUSH)(COLOR_WINDOW + 1), NULL, (TCHAR*)gName, NULL };
	if (!RegisterClassEx(&wcex))
		return 0;

	int sw = 600, sh = 600;
	RECT r = { 0, 0, sw, sh };
	::AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
	if (!(hWnd = CreateWindow(gName, gName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, r.right - r.left, r.bottom - r.top, NULL, NULL, hInstance, NULL)))
		return 0;

	// Direct3Dの初期化
	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pD3DDev;
	if (!(g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) return 0;

	D3DPRESENT_PARAMETERS d3dpp = { sw , sh, D3DFMT_X8R8G8B8, 0, D3DMULTISAMPLE_NONE, 0, D3DSWAPEFFECT_DISCARD, NULL, TRUE, TRUE, D3DFMT_D24S8, 0, 0, D3DPRESENT_INTERVAL_DEFAULT };

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev)))
	{
		g_pD3D->Release();
		return 0;
	}

	// スキンメッシュ情報をXファイル保存用
	SkinMesh::AllocateHierarchy allocater;
	SkinMesh::SMD3DXFRAME *pRootFrame = 0;
	ID3DXAnimationController *controller = 0;
	//メモリ確保
	std::shared_ptr<IHighLevelAnimController> HLcontroller(new IHighLevelAnimController);

	HRESULT model = D3DERR_WRONGTEXTUREFORMAT;

	model = D3DXLoadMeshHierarchyFromX(_T("resource/test_slime_model02.x"), D3DXMESH_MANAGED, g_pD3DDev, &allocater, 0, (D3DXFRAME**)&pRootFrame, &controller);

	if (model == D3DERR_INVALIDCALL)
	{
		return 0;
	}

	//アニメーションコントローラーのコピー
	HLcontroller->SetAnimationController(controller);
	// SMD3DXMESHCONTAINER(メッシュ)関連の情報を保存用
	std::vector<SkinMesh::SMD3DXMESHCONTAINER*> cont;

	//メッシュコンテナ取得関数
	SkinMesh::getMeshContainer(pRootFrame, &cont);

	//ボーンコンビネーションテーブルのポインタ取得
	std::vector<D3DXBONECOMBINATION*> combs;

	for (int i = 0; i < cont.size(); i++)
	{
		combs.push_back((D3DXBONECOMBINATION*)cont[i]->boneCombinationTable->GetBufferPointer());

		// フレーム内にボーンIDとオフセット行列を埋め込む
		SkinMesh::setFrameId(pRootFrame, cont[i]->pSkinInfo);
	}

	// テクスチャ作成
	//IDirect3DTexture9 *tex = 0;
	//D3DXCreateTextureFromFile(g_pD3DDev, _T("resource/Tiny_skin.dds"), &tex);

	// ビュー、射影変換行列設定
	D3DXMATRIX world, view, proj;
	D3DXMatrixIdentity(&world);
	D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(0.0f, 0.0f, 2000.0f), &D3DXVECTOR3(0.0f, -100.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(30.0f), 1.0f, 0.01f, 10000000.0f);
	g_pD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pD3DDev->SetTransform(D3DTS_VIEW, &view);
	g_pD3DDev->SetTransform(D3DTS_PROJECTION, &proj);

	ShowWindow(hWnd, nCmdShow);
	// メッセージ ループ

	//現在フレーム(fps)のワールド変換行列
	std::map<DWORD, D3DXMATRIX> combMatrixMap;

	//ループ時間
	HLcontroller->SetLoopTime(1, 100);
	HLcontroller->SetLoopTime(0, 100);

	//アニメーション変更
	HLcontroller->ChangeAnimation(0);

	//アニメーションのシフトにかかる時間
	HLcontroller->SetShiftTime(1, 100);
	HLcontroller->SetShiftTime(0, 100);

	HLcontroller->ChangeAnimation(1);

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);
		}
		else
		{
			static int hoge = 0;

			hoge++;

			if (hoge == 1000)
			{
				HLcontroller->ChangeAnimation(0);
			}

			//// 時間を進めて姿勢更新
			//controller->AdvanceTime(0.00001f, 0);
			//controller->SetTrackAnimationSet(0, 0);

			////controller->GetMaxNumAnimationOutputs();
			////controller->GetMaxNumAnimationSets();
			////controller->GetMaxNumTracks();
			////controller->GetMaxNumEvents();

			updateCombMatrix(combMatrixMap, pRootFrame);

			// Direct3Dの処理
			g_pD3DDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 0, 255), 1.0f, 0);
			g_pD3DDev->BeginScene();
			//g_pD3DDev->SetTexture(0, tex);

			//アニメーション更新
			HLcontroller->AdvanceTime(1);

			for (DWORD BCombiId = 0; BCombiId < cont.size(); BCombiId++)
			{
				for (DWORD AttribId = 0; AttribId < cont[BCombiId]->numBoneCombinations; AttribId++)
				{
					DWORD boneCount = 0;

					for (DWORD Count = 0; Count < cont[BCombiId]->maxFaceInfl; Count++)
					{
						//ボーンコンビネーションテーブルからボーンIDを抽出
						DWORD BoneId = combs[BCombiId][AttribId].BoneId[Count];

						//ボーンIDが存在している
						if (BoneId != UINT_MAX)
						{
							// インデックス付きワールドマトリックスの設定
							g_pD3DDev->SetTransform(D3DTS_WORLDMATRIX(Count), &combMatrixMap[BoneId]);
							boneCount++;
						}
					}

					for (int nCntMat = 0; nCntMat < (int)cont[BCombiId]->NumMaterials; nCntMat++)
					{
						//マテリアルの設定
						g_pD3DDev->SetMaterial(&cont[BCombiId]->pMaterials->MatD3D);
					}

					g_pD3DDev->SetRenderState(D3DRS_VERTEXBLEND, boneCount - 1);

					//メッシュコンテナ内のメッシュデータ
					cont[BCombiId]->MeshData.pMesh->DrawSubset(AttribId);

				}
			}

			g_pD3DDev->EndScene();
			g_pD3DDev->Present(NULL, NULL, NULL, NULL);
		}
	} while (msg.message != WM_QUIT);

	// スキンメッシュ情報削除
	allocater.DestroyFrame(pRootFrame);

	//tex->Release();

	g_pD3DDev->Release();
	g_pD3D->Release();

	return 0;
}