//=============================================================================
//
// �񕜃N���X [heel.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "heel.h"
#include "heel_point.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "gauge.h"
#include "particleshrink_heel.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define HEEL_NUM        (1)    // �񕜂̒l

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CHeel::CHeel()
{
    m_apHeelPoint.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CHeel::~CHeel()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CHeel * CHeel::Create()
{
    // �������m��
    CHeel *pCheckPoint = new CHeel;

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
HRESULT CHeel::Init()
{
    // ���̐���
    CreateHeelPoint();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CHeel::Uninit()
{
    if (m_apHeelPoint.size() > 0)
    {
        // �I������
        for (auto &HeelPoint : m_apHeelPoint)
        {
            HeelPoint->Uninit();
        }
        m_apHeelPoint.clear();
    }
}

//=============================================================================
// �X�V����
//=============================================================================
void CHeel::Update()
{
    // �v���C���[�̈ʒu�擾
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    CGauge * pGauge = CManager::GetInstance()->GetGame()->GetGauge();
    if (!pPlayer)
    {
        return;
    }
    D3DXVECTOR3 pos = pPlayer->GetPos();

    for (auto &HeelPoint : m_apHeelPoint)
    {
        // �����蔻��
        if (HeelPoint->Collision())
        {
            // ��
            CManager::GetInstance()->GetPlayer()->SubLife(-HEEL_NUM);
            pGauge->SetDown((float)HEEL_NUM);
            pGauge->SetHitUp(true);
            // �v���C���[�̈ʒu�ɃG�t�F�N�g����
            CParticleHeel::Create(pos);
        }
    }
}

//=============================================================================
// ���̐���
//=============================================================================
void CHeel::CreateHeelPoint()
{
    // ���̐���
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(57761.4f, 1370.0f, 27879.0f)));
//    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-23408.0f, 107.3f, 15867.4f)));

    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(7223.2f, 5140.0f, -50789.8f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-28757.1f, 5310.0f, -55027.8f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-58786.7f, 5050.0f, -23108.5f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(1908.0f, 1750.0f, 67083.5f)));
}