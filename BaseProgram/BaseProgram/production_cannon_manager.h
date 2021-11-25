#ifndef _PRODUCTION_CANNON_MANAGER_H_
#define _PRODUCTION_CANNON_MANAGER_H_
//=======================================================================================
//
// ���o�N���X [.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "production.h"

//=======================================================================================
// �O���錾
//=======================================================================================
class CProduction;

//=======================================================================================
// �N���X��`
//=======================================================================================
class CProductionCannonManager
{
public:
    CProductionCannonManager();    // �R���X�g���N�^
    ~CProductionCannonManager();   // �f�X�g���N�^

    static CProductionCannonManager* Create();      // �C���X�^���X����
    void Init();                                    // ����������
    void Uninit();                                  // �I������
    void Update();                                  // �X�V����
    inline bool GetEnd()const { return m_bEnd; }    // �I���t���O

private:
    void CreateProductionCannonShot();              // ���o�̐���
    void CreateProductionAngry();                   // ���o�̐���

    CProduction *m_pProduction; // ���o�̃|�C���^
    bool m_bEnd;                // �I���t���O
    int m_nStep;                // ���o�̃X�e�b�v

    typedef void(CProductionCannonManager::*SENTENCE_FUNC)();
    vector<SENTENCE_FUNC> m_CreateProduction =
    { &CProductionCannonManager::CreateProductionCannonShot ,
        &CProductionCannonManager::CreateProductionAngry };

};
#endif