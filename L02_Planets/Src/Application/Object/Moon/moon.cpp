#include "Moon.h"

moon::moon()
{
}

moon::~moon()
{
}

void moon::Update()
{
	static float _deg = 0;
	//地球の座標を格納してる
	m_mEarthTrans = Math::Matrix::CreateTranslation(m_mWorld.Translation());
	_deg -= 1.0f;
	if (_deg > 360)
	{
		_deg -= 360;
	}

	Math::Matrix _mScale = Math::Matrix::CreateScale(2);
	Math::Matrix _mRotationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_deg));
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(m_pos.x+2, m_pos.y, m_pos.z);
	//月*地球
	m_mWorld = (_mScale* _mRotationY *_mTrans * _mRotationY) * m_mEarthTrans;
}

void moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_mWorld);
}

void moon::Init()
{
	m_model.Load("Asset/Data/LessonData/Planets/moon.gltf");
	m_pos = {};
	m_objType = ObjectType::moon;
}


