//=============================================================================
//
// NPC�N���X [non_player_character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "non_player_character.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "library.h"
#include "game.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "player.h"
#include "key_e.h"
#include "npc_text_enemy.h"
#include "production_npc_talk.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DISTANCE    (700.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNonPlayerCharacter::CNonPlayerCharacter(PRIORITY Priority) : CScene(Priority)
{
    m_pos = ZeroVector3;
    m_rot = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);
    m_pSkinmeshModel = nullptr;
    m_pKeyE = nullptr;
    m_pText = nullptr;
    m_bDead = false;
    m_pProduction = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNonPlayerCharacter::~CNonPlayerCharacter()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CNonPlayerCharacter::Init()
{
    // ���f������
    CreateModel();

    if (!m_pKeyE)
    {
        m_pKeyE = CKeyE::Create();
    }
    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CNonPlayerCharacter::Uninit()
{
    //�I�u�W�F�N�g�̔j��
    Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CNonPlayerCharacter::Update()
{
    //���f���ʒu�������f(������character�Ɉړ����������j
    m_pSkinmeshModel->SetPos(m_pos);
    m_pSkinmeshModel->SetRot(m_rot);

    if (m_bDead)
    {
        return;
    }

    if (m_pText)
    {
        // �e�L�X�g�̏I���Ȃ�
        if (m_pText->GetEnd())
        {
            EndProduction();
            m_pText->Uninit();
            m_pText = nullptr;
            m_bDead = true;
            m_pKeyE->SetDrawFlag(false);
            return;
        }
    }
    Collision();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CNonPlayerCharacter::Draw()
{
    //�f�o�C�X���̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // �}�g���N�X�̐ݒ�
    CLibrary::ConfigMatrix(&m_mtxWorld, m_pos, m_rot);

    //���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

}

//=============================================================================
// ���f������
//=============================================================================
void CNonPlayerCharacter::CreateModel()
{
    m_pSkinmeshModel = CSkinmeshModel::Create(m_pos, m_rot, CSkinmeshModel::MODEL_PLAYER_50);
    
    m_pSkinmeshModel->GetHLcontroller()->ChangeAnimation(0);
    m_pSkinmeshModel->GetHLcontroller()->SetLoopTime(0, 60);
    m_pSkinmeshModel->GetHLcontroller()->SetShiftTime(0, 60);
}

//=============================================================================
// �����蔻��
//=============================================================================
void CNonPlayerCharacter::Collision()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    float fAngle = CLibrary::CalAngleXZ(m_pos, pPlayer->GetPos());
    // �߂Â�����E�{�^�����o��
    if (CLibrary::CalDistance(m_pos, pPlayer->GetPos()) <= DISTANCE
        && fAngle <= m_rot.y + D3DXToRadian(-60.0f) && fAngle >= m_rot.y + D3DXToRadian(-135.0f))
    {
        m_pKeyE->SetDrawFlag(true);

        // ���͂��ꂽ��
        if (CLibrary::KeyboardTrigger(DIK_E))
        {
            // �b��
            Talk();

            // ���o�X�^�[�g
            BebinProduction(m_pos, m_rot);
        }
    }
    else
    {
        m_pKeyE->SetDrawFlag(false);
    }


}

//=============================================================================
// �b������
//=============================================================================
void CNonPlayerCharacter::Talk()
{
    if (!m_pText)
    {
        m_pText = CNpcTextEnemy::Create();
    }
}

//=============================================================================
// ��Ԃ̊J�n
//=============================================================================
void CNonPlayerCharacter::BebinProduction(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
    if (!m_pProduction)
    {
        m_pProduction = CProductionNpcTalk::Create(pos, rot);
    }
}

//=============================================================================
// ��Ԃ̏I��
//=============================================================================
void CNonPlayerCharacter::EndProduction()
{
    if (m_pProduction)
    {
        // �I������
        m_pProduction->Uninit();
        m_pProduction = nullptr;
    }
}
