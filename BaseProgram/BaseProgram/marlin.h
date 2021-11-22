#ifndef _MARLIN_H_
#define _MARLIN_H_
//=============================================================================
//
// �J�W�L [marlin.h]
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
class CMarlinModel;

//=============================================================================
// �N���X��`
//=============================================================================
class CMarlin : public CWimpEnemy
{
public:
    CMarlin(PRIORITY Priority = PRIORITY_CHARACTER);    // �R���X�g���N�^
    ~CMarlin();                                         // �f�X�g���N�^

    static CMarlin *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // ����������
    void Uninit();                                                          // �I������
    void Update();                                                          // �X�V����

private:
    // private�֐�
    void CreateModel(); // ���f������
    void Attack();      // �U��

    // �����o�ϐ�
    CMarlinModel *m_pMarlinModel;   // ���f���̃|�C���^
    static const float m_fCollisionSize;
};
#endif