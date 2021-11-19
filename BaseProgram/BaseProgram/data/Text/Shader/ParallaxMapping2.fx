//=============================================================================
//
// �����}�b�v�̃V�F�[�_ [ParallaxMapping2.fx]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
float4x4 m_WVPP;				// �s��ϊ��}�g���N�X
float4x4 m_WVPPT;				// �X�N���[�����W�n�̃}�g���N�X
float4 m_LightDir;				// ���C�g�̖@��
float4 m_EyePos;				// �J�����̍��W
float4 m_Ambient;				// �F
float m_Specular;				// ���˂̍L��
float m_SpecularPower;			// ���˂̗�
float m_Height;					// �����̍ő�l�B�傫������قǍ����Ȃ�B
float m_Refraction;				// ���ܗ�
float m_ZF;						// ���ߎˉe�s��̉��ߋ���

//=============================================================================
// �e�N�X�`�����
//=============================================================================
sampler tex0 : register(s0);	// ���ʂ̃e�N�X�`���[
sampler tex1 : register(s1);	// �@���}�b�v(�A���t�@�����ɍ��������i�[)
sampler tex2 : register(s2);	// �V�[���̃����_�����O�C���[�W�e�N�X�`���[
sampler tex3 : register(s3);	// ���˃}�b�v�e�N�X�`���[
sampler tex4 : register(s4);	// ���ʂ̃}�X�N�}�b�v�e�N�X�`���[

//=============================================================================
// �\����
//=============================================================================
struct VS_OUTPUT
{		
	float4 Pos : POSITION;			// ���[���h�}�g���N�X
	float2 Tex : TEXCOORD0;			// �e�N�X�`�����W
	float3 Eye : TEXCOORD1;			// �����x�N�g��
	float3 Light : TEXCOORD2;		// ���C�g�x�N�g��
	float3 RocalPos : TEXCOORD3;	// ���[�J�����W
	float4 PosWVP : TEXCOORD4;		// ���[���h���W�n�̒��_���W
	float4 WVPPTPos : TEXCOORD5;	// �X�N���[�����W�`��̒��_���W
	float3 Normal : TEXCOORD6;		// �@���x�N�g��
};

