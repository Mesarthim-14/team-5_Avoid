#ifndef _PRODUCTION_H_
#define _PRODUCTION_H_
//=======================================================================================
//
// ���o�N���X [production.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "main.h"

//=======================================================================================
// �O���錾
//=======================================================================================
class CState;
class CStateObject;

//=======================================================================================
// �N���X��`
//=======================================================================================
class CProduction
{
public:
    CProduction();          // �R���X�g���N�^
    virtual ~CProduction(); // �f�X�g���N�^

    virtual void Init();    // ����������
    virtual void Uninit();  // �I������
    virtual void Update();  // �X�V����

    inline bool GetEnd()const { return m_bEnd; }    // �I���t���O

protected:
    void CreateState(CStateObject* pObj, CState* pState);

    // �I���̃J�E���g�����鎮
    function<int (const int)> TimeCounter = [&](const int nLimit)
    {
        m_nCounter++;

        if (m_nCounter >= nLimit)
        {// ���Ԍo�߂�����
            m_bEnd = true;
        }
        return m_nCounter;
    };

private:
    int m_nCounter; // �J�E���^
    bool m_bEnd;    // �I���t���O
};
#endif