#include "DxLib.h"
#include "GameCtl.h"
#include "SceneMng.h"
#include "HelpMode.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "Enemy.h"
#include "ScoreMng.h"
#include "Obj.h"

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

	// ボスが生きているてプレイヤーが生きている＝ゲームが続いている
	if (/*0 <= _bossLife&&*/ 0<=playerLife)
	{
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RSHIFT] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RSHIFT] == 0)
		{
			helpFlag = true;
			lpHelpMode.setHelpFlag(helpFlag);

		}
		
		if (helpFlag == false)
		{

			if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RCONTROL] == 1
				&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RCONTROL] == 0)
			{
				ChangeColor();
				colorNum += 1;
			}

			// Dを押したら右移動
			if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_D])
			{
				playerPos.x += 5;
				//frendPos += 5;
				//moveFlag = true;
				playerDir = DIR_RIGHT;
			}
			//else
			//{
			//	moveFlag = false;
			//}
			// 左に移動
			else if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_A])
			{
				//if (mapPos.x <= playerPos.x)
				//{
				//	playerPos.x -= 5;
				//	//frendPos -= 5;
				//}
				if (0 <= playerPos.x)
				{
					playerPos.x -= 5;
					//frendPos -= 5;
				}
				else
				{
					playerPos.x += 1;
				}
				playerDir = DIR_LEFT;
			}
			else
			{
				playerDir = DIR_MAX;
			}
			if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_W] == 1
				&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_W] == 0)
			{
				jumpFlag = true;
				playerOldPos.y = playerPos.y; // ジャンプする前の座標を保存
			}
			if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S])
			{
				underFlag = true;
			}
			else
			{
				underFlag = false;
			}
			// 攻撃
			if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_K])
			{
				_atackFlag = true;
			}
			// 遠距離攻撃		
			if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_L] == 1
				&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_L] == 0)
			{
				_shotFlag = true;
			}

			NormalEnemy();
		}
	}
	//if (_bossLife<=0)
	//{
	//	time++;
	//	if (50 <= time)
	//	{

			//return std::make_unique<ResultScene>();

	//	}
	//}
	if (playerLife <= 0)
	{
		GameOverDraw();
		// プレイヤー敗北
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_W] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_W] == 0)
		{
			// 上のステージ
			if (2 <= _buttonNum)
			{
				_buttonNum -= 1;
				//selectPos.y -= 270;
			}
		}
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_S] == 0)
		{
			// 下のステージ
			if (_buttonNum < 3)
			{
				_buttonNum += 1;
				//selectPos.y += 270;
			}
		}
		
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RETURN] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RETURN] == 0)
		{
			if (_buttonNum == 1)
			{

				return std::make_unique<SelectScene>();
			}
			else if (_buttonNum == 3)
			{
				return std::make_unique<TitleScene>();

			}
			else if (_buttonNum == 3)
			{
				return std::make_unique<GameScene>();

			}
		}
		//if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_L] == 1
		//	&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_L] == 0)
		//{
		//	return std::make_unique<ResultScene>();
		//}


	}

	if (_shotFlag == true)
	{
		_shotPos.x += _shotSpeed;
	}
	if (jumpFlag == true)
	{
		playerPos.y -= jumpCnt/**0.25f*/;
		if (playerPos.y <= SCREEN_SIZE_Y/2)
		{
			jumpFlag = false;
		}
	}
	else
	{
		if (playerOldPos.y<=playerPos.y  )
		{
			playerPos.y = playerOldPos.y;

		}
		else
		{
			playerPos.y += jumpCnt;

		}
	}



	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->Update(ctl, objList);
	}

	if (helpFlag == true)
	{
		lpHelpMode.HelpDraw();
	//	lpHelpMode.Updata(own,ctl);


	}
	else
	{
		GameDraw();
	}
	//if (_atackFlag == true
	//	&& _pPosX + _pAtackRange + 75 >= _ePosX)// 右側攻撃の範囲に入ってた時
	//	//&& _ePosX + 75 >= _pPosX)
	//{
	//	// 敵を消す
	//	_eDeathFlag = true;
	//}
	//
	// Scroll
	//if (dir == DIR_RIGHT && SCREEN_SIZE_X <= _pPosX)
	//{
	// プレイヤーが画面の真ん中より右側に行ったらカメラを左にスクロールする
	//}
	//if (moveFlag == true)
	//{
	//	StageControl();
	//}
	//playerColor;
	//color[testNum];

	//BossCheck();
	StageControl();
	PlayerCtl();
	AddScore();
	lpScoreMng.setScore(highScore);
	//GameDraw();
	flamCnt++;

	return std::move(own);
}

