#pragma once
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
protected:
	std::weak_ptr<KdGameObject>m_spTarget;
	std::shared_ptr<KdCamera> m_spCamera = nullptr;

	Math::Matrix m_mLocalPos=Math::Matrix::Identity;
	Math::Matrix m_mRot = Math::Matrix::Identity;
};

