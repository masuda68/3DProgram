#include "inc_KdLessonShader.hlsli"
#include "../inc_KdCommon.hlsli"

//================================
// 頂点シェーダ
//================================
VSOutput main(
	float4 pos : POSITION,		// 頂点座標
	float2 uv : TEXCOORD0,		// テクスチャUV座標
	float4 color : COLOR,		// 頂点カラー
	float3 normal : NORMAL,		// 法線
	float3 tangent : TANGENT)	// 接線
{
	VSOutput Out;

	// アウトライン描画チェック
	if (g_EnableOutLineDraw)
	{
		// 頂点座標を「法線方向」に少しずらす
		pos.xyz = pos.xyz + normal * 0.03;
	}

	// 座標変換
	Out.Pos = mul(pos, g_mWorld);		// ローカル座標系	-> ワールド座標系へ変換
	Out.wPos = Out.Pos.xyz;				// ワールド座標を別途保存
	Out.Pos = mul(Out.Pos, g_mView);	// ワールド座標系	-> ビュー座標系へ変換
	Out.Pos = mul(Out.Pos, g_mProj);	// ビュー座標系		-> 射影座標系へ変換

	// 頂点色
	Out.Color = color;

	// 法線
	Out.wN = normalize(mul(normal, (float3x3) g_mWorld));
	// 接線
	Out.wT = normalize(mul(tangent, (float3x3) g_mWorld));
	// 従接線
	float3 binormal = cross(normal, tangent);
	Out.wB = normalize(mul(binormal, (float3x3) g_mWorld));

	// UV座標
	Out.UV = uv * g_UVTiling + g_UVOffset;
	// 本告授業
	Out.UV2 = uv * g_UVTiling - g_UVOffset;
	
	// 出力
	return Out;
}
