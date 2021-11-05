#ifndef _PAUSE_H_
#define _PAUSE_H_
//=====================================================================
//
//	ポーズ処理[pause.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "scene.h"

//=====================================================================
// 前方宣言
//=====================================================================
class CPolygon;

//=====================================================================
// クラス定義
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
