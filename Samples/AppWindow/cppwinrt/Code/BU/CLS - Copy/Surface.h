/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef SURFACE_H
#define SURFACE_H

#include <vector>
#include <math.h>

#include "Corner.h"

namespace ecoin
{

	enum CLS_SurfaceType
	{
		CLS_Surface
	};

	class classSurface// : classElement
	{
	public:
		classSurface(shared_ptr<classElement> f_Element) {};// : classElement(f_Element) {};
		~classSurface() {};

		BiPlane m_PropPlane;
		BiVector m_Position;
		matrix m_Orientation;
	};

};

#endif