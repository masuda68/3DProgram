#include "Hamu.h"

Hamu::Hamu()
{
}

Hamu::~Hamu()
{
}

void Hamu::Update()
{
	//ハム太郎の更新
	float moveSpd = 0.05;
	Math::Vector3 _moveVec;
	Math::Vector3 m_pos = m_mWorld.Translation();
	//float _len = _moveVec.Length();


	if (GetAsyncKeyState('A'))
	{
		_moveVec.x -= moveSpd;
		//m_HamWorld._43-=0.1;
	}
	if (GetAsyncKeyState('D'))
	{
		//m_Vec.y += 0.05;
		_moveVec.x += moveSpd;
		//m_HamWorld._43+=0.1;
	}
	if (GetAsyncKeyState('W'))
	{
		//m_Vec.y += 0.05;
		_moveVec.z += moveSpd;
		//m_HamWorld._41+=0.1;
	}
	if (GetAsyncKeyState('S'))
	{
		//m_Vec.y += 0.05;
		_moveVec.z -= moveSpd;
		////m_HamWorld._41-=0.1;
	}

	_moveVec.Normalize();//
	_moveVec *= moveSpd;
	m_pos += _moveVec;
	Math::Matrix _mScale = Math::Matrix::CreateScale(1);
	Math::Matrix _mRotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(15));
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _mScale * _mRotationX * _mTrans;

}

void Hamu::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Hamu::Init()
{
	//===================================================================
	// ハム太郎初期化
	//===================================================================
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
	m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}
