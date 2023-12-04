cbuffer SceneConstantBuffer : register(b0)
{
    float4x4 g_wvp;
};
//
//�o�[�e�b�N�X�V�F�[�_�[
//
float4 VS(float4 Pos : POSITION) : SV_POSITION
{
    float4 pos = mul(Pos, g_wvp);

    return pos;
}
//
//�s�N�Z���V�F�[�_�[
//
float4 PS(float4 Pos : SV_POSITION) : SV_Target
{
    return float4(1, 1, 0, 1);
}
