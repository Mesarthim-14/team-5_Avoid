#ifndef _SHARK_H_
#define _SHARK_H_
//=============================================================================
//
// �T�� [shark.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "wimp_enemy.h"

//=============================================================================
// �O���錾
//=============================================================================
class CSharkModel;

//=============================================================================
// �N���X��`
//=============================================================================
class CShark : public CWimpEnemy
{
public:
    CShark(PRIORITY Priority = PRIORITY_CHARACTER); // �R���X�g���N�^
    ~CShark();                                      // �f�X�g���N�^

    static CShark *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // ����������
    void Uninit();  // �I������
    void Update();  // �X�V����

private:
    // private�֐�
    void CreateModel(); // ���f������
    void Attack();      // �U��

    // �����o�ϐ�
    CSharkModel *m_pSharkModel; // ���f���̕ϐ�
    static const float m_fCollisionSize;
};
#endif