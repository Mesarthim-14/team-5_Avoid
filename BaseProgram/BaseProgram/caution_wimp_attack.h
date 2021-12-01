#ifndef _CAUTION_WIMP_ATTACK_H_
#define _CAUTION_WIMP_ATTACK_H_
//=====================================================================
//
// �G���G�̍U���x�� [caution_wimp_attack.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "billboard.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CCautionWimpAttack : public CBillboard
{
public:
    CCautionWimpAttack(PRIORITY priority);  // �R���X�g���N�^
    ~CCautionWimpAttack();                  // �f�X�g���N�^

    static CCautionWimpAttack * Create(const D3DXVECTOR3& pos); // �C���X�^���X����
    HRESULT Init()override;                                     // ����������
    void Uninit()override;                                      // �I������
    void Update()override;                                      // �X�V����
    void Draw()override;                                        // �`�揈��

private:
    D3DXVECTOR3 FixPos(const D3DXVECTOR3& pos);  // ���W�̏C��
};


#endif