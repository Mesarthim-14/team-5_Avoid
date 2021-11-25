//=============================================================================
//
// �X�L�����b�V������ [skinmesh.cpp]
// Author : Takahashi Naoyuki
//
//=============================================================================
#ifndef SKINMESH_H
#define SKINMESH_H

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TRIANGLE 3 //�אڃ|���S���C���f�b�N�X

//�X�L�����b�V��
namespace SkinMesh
{
    // D3DXFRAME(�{�[��)�֘A�̏���ێ�
    // D3DXFRAME�̔h��(SMD3DXFRAME)�쐬id��offsetMatrix��ǉ�
    struct SMD3DXFRAME : public D3DXFRAME
    {
        DWORD id;                       // �{�[��ID
        D3DXMATRIX offsetMatrix;        // �{�[���I�t�Z�b�g�s��

        SMD3DXFRAME() : id(0xffffffff)    // ������
        {
            D3DXMatrixIdentity(&offsetMatrix);
        }
    };

    // SMD3DXMESHCONTAINER(���b�V��)�֘A�̏���ێ�
    struct SMD3DXMESHCONTAINER : public D3DXMESHCONTAINER
    {
        DWORD maxFaceInfl;                    // �{�[���ő�e����
        DWORD numBoneCombinations;            // �{�[���R���r�l�[�V������
        ID3DXBuffer *boneCombinationTable;    // �{�[���R���r�l�[�V�����\���̔z��ւ̃|�C���^
        SMD3DXMESHCONTAINER() : maxFaceInfl(1), numBoneCombinations(0), boneCombinationTable(0) {}    // ������
    };

	struct BlendIndex {
		int boneNum;
		int index[4];
	};

    // �K�w���蓖�ăN���X�i�{�[���̍\���ł���t���[���c���[�iD3DXFRAME�j�AFK�A�j���[�V�����iID3DXAnimationController�j�Ƃ���2�̃I�u�W�F�N�g��Ԃ��B�j
    class AllocateHierarchy : public ID3DXAllocateHierarchy
    {
    public:
        // �t���[���I�u�W�F�N�g�iD3DXFRAME�\���́j�쐬�֐�
        STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
        // �w�肳�ꂽ�t���[�����폜����֐�
        STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
        // ���b�V���R���e�i�iD3DXMESHCONTAINER�\���́j�쐬�֐�
        STDMETHOD(CreateMeshContainer)(THIS_
            LPCSTR Name,                                // �t���[���̖��O
            CONST D3DXMESHDATA *pMeshData,                // D3DXMESHDATA�\���̂ւ̃|�C���^
            CONST D3DXMATERIAL *pMaterials,                // �}�e���A�����
            CONST D3DXEFFECTINSTANCE *pEffectInstances,    // �G�t�F�N�g���i�����_�����O���J�X�^�}�C�Y�����p�̃v���O�����̂悤�Ȃ��́j
            DWORD NumMaterials,                            // �}�e���A���̐�
            CONST DWORD *pAdjacency,                    // ���b�V�����\������O�p�|���S���̐�
            LPD3DXSKININFO pSkinInfo,                    // �X�L�j���O(���b�V����ό`)���
            LPD3DXMESHCONTAINER *ppNewMeshContainer);    // ���b�V���R���e�i�\���̂ւ̃|�C���^

        //�w�肳�ꂽ���b�V���R���e�i���폜�֐�
        STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);
    private:
        //���O�R�s�[�֐�
        char *copyName(const char* name);
    };
    //�{�[���}�g���N�X�X�V�֐�
    void updateCombMatrix(std::map<DWORD, D3DXMATRIX> &combMatrixMap, D3DXMATRIX matrix, SkinMesh::SMD3DXFRAME *frame);
    //���b�V���R���e�i�[�擾�֐�
    void getMeshContainer(D3DXFRAME *frame, std::vector<SkinMesh::SMD3DXMESHCONTAINER*> *cont);
    //�{�[���f�[�^�i�[�֐�
    void setFrameId(SkinMesh::SMD3DXFRAME * frame, ID3DXSkinInfo * info);

	void createBlendIndex(BlendIndex** ppIndex, D3DXBONECOMBINATION* pBoneComb, DWORD boneCombNum);
}
#endif