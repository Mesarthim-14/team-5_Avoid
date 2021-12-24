//=============================================================================
//
// ���ʔ��˂̃V�F�[�_ [Reflect.fx]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
float4x4 m_WVPP;                 //���[���h�s�� �~ �r���[ �~ ���ߎˉe�s��
float4x4 m_W;                    //���[���h�s��̂�
float4 m_LightDir;
float4 m_Ambient;
float  m_Height;

float4x4 matWorld[4]: WORLD;		// ���[���h�ϊ��s��z��

float4x4 matView : VIEW;            // �r���[�ϊ��s��
float4x4 matProj : PROJECTION;      // �ˉe�ϊ��s��
int iBlendNum;                      // �u�����h����z��̐�

// �I�u�W�F�N�g�̃e�N�X�`���[
sampler tex0 : register(s0);

//=============================================================================
// �\����
//=============================================================================
struct VS_OUTPUT
{
	float4 Pos : POSITION;		// ���g
	float4 Col : COLOR0;		// �F
	float2 Tex : TEXCOORD0;		// �e�N�X�`�����W
	float4 WPos : TEXCOORD1;	// ���[���h���W
};

//=============================================================================
// ���_�V�F�[�_
//=============================================================================
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal: NORMAL, float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;
	
	Out.Pos = mul( Pos, m_WVPP );	// ���[���h�ϊ�
	Out.Tex = Tex;					// �e�N�X�`�����W
	
	float3 Light = -m_LightDir.xyz;					// ���C�g�̔��]
	float3 NorLight = normalize(Normal.xyz);		// ���K��
	Out.Col = max(m_Ambient, dot(NorLight, Light));	// �F�̐ݒ�
	Out.WPos = mul( Pos, m_W );						// ���[���h�s��̂�
	
	return Out;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 PS( VS_OUTPUT In ) : COLOR0
{
	// �ϐ��錾
	float4 Color;
	
	// ���˃C���[�W�̃��[���h���W�`��ł̒��_�� Y ���W��m_Height�ϐ���荂���Ƃ��`�悵�Ȃ��悤�ɂ���
	// ����ɂ�萅�ʉ��̃C���[�W�̂݃����_�����O����
	clip( m_Height - In.WPos.y );	// clip(x) x��0�ȉ��ɂȂ�����s�N�Z����j��
	
	// �F����RGB�Ɋi�[����
	Color.rgb = tex2D( tex0, In.Tex ).rgb * In.Col.rgb;
	Color.a = 1.0f;
	   
	return Color;
}

//=============================================================================
// ���_�V�F�[�_(�X�L�����b�V��)
//=============================================================================
VS_OUTPUT SkinmeshVS(float4 Pos : POSITION, float4 World : BLENDWEIGHT,
    float4 Normal : NORMAL, float2 Tex : TEXCOORD0)
{
    VS_OUTPUT Out;

    float4 P_after;							// �o�͒��_���W
    float Weight[4] = (float[4])World;		// �d�݂�float�ɕ������܂�
    float LastBlendWeight = 0.0f;			// �Ō�̍s��Ɋ|������d��
    float4x4 matCombWorld = 0.0f;			// �������[���h�ϊ��s��
    for (int nCount = 0; nCount < iBlendNum - 1; nCount++)
    {
        LastBlendWeight += Weight[nCount];		// �Ō�̏d�݂������Ōv�Z���Ă���
        matCombWorld += matWorld[nCount] * Weight[nCount];
    }

    // �Ō�̏d�݂𑫂��Z
    matCombWorld += matWorld[iBlendNum - 1] * (1.0f - LastBlendWeight);

    P_after = mul(Pos, matCombWorld);	// ���[���h�ϊ�
    //Z�l�͉��ߎˉe�s��Ŏ擾����
    Out.WPos = mul(Pos, P_after);

    P_after = mul(P_after, matView);    // �r���[�ϊ�
    P_after = mul(P_after, matProj);    // �ˉe�ϊ�

    Out.Pos = P_after;
    Out.Tex = Tex;

    float3 Light = -m_LightDir.xyz;                 // ���C�g�̔��]
    float3 NorLight = normalize(Normal.xyz);        // ���K��
    Out.Col = max(m_Ambient, dot(NorLight, Light)); // �F�̐ݒ�

    return Out;
}

//=============================================================================
// �e�N�j�b�N
//=============================================================================
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}
    pass P1
    {
        VertexShader = compile vs_1_1 SkinmeshVS();
        PixelShader = compile ps_2_0 PS();
    }

}