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

//
//void ScoreMng::JunokuraiNum(void)
//{
//	if (10 <= _score && _score <= 99)
//	{
//		auto tesnnnokurai = _score / 10;
//		junokuraiNumber->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_numberTable[tesnnnokurai]));
//	}
//	else if (100 <= _score && _score <= 999999)
//	{
//		auto juunokurai = _score / 10;
//		auto nextjuunokurai = juunokurai % 10;
//		junokuraiNumber->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_numberTable[nextjuunokurai]));
//	}
//}
//
//void ScoreMng::HyakunokuraiNum(void)
//{
//	if (100 <= _score && _score <= 999)
//	{
//		auto hyakunokurai = _score / 100;
//		hyakunokuraiNumber->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_numberTable[hyakunokurai]));
//	}
//	else if (1000 <= _score && _score <= 999999)
//	{
//		auto hundredNumber = _score / 100;
//		auto handred = hundredNumber % 10;
//		hyakunokuraiNumber->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_numberTable[handred]));
//	}
//}
