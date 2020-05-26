#include "DxLib.h"
#include "GameCtl.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "ResultScene.h"
#include "Enemy.h"
#include "Camera.h"
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
	//if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_G])
	//{
	//	return std::make_unique<TitleScene>();
	//}
	// �v���C���[��HP�����邩�G�������Ă���Ƃ��͓����Ă��悢
	
	
	if ((0 <= playerLife) && _eDeathFlag == false)
	{
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RCONTROL] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RCONTROL] == 0)
		{
			ChangeColor();
			testNum += 1;
		}
		
		// D����������E�ړ�
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_D])
		{
			playerPos.x += 5;
			//frendPos += 5;
			moveFlag = true;
			dir = DIR_RIGHT;
		}
		else
		{
			moveFlag = false;

		}
		// ���Ɉړ�
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_A])
		{
			if (0 <= playerPos.x)
			{
				playerPos.x -= 5;
				//frendPos -= 5;
			}
			else
			{
				playerPos.x += 1;

			}
			dir = DIR_LEFT;
		}
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_W] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_W] == 0)
		{
			for (int jumpPos=0; 10 >= jumpPos; jumpPos++)
			{
				playerPos.y -= jumpPos;
			}
			jumpFlag = true;

		}
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_S] == 0)
		{
			underFlag = true;

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
	if (playerLife <= 0)
	{
		// �v���C���[�s�k
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RETURN] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RETURN] == 0)
		{
			SetDrawBright(255, 255, 255);

			return std::make_unique<GameScene>();
		}


	}

	if (_shotFlag == true)
	{
		_shotPos.x += _shotSpeed;
	}

	//if (_atackFlag == true
	//	&& _pPosX + _pAtackRange + 75 >= _ePosX)// �E���U���͈̔͂ɓ����Ă���
	//	//&& _ePosX + 75 >= _pPosX)
	//{
	//	// �G������
	//	_eDeathFlag = true;
	//}
	//
	// Scroll
	//if (dir == DIR_RIGHT && SCREEN_SIZE_X <= _pPosX)
	//{
	// �v���C���[����ʂ̐^�񒆂��E���ɍs������J���������ɃX�N���[������
	//}
	//if (moveFlag == true)
	//{
	//	StageControl();
	//}
	//playerColor;
	//color[testNum];
	lpCamera.CameraControl(playerPos, centerPos);

	AddScore();
	lpScoreMng.setScore(highScore);
	GameDraw();
	flamCnt++;
	return std::move(own);
}

void GameScene::HitCheck(void)
{
	//if (_eMoveFlag == true)
	//{
		// �������ǂ���
		if (playerPos.x + 125 <= enemyPos.x - 25)
		{
			// �v���C���[���E���ɂ����獶�i�v���C���[���j�Ɉړ�
			enemyPos.x -= 2;
			_eMoveFlag = true;

		}
		else if (enemyPos.x +55  <= playerPos.x)
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
			if (_eMoveFlag == false )
			{
				// �߂��ɗ�����v���C���[�ɍU��
				playerPos.x -= 25;
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
			playerLife-=_damage;
		}
	//}

		if (_atackFlag == true)// �v���C���[���U�������Ƃ�=�G�l�~�[���_���[�W���󂯂�ꍇ
		{
			if ((playerPos.x + _pAtackRange + 75 >= enemyPos.x))
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
			//if ((_shotPos.x < enemyPos.x + 100)	// �e�̍�<�G�̉E
			//	&& (enemyPos.x < _shotPos.x + _shotSize)	// �G�̍�<�e�̉E
			//	&& (_shotPos.y < enemyPos.y + 150)	// �e�̏�<�G�̉�
			//	&& (enemyPos.y < _shotPos.y + _shotSize))// �G�̏�<�e�̉�
				if (enemyPos.x<= _shotPos.x + _shotSize)
			{
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
				_shotFlag = false;
			}
		}
		if (enemyLife <= 0)
	{
		//�@
		_eDeathFlag = true;
		_bossFlag = true;

	}

}

/*BOSS*/
//void GameScene::BossCheck(void)
//{
//	if (_bossFlag == true)// �v���C���[���U�������Ƃ�=�G�l�~�[���_���[�W���󂯂�ꍇ
//	{
//		if ((playerPos.x + _pAtackRange + 75 >= enemyPos.x))
//		{
//			// ���������
//			enemyPos.x += 50;
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
//	if (_bossLife <= 0)
//	{
//		//�@
//		_eDeathFlag = true;
//	}
//
//}


