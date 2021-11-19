//=============================================================================
//
// 視差マップのシェーダ [ParallaxMapping2.fx]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// グローバル変数宣言
//=============================================================================
float4x4 m_WVPP;				// 行列変換マトリクス
float4x4 m_WVPPT;				// スクリーン座標系のマトリクス
float4 m_LightDir;				// ライトの法線
float4 m_EyePos;				// カメラの座標
float4 m_Ambient;				// 色
float m_Specular;				// 反射の広さ
float m_SpecularPower;			// 反射の力
float m_Height;					// 高さの最大値。大きくするほど高くなる。
float m_Refraction;				// 屈折率
float m_ZF;						// 遠近射影行列の遠近距離

//=============================================================================
// テクスチャ情報
//=============================================================================
sampler tex0 : register(s0);	// 水面のテクスチャー
sampler tex1 : register(s1);	// 法線マップ(アルファ成分に高さ情報を格納)
sampler tex2 : register(s2);	// シーンのレンダリングイメージテクスチャー
sampler tex3 : register(s3);	// 反射マップテクスチャー
sampler tex4 : register(s4);	// 水面のマスクマップテクスチャー

//=============================================================================
// 構造体
//=============================================================================
struct VS_OUTPUT
{		
	float4 Pos : POSITION;			// ワールドマトリクス
	float2 Tex : TEXCOORD0;			// テクスチャ座標
	float3 Eye : TEXCOORD1;			// 視線ベクトル
	float3 Light : TEXCOORD2;		// ライトベクトル
	float3 RocalPos : TEXCOORD3;	// ローカル座標
	float4 PosWVP : TEXCOORD4;		// ワールド座標系の頂点座標
	float4 WVPPTPos : TEXCOORD5;	// スクリーン座標形状の頂点座標
	float3 Normal : TEXCOORD6;		// 法線ベクトル
};

//=============================================================================
// 頂点シェーダ
//=============================================================================
VS_OUTPUT VS(float3 Pos : POSITION, float3 Tangent : TANGENT0,
	float3 Binormal : BINORMAL0, float3 Normal : NORMAL, float2 Tex : TEXCOORD0)
{
	// 変数宣言
	VS_OUTPUT Out;
	
	// ワールド変換
	Out.Pos = mul( float4( Pos, 1.0f ), m_WVPP );
	Out.Tex = Tex;
	
	// 視線ベクトルを計算
	float3 Eye = normalize( m_EyePos.xyz - Pos.xyz );	// カメラとの距離
	
	// 視線ベクトルを頂点座標系に変換する
	Out.Eye.x = dot( Eye, Tangent );		// 接線ベクトル
	Out.Eye.y = dot( Eye, Binormal );		// 従法線ベクトル
	Out.Eye.z = dot( Eye, Normal );			// 主法線ベクトル
	Out.Eye = normalize( Out.Eye );			// 正規化
	
	// オブジェクトの頂点座標 -> ライトの位置ベクトル に変換する
	float3 Light = -m_LightDir.xyz;
	
	// ライトベクトルを頂点座標系に変換する
	Out.Light.x = dot(Light, Tangent );		// 接線ベクトル
	Out.Light.y = dot(Light, Binormal);		// 従法線ベクトル
	Out.Light.z = dot(Light, Normal);		// 主法線ベクトル
	Out.Light = normalize(Out.Light);		// 正規化
	
	// ローカル座標系上での頂点の座標
	Out.RocalPos = Pos;
	
	// ワールド座標系の頂点の座標
	Out.PosWVP = Out.Pos;
	
	// スクリーン座標形状での頂点の座標
	Out.WVPPTPos = mul( float4( Pos, 1.0f ), m_WVPPT );
	
	// 法線ベクトル
	Out.Normal = Normal;
	
	return Out;
}

