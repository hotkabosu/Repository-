#include "DxLib.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "SceneMng.h"
#include "GameCtl.h"
#include "TitleScene.h"
#include "Player.h"

GameScene::GameScene()
{
	Init();

}


GameScene::~GameScene()
{
}

unique_Base GameScene::Updata(unique_Base own, const GameCtl& ctl)
{
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_G])
	{
		return std::make_unique<TitleScene>();
	}

	// Dを押したら右移動
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_D])
	{
		_pPosX += 5;
		dir = DIR_RIGHT;
	}
	// 左に移動
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_A])
	{
		if (0 <= _pPosX)
		{
			_pPosX -= 5;
		}
		else
		{
			_pPosX += 1;

		}
		dir = DIR_LEFT;
	}
	// 攻撃
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_K])
	{
		_atackFlag = true;
	}


	//if (_atackFlag == true
	//	&& _pPosX + _pAtackRange + 75 >= _ePosX)// 右側攻撃の範囲に入ってた時
	//	//&& _ePosX + 75 >= _pPosX)
	//{
	//	// 敵を消す
	//	_eDeathFlag = true;
	//}


	// Scroll
	//if (dir == DIR_RIGHT && SCREEN_SIZE_X <= _pPosX)
	//{
	// プレイヤーが画面の真ん中より右側に行ったらカメラを左にスクロールする
	//}

	HitCheck();
	GameDraw();


	flamCnt++;
	nowTime++;
	return std::move(own);
}

void GameScene::HitCheck(void)
{
	if (_eMoveFlag == true)
	{
		// 動くかどうか
		if (_pPosX + 125 <= _ePosX - 25)
		{
			// プレイヤーより右側にいたら左（プレイヤー側）に移動
			_ePosX -= 2;
			_eMoveFlag = true;

		}
		else if (_ePosX + 55 <= _pPosX)
		{
			// プレイヤーより左側にいたら右（プレイヤー側）に移動
			_ePosX += 2;
			_eMoveFlag = true;

		}
		else
		{
			// 接触したとき
			_eMoveFlag = false;
			//if ((_ePosX + 100 <= _pPosX) || (_pPosX + 150 <= _ePosX))
			//{
			//	
			//}
		}
	}

	if (_atackFlag == true)// プレイヤーが攻撃したとき
	{
		if ((_pPosX + _pAtackRange + 75 >= _ePosX))
		{
			_ePosX += 25;
			oldTime = nowTime;
			eHP-=1;
		}
	}
	if (oldTime + 50.0 <= nowTime)
	{
		// 今の時間が攻撃を受けた時の時間+50.0を超えたら動いてもよい
		_ePosX;
	}
	//if (eHP == 0)
	//{
	//	//　
	//	_eDeathFlag = true;
	//}

}


bool GameScene::GameDraw(void)
{
	ClsDrawScreen();
	stageBack = LoadGraphScreen(0, 0, "stage/testStage.png", true);
	//DrawBox(_pPosX, 550, _pPosX+150, 550-150, GetColor(0, 255, 0), TRUE);// プレイヤー


	DrawFormatString(SCREEN_SIZE_X-100, 600, GetColor(255, 255, 0), "GameScene");
	DrawBox(_pPosX, _pPosY, _pPosX + 150, _pPosY - 150, GetColor(255, 0, 255), false);// プレイヤー

	if (_atackFlag == true)
	{
		// 攻撃
		DrawBox(_pPosX + 75, 550 - 75, _pPosX + _pAtackRange + 75, 550 - 150, GetColor(0, 255, 0), false);// 攻撃範囲
		_player = LoadGraphScreen(_pPosX, _pPosY - 150, "image/player/pTest2.png", true);// 仮画像
		_atackFlag = false;
	}
	else
	{
		// 移動
		_player = LoadGraphScreen(_pPosX, _pPosY - 150, "image/player/pTest.png", true);// 仮画像

	}


	//　敵が生きてるとき
	if (_eDeathFlag == false)
	{
		
		if (_eMoveFlag == true)
		{
			// 死んでないから描画
		//DrawBox(_ePosX, 550, _ePosX + 30, 550 - 150, GetColor(0, 255, 255), true);//右端画面外
			DrawBox(_ePosX, 550, _ePosX + 100, 400, GetColor(255, 0, 0), false);// 
			_enemy = LoadGraphScreen(_ePosX, 400, "image/enemy/test2.png", true);// 仮画像

		}
		// 動いてないとき＝キャラに接近し終わった 
		else if (_eMoveFlag == false)
		{
			//if ((flamCnt / 10) % 2 == 0)
			//{
				// 攻撃
				_enemy = LoadGraphScreen(_ePosX-25, 400, "image/enemy/test3.png", true);// 仮画像

				DrawBox(_ePosX, 550 - 75, _ePosX - 25, 550 - 150, GetColor(0, 255, 0), false);// 攻撃範囲
				_damage += 15;
			//}
		}
	}

	StatusDraw();
	ScreenFlip();
	return false;
}


void GameScene::StatusDraw(void)
{
	// この線より下にＨＰやゲージ
	DrawLine(0, 700 - 150, 1200, 700 - 150, GetColor(255, 255, 0), TRUE);	
	// この線より左、HPのとこ
	DrawLine(200, 550, 200, 700, GetColor(0, 255, 0), false);
	hpBox=DrawBox(0, 550 , 200, 700, GetColor(255, 255, 255), true);
	//hpBox = SetDrawBright(255 - _damage, 255 - _damage, 255 - _damage);


	// この線より右、タイムとかスコアが入るとこ
	DrawLine(SCREEN_SIZE_X-200, 550, SCREEN_SIZE_X-200, 700, GetColor(0, 255, 0), false);
	// この線の左右に色バー
	DrawLine(SCREEN_SIZE_X /2, 550, SCREEN_SIZE_X/2, 700, GetColor(0, 255, 0), false);

	// 色ゲージ
	DrawBox(250, 570, SCREEN_SIZE_X / 2 - 50, 595, GetColor(0, 255, 0), true);// 緑
	DrawBox(250, 620, SCREEN_SIZE_X / 2 - 50, 645, GetColor(255, 0, 0), true);// 赤
	DrawBox(250, 670, SCREEN_SIZE_X / 2 - 50, 695, GetColor(0, 0, 255), true);// 青

}



int GameScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));

	// プレイヤー
	_pPosY = 550;
	_pPosX = 0;
	_pAtackRange = 125;
	_damage = 0;

	// エネミー
	_ePosX = SCREEN_SIZE_X;
	_eMoveFlag = true;
	_atackFlag = false;
	_eDeathFlag = false;
	eHP = 2;

	nowTime = 0.0f;
	oldTime = nowTime;
	return 0;
}
