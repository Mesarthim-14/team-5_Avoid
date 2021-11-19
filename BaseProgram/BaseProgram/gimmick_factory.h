#ifndef _GIMMICK_FACTORY_H_
#define _GIMMICK_FACTORY_H_
//=======================================================================================
//
// �Q�[���N���X [game.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// �O���錾
//=======================================================================================
class CCheckPoint;
class CBarrelFactory;
class CHeel;
class CCannonManager;

//=======================================================================================
// �Q�[���N���X
//=======================================================================================
class CGimmickFactory
{
public:
    CGimmickFactory();  // �R���X�g���N�^
    ~CGimmickFactory(); // �f�X�g���N�^

    static CGimmickFactory *Create();   // �C���X�^���X����
    HRESULT Init();                     // ����������
    void Uninit();                      // �I������
    void Update();                      // �X�V����

    // Get�֐�
    inline CCheckPoint *GetCheckPoint()const        { return m_pCheckPoint; }       // �`�F�b�N�|�C���g
    inline CCannonManager* GetCannonManager()const  { return m_pCannonManager; }    // ��C�Ǘ��N���X

private:
    // private�֐�
    void CreateCheckPoint();    // �`�F�b�N�|�C���g�̐ݒu
    void CreateGimmick();       // �}�b�v����
    void CreateMoveScaffold();  // �������M�~�b�N
    void CreateRotateGimmick(); // ��]�M�~�b�N
    void CreateSlope();         // �⓹
    void CreateCannon();        // ��C
    void CreateBridge();        // ��
    void CreateSwirl();         // �Q

    // �����o�ϐ�
    CCheckPoint *m_pCheckPoint;         // �`�F�b�N�|�C���g�̃t���O
    CBarrelFactory *m_pBarrelFactory;   // �M�̐���
    CHeel *m_pHeel;                     // �񕜃N���X
    CCannonManager *m_pCannonManager;   // ��C�Ǘ��N���X
};
#endif