#ifndef _LIBRARY_H_
#define _LIBRARY_H_
//=============================================================================
//
// ���C�u�������� [library.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �����蔻��N���X
//=============================================================================
class CLibrary
{
public:
	static string split(string str, char del, int nNum);											// ������𕪊����A���o���֐�
	static void ConfigMatrix(D3DXMATRIX *pMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot);	// �}�g���N�X�̐ݒ�
	static void RotFix(float &fRot);																// �p�x�̏C��
	static int Random(int nNum);																	// �����_���ϐ�
	static int Random(int nMin, int nMax);															// �����_���ϐ�
	static float Random(float fNum);																// �����_���ϐ�
	static float Random(float fMin, float fMax);													// �����_���ϐ�

private:
};

#endif