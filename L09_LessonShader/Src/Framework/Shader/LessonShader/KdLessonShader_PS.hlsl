// カメラやライトのデータが消えるようになる
#include "../inc_KdCommon.hlsli"
#include "inc_KdLessonShader.hlsli"

// テクスチャの受け取り（画像データ※そのままでは使えません）
Texture2D g_baseTex : register(t0);		// ベースカラーテクスチャー

// サンプラ（テクスチャから情報を抜き出す機能）
SamplerState g_ss : register(s0);		// 通商のテクスチャ描画用

// ピクセルシェーダー　一つ一つのピクセルがやってくる
// UV テクスチャー座標
float4 main(VSOutput In) : SV_TARGET
{
	return g_baseTex.Sample(g_ss, In.UV) * g_BaseColor * In.Color;
}
