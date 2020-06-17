#pragma once

#define lpScoreMng ScoreMng::GetInstance()


class ScoreMng
{
public:
	static ScoreMng& GetInstance(void)
	{
		static ScoreMng s_Instance;
		return (s_Instance);
	}
	int getScore(void);
	void setScore(int score);


private:
	ScoreMng();
	~ScoreMng();
	virtual int Init(void);

	int _score;
	int _nowScore;

};

