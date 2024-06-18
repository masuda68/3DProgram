#include "Character.h"
#include"Application/main.h"
#include"../../main.h"


void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
	m_tex.Load("Asset/Textures/T.png");
}

void Character::Update()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{

		//①マウス座標を取得する
		POINT _mouse = {};
		GetCursorPos(&_mouse);
		ScreenToClient(Application::Instance().GetWindowHandle(), &_mouse);
		std::shared_ptr<KdCamera>_camera = m_wpCamera.lock();
		if (_camera)
		{
			//②レイの発射方向を求める
			Math::Vector3 _dir = { 0,0,0 };
			Math::Vector3 _camPos = _camera->GetCameraMatrix().Translation();
			float _ray = 1000.0f;
			_camera->GenerateRayInfoFromClientPos(_mouse, _camPos, _dir, _ray);
			
			//③実際に例を飛ばして衝突位置を求める
			const std::shared_ptr<KdGameObject> _terrain = m_wpTerrain.lock();
			if (_terrain)
			{
				Math::Vector3 _endRayPos = _camPos + (_dir * _ray);
				KdCollider::RayInfo _rayInfo(KdCollider::TypeGround,_camPos, _endRayPos);
				
				//実際の当たり判定の処理
				std::list<KdCollider::CollisionResult> _results;
				_terrain->Intersects(_rayInfo,&_results);

				//結果が一つでも変ええてきていたら
				if (_results.size())
				{
					for (const KdCollider::CollisionResult &result : _results)
					{
						m_TargetPos = result.m_hitPos;
					}
				}
			}
		}
	}

	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	//Math::Vector3 nowPos = m_TargetPos;
	Math::Vector3 nowPos = GetPos();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	
	moveVec = (m_TargetPos - nowPos);
	if (moveVec.Length() < moveSpd) { moveSpd = moveVec.Length(); }
	moveVec.Normalize();

	moveVec *= moveSpd;
	nowPos += moveVec;

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	std::shared_ptr<KdCamera>_camera = m_wpCamera.lock();
	if (_camera)
	{
		Math::Vector3 result = Math::Vector3::Zero;
		_camera->ConvertWorldToScreenDetail(GetPos(), result);
		Math::Matrix trans, scale;
		trans = Math::Matrix::CreateTranslation(result.x, result.y,0);
		scale = Math::Matrix::CreateScale(1);
		mat = scale * trans;

		Math::Color _color = { 1,1,1,1 };
		Math::Rectangle _rec = { 0,0,50,34 };

		KdShaderManager::Instance().m_spriteShader.DrawCircle(result.x, result.y, 5, &kRedColor);

		KdShaderManager::Instance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0,50,34 ,&_rec, &_color);

	}
}

