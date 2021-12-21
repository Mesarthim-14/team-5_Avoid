//=============================================================================
//
// �N���[�P���G��N���X [kraken_tentacles.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "kraken_tentacles.h"
#include "animation_skinmesh.h"
#include "skinmesh_model.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SIZE            (D3DXVECTOR3(3200.0f, 7500.0f, 3200.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKrakenTentacles::CKrakenTentacles(PRIORITY Priority) : CScene(Priority)
{
    m_pSkinmeshModel = nullptr;
    m_pos = ZeroVector3;
    m_rot = ZeroVector3;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKrakenTentacles::~CKrakenTentacles()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CKrakenTentacles * CKrakenTentacles::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    // �������m��
    CKrakenTentacles *pTentacles = new CKrakenTentacles(PRIORITY_MODEL);
    if (pTentacles)
    {
        pTentacles->SetTentaclesInfo(pos, rot);
        pTentacles->Init();
        return pTentacles;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CKrakenTentacles::Init()
{
    // ���f���̐���
    CreateModel();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CKrakenTentacles::Uninit()
{
    if (m_pSkinmeshModel)
    {
        m_pSkinmeshModel->Uninit();
        m_pSkinmeshModel = nullptr;
    }

    Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CKrakenTentacles::Update()
{
    if (m_pSkinmeshModel)
    {
        m_pSkinmeshModel->SetPos(m_pos);
        m_pSkinmeshModel->SetRot(m_rot);
    }
}


//=============================================================================
// ���f���̐���
//=============================================================================
void CKrakenTentacles::CreateModel()
{
    m_pSkinmeshModel = CSkinmeshModel::Create(m_pos, m_rot, CSkinmeshModel::MODEL_ENEMY_KRAKEN_TENTACLESD);
    if (m_pSkinmeshModel)
    {
        CTexture* pTexture = GET_TEXTURE_PTR;
        m_pSkinmeshModel->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_KRAKEN));
        m_pSkinmeshModel->IsDraw(true);

        // ���f���̏�񕪂���Ȃ�
        m_pSkinmeshModel->GetHLcontroller()->ChangeAnimation(0);
        m_pSkinmeshModel->GetHLcontroller()->SetLoopTime(0, 60);
        m_pSkinmeshModel->GetHLcontroller()->SetShiftTime(0, 60);
    }

}

//=============================================================================
// �G��̊�{���ݒ�
//=============================================================================
void CKrakenTentacles::SetTentaclesInfo(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & rot)
{
    m_pos = pos;
    m_rot = rot;
}