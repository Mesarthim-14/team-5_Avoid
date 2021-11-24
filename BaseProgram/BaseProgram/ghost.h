#ifndef _GHOST_H_
#define _GHOST_H_
//=============================================================================
//
// �H�� [ghost.h]
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
class CGhostModel;

//=============================================================================
// �N���X��`
//=============================================================================
class CGhost : public CWimpEnemy
{
public:
    CGhost(PRIORITY Priority = PRIORITY_CHARACTER); // �R���X�g���N�^
    ~CGhost();                                      // �f�X�g���N�^

    static CGhost *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);  // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);           // ����������
    void Uninit();                                                          // �I������
    void Update();                                                          // �X�V����

private:
    // private�֐�
    void CreateModel();     // ���f������
    void Attack();          // �U��
    void Move()override;    // �ړ�����
    void Rise();            // �㏸

    // �����o�ϐ�
    CGhostModel *m_pGhostModel; // ���f���̕ϐ�
    bool m_bFollow;             // �Ǐ]�t���O
    bool m_bEnd;                // �I���t���O
    int m_nEndCount;            // �I�����̃J�E���g

    static const float m_fCollisionSize;
};
#endif