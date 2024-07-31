﻿#pragma once
class CameraBase:public KdGameObject
{
public:
	CameraBase() {};
	virtual  ~CameraBase()override {};

	void Init()override;
	void Update()override;
	void PreDraw();

	void SetTarget(const std::shared_ptr<KdGameObject>& target)
	{
		m_spTarget = target;
	}

	void RegisHitObject(const std::shared_ptr<KdGameObject>& object)
	{
		m_wpHitObjectList.push_back(object);
	}

	const Math::Matrix GetRotationYMatrix()const;
protected:
	void UpdateRotateByMouse();
	const Math::Matrix GetRotaionMatrix()const;
	std::weak_ptr<KdGameObject>m_spTarget;
	std::vector<std::weak_ptr<KdGameObject>> m_wpHitObjectList;
	std::shared_ptr<KdCamera> m_spCamera = nullptr;

	Math::Matrix m_mLocalPos=Math::Matrix::Identity;
	Math::Matrix m_mRot = Math::Matrix::Identity;

	//カメラ回転用マウス座標
	POINT m_FixMousePos{};
private:
	//カメラの回転用角度
	Math::Vector3 m_DegAng = Math::Vector3::Zero;
};