void GameScene::NormalEnemy(void)
{
	if (enemyLife <= 0)
	{
		//　
		enemyType = ENEMY_COLOR::NON;
		_eDeathFlag = true;
		//_bossFlag = true;
		//_bossMoveFlag = true;
	}
	else
	{// 動くかどうか
		if ((playerPos.x + 125 <= enemyPos.x - 25))
		{
			// プレイヤーより右側にいたら左（プレイヤー側）に移動
			enemyPos.x -= 2;
			_eMoveFlag = true;

		}
		else if (enemyPos.x + 55 <= playerPos.x)
		{
			// プレイヤーより左側にいたら右（プレイヤー側）に移動
			enemyPos.x += 2;
			_eMoveFlag = true;
		}
		else
		{
			// 接触したとき＝エネミーが攻撃
			_eMoveFlag = false;

			//	hitFrend = true;
			//	frendPos -= 25;
			if (_eMoveFlag == false)
			{
				if (playerPos.x + 125 >= enemyAtackRange.x)
				//&&(enemyAtackRange.y <= playerPos.y + 150)
				//	&&(playerPos.y+150<=enemyAtackRange.y+75))
				{// 近くに来たらプレイヤーに攻撃
					playerPos.x -= 25;
					oldFlam = flamCnt;
					_damageFlag = true;
					if (enemyColor == COLOR_TYPE::GREEN)
					{
						if (playerColor == COLOR_TYPE::RED)
						{
							_damage = 4;
						}
						else if (playerColor == COLOR_TYPE::BLUE)
						{
							_damage = 12;
						}
						else if (playerColor == COLOR_TYPE::GREEN)
						{
							_damage = 8;
						}

					}
				}
			}
		}
		//}
	}
	playerLife -= _damage;

	enemyAtackRange = { enemyPos.x - 25,400 };
}

/*BOSS*/
//void GameScene::BossCheck(void)
//{
//	if (_bossFlag == true)// プレイヤーが攻撃したとき=エネミーがダメージを受ける場合
//	{
//
//		if ((playerPos.x + _pAtackRange + 15 >= _bossPos.x))
//		{
//			// 少し離れる
//			_bossPos.x += 50;
//			if (enemyColor == COLOR_TYPE::GREEN)
//			{
//				if (playerColor == COLOR_TYPE::RED)
//				{
//					_bossLife -= 3;
//					score += 30;
//				}
//				else if (playerColor == COLOR_TYPE::BLUE)
//				{
//					_bossLife -= 1;
//					score += 10;
//				}
//				else if (playerColor == COLOR_TYPE::GREEN)
//				{
//					_bossLife -= 2;
//					score += 20;
//				}
//
//			}
//			//_eDeathFlag = true;
//		}
//	}
//
//
//	if (_bossMoveFlag == true)
//	{
//		if (playerPos.x + 125 <= _bossPos.x - 25)
//		{
//			// プレイヤーより右側にいたら左（プレイヤー側）に移動
//			_bossPos.x -= 2;
//
//		}
//		else if (_bossPos.x + 55 <= playerPos.x)
//		{
//			// プレイヤーより左側にいたら右（プレイヤー側）に移動
//			_bossPos.x += 2;
//		}
//
//	}
//	else
//	{
//		if (playerPos.x + 125 >= enemyAtackRange.x)
//			//&&(enemyAtackRange.y <= playerPos.y + 150)
//			//	&&(playerPos.y+150<=enemyAtackRange.y+75))
//		{// 近くに来たらプレイヤーに攻撃
//			playerPos.x -= 25;
//			oldFlam = flamCnt;
//			_damageFlag = true;
//			if (enemyColor == COLOR_TYPE::GREEN)
//			{
//				if (playerColor == COLOR_TYPE::RED)
//				{
//					_damage = 8;
//				}
//				else if (playerColor == COLOR_TYPE::BLUE)
//				{
//					_damage = 24;
//				}
//				else if (playerColor == COLOR_TYPE::GREEN)
//				{
//					_damage = 16;
//				}
//
//			}
//		}
//	}
//	playerLife -= _damage;
//	enemyAtackRange = { enemyPos.x - 50,400 };
//
//
//	if (_bossLife <= 0)
//	{
//		//　
//		_bossFlag = false;
//	}
//
//}


