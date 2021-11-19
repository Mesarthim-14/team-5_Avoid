#ifndef _CAMERA_H_
#define _CAMERA_H_
//=============================================================================
//
// �J�����N���X�w�b�_�[ [camera.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �J�����N���X
//=============================================================================
class CCamera
{
public:
    CCamera();				// �R���X�g���N�^
    virtual ~CCamera();		// �f�X�g���N�^

    HRESULT Init();             // ����������
    virtual void Uninit();      // �I������
    virtual void Update();      // �X�V����
    virtual void SetCamera();   // �J�����̕`��ݒ�
    void ShowInfo();            // imgui�̐ݒ�

    // Set�֐�
    inline void SetDistance(const float &fDistance)     { m_fDistance = fDistance; }
    inline void SetVartical(const float &fVartical)     { m_fVartical = fVartical; }
    inline void SetHorizontal(const float &fHorizontal) { m_fHorizontal = fHorizontal; }
    inline void SetposV(const D3DXVECTOR3 &posV)        { m_posV = posV; };
    inline void SetposR(const D3DXVECTOR3 &posR)        { m_posR = posR; };
    inline void Setrot(const D3DXVECTOR3 &rot)          { m_rot = rot; };

    // Get�֐�
    inline D3DXVECTOR3 &GetposV()       { return m_posV; }              // �J�������W
    inline D3DXVECTOR3 &GetposR()       { return m_posR; }              // �J�����p�x
    inline D3DXVECTOR3 &GetposU()       { return m_posU; }              // ������x�N�g��
    inline D3DXVECTOR3 &GetposVDest()   { return m_posVDest; }          // �ړI�̍��W
    inline D3DXVECTOR3 &GetposRDest()   { return m_posRDest; }          // �ړI�̊p�x
    inline D3DXVECTOR3 &GetRot()        { return m_rot; }               // ����
    inline D3DXMATRIX GetMtxView()const { return m_mtxView; }           // �}�g���N�X�r���[
    inline D3DXMATRIX GetMtxProj()const { return m_mtxProjection; }     // �v���W�F�N�g
    inline float GetVartical()const     { return m_fVartical; }         // �c�̉�]
    inline float GetHorizontal()const   { return m_fHorizontal; }       // ���̉�]
    inline float GetDistance()const     { return m_fDistance; }         // ����

private:
	//=========================================================================
	// �����o�ϐ��錾
	//=========================================================================
	D3DXVECTOR3 m_posV;						// �J�����̍��W
	D3DXVECTOR3 m_posVDest;					// �J�����̍��W�i�ړI�n�j
	D3DXVECTOR3 m_posVRot;					// �J�����̍��W�i�j
	D3DXVECTOR3 m_posR;						// �����_
	D3DXVECTOR3 m_posRDest;					// �����_�i�ړI�n�j
	D3DXVECTOR3 m_posRRot;					// �����_�i�j
	D3DXVECTOR3 m_posU;						// ������x�N�g��
	D3DXMATRIX m_mtxProjection;				// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;					// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;						// ����
	float m_fVartical;						// �c��]�p�x
	float m_fHorizontal;					// ����]�p
	float m_fDistance;						// ���_�`�����_�̋���
	float m_fMove;							// �ړ���
};
#endif 