#ifndef _MOVE_SCAFFOLD_H_
#define _MOVE_SCAFFOLD_H_
//=============================================================================
//
// ��������N���X [move_scaffold.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "model.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CMoveScaffold : public CModel
{
public:
    CMoveScaffold(PRIORITY = PRIORITY_TEST_MODEL);  // �R���X�g���N�^
    ~CMoveScaffold();                               // �f�X�g���N�^

    static CMoveScaffold *Create(); // �C���X�^���X����
    HRESULT Init();                 // ����������
    void Uninit();                  // ����������
    void Update();                  // �X�V����
    void Draw();                    // �`��

private:
    // private�֐�
    void Move();    // �ړ���

    int m_nTime;
    float m_fSpeed;
};

#endif