bool GameScene::GameDraw(void)
{
	ClsDrawScreen();
	StageDraw();

	if (_shotFlag == true)
	{
		_shot = LoadGraphScreen(_shotPos.x, _shotPos.y, "image/player/baku.png", true);
		if (SCREEN_SIZE_X < _shotPos.x)
		{
			_shotFlag = false;
		}
	}

	//DrawBox(_pPosX, 550, _pPosX+150, 550-150, GetColor(0, 255, 0), TRUE);// �v���C���[


	DrawFormatString(SCREEN_SIZE_X - 100, 600, GetColor(255, 255, 0), "GameScene");
	DrawBox(playerPos.x, playerPos.y, playerPos.x + 150, playerPos.y - 150, GetColor(255, 0, 255), false);// �v���C���[

	//if (_atackFlag == true)
	//{
	//	// �U��
	//	DrawBox(playerPos.x + 75, 550 - 75, playerPos.x + _pAtackRange + 75, 550 - 150, GetColor(0, 255, 0), false);// �U���͈�
	//	_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pTest2.png", true);// ���摜
	//	//_player=SetBlendGraph
	//	_atackFlag = false;
	//}
	//else
	//{
	//	if (_eMoveFlag == false)
	//	{
	//		// �ړ�
	//		//if ((flamCnt / 10) % 2 == 0)
	//		//{
	//		//_player = 
	//				//_player = LoadGraphScreen(_pPosX, _pPosY - 150, "image/player/pTest.png", true);// ���摜
	//		//}
	//				_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pDamage.png", true);// ���摜
	//	}
	//	else
	//	{
	//		_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/pTest.png", true);// ���摜
	//	}
	//}
	//DrawBox(frendPos, playerPos.y - 150, frendPos + 150, playerPos.y - 75, GetColor(255, 0, 255), false);// �v���C���[
	//if (hitFrend == true)
	//{
	//	// �G�ƐڐG������_��
	////	if ((flamCnt / 10) % 2 == 0)
	//	//{
	//		LoadGraphScreen(frendPos, playerPos.y - 150, "image/player/frend/frend2.png", true);
	//	//}
	//}
	//else
	//{
	//	LoadGraphScreen(frendPos, playerPos.y - 150, "image/player/frend/frend2.png", true);

	//}
	if (_bossFlag == true)
	{
		_gBoss = LoadGraphScreen(enemyPos.x, 400, "image/enemy/test2.png", true);
	}
	
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

				DrawBox(enemyPos.x, 550 - 75, enemyPos.x - 25, 550 - 150, GetColor(0, 255, 0), false);// �U���͈�
		}
	}
	else
	{
		//if ((flamCnt / 10) % 2 == 0)
		//{
		//	_enemy = LoadGraphScreen(_ePosX, 400, "image/enemy/test2.png", true);// ���摜

		//}
		//SetDrawBright(255 / 2, 255 / 2, 255 / 2);
		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 0), "WIN");

	}

	if (playerLife <= 0)
	{
		SetDrawBright(255 / 2, 255 / 2, 255 / 2);
		DrawFormatString(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, GetColor(255, 255, 0), "GameOver�@PushEnterKey");
	}
	StatusDraw();
	PlayerColor();
	triangle = LoadGraphScreen(215, trianglePosY, "image/check.png", true);// ���摜
	
	ScreenFlip();
	return false;
}


void GameScene::StatusDraw(void)
{
	// ���̐���艺�ɂg�o��Q�[�W
	DrawLine(0, 700 - 150, 1200, 700 - 150, GetColor(255, 255, 0), TRUE);	
	// ���̐���荶�AHP�̂Ƃ�
	DrawLine(200, 550, 200, 700, GetColor(0, 255, 0), false);
	//hpBox = SetDrawBright(255 - _damage, 255 - _damage, 255 - _damage);
	//hpBox=SetTransColor(255 - _damage, 255 - _damage, 255 - _damage);

	// ���̐����E�A�^�C���Ƃ��X�R�A������Ƃ�
	DrawLine(SCREEN_SIZE_X-200, 550, SCREEN_SIZE_X-200, 700, GetColor(0, 255, 0), false);
	DrawFormatString(SCREEN_SIZE_X - 50, 570, GetColor(255, 255, 255), "[%d]", score);
	//LoadGraphScreen(SCREEN_SIZE_X-180, 570, "image/num.png", true);

// ���̐��̍��E�ɐF�o�[
	DrawLine(SCREEN_SIZE_X /2, 550, SCREEN_SIZE_X/2, 700, GetColor(0, 255, 0), false);

	// �F�Q�[�W
	nowColor[static_cast<int>(COLOR_TYPE::RED)] = DrawBox(250, 570, SCREEN_SIZE_X / 2 - 50, 595, GetColor(255, 0, 0), true);// ��
	
	nowColor[static_cast<int>(COLOR_TYPE::BLUE)] = DrawBox(250, 620, SCREEN_SIZE_X / 2 - 50, 645, GetColor(0, 0, 255), true);// ��
	nowColor[static_cast<int>(COLOR_TYPE::GREEN)] = DrawBox(250, 670, SCREEN_SIZE_X / 2 - 50, 695, GetColor(0, 255, 0), true);// ��

	// GetColor���}�C�i�X���Ɣ��ɂȂ邩��Q�[���I�[�o�[����0���w��
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
		// center�ɗ�����w�i�摜�����ɂ��炵�Ă���
	//	mapPos.x -= 50;
	}

}

