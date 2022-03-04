/*

ClassVar - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

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

#include "Variable.h"

namespace ecoin
{
    class Class;

	enum
	{
		MuClassVar_Start,
		MuClassVar_ClassVar,
		MuClassVar_AnyClass,
		MuClassVar_Full,
		MuClassVar_Total
	};

	class ClassVar : public MuType
		{
		public:
			ClassVar() : MuType(MuTYPE_Class_Variable)
                { acClear(); };
			ClassVar(std::shared_ptr<Class> f_Class);
			ClassVar(ecom_base* f_AnyClassBase, std::string f_ObjectName, std::string f_TypeName);
			~ClassVar()
				{ acClear(); };

            void acClear(void)
                {
                m_MxName.clear();
				m_ClassVar = MuClassVar_ClassVar;
				m_PrecType = 0;
				m_CodeType = 0;
				m_Class = nullptr;
				m_AnyClassBase = nullptr;
                }

			void acCall_Constructor(void);

			std::shared_ptr<ecoin::Class> m_Class;
			ecom_base* m_AnyClassBase;

			uint m_PrecType;
			uint m_CodeType;
			uint m_ClassVar;

			std::string m_MxName;
			std::string m_MxAnyTypeName;
		};

	extern int agFind_VarType(std::string f_String);

    extern int agFind_CurrentSpec_VarType(std::string f_String);
	
	extern int agFind_CurrentSpec_AnyClassVarType(std::string f_String);

	extern int agFind_ClassVarType(std::string f_String);
}


#endif