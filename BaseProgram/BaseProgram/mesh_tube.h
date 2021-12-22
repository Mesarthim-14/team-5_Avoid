#ifndef _MESH_TUBE_H_
#define _MESH_TUBE_H_
//=============================================================================
//
// ���b�V���t�B�[���h�N���X [meshfield.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "mesh_3d.h"

//=============================================================================
// ���b�V���t�B�[���h�N���X
//=============================================================================
class CMeshTube : public CMesh3d
{
public:
    CMeshTube(PRIORITY = PRIORITY_0);  // �R���X�g���N�^
    ~CMeshTube();                      // �f�X�g���N�^

    static CMeshTube*Create(const D3DXVECTOR3 &pos, const MESH_TYPE &MeshNum); // ���b�V���t�B�[���h
    HRESULT Init();     // ����������
    void Update();      // �X�V����
    void Uninit();
    void Draw();        // �`�揈��

private:
    // private�֐�
    void InitAnimation(const int &nPatternNum, const int &nSpeed, const int &nLoop) {}  // �A�j���[�V������񏉊���
    void UpdateAnimation() {}                                                           // �A�j���[�V�����X�V
};

#endif