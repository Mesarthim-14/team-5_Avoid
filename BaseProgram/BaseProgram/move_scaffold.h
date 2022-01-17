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
#include "map.h"
#include "collisionModel_OBB.h"

//=========================================================================
// �N���X��`
//=========================================================================
class CMoveScaffold : public CMap
{
public:
    CMoveScaffold(PRIORITY Priority);  // �R���X�g���N�^
    ~CMoveScaffold();                  // �f�X�g���N�^

    static CMoveScaffold *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                 // ����������
    void Uninit()override;                                                        // ����������
    void Update()override;                                                        // �X�V����
    void Draw()override;                                                          // �`��

    void Respawn(); // ���X�|�[�����̏���

private:
    // private�֐�
    void Move();        // �ړ���
    void CarryPlayer(); // �v���C���[���^��
    void OnOBBs();      // ����Ă��邩�̔���
    void Col();         // �����蔻��

    // �����o�ϐ�
    CCollisionModelOBB* m_pColModelOBB[CCollisionModelOBB::SURFACE_MAX];    // �����蔻�胂�f���|�C���^(OBB)
    D3DXVECTOR3 m_StartPos;                                                 // �n�܂�̈ʒu
    D3DXVECTOR3 m_GoalPos;                                                  // �S�[���̈ʒu
    int m_nTime;                                                            // ����
    float m_fSpeed;                                                         // ���x
    bool m_bMove;                                                           // �ړ��̃t���O
};

#endif