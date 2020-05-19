//#pragma once
//#include <memory>
//#include <array>
//#include "VECTOR2.h"
//#include "Obj.h"
//
//using DIR_TBL_ARRAY = std::array<int, DIR_MAX>;
//#define lpPlayer Player::GetInstance()
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
//private:
//	bool initAnim(void);
//	bool CheckObjType(OBJ_TYPE type);
//
//	void SetMove(const GameCtl& ctl, weakListObj objList);
//	DIR_TBL_ARRAY		 keyIdTbl;
//
//	int _player;
//	bool _atackFlag;
//	VECTOR2 _pos;
//	float _pAtackRange;
//
//	DIR dir;
//	int speed;
//	VECTOR2 pos(float x, float y);
//};
//
