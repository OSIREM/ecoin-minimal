/*

ClassVar - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

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
	std::string f_ref_CurrentPath = "ClassVar::ClassVar";
	acClear();

	m_MxName = f_Class->m_MxName;
	m_MxName += "?ClassVar";

	m_CodeType = MuCode_ClassVar;

	//ag_StatusLive(f_ref_CurrentPath, "f_NewClass");
	std::shared_ptr<Class> f_NewClass = std::make_shared<Class>();

	f_NewClass->m_Class_Declaration = f_Class;

	for(int f_Jet = 0; f_Jet < f_Class->m_vec_Variable.size(); f_Jet++)
		{
		std::shared_ptr<Variable> f_Var = f_Class->m_vec_Variable[f_Jet];

		//ag_StatusLive(f_ref_CurrentPath, "f_NewVar");
		std::shared_ptr<Variable> f_NewVar = std::make_shared<Variable>(f_Var->m_MxName, MuCode_Var, MuVar_Full);

		f_NewVar->CloneVar(f_Var);

		f_NewVar->m_LinkClass = f_Class;

		f_NewClass->m_vec_Variable.push_back(f_NewVar);
		}

	if(f_Class->m_vec_Function.size() > 0)
		{
		std::shared_ptr<Function> f_Function = f_Class->m_vec_Function[0];

		//ag_StatusLive(f_ref_CurrentPath, "f_NewFunction");
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
			std::shared_ptr<Function> f_Func = f_Class->m_vec_Function[f_Jet];

			//ag_StatusLive(f_ref_CurrentPath, "f_NewFunction");
			std::shared_ptr<Function> f_NewFunc = std::make_shared<Function>(f_Func->m_Function);

			f_NewFunc->m_Start_CodeLine = f_Func->m_Start_CodeLine;
			f_NewFunc->m_Return_V = f_Func->m_Return_V;
			f_NewFunc->m_Return_CV = f_Func->m_Return_CV;
			f_NewFunc->m_LinkClass = f_Func->m_LinkClass;
			f_NewFunc->m_MxName = f_Func->m_MxName;

			for(int f_XY = 0; f_XY < f_Func->m_Line.size(); f_XY++)
				{
				f_NewFunc->m_Line.push_back(f_Func->m_Line[f_XY]);
				}

			for(int f_XY = 0; f_XY < f_Func->m_vec_CodeLine.size(); f_XY++)
				{
				f_NewFunc->m_vec_CodeLine.push_back(f_Func->m_vec_CodeLine[f_XY]);
				}

			for(int f_XY = 0; f_XY < f_Func->m_vec_Variable.size(); f_XY++)
				{
				f_NewFunc->m_vec_Variable.push_back(f_Func->m_vec_Variable[f_XY]);
				}

			f_NewClass->m_vec_Function.push_back(f_NewFunc);
			}
		}

	m_Class = f_NewClass;
}

ClassVar::ClassVar(ecom_base* f_AnyClassBase, std::string f_ObjectName, std::string f_TypeName) : MuType(MuTYPE_Any_Class_Variable)
{
	std::string f_ref_CurrentPath = "ClassVar::ClassVar";
	
	acClear();

	m_AnyClassBase = f_AnyClassBase;

	m_MxName = f_ObjectName;
	m_MxName += "?AnyClassVar";
	
	m_MxAnyTypeName = f_TypeName;

	m_CodeType = MuCode_ClassVar;

	//ag_StatusLive(f_ref_CurrentPath, "f_NewClass");
	std::shared_ptr<Class> f_NewClass = std::make_shared<Class>(MuClass_Custom_Any);

	//ag_StatusLive(f_ref_CurrentPath, "f_Class");
	f_NewClass->m_Class_Declaration = std::make_shared<Class>();

	  //////////////////////////
	 // [bool] map iteration
	// Create a map iterator and point to beginning of map
#ifdef ECOIN_OSI_MEMORY
#ifdef ECOIN_OSI_MEM_MUSION
	std::map<std::string, bool*>::iterator it_bool = m_AnyClassBase->m_Map_Bool.begin();

	while(it_bool != m_AnyClassBase->m_Map_Bool.end())
		{
		// Accessing KEY from element pointed by it_bool.
		std::string f_BoolName = it_bool->first;
		bool* f_BoolRefPtr = it_bool->second;

		ag_StatusLive(f_ref_CurrentPath, "f_NewVar");
		std::shared_ptr<Variable> f_NewVar = std::make_shared_reflect<Variable>(f_BoolName, MuCode_Var, MuVar_Full);

		f_NewVar->m_LinkClass = f_NewClass->m_Class_Declaration;

		f_NewVar->m_Map_Bool.emplace(f_BoolName, f_BoolRefPtr);

		f_NewClass->m_vec_Variable.push_back(f_NewVar);
		f_NewClass->m_Class_Declaration->m_vec_Variable.push_back(f_NewVar);

		it_bool++;
		}

	  //////////////////////////
	 // [Float] map iteration
	// Create a map iterator and point to beginning of map
	std::map<std::string, float*>::iterator it_float = m_AnyClassBase->m_Map_Float.begin();

	while(it_float != m_AnyClassBase->m_Map_Float.end())
		{
		// Accessing KEY from element pointed by it_float.
		std::string f_FloatName = it_float->first;
		float* f_FloatRefPtr = it_float->second;

		ag_StatusLive(f_ref_CurrentPath, "f_NewVar");
		std::shared_ptr<Variable> f_NewVar = std::make_shared_reflect<Variable>(f_FloatName, MuCode_Var, MuVar_Full);

		f_NewVar->m_LinkClass = f_NewClass->m_Class_Declaration;

		f_NewVar->m_Map_Float.emplace(f_FloatName, f_FloatRefPtr);

		f_NewClass->m_vec_Variable.push_back(f_NewVar);
		f_NewClass->m_Class_Declaration->m_vec_Variable.push_back(f_NewVar);

		it_float++;
		}

	  //////////////////////////
	 // [Int] map iteration
	// Create a map iterator and point to beginning of map
	std::map<std::string, int*>::iterator it_int = m_AnyClassBase->m_Map_Int.begin();

	while(it_int != m_AnyClassBase->m_Map_Int.end())
		{
		// Accessing KEY from element pointed by it_int.
		std::string f_IntName = it_int->first;
		int* f_IntRefPtr = it_int->second;

		ag_StatusLive(f_ref_CurrentPath, "f_NewVar");
		std::shared_ptr<Variable> f_NewVar = std::make_shared_reflect<Variable>(f_IntName, MuCode_Var, MuVar_Full);

		f_NewVar->m_LinkClass = f_NewClass->m_Class_Declaration;

		f_NewVar->m_Map_Int.emplace(f_IntName, f_IntRefPtr);

		f_NewClass->m_vec_Variable.push_back(f_NewVar);
		f_NewClass->m_Class_Declaration->m_vec_Variable.push_back(f_NewVar);

		it_int++;
		}

	  //////////////////////////
	 // [String] map iteration
	// Create a map iterator and point to beginning of map
	std::map<std::string, std::string*>::iterator it_string = m_AnyClassBase->m_Map_String.begin();

	while(it_string != m_AnyClassBase->m_Map_String.end())
		{
		// Accessing KEY from element pointed by it_string.
		std::string f_StringName = it_string->first;
		std::string* f_StringRefPtr = it_string->second;

		ag_StatusLive(f_ref_CurrentPath, "f_NewVar");
		std::shared_ptr<Variable> f_NewVar = std::make_shared_reflect<Variable>(f_StringName, MuCode_Var, MuVar_Full);

		f_NewVar->m_LinkClass = f_NewClass->m_Class_Declaration;

		f_NewVar->m_Map_String.emplace(f_StringName, f_StringRefPtr);

		f_NewClass->m_vec_Variable.push_back(f_NewVar);
		f_NewClass->m_Class_Declaration->m_vec_Variable.push_back(f_NewVar);

		it_string++;
		}

#if 0
	  ////////////////////////////////////////////////////////////
	 // [boost::any] map iteration
	// Create a map iterator and point to beginning of map
	std::map<std::string, boost::any>::iterator it_var = m_AnyClassBase->m_Map_Var.begin();

	while(it_var != m_AnyClassBase->m_Map_Var.end())
		{
		// Accessing KEY from element pointed by it_var.
		std::string f_AnyVarName = it_var->first;
		const boost::any* f_AnyVarRefPtr = it_var->second;

		ag_StatusLive(f_ref_CurrentPath, "f_NewVar");
		std::shared_ptr<Variable> f_NewVar = std::make_shared_reflect<Variable>(f_Var->m_MxName, MuCode_Var, MuVar_Full);

		f_NewVar->m_LinkClass = f_NewClass->m_Class_Declaration;

		f_NewVar->m_Map_Var.emplace(f_AnyVarName, f_StringRefPtr);

		f_NewClass->m_vec_Variable.push_back(f_NewVar);
		f_NewClass->m_Class_Declaration->m_vec_Variable.push_back(f_NewVar);
		}
#endif

	  ////////////////////////////////////////////////////////////
	 // [Function] map iteration
	// Create a map iterator and point to beginning of map
	std::map<std::string, ecom_base::ControllerMethod_void>::iterator it_func = m_AnyClassBase->m_Map_Function.begin();

	while(it_func != m_AnyClassBase->m_Map_Function.end())
		{
		// Accessing KEY from element pointed by it_func.
		std::string f_FunctionName = it_func->first;
		const ecom_base::ControllerMethod_void f_RefPtr = it_func->second;

		ag_StatusLive(f_ref_CurrentPath, "f_NewVar");
		std::shared_ptr<Variable> f_NewVar = std::make_shared_reflect<Variable>(f_FunctionName, MuCode_Var, MuVar_Full);

		f_NewVar->m_LinkClass = f_NewClass->m_Class_Declaration;

		f_NewVar->m_Map_Function.emplace(f_FunctionName, f_RefPtr);

		f_NewClass->m_vec_Variable.push_back(f_NewVar);
		f_NewClass->m_Class_Declaration->m_vec_Variable.push_back(f_NewVar);

		it_func++;
		}
#endif
#endif

	m_Class = f_NewClass;
}

void ClassVar::acCall_Constructor(void)
{
	if(m_Class != nullptr)
		{
		m_Class->m_Constructor_Function->acExecute();
		}
	else
		{
		if(m_AnyClassBase != nullptr)
			{
			//m_AnyClass->m_Constructor_Function->acExecute();
			}
		}
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
		return ECN_FLOAT;
		}
	else if(f_String.compare("float2") == 0 ||
			f_String.compare("Float2") == 0)
		{
		return ECN_FLOAT;
		}
	else if(f_String.compare("float3") == 0 ||
			f_String.compare("Float3") == 0)
		{
		return ECN_FLOAT;
		}
	else if(f_String.compare("float4") == 0 ||
			f_String.compare("Float4") == 0)
		{
		return ECN_FLOAT;
		}
	else if(f_String.compare("int") == 0 ||
	   f_String.compare("Int") == 0 ||
	   f_String.compare("int1") == 0 ||
	   f_String.compare("Int1") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("int2") == 0 ||
			f_String.compare("Int2") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("int3") == 0 ||
			f_String.compare("Int3") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("int4") == 0 ||
			f_String.compare("Int4") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("uint") == 0 ||
			f_String.compare("uInt") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("bool") == 0 ||
			f_String.compare("Bool") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("char") == 0 ||
			f_String.compare("Char") == 0)
		{
		return ECN_STRING;
		}
	else if(f_String.compare("string") == 0 ||
			f_String.compare("String") == 0)
		{
		return ECN_STRING;
		}

	return 0;
	}
	
int agFind_CurrentSpec_AnyClassVarType(std::string f_String)
	{
	if(f_String.compare("float") == 0 ||
	   f_String.compare("Float") == 0 ||
	   f_String.compare("float1") == 0 ||
	   f_String.compare("Float1") == 0)
		{
		return ECN_FLOAT;
		}
	else if(f_String.compare("float2") == 0 ||
			f_String.compare("Float2") == 0)
		{
		return ECN_FLOAT;
		}
	else if(f_String.compare("float3") == 0 ||
			f_String.compare("Float3") == 0)
		{
		return ECN_FLOAT;
		}
	else if(f_String.compare("float4") == 0 ||
			f_String.compare("Float4") == 0)
		{
		return ECN_FLOAT;
		}
	else if(f_String.compare("int") == 0 ||
	   f_String.compare("Int") == 0 ||
	   f_String.compare("int1") == 0 ||
	   f_String.compare("Int1") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("int2") == 0 ||
			f_String.compare("Int2") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("int3") == 0 ||
			f_String.compare("Int3") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("int4") == 0 ||
			f_String.compare("Int4") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("uint") == 0 ||
			f_String.compare("uInt") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("bool") == 0 ||
			f_String.compare("Bool") == 0)
		{
		return ECN_INT;
		}
	else if(f_String.compare("char") == 0 ||
			f_String.compare("Char") == 0)
		{
		return ECN_STRING;
		}
	else if(f_String.compare("string") == 0 ||
			f_String.compare("String") == 0)
		{
		return ECN_STRING;
		}

	return 0;
	}

};