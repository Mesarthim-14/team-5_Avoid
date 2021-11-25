#ifndef _CANNON_BULLETH_
#define _CANNON_BULLETH_
//=============================================================================
//
// ��C�̒e�N���X [cannon_bullet.h]
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
class CCannonBullet : public CModel
{
public:
    CCannonBullet(PRIORITY = PRIORITY_TEST_MODEL);  // �R���X�g���N�^
    ~CCannonBullet();                               // �f�X�g���N�^

    static CCannonBullet *Create(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot);   // �C���X�^���X����
    HRESULT Init(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot);                   // ����������
    void Update();                                                                              // �X�V����
private:
    // private�֐�
    void CalDistance();                                             // �����v�Z
    void SetBulletInfo(D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);   // �e�̏���ݒ�
    void Collision();                                               // �����蔻��

    // �����o�ϐ�
    float m_fDistanceToKraken;          // ����
    D3DXVECTOR3 m_KrakenPos;            // �N���[�P���̍��W
    CCollisionModelOBB* m_pCollision;   // �����蔻��
    bool m_bHit;                        // �����������̃t���O
};

#endif