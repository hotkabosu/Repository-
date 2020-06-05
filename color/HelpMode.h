#pragma once
#include "VECTOR2.h"
#include "SceneMng.h"

#define lpHelpMode HelpMode::GetInstance()

class HelpMode
{
public:
	static HelpMode& GetInstance(void)
	{
		static HelpMode s_Instance;
		return (s_Instance);
	}
	virtual unique_Base Updata(unique_Base own, const GameCtl& ctl);
	void CheckButton(const GameCtl& ctl);
	bool getHelpFlag(void);
	void setHelpFlag(bool flag);
	bool HelpDraw(void);
	virtual int Init(void);

private:
	HelpMode();
	~HelpMode();
	
	bool _helpFlag;
	VECTOR2 _helpPos;
	int _helpTitle;
	int _selectBackButton;
	int _titleBackButton;
	int _playBuckButton;
	int _button[3];
	int _buttonNum;
	bool selectFlag;
	int changeTime;

};

