#pragma once
#include <map>
#include <mutex>
#include "VECTOR2.h"
#include "classObj.h"

enum DIR {
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_MAX
};

enum ANIM_TBL {			// ��Ұ���ð���
	ANIM_TBL_START_ID,	// �J�n�ʒu
	ANIM_TBL_FRAME,		// �ϐ�
	ANIM_TBL_INV,		// �Ԋu�i�������
	ANIM_TBL_LOOP,		// ٰ�߂��邩�ǂ���
	ANIM_TBL_MAX,
};

enum OBJ_TYPE {
	OBJ_TYPE_PLAYER,
	OBJ_TYPE_ENEMY,
	OBJ_TYPE_MAX
};

class GameCtl;

class Obj
{
public:
	Obj(VECTOR2 drawOffset);
	Obj();
	// Draw���邾���ŉ摜���\���ł���悤��
	bool init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt);
	bool init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos);
	virtual bool initAnim(void) { return true; };
	~Obj();
	void Update(const GameCtl& ctl, weakListObj objList);	// void��GameCtl�N���X�̎Q�Ƃɕς�����

	// �֐��[ ���z�֐� ����ł邩�ǂ����̔���֐� ����ł��ꍇ�^��Ԃ� =�ʏ�͎���łȂ�
	virtual bool CheckDeath(void) { return false; };

	// �w�肵���^�Ɠ������ǂ�������
	virtual bool CheckObjType(OBJ_TYPE type) = 0;// ���q�֐��͐^�U������Ԃ�l�͊�{�I��bool

	virtual void Draw(void);	// �`��
	void Draw(unsigned int id);	// id�w��
	const VECTOR2& GetPos(void);// ���W
	// ID���ǂ��w�肷�邩 id,id,�ڰѐ�,�������(�Ԋu),ٰ�߂��邩�ǂ���
	bool AddAnim(std::string animName, int id_x, int id_y, int frame, int inv, bool loop);
	bool SetAnim(std::string animName);
	std::string GetAnim(void);

private:
	virtual void SetMove(const GameCtl& ctl, weakListObj objList) = 0;	// ���ڽ�Ȃ��@�������z�֐�

	std::map <std::string, int[ANIM_TBL_MAX]>animTable;		// ��Ұ��݂��n�܂����綳�ı��߂���
	std::string animName;		// �\����Ұ��ݖ�

protected:
	bool animEndFlag;			// ��Ұ��ݍŏI�ϓ��B�׸�
	unsigned int animCnt;		// ��Ұ��ݶ���
	const VECTOR2 drawOffset;	// �`��̾��
	VECTOR2 pos;				// ���W	
	// pos &pos �ǂ���ł��悢 �Q�ƌ���������\��������Ȃ�&�͂���Ȃ�
	void SetPos(VECTOR2 pos);

	std::string imageName;		// �\���摜̧�ٖ�
	VECTOR2 divSize;			// �������ށ@Ͻ�ڂ̻��ނƓ���
	VECTOR2 divCnt;				// ������
	DIR dir;					// ����
	bool visible;				// �\���E��\��

};