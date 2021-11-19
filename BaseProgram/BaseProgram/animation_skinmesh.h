#ifndef IKD_AnimController_H
#define IKD_AnimController_H

#include <d3dx9.h>
#include <vector>

class IHighLevelAnimController
{
public:
    struct HLANIMATION_DESC
    {
        UINT uiAnimID;                 // アニメーションID
        ID3DXAnimationSet *pAnimSet;   // アニメーションセット
        FLOAT fLoopTime;               // 1ループの時間
        FLOAT fTrackSpeed;             // トラックスピード調節値
        FLOAT fShiftTime;              // シフトするにかかる時間
        FLOAT fCurWeightTime;          // 現在のウェイト時間
    };
    // アニメーションコントローラを設定
    bool SetAnimationController(ID3DXAnimationController *pAnimCont);
    // アニメーションコントローラを取得
    bool GetAnimationController(ID3DXAnimationController **ppAnimCont);
    // ループ時間を設定
    bool SetLoopTime(UINT animID, FLOAT time);
    // 動作開始にかかる時間を設定
    bool SetShiftTime(UINT animID, FLOAT interval);
    // アニメーションを切り替え
    bool ChangeAnimation(UINT animID);
    // アニメーションを更新
    bool AdvanceTime(FLOAT time);

private:
    std::vector<HLANIMATION_DESC> m_Anim;//アニメーションデータ保存用
    UINT m_CurAnimID;//現在のアニメーション
    UINT m_PreAnimID;//前回アニメーション
    ID3DXAnimationController * m_AnimCont;//アニメーションコントローラー
};
#endif