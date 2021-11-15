#ifndef _MAP_UI_H_
#define _MAP_UI_H_
//=====================================================================
//
//	操作説明表示処理[gauge.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "scene2d.h"

//=====================================================================
// クラス定義
//=====================================================================
class CMapUi : public CScene2D
{
public:
	CMapUi();
	~CMapUi();

	static CMapUi * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};


#endif // !_MAP_UI_H_
