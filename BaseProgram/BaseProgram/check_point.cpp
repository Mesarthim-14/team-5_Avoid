//=============================================================================
//
// �`�F�b�N�|�C���g�N���X [check_point.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
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
// �}�N����`
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCheckPoint::CCheckPoint()
{
	m_apChackFlag.clear();
	m_nPointNum = -1;
	m_PointPos = {ZeroVector3};
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCheckPoint::~CCheckPoint()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCheckPoint * CCheckPoint::Create(void)
{
	// �������m��
	CCheckPoint *pCheckPoint = new CCheckPoint;

	// !nullcheck
	if (pCheckPoint)
	{
		// ����������
		pCheckPoint->Init();
		return pCheckPoint;
	}

	return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCheckPoint::Init(void)
{
	// ���̐���
	CreateFlag();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCheckPoint::Uninit(void)
{
	if (m_apChackFlag.size() > 0)
	{
		for (auto &ChackFlag : m_apChackFlag)
		{
			// �I������
			ChackFlag->Uninit();
		}

		m_apChackFlag.clear();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CCheckPoint::Update(void)
{
	size_t size = m_apChackFlag.size();
	for (size_t nCount = m_nPointNum+1; nCount < size; nCount++)
	{
		// �t���b�O�̓����蔻��
		if (m_apChackFlag.at(nCount)->Collision())
		{
			m_PointPos = m_apChackFlag.at(nCount)->GetPos();
			m_nPointNum = nCount;
			break;
		}
	}

}

//=============================================================================
// ���̐���
//=============================================================================
void CCheckPoint::CreateFlag()
{
	// ���̐���
	m_apChackFlag.push_back(CCheckFlag::Create(ZeroVector3));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-3861.5f, 101.4f, -12821.2f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-18772.6f, 1030.4f, -18250.0f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-34715.7f, 981.2f, -13988.7f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-32843.1f, 960.5f, 5418.3f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-24373.2f, 107.3f, 14578.4f)));
}