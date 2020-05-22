#pragma once
#include "BaseScene.h"
#include "Obj.h"
#include "color.h"
#include "StageCtl.h"
#include "VECTOR2.h"


// �v���C���[���󂯂�_���[�W���
enum DAMAGE
{
	// ���݂̐F���G�̐F�ɑ΂���
	DAMAGE_WEAK,		// �ア�F�@��jplayer�@enemy��		������12�_���[�W
	DAMAGE_NORMAL,		// �����F�@��jplayer�@enemy��		������8�_���[�W
	DAMAGE_STRONG,		// �����F ��jplayer�@enemy��		������4�_���[�W
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
	void ChangeColor(void);
	void PlayerColor(void);

private:
	sharedListObj objList;
	virtual int Init(void);
	bool GameDraw(void);
	
	// Player
	int _player;// �摜
	bool _atackFlag;
	bool moveFlag;
	VECTOR2 playerPos;// ���W
	float _pAtackRange;// �U���͈�
	int _damage;
	int hpBox;
	int playerLife;
	int jumpCnt;
	//float frendPos;
	//bool hitFrend;



	// enemy
	int _enemy;		// �G
	VECTOR2 enemyPos;
	bool _eMoveFlag;	// �������ǂ����@true=���� false=�����Ȃ�(�������U��)
	bool _eDeathFlag;// ����ł��邩�ǂ���
	int enemyLife;
	// ���̂ق�
	int stageBack;	// �w�i�摜
	DIR dir;
	int flamCnt;
	int triangle;
	int trianglePosY;
	//VECTOR2 mapPos;
//	const GameCtl& test;
	int time;
	STAGE playStage;

	int bgImage;
	int bgPosX1;				// ���T�C�Y1
	VECTOR2 centerPos;// ��ʒ���

	VECTOR2 markerPos[3];
	COLOR_TYPE colorType[static_cast<int>(COLOR_TYPE::MAX)];
	int nowColor[3];
	int testNum;
	COLOR_TYPE enemyColor;
	COLOR_TYPE playerColor;
	
	
	int score;
};