bool GameScene::GameDraw(void)
{
	ClsDrawScreen();
	StageDraw();
	std::for_each((*objList).begin(), (*objList).end(),
		[](std::shared_ptr<Obj>& itr) {itr->Draw(); });

	//DrawBox(_pPosX, 550, _pPosX+150, 550-150, GetColor(0, 255, 0), TRUE);// プレイヤー


	DrawFormatString(SCREEN_SIZE_X - 100, 600, GetColor(255, 255, 0), "GameScene");

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
	//DrawBox(frendPos, playerPos.y - 150, frendPos + 150, playerPos.y - 75, GetColor(255, 0, 255), false);// プレイヤー
	//if (hitFrend == true)
	//{
	//	// 敵と接触したら点滅
	////	if ((flamCnt / 10) % 2 == 0)
	//	//{
	//		LoadGraphScreen(frendPos, playerPos.y - 150, "image/player/frend/frend2.png", true);
	//	//}
	//}
	//else
	//{
	//	LoadGraphScreen(frendPos, playerPos.y - 150, "image/player/frend/frend2.png", true);

	//}
	//if (_bossFlag == true)
	//{
	//	_gBoss = LoadGraphScreen(_bossPos.x, _bossPos.y, "image/enemy/gBossBig.png", true);
	//}
	
	//　敵が生きてるとき
	if (_eDeathFlag == false)
	{
		
		DrawBox(enemyPos.x, 550, enemyPos.x + 100, 400, GetColor(255, 0, 0), false);// 
		if (_eMoveFlag == true)
		{
			// 死んでないから描画
		//DrawBox(_ePosX, 550, _ePosX + 30, 550 - 150, GetColor(0, 255, 255), true);//右端画面外
			_enemy = LoadGraphScreen(enemyPos.x, 400, "image/enemy/test2.png", true);// 仮画像

		}
		// 動いてないとき＝キャラに接近し終わった 
		else if (_eMoveFlag == false)
		{
				// 攻撃
				_enemy = LoadGraphScreen(enemyPos.x -25, 400, "image/enemy/test3.png", true);// 仮画像

				DrawBox(enemyPos.x, 550 - 150, enemyPos.x - 25, 550 - 75, GetColor(0, 255, 0), false);// 攻撃範囲
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

	if (playerLife <= 0)
	{
		SetDrawBright(255 / 2, 255 / 2, 255 / 2);
		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 0), "GameOver　PushEnterKey");

	}
	StatusDraw();
	PlayerDraw();
	triangle = LoadGraphScreen(215, trianglePosY, "image/game/check.png", true);// 仮画像
	
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
	DrawFormatString(SCREEN_SIZE_X - 50, 570, GetColor(255, 255, 255), "[%d]", score);
	DrawFormatString(SCREEN_SIZE_X - 150, 650, GetColor(255, 255, 255), "[%d]", playerLife);
	DrawFormatString(SCREEN_SIZE_X / 2+150, 570, GetColor(255, 255, 0), "右Shiftストップ");
	//LoadGraphScreen(SCREEN_SIZE_X-180, 570, "image/num.png", true);

// この線の左右に色バー
	//DrawLine(SCREEN_SIZE_X /2, 550, SCREEN_SIZE_X/2, 700, GetColor(0, 255, 0), false);

	// 色ゲージ
	nowColor[static_cast<int>(COLOR_TYPE::RED)] = DrawBox(_gagePosX, 570, _gageEndPosX, 595, color[0], true);// 赤
	
	nowColor[static_cast<int>(COLOR_TYPE::BLUE)] = DrawBox(_gagePosX, 620, _gageEndPosX, 645, color[1], true);// 青
	nowColor[static_cast<int>(COLOR_TYPE::GREEN)] = DrawBox(_gagePosX, 670, _gageEndPosX, 695, color[2], true);// 緑

	if ((_atackFlag == true) || (_shotFlag == true))
	{// unsigned int
		nowColor[colorNum] = DrawBox(_gagePosX, 570, _gageEndPosX-50, 595, color[colorNum], true);;
		_gageEndPosX;
	}


	// GetColorがマイナスだと白になるからゲームオーバー時は0を指定
	if (playerLife <= 0)
	{
		hpBox = DrawBox(0, 550, 200, 700, GetColor(0, 0, 0), true);
	}
	else
	{
		hpBox = DrawBox(0, 550, 200, 700, GetColor(playerLife, playerLife, playerLife), true);
	}
	
	
	if (SCREEN_SIZE_X/2 <= playerPos.x)
	{
		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 0), "center");
		// centerに来たら背景画像を左にずらしていく
	//	mapPos.x -= 50;
	}

}

