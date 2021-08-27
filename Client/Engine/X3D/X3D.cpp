#include "StdAfx.h"
#include "X3D.h"

namespace X3D
{
	float easeInOutCircf(float t, float b, float c, float d)
	{
		return (t /= d / 2) < 1 ? -c / 2 * (sqrt(1 - t * t) - 1) + b : c / 2 * (sqrt(1 - t * (t -= 2)) + 1) + b;
	}
}