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
//	DIR_JUMP,// �W�����v
//	DIR_DOWN,// ���Ⴊ��
//	DIR_MAX
//};
//
//enum ANIM_TBL {			// ��Ұ���ð���
//	ANIM_TBL_START_ID,	// �J�n�ʒu
//	ANIM_TBL_FRAME,		// �ϐ�
//	ANIM_TBL_INV,		// �Ԋu�i�������
//	ANIM_TBL_LOOP,		// ٰ�߂��邩�ǂ���
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
