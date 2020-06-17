#include "DxLib.h"
#include "ScoreMng.h"
#include "SceneMng.h"

int ScoreMng::getScore(void)
{
	return _score;
}

void ScoreMng::setScore(int score)
{
	_score = score;
}

ScoreMng::ScoreMng()
{
	Init();
}


ScoreMng::~ScoreMng()
{

}

int ScoreMng::Init(void)
{

	LoadGraphScreen(SCREEN_SIZE_X - 180, 570, "image/game/num0.png", true);

	return 0;
}

