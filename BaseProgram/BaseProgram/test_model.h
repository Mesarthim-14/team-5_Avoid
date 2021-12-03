#ifndef _TEST_MODEL_H_
#define _TEST_MODEL_H_
//=============================================================================
//
// �e�X�g���f���N���X [test_model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"

//=========================================================================
// �O���錾
//=========================================================================
class CCollisionModelOBB;
class CBlurFilter;
class CShaderSquare;
class CGaussFilter;

//=========================================================================
// �N���X��`
//=========================================================================
class CTestModel : public CModel
{
public:

    CTestModel(PRIORITY = PRIORITY_TEST_MODEL); // �R���X�g���N�^
    ~CTestModel();                              // �f�X�g���N�^

    static CTestModel *Create();    // �C���X�^���X����
    HRESULT Init();                 // ����������
    void Uninit();                  // ����������
    void Update();                  // �X�V����
    void Draw();                    // �`��
    void Hit();                     // �Փ˔���
    void OBBs();                    // OBB�Փ˔���

private:
    CCollisionModelOBB* m_pCollisionModelOBB;   //�����蔻�胂�f���̃|�C���^
    //2D�I�u�W�F�N�g(�\�ʉ��U��(Subsurface Scattering) �y�[�W�Q��)
    CShaderSquare* m_pSqu1Back;
    CGaussFilter* m_pGaussFilter;
};

#endif