void GameScene::StageControl(void)
{
	// 背景が動く
	int speed = 5;
	//if (mapPos.x < 0)
	//{
	//	mapPos.x = 0;
	//}
	//if (mapPos.x > 15* CHIP_SIZE_X - SCREEN_SIZE_X)
	//{
	//	mapPos.x = 15 * CHIP_SIZE_X - SCREEN_SIZE_X;
	//}
	if (playerDir == DIR_RIGHT)
	{
		//if ((mapPos.y <= 0) || (mapPos.y >= PLAY_SIZE_Y - SCREEN_SIZE_Y))
		//{
		if (playerPos.x > SCREEN_SIZE_X / 2 + mapPos.x)
		{
			mapPos.x -= speed;
		}
		//	}
	}
	else if (playerDir == DIR_LEFT)
	{
		//if ((mapPos.y <= 0) || (mapPos.y >= PLAY_SIZE_Y - SCREEN_SIZE_Y))
		//{
		if (playerPos.x < mapPos.x + SCREEN_SIZE_X / 2)
		{
			mapPos.x += speed;
		}
		//}
	}	//	bgImage = LoadGraphScreen(mapPos.x, mapPos.y, "stage/testStage.png", true);
}



void GameScene::ChangeColor(void)
{
	trianglePosY += 50;
	if (680 <= trianglePosY)
	{
		//　一番下まで来たら座標を戻してcolorを赤（一番上）に戻す
		trianglePosY = 570;
		colorNum = 0;

	}

	if (colorNum == 0)
	{
		playerColor = COLOR_TYPE::RED;
	}
	else if (colorNum == 1)
	{
		playerColor = COLOR_TYPE::BLUE;
	}
	else if (colorNum == 2)
	{
		playerColor = COLOR_TYPE::GREEN;
	}
//	testNum += 1;

}

void GameScene::PlayerCtl(void)
{
	if (_atackFlag == true)// プレイヤーが攻撃したとき=エネミーがダメージを受ける場合
	{
		if ((playerPos.x + _pAtackRange + 75 >= enemyPos.x))
		{
			// 少し離れる
			enemyPos.x += 50;
			if (enemyColor == COLOR_TYPE::GREEN)
			{
				if (playerColor == COLOR_TYPE::RED)
				{
					enemyLife -= 3;
					score += 30;
				}
				else if (playerColor == COLOR_TYPE::BLUE)
				{
					enemyLife -= 1;
					score += 10;
				}
				else if (playerColor == COLOR_TYPE::GREEN)
				{
					enemyLife -= 2;
					score += 20;
				}

			}
			//_eDeathFlag = true;
		}

	}
	if (_shotFlag == true)
	{
		//if ((_shotPos.x < enemyPos.x + 100)	// 弾の左<敵の右
		//	&& (enemyPos.x < _shotPos.x + _shotSize)	// 敵の左<弾の右
		//	&& (_shotPos.y < enemyPos.y + 150)	// 弾の上<敵の下
		//	&& (enemyPos.y < _shotPos.y + _shotSize))// 敵の上<弾の下
		if (enemyPos.x <= _shotPos.x + _shotSize)
		{
			// 遠距離攻撃が当たったら
			enemyPos.x += 50;// エネミーを少し後退させる
			if (enemyColor == COLOR_TYPE::GREEN)
			{
				if (playerColor == COLOR_TYPE::RED)
				{
					enemyLife -= 3;
					score += 30;
				}
				else if (playerColor == COLOR_TYPE::BLUE)
				{
					enemyLife -= 1;
					score += 10;
				}
				else if (playerColor == COLOR_TYPE::GREEN)
				{
					enemyLife -= 2;
					score += 20;
				}

			}
			_shotFlag = false;
		}
	}
	else
	{
		_shotPos = { playerPos.x + 150,playerPos.y - 125 };
	}

	//if (_damageFlag == true)
	//{
	//	if ((flamCnt / 10) % 2 == 0)
	//	{
	//		_player;
	//	}
	//}
}

