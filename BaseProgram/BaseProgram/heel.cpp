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
#include "particleshrink.h"

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
    D3DXVECTOR3 pos = pPlayer->GetPos();

    for (auto &HeelPoint : m_apHeelPoint)
    {
        // �����蔻��
        if (HeelPoint->Collision())
        {
            // ��
            CManager::GetInstance()->GetPlayer()->SubLife(-HEEL_NUM);
            CGauge::SetDown((float)HEEL_NUM);
            CGauge::SetHitUp(true);
            // �v���C���[�̈ʒu�ɃG�t�F�N�g����
            CParticleShrink::Create(pos);
        }
    }
}

//=============================================================================
// ���̐���
//=============================================================================
void CHeel::CreateHeelPoint()
{
    // ���̐���
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-1546.4f, 100.0f, -0.0f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-4587.7f, 87.3f, -12224.9f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-19864.6f, 1030.4f, -18272.0f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-34715.7f, 981.2f, -13988.7f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-32146.7f, 1006.5f, 5995.2f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-23408.0f, 107.3f, 15867.4f)));
}