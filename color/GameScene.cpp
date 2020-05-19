#include "DxLib.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "SceneMng.h"
#include "GameCtl.h"
#include "ResultScene.h"
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
	//if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_G])
	//{
	//	return std::make_unique<TitleScene>();
	//}

	// プレイヤーのHPがあるかつ敵が生きているときは動いてもよい
	if ((1 <= playerLife && playerLife <= 10) && _eDeathFlag == false)
	{
		// Dを押したら右移動
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_D])
		{
			playerPos.x += 5;
			frendPos += 5;
			dir = DIR_RIGHT;
		}
		// 左に移動
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_A])
		{
			if (0 <= playerPos.x)
			{
				playerPos.x -= 5;
				frendPos -= 5;
			}
			else
			{
				playerPos.x += 1;

			}
			dir = DIR_LEFT;
		}
		// 攻撃
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_K])
		{
			_atackFlag = true;
		}
		HitCheck();

	}
	if ((_eDeathFlag == true))
	{
		//if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RETURN] == 1
		//	&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RETURN] == 0)
		//{
			time++;
		//}
		if (50 <= time)
		{

			return std::make_unique<ResultScene>();

		}
	}
	if (playerLife == 0)
	{
		// プレイヤー敗北
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RETURN] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RETURN] == 0)
		{
			SetDrawBright(255, 255, 255);

			return std::make_unique<GameScene>();
		}


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

	GameDraw();
	StageControl();


	flamCnt++;
	return std::move(own);
}

void GameScene::HitCheck(void)
{
	//if (_eMoveFlag == true)
	//{
		// 動くかどうか
		if (playerPos.x + 125 <= _ePosX - 25)
		{
			// プレイヤーより右側にいたら左（プレイヤー側）に移動
			_ePosX -= 2;
			_eMoveFlag = true;

		}
		else if (_ePosX+55  <= playerPos.x)
		{
			// プレイヤーより左側にいたら右（プレイヤー側）に移動
			_ePosX += 2;
			_eMoveFlag = true;
		}
		else
		{
			// 接触したとき
			_eMoveFlag = false;
			
			hitFrend = true;
			playerPos.x -= 25;
			frendPos -= 25;
			playerLife--;
				//if ((_ePosX + 100 <= _pPosX) || (_pPosX + 150 <= _ePosX))
			//{
			//	
			//}
		}
	//}

	if (_atackFlag == true)// プレイヤーが攻撃したとき
	{
		if ((playerPos.x + _pAtackRange + 75 >= _ePosX))
		{
			// 少し離れる
			_ePosX += 50;
			enemyLife--;
			//_eDeathFlag = true;
		}
	}
	if (enemyLife == 0)
	{
		//　
		_eDeathFlag = true;
	}

}


