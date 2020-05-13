//#pragma once
//#include <memory>
//#include <array>
//#include "VECTOR2.h"
//#include "Obj.h"
//
//
//enum DIR {
//	DIR_LEFT,
//	DIR_RIGHT,
//	DIR_JUMP,// ジャンプ
//	DIR_DOWN,// しゃがみ
//	DIR_MAX
//};
//
//enum ANIM_TBL {			// ｱﾆﾒｰｼｮﾝﾃｰﾌﾞﾙ
//	ANIM_TBL_START_ID,	// 開始位置
//	ANIM_TBL_FRAME,		// ｺﾏ数
//	ANIM_TBL_INV,		// 間隔（ｲﾝﾀｰﾊﾞﾙ
//	ANIM_TBL_LOOP,		// ﾙｰﾌﾟするかどうか
//	ANIM_TBL_MAX,
//};
//
//enum OBJ_TYPE {
//	OBJ_TYPE_PLAYER,
//	OBJ_TYPE_ENEMY,
//	OBJ_TYPE_MAX
//};
//
//class Player:
//	public Obj
//
//{
//public:
//	Player(VECTOR2 setUpPos, VECTOR2 drawOffset);
//
//	Player();
//	~Player();
//
//	bool PlayerDraw(void);
//
//private:
//	DIR dir;
//	int speed;
//	VECTOR2 pos(float x, float y);
//};
//
