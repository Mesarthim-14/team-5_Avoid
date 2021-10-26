//=============================================================================CGround
//
// �n�ʃN���X [ground.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "ground.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SIZE (D3DXVECTOR3(1000.0f, 0.0f, 1000.0f))
#define GROUND_VERTEX_NUM (INT_VERTEX_2D{5, 5})

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGround::CGround(PRIORITY Priority) : CMeshField(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGround::~CGround()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CGround * CGround::Create(void)
{
	// �������m��
	CGround *pPolygon = new CGround(PRIORITY_UI);

	// !nullcheck
	if (pPolygon)
	{
		// ����������
		pPolygon->Init();

		return pPolygon;
	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGround::Init(void)
{
	// ����������
	SetInfo(SIZE, GROUND_VERTEX_NUM);
	CMeshField::Init();
	CTexture *pTexture = GET_TEXTURE_PTR;
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TEST));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGround::Uninit(void)
{
	CMeshField::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGround::Update(void)
{
	CMeshField::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGround::Draw(void)
{
	CMeshField::Draw();
}