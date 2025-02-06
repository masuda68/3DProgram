// 定数バッファ（メッシュ単位）
cbuffer cbMesh : register(b1)
{
	//オブジェクト情報
	row_major float4x4 g_mWorld; //ワールド座標行列
}

cbuffer cbMaterial : register(b2)
{
	float4 g_BaseColor;		// ベース色
	float3 g_Emissive;		// 自己発行色
	float g_Metallic;		// 金属度（メタリック）
	float g_Roughness;		// 荒さ(ラグネス)
}


//頂点シェーダから出力するデータ
struct VSOutput
{
	float4 Pos		: SV_Position;
	float2 UV		: TEXCOORD1;//テクスコード
	float4 Color	: TEXCOORD2;
};
