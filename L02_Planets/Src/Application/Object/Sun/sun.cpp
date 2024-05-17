#include "sun.h"


sun::sun()
{
}

sun::~sun()
{
}

void sun::Update()
{

	Math::Matrix _mScale = Math::Matrix::CreateScale(1);
	Math::Matrix _mRotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(0, 0, 0);

	m_mWorld = _mScale * _mRotationX * _mTrans;
}

void sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_mWorld);
}

void sun::Init()
{
	m_model.Load("Asset/Data/LessonData/Planets/sun.gltf");
	m_objType = ObjectType::sun;
}
