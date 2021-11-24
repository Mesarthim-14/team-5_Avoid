#ifndef _CANNON_MANAGER_H_
#define _CANNON_MANAGER_H_
//=============================================================================
//
// ��C�Ǘ��N���X [cannon_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "main.h"

//=========================================================================
// �O���錾
//=========================================================================
class CCannon;
class CKeyE;
class CProductionCannonManager;

//=========================================================================
// �N���X��`
//=========================================================================
class CCannonManager
{
public:
    CCannonManager();   // �R���X�g���N�^
    ~CCannonManager();  // �f�X�g���N�^

    static CCannonManager *Create();                        // �C���X�^���X����
    HRESULT Init();                                         // ����������
    void Uninit();                                          // �I������
    void Update();                                          // �X�V����
    inline int GetAttackNum()const { return m_nAttackNum; } // �`�F�b�N�|�C���g�̒l

    // Get�֐�
    inline CCannon* GetCurrentCannon()const { return m_apCannon.at(m_nTargetCannon); }

private:
    // private�֐�
    void CreateCannon();        // ���̐���
    void CreateUi();            // Ui����
    void CannonCollision();     // ���ꂼ��̑�C�̓����蔻��
    void InputJudge();          // �{�^���̔���
    void CreateBullet();        // ��C�̒e����
    void SetProductionMode();   // ��C�̉��o���[�h�ֈȍ~

    vector<CCannon*> m_apCannon;                // ��C�̃|�C���^
    int m_nAttackNum;                           // �U��������
    CKeyE *m_pKeyE;                             // E�L�[��UI�|�C���^
    int m_nTargetCannon;                        // �ΏۂƂȂ��C�̔ԍ�
    CProductionCannonManager *m_pProduction;    // ���o�̃|�C���^
};

#endif