//=============================================================================
// ピクセルシェーダ
//=============================================================================
float4 PS( VS_OUTPUT In ) : COLOR
{
	//*********************************************************************************************************
	//視差マッピング
	//*********************************************************************************************************
	// 高さマップを参照し、高さを取得する
	float fHeight = tex2D( tex1, In.Tex ).a;
	
	// テクセルを頂点座標系での視線ベクトル方向に重みをつけてずらす。
	float2 TexNormal = In.Tex + m_Height * fHeight * In.Eye.xy;
	
	// 法線マップを参照し、法線を取得する
	// 法線マップは -1.0f ～ 1.0f の値を 0.0f ～ 1.0f の範囲に保存してあるので変換する
	float3 Normal = 2.0f * tex2D( tex1, TexNormal).xyz - 1.0f;
	   
	// フォンシェーディングによるスペキュラーの色を計算する
	// 頂点 -> ライト位置ベクトル + 頂点 -> 視点ベクトル
	float3 LightH = normalize( In.Light + (float3)In.WVPPTPos + In.Eye );
	
	// スペキュラーカラーを計算する
	float Specular = pow(max(0.0f, dot(Normal, LightH)), m_Specular) * m_SpecularPower;
	
	// 拡散反射率
	float4 Diffuse = max( m_Ambient, dot( Normal, In.Light ) );
	// 水面の明るさ調整
	float spot = 0.5f;
	Diffuse = Diffuse * spot + (1.0f - spot);
	
	// 水面のマテリアル tex0
	float3 WaterCol = tex2D( tex0, TexNormal).rgb;
	
	// 海底のＺ値 (重なり)
	float SeabedZ = tex2Dproj( tex2, In.WVPPTPos ).a * 0.5f;

	// 水の厚みを計算する
	float WaterZ = /*SeabedZ -*/ In.PosWVP.z / m_ZF * 2;
	
	//*********************************************************************************************************
	//屈折
	//*********************************************************************************************************   
	// ゆがみ量の計算
	// 水の厚みが薄くなるほど屈折しないようにする
	float4 Offset = float4((Normal - In.Eye).xy * WaterZ * m_Refraction, 0.0f, 0.0f);
	
	// 海底の色
	float3 SeabedCol;
	
	// 反射マップの色
	float3 ReflectCol;
	
	// 水面のマスクマップを参照 tex4
	float Mask = tex2Dproj( tex4, In.WVPPTPos + Offset ).r;
	// マスクマップを参照したら水の部分だったのでゆがませる
	if (Mask == 1)
	{
		// 海底の色
		SeabedCol = tex2Dproj(tex2, In.WVPPTPos + Offset).rgb;
		// 反射マップの色
		ReflectCol = tex2Dproj(tex3, In.WVPPTPos + Offset).rgb;
	}
	// マスクマップを参照したら水の部分でなかったのでゆがませない
	else
	{
		// 海底の色
		SeabedCol = tex2Dproj(tex2, In.WVPPTPos).rgb;
		// 反射マップの色
		ReflectCol = tex2Dproj(tex3, In.WVPPTPos).rgb;
	}
	
	//*********************************************************************************************************
	// フレネル効果
	//*********************************************************************************************************
	// 頂点 → 視点ベクトル と 法線ベクトルの内積を計算
	float fresnel = dot(normalize(m_EyePos.xyz - In.RocalPos), normalize(In.Normal));
	
	// 内積の結果が0.0fに近いほど反射マップの色が強くなり、1.0fに近いほど海底マップの色が強くなるように線形合成する
	float4 Col;
	Col.rgb = lerp(ReflectCol, SeabedCol, fresnel);

	// 水面のテクスチャを透明にする
	WaterCol.x = 1.0f;
	WaterCol.y = 1.0f;
	WaterCol.z = 1.0f;
	Col.rgb = Col.rgb * (float3)Diffuse * WaterCol + Specular;
	
	//*********************************************************************************************************
	// 透明度
	//*********************************************************************************************************   
	//Ｚ値が小さくなるほど透明度を高くする（注意１）
	WaterZ = min(WaterZ * 20.0f, 1.0f);
	Col.rgb = lerp( SeabedCol, Col.rgb, WaterZ);
	Col.a = 1.0f;
	
	return Col;
}

//=============================================================================
// テクニック
//=============================================================================
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}
}
