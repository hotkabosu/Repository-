#include "Dxlib.h"
#include "SelectScene.h"
#include "SceneMng.h"
#include "GameCtl.h"
#include "TitleScene.h"
#include "GameScene.h"


SelectScene::SelectScene()
{
	Init();
}


SelectScene::~SelectScene()
{

}

unique_Base SelectScene::Updata(unique_Base own, const GameCtl & ctl)
{
	// EnterKeyで決定
	if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_RETURN] == 1
		&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_RETURN] == 0)
	{
		selectFlag = true;
	}

	if (30 <= selectPos.y && selectPos.y <=620)
	{
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_W] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_W] == 0)
		{
			// W=上のマップ
			selectPos.y -= 270;
		//	Stage(stage1, STAGE::FIRST);
		}
		if (ctl.GetCtl(KEY_TYPE_NOW)[KEY_INPUT_S] == 1
			&& ctl.GetCtl(KEY_TYPE_OLD)[KEY_INPUT_S] == 0)
		{
			//if (nowPos.y <= selectPos.y + 271)
			//{
			//	selectPos.y += 0;
			//}
			//else
			//{
			selectPos.y += 270;
		//	Stage(stage2, STAGE::SECOND);

			//}
		}
	}

	if (selectFlag == true)
	{
		changeTime++;
		// エンターを押したらchangeTime加算
		//　changeTimeが50になるまで点滅を早く　50を超えたらゲームシーンに移動
		if (50 <= changeTime)
		{
			selectFlag = false;
			return std::make_unique<GameScene>();
		}

	}

	// 決定したら

	SelectDraw();
	flamCnt++;

	return std::move(own);
}

bool SelectScene::FadeInScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(255, 255, 255);
		fadeCnt = 0;
		return false;
	}
}

//STAGE SelectScene::StageLoad(STAGE getStage, VECTOR2 pos, std::string f_name, bool flag)
//{
//	stage1 = LoadGraph("image/select/testStage.png");
//
//	auto test = LoadGraphScreen(pos.x, pos.y, stage1, flag);
//	if (selectPos.y == 30)
//	{
//
//	}
//	else
//	{
//		stage2 = LoadGraphScreen(0, 0, "stage/testStage2.png", true);
//	}
//	return getStage;
//}

bool SelectScene::SelectDraw(void)
{
	ClsDrawScreen();
	//backImage = LoadGraphScreen(0, 0, "image/select/sBack0.png", true);

	DrawFormatString(150, 100, GetColor(255, 0, 255), "SelectStage　PushEnter");
	if (selectFlag == false)
	{
		if ((flamCnt / 30) % 2 == 0)
		{

			DrawBox(selectPos.x, selectPos.y, selectPos.x+540, selectPos.y + 270, GetColor(0, 255, 0), true);
		}
	}
	else
	{
		// ステージが決まった
		if ((flamCnt / 5) % 2 == 0)
		{

			DrawBox(selectPos.x, selectPos.y, selectPos.x+540, selectPos.y+270, GetColor(0, 255,100), true);
		}

	}
	stage1 = LoadGraphScreen(100, 50, "image/select/testStage.png", true);
	stage2 = LoadGraphScreen(100, 320, "image/select/testStage2.png", true);

	ScreenFlip();

	return false;
}


int SelectScene::Init(void)
{
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	selectPos = { VECTOR2(80,30) };
	nowPos.y = selectPos.y;
	changeTime = 0;
	selectFlag = false;
	return 0;
}
