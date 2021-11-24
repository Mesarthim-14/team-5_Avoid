//=============================================================================
//
// �X�L�����b�V������ [skinmesh.cpp]
// Author : Takahashi Naoyuki
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "skinmesh.h"

//�t���[�����R�s�[�֐�
char * SkinMesh::AllocateHierarchy::copyName(const char * name)
{
    char *cName = 0;

    // �U��\0�Ȃ�
    if (!name || name[0] == '\0')
    {
        cName = new char[1];
        cName[0] = '\0';
    }
    else
    {
        size_t len = strlen(name);
        cName = new char[strlen(name) + 1];
        strcpy_s(cName, strlen(name) + 1, name);
    }

    return cName;
}

//�t���[�������֐�
HRESULT SkinMesh::AllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
    SMD3DXFRAME *newFrame = new SMD3DXFRAME;
    newFrame->Name = copyName(Name);    // �t���[���̖��O������
    newFrame->pFrameFirstChild = 0;        // �q�t���[���ւ̃|�C���^������
    newFrame->pFrameSibling = 0;        // �Z��t���[���ւ̃|�C���^������
    newFrame->pMeshContainer = 0;        // ���b�V���R���e�i�ւ̃|�C���^������
    D3DXMatrixIdentity(&newFrame->TransformationMatrix);// ������
    *ppNewFrame = newFrame;

    return D3D_OK;
}

//�t���[���폜�֐�
HRESULT SkinMesh::AllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
    // �q�t���[���������Ă���Ȃ�
    if (pFrameToFree->pFrameFirstChild)
    {
        //�q�t���[��������
        DestroyFrame(pFrameToFree->pFrameFirstChild);
    }

    // �Z��t���[���������Ă���Ȃ�
    if (pFrameToFree->pFrameSibling)
    {
        // �Z��t���[��������
        DestroyFrame(pFrameToFree->pFrameSibling);
    }

    // ���b�V���R���e�i�������Ă���Ȃ�
    if (pFrameToFree->pMeshContainer)
    {
        // ���b�V���R���e�i������
        DestroyMeshContainer(pFrameToFree->pMeshContainer);
    }

    // �t���[�����폜
    delete[] pFrameToFree->Name;

    // �t���[���폜
    delete pFrameToFree;

    return D3D_OK;
}

//���b�V���R���e�i�[�����֐�
HRESULT SkinMesh::AllocateHierarchy::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, CONST DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
    SMD3DXMESHCONTAINER *newCont = new SMD3DXMESHCONTAINER;
    newCont->Name = copyName(Name);// �t���[���̖��O������

    newCont->pAdjacency = new DWORD[pMeshData->pMesh->GetNumFaces() * TRIANGLE];    // ���b�V�����\������O�p�|���S���̐����擾�y�єz��̊m��
    memset(newCont->pAdjacency, 0, pMeshData->pMesh->GetNumFaces() * TRIANGLE * sizeof(DWORD));    // �אڂ���(3��)�|���S���C���f�b�N�X�̃R�s�[

    newCont->MeshData.Type = pMeshData->Type;    // ���b�V���^�C�v�̃R�s�[

                                                // �ǂݍ��񂾃��b�V�����X�L�����b�V���p�ɍœK������w���p�[�֐�
    pSkinInfo->ConvertToBlendedMesh
    (
        pMeshData->pMesh,// ID3DAllocateHierarchy�œǂݍ��񂾍œK�������O�̃��b�V��
        0,
        pAdjacency,
        newCont->pAdjacency,
        0,
        0,
        &newCont->maxFaceInfl,            // 1�̒��_�ɉe������{�[���̍ő吔���Ԃ�
        &newCont->numBoneCombinations,    // �{�[���R���r�l�[�V�����̐�
        &newCont->boneCombinationTable,    // �{�[���ƒ��_�̑Ή��\���z��Ƃ��Ċi�[����Ă���
        &newCont->MeshData.pMesh        // �œK�����ꂽ���b�V�����Ԃ�
    );

    newCont->NumMaterials = NumMaterials;    // �}�e���A���̐��R�s�[
    newCont->pMaterials = new D3DXMATERIAL[NumMaterials];    // �z��̊m��
    memcpy(newCont->pMaterials, pMaterials, NumMaterials * sizeof(D3DXMATERIAL)); //D3DXMATERIAL�\���̂̔z��̐擪�|�C���^�R�s�[

    newCont->pEffects = 0;// ������

    // pEffectInstances���^�Ȃ�
    if (pEffectInstances)
    {
        newCont->pEffects = new D3DXEFFECTINSTANCE;// �������m��
        newCont->pEffects->pEffectFilename = copyName(pEffectInstances->pEffectFilename);    // �G�t�F�N�g�t�@�C���̖��O�R�s�[
        newCont->pEffects->NumDefaults = pEffectInstances->NumDefaults;                        // pDefaults(D3DXEFFECTDEFAULT�\����)�̔z��̗v�f���R�s�[
        newCont->pEffects->pDefaults = new D3DXEFFECTDEFAULT[pEffectInstances->NumDefaults];// �������m�ہipDefaults�͔z��̐擪�|�C���^�j
        for (DWORD i = 0; i < pEffectInstances->NumDefaults; i++)
        {
            D3DXEFFECTDEFAULT *src = pEffectInstances->pDefaults + i;    // �R�s�[��
            D3DXEFFECTDEFAULT *dest = newCont->pEffects->pDefaults + i;    // �R�s�[��
            dest->NumBytes = src->NumBytes;                        // �p�����[�^�̏��傫���R�s�[
            dest->Type = src->Type;                                // �p�����[�^�̌^���R�s�[
            dest->pParamName = copyName(src->pParamName);        // �p�����[�^�ɕt����ꂽ���O�R�s�[
            dest->pValue = new char[src->NumBytes];                // �p�����[�^�̒l���w���|�C���^�̃������m��
            memcpy(dest->pValue, src->pValue, src->NumBytes);    // �p�����[�^�̒l���w���|�C���^�̃R�s�[
        }
    }

    newCont->pSkinInfo = pSkinInfo;// �X�L�j���O���R�s�[
    pSkinInfo->AddRef();//�Q�ƃJ�E���^�����Z

    *ppNewMeshContainer = newCont;// �쐬�������b�V���R���e�i�iD3DXMESHCONTAINER�\���́j�������ɓn��

    return D3D_OK;
}

