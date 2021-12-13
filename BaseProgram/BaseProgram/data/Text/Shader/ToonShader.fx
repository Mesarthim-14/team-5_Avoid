//=============================================================================
//
// �g�D�[���V�F�[�_ [ToonShader.fx]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
float4x4 m_WVP;						// ���[���h �~ �r���[ �~ ���ߎˉe
float4x4 m_pMtxWorld;				// �}�g���N�X���[���h
float4 m_LightDir;					// ���s�����̕����x�N�g��
float2 m_Texel;						// �P�e�N�Z���̃T�C�Y
float m_Limit;						// �G�b�W�ƂȂ邩�𔻒肷�邽�߂̊�l�B1.0f�ŃG�b�W�t�B���^�[�������ɂȂ�B
float4 m_EyePos;					// �J�����̍��W
float4 m_Diffuse;					// �}�e���A���̐F

float4x4 matWorld[4]: WORLD;		// ���[���h�ϊ��s��z��

float4x4 matView : VIEW;            // �r���[�ϊ��s��
float4x4 matProj : PROJECTION;      // �ˉe�ϊ��s��
int iBlendNum;                      // �u�����h����z��̐�

//=============================================================================
// �e�N�X�`�����
//=============================================================================
sampler tex0 : register(s0);		// �I�u�W�F�N�g�̃e�N�X�`���[/�擾�����F�̃e�N�X�`��
sampler tex1 : register(s1);		// �g�D�[���}�b�v�e�N�X�`���[/Z�l���Q�Ƃ��֊s���o�����߂̃e�N�X�`��

//=============================================================================
// �\����
//=============================================================================
struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	float3 Normal : TEXCOORD1;
	float4 Depth : TEXCOORD2;
};

//=============================================================================
// �s�N�Z���V�F�[�_�[�ŏo�͂���F���
//=============================================================================
struct PS_OUTPUT
{
	float4 Col1 : COLOR0;   //�V�[���̐F���
	float4 Col2 : COLOR1;   //�V�[����Z�l���
    float4 Canvas : COLOR2; // �L�����o�X�p�̏��
};

//=============================================================================
// ���_�V�F�[�_(�X�L�����b�V��)
//=============================================================================
VS_OUTPUT VS(float4 Pos : POSITION, float4 World : BLENDWEIGHT,
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
	matCombWorld += matWorld[iBlendNum-1] * (1.0f - LastBlendWeight);

	P_after = mul(Pos, matCombWorld);	// ���[���h�ϊ�
	P_after = mul(P_after, matView);    // �r���[�ϊ�
	P_after = mul(P_after, matProj);    // �ˉe�ϊ�

	Out.Pos = P_after;
	Out.Tex = Tex;

	Out.Normal = normalize(Normal.xyz);
	//Z�l�͉��ߎˉe�s��Ŏ擾����
	Out.Depth = Out.Pos;

	return Out;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
PS_OUTPUT PS(VS_OUTPUT In) : COLOR0
{
	float4 Out;
	PS_OUTPUT ps = (PS_OUTPUT)0;
	// �n�[�t�����o�[�g�g�U�Ɩ��ɂ�郉�C�e�B���O�v�Z
	float p = dot(In.Normal, -m_LightDir.xyz);
	p = p * 0.5f + 0.5f;
	p = p * p;
	
    float canvas = dot(In.Normal, -m_LightDir.xyz);
    canvas = canvas * 1.0f + 0.6f;
    canvas = canvas * canvas;

	//****************************************************************
	// �g�D�[���V�F�[�_�[����
	//****************************************************************
	//�F�����e�N�Z���̂t�����Ƃ��A�g�D�[���}�b�v�e�N�X�`���[������̔��˗����擾����
	float4 Col = tex2D(tex1, float2(p, 0.0f));
	Out = Col * tex2D(tex0, In.Tex);
	//�F����RGB�Ɋi�[����
	ps.Col1 = Out * tex2D(tex0, In.Tex);

	//�[�x�����i�[����B
	//Z / W �ɂ�� 0 ���� 1 �̊Ԃɐ��K�����ꂽZ�l���ɕϊ�����B
	ps.Col2 = In.Depth.z / In.Depth.w;
	
    ps.Canvas = max((float4)0, canvas);
    ps.Canvas.a = 1.0f;

	return ps;
}

//=============================================================================
// �s�N�Z���V�F�[�_(�e�N�X�`������)
//=============================================================================
PS_OUTPUT ps_not_tex(VS_OUTPUT In) : COLOR0
{
    float4 Out;
    PS_OUTPUT ps = (PS_OUTPUT)0;
    // �n�[�t�����o�[�g�g�U�Ɩ��ɂ�郉�C�e�B���O�v�Z
    float p = dot(In.Normal, -m_LightDir.xyz);
    p = p * 0.5f + 0.5f;
    p = p * p;
    
    float canvas = dot(In.Normal, -m_LightDir.xyz);
    canvas = canvas * 1.0f + 0.6f;
    canvas = canvas * canvas;
    
    //****************************************************************
    // �g�D�[���V�F�[�_�[����
    //****************************************************************
    //�F�����e�N�Z���̂t�����Ƃ��A�g�D�[���}�b�v�e�N�X�`���[������̔��˗����擾����
    float4 Col = tex2D(tex1, float2(p, 0.0f));
    Out = Col * m_Diffuse;

    //�F����RGB�Ɋi�[����
    ps.Col1 = Out * m_Diffuse;
    
    //�[�x�����i�[����B
    //Z / W �ɂ�� 0 ���� 1 �̊Ԃɐ��K�����ꂽZ�l���ɕϊ�����B
    ps.Col2 = In.Depth.z / In.Depth.w;
    
    ps.Canvas = max((float4)0, canvas);
    ps.Canvas.a = 1.0f;

    return ps;
}


//=============================================================================
// �\����
//=============================================================================
struct EdgeVS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};

