#include "Dxlib.h"	// DxLibײ���؂��g�p����
#include "SceneMng.h"
#include "GameCtl.h"
#include "TitleScene.h"
#include"SelectScene.h"
#include "GameScene.h"

SceneMng::SceneMng()	// �ݽ�׸�
{
	SysInit();
}

SceneMng::~SceneMng()	// �޽�׸�
{
}

void SceneMng::Run(void) 
{
								// ��ԍŏ��ɌĂ΂����
	activeScene = std::make_unique<SelectScene>();	// ������

	//ImageMng::GetInstance().GetID("���", "image/char.png", { 30, 32 }, { 10,10 });	// �L�����摜

	// ---------- �ް�ٰ�� 
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)	// ����DxLib�̖���
	{
		gameCtl->UpdateKey();

		activeScene = activeScene->Updata(std::move(activeScene), *gameCtl);
	}
}

VECTOR2 SceneMng::GetScreenSize(void)
{
	return VECTOR2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

bool SceneMng::SetDrawOffset(VECTOR2 vec)
{
	drawOffset = vec;
	return true;
}

const VECTOR2& SceneMng::GetDrawOffset(void)
{
	return drawOffset;
}


bool SceneMng::DelObjList(std::list<Obj*>::iterator itr)
{
	delete (*itr);
	return true;
}

bool SceneMng::SysInit(void)
{
	// ���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);					// true:window�@false:�ٽ�ذ�
	SetWindowText("Color");
	if (DxLib_Init() == -1) return false;	// DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);			// �ЂƂ܂��ޯ��ޯ̧�ɕ`��
	gameCtl = std::make_unique<GameCtl>();
	return true;
}

