#pragma once
class sun:public KdGameObject
{
public:
	sun();
	~sun()override;

	void Update()override;
	void DrawLit()override;
	void Init()override;
private:
	KdModelData m_model;
};