void GameScene::PlayerDraw(void)
{	

	// 遠距離攻撃
	if (_shotFlag == true)
	{
		_shot = LoadGraphScreen(_shotPos.x + mapPos.x, _shotPos.y, "image/player/baku.png", true);
		if (SCREEN_SIZE_X < _shotPos.x + mapPos.x)
		{
			_shotFlag = false;
		}
	}
	// 近距離攻撃
	if (_atackFlag == true)
	{
		// 攻撃
		DrawBox(playerPos.x + 75 + mapPos.x, 550 - 75, playerPos.x + _pAtackRange + 75 + mapPos.x, 550 - 150, GetColor(0, 255, 0), false);// 攻撃範囲
		_player = LoadGraphScreen(playerPos.x + mapPos.x, playerPos.y - 150, "image/player/wAttack.png", true);// 仮画像
		//_player=SetBlendGraph
		_atackFlag = false;
	}
	if (jumpFlag == true)
	{
		_player = LoadGraphScreen(playerPos.x + mapPos.x, playerPos.y - 150, "image/player/wJump.png", true);
	}
	if (underFlag == true)
	{
		DrawBox(playerPos.x + mapPos.x, playerPos.y - 80, playerPos.x + 150 + mapPos.x, playerPos.y, GetColor(0, 255, 0), false);// 攻撃範囲
		_player = LoadGraphScreen(playerPos.x + mapPos.x, playerPos.y - 150, "image/player/wUnder.png", true);

	}
	
	if (_atackFlag == false && jumpFlag == false && underFlag == false)
	{
		if (_damageFlag == true)
		{
			// 移動
			if (oldFlam + 500 < flamCnt)
			{
				_damageFlag = false;
			}
			else
			{
				if ((flamCnt / 10) % 2 == 0)
				{
					_player = LoadGraphScreen(playerPos.x + mapPos.x, playerPos.y - 150, "image/player/wDamage.png", true);// 仮画像
				}
			}
			DrawBox(playerPos.x + mapPos.x, playerPos.y, playerPos.x + 150 + mapPos.x, playerPos.y - 150, GetColor(255, 0, 255), false);// プレイヤー

		}
		else
		{
			//_player = LoadGraphScreen(playerPos.x + mapPos.x, playerPos.y - 150, "image/player/wIdle.png", true);// 仮画像
			//DrawBox(playerPos.x + mapPos.x, playerPos.y, playerPos.x + 150 + mapPos.x, playerPos.y - 150, GetColor(255, 0, 255), false);// プレイヤー
			//if ((flamCnt / 50) % 2 == 0)
			//{
			//	_player;
			//}

			for (int j = 0; j < 4; j++)
			{
				DrawGraph(playerPos.x + mapPos.x, playerPos.y - 150, GHandle[j], true);

			}
		}

	}


}

