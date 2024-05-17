#pragma once
class Hamu: public KdGameObject
{
public:
	Hamu();
	~Hamu() override;
	void Update()override;
	void DrawLit()override;
	void Init()override;
private:

	//ポリゴンデータ
	std::shared_ptr<KdSquarePolygon>	m_spPoly = nullptr;
};

