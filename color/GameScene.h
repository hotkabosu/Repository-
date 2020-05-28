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

enum class ENEMY_COLOR
{
	NON,
	RED,
	BLUE,
	GREEN,
	MAX
};

enum class ENEMY_TYPE
{
	NON,
	NORMAL,
	BOSS,
	MAX
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
	void NormalEnemy(void);
	void BossCheck(void);
	void StatusDraw(void);
	void StageControl(void);
	void ChangeColor(void);
	void PlayerCtl(void);
	void PlayerDraw(void);

	void AddScore(void);
	void StageDraw(void);

private:
	sharedListObj objList;
	virtual int Init(void);
	bool GameDraw(void);
	
	// Player
	int _player;// �摜
	bool _atackFlag;	// �ߋ����U��
	bool moveFlag;	// �����邩�ǂ���
	bool jumpFlag;
	int jumpCnt;
	bool underFlag;
	VECTOR2 playerPos;// ���W
	VECTOR2 playerOldPos;
	float _pAtackRange;// �U���͈�
	int _damage;
	bool _damageFlag;
	int hpBox;		
	int playerLife;
	// �������U��
	int _shot;
	int _shotSpeed;
	int _shotSize;
	bool _shotFlag;
	VECTOR2 _shotPos;
	//float frendPos;
	//bool hitFrend;



	// enemy
	int _enemy;		// �G
	VECTOR2 enemyAtackRange;
	VECTOR2 enemyPos;
	bool _eMoveFlag;	// �������ǂ����@true=���� false=�����Ȃ�(�������U��)
	bool _eDeathFlag;// ����ł��邩�ǂ���
	int enemyLife;
	// ���̂ق�
	int stageBack;	// �w�i�摜
	DIR playerDir;
	int flamCnt;
	int oldFlam;
	int triangle;
	int trianglePosY;
	VECTOR2 mapPos;
//	const GameCtl& test;
	int time;
	STAGE playStage;

	int bgImage;
	int bgPosX1;				// ���T�C�Y1
	VECTOR2 centerPos;// ��ʒ���

	VECTOR2 markerPos[3];
	COLOR_TYPE colorType[static_cast<int>(COLOR_TYPE::MAX)];
	int nowColor[3];
	int colorNum;
	int enemyNum;
	ENEMY_TYPE enemyTypetest[static_cast<int>(ENEMY_TYPE::MAX)];

	COLOR_TYPE enemyColor;
	ENEMY_COLOR enemyType;
	COLOR_TYPE playerColor;
	
	int _gBoss;
	VECTOR2 _bossPos;
	int _bossLife;
	bool _bossFlag;
	int score;
	int highScore;
};
