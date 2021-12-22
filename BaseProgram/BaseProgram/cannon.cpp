//=============================================================================
//
// ��C�N���X [cannon.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "cannon.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "kraken.h"
#include "library.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CAN_PUSH_DISTANCE    (1000.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCannon::CCannon(PRIORITY Priority) : CModel(Priority)
{
    m_bUse = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCannon::~CCannon()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCannon * CCannon::Create(const D3DXVECTOR3 &pos)
{
    // �������m��
    CCannon *pTestModel = new CCannon(PRIORITY_GIMMICK);

    // !nullcheck
    if (pTestModel)
    {
        // ����������
        pTestModel->Init(pos);
        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCannon::Init(const D3DXVECTOR3 &pos)
{
    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CANNON);

    GetModelInfo()->SetModelStatus(pos, LookAtKraken(pos), model);

    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CCannon::Update()
{
    CModel::Update();
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CCannon::Collision()
{
    if (!m_bUse)
    {
        return PlayerDisCollision(CAN_PUSH_DISTANCE);
    }
    return false;
}

//=============================================================================
// �N���[�P�������鏈��
//=============================================================================
D3DXVECTOR3 CCannon::LookAtKraken(const D3DXVECTOR3 &pos)
{
    CKraken* pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    if (pKraken)
    {
        D3DXVECTOR3 Tpos = pKraken->GetPos();
        D3DXVECTOR3 rot = GetRot();
        rot.y = CLibrary::LookTarget(Tpos, pos);
        return rot;
    }
    return ZeroVector3;
}
