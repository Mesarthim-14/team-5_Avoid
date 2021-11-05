#ifndef _PAUSE_H_
#define _PAUSE_H_
//=====================================================================
//
//	�|�[�Y����[pause.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "scene.h"

//=====================================================================
// �O���錾
//=====================================================================
class CPolygon;

//=====================================================================
// �N���X��`
//=====================================================================
class CPause
{
public:
	enum MENU
	{
		BACK = 0,
		RESUME,
		RESTART,
		EXIT,
		MAX
	};

	CPause();
	~CPause();

	static CPause * Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool SetMove(bool move) { m_bMove = move; }

private:
	CPolygon * m_pPolygon[MAX];
	int m_nMenu;
	bool m_bMove;
};


#endif // !_GAUGE_H_
