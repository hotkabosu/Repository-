#pragma once
#include <mutex>
#include <list>
#include <memory>
#include "VECTOR2.h"
#include "BaseScene.h"


enum SCENE_TYPE
{
	SCENE_TYPE_TITLE,
	SCENE_TYPE_SELECT,
	SCENE_TYPE_GAME,
	SCENE_TYPE_RESULT,
	SCENE_TYPE_MAX,
};

class Obj;
class GameCtl;

#define lpSceneMng SceneMng::GetInstance()

// ç∂è„Ç™ÇO
#define SCREEN_SIZE_X 1200	// âÊñ âëúìx 800
#define SCREEN_SIZE_Y 700	//600


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

