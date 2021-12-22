//=============================================================================
//
// �Q�̑���N���X [swirl_scaffold.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "swirl_scaffold.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "swirl_scaffold_object.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_ROT            (D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))   // �p�x
#define ROTATE_NUM          (D3DXToRadian(1.0f))                            // ��]�̒l
#define OBJECT_INTER_POS    (3000.0f)                                       // �I�u�W�F�N�g�̊Ԋu
#define OBJECT_ROT_NUM      (D3DXToRadian(1))                               // �I�u�W�F�N�g�̉�]

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSwirlScaffold::CSwirlScaffold(PRIORITY Priority) : CScene(Priority)
{
    m_pos = ZeroVector3;
    m_fAngle = D3DXToRadian(CLibrary::Random(180));
 //   m_fAngle = 0.0f;
    memset(m_pObject, 0, sizeof(m_pObject));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSwirlScaffold::~CSwirlScaffold()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CSwirlScaffold * CSwirlScaffold::Create(const D3DXVECTOR3 &pos)
{
    // �������m��
    CSwirlScaffold *pRotatebody = new CSwirlScaffold(PRIORITY_GIMMICK);

    // !nullcheck
    if (pRotatebody)
    {
        // ����������
        pRotatebody->m_pos = pos;
        pRotatebody->Init();
        return pRotatebody;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSwirlScaffold::Init()
{
    CreateObject();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSwirlScaffold::Uninit()
{
    for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
    {
        if (m_pObject[nCount])
        {
            m_pObject[nCount]->Uninit();
            m_pObject[nCount] = nullptr;
        }
    }
}

//=============================================================================
// �X�V����
//=============================================================================
void CSwirlScaffold::Update()
{
    RotateObject();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSwirlScaffold::Draw()
{

}

//=============================================================================
// ��]
//=============================================================================
void CSwirlScaffold::RotateObject()
{
    m_fAngle += OBJECT_ROT_NUM;
    CLibrary::RotFix(m_fAngle);
    D3DXVECTOR3 rot = ZeroVector3;
    float fAngle = D3DXToRadian(90.0f);

    for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
    {
        if (m_pObject[nCount])
        {
            m_pObject[nCount]->SetPos(D3DXVECTOR3(
                m_pos.x + sinf(m_fAngle + fAngle)*OBJECT_INTER_POS,
                m_pos.y,
                m_pos.z + cosf(m_fAngle + fAngle)*OBJECT_INTER_POS));
            rot = m_pObject[nCount]->GetRot();
            rot.y = m_fAngle + fAngle;
            //m_pObject[nCount]->SetRot(rot);
        }

        // �p�x���]
        fAngle *= -1;
    }
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
void CSwirlScaffold::CreateObject()
{
    float fAngle = D3DXToRadian(90.0f);
    for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
    {
        if (!m_pObject[nCount])
        {
            m_pObject[nCount] = CSwirlScaffoldObject::Create(D3DXVECTOR3(
                m_pos.x + sinf(m_fAngle + fAngle)*OBJECT_INTER_POS,
                m_pos.y,
                m_pos.z + cosf(m_fAngle + fAngle)*OBJECT_INTER_POS));
        }
    }
}
