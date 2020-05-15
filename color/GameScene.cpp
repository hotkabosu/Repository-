#include "DxLib.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "SceneMng.h"
#include "GameCtl.h"
#include "TitleScene.h"

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
	}
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_A])
	{
		_pPosX -= 5;
	}
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_K])
	{
		_atackFlag = true;
	}

	HitCheck();
	GameDraw();



	return std::move(own);
}

void GameScene::HitCheck(void)
{
	if (_atackFlag == true)
	{
		if ((_pAtackRange + 75 <= _ePosX))
		{
			_eMoveFlag = false;
		}
	}

	// 動くかどうか
	if (_pPosX + 150 <= _ePosX - 25)
	{			// プレイヤーより右側にいたら左（プレイヤー側）に移動
		_ePosX -= 2;
		_eMoveFlag = true;

	}
	else if (_ePosX + 100 + 25 <= _pPosX)
	{
		// プレイヤーより左側にいたら右（プレイヤー側）に移動
		_ePosX += 2;
		_eMoveFlag = true;

	}
	else
	{
		_eMoveFlag = false;
		//if ((_ePosX + 100 <= _pPosX) || (_pPosX + 150 <= _ePosX))
		//{
		//	eflag = true;

		//}
	}


	//if (_ePosX <= _pPosX + 30  )
	//{
	//	eflag = false;

	//}
	//else
	//{
	//}


}


bool GameScene::GameDraw(void)
{
	ClsDrawScreen();
	stageBack = LoadGraphScreen(0, 0, "stage/testStage.png", true);
	//DrawBox(_pPosX, 550, _pPosX+150, 550-150, GetColor(0, 255, 0), TRUE);// プレイヤー
	DrawBox(_pPosX, _pPosY, _pPosX + 150, _pPosY - 150, GetColor(255, 0, 255), false);// プレイヤー


	DrawFormatString(150, 150, GetColor(255, 255, 0), "GameScene");

	if (_atackFlag == true)
	{
		DrawBox(_pPosX+_pAtackRange, 550 - 75, _pPosX+_pAtackRange +75, 550 - 150, GetColor(0, 255, 0), false);// 攻撃範囲
		_atackFlag = false;
	}


	//
	if (_eDeathFlag == false)
	{// 死んでないから描画
		//DrawBox(_ePosX, 550, _ePosX + 30, 550 - 150, GetColor(0, 255, 255), true);//右端画面外
		_enemy = LoadGraphScreen(_ePosX, 400, "image/enemy/testE.png", true);// 仮画像
	}
	if (_eMoveFlag == false)
	{
		// 攻撃
		DrawBox(_ePosX, 550 - 75, _ePosX-25, 550 - 150, GetColor(0, 255, 0), false);// 攻撃範囲
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
	_pAtackRange = 150;
	_ePosX = SCREEN_SIZE_X-30;

	// エネミー
	_eMoveFlag = true;
	_atackFlag = false;
	_eDeathFlag = false;
	return 0;
}
