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
#include "sound.h"

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
CCheckPoint * CCheckPoint::Create()
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
HRESULT CCheckPoint::Init()
{
	// ���̐���
	CreateFlag();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCheckPoint::Uninit()
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
void CCheckPoint::Update()
{
	size_t size = m_apChackFlag.size();
	for (size_t nCount = m_nPointNum+1; nCount < size; nCount++)
	{
		// �t���b�O�̓����蔻��
		if (m_apChackFlag.at(nCount)->Collision())
		{
			m_PointPos = m_apChackFlag.at(nCount)->GetPos();
			m_nPointNum = nCount;
            CLibrary::SetSound(CSound::SOUND_SE_CHECKPOINT);
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
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(54500.0f, 1200.0f, 25500.0f)));

	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(48483.7f, 1000.0f, -10885.5f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(21581.8f, 4950.0f, -48310.7f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(2572.5f, 4950.0f, -50047.8f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-30587.8f, 5200.0f, -53817.8f)));
	m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(-54192.9f, 4950.0f, -16407.5f)));
    m_apChackFlag.push_back(CCheckFlag::Create(D3DXVECTOR3(734.8f, 850.0f, 60978.5f)));
}