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

	// D����������E�ړ�
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

	// �������ǂ���
	if (_pPosX + 150 <= _ePosX - 25)
	{			// �v���C���[���E���ɂ����獶�i�v���C���[���j�Ɉړ�
		_ePosX -= 2;
		_eMoveFlag = true;

	}
	else if (_ePosX + 100 + 25 <= _pPosX)
	{
		// �v���C���[��荶���ɂ�����E�i�v���C���[���j�Ɉړ�
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
	//DrawBox(_pPosX, 550, _pPosX+150, 550-150, GetColor(0, 255, 0), TRUE);// �v���C���[
	DrawBox(_pPosX, _pPosY, _pPosX + 150, _pPosY - 150, GetColor(255, 0, 255), false);// �v���C���[


	DrawFormatString(150, 150, GetColor(255, 255, 0), "GameScene");

	if (_atackFlag == true)
	{
		DrawBox(_pPosX+_pAtackRange, 550 - 75, _pPosX+_pAtackRange +75, 550 - 150, GetColor(0, 255, 0), false);// �U���͈�
		_atackFlag = false;
	}


	//
	if (_eDeathFlag == false)
	{// ����łȂ�����`��
		//DrawBox(_ePosX, 550, _ePosX + 30, 550 - 150, GetColor(0, 255, 255), true);//�E�[��ʊO
		_enemy = LoadGraphScreen(_ePosX, 400, "image/enemy/testE.png", true);// ���摜
	}
	if (_eMoveFlag == false)
	{
		// �U��
		DrawBox(_ePosX, 550 - 75, _ePosX-25, 550 - 150, GetColor(0, 255, 0), false);// �U���͈�
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
	_pAtackRange = 150;
	_ePosX = SCREEN_SIZE_X-30;

	// �G�l�~�[
	_eMoveFlag = true;
	_atackFlag = false;
	_eDeathFlag = false;
	return 0;
}
