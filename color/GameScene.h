#pragma once
#include "BaseScene.h"
#include "Obj.h"
#include "VECTOR2.h"


// �v���C���[���󂯂�_���[�W���
enum DAMAGE
{
	DAMAGE_WEAK,// �ア�F�@��jplayer�@enemy��
	DAMAGE_NORMAL,// �����F�@��jplayer�@enemy��
	DAMAGE_STRONG,// �����F ��jplayer�@enemy��
	DAMAGE_MAX
};

class GameCtl;
class Obj;

class GameScene:
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	virtual unique_Base Updata(unique_Base own, const GameCtl& ctl);
	void HitCheck(void);
	void StatusDraw(void);
	void StageControl(void);

	void PlayerColor(void);

private:
	sharedListObj objList;
	virtual int Init(void);
	bool GameDraw(void);
	
	// Player
	int _player;// �摜
	bool _atackFlag;
	VECTOR2 playerPos;// ���W
	float _pAtackRange;// �U���͈�
	int _damage;
	int hpBox;
	int playerLife;

	float frendPos;
	bool hitFrend;
	// enemy
	int _enemy;		// �G
	float _ePosX;	// ���W
	bool _eMoveFlag;	// �������ǂ����@true=���� false=�����Ȃ�(�������U��)
	bool _eDeathFlag;// ����ł��邩�ǂ���
	int enemyLife;
	// ���̂ق�
	int stageBack;	// �w�i�摜
	DIR dir;
	int flamCnt;

	VECTOR2 mapPos;

	int time;
};
