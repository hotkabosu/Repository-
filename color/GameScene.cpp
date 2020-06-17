#include "DxLib.h"
#include "GameCtl.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "ScoreMng.h"

GameScene::GameScene()
{
	Init();

}


GameScene::~GameScene()
{

}

unique_Base GameScene::Updata(unique_Base own, const GameCtl& ctl)
{

	// �{�X�������Ă���ăv���C���[�������Ă��遁�Q�[���������Ă���
	if (/*0 <= _bossLife&&*/ 0 <= playerLife)
	{

		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RCONTROL] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RCONTROL] == 0)
		{
			ChangeColor();
			colorNum += 1;
		}

		// D����������E�ړ�
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
		// ���Ɉړ�
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
			playerOldPos.y = playerPos.y; // �W�����v����O�̍��W��ۑ�
		}
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S])
		{
			underFlag = true;
		}
		else
		{
			underFlag = false;
		}
		// �U��
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_K])
		{
			_atackFlag = true;
		}
		// �������U��		
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_L] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_L] == 0)
		{
			_shotFlag = true;
		}

		NormalEnemy();

	}
	if (enemyLife<=0)
	{
		time++;
		if (50 <= time)
		{

			return std::make_unique<ResultScene>();

		}
	}
	if (playerLife <= 0)
	{
		GameOverDraw();
		// �v���C���[�s�k
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_W] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_W] == 0)
		{
			if (1 <= _buttonNum)
			{
				_buttonNum -= 1;
				_buttonPosY -= 100;
			}
		}
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_S] == 0)
		{
			if (_buttonNum < 2)
			{
				_buttonNum += 1;
				_buttonPosY += 100;
			}
		}
		
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RETURN] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RETURN] == 0)
		{
			if (_buttonNum == 0)
			{
				return std::make_unique<SelectScene>();
			}
			else if (_buttonNum == 1)
			{
				return std::make_unique<TitleScene>();

			}
			else if (_buttonNum == 2)
			{
				return std::make_unique<GameScene>();

			}
		}
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



	GameDraw();
	PlayerCtl();
	AddScore();
	lpScoreMng.setScore(highScore);
	flamCnt++;

	return std::move(own);
}

void GameScene::NormalEnemy(void)
{
	if (enemyLife <= 0)
	{
		//�@
		enemyType = ENEMY_COLOR::NON;
		_eDeathFlag = true;
		//_bossFlag = true;
		//_bossMoveFlag = true;
	}
	else
	{// �������ǂ���
		if ((playerPos.x + 125 <= enemyPos.x - 25))
		{
			// �v���C���[���E���ɂ����獶�i�v���C���[���j�Ɉړ�
			enemyPos.x -= 2;
			_eMoveFlag = true;

		}
		else if (enemyPos.x + 55 <= playerPos.x)
		{
			// �v���C���[��荶���ɂ�����E�i�v���C���[���j�Ɉړ�
			enemyPos.x += 2;
			_eMoveFlag = true;
		}
		else
		{
			// �ڐG�����Ƃ����G�l�~�[���U��
			_eMoveFlag = false;

			//	hitFrend = true;
			//	frendPos -= 25;
			if (_eMoveFlag == false)
			{
				if (playerPos.x + 125 >= enemyAtackRange.x)
				//&&(enemyAtackRange.y <= playerPos.y + 150)
				//	&&(playerPos.y+150<=enemyAtackRange.y+75))
				{// �߂��ɗ�����v���C���[�ɍU��
					playerPos.x -= 25;
					oldFlam = flamCnt;
					_damageFlag = true;
				}
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
					playerLife -= _damage;

				}

			}
		}
		//}
	}

	enemyAtackRange = { enemyPos.x - 25,400 };
}

/*BOSS*/
//void GameScene::BossCheck(void)
//{
//	if (_bossFlag == true)// �v���C���[���U�������Ƃ�=�G�l�~�[���_���[�W���󂯂�ꍇ
//	{
//
//		if ((playerPos.x + _pAtackRange + 15 >= _bossPos.x))
//		{
//			// ���������
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
//			// �v���C���[���E���ɂ����獶�i�v���C���[���j�Ɉړ�
//			_bossPos.x -= 2;
//
//		}
//		else if (_bossPos.x + 55 <= playerPos.x)
//		{
//			// �v���C���[��荶���ɂ�����E�i�v���C���[���j�Ɉړ�
//			_bossPos.x += 2;
//		}
//
//	}
//	else
//	{
//		if (playerPos.x + 125 >= enemyAtackRange.x)
//			//&&(enemyAtackRange.y <= playerPos.y + 150)
//			//	&&(playerPos.y+150<=enemyAtackRange.y+75))
//		{// �߂��ɗ�����v���C���[�ɍU��
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
//		//�@
//		_bossFlag = false;
//	}
//
//}