bool GameScene::GameDraw(void)
{
	ClsDrawScreen();
	//StageLoad();
	//DrawBox(_pPosX, 550, _pPosX+150, 550-150, GetColor(0, 255, 0), TRUE);// プレイヤー


	DrawFormatString(SCREEN_SIZE_X-100, 600, GetColor(255, 255, 0), "GameScene");
	DrawBox(playerPos.x, playerPos.y, playerPos.x + 150, playerPos.y - 150, GetColor(255, 0, 255), false);// プレイヤー

	//if (_atackFlag == true)
	//{
	//	// 攻撃
	//	DrawBox(playerPos.x + 75, 550 - 75, playerPos.x + _pAtackRange + 75, 550 - 150, GetColor(0, 255, 0), false);// 攻撃範囲
	//	_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pTest2.png", true);// 仮画像
	//	//_player=SetBlendGraph
	//	_atackFlag = false;
	//}
	//else
	//{
	//	if (_eMoveFlag == false)
	//	{
	//		// 移動
	//		//if ((flamCnt / 10) % 2 == 0)
	//		//{
	//		//_player = 
	//				//_player = LoadGraphScreen(_pPosX, _pPosY - 150, "image/player/pTest.png", true);// 仮画像
	//		//}
	//				_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pDamage.png", true);// 仮画像

	//	}
	//	else
	//	{
	//		_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pTest.png", true);// 仮画像

	//	}

	//}

	DrawBox(frendPos, playerPos.y - 150, frendPos + 150, playerPos.y - 75, GetColor(255, 0, 255), false);// プレイヤー
	if (hitFrend == true)
	{
		// 敵と接触したら点滅
	//	if ((flamCnt / 10) % 2 == 0)
		//{
			LoadGraphScreen(frendPos, playerPos.y - 150, "image/frend2.png", true);
		//}
	}
	else
	{
		LoadGraphScreen(frendPos, playerPos.y - 150, "image/frend2.png", true);

	}
	
	
	
	//　敵が生きてるとき
	if (_eDeathFlag == false)
	{
		
		DrawBox(_ePosX, 550, _ePosX + 100, 400, GetColor(255, 0, 0), false);// 
		if (_eMoveFlag == true)
		{
			// 死んでないから描画
		//DrawBox(_ePosX, 550, _ePosX + 30, 550 - 150, GetColor(0, 255, 255), true);//右端画面外
			_enemy = LoadGraphScreen(_ePosX, 400, "image/enemy/test2.png", true);// 仮画像

		}
		// 動いてないとき＝キャラに接近し終わった 
		else if (_eMoveFlag == false)
		{
				// 攻撃
				_enemy = LoadGraphScreen(_ePosX-25, 400, "image/enemy/test3.png", true);// 仮画像

				DrawBox(_ePosX, 550 - 75, _ePosX - 25, 550 - 150, GetColor(0, 255, 0), false);// 攻撃範囲
				_damage += 5;
		}
	}
	else
	{
		//if ((flamCnt / 10) % 2 == 0)
		//{
		//	_enemy = LoadGraphScreen(_ePosX, 400, "image/enemy/test2.png", true);// 仮画像

		//}
		//SetDrawBright(255 / 2, 255 / 2, 255 / 2);
		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 0), "WIN");

	}

	if (playerLife == 0)
	{
		SetDrawBright(255 / 2, 255 / 2, 255 / 2);
		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 0), "GameOver　PushEnterKey");
	}

	StatusDraw();
	PlayerColor();
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
	//hpBox=SetTransColor(255 - _damage, 255 - _damage, 255 - _damage);

	// この線より右、タイムとかスコアが入るとこ
	DrawLine(SCREEN_SIZE_X-200, 550, SCREEN_SIZE_X-200, 700, GetColor(0, 255, 0), false);
	 LoadGraphScreen(SCREEN_SIZE_X-180, 570, "image/num.png", true);
// この線の左右に色バー
	DrawLine(SCREEN_SIZE_X /2, 550, SCREEN_SIZE_X/2, 700, GetColor(0, 255, 0), false);

	// 色ゲージ
	DrawBox(250, 570, SCREEN_SIZE_X / 2 - 50, 595, GetColor(0, 255, 0), true);// 緑
	DrawBox(250, 620, SCREEN_SIZE_X / 2 - 50, 645, GetColor(255, 0, 0), true);// 赤
	DrawBox(250, 670, SCREEN_SIZE_X / 2 - 50, 695, GetColor(0, 0, 255), true);// 青

}

void GameScene::StageControl(void)
{
	// X方向
	if (mapPos.x < 0)
	{
		mapPos.x = 0;
	}
	//if (mapPos.x > SCREEN_SIZE_X)
	//{
	//	mapPos.x =  SCREEN_SIZE_X;
	//}
	if (SCREEN_SIZE_X/2 <= playerPos.x)
	{
		mapPos.x += SCREEN_SIZE_X;

	}
}

void GameScene::PlayerColor(void)
{
	if (_atackFlag == true)
	{
		// 攻撃
		DrawBox(playerPos.x + 75, 550 - 75, playerPos.x + _pAtackRange + 75, 550 - 150, GetColor(0, 255, 0), false);// 攻撃範囲
		_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pTest2.png", true);// 仮画像
		//_player=SetBlendGraph
		_atackFlag = false;
	}
	else
	{
		if (_eMoveFlag == false)
		{
			// 移動
			//if ((flamCnt / 10) % 2 == 0)
			//{
			//_player = 
					//_player = LoadGraphScreen(_pPosX, _pPosY - 150, "image/player/pTest.png", true);// 仮画像
			//}
			_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pDamage.png", true);// 仮画像

		}
		else
		{
			_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pTest.png", true);// 仮画像

		}

	}


}

int GameScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));

	// プレイヤー
	mapPos = { VECTOR2(0, 0) };
	playerPos = { VECTOR2(0, 550) };
	_pAtackRange = 125;
	_damage = 0;
	playerLife = 10;
	frendPos = playerPos.x - 75;
	hitFrend = false;
	// エネミー
	_ePosX = SCREEN_SIZE_X / 2;
	_eMoveFlag = true;
	_atackFlag = false;
	_eDeathFlag = false;
	enemyLife = 1000000000000;

	time =0;
	return 0;
}
