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

	// D����������E�ړ�
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_D])
	{
		_pPosX += 5;
		dir = DIR_RIGHT;
	}
	// ���Ɉړ�
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
	// �U��
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_K])
	{
		_atackFlag = true;
	}


	//if (_atackFlag == true
	//	&& _pPosX + _pAtackRange + 75 >= _ePosX)// �E���U���͈̔͂ɓ����Ă���
	//	//&& _ePosX + 75 >= _pPosX)
	//{
	//	// �G������
	//	_eDeathFlag = true;
	//}


	// Scroll
	//if (dir == DIR_RIGHT && SCREEN_SIZE_X <= _pPosX)
	//{
	// �v���C���[����ʂ̐^�񒆂��E���ɍs������J���������ɃX�N���[������
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
		// �������ǂ���
		if (_pPosX + 125 <= _ePosX - 25)
		{
			// �v���C���[���E���ɂ����獶�i�v���C���[���j�Ɉړ�
			_ePosX -= 2;
			_eMoveFlag = true;

		}
		else if (_ePosX + 55 <= _pPosX)
		{
			// �v���C���[��荶���ɂ�����E�i�v���C���[���j�Ɉړ�
			_ePosX += 2;
			_eMoveFlag = true;

		}
		else
		{
			// �ڐG�����Ƃ�
			_eMoveFlag = false;
			//if ((_ePosX + 100 <= _pPosX) || (_pPosX + 150 <= _ePosX))
			//{
			//	
			//}
		}
	}

	if (_atackFlag == true)// �v���C���[���U�������Ƃ�
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
		// ���̎��Ԃ��U�����󂯂����̎���+50.0�𒴂����瓮���Ă��悢
		_ePosX;
	}
	//if (eHP == 0)
	//{
	//	//�@
	//	_eDeathFlag = true;
	//}

}


bool GameScene::GameDraw(void)
{
	ClsDrawScreen();
	stageBack = LoadGraphScreen(0, 0, "stage/testStage.png", true);
	//DrawBox(_pPosX, 550, _pPosX+150, 550-150, GetColor(0, 255, 0), TRUE);// �v���C���[


	DrawFormatString(SCREEN_SIZE_X-100, 600, GetColor(255, 255, 0), "GameScene");
	DrawBox(_pPosX, _pPosY, _pPosX + 150, _pPosY - 150, GetColor(255, 0, 255), false);// �v���C���[

	if (_atackFlag == true)
	{
		// �U��
		DrawBox(_pPosX + 75, 550 - 75, _pPosX + _pAtackRange + 75, 550 - 150, GetColor(0, 255, 0), false);// �U���͈�
		_player = LoadGraphScreen(_pPosX, _pPosY - 150, "image/player/pTest2.png", true);// ���摜
		_atackFlag = false;
	}
	else
	{
		// �ړ�
		_player = LoadGraphScreen(_pPosX, _pPosY - 150, "image/player/pTest.png", true);// ���摜

	}


	//�@�G�������Ă�Ƃ�
	if (_eDeathFlag == false)
	{
		
		if (_eMoveFlag == true)
		{
			// ����łȂ�����`��
		//DrawBox(_ePosX, 550, _ePosX + 30, 550 - 150, GetColor(0, 255, 255), true);//�E�[��ʊO
			DrawBox(_ePosX, 550, _ePosX + 100, 400, GetColor(255, 0, 0), false);// 
			_enemy = LoadGraphScreen(_ePosX, 400, "image/enemy/test2.png", true);// ���摜

		}
		// �����ĂȂ��Ƃ����L�����ɐڋ߂��I����� 
		else if (_eMoveFlag == false)
		{
			//if ((flamCnt / 10) % 2 == 0)
			//{
				// �U��
				_enemy = LoadGraphScreen(_ePosX-25, 400, "image/enemy/test3.png", true);// ���摜

				DrawBox(_ePosX, 550 - 75, _ePosX - 25, 550 - 150, GetColor(0, 255, 0), false);// �U���͈�
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
	// ���̐���艺�ɂg�o��Q�[�W
	DrawLine(0, 700 - 150, 1200, 700 - 150, GetColor(255, 255, 0), TRUE);	
	// ���̐���荶�AHP�̂Ƃ�
	DrawLine(200, 550, 200, 700, GetColor(0, 255, 0), false);
	hpBox=DrawBox(0, 550 , 200, 700, GetColor(255, 255, 255), true);
	//hpBox = SetDrawBright(255 - _damage, 255 - _damage, 255 - _damage);


	// ���̐����E�A�^�C���Ƃ��X�R�A������Ƃ�
	DrawLine(SCREEN_SIZE_X-200, 550, SCREEN_SIZE_X-200, 700, GetColor(0, 255, 0), false);
	// ���̐��̍��E�ɐF�o�[
	DrawLine(SCREEN_SIZE_X /2, 550, SCREEN_SIZE_X/2, 700, GetColor(0, 255, 0), false);

	// �F�Q�[�W
	DrawBox(250, 570, SCREEN_SIZE_X / 2 - 50, 595, GetColor(0, 255, 0), true);// ��
	DrawBox(250, 620, SCREEN_SIZE_X / 2 - 50, 645, GetColor(255, 0, 0), true);// ��
	DrawBox(250, 670, SCREEN_SIZE_X / 2 - 50, 695, GetColor(0, 0, 255), true);// ��

}



int GameScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));

	// �v���C���[
	_pPosY = 550;
	_pPosX = 0;
	_pAtackRange = 125;
	_damage = 0;

	// �G�l�~�[
	_ePosX = SCREEN_SIZE_X;
	_eMoveFlag = true;
	_atackFlag = false;
	_eDeathFlag = false;
	eHP = 2;

	nowTime = 0.0f;
	oldTime = nowTime;
	return 0;
}