//=============================================================================
// ���_�V�F�[�_
//=============================================================================
EdgeVS_OUTPUT EdgeVS(float4 Pos : POSITION, 
	float4 Col : COLOR0, float2 Tex : TEXCOORD0)
{
	EdgeVS_OUTPUT Out;

	Out.Pos = Pos;
	Out.Tex = Tex;

	return Out;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 EdgePS(EdgeVS_OUTPUT In) : COLOR0
{
	float4 Col = float4(0.0f, 0.0f, 0.0f, 1.0f);

	// �y�l���ŏ�������ł���e�N�X�`���[���Q�Ƃ��A���݂̃s�N�Z���ʒu�̂y�l���擾
	float Z1 = tex2D(tex1, In.Tex).r;

	// ���ӂ̃s�N�Z���ʒu�̂y�l���擾
	float Z2 = tex2D(tex1, clamp(In.Tex + float2(m_Texel.x,  m_Texel.y), 0.0f, 1.0f)).r;
	float Z3 = tex2D(tex1, clamp(In.Tex + float2(m_Texel.x, -m_Texel.y), 0.0f, 1.0f)).r;
	float Z4 = tex2D(tex1, clamp(In.Tex + float2(-m_Texel.x,  m_Texel.y), 0.0f, 1.0f)).r;
	float Z5 = tex2D(tex1, clamp(In.Tex + float2(-m_Texel.x, -m_Texel.y), 0.0f, 1.0f)).r;

	// ���ӂ̃s�N�Z���ʒu�̂y�l�Ɣ�r���Am_Limit���傫���Ƃ��낪��������G�b�W�����Ɣ��肷��
	if (abs(Z1 - Z2) < m_Limit &&
		abs(Z1 - Z3) < m_Limit &&
		abs(Z1 - Z4) < m_Limit &&
		abs(Z1 - Z5) < m_Limit)
	{
		Col = tex2D(tex0, In.Tex);
	}

	return Col;
}

//=============================================================================
// ���_�V�F�[�_
//=============================================================================
VS_OUTPUT NormalVS(float4 Pos : POSITION,
    float4 Normal : NORMAL, float2 Tex : TEXCOORD0)
{
    VS_OUTPUT Out;

    Out.Pos = mul(Pos, m_WVP);
    Out.Tex = Tex;

    Out.Normal = normalize(Normal.xyz);

    //Z�l�͉��ߎˉe�s��Ŏ擾����
    Out.Depth = mul(Pos, m_WVP);

    return Out;
}

//=============================================================================
// �e�N�j�b�N
//=============================================================================
technique TShader
{
	// �g�D�[���V�F�[�_
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}

	// �G�b�W�V�F�[�_
	pass P1
	{
		VertexShader = compile vs_1_1 EdgeVS();
		PixelShader = compile ps_2_0 EdgePS();
	}
    // �G�b�W�V�F�[�_
    pass P2
    {
        VertexShader = compile vs_1_1 NormalVS();
        PixelShader = compile ps_2_0 PS();
    }
    // 
    pass P3
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader = compile ps_2_0 ps_not_tex();

    }

}