﻿#pragma once

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;
	void DrawSprite()		override;
	void SetCamera(std::shared_ptr<KdCamera> _camera)
	{
		m_wpCamera = _camera;
	}
	void SetTerrain(std::shared_ptr<KdGameObject> _terrain)
	{
		m_wpTerrain = _terrain;
	}
private:
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;
	std::weak_ptr<KdCamera>			 m_wpCamera;
	std::weak_ptr<KdGameObject>		 m_wpTerrain;
	Math::Vector3 m_TargetPos;
	Math::Matrix mat;
	KdTexture m_tex;
};