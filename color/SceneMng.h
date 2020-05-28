#pragma once
#include <mutex>
#include <list>
#include <memory>
#include "VECTOR2.h"
#include "BaseScene.h"


enum class SCENE_TYPE
{
	TITLE,
	SELECT,
	GAME,
	RESULT,
	MAX,
};

class Obj;
class GameCtl;

#define lpSceneMng SceneMng::GetInstance()

// ç∂è„Ç™ÇO
#define SCREEN_SIZE_X 1200	// âÊñ âëúìx 800
#define SCREEN_SIZE_Y 700	//600

#define PLAY_SIZE_X 2400
#define PLAY_SIZE_Y 500

#define CHIP_SIZE_X 50
#define CHIP_SIZE_Y 50

class SceneMng
{
public:
	static SceneMng& GetInstance(void)
	{
		static SceneMng s_Instance;
		return (s_Instance);		
	}
	void Run(void);
	VECTOR2 GetScreenSize(void);
	bool SetDrawOffset(VECTOR2 vec);
	const VECTOR2& GetDrawOffset(void);
	bool DelObjList(std::list<Obj*>::iterator itr);	

private:

	SceneMng();
	~SceneMng();
	VECTOR2 drawOffset;

	std::unique_ptr<GameCtl>gameCtl;
	unique_Base activeScene;
	bool SysInit(void);

};

