#include "Water.h"

void Water::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/LessonData/Stage/Water/Water.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Water", m_spModel, KdCollider::TypeGround);

		SetPos({0, 0.5f, 0});
		SetScale(2);
	}
}

void Water::Update()
{
	m_UVOffset.x += 0.0001f;
	m_UVOffset.y += 0.0001f;
}

void Water::DrawLesson()
{
	if (!m_spModel) return;
	Math::Color c = { 1,1,1,0.5f };
	KdShaderManager::Instance().m_LessonShader.SetUVOffset(m_UVOffset);
	KdShaderManager::Instance().m_LessonShader.DrawModel(*m_spModel->GetData(), m_mWorld,c);

}

