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
//	void SetEnemy(const VECTOR2& pos, weakListObj objList);
	void Draw(void);
	//bool MapLoad(void);		// ϯ�߂�۰��
	void FirstStage(VECTOR2 pos);	// ��̫��ϯ��(��)��۰��
	void SecondStage(VECTOR2 pos);	// ��̫��ϯ��(��)��۰��

	STAGE getStage(void);
	void setStage(STAGE stage);

private:
	StageCtl();
	~StageCtl();

	STAGE selectStage;
	// �w�i����ٗp���̨�������
	int bgImage;

};

