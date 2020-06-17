#pragma once
#include "VECTOR2.h"
#include "classObj.h"


enum class STAGE {
	FIRST,
	SECOND,
	MAX
};

#define lpStageCtl StageCtl::GetInstance()


class StageCtl
{
public:
	static StageCtl& GetInstance(void)
	{
		static StageCtl s_Instance;
		return (s_Instance);
	}
	void FirstStage(VECTOR2 pos);	// ��̃}�b�v
	void SecondStage(VECTOR2 pos);	// ���̃}�b�v

	STAGE getStage(void);
	void setStage(STAGE stage);

private:
	StageCtl();
	~StageCtl();

	STAGE selectStage;
	// �w�i����ٗp���̨�������
	int bgImage;

};