bool GameScene::GameDraw(void)
{
	ClsDrawScreen();
	StageDraw();
	//�@�G�������Ă�Ƃ�
	if (_eDeathFlag == false)
	{
		
		DrawBox(enemyPos.x, 550, enemyPos.x + 100, 400, GetColor(255, 0, 0), false);// 
		if (_eMoveFlag == true)
		{
			// ����łȂ�����`��
		//DrawBox(_ePosX, 550, _ePosX + 30, 550 - 150, GetColor(0, 255, 255), true);//�E�[��ʊO
			_enemy = LoadGraphScreen(enemyPos.x, 400, "image/enemy/test2.png", true);// ���摜

		}
		// �����ĂȂ��Ƃ����L�����ɐڋ߂��I����� 
		else if (_eMoveFlag == false)
		{
				// �U��
				_enemy = LoadGraphScreen(enemyPos.x -25, 400, "image/enemy/test3.png", true);// ���摜

				DrawBox(enemyPos.x, 550 - 150, enemyPos.x - 25, 550 - 75, GetColor(0, 255, 0), false);// �U���͈�
		}
	}
	else
	{

		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 0), "WIN");

	}

	StatusDraw();
	PlayerDraw();
	triangle = LoadGraphScreen(215, trianglePosY, "image/game/check.png", true);// ���摜
	if (playerLife <= 0)
	{
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(255 / 2, 255 / 2, 255 / 2), false);
		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 0), "GameOver�@PushEnterKey");
		GameOverDraw();

	}

	ScreenFlip();
	return false;
}


void GameScene::StatusDraw(void)
{
	// ���̐���艺�ɂg�o��Q�[�W
	DrawLine(0, 700 - 150, 1200, 700 - 150, GetColor(255, 255, 0), TRUE);	
	// ���̐���荶�AHP�̂Ƃ�
	DrawLine(200, 550, 200, 700, GetColor(0, 255, 0), false);

	// ���̐����E�A�^�C���Ƃ��X�R�A������Ƃ�
	DrawLine(SCREEN_SIZE_X-200, 550, SCREEN_SIZE_X-200, 700, GetColor(0, 255, 0), false);
	DrawFormatString(SCREEN_SIZE_X - 50, 570, GetColor(255, 255, 255), "[%d]", score);
	DrawFormatString(SCREEN_SIZE_X - 200, 590, GetColor(255, 255, 255), "[�j�L�[�F�ߋ����U��]");
	DrawFormatString(SCREEN_SIZE_X - 200, 620, GetColor(255, 255, 255), "[�k�L�[�F�������U��]");
	//LoadGraphScreen(SCREEN_SIZE_X-180, 570, "image/num.png", true);

// ���̐��̍��E�ɐF�o�[
	//DrawLine(SCREEN_SIZE_X /2, 550, SCREEN_SIZE_X/2, 700, GetColor(0, 255, 0), false);

	// �F�Q�[�W
	DrawBox(250,570, SCREEN_SIZE_X/2,595, GetColor(255,0,  0), true);// ��
	markRed = LoadGraphScreen(SCREEN_SIZE_X / 2 + 10, 568, "image/fireMark.png", true);
	
	DrawBox(250,620, SCREEN_SIZE_X / 2, 645, GetColor(0, 0, 255), true);// ��
	markBlue = LoadGraphScreen(SCREEN_SIZE_X / 2 + 10, 618, "image/blueMark.png", true);
	
	DrawBox(250, 670, SCREEN_SIZE_X / 2, 695, GetColor(0,255,0), true);// ��
	markGreen = LoadGraphScreen(SCREEN_SIZE_X/2+10,665,"image/greenMark.png",true);


	// GetColor���}�C�i�X���Ɣ��ɂȂ邩��Q�[���I�[�o�[����0���w��
	if (playerLife <= 0)
	{
		hp = LoadGraphScreen(0, 525, "image/frend.png", true);
		hpBox = DrawBox(0, 550, 200, 700, GetColor(0, 0, 0), true);
	}
	else
	{
		hp = LoadGraphScreen(0, 525, "image/frend.png", true);
		DrawFormatString(0, 560, GetColor(255, 255, 255), "[%d]", playerLife);
	}
	
	
	if (SCREEN_SIZE_X/2 <= playerPos.x)
	{
		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 0), "center");
		// center�ɗ�����w�i�摜�����ɂ��炵�Ă���
	//	mapPos.x -= 50;
	}

}

