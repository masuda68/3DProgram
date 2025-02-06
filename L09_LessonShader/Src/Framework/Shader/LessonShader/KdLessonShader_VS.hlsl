//カメラやライトのデータが消えるようになる
#include "../inc_KdCommon.hlsli"
#include "inc_KdLessonShader.hlsli"

VSOutput main(float4 pos	: POSITION,
			  float2 uv		: TEXCOORD,
			  float4 color	: COLOR)
{
	VSOutput Out;

	// ここ大事！(座標変換)
	Out.Pos = mul(pos, g_mWorld);	// ローカル座標系->	ワールド座標へ変換
	Out.Pos = mul(Out.Pos, g_mView); // ワールド座標系->	ビュー座標系へ変更
	Out.Pos = mul(Out.Pos, g_mProj);// ビュー座標系  ->	射影座標へ変換
	
	// 頂点色
	Out.Color = color;

	// UV座標
	Out.UV = uv;
	
	return Out;
}
