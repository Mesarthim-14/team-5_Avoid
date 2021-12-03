//=======================================================================================
//
// �Q�[������ [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "joypad.h"
#include "sound.h"
#include "keyboard.h"
#include "resource_manager.h"
#include "fade.h"
#include "test_2d.h"
#include "test_model.h"
#include "test_character.h"
#include "ground.h"
#include "skinmesh_model.h"
#include "library.h"
#include "check_point.h"
#include "water_fresnel.h"
#include "shark.h"
#include "marlin.h"
#include "ghost.h"
#include "gimmick_factory.h"
#include "kraken.h"
#include "sky.h"
#include "gauge.h"
#include "gaugebar.h"
#include "npc_enemy_info.h"
#include "npc_factory.h"
#include "gauss_filter.h"
#include "state_player_not_move.h"
#include "state_kraken_not_attack.h"
#include "camera_game.h"
#include "state_camera_descent.h"
#include "pause.h"

float CGame::m_fGravity = 1.5f;
CGaussFilter* CGame::m_pGaussFilter = nullptr;
bool CGame::m_bGaussFilter = true;

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{
    m_pPlayer = nullptr;
    m_bGameEnd = false;
    m_pFont = nullptr;
    m_pGimmickFactory = nullptr;
    m_pKraken = nullptr;
    m_pNpcFactory = nullptr;
    m_pPause = nullptr;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{
    // �I������
    Uninit();
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init()
{
    CreateFilter();
    CreateObject();
    return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit()
{
    // �v���C���[�̏I������
    if (m_pPlayer)
    {
        m_pPlayer->Uninit();
        m_pPlayer = nullptr;
    }
    if (m_pKraken)
    {
        m_pKraken->Uninit();
        m_pKraken = nullptr;
    }
    if (m_pNpcFactory)
    {
        m_pNpcFactory->Uninit();
        m_pNpcFactory = nullptr;
    }

    // �f�o�b�O���\���p�t�H���g�̔j��
    if (m_pFont)
    {
        m_pFont->Release();
        m_pFont = nullptr;
    }
    if (m_pGimmickFactory)
    {
        m_pGimmickFactory->Uninit();
        delete m_pGimmickFactory;
        m_pGimmickFactory = nullptr;
    }
    if (m_pGaussFilter)
    {
        m_pGaussFilter->Uninit();
        m_pGaussFilter = nullptr;
    }
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update()
{
    CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();

    //if (pKey->GetTrigger(DIK_ESCAPE))
    //{
    //    m_pPause = CManager::GetInstance()->GetPause();
    //    m_pPause->Create();
    //}
    if (m_pGimmickFactory)
    {
        m_pGimmickFactory->Update();
    }

    if (m_bGameEnd)
    {
        CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();
        if (mode == CFade::FADE_MODE_NONE)
        {
            CFade *pFade = CManager::GetInstance()->GetFade();
            pFade->SetFade(CManager::MODE_TYPE_TITLE);
        }
    }

#ifdef _DEBUG
    //CInputKeyboard* pKey = CManager::GetInstance()->GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetInstance()->GetFade()->GetFade();

    // �^�C�g���ɖ߂�
    if (pKey->GetTrigger(DIK_TAB) && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetInstance()->GetFade();
        pFade->SetFade(CManager::MODE_TYPE_TITLE);
    }
    // �^�C�g���ɖ߂�
    if (pKey->GetTrigger(DIK_RETURN))
    {
        if (m_pGaussFilter)
        {
            // �K�E�X�̃t�F�[�h�Ɉȍ~
            m_pGaussFilter->SetFade(true);

            // �J�����̎�ނ�ς���
            CCameraGame* pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();
            pCamera->ChangeState(CCameraStateDescent::Create());
        }
    }

    ShowInfo();
#endif // !_DEBUG
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CGame::Draw()
{

}

//=======================================================================================
// �K�E�X�t�B���^�̊J�n
//=======================================================================================
void CGame::BeginGauss()
{
    if (m_pGaussFilter)
    {
        if (m_pGaussFilter->GetUse())
        {
            m_pGaussFilter->BeginSurface();
        }
    }
}

//=======================================================================================
// �K�E�X�t�B���^�̏I��
//=======================================================================================
void CGame::EndGauss()
{
    if (m_pGaussFilter)
    {
        if (m_pGaussFilter->GetUse())
        {
            m_pGaussFilter->DrawPolygon();
        }
    }
}

//=======================================================================================
// �v���C���[�̐���
//=======================================================================================
void CGame::CreatePlayer()
{
    // �v���C���[�̐���
    if (!m_pPlayer)
    {
        m_pPlayer = CPlayer::Create(ZeroVector3, ZeroVector3);
        m_pPlayer->ChangeState(CPlayerStateNotMove::Create());
    }
}

//=======================================================================================
// �G�l�~�[�̐���
//=======================================================================================
void CGame::CreateEnemy()
{
    CShark::Create(D3DXVECTOR3(-13534.7f, 0.0f, -24998.2f), ZeroVector3);
    CShark::Create(D3DXVECTOR3(-29145.5f, 0.0f, -14420.8f), ZeroVector3);
    CShark::Create(D3DXVECTOR3(-30498.5f, 0.0f, -8135.1f), ZeroVector3);
    CShark::Create(D3DXVECTOR3(-38483.3f, 0.0f, -5445.3f), ZeroVector3);
    CShark::Create(D3DXVECTOR3(-47151.3f, 0.0f, -544.6f), ZeroVector3);

    CMarlin::Create(D3DXVECTOR3(-23991.0f, 0.0f, -21278.3f), ZeroVector3);
    CMarlin::Create(D3DXVECTOR3(-42865.0f, 0.0f, -17226.5f), ZeroVector3);
    CMarlin::Create(D3DXVECTOR3(-42473.7f, 0.0f, 1648.0f), ZeroVector3);

    CGhost::Create(D3DXVECTOR3(-36078.3f, 200.0f, -25948.0f), ZeroVector3);
    CGhost::Create(D3DXVECTOR3(-38673.9f, 2586.1f, 1478.9f), ZeroVector3);

    // �N���[�P��
    if (!m_pKraken)
    {
        m_pKraken = CKraken::Create();
        m_pKraken->ChangeState(CKrakenStateNotAttack::Create());
    }
}

//=======================================================================================
// NPC�̐���
//=======================================================================================
void CGame::CreateNPC()
{
    if (!m_pNpcFactory)
    {
        m_pNpcFactory = CNpcFactory::Create();
    }
}

//=======================================================================================
// �}�b�v�̐���
//=======================================================================================
void CGame::CreateMap()
{
    CTestModel::Create();
    CWaterFresnel::Create();
    CSky::Create();

    if (!m_pGimmickFactory)
    {
        m_pGimmickFactory = CGimmickFactory::Create();
    }
}

//=======================================================================================
// ���\��
//=======================================================================================
void CGame::ShowInfo()
{
#ifdef _DEBUG
    //�����_���[�ŊǗ����Ă��̏��
    ImGui::Begin("DebugInfo");

    if (ImGui::CollapsingHeader("WorldInfo"))
    {
        LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();    // �f�o�C�X�̎擾

        // �d�͂̒l
        ImGui::SliderFloat("Gravity", &m_fGravity, 0.0f, 50.0f);
        ImGui::Checkbox("Gauss", &m_bGaussFilter);

        // ImGui::TreePop();
    }

    ImGui::End();
#endif // !_DEBUG
}

//=======================================================================================
// �I�u�W�F�N�g����
//=======================================================================================
void CGame::CreateObject()
{
    CreateMap();
    CreatePlayer();
    CreateEnemy();
    CreateNPC();
    CGauge::Create();
    CGaugebar::Create();
}

//=======================================================================================
// �t�B���^�̐���
//=======================================================================================
void CGame::CreateFilter()
{
    if (!m_pGaussFilter)
    {
        m_pGaussFilter = new CGaussFilter(GET_RENDERER_DEVICE);
        m_pGaussFilter->Load();
        m_pGaussFilter->Restore();
    }
}
