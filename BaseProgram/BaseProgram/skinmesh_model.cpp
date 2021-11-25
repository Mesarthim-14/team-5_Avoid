//=============================================================================
//
// ���f���N���X [model.cpp]
// Author : Takahashi Naoyuki
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "skinmesh_model.h"
#include "manager.h"
#include "renderer.h"
#include "shadow.h"
#include "model_info.h"
#include "skinmesh.h"
#include "animation_skinmesh.h"

const char * CSkinmeshModel::m_aParam[MODEL_MAX] =
{
    "data/Model/Hierarchy/player/slime_10.x",
    "data/Model/Hierarchy/player/slime_50.x",
    "data/Model/Hierarchy/player/slime_100.x",
    "data/Model/Hierarchy/enemy/boss/takohead.x",
};


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSkinmeshModel::CSkinmeshModel(PRIORITY Priority) : CScene(Priority)
{
    m_move = ZeroVector3;
    m_size = ZeroVector3;
    m_scale = MODEL_DEFAULT_SIZE;
    m_nTexPattern = 0;
    m_nLife = 0;
    m_pModelInfo = nullptr;
    m_pAnimetionController = 0;
    m_pRootFrame = 0;
    m_HLcontroller = nullptr;
    m_ModelNum = MODEL_PLAYER_100;
    m_bIsDraw = true;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSkinmeshModel::~CSkinmeshModel()
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CSkinmeshModel * CSkinmeshModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL modelNum)
{
    //���f���N���X�̃|�C���^�ϐ�
    CSkinmeshModel *pModel = new CSkinmeshModel;

    // nullcheck
    if (pModel)
    {
        pModel->m_ModelNum = modelNum;
        //�����������Ăяo��
        pModel->Init();
        pModel->GetModelInfo()->SetPos(pos);
        return pModel;
    }

    return nullptr;
}

//=============================================================================
//���f���N���X�̏���������
//=============================================================================
HRESULT CSkinmeshModel::Init()
{
    // ���̐���
    CreateInfoPtr();

    //�f�o�C�X���̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // �X�L�����b�V������X�t�@�C���ۑ��p
    SkinMesh::AllocateHierarchy allocater;

    //�������m��(�A�j���[�V�����j
    m_HLcontroller = new IHighLevelAnimController;

    //�G���[�m�F�p
    HRESULT model = D3DERR_WRONGTEXTUREFORMAT;
    //�����f��
    model = D3DXLoadMeshHierarchyFromX((m_aParam[m_ModelNum]), D3DXMESH_MANAGED, pDevice, &allocater, 0, (D3DXFRAME**)&m_pRootFrame, &m_pAnimetionController);

    if (model == D3DERR_INVALIDCALL)
    {
        return 0;
    }

    //�A�j���[�V�����R���g���[���[�̃R�s�[
    m_HLcontroller->SetAnimationController(m_pAnimetionController);

    //���b�V���R���e�i�擾�֐�
    SkinMesh::getMeshContainer(m_pRootFrame, &m_cont);

	// �u�����h�s��C���f�b�N�X�쐬
	SkinMesh::BlendIndex* pBlendIndex;

    for (unsigned int i = 0; i < m_cont.size(); i++)
    {
		m_combs.push_back((D3DXBONECOMBINATION*)m_cont[i]->boneCombinationTable->GetBufferPointer());

		m_cont[i]->pSkinInfo->ConvertToBlendedMesh(m_cont[i]->MeshData.pMesh, 0, 0, 0, 0, 0, &m_cont[i]->maxFaceInfl, &m_cont[i]->numBoneCombinations, &m_cont[i]->boneCombinationTable, &m_cont[i]->MeshData.pMesh);

		// �t���[�����Ƀ{�[��ID�ƃI�t�Z�b�g�s��𖄂ߍ���
		SkinMesh::setFrameId(m_pRootFrame, m_cont[i]->pSkinInfo);

		SkinMesh::createBlendIndex(&pBlendIndex, (D3DXBONECOMBINATION*)m_cont[i]->boneCombinationTable->GetBufferPointer(), m_cont[i]->numBoneCombinations);
	}

    return S_OK;
}

