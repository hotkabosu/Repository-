#include "Dxlib.h"
#include "ImageMng.h"
#include "Obj.h"

Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)
{
	dir = DIR_DOWN;	// DOWN��0
	visible = true;		// �ŏ��͐��true

}

Obj::Obj()
{
	dir = DIR_DOWN;
	visible = true;		// �ŏ��͐��true
}

// �ݽ�ݽ�ł���@�������Ă΂Ȃ��ƕ`��ł��Ȃ�
bool Obj::init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt)
{
//	lpImageMng.GetID(fileName, divSize, divCnt);	// ���ݸނ���۰ق��ČĂяo������
	// ���		�F���t�ɂȂ�Ƌt�ɑ�����Ă���@�Z���@����
	imageName = fileName;
	this->divSize = divSize;
	this->divCnt = divCnt;
	return true;
}

bool Obj::init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos)
{
	init(fileName, divSize, divCnt);
	SetPos(pos);
	return true;
}

Obj::~Obj()
{
}

void Obj::Update(const GameCtl& ctl, weakListObj objList)
{
	SetMove(ctl, objList);	// �p����ɂ��� �������z�֐�
}

void Obj::Draw(void)	 // �`�� ���̉摜�̂ǂ��̺ς�`�悷��̂��@
{
	if (imageName.length() == 0)
	{
		return;
	}
	unsigned int id = 0;	// id��0��
	if (animTable.find(animName) != animTable.end())
	{
		// ۰�ٕϐ� ���߂�l��animcount �̊���Z(/)�̌���
		// �S�̂�3�R�}�Ȃ�0�C1�C2�@��01222�`�ɂ���
		int count = (animCnt / animTable[animName][ANIM_TBL_INV]);

		// (ٰ�߂��ǂ���||���Ă��ڰѐ���菬�������ǂ���)
		if (animTable[animName][ANIM_TBL_LOOP]
			|| count < animTable[animName][ANIM_TBL_FRAME])
		{
			// 012,012���J��Ԃ� �܂�01��else�Ɠ����ɂȂ邩�炱����ŏ�������
			count %= animTable[animName][ANIM_TBL_FRAME];
		}
		else
		{
			// �l��012222�̏��������� �s����1�傫�� 
			count = animTable[animName][ANIM_TBL_FRAME] - 1;
			animEndFlag = true;//�ŏI�ςɓ��B
			visible = false;

		}
		// ���Z����l��0������e�����Ȃ�
		// ANIM_TBL_START_ID���N�_ FRAME��-1�ł����v

		id = animTable[animName][ANIM_TBL_START_ID] + (int)dir
			+ count * divCnt.x;

		//id = animTable[animName][ANIM_TBL_START_ID] +(int)dir
		//	+ ((animCnt / animTable[animName][ANIM_TBL_INV])
		//	% animTable[animName][ANIM_TBL_FRAME])*divCnt.x; ����
	}
	animCnt++;
	if (id < IMAGE_ID(imageName).size())	// id���z��͈͓̔����ǂ���������
	{
		if (visible)
		{
			DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y,
				IMAGE_ID(imageName)[id], true);	// pos���߼޼�݂ɕ`�� [id�ԍ�]
		}
	}
	// �t�@�C�����ǂݍ��܂�Ă��邩 �L���Ȓl���ǂ������`�F�b�N

}

void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())	// id���z��͈͓̔����ǂ���������
	{
		if (visible)
		{

			DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y,
				IMAGE_ID(imageName)[id], true);
			// drawOffset�ǉ��ō��ォ��Ͻ�ڏ��
		}
	}
}

const VECTOR2& Obj::GetPos(void)
{
	return pos;
}

bool Obj::AddAnim(std::string animName, int id_x, int id_y, int frame, int inv, bool loop)
{
	// ���ɂȂ�l�������@animname�Ƃ���string�^�̂��̂��g��
	animTable[animName][ANIM_TBL_START_ID] = divCnt.x * id_y + id_x;
	animTable[animName][ANIM_TBL_FRAME] = frame;
	animTable[animName][ANIM_TBL_INV] = inv;
	animTable[animName][ANIM_TBL_LOOP] = loop;
	return true;
}

bool Obj::SetAnim(std::string animName)
{
	if (Obj::animName == animName)	// �d�������������ق����ǂ� 
	{
		return true;
	}
	// find���݂��邩�ǂ��� ���݂��Ȃ��ꍇ
	if (animTable.find(animName) == animTable.end())
	{
		return false;
	}
	// �d�����ĂȂ����݂��Ă����ꍇ
	Obj::animName = animName;
	Obj::animCnt = 0;				// Obj::�͂ǂ���ł��悢 ۰�ٕϐ��ƌ�����Ȃ��悤��
	animEndFlag = false;		// 2�ڂ�if���̉��@��Ұ��݂�؂�ւ��Ȃ�����true
	 // �ް������݂�����۰�ق�animName�Ɂ@���݂��Ȃ��ꍇ��false
	return false;
}

std::string Obj::GetAnim(void)
{
	return animName;
}

void Obj::SetPos(VECTOR2 pos)
{
	Obj::pos = pos;
}