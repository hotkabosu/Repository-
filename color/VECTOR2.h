#pragma once
class VECTOR2
{
public:
	VECTOR2();
	VECTOR2(int x, int y);

	~VECTOR2();

	int x;
	int y;
	//ë„ì¸ââéZéq
	VECTOR2& operator = (const VECTOR2& vec);

	//ìYÇ¶éöââéZéq
	int& operator[](int i);
	//î‰ärââéZéq
	bool operator ==(const VECTOR2& vec) const;
	bool operator !=(const VECTOR2& vec) const;
	bool operator >=(const VECTOR2& vec) const;
	bool operator < (const VECTOR2& vec) const;	// < ÇÃãtÇÕ >=

	//bool operator <=(const VECTOR2& vec) const;
	//bool operator > (const VECTOR2& vec) const;


	//íPçÄââéZéq
	VECTOR2& operator+=(const VECTOR2& vec);
	VECTOR2& operator-=(const VECTOR2& vec);
	VECTOR2& operator*=(int k);
	VECTOR2& operator/=(int k);
	VECTOR2 operator+()const;
	VECTOR2 operator-()const;
};

//ÉxÉNÉgÉãÇ∆ÉxÉNÉgÉãÇÃââéZ
//Vector2+Vector2
VECTOR2 operator+(const VECTOR2& u, const VECTOR2& v);
//Vector2-Vector2
VECTOR2 operator-(const VECTOR2& u, const VECTOR2& v);

// VECTOR2*VECTOR2
VECTOR2 operator*(const VECTOR2 & u, const VECTOR2 & v);
//int*Vector2
VECTOR2 operator*(int v, const VECTOR2 & u);
//Vector2*int
VECTOR2 operator*(const VECTOR2 & u, int v);
//Vector2+int
VECTOR2 operator+(const VECTOR2& u, int v);
//Vector2-int
VECTOR2 operator-(const VECTOR2 & u, int v);

//Vector2/int
VECTOR2 operator/(const VECTOR2 & u, int v);
// VECTOR2%int
VECTOR2 operator%(const VECTOR2 & u, int v);
// VECTOR2/VECTOR2
VECTOR2 operator/(const VECTOR2 & u, const VECTOR2 & v);
// VECTOR2%VECTOR2
VECTOR2 operator%(const VECTOR2 & u, const VECTOR2 & v);