//���b�V���R���e�i�[�폜�֐�
HRESULT SkinMesh::AllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
    {
        // ���b�V���R���e�i���R�s�[(��������Z��)
        SMD3DXMESHCONTAINER *pMCont = (SMD3DXMESHCONTAINER*)pMeshContainerToFree;

        // ���b�V���̉��
        pMCont->MeshData.pMesh->Release();

        // ���O�̉��
        delete[] pMCont->Name;

        // ���b�V�����\������O�p�|���S�����̉��
        delete[] pMCont->pAdjacency;

        // pEffect���^�Ȃ�
        if (pMCont->pEffects)
        {
            for (DWORD i = 0; i < pMCont->pEffects->NumDefaults; i++)
            {
                D3DXEFFECTDEFAULT *pDefaults = pMCont->pEffects->pDefaults + i;// �R�s�[(��������Z��)

                delete[] pDefaults->pParamName;    // �p�����[�^�̖��O���
                delete[] pDefaults->pValue;        // �p�����[�^�̒l���w���|�C���^�̉��
            }

            delete[] pMCont->pEffects->pDefaults;        // pEffects�z��̐擪�|�C���^���
            delete[] pMCont->pEffects->pEffectFilename;    // �G�t�F�N�g�t�@�C���̖��O���
            delete pMCont->pEffects;                    // pEffectInstances���
        }

        // �}�e���A�����̉��
        delete[] pMCont->pMaterials;

        // �X�L����񂪐^�Ȃ�
        if (pMCont->pSkinInfo)
        {
            pMCont->pSkinInfo->Release();    // �X�L�������
        }

        // �{�[���R���r�l�[�V�����\���̔z��ւ̃|�C���^���^�Ȃ�
        if (pMCont->boneCombinationTable)
        {
            pMCont->boneCombinationTable->Release();    // �{�[���R���r�l�[�V�����\���̔z��ւ̃|�C���^���
        }

        //���b�V���R���e�i���폜
        delete pMCont;

        return D3D_OK;
    }
}

//���b�V���R���e�i�擾�֐�
void SkinMesh::getMeshContainer(D3DXFRAME * frame, std::vector<SkinMesh::SMD3DXMESHCONTAINER*>* cont)
{
    // ���b�V���R���e�i��ۗL���Ă���
    if (frame->pMeshContainer)
    {
        // ���b�V���R���e�i��Ԃ�
        cont->push_back((SkinMesh::SMD3DXMESHCONTAINER*)frame->pMeshContainer);
    }

    // ���b�V���R���e�i��ۗL���Ă��Ȃ�

    // �q�t���[����ۗL���Ă���
    if (frame->pFrameFirstChild)
    {
        // �q�t���[���̃��b�V���R���e�i��Ԃ�
        return getMeshContainer(frame->pFrameFirstChild, cont);
    }

    // ���b�V���R���e�i�A�q�t���[����ۗL���Ă��Ȃ�
    // �Z��t���[����ۗL���Ă���
    if (frame->pFrameSibling)
    {
        // �Z��t���[���̃��b�V���R���e�i��Ԃ�
        return getMeshContainer(frame->pFrameSibling, cont);
    }
}

