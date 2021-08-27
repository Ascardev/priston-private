#pragma once

template <class T>
class CPoint
{
public:
	T x;
	T y;
	T z;
	CPoint()
	{
		x = T();
		y = T();
		z = T();
	}
	CPoint(T _x, T _y, T _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	T GetX() { return x; }
	T GetY() { return y; }
	T GetZ() { return z; }
};