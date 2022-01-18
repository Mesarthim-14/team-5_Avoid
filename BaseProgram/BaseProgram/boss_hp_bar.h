#ifndef _BOSS_HP_BAR_H_
#define _BOSS_HP_BAR_H_
//=========================================================
//
// ボス体力バークラスヘッダー    [boss_hp_bar.h]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// インクルード
//=========================================================
#include "scene_base.h"

//=========================================================
// ゲージバークラス
//=========================================================
class CBossHpBar : public CSceneBase
{
public:
    CBossHpBar(PRIORITY Priority);  // コンストラクタ
    ~CBossHpBar();                  // デストラクタ

    static CBossHpBar* Create(const int& nLife);    // インスタンス生成
   HRESULT Init();                                  // 初期化処理
   void Uninit();                                   // 終了処理
   void Update();                                   // 更新処理
   void Draw();                                     // 描画処理
   void SetGageVertex();                            // ゲージの頂点設定
   void SubHp(const int& nNum);                     // HPの減算
   void Render();                                   // 描画

    // Get関数
    inline int GetGage()const       { return m_nGage; }                        // 体力の情報
    inline int GetMaxGage()const    { return m_nMaxGage; }                    // 体力の最大数情報

private:
    int m_nMaxGage;     // 体力の最大値
    int m_nGage;        // 体力

    void CreateVertex(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);    // 頂点の生成
    void InitAnimation(const int &nPatternNum, const int &nSpeed, const int &nLoop) {}  // アニメーション情報初期化
    void UpdateAnimation() {}                                                           // アニメーション更新


};
#endif