#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"

// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}

void GameScene::Init()
{
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
	//std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	//std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);

	{
		//===================================================================
		// 乱数実験場
		//===================================================================
		//int _randRes[10] = {};

		////如何にrand（）が偏るか
		//srand((unsigned)time(NULL));
		//for (int i = 0; i < 100000000; i++)
		//{
		//	int tmp = rand() % 10000;
		//	int idx = tmp / 1000;
		//	_randRes[idx]++;
		//}
		////結果を出力
		//OutputDebugStringA("---------------------------------\n");
		//for (int i = 0; i < 10; i++)
		//{
		//	std::stringstream ss;
		//	ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 << "の件数:\t" << _randRes[i] << "\n";
		//	std::string str = ss.str();
		//	OutputDebugStringA(str.c_str());
		//}
		//OutputDebugStringA("---------------------------------\n");

		//メルセンヌついスタ
		//for (int i = 0; i < 100000000; i++)
		//{
		//	int tmp = KdGetInt(0,9999);
		//	int idx = tmp / 1000;
		//	_randRes[idx]++;
		//}
		////結果を出力
		//OutputDebugStringA("---------------------------------\n");
		//for (int i = 0; i < 10; i++)
		//{
		//	std::stringstream ss;
		//	ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 << "の件数:\t" << _randRes[i] << "\n";
		//	std::string str = ss.str();
		//	OutputDebugStringA(str.c_str());
		//}
		//OutputDebugStringA("---------------------------------\n");

		//レッスン１
		//CかーどとRカードをそれぞれ50％の確率で軌道に表示せよ
		//レッスン２
		//Cかーど（90.5%）とRカード(0.5%)をそれぞれの確率で軌道に表示せよ
		//レッスン３
		//C（34％）とR（33%）とS（33％）
		//レッスン4
		//C（50％）とR（49.5%）とS（0.5％）


		//int countR = 0;
		//int countC = 0;
		//for (int i = 0; i < 100; i++)
		//{
		//	int card = KdGetInt(0, 99);
		//	if (card < 5)
		//	{
		//		countR++;
		//	}
		//	else if (card >= 5)
		//	{
		//		countC++;
		//	}
		//}
		//std::stringstream ss;
		//ss << "Cカード" << countC << "\n" << "Rカード" << countR << "\n";
		//	std::string str = ss.str();
		//OutputDebugStringA(str.c_str());
	}
	
	OutputDebugStringA("---------------------------------\n");
	int _bunbo = 1000;
	int _randNum[3] = {500,495,5};
	int _ThusenNum = 10000000;
	int _TousenNum[3] = { 0,0,0 };
	for (int i = 0; i < _ThusenNum; i++)
	{
		int _rnd = KdGetInt(0, _bunbo - 1);
		for (int j = 0; j < std::size(_randNum); j++)
		{
			_rnd -= _randNum[j];
			if (_rnd < 0)
			{
				_TousenNum[j]++;
					break;
			}
		}
	}
	OutputDebugStringA("---------------------------------\n");

	float prob = 0;
	for(int i=0;i<3;i++)
	{
		std::stringstream ss;
		prob = ((float)_TousenNum[i] / (float)_ThusenNum)* 100;
		round_n(prob, 3);

		switch (i)
		{
		case 0:
			ss << "C" << _TousenNum[0] <<"\t:" << prob << "%\n";
			break;
		case 1:
			ss << "R" << _TousenNum[1] << "\t:" << prob << "%\n";
			break;
		case 2:
			ss << "S" << _TousenNum[2] << "\t:" << prob << "%\n";
			break;
		}

		std::string str = ss.str();
		OutputDebugStringA(str.c_str());

	}
	OutputDebugStringA("---------------------------------\n");

}

void GameScene::Event()
{
}