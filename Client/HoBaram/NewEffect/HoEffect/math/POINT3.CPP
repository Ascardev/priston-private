#include "StdAfx.h"
#include "point3.h"
#include "point4.h"

const point3 point3::Zero(0.f, 0.f, 0.f);

const point3 point3::i(1.f, 0.f, 0.f);
const point3 point3::j(0.f, 1.f, 0.f);
const point3 point3::k(0.f, 0.f, 1.f);

point3::point3(const point4& in)
{
	if (in.w != 1.f)
	{
		float inv = 1 / in.w;
		x = in.x * inv;
		y = in.y * inv;
		z = in.z * inv;
	}
	else
	{
		x = in.x;
		y = in.y;
		z = in.z;
	}
}