//�t���[����񃊃��N�֐�
void frameLink(std::map<std::string, DWORD> nameToIdMap, ID3DXSkinInfo * info, SkinMesh::SMD3DXFRAME* frame)
{
    //nameToIdMap�̖��O���������āA�t���[���̍Ō���ł͂Ȃ��Ȃ�
    if (nameToIdMap.find(frame->Name) != nameToIdMap.end())
    {
        //�t���[���ɑΉ�����{�[���I�t�Z�b�g�s��Ɩ��O��R�Â�
        frame->id = nameToIdMap[frame->Name];
        frame->offsetMatrix = *info->GetBoneOffsetMatrix(frame->id);
    }

    //�q�t���[���̗L��
    if (frame->pFrameFirstChild)
    {
        frameLink(nameToIdMap, info, (SkinMesh::SMD3DXFRAME*)frame->pFrameFirstChild);
    }

    //�Z��t���[���̗L��
    if (frame->pFrameSibling)
    {
        frameLink(nameToIdMap, info, (SkinMesh::SMD3DXFRAME*)frame->pFrameSibling);
    }
};

// �{�[��ID���̏��������o���A�t���[���ɑΉ�����{�[��ID��R�Â�
void SkinMesh::setFrameId(SkinMesh::SMD3DXFRAME *frame, ID3DXSkinInfo *info)
{
    std::map < std::string, DWORD > BonesMap;//�{�[���l�[����ID�ۑ��p

                                             //�{�[���̖��O��ID��R�Â�
    for (DWORD nCount = 0; nCount < info->GetNumBones(); nCount++)
    {
        BonesMap[info->GetBoneName(nCount)] = nCount;
    }

    //�t���[�����R�Â�
    frameLink(BonesMap, info, frame);
}

//�T�u���b�V���ւ̃{�[���e���x���v�Z�i�[����֐�
void boneMatrixLink(std::map<DWORD, D3DXMATRIX> &combMatrixMap, D3DXMATRIX &parentBoneMatrix, SkinMesh::SMD3DXFRAME *frame)
{
    //�t���[���̃{�[���e���x�𒊏o
    D3DXMATRIX &localBoneMatrix = frame->TransformationMatrix;

    //�{�[���e���x�̃��[���h�ϊ�
    D3DXMATRIX boneMatrix = localBoneMatrix * parentBoneMatrix;

    //�{�[�������݂��Ă���
    if (frame->id != 0xffffffff)
    {
        //�{�[���̃I�t�Z�b�g * �t���[���̃{�[���e���x �� �t���[���̃T�u���b�V���ւ̃{�[���e���x���v�Z�i�[
        combMatrixMap[frame->id] = frame->offsetMatrix * boneMatrix;
    }

    //�q�t���[�������݂��Ă���
    if (frame->pFrameFirstChild)
    {
        //�q�t���[���̌v�Z
        boneMatrixLink(combMatrixMap, boneMatrix, (SkinMesh::SMD3DXFRAME*)frame->pFrameFirstChild);
    }

    //�Z��t���[�������݂��Ă���
    if (frame->pFrameSibling)
    {
        //�Z��t���[���̌v�Z
        boneMatrixLink(combMatrixMap, parentBoneMatrix, (SkinMesh::SMD3DXFRAME*)frame->pFrameSibling);
    }
}

//���݃t���[��(fps)�̃��[���h�ϊ��s��v�Z(�s��ۑ��p,�Q�ƃt���[��)
void SkinMesh::updateCombMatrix(std::map<DWORD, D3DXMATRIX>& combMatrixMap, D3DXMATRIX matrix, SkinMesh::SMD3DXFRAME * frame)
{
    boneMatrixLink(combMatrixMap, matrix, frame);
}

// �u�����h�s��C���f�b�N�X�쐬
void SkinMesh::createBlendIndex(BlendIndex** ppIndex, D3DXBONECOMBINATION* pBoneComb, DWORD boneCombNum)
{
	*ppIndex = new BlendIndex[boneCombNum];
	BlendIndex *bi = *ppIndex;

	for (DWORD i = 0; i < boneCombNum; ++i)
	{
		memcpy(bi[i].index, pBoneComb[i].BoneId, sizeof(DWORD) * 4);
		bi[i].boneNum = 0;
		for (int j = 0; j < 4; ++j)
		{
			if (pBoneComb[i].BoneId[j] != UINT_MAX)
			{
				bi[i].boneNum++;
			}
		}
	}
}