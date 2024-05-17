#pragma once
class Application;
class earth :public KdGameObject
{
public:
	earth();
	~earth()override;

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:
	KdModelData m_model;
	float m_angle;
	Math::Vector3 m_pos;
};

