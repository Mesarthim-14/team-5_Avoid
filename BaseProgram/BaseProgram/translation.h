#ifndef _TRANSLATION_H_
#define _TRANSLATION_H_
//=====================================================================
//
//	��������\������[gauge.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "scene2d.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CTranslation : public CScene2D
{
public:
	CTranslation();
	~CTranslation();

	static CTranslation * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};


#endif // !_GAUGE_H_