//=============================================================================
//���f���N���X�̏I������
//=============================================================================
void CSkinmeshModel::Uninit()
{
    // �e�̏I������
    HasPtrDelete();

    
    //�I�u�W�F�N�g�̔j��
    Release();
}

//=============================================================================
// ���f���N���X�̍X�V����
//=============================================================================
void CSkinmeshModel::Update(void)
{
    // ���������炷
    m_nLife--;

    // ���W�̍X�V
    m_pModelInfo->GetPos() += m_move;

    ////��
    ////�A�j���[�V�����ύX
    ////m_HLcontroller->ChangeAnimation(0);
    ////���[�v����
    //m_HLcontroller->SetLoopTime(1, 60);
    //m_HLcontroller->SetLoopTime(0, 60);

    //////�A�j���[�V�����ύX
    ////m_HLcontroller->ChangeAnimation(0);

    ////�A�j���[�V�����̃V�t�g�ɂ����鎞��
    //m_HLcontroller->SetShiftTime(1, 10);
    //m_HLcontroller->SetShiftTime(0, 10);

    ////m_HLcontroller->ChangeAnimation(1);
    
}

//=============================================================================
// ���f���N���X�̕`�揈��
//=============================================================================
void CSkinmeshModel::Draw()
{
    if (m_bIsDraw)
    {
        //�f�o�C�X���̎擾
        LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
        D3DMATERIAL9 matDef;
        D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxWorld;
        D3DXVECTOR3 pos = m_pModelInfo->GetPos();
        D3DXVECTOR3 rot = m_pModelInfo->GetRot();

        //���݂̃}�e���A�����擾����
        pDevice->GetMaterial(&matDef);
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

        //���݃t���[��(fps)�̃��[���h�ϊ��s��
        std::map<DWORD, D3DXMATRIX> combMatrixMap;

        //// ���Ԃ�i�߂Ďp���X�V
        //m_pAnimetionController->AdvanceTime(0.0001f, 0);
        //m_pAnimetionController->SetTrackAnimationSet(0, 0);
        //�A�j���[�V�����X�V
        m_HLcontroller->AdvanceTime(1);

        SkinMesh::updateCombMatrix(combMatrixMap, mtxWorld, m_pRootFrame);

        for (DWORD BCombiId = 0; BCombiId < m_cont.size(); BCombiId++)
        {
            for (DWORD AttribId = 0; AttribId < m_cont[BCombiId]->numBoneCombinations; AttribId++)
            {
                DWORD boneCount = 0;

                for (DWORD Count = 0; Count < m_cont[BCombiId]->maxFaceInfl; Count++)
                {
                    //�{�[���R���r�l�[�V�����e�[�u������{�[��ID�𒊏o
                    DWORD BoneId = m_combs[BCombiId][AttribId].BoneId[Count];

                    //�{�[��ID�����݂��Ă���
                    if (BoneId != UINT_MAX)
                    {
                        // �C���f�b�N�X�t�����[���h�}�g���b�N�X�̐ݒ�
                        pDevice->SetTransform(D3DTS_WORLDMATRIX(Count), &combMatrixMap[BoneId]);
                        boneCount++;
                    }
                }

                pDevice->SetRenderState(D3DRS_VERTEXBLEND, boneCount - 1);

                m_cont[BCombiId]->pMaterials->MatD3D.Ambient = WhiteColor;
                pDevice->SetMaterial(&m_cont[BCombiId]->pMaterials->MatD3D);
                //���b�V���R���e�i���̃��b�V���f�[�^
                m_cont[BCombiId]->MeshData.pMesh->DrawSubset(AttribId);

            }
        }

        //�ێ����Ă����}�e���A����߂�
        pDevice->SetMaterial(&matDef);
        pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

        // �e�̕`��
        m_pModelInfo->ShadowDraw(rot);
    }
}

//=============================================================================
// ���f�����̐ݒ�
//=============================================================================
void CSkinmeshModel::HasPtrDelete()
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
void CSkinmeshModel::CreateInfoPtr()
{
    if (!m_pModelInfo)
    {
        m_pModelInfo = CModelInfo::Create(CModelInfo::MODEL_TYPE_NONE);
    }
}

//=============================================================================
// ���̃|�C���^����
//=============================================================================
void CSkinmeshModel::SetModelNumber(MODEL model)
{
    m_ModelNum = model;
}