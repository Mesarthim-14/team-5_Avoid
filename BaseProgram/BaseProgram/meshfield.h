#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
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
class CMeshField : public CMesh3d
{
public:
    CMeshField(PRIORITY = PRIORITY_0);  // �R���X�g���N�^
    ~CMeshField();                      // �f�X�g���N�^

    virtual HRESULT Init();     // ����������
    virtual void Update();      // �X�V����
    virtual void Draw();        // �`�揈��
    static CMeshField*Create(); // ���b�V���t�B�[���h

protected:
    void SetInfo(const D3DXVECTOR3 &size, const INT_VERTEX_2D &PieceNum);   // ���̐ݒ�

private:
    // private�֐�
    void CreateVerterx();                                                               // ���_�̐���
    void InitAnimation(const int &nPatternNum, const int &nSpeed, const int &nLoop) {}  // �A�j���[�V������񏉊���
    void UpdateAnimation() {}                                                           // �A�j���[�V�����X�V
};

#endif