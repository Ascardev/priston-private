#pragma once

namespace TERRAIN
{
	class Element
	{
	public:
		Element();
		virtual ~Element();

		void Render(Point3D sCameraPosition, Point3D sCameraAngle);
	};
}
