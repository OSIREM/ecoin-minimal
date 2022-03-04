/*

Function - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <math.h>

#include "Code.h"
#include "CodeLine.h"
#include "MuType.h"
#include "Operator.h"
#include "System.h"
#include "Variable.h"

namespace ecoin
{

	enum
	{
		MuFunc_Default,
		MuFunc_Custom,
		MuFunc_Frame,
		MuFunc_RandFloat,
		MuFunc_RandInt,
		MuFunc_Sin,
		MuFunc_Cos,
		MuFunc_Tan,
		MuFunc_Log,
		MuFunc_InvSin,
		MuFunc_InvCos,
		MuFunc_InvTan,
		MuFunc_Sqr,
		MuFunc_Sqrt,
		MuFunc_ArcTan2,
		MuFunc_Gate_NOT,
		MuFunc_Gate_AND,
		MuFunc_Gate_OR,
		MuFunc_Gate_XOR,
		MuFunc_Gate_NAND,
		MuFunc_Gate_NOR,
		MuFunc_Gate_XNOR,
		MuSetGLOBAL_,
	};

	class Function : MuType
		{
		public:
			Function() : MuType(MuTYPE_Function)
				{
				m_Function = 0;
				m_Start_CodeLine = nullptr;
				m_vec_CodeLine.clear();
				m_vec_Variable.clear();
				m_Return_V = nullptr;
				m_Return_CV = nullptr;
				m_Line.clear();
				m_MxName.clear();
				m_LinkClass = nullptr;
				};

			Function(uint f_Function) : MuType(MuTYPE_Function), m_Function(f_Function)
				{
				m_Function = f_Function;
				m_Start_CodeLine = nullptr;
				m_vec_CodeLine.clear();
				m_vec_Variable.clear();
				m_Return_V = nullptr;
				m_Return_CV = nullptr;
				m_Line.clear();
				m_MxName.clear();
				m_LinkClass = nullptr;
				};

			uint acPrep_addVariable(std::shared_ptr<Variable> f_Var);

			std::shared_ptr<Variable> acExecute(void);

			std::shared_ptr<Variable> acFind_Var(std::string f_VarName);
			std::shared_ptr<ClassVar> acFind_ClassVar(std::string f_VarName);

			int m_Function;

			std::shared_ptr<CodeLine> m_Start_CodeLine;
			std::vector<std::shared_ptr<CodeLine>> m_vec_CodeLine;
			std::vector<std::shared_ptr<Variable>> m_vec_Variable;
			std::vector<std::shared_ptr<ClassVar>> m_vec_ClassVar;
			std::shared_ptr<Variable> m_Return_V;
			std::shared_ptr<ClassVar> m_Return_CV;
			std::shared_ptr<Class> m_LinkClass;
			std::vector<std::string> m_Line;
			std::string m_MxName;
		};

	extern int agFind_FunctionType(std::string f_String);

	extern std::shared_ptr<Variable> ag_Find_Var(std::string f_String);
	extern std::shared_ptr<ClassVar> ag_Find_ClassVar(std::string f_VarName);
};


#endif