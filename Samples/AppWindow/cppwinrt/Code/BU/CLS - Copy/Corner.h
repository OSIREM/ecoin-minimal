/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CORNER_H
#define CORNER_H

#include <vector>
#include <math.h>

#include "Include/Cube.h"
#include "Element.h"

using namespace Cube;

namespace ecoin
{

	enum CLS_CornerType
	{
		CLS_Corner
	};

	class classCorner// : classElement
	{
	public:
		classCorner(shared_ptr<classElement> f_Element);// : classElement(f_Element) {};
		classCorner() {};// : classElement() {};
		~classCorner() {};
		
		void acSpecify(BiVector f_Corner, BiVector f_X, BiVector f_Y, BiVector f_Z)
			{
			m_Corner = f_Corner;
			m_X = f_X;
			m_Y = f_Y;
			m_Z = f_Z;
			}

		bool acClassify(void);

		BiVector m_Corner;
		BiVector m_X;
		BiVector m_Y;
		BiVector m_Z;
	};

	

};

#endif