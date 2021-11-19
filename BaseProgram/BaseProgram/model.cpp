//=============================================================================
//
// ���f���N���X [model.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "shadow.h"
#include "model_info.h"
#include "player.h"
#include "library.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel::CModel(PRIORITY Priority) : CScene(Priority)
{
    m_move = ZeroVector3;
    m_size = ZeroVector3;
    m_scale = MODEL_DEFAULT_SIZE;
    m_nTexPattern = 0;
    m_nLife = 0;
    m_pModelInfo = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CModel * CModel::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    //���f���N���X�̃|�C���^�ϐ�
    CModel *pModel = new CModel(PRIORITY_MODEL);

    // nullcheck
    if (pModel)
    {
        //�����������Ăяo��
        pModel->Init();
        return pModel;
    }

    return nullptr;
}

//=============================================================================
// �v���C���[�Ƃ̋����̓����蔻��
//=============================================================================
bool CModel::PlayerDisCollision(const float &fDistanse)
{
    // ���W�̎擾
    D3DXVECTOR3 PPos = CManager::GetInstance()->GetPlayer()->GetPos();
    D3DXVECTOR3 ThisPos = GetModelInfo()->GetPos();

    // �����̎擾
    float fDistance = CLibrary::CalDistance(PPos, ThisPos);

    // �����𑪂�
    if (fDistance <= fDistanse)
    {
        return true;
    }

    return false;
}

//=============================================================================
//���f���N���X�̏���������
//=============================================================================
HRESULT CModel::Init()
{
    // ���̐���
    CreateInfoPtr();

    return S_OK;
}

//=============================================================================
//���f���N���X�̏I������
//=============================================================================
void CModel::Uninit()
{
    // �e�̏I������
    HasPtrDelete();

    //�I�u�W�F�N�g�̔j��
    Release();
}

//=============================================================================
// ���f���N���X�̍X�V����
//=============================================================================
void CModel::Update()
{
    // ���������炷
    m_nLife--;

    // ���W�̍X�V
    m_pModelInfo->GetPos() += m_move;
}

//=============================================================================
// ���f���N���X�̕`�揈��
//=============================================================================
void CModel::Draw()
{
    //�f�o�C�X���̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
    D3DMATERIAL9 matDef;
    D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxWorld;
    D3DXVECTOR3 pos = m_pModelInfo->GetPos();
    D3DXVECTOR3 rot = m_pModelInfo->GetRot();

    //���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&mtxWorld);

    // �g�嗦�𔽉f
    D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

    //�����𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

    //�ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

    //���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
    m_pModelInfo->SetMtxWorld(mtxWorld);

    //���݂̃}�e���A�����擾����
    pDevice->GetMaterial(&matDef);

    //�}�e���A���f�[�^�ւ̃|�C���^���擾
    CXfile::MODEL model = m_pModelInfo->GetModel();
    D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pModelInfo->GetBuffMat()->GetBufferPointer();
    for (int nCntMat = 0; nCntMat < (int)model.dwNumMat; nCntMat++)
    {
        //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
        pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

        //�}�e���A���̐ݒ�
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

        // �e�N�X�`���̐ݒ�
        if (model.apTexture[nCntMat])
        {
            pDevice->SetTexture(0, model.apTexture[nCntMat]);
        }
        else
        {
            pDevice->SetTexture(0, nullptr);
        }
        
        //���f���p�[�c�̕`��
        model.pMesh->DrawSubset(nCntMat);
        pDevice->SetTexture(0, nullptr);
    }

    //�ێ����Ă����}�e���A����߂�
    pDevice->SetMaterial(&matDef);
    pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

    // �e�̕`��
    m_pModelInfo->ShadowDraw(rot);
}

//=============================================================================
// ���f�����̐ݒ�
//=============================================================================
void CModel::HasPtrDelete()
{
    if (m_pModelInfo)
    {
        m_pModelInfo->Uninit();
        m_pModelInfo = nullptr;
    }
}

//=============================================================================
// ���̃|�C���^����
//=============================================================================
void CModel::CreateInfoPtr()
{
    if (!m_pModelInfo)
    {
        m_pModelInfo = CModelInfo::Create(CModelInfo::MODEL_TYPE_NONE);
    }
}

//=============================================================================
// ���W�̏��擾
//=============================================================================
D3DXVECTOR3 CModel::GetPos()const
{
    return GetModelInfo()->GetPos();
}

//=============================================================================
// �p�x�̏��擾
//=============================================================================
D3DXVECTOR3 CModel::GetRot()const
{
    return GetModelInfo()->GetRot();
}
