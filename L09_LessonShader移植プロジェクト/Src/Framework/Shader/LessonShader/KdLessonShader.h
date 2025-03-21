﻿#pragma once

class KdLessonShader
{
public:
	// 定数バッファ(オブジェクト単位更新)
	struct cbObject
	{
		// UV操作
		Math::Vector2	UVOffset = { 0.0f, 0.0f };
		Math::Vector2	UVTiling = { 1.0f, 1.0f };

		// フォグ有効
		int				FogEnable = 1;

		// エミッシブのみの描画
		int				OnlyEmissie = 0;

		// スキンメッシュオブジェクトかどうか(スキンメッシュ対応)
		int				IsSkinMeshObj = 0;

		// ディゾルブ関連
		float			DissolveThreshold = 0.0f;	// 0 ～ 1
		float			DissolveEdgeRange = 0.03f;	// 0 ～ 1

		Math::Vector3	DissolveEmissive = { 0.0f, 1.0f, 1.0f };
	};


	//定数バッファ（メッシュ単位更新）
	struct cbMesh
	{
		Math::Matrix mW;
	};

	//定数バッファ（マテリアル単位更新）
	struct cbMaterial
	{
		Math::Vector4		BaseColor = { 1.0f,1.0f,1.0f,1.0f };

		Math::Vector3		Emissive = { 1.0f,1.0f,1.0f };
		float				Metallic = 0.0f;

		float				Roughness = 1.0f;
		float				_blank[3] = { 0.0f,0.0f,0.0f };
	};

public:

    //================================================
    // 初期化・解放
    //================================================

    // 初期化
    bool Init();
    // 解放
    void Release();

    // デストラクタで自動で解放するようにする
    ~KdLessonShader() { Release(); }

    //================================================
    // 描画準備
    //================================================
    // 陰影をつけるオブジェクト等を描画する前後に行う
    void Begin();
    void End();

	// 最も初めに行う、光を遮るオブジェクトを描画する前後に行う
	void BeginGenerateDepthMapFromLight();
	void EndGenerateDepthMapFromLight();

    //================================================
    // 描画関数
    //================================================
    // メッシュ描画
    void DrawMesh(const KdMesh* mesh, const Math::Matrix& mWorld, const std::vector<KdMaterial>& materials,
        const Math::Vector4& col, const Math::Vector3& emissive);

    // モデルデータ描画：アニメーションに非対応
    void DrawModel(const KdModelData& rModel, const Math::Matrix& mWorld = Math::Matrix::Identity,
        const Math::Color& colRate = kWhiteColor, const Math::Vector3& emissive = Math::Vector3::Zero);

private:

	// マテリアルのセット
	void WriteMaterial(const KdMaterial& material, const Math::Vector4& colRate, const Math::Vector3& emiRate);

    ID3D11VertexShader* m_VS            = nullptr;				// 頂点シェーダー
    ID3D11PixelShader*  m_PS            = nullptr;				// ピクセルシェーダー

    ID3D11InputLayout*  m_inputLayout   = nullptr;				// 頂点入力レイアウト

    //定数バッファ
	KdConstantBuffer<cbMesh>		m_cb1_Mesh;					//メッシュ毎に更新
	KdConstantBuffer<cbMaterial>	m_cb2_Material;				//マテリアル毎に更新

	KdRenderTargetPack	m_depthMapFromLightRTPack;
	KdRenderTargetChanger m_depthMapFromLightRTChanger;

};
