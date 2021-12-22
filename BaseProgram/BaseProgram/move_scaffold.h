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
// �O���錾
//=========================================================================
class CCollisionModelOBB;

//=========================================================================
// �N���X��`
//=========================================================================
class CMoveScaffold : public CModel
{
public:
    CMoveScaffold(PRIORITY = PRIORITY_MAP);  // �R���X�g���N�^
    ~CMoveScaffold();                               // �f�X�g���N�^

    static CMoveScaffold *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot); // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);                 // ����������
    void Uninit()override;                                                        // ����������
    void Update()override;                                                        // �X�V����
    void Draw()override;                                                          // �`��

    void HitOBBs(); // OBB���m�̓����蔻��
    void Respawn(); // ���X�|�[�����̏���

private:
    // private�֐�
    void Move();        // �ړ���
    void CarryPlayer(); // �v���C���[���^��

    // �����o�ϐ�
    CCollisionModelOBB* m_pColModelOBB; // �����蔻�胂�f���|�C���^(OBB)
    D3DXVECTOR3 m_StartPos;             // �n�܂�̈ʒu
    D3DXVECTOR3 m_GoalPos;              // �S�[���̈ʒu
    int m_nTime;                        // ����
    float m_fSpeed;                     // ���x
    bool m_bMove;                       // �ړ��̃t���O
};

#endif