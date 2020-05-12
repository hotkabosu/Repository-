#include "VECTOR2.h"

VECTOR2::VECTOR2()
{
	x = 0;
	y = 0;
}

VECTOR2::VECTOR2(int x, int y) //引数付きｺﾝｽﾄﾗｸﾀ
{
	this->x = x;
	this->y = y;
}

VECTOR2::~VECTOR2()
{
}

// 代入演算子
VECTOR2 & VECTOR2::operator=(const VECTOR2 & vec)
{
	//(*this).x = vec.x;// ↓と同じ,アドレスを実体化
	this->x = vec.x;
	this->y = vec.y;
	return (*this);	//　返り値を参照で返す→引数を渡すときと同じ,
					// 自分自身はthisﾎﾟｲﾝﾀ　,thisだとアドレス返しになるから*thisにする
}

int & VECTOR2::operator[](int i)
{
	if (i = 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

// 比較演算子
// const　読み込み専用で比較演算子を使う時にconsr修飾子がないとｺﾝﾊﾟｲﾙが通らない
bool VECTOR2::operator==(const VECTOR2 & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}

bool VECTOR2::operator!=(const VECTOR2 & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}

bool VECTOR2::operator>=(const VECTOR2 & vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));//
}

bool VECTOR2::operator<(const VECTOR2 & vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y));//
}

//bool VECTOR2::operator<=(const VECTOR2 & vec) const
//{
//	return ((this->x == vec.x) && (this->y == vec.y));//
//}
//
//bool VECTOR2::operator>(const VECTOR2 & vec) const
//{
//	return ((this->x == vec.x) && (this->y == vec.y));//
//}


// 単項演算子
VECTOR2 & VECTOR2::operator+=(const VECTOR2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

VECTOR2 & VECTOR2::operator-=(const VECTOR2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

VECTOR2 & VECTOR2::operator*=(int k)
{
	this->x *= k;
	this->y *= k;
	return (*this);
}

VECTOR2 & VECTOR2::operator/=(int k)
{
	this->x /= k;
	this->y /= k;
	return (*this);
}

VECTOR2 VECTOR2::operator+() const
{
	return (*this);
}

VECTOR2 VECTOR2::operator-() const
{
	return VECTOR2(-this->x, -this->y);
}


// ベクトル vはベクトルという意味 ベクトル演算子
VECTOR2 operator+(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x + v;
	vec.y = u.y + v;
	return vec;
}

// VECTOR2 - int 
VECTOR2 operator-(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x - v;
	vec.y = u.y - v;
	return vec;
}

// VECTOR2+VECTOR2
VECTOR2 operator+(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	return vec;
}

// VECTOR2-VECTOR2
VECTOR2 operator-(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	return vec;
}

// VECTOR2*VECTOR2
VECTOR2 operator*(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	return vec;
}

// VECTOR2*int
VECTOR2 operator*(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x * v;
	vec.y = u.y * v;
	return vec;
}

// int*VECTOR2
VECTOR2 operator*(int v, const VECTOR2 & u)
{
	VECTOR2 vec;
	vec.x = v * u.x;
	vec.y = v * u.y;
	return vec;
}

// VECTOR2/int
VECTOR2 operator/(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x / v;
	vec.y = u.y / v;
	return vec;
}

// VECTOR2%int
VECTOR2 operator%(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x % v;
	vec.y = u.y % v;
	return vec;
}

// VECTOR2/VECTOR2
VECTOR2 operator/(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;
	return vec;
}

// VECTOR2%VECTOR2
VECTOR2 operator%(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;
	return vec;
}