//=============================================================================
// ���_�V�F�[�_
//=============================================================================
VS_OUTPUT VS(float3 Pos : POSITION, float3 Tangent : TANGENT0,
	float3 Binormal : BINORMAL0, float3 Normal : NORMAL, float2 Tex : TEXCOORD0)
{
	// �ϐ��錾
	VS_OUTPUT Out;
	
	// ���[���h�ϊ�
	Out.Pos = mul( float4( Pos, 1.0f ), m_WVPP );
	Out.Tex = Tex;
	
	// �����x�N�g�����v�Z
	float3 Eye = normalize( m_EyePos.xyz - Pos.xyz );	// �J�����Ƃ̋���
	
	// �����x�N�g���𒸓_���W�n�ɕϊ�����
	Out.Eye.x = dot( Eye, Tangent );		// �ڐ��x�N�g��
	Out.Eye.y = dot( Eye, Binormal );		// �]�@���x�N�g��
	Out.Eye.z = dot( Eye, Normal );			// ��@���x�N�g��
	Out.Eye = normalize( Out.Eye );			// ���K��
	
	// �I�u�W�F�N�g�̒��_���W -> ���C�g�̈ʒu�x�N�g�� �ɕϊ�����
	float3 Light = -m_LightDir.xyz;
	
	// ���C�g�x�N�g���𒸓_���W�n�ɕϊ�����
	Out.Light.x = dot(Light, Tangent );		// �ڐ��x�N�g��
	Out.Light.y = dot(Light, Binormal);		// �]�@���x�N�g��
	Out.Light.z = dot(Light, Normal);		// ��@���x�N�g��
	Out.Light = normalize(Out.Light);		// ���K��
	
	// ���[�J�����W�n��ł̒��_�̍��W
	Out.RocalPos = Pos;
	
	// ���[���h���W�n�̒��_�̍��W
	Out.PosWVP = Out.Pos;
	
	// �X�N���[�����W�`��ł̒��_�̍��W
	Out.WVPPTPos = mul( float4( Pos, 1.0f ), m_WVPPT );
	
	// �@���x�N�g��
	Out.Normal = Normal;
	
	return Out;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 PS( VS_OUTPUT In ) : COLOR
{
	//*********************************************************************************************************
	//�����}�b�s���O
	//*********************************************************************************************************
	// �����}�b�v���Q�Ƃ��A�������擾����
	float fHeight = tex2D( tex1, In.Tex ).a;
	
	// �e�N�Z���𒸓_���W�n�ł̎����x�N�g�������ɏd�݂����Ă��炷�B
	float2 TexNormal = In.Tex + m_Height * fHeight * In.Eye.xy;
	
	// �@���}�b�v���Q�Ƃ��A�@�����擾����
	// �@���}�b�v�� -1.0f �` 1.0f �̒l�� 0.0f �` 1.0f �͈̔͂ɕۑ����Ă���̂ŕϊ�����
	float3 Normal = 2.0f * tex2D( tex1, TexNormal).xyz - 1.0f;
	   
	// �t�H���V�F�[�f�B���O�ɂ��X�y�L�����[�̐F���v�Z����
	// ���_ -> ���C�g�ʒu�x�N�g�� + ���_ -> ���_�x�N�g��
	float3 LightH = normalize( In.Light + (float3)In.WVPPTPos + In.Eye );
	
	// �X�y�L�����[�J���[���v�Z����
	float Specular = pow(max(0.0f, dot(Normal, LightH)), m_Specular) * m_SpecularPower;
	
	// �g�U���˗�
	float4 Diffuse = max( m_Ambient, dot( Normal, In.Light ) );
	// ���ʂ̖��邳����
	float spot = 0.5f;
	Diffuse = Diffuse * spot + (1.0f - spot);
	
	// ���ʂ̃}�e���A�� tex0
	float3 WaterCol = tex2D( tex0, TexNormal).rgb;
	
	// �C��̂y�l (�d�Ȃ�)
	float SeabedZ = tex2Dproj( tex2, In.WVPPTPos ).a * 0.5f;

	// ���̌��݂��v�Z����
	float WaterZ = /*SeabedZ -*/ In.PosWVP.z / m_ZF * 2;
	
	//*********************************************************************************************************
	//����
	//*********************************************************************************************************   
	// �䂪�ݗʂ̌v�Z
	// ���̌��݂������Ȃ�قǋ��܂��Ȃ��悤�ɂ���
	float4 Offset = float4((Normal - In.Eye).xy * WaterZ * m_Refraction, 0.0f, 0.0f);
	
	// �C��̐F
	float3 SeabedCol;
	
	// ���˃}�b�v�̐F
	float3 ReflectCol;
	
	// ���ʂ̃}�X�N�}�b�v���Q�� tex4
	float Mask = tex2Dproj( tex4, In.WVPPTPos + Offset ).r;
	// �}�X�N�}�b�v���Q�Ƃ����琅�̕����������̂ł䂪�܂���
	if (Mask == 1)
	{
		// �C��̐F
		SeabedCol = tex2Dproj(tex2, In.WVPPTPos + Offset).rgb;
		// ���˃}�b�v�̐F
		ReflectCol = tex2Dproj(tex3, In.WVPPTPos + Offset).rgb;
	}
	// �}�X�N�}�b�v���Q�Ƃ����琅�̕����łȂ������̂ł䂪�܂��Ȃ�
	else
	{
		// �C��̐F
		SeabedCol = tex2Dproj(tex2, In.WVPPTPos).rgb;
		// ���˃}�b�v�̐F
		ReflectCol = tex2Dproj(tex3, In.WVPPTPos).rgb;
	}
	
	//*********************************************************************************************************
	// �t���l������
	//*********************************************************************************************************
	// ���_ �� ���_�x�N�g�� �� �@���x�N�g���̓��ς��v�Z
	float fresnel = dot(normalize(m_EyePos.xyz - In.RocalPos), normalize(In.Normal));
	
	// ���ς̌��ʂ�0.0f�ɋ߂��قǔ��˃}�b�v�̐F�������Ȃ�A1.0f�ɋ߂��قǊC��}�b�v�̐F�������Ȃ�悤�ɐ��`��������
	float4 Col;
	Col.rgb = lerp(ReflectCol, SeabedCol, fresnel);

	// ���ʂ̃e�N�X�`���𓧖��ɂ���
	WaterCol.x = 1.0f;
	WaterCol.y = 1.0f;
	WaterCol.z = 1.0f;
	Col.rgb = Col.rgb * (float3)Diffuse * WaterCol + Specular;
	
	//*********************************************************************************************************
	// �����x
	//*********************************************************************************************************   
	//�y�l���������Ȃ�قǓ����x����������i���ӂP�j
	WaterZ = min(WaterZ * 20.0f, 1.0f);
	Col.rgb = lerp( SeabedCol, Col.rgb, WaterZ);
	Col.a = 1.0f;
	
	return Col;
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
}
