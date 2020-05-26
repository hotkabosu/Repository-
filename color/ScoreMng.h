#pragma once

enum class NUMBER
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	MAX
};

#define lpScoreMng ScoreMng::GetInstance()


class ScoreMng
{
public:
	static ScoreMng& GetInstance(void)
	{
		static ScoreMng s_Instance;
		return (s_Instance);
	}
	//void JunokuraiNum(void);
	//void HyakunokuraiNum(void);
	int getScore(void);
	void setScore(int score);

	//void GoodHit(void);
	//void NormalHit(void);
	//void BadHit(void);

	int _score;
	int _nowScore;

private:
	ScoreMng();
	~ScoreMng();
	virtual int Init(void);

	const char* _numberTable[static_cast<int>(NUMBER::MAX)] =
	{ "numberZero","numberOne","numberTwo","numberThree","numberFour","numberFive" ,"numberSix","numberSeven","numberEight","numberNine" };
	int junokuraiNumber;
	int hyakunokuraiNumber;


};

