/*

ClassVar - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CLASSVAR_H
#define CLASSVAR_H

#include <vector>
#include <math.h>

#include "MuType.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>

#include <boost/any.hpp>

#define ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT 0
#define ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT 1
#define ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING 2

namespace ecoin
{
    class Class;

	enum
	{
		MuClassVar_Start,
		MuClassVar_ClassVar,
		MuClassVar_Full,
		MuClassVar_Total
	};

	class ClassVar : MuType
		{
		public:
			ClassVar() : MuType(MuTYPE_Class_Variable)
                { acClear(); };
			ClassVar(std::shared_ptr<Class> f_Class);
			~ClassVar()
				{ acClear(); };

            void acClear(void)
                {
                m_MxName.clear();
				m_ClassVar = MuClassVar_ClassVar;
				m_PrecType = 0;
				m_CodeType = 0;
                }

			void acCall_Constructor(void);

			std::shared_ptr<ecoin::Class> m_Class;

			uint m_PrecType;
			uint m_CodeType;
			uint m_ClassVar;

			std::string m_MxName;
		};

	extern int agFind_VarType(std::string f_String);

    extern int agFind_CurrentSpec_VarType(std::string f_String);

	extern int agFind_ClassVarType(std::string f_String);
}


#endif