#ifndef _MAP_H_
#define _MAP_H_
//=============================================================================
//
// �}�b�v�e�N���X [map.h]
// Author : Suzuki Mahiro
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
class CCollisionModelCylinder;
class CCollisionModelPolygon;

//=========================================================================
// �N���X��`
//=========================================================================
class CMap : public CModel
{
public:
    CMap(PRIORITY Priority); // �R���X�g���N�^
    ~CMap();                 // �f�X�g���N�^

    HRESULT Init();         // ����������
    void Uninit()override;  // ����������
    void Update()override;  // �X�V����
    void Draw()override;    // �`��

    // �����蔻��
    void HitColOBBsPlayer(const CCollisionModelOBB* const* pMapColOBB);             // �v���C���[�Ƃ̓����蔻��֐�(�����̓��m)
    void HitColOBBsPlayer(const CCollisionModelOBB* const &pMapColOBB);             // �v���C���[�Ƃ̓����蔻��֐�(�����̓��m)
    void HitColPolygonPlayer(const CCollisionModelPolygon* const &pMapColPolygon);     // �v���C���[�Ƃ̓����蔻��֐�(�����̓��m)
    void HitColPolygonOnPlayer(const CCollisionModelPolygon* const &pMapColPolygon);  // �v���C���[�Ƃ̓����蔻��֐�(�����̓��m)
    void HitColOBBsBossBullet(const CCollisionModelOBB* const pMapColOBB);          // �{�X�o���b�g�Ƃ̓����蔻��֐�(�����̓��m)
    void HitColPlayer(const CCollisionModelCylinder* const pMapColCylinder);        // �v���C���[�Ƃ̓����蔻��֐�(���̂Ɖ~��)
    void HitColBossBullet(const CCollisionModelCylinder* const pMapColCylinder);    // �{�X�o���b�g�Ƃ̓����蔻��֐�(���̂Ɖ~��)

protected:
    void SetHitMap(const bool bHitMap) { m_bHitMap = bHitMap; } // �P�ȏ�}�b�v�ɓ������Ă��邩�̔���̐ݒ�
    bool GetHitMap()const { return m_bHitMap; }                 // �P�ȏ�}�b�v�ɓ������Ă��邩�̔���̎擾

private:
    virtual void Col() = 0;

    static bool m_bHitMap; // �P�ȏ�}�b�v�ɓ������Ă��邩�̔���
};

#endif