//=============================================================================
//
// �V�[���N���X [scene.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"
#include "game.h"
#include "camera.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScene * CScene::m_pTop[CScene::PRIORITY_MAX] = {};
CScene * CScene::m_pCur[CScene::PRIORITY_MAX] = {};
bool CScene::m_bPause = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(PRIORITY Priority)
{
    //�v���C�I���e�B�̐ݒ�
    m_Priority = Priority;

    //���S�t���O��false�ɐݒ肷��
    m_bDeath = false;

    //�擪�I�u�W�F�N�g���m�ۂ���Ă��Ȃ��Ƃ�
    if (!m_pTop[m_Priority])
    {
        //�擪�I�u�W�F�N�g�Ɏ��g�̃|�C���^��ݒ肷��
        m_pTop[m_Priority] = this;

        //�擪�̂��߁A�O����nullptr�ŃN���A����
        m_pPrev = nullptr;
    }

    //���݃I�u�W�F�N�g���m�ۂ���Ă��Ȃ������ꍇ
    if (!m_pCur[m_Priority])
    {
        //���݃I�u�W�F�N�g�֎��g�̃|�C���^��ݒ�
        m_pCur[m_Priority] = this;
    }

    //���݃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���Ɏ����̏�������
    m_pCur[m_Priority]->m_pNext = this;

    //���݃I�u�W�F�N�g�������������ꍇ
    if (m_pCur[m_Priority] == this)
    {
        //�O����nullptr������
        m_pPrev = nullptr;
    }
    else
    {
        //�O���Ɍ��݃I�u�W�F�N�g������
        m_pPrev = m_pCur[m_Priority];
    }

    //���݃I�u�W�F�N�g�Ɏ��g�̃|�C���^���ɏ㏑������
    m_pCur[m_Priority] = this;

    //���g�̎������N���A����
    m_pNext = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// �S�Ă̍X�V����
//=============================================================================
void CScene::UpdateAll()
{
    //�|�[�Y���Ă��邩�@bool pause = m_pause   ->>  pause =true ->> if (type == OBJTYPE_PAUSE)
    for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        if (m_pTop[nCount])
        {
            // �擪�V�[��
            CScene *pScene = m_pTop[nCount];

            do
            {
                // ���̃V�[�����擾
                CScene *pSceneCur = pScene->m_pNext;

                // ���S�t���O���Ȃ��Ƃ�
                if (!pScene->m_bDeath)
                {
                    // �X�V����
                    pScene->Update();
                }

                // ���̃V�[����
                pScene = pSceneCur;

            } while (pScene);
        }
    }

    for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        // !nullcheck
        if (m_pTop[nCount])
        {
            // �擪�̃V�[�����m��
            CScene *pScene = m_pTop[nCount];

            do
            {
                CScene *pSceneCur = pScene->m_pNext;

                if (pScene->m_bDeath)
                {
                    // ���S�t���O�̏���
                    pScene->DeathRelease();
                }

                // ���̃V�[����
                pScene = pSceneCur;

            } while (pScene);
        }
    }
}

//=============================================================================
// �S�Ă̕`�揈��
//=============================================================================
void CScene::DrawAll()
{
    for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        // !nullcheck
        if (m_pTop[nCount])
        {
            // �擪���擾
            CScene *pScene = m_pTop[nCount];
            do
            {
                // ���̃V�[���擾z
                CScene *pSceneCur = pScene->m_pNext;

                // ���S�t���O���Ȃ���
                if (!pScene->m_bDeath)
                {
                    pScene->Draw();
                }

                // ���̃V�[����
                pScene = pSceneCur;

            } while (pScene);
        }
    }
}

//=============================================================================
// �S�Ă̏I������
//=============================================================================
void CScene::ReleaseAll()
{
    for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        // �擪���擾
        CScene *pScene = m_pTop[nCount];

        while (pScene)
        {
            // ���̃V�[���擾
            CScene *pCurScene = pScene->m_pNext;

            // �V�[���̏I������
            pScene->Uninit();

            // ���̃V�[����
            pScene = pCurScene;
        }
    }

    for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        // nullcheck
        if (m_pTop[nCount])
        {
            // �擪�̃V�[��
            CScene *pScene = m_pTop[nCount];

            do
            {
                // ���̃V�[���擾
                CScene *pSceneCur = pScene->m_pNext;

                // ���S�t���O����������
                if (pScene->m_bDeath)
                {
                    // ���S�t���O�̏���
                    pScene->DeathRelease();
                }

                // ���̃V�[����
                pScene = pSceneCur;

            } while (pScene);
        }
    }
}

//=============================================================================
// �P�������[�X
//=============================================================================
void CScene::Release()
{
    // ���S�t���O
    m_bDeath = true;
}

//=============================================================================
// ���S�t���O����������̃����[�X
//=============================================================================
void CScene::DeathRelease()
{
    // �ʒu�����炷
    for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        // �擪��������
        if (m_pTop[nCount] == this)
        {
            // �擪�����̃I�u�W�F�N�g�ɂ���
            m_pTop[nCount] = m_pNext;
        }

        // �Ōゾ������
        if (m_pCur[nCount] == this)
        {
            // �Ō�����̑O�̃I�u�W�F�N�g�ɂ���
            m_pCur[nCount] = m_pPrev;
        }

        // �O��̃V�[�����q���鏈��
        if (m_pPrev)
        {
            m_pPrev->m_pNext = m_pNext;
        }
        if (m_pNext)
        {
            m_pNext->m_pPrev = m_pPrev;
        }
    }

    // ���g��delete
    delete this;
}

//=============================================================================
// �擪���̎擾����
//=============================================================================
CScene * CScene::GetTop(const int &nNum)
{
    return m_pTop[nNum];
}

//=============================================================================
// ���̃V�[�����
//=============================================================================
CScene * CScene::GetNext()
{
    return m_pNext;
}

//=============================================================================
// �|�[�Y���̎擾
//=============================================================================
void CScene::SetPause(const bool &Pause)
{
    m_bPause = Pause;
}