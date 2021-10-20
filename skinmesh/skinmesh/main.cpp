//=============================================================================
//
// ���C������ [main.h]
// Author : Takahashi Naoyuki
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "skinmesh.h"
#include "animation.h"

TCHAR gName[] = _T("XFile Skin Mesh Animation");//window�l�[��

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	if (mes == WM_DESTROY) { PostQuitMessage(0); return 0; }
	return DefWindowProc(hWnd, mes, wParam, lParam);
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// �A�v���P�[�V�����̏�����
	MSG msg; HWND hWnd;
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, NULL, NULL, (HBRUSH)(COLOR_WINDOW + 1), NULL, (TCHAR*)gName, NULL };
	if (!RegisterClassEx(&wcex))
		return 0;

	int sw = 600, sh = 600;
	RECT r = { 0, 0, sw, sh };
	::AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
	if (!(hWnd = CreateWindow(gName, gName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, r.right - r.left, r.bottom - r.top, NULL, NULL, hInstance, NULL)))
		return 0;

	// Direct3D�̏�����
	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pD3DDev;
	if (!(g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) return 0;

	D3DPRESENT_PARAMETERS d3dpp = { sw , sh, D3DFMT_X8R8G8B8, 0, D3DMULTISAMPLE_NONE, 0, D3DSWAPEFFECT_DISCARD, NULL, TRUE, TRUE, D3DFMT_D24S8, 0, 0, D3DPRESENT_INTERVAL_DEFAULT };

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev)))
	{
		g_pD3D->Release();
		return 0;
	}

	// �X�L�����b�V������X�t�@�C���ۑ��p
	SkinMesh::AllocateHierarchy allocater;
	SkinMesh::SMD3DXFRAME *pRootFrame = 0;
	ID3DXAnimationController *controller = 0;
	//�������m��
	std::shared_ptr<IHighLevelAnimController> HLcontroller(new IHighLevelAnimController);

	HRESULT model = D3DERR_WRONGTEXTUREFORMAT;

	model = D3DXLoadMeshHierarchyFromX(_T("resource/test_slime_model02.x"), D3DXMESH_MANAGED, g_pD3DDev, &allocater, 0, (D3DXFRAME**)&pRootFrame, &controller);

	if (model == D3DERR_INVALIDCALL)
	{
		return 0;
	}

	//�A�j���[�V�����R���g���[���[�̃R�s�[
	HLcontroller->SetAnimationController(controller);
	// SMD3DXMESHCONTAINER(���b�V��)�֘A�̏���ۑ��p
	std::vector<SkinMesh::SMD3DXMESHCONTAINER*> cont;

	//���b�V���R���e�i�擾�֐�
	SkinMesh::getMeshContainer(pRootFrame, &cont);

	//�{�[���R���r�l�[�V�����e�[�u���̃|�C���^�擾
	std::vector<D3DXBONECOMBINATION*> combs;

	for (int i = 0; i < cont.size(); i++)
	{
		combs.push_back((D3DXBONECOMBINATION*)cont[i]->boneCombinationTable->GetBufferPointer());

		// �t���[�����Ƀ{�[��ID�ƃI�t�Z�b�g�s��𖄂ߍ���
		SkinMesh::setFrameId(pRootFrame, cont[i]->pSkinInfo);
	}

	// �e�N�X�`���쐬
	//IDirect3DTexture9 *tex = 0;
	//D3DXCreateTextureFromFile(g_pD3DDev, _T("resource/Tiny_skin.dds"), &tex);

	// �r���[�A�ˉe�ϊ��s��ݒ�
	D3DXMATRIX world, view, proj;
	D3DXMatrixIdentity(&world);
	D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(0.0f, 0.0f, 2000.0f), &D3DXVECTOR3(0.0f, -100.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(30.0f), 1.0f, 0.01f, 10000000.0f);
	g_pD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pD3DDev->SetTransform(D3DTS_VIEW, &view);
	g_pD3DDev->SetTransform(D3DTS_PROJECTION, &proj);

	ShowWindow(hWnd, nCmdShow);
	// ���b�Z�[�W ���[�v

	//���݃t���[��(fps)�̃��[���h�ϊ��s��
	std::map<DWORD, D3DXMATRIX> combMatrixMap;

	//���[�v����
	HLcontroller->SetLoopTime(1, 100);
	HLcontroller->SetLoopTime(0, 100);

	//�A�j���[�V�����ύX
	HLcontroller->ChangeAnimation(0);

	//�A�j���[�V�����̃V�t�g�ɂ����鎞��
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

			//// ���Ԃ�i�߂Ďp���X�V
			//controller->AdvanceTime(0.00001f, 0);
			//controller->SetTrackAnimationSet(0, 0);

			////controller->GetMaxNumAnimationOutputs();
			////controller->GetMaxNumAnimationSets();
			////controller->GetMaxNumTracks();
			////controller->GetMaxNumEvents();

			updateCombMatrix(combMatrixMap, pRootFrame);

			// Direct3D�̏���
			g_pD3DDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 0, 255), 1.0f, 0);
			g_pD3DDev->BeginScene();
			//g_pD3DDev->SetTexture(0, tex);

			//�A�j���[�V�����X�V
			HLcontroller->AdvanceTime(1);

			for (DWORD BCombiId = 0; BCombiId < cont.size(); BCombiId++)
			{
				for (DWORD AttribId = 0; AttribId < cont[BCombiId]->numBoneCombinations; AttribId++)
				{
					DWORD boneCount = 0;

					for (DWORD Count = 0; Count < cont[BCombiId]->maxFaceInfl; Count++)
					{
						//�{�[���R���r�l�[�V�����e�[�u������{�[��ID�𒊏o
						DWORD BoneId = combs[BCombiId][AttribId].BoneId[Count];

						//�{�[��ID�����݂��Ă���
						if (BoneId != UINT_MAX)
						{
							// �C���f�b�N�X�t�����[���h�}�g���b�N�X�̐ݒ�
							g_pD3DDev->SetTransform(D3DTS_WORLDMATRIX(Count), &combMatrixMap[BoneId]);
							boneCount++;
						}
					}

					for (int nCntMat = 0; nCntMat < (int)cont[BCombiId]->NumMaterials; nCntMat++)
					{
						//�}�e���A���̐ݒ�
						g_pD3DDev->SetMaterial(&cont[BCombiId]->pMaterials->MatD3D);
					}

					g_pD3DDev->SetRenderState(D3DRS_VERTEXBLEND, boneCount - 1);

					//���b�V���R���e�i���̃��b�V���f�[�^
					cont[BCombiId]->MeshData.pMesh->DrawSubset(AttribId);

				}
			}

			g_pD3DDev->EndScene();
			g_pD3DDev->Present(NULL, NULL, NULL, NULL);
		}
	} while (msg.message != WM_QUIT);

	// �X�L�����b�V�����폜
	allocater.DestroyFrame(pRootFrame);

	//tex->Release();

	g_pD3DDev->Release();
	g_pD3D->Release();

	return 0;
}