/*void GameScene::StageControl(void)*/
//{
//	// �w�i������
//	int speed = 5;
//	//if (mapPos.x < 0)
//	//{
//	//	mapPos.x = 0;
//	//}
//	//if (mapPos.x > 15* CHIP_SIZE_X - SCREEN_SIZE_X)
//	//{
//	//	mapPos.x = 15 * CHIP_SIZE_X - SCREEN_SIZE_X;
//	//}
//	if (playerDir == DIR_RIGHT)
//	{
//		//if ((mapPos.y <= 0) || (mapPos.y >= PLAY_SIZE_Y - SCREEN_SIZE_Y))
//		//{
//		if (playerPos.x > SCREEN_SIZE_X / 2 + mapPos.x)
//		{
//			mapPos.x -= speed;
//		}
//		//	}
//	}
//	else if (playerDir == DIR_LEFT)
//	{
//		//if ((mapPos.y <= 0) || (mapPos.y >= PLAY_SIZE_Y - SCREEN_SIZE_Y))
//		//{
//		if (playerPos.x < mapPos.x + SCREEN_SIZE_X / 2)
//		{
//			mapPos.x += speed;
//		}
//		//}
//	}	//	bgImage = LoadGraphScreen(mapPos.x, mapPos.y, "stage/testStage.png", true);
//}



void GameScene::ChangeColor(void)
{
	trianglePosY += 50;
	//if (680 <= trianglePosY)
	//{
	//	//�@��ԉ��܂ŗ�������W��߂���color��ԁi��ԏ�j�ɖ߂�
	//	trianglePosY = 570;
	//	colorNum = 0;

	//}
	if (2< colorNum)
	{
		//�@��ԉ��܂ŗ�������W��߂���color��ԁi��ԏ�j�ɖ߂�
		trianglePosY = 570;
		colorNum = 0;

	}

	if (colorNum == 1)
	{
		playerColor = COLOR_TYPE::RED;
	}
	else if (colorNum == 2)
	{
		playerColor = COLOR_TYPE::BLUE;
	}
	else if (colorNum == 3)
	{
		playerColor = COLOR_TYPE::GREEN;
	}
//	testNum += 1;

}

