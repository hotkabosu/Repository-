#pragma once
#include <memory>


// �̾�Ă̈ʒu
#define GAME_SCREEN_X 40	// �ްѴر�̉��\���̾��
#define GAME_SCREEN_Y 75	// �ްѴر�̏c�\���̾��

// �ްт���ڲ�ر
#define GAME_SCREEN_SIZE_X 640	// �ްѴر�̉�����
#define GAME_SCREEN_SIZE_Y 480	// �ްѴر�̏c����

#define CHIP_SIZE 20

class BaseScene; // �������ߐ錾
class GameCtl;

using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	// �ݽ�׸��͂���Ȃ� �K�v�Ȃ̂��޽�׸�
	virtual ~BaseScene();

	virtual unique_Base Updata(unique_Base own, const GameCtl&ctl) = 0;// own�������g �������z�֐���
	// �������z�֐����p�����鼰݂͕K���p�ӂ������Ă��������A�Y��邱�Ƃ��Ȃ��悤��
	virtual bool CheckEditMode(void) {	return false;};

private:

	virtual int Init(void) = 0;
};