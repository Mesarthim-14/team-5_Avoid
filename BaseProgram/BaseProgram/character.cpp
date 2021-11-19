//=============================================================================
//
// �L�����N�^�[�N���X [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "motion.h"
#include "model_info.h"
#include "library.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GRAVITY_POWAR   (1.0f)  // �d�͂̋���
#define GROUND_RIMIT    (0.0f)  // �n�ʂ̐���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter::CCharacter(PRIORITY Priority) : CScene(Priority)
{
    m_pos = ZeroVector3;
    m_posOld = ZeroVector3;
    m_move = ZeroVector3;
    m_rot = ZeroVector3;
    m_size = ZeroVector3;
    m_fSpeed = 0.0f;
    m_nStateCounter = 0;
    m_pMotion = nullptr;
    m_nParts = 0;
    m_apModelAnime.clear();
    m_bLanding = false;
    m_State = STATE_NORMAL;
    m_bUseShadow = false;
    m_bGravity = true;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCharacter::Init()
{

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCharacter::Uninit()
{
    for (auto &ModelAnime : m_apModelAnime)
    {
        // nullcheck
        if (ModelAnime)
        {
            //�������̍폜
            delete ModelAnime;
            ModelAnime = nullptr;
        }
    }

    // �N���A
    m_apModelAnime.clear();

    // nullcheck
    if (m_pMotion)
    {
        //�������̍폜
        delete m_pMotion;
        m_pMotion = nullptr;
    }

    //�I�u�W�F�N�g�̔j��
    Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCharacter::Update()
{
    // �d��
    Gravity();

    // �ړ��ʉ��Z
    m_pos += m_move;

    // �J�E���^�[��i�߂�
    m_nStateCounter++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCharacter::Draw()
{
    //�f�o�C�X���̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // �}�g���N�X�̐ݒ�
    CLibrary::ConfigMatrix(&m_mtxWorld, m_pos, m_rot);

    //���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    // ���f���̕`��
    for (auto &model : m_apModelAnime)
    {
        if (model)
        {
            model->Draw(m_rot);
        }
    }

    // �e�̕`��
    if (m_bUseShadow)
    {
        for (auto &shadow : m_apModelAnime)
        {
            if (shadow)
            {
                shadow->ShadowDraw(m_rot);
            }
        }
    }
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CCharacter::ModelCreate(const CXfile::HIERARCHY_XFILE_NUM &FileNum)
{
    // XFile�̃|�C���^�擾
    CXfile *pXfile = CManager::GetInstance()->GetResourceManager()->GetXfileClass();

    // nullcheck
    if (pXfile)
    {
        // ���f���p�[�c�̐ݒ�
        m_nParts = pXfile->GetModelParts(FileNum);

        //���f���p�[�c�����J��Ԃ�
        for (int nCntModel = 0; nCntModel < m_nParts; nCntModel++)
        {
            // ���[�J���ϐ��擾
            CModelAnime *pModelAnime = nullptr;
            CXfile::MODELFILE ModelFile = pXfile->GetModelFile(nCntModel, FileNum);
            vector<CXfile::MODEL> model = pXfile->GetHierarchyXfile(FileNum);

            // nullcheck
            if (!pModelAnime)
            {
                // �C���X�^���X����
                pModelAnime = CModelAnime::Create(ModelFile.offsetPos, ModelFile.offsetRot, model.at(nCntModel));

                // nullcheck
                if (pModelAnime)
                {
                    // ���f�����̐ݒ�
                    pModelAnime->GetModelInfo()->SetModelStatus(ModelFile.offsetPos, ModelFile.offsetRot, model.at(nCntModel));
                    if (m_bUseShadow)
                    {
                        // �e�̐���
                        pModelAnime->GetModelInfo()->CreateShadowPtr();
                    }

                    //�e���f���̏ꍇ
                    if (nCntModel == 0)
                    {
                        pModelAnime->SetParent(nullptr);
                    }
                    //�q���f���̏ꍇ
                    else
                    {
                        //�����̐e����ݒ肷��
                        pModelAnime->SetParent(m_apModelAnime.at(ModelFile.nParent));
                    }
                }

                // ��������
                m_apModelAnime.push_back(pModelAnime);
            }
        }
        // nullcheck
        if (!m_pMotion)
        {
            // ���[�V�������̃C���X�^���X����
            m_pMotion = CMotion::Create(pXfile->GetModelFileName(FileNum));
        }
    }
}

//=============================================================================
// ���f���A�j���[�V����
//=============================================================================
void CCharacter::ModelAnimeUpdate()
{
    // ���[�V�����̍X�V����
    if (m_pMotion)
    {
        // ���[�V�����̍X�V
        m_pMotion->UpdateMotion(m_nParts, m_apModelAnime);
    }
}

//=============================================================================
// �d�͂̏���
//=============================================================================
void CCharacter::Gravity()
{
    if (!m_bLanding && m_bGravity)
    {
        // �d�͂�������
        m_move.y -= CGame::GetGravity();
        m_pos.y += m_move.y;        // ����
    }

    //// �n�ʂ̔���
    //if (m_pos.y <= GROUND_RIMIT)
    //{
    //    //Landing(GROUND_RIMIT);
    //    m_bLanding = true;
    //}
    //else
    //{
    //    m_bLanding = false;
    //}
}

//=============================================================================
// ���n�̏���
//=============================================================================
void CCharacter::Landing(const float &fHeight)
{
    m_move.y = 0.0f;
    m_pos.y = fHeight;

    // ���n�̏��
    if (!m_bLanding)
    {
        m_bLanding = true;
    }
}

//=============================================================================
// ���[�V�����̐ݒ�
//=============================================================================
void CCharacter::SetMotion(const int &nMotionState)
{
    // nullcheck
    if (m_pMotion)
    {
        // ���[�V�����̍X�V
        m_pMotion->SetMotion(nMotionState, m_nParts, m_apModelAnime);
    }
}

//=============================================================================
// �e�̉�]�𔽉f�����邩
//=============================================================================
void CCharacter::SetShadowRotCalculation()
{
    // ���f���̕`��
    for (auto &model : m_apModelAnime)
    {
        if (model)
        {
            model->SetRotCalculation(true);
        }
    }
}

//=============================================================================
// �L�����N�^�[�̏��
//=============================================================================
void CCharacter::SetCharacterInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    m_pos = pos;
    m_rot = rot;
}