void GameScene::GameOverDraw(void)
{	
	
	ClsDrawScreen();
	//backImage = LoadGraphScreen(0, 0, "image/select/sBack0.png", true);
	//DrawBox(_helpPos.x, _helpPos.y, _helpPos.x + 450, _helpPos.y + 100, GetColor(255, 255, 255), true);
	//SetDrawBright(255, 255, 255);

	DrawFormatString(150, 100, GetColor(255, 0, 255), "SelectStage　PushEnter");

	//_helpTitle = LoadGraphScreen(SCREEN_SIZE_X / 3, 50, "image/helpMode/helpTitle.png", true);
	// ボタン
	_button[static_cast<int>(SCENE_TYPE::SELECT)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2 - 100, "image/helpMode/selectButton.png", true);
	//_selectBackButton=LoadGraphScreen(_helpPos.x, _helpPos.y, "image/helpMode/selectButton.png", true);
	_button[static_cast<int>(SCENE_TYPE::TITLE)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2, "image/helpMode/titleButton.png", true);
	//_titleBackButton = LoadGraphScreen(_helpPos.x, _helpPos.y+100, "image/helpMode/titleButton.png", true);
	_button[static_cast<int>(SCENE_TYPE::GAME)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2 + 100, "image/helpMode/playButton.png", true);
	//_playBuckButton = LoadGraphScreen(_helpPos.x, _helpPos.y+200, "image/helpMode/playButton.png", true);


	DrawFormatString(SCREEN_SIZE_X - 50, 450, GetColor(255, 255, 255), "[%d]", _buttonNum);
	ScreenFlip();

}

void GameScene::AddScore(void)
{
	// 
	if (score > highScore)
	{
		highScore = score;
	}
	highScore;
}

void GameScene::StageDraw(void)
{
	auto playStage =lpStageCtl.getStage();
	if (playStage == STAGE::FIRST)
	{
		lpStageCtl.FirstStage(mapPos);
	}
	else if (playStage == STAGE::SECOND)
	{
		lpStageCtl.SecondStage(mapPos);
	}

}

int GameScene::Init(void)
{
	if (!objList)	// 真の場合があるない場合を作りたいので「!」 uniqueでもsharedでも同じ　残り一つは違う
	{
		objList = std::make_shared<sharedObjList>();	// <>の中には管理ｵﾌﾞｼﾞｪｸﾄ
	}

	objList->clear();
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	trianglePosY = 570;
	// プレイヤー
	mapPos = { VECTOR2(0, 0) };
	playerDir = DIR_RIGHT;
	playerPos = { VECTOR2(0, 550) };
	playerOldPos = playerPos;
	_shotPos = { playerPos.x+200,playerPos.y -125 };
	_shotSpeed = 10;
	_shotSize = 40;
	_shotFlag = false;
	jumpFlag = false;
	jumpCnt = 10;
	underFlag = false;
	_pAtackRange = 125;
	_damage = 0;
	_damageFlag = false;
	playerLife = 255;
	//frendPos = playerPos.x - 75;
	//hitFrend = false;
	// エネミー
	enemyPos = { VECTOR2(SCREEN_SIZE_X / 2,550) };
	enemyAtackRange = { enemyPos.x - 25,400 };
	_eMoveFlag = true;
	_atackFlag = false;
	moveFlag = false;
	_eDeathFlag = false;
	enemyLife = 3;
	//_bossPos = { VECTOR2(SCREEN_SIZE_X - 200,300) };
	//_bossLife = 30;
	//_bossFlag = false;
	//_bossMoveFlag=false;

	time =0;	

	//centerPos = VECTOR2{ SCREEN_SIZE_X/2,SCREEN_SIZE_Y / 2 };
	//bgPosX1=0;				// 横サイズ1
	colorNum = 1;
	_gagePosX = 250;
	color[0] = GetColor(255, 0, 0);
	color[1] = GetColor(0, 0, 255);
	color[2] = GetColor(0, 255, 0);
	_gageEndPosX = SCREEN_SIZE_X / 2;

	playerColor = COLOR_TYPE::RED;
	enemyColor = COLOR_TYPE::GREEN;
	enemyType = ENEMY_COLOR::GREEN;
	//markerPos[3]  {
	//	VECTOR2(215,570),VECTOR2(215,620),VECTOR2(215,670)
	//};
	auto marlerPos = VECTOR2(215, 570);
	markerPos[0] = VECTOR2(215, 570);

	helpFlag = false;
	score = 0;
	flamCnt = 0;
	oldFlam = flamCnt;

	LoadDivGraph("image/player/bMove3.png", 4, 4, 1, 150, 150, GHandle, true);// 仮画像

	return 0;
}
