#pragma once
class moon :public KdGameObject
{
public:
	moon();
	~moon()override;

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:
	KdModelData m_model;
	Math::Matrix m_mEarthTrans;
	Math::Vector3 m_pos;
};