void GameScene::PlayerCtl(void)
{
	if (_atackFlag == true)// �v���C���[���U�������Ƃ�=�G�l�~�[���_���[�W���󂯂�ꍇ
	{
		//if ((playerPos.x + _pAtackRange + 75 >= enemyPos.x))
		if(enemyPos.x>= playerPos.x/* + _pAtackRange + 75*/)
		{
			// ���������
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
		if (enemyPos.x <= _shotPos.x + _shotSize)
		{
			// �������U��������������
			enemyPos.x += 50;// �G�l�~�[��������ނ�����
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

}

void GameScene::PlayerDraw(void)
{	

	// �������U��
	if (_shotFlag == true)
	{
		_shot = LoadGraphScreen(_shotPos.x + mapPos.x, _shotPos.y, "image/player/bShot.png", true);
		if (SCREEN_SIZE_X < _shotPos.x + mapPos.x)
		{
			_shotFlag = false;
		}
	}
	// �ߋ����U��
	if (_atackFlag == true)
	{
		// �U��
		DrawBox(playerPos.x + 75 + mapPos.x, 550 - 75, playerPos.x + _pAtackRange + 75 + mapPos.x, 550 - 150, GetColor(0, 255, 0), false);// �U���͈�
		_player = LoadGraphScreen(playerPos.x + mapPos.x, playerPos.y - 150, "image/player/wAttack.png", true);// ���摜
		//_player=SetBlendGraph
		_atackFlag = false;
	}
	if (jumpFlag == true)
	{
		_player = LoadGraphScreen(playerPos.x + mapPos.x, playerPos.y - 150, "image/player/wJump.png", true);
	}
	if (underFlag == true)
	{
		DrawBox(playerPos.x + mapPos.x, playerPos.y - 80, playerPos.x + 150 + mapPos.x, playerPos.y, GetColor(0, 255, 0), false);// �U���͈�
		_player = LoadGraphScreen(playerPos.x + mapPos.x, playerPos.y - 150, "image/player/wUnder.png", true);

	}
	
	if (_atackFlag == false && jumpFlag == false && underFlag == false)
	{
		if (_damageFlag == true)
		{
					_player = LoadGraphScreen(playerPos.x + mapPos.x, playerPos.y - 150, "image/player/wDamage.png", true);// ���摜
			DrawBox(playerPos.x + mapPos.x, playerPos.y, playerPos.x + 150 + mapPos.x, playerPos.y - 150, GetColor(255, 0, 255), false);// �v���C���[

		}
		else
		{
			_player = LoadGraphScreen(playerPos.x + mapPos.x, playerPos.y - 150, "image/player/wIdle.png", true);// ���摜
			DrawBox(playerPos.x + mapPos.x, playerPos.y, playerPos.x + 150 + mapPos.x, playerPos.y - 150, GetColor(255, 0, 255), false);// �v���C���[
			if ((flamCnt / 50) % 2 == 0)
			{
				_player;
			}

		}
	}


}

void GameScene::GameOverDraw(void)
{	
	
	_backLayer =LoadGraphScreen(mapPos.x, mapPos.x, "image/game/back.png", true);
	_mojiGameOver = LoadGraphScreen(SCREEN_SIZE_X / 3-20, 50, "image/game/gameOver.png", true);
	// �{�^��
	_button[static_cast<int>(SCENE_TYPE::SELECT)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2 - 100, "image/helpMode/selectButton.png", true);
	_button[static_cast<int>(SCENE_TYPE::TITLE)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2, "image/helpMode/titleButton.png", true);
	_button[static_cast<int>(SCENE_TYPE::GAME)] = LoadGraphScreen(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2 + 100, "image/helpMode/playButton.png", true);
	int checker;
	checker= LoadGraphScreen(SCREEN_SIZE_X / 3-100, _buttonPosY,"image/game/checkButton.png", true);


	DrawFormatString(SCREEN_SIZE_X - 50, 450, GetColor(255, 255, 255), "[%d]", _buttonNum);

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
	if (!objList)	// �^�̏ꍇ������Ȃ��ꍇ����肽���̂Łu!�v unique�ł�shared�ł������@�c���͈Ⴄ
	{
		objList = std::make_shared<sharedObjList>();	// <>�̒��ɂ͊Ǘ���޼ު��
	}

	objList->clear();
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	trianglePosY = 570;
	// �v���C���[
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
	// �G�l�~�[
	enemyPos = { VECTOR2(SCREEN_SIZE_X / 2,550) };
	enemyAtackRange = { enemyPos.x - 25,400 };
	_eMoveFlag = true;
	_atackFlag = false;
	moveFlag = false;
	_eDeathFlag = false;
	enemyLife = 3;

	time =0;	

	//centerPos = VECTOR2{ SCREEN_SIZE_X/2,SCREEN_SIZE_Y / 2 };
	//bgPosX1=0;				// ���T�C�Y1
	colorNum = 1;

	playerColor = COLOR_TYPE::RED;
	enemyColor = COLOR_TYPE::GREEN;
	enemyType = ENEMY_COLOR::GREEN;
	//markerPos[3]  {
	//	VECTOR2(215,570),VECTOR2(215,620),VECTOR2(215,670)
	//};
	auto marlerPos = VECTOR2(215, 570);
	markerPos[0] = VECTOR2(215, 570);

	score = 0;
	flamCnt = 0;
	oldFlam = flamCnt;
	_buttonPosY = SCREEN_SIZE_Y / 2 - 100;
	//LoadDivGraph("image/player/bMove3.png", 4, 4, 1, 150, 150, GHandle, true);// ���摜
	_buttonNum = 1;

	return 0;
}
