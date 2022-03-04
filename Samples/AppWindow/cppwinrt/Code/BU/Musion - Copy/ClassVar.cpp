/*

ClassVar - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Code.h"
#include "CodeLine.h"
#include "ClassVar.h"

using namespace ecoin;

namespace ecoin
{

ClassVar::ClassVar(std::shared_ptr<Class> f_Class) : MuType(MuTYPE_Class_Variable)
{
	acClear();

	m_MxName = f_Class->m_MxName;
	m_MxName += "?ClassVar";

	m_CodeType = MuCode_ClassVar;

	std::shared_ptr<Class> f_NewClass = std::make_shared<Class>();

	f_NewClass->m_Class_Declaration = f_Class;

	for(int f_Jet = 0; f_Jet < f_Class->m_vec_Variable.size(); f_Jet++)
		{
		std::shared_ptr<Variable> f_Var = f_Class->m_vec_Variable[f_Jet];
		std::shared_ptr<Variable> f_NewVar = std::make_shared<Variable>(f_Var->m_MxName, f_Var->m_Variable, MuVar_Full);

		f_NewVar->CloneVar(f_Var);

		f_NewVar->m_LinkClass = f_Class;

		f_NewClass->m_vec_Variable.push_back(f_NewVar);
		}

	if(f_Class->m_vec_Function.size() > 0)
		{
		std::shared_ptr<Function> f_Function = f_Class->m_vec_Function[0];
		std::shared_ptr<Function> f_NewFunction = std::make_shared<Function>(f_Function->m_Function);

		f_NewFunction->m_Start_CodeLine = f_Function->m_Start_CodeLine;
		f_NewFunction->m_Return_V = f_Function->m_Return_V;
		f_NewFunction->m_Return_CV = f_Function->m_Return_CV;
		f_NewFunction->m_LinkClass = f_Function->m_LinkClass;
		f_NewFunction->m_MxName = f_Function->m_MxName;

		for(int f_XY = 0; f_XY < f_Function->m_Line.size(); f_XY++)
			{
			f_NewFunction->m_Line.push_back(f_Function->m_Line[f_XY]);
			}

		for(int f_XY = 0; f_XY < f_Function->m_vec_CodeLine.size(); f_XY++)
			{
			f_NewFunction->m_vec_CodeLine.push_back(f_Function->m_vec_CodeLine[f_XY]);
			}

		for(int f_XY = 0; f_XY < f_Function->m_vec_Variable.size(); f_XY++)
			{
			f_NewFunction->m_vec_Variable.push_back(f_Function->m_vec_Variable[f_XY]);
			}

		f_NewClass->m_Constructor_Function = f_NewFunction;

		for(int f_Jet = 0; f_Jet < f_Class->m_vec_Function.size(); f_Jet++)
			{
			std::shared_ptr<Function> f_Function = f_Class->m_vec_Function[f_Jet];
			std::shared_ptr<Function> f_NewFunction = std::make_shared<Function>(f_Function->m_Function);

			f_NewFunction->m_Start_CodeLine = f_Function->m_Start_CodeLine;
			f_NewFunction->m_Return_V = f_Function->m_Return_V;
			f_NewFunction->m_Return_CV = f_Function->m_Return_CV;
			f_NewFunction->m_LinkClass = f_Function->m_LinkClass;
			f_NewFunction->m_MxName = f_Function->m_MxName;

			for(int f_XY = 0; f_XY < f_Function->m_Line.size(); f_XY++)
				{
				f_NewFunction->m_Line.push_back(f_Function->m_Line[f_XY]);
				}

			for(int f_XY = 0; f_XY < f_Function->m_vec_CodeLine.size(); f_XY++)
				{
				f_NewFunction->m_vec_CodeLine.push_back(f_Function->m_vec_CodeLine[f_XY]);
				}

			for(int f_XY = 0; f_XY < f_Function->m_vec_Variable.size(); f_XY++)
				{
				f_NewFunction->m_vec_Variable.push_back(f_Function->m_vec_Variable[f_XY]);
				}

			f_NewClass->m_vec_Function.push_back(f_NewFunction);
			}
		}

	m_Class = f_NewClass;
}

void ClassVar::acCall_Constructor(void)
{
	m_Class->m_Constructor_Function->acExecute();
}

int agFind_ClassVarType(std::string f_String)
	{
	if(f_String.compare("vector") == 0 ||
	   f_String.compare("Float") == 0 ||
	   f_String.compare("float1") == 0 ||
	   f_String.compare("Float1") == 0)
		{
		return MuVar_Float;
		}
	else if(f_String.compare("float2") == 0 ||
			f_String.compare("Float2") == 0)
		{
		return MuVar_Float2;
		}
	else if(f_String.compare("float3") == 0 ||
			f_String.compare("Float3") == 0)
		{
		return MuVar_Float3;
		}
	else if(f_String.compare("float4") == 0 ||
			f_String.compare("Float4") == 0)
		{
		return MuVar_Float4;
		}
	else if(f_String.compare("int") == 0 ||
	   f_String.compare("Int") == 0 ||
	   f_String.compare("int1") == 0 ||
	   f_String.compare("Int1") == 0)
		{
		return MuVar_Int;
		}
	else if(f_String.compare("int2") == 0 ||
			f_String.compare("Int2") == 0)
		{
		return MuVar_Int2;
		}
	else if(f_String.compare("int3") == 0 ||
			f_String.compare("Int3") == 0)
		{
		return MuVar_Int3;
		}
	else if(f_String.compare("int4") == 0 ||
			f_String.compare("Int4") == 0)
		{
		return MuVar_Int4;
		}
	else if(f_String.compare("uint") == 0 ||
			f_String.compare("uInt") == 0)
		{
		return MuVar_uInt;
		}
	else if(f_String.compare("bool") == 0 ||
			f_String.compare("Bool") == 0)
		{
		return MuVar_Bool;
		}
	else if(f_String.compare("char") == 0 ||
			f_String.compare("Char") == 0)
		{
		return MuVar_Char;
		}
	else if(f_String.compare("string") == 0 ||
			f_String.compare("String") == 0)
		{
		return MuVar_String;
		}

	return 0;
	}

int agFind_CurrentSpec_ClassVarType(std::string f_String)
	{
	if(f_String.compare("float") == 0 ||
	   f_String.compare("Float") == 0 ||
	   f_String.compare("float1") == 0 ||
	   f_String.compare("Float1") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT;
		}
	else if(f_String.compare("float2") == 0 ||
			f_String.compare("Float2") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT;
		}
	else if(f_String.compare("float3") == 0 ||
			f_String.compare("Float3") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT;
		}
	else if(f_String.compare("float4") == 0 ||
			f_String.compare("Float4") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT;
		}
	else if(f_String.compare("int") == 0 ||
	   f_String.compare("Int") == 0 ||
	   f_String.compare("int1") == 0 ||
	   f_String.compare("Int1") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("int2") == 0 ||
			f_String.compare("Int2") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("int3") == 0 ||
			f_String.compare("Int3") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("int4") == 0 ||
			f_String.compare("Int4") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("uint") == 0 ||
			f_String.compare("uInt") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("bool") == 0 ||
			f_String.compare("Bool") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("char") == 0 ||
			f_String.compare("Char") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING;
		}
	else if(f_String.compare("string") == 0 ||
			f_String.compare("String") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING;
		}

	return 0;
	}

};