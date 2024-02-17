// スキニング用コンピュートシェーダー
// 必要な構造体とバッファ定義

struct VertexIn
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    uint4 boneIndices : BONEINDICES;
    float4 boneWeights : BONEWEIGHTS;
};

struct VertexOut
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

StructuredBuffer<VertexIn> InputVertices : register(t0);
StructuredBuffer<float4x4> BoneTransforms : register(t1);
RWStructuredBuffer<VertexOut> OutputVertices : register(u0);

[numthreads(256, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    VertexIn vin = InputVertices[DTid.x];

    float4x4 boneTransform = BoneTransforms[vin.boneIndices.x] * vin.boneWeights.x +
                             BoneTransforms[vin.boneIndices.y] * vin.boneWeights.y +
                             BoneTransforms[vin.boneIndices.z] * vin.boneWeights.z +
                             BoneTransforms[vin.boneIndices.w] * vin.boneWeights.w;

    float4 pos = mul(boneTransform, float4(vin.position, 1.0));
    float4 norm = mul(boneTransform, float4(vin.normal, 0.0));

    OutputVertices[DTid.x].position = pos.xyz;
    OutputVertices[DTid.x].normal = normalize(norm.xyz);
}
