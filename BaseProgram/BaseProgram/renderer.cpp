//=============================================================================
//
// �����_���[���� [renderer.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
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

//=============================================================================
// �}�N����`
//=============================================================================
#define FOG_COLOR (D3DCOLOR_RGBA(45, 45, 45, 0))

//=============================================================================
// �����_�����O�N���X�̃R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;			// Direct3D�I�u�W�F�N�g
	m_fillMode = D3DFILL_SOLID;
}

//=============================================================================
// �����_�����O�N���X�̃f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{

}

//=============================================================================
// �����_�����O�N���X�̏���������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^
	D3DDISPLAYMODE d3ddm;	//�f�B�X�v���C���[�h

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

	m_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3DInterface == nullptr)
	{
		// �쐬���s

		return E_FAIL;
	}


	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,				// D3DDEVTYPE_HAL�F�n�[�h�E�F�A�Ń��X�^���ƃV�F�[�f�B���O���s���A(���W�ϊ��ƏƖ��v�Z)���s��
		D3DDEVTYPE_HAL,												// D3DDEVTYPE_REF:���t�@�����X���X�^���C�U�B�h���C�o�̃o�O���`�F�b�N�ł���
		hWnd,														// D3DCREATE_PUREDEVICE                :���X�^���A���W�ϊ��A�Ɩ��v�Z�A�V�F�[�f�B���O���w��A��̃t���O�̏C���q
		D3DCREATE_HARDWARE_VERTEXPROCESSING,						// D3DCREATE_SOFTWARE_VERTEXPROCESSING�F�\�t�g�E�F�A�ɂ�钸�_�������w��
		&d3dpp, &m_pD3DDevice)))									// D3DCREATE_HARDWARE_VERTEXPROCESSING�F�n�[�h�E�F�A�ɂ�钸�_�����B
	{																// D3DCREATE_MIXED_VERTEXPROCESSING   �F�~�b�N�X(�\�t�g�E�F�A�ƃn�[�h�E�F�A�̗���)�ɂ�钸�_�������w�肵�܂��B

		// ��L�̐ݒ肪���s������								
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// ���ʂ��i�����j���J�����O
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);							// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̐ݒ�

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// �e�N�X�`����U�l�̌J��Ԃ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// �e�N�X�`����V�l�̌J��Ԃ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���g�厞�̕⊮�ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���k�����̕⊮�ݒ�

	//�t�H�O�̐ݒ�
	float fStart = 1000.0f;
	float fEnd = 3500.0f;
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, FOG_COLOR);					// �J���[�ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);				// ���_���[�h
	m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);			// �e�[�u�����[�h
	m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fStart));			// �J�n�ʒu
	m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fEnd));				// �I���ʒu

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// �A���t�@�u�����f�B���O����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// �ŏ��̃A���t�@�����i�����l�j
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// 2�Ԗڂ̃A���t�@�����i�����l�j

	//����
	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	m_pD3DDevice->SetMaterial(&material);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	return S_OK;
}

//=============================================================================
// �����_�����O�N���X�̏I������
//=============================================================================
void CRenderer::Uninit(void)
{
	// �f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=============================================================================
// �����_�����O�N���X�̍X�V����
//=============================================================================
void CRenderer::Update(void)
{
#ifdef _DEBUG

	//ImGui�̍X�V
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

#endif	//DEBUG

	// �S�Ă̍X�V
	CScene::UpdateAll();
#ifdef _DEBUG

	//���
//	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
//	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

	//�f�o�b�O�̃R�}���h
	CLibrary::ShowDebugInfo();
	//�����_���[�֌W�̏I��
//	ImGui::End();

	//�|�b�v�̐F��񏉊���
//	ImGui::PopStyleColor();
//	ImGui::PopStyleColor();

//	ImGui::EndFrame();//�X�V�����̏I����

#endif	//DEBUG

	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();
	
	// �|���S���̕\��
	if (pKeyboard->GetTrigger(DIK_M))
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^

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
// �����_�����O�N���X�̕`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	m_pD3DDevice->Clear(0, 
		nullptr, 
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), 
		D3DCOLOR_RGBA(0, 255, 255, 0), 
		1.0f, 
		0);

	m_pD3DDevice->Clear(0,
		nullptr,
		D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �ˉe�s��/�r���[/���[���h
		D3DXMATRIX matProj, matView, matWorld;
		D3DXMATRIX trans;

		if (CManager::GetInstance()->GetCamera() != nullptr)
		{
			// �J�����̃|�C���^�擾
			CCamera *pCamera = CManager::GetInstance()->GetCamera();

			// �J�������g���Ă�����
			if (pCamera != nullptr)
			{
				pCamera->SetCamera();
			}
		}

		//�I�u�W�F�N�g�N���X�̑S�`�揈���Ăяo��
		CScene::DrawAll();
		
		CFade *pFade = CManager::GetInstance()->GetFade();

		if (pFade != nullptr)
		{
			// �`�揈��
			pFade->Draw();
		}

		if (CManager::GetInstance()->GetMode() == CManager::MODE_TYPE_GAME&&CManager::GetActivePause())
		{// �|�[�Y��Ԃ̎�
		 // �|�[�Y���j���[�̕\��
			CManager::GetInstance()->GetPause()->Draw();
		}
#ifdef _DEBUG
		//ImGui�̏��\�����鎞
		if (m_bDispImGuiInfo)
		{
			//�ʏ�`��
			m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			//ImGui�`��
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

			//���C���[�t���[���`��̎��͌��ɖ߂�
			CLibrary::CheckWireMode();

#endif	//DEBUG

		}


		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//=============================================================================
// �f�o�C�X�̎擾����
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}