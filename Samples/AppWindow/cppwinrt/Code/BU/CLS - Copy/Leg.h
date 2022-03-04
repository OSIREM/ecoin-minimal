/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef LEG_H
#define LEG_H

#include <vector>
#include <math.h>

#include "Corner.h"

namespace ecoin
{

	enum CLS_LegType
	{
		CLS_Leg
	};

	class classLeg// : classElement
	{
	public:
		classLeg(shared_ptr<classElement> f_Element) {};// : classElement(f_Element) {};
		~classLeg() {};

		float m_Width;
		float m_Height;
		float m_Length;

		BiVector m_Position;
		matrix m_Orientation;
	};

};

#endif