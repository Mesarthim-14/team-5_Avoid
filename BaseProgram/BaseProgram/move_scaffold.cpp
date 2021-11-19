//=============================================================================CMoveScaffold
//
// ��������N���X [move_scaffold.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "move_scaffold.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS		(D3DXVECTOR3(-30637.0f, 0.0f, 8337.8f))
#define TEST_ROT		(D3DXVECTOR3(0.0f, D3DXToRadian(135.0f), 0.0f))
#define TURN_TIME		(800.0f)	// ���]�܂ł̃J�E���g
#define SPEED			(8.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMoveScaffold::CMoveScaffold(PRIORITY Priority) : CModel(Priority)
{
	m_nTime = 0;
	m_fSpeed = SPEED;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMoveScaffold::~CMoveScaffold()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CMoveScaffold * CMoveScaffold::Create()
{
	// �������m��
	CMoveScaffold *pTestModel = new CMoveScaffold(PRIORITY_TEST_MODEL);

	// !nullcheck
	if (pTestModel)
	{
		// ����������
		pTestModel->Init();

		return pTestModel;
	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMoveScaffold::Init()
{
	// ����������
	CModel::Init();

	CXfile *pXfile = GET_XFILE_PTR;
	CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_MOVE_SCAFFOLD);
	GetModelInfo()->SetModelStatus(TEST_POS, TEST_ROT, model);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMoveScaffold::Uninit()
{
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMoveScaffold::Update()
{
	// �ړ�����
	Move();

	CModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMoveScaffold::Draw()
{
	CModel::Draw();
}

//=============================================================================
// �ړ�����
//=============================================================================
void CMoveScaffold::Move()
{
	m_nTime++;
	
	float fAngle = GetModelInfo()->GetRot().y;

	// �ړ��ʐݒ�
	D3DXVECTOR3 move = D3DXVECTOR3(
		cosf(D3DXToRadian(fAngle+45.0f))*m_fSpeed, 
		0.0f, sinf(D3DXToRadian(fAngle + 45.0f))*m_fSpeed);

	// �ړ��ʐݒ�
	SetMove(move);

	// ��莞�Ԃ�
	if (m_nTime >= TURN_TIME)
	{
		m_nTime = 0;
		m_fSpeed *= -1;
	}
}