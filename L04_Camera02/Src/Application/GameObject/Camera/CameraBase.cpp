#include "CameraBase.h"

void CameraBase::Init()
{
	if (!m_spCamera)
	{
		m_spCamera = std::make_shared<KdCamera>();
	}
}

void CameraBase::Update()
{
	//ヌルチェック必須//
	if (!m_spCamera)return;

	m_spCamera->SetCameraMatrix(m_mWorld);
}

void CameraBase::PreDraw()
{
	if (!m_spCamera)return;
	m_spCamera->SetToShader();
}
