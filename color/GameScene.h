#pragma once
#include "BaseScene.h"

class GameCtl;

class GameScene:
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	virtual unique_Base Updata(unique_Base own, const GameCtl& ctl);
	void HitCheck(void);
	void StatusDraw(void);

private:
	virtual int Init(void);
	bool GameDraw(void);
	
	// Player
	bool _atackFlag;
	float _pPosX;
	float _pPosY;
	float _pAtackRange;

	// enemy
	int _enemy;		// �G
	float _ePosX;	// ���W
	bool _eMoveFlag;	// �������ǂ����@true=���� false=�����Ȃ�(�������U��)
	bool _eDeathFlag;// ����ł��邩�ǂ���

	// ���̂ق�
	int stageBack;	// �w�i�摜

};
