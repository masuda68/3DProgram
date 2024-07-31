#include "TPSCamera.h"

void TPSCamera::Init()
{
	CameraBase::Init();
	//基準点（ターゲット）からどれだけ離れているか
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -10.f);
	//マウスカーソルを画面中央値に固定する
	SetCursorPos(m_FixMousePos.x,m_FixMousePos.y);
}

void TPSCamera::Update()
{
	//Targetの行列（有効ンな場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;
	const std::shared_ptr<KdGameObject> _spTarget = m_spTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	//カメラ回転処理
	UpdateRotateByMouse();

	m_mRot = GetRotaionMatrix();

	//_targetMatこれを最後に書く
	m_mWorld = m_mLocalPos *m_mRot* _targetMat;

	//当たり判定は行列が確定した後
	//めり込み防止のための座標補正計算
	//①当たり判定（レイ判定）用の情報作成
	KdCollider::RayInfo _rayInfo;
	//レイの発射位置を設定
	_rayInfo.m_pos = GetPos();
	//レイの発射方向を設定
	_rayInfo.m_dir = Math::Vector3::Down;
	//レイの長さを設定
	_rayInfo.m_range = 1000.f;
	//レイの当たり判定をしたいタイプを設定
	_rayInfo.m_type = KdCollider::TypeGround;

	if (_spTarget)
	{
		Math::Vector3 _targetPos = _spTarget->GetPos();
		_targetPos.y += .1f;
		_rayInfo.m_dir=(_targetPos) - GetPos();
		_rayInfo.m_range = _rayInfo.m_dir.Length();
		_rayInfo.m_dir.Normalize();
	}

	//②Hit判定対象のオブジェクトに総当たり
	for (std::weak_ptr<KdGameObject> wpGameObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject> _spGameObj = wpGameObj.lock();
			if (_spGameObj)
			{
				std::list<KdCollider::CollisionResult> _retResultList;
				_spGameObj->Intersects(_rayInfo, &_retResultList);

				//③結果を利用して座標を補完する
				//例に当たったリストから一番近いオブジュエクト
				float			_maxOverLap = 0;
				Math::Vector3   _hitPos = {};
				bool			_hit = false;

				for (auto& ret : _retResultList)
				{
					//レイを遮断し、オー橋た長さが
					//一番長いものを探す
					if (_maxOverLap < ret.m_overlapDistance)
					{
						_maxOverLap = ret.m_overlapDistance;
						_hitPos = ret.m_hitPos;
						_hit = true;

					}
				}
				//何らかの障害にあっている
				if (_hit)
				{
					Math::Vector3 _hoseiPos = _hitPos;
					_hoseiPos += _rayInfo.m_dir * 0.4f;
					SetPos(_hoseiPos);
				}
			
			}
	}

	//②HIT判定対象オブジェクトに総当たり
	

	//親呼び出し
	CameraBase::Update();
}
