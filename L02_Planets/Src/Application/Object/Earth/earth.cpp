#include "earth.h"
#include "../Moon/Moon.h"

earth::earth()
{
}

earth::~earth()
{
}

void earth::Update()
{

	static float deg = 0;
	deg -= 1.0f;
	if (deg > 360)
	{
		deg -= 360;
	}
	Math::Matrix _mScale = Math::Matrix::CreateScale(1);
	Math::Matrix _mRotationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(deg));
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = _mScale * _mRotationY * _mTrans* _mRotationY;

}

void earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_mWorld);
}

void earth::Init()
{
	m_model.Load("Asset/Data/LessonData/Planets/earth.gltf");
	m_pos = {-20,0,0};
	m_mWorld.Translation(m_pos);
	m_angle = 0.0f;
	m_objType = ObjectType::earth;
}
