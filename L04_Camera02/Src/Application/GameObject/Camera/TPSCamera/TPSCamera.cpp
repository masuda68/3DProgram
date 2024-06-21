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

	//親呼び出し
	CameraBase::Update();


}
