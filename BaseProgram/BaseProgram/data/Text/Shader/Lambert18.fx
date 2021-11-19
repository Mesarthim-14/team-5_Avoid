//=============================================================================
//
// 光の反射 [Lambert18.fx]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// グローバル変数宣言
//=============================================================================
float4x4 m_WVPP;				// ワールド行列 × ビュー × 遠近射影行列
float4 m_LightDir;				// 平行光源の方向ベクトル
float4 m_Ambient;				// 環境光
bool m_ZEnable;					// true:Ｚ値をα成分に出力する　false:1.0fをα成分に出力する
float m_ZF;						// 遠近射影行列の最遠近距離

//オブジェクトのテクスチャー
sampler tex0 : register(s0);

//=============================================================================
// 構造体
//=============================================================================
struct VS_OUTPUT
{
   float4 Pos     : POSITION;
   float4 Col     : COLOR0;
   float2 Tex     : TEXCOORD0;
   float4 PosWVP  : TEXCOORD1;
};

//=============================================================================
// 頂点シェーダ
//=============================================================================
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal : NORMAL, float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;
	
	Out.Pos = mul(Pos, m_WVPP);					// ワールド変換
	Out.Tex = Tex;								// テクスチャ座標
	
	float3 Light = -m_LightDir.xyz;				// ライトを反転
	float3 Nor = normalize(Normal.xyz);			// 法線の正規化
	Out.Col = max( m_Ambient, dot(Nor, Light));	// 元の色と内積(ライト法線)の大きい方
	Out.PosWVP = Out.Pos;						// ワールド座標
	
	return Out;
}

//=============================================================================
// ピクセルシェーダ
//=============================================================================
float4 PS(VS_OUTPUT In) : COLOR0
{
	// 変数宣言
	float4 Out;
	
	// 色情報をRGBに格納する
	Out = tex2D( tex0, In.Tex );	// テクスチャとその座標を出す
	Out.rgb *= In.Col.rgb;			// テクスチャとピクセルをかける
	
	// Z値を格納する
	if (m_ZEnable)	// trueなら
	{
		Out.a = In.PosWVP.z / m_ZF;	// 
	}
	else
	{
		Out.a = 1.0f;
	}
	
	return Out;
}

//=============================================================================
// テクニック
//=============================================================================
technique TShader
{
   pass P0
   {
      VertexShader = compile vs_1_1 VS();
      PixelShader  = compile ps_2_0 PS();
   }
}