//void GameScene::StageControl(void)
//{
//	// ��ʐ^�񒆂��v���C���[�̍��W���E�ɂ��Ă�����^�񒆂����炷
//	if (centerPos.x <= playerPos.x)
//	{
//		// center�ɗ�����w�i�摜�����ɂ��炵�Ă���
//		centerPos.x += 5;
//	}
//	// X����
//	if (mapPos.x < 0)
//	{
//		mapPos.x = 0;
//	}
//	if (mapPos.x > playerPos.x*5-SCREEN_SIZE_X)
//	{
//		mapPos.x =2;
//	}
//	if (SCREEN_SIZE_X/2 <= playerPos.x)
//	{
//		mapPos.x += SCREEN_SIZE_X;
//
//	}
//	bgImage = LoadGraphScreen(0, 0, "stage/testStage.png", true);
//}

void GameScene::ChangeColor(void)
{
	trianglePosY += 50;
	if (680 <= trianglePosY)
	{
		//�@��ԉ��܂ŗ�������W��߂���color��ԁi��ԏ�j�ɖ߂�
		trianglePosY = 570;
		testNum = 0;

	}

	if (testNum == 0)
	{
		playerColor = COLOR_TYPE::RED;
	}
	else if (testNum == 1)
	{
		playerColor = COLOR_TYPE::BLUE;
	}
	else if (testNum == 2)
	{
		playerColor = COLOR_TYPE::GREEN;
	}
//	testNum += 1;

}

void GameScene::PlayerColor(void)
{
	if (_atackFlag == true)
	{
		// �U��
		DrawBox(playerPos.x + 75, 550 - 75, playerPos.x + _pAtackRange + 75, 550 - 150, GetColor(0, 255, 0), false);// �U���͈�
		_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/wAttack.png", true);// ���摜
		//_player=SetBlendGraph
		_atackFlag = false;
	}
	else
	{
		if (_eMoveFlag == false)
		{
			// �ړ�
			//if ((flamCnt / 10) % 2 == 0)
			//{
			//_player = 
					//_player = LoadGraphScreen(_pPosX, _pPosY - 150, "image/player/pTest.png", true);// ���摜
			//}
			_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/wDamage.png", true);// ���摜

		}
		else
		{
			_player = LoadGraphScreen(playerPos.x, playerPos.y - 150, "image/player/wIdle.png", true);// ���摜

		}

	}


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
	auto test =lpStageCtl.getStage();
	if (test == STAGE::FIRST)
	{
		lpStageCtl.FirstStage();
	}
	else if (test == STAGE::SECOND)
	{
		lpStageCtl.SecondStage();
	}

}

//int GameScene::setScore(void)
//{
//	AddScore();
//	return highScore;
//}

int GameScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	trianglePosY = 570;
	// �v���C���[
	//mapPos = { VECTOR2(0, 0) };
	playerPos = { VECTOR2(0, 550) };
	_shotPos = { playerPos.x+200,playerPos.y -125 };
	_shotSpeed = 5;
	_shotSize = 40;
	_shotFlag = false;
	jumpFlag = false;
	underFlag = false;
	_pAtackRange = 125;
	_damage = 0;
	playerLife = 255;
	//frendPos = playerPos.x - 75;
	//hitFrend = false;
	// �G�l�~�[
	enemyPos = { VECTOR2(SCREEN_SIZE_X / 2,550) };
	_eMoveFlag = true;
	_atackFlag = false;
	moveFlag = false;
	_eDeathFlag = false;
	enemyLife = 3;
	_bossLife = 30;
	_bossFlag = false;
	time =0;	

	//centerPos = VECTOR2{ SCREEN_SIZE_X/2,SCREEN_SIZE_Y / 2 };
	//bgPosX1=0;				// ���T�C�Y1
	bgImage = LoadGraph("stage/testStage.png");
	testNum = 1;
	playerColor = COLOR_TYPE::RED;
	enemyColor = COLOR_TYPE::GREEN;
	//markerPos[3]  {
	//	VECTOR2(215,570),VECTOR2(215,620),VECTOR2(215,670)
	//};
	auto marlerPos = VECTOR2(215, 570);
	markerPos[0] = VECTOR2(215, 570);

	score = 0;
	return 0;
}
