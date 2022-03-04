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
			Function() : MuType(MuTYPE_Function) {};
			Function(uint f_Function) : MuType(MuTYPE_Function),
				m_Function(f_Function) { m_Function = f_Function; };

			uint acPrep_addVariable(std::shared_ptr<Variable> f_Var);

			std::shared_ptr<Variable> acExecute(void);

			std::vector<std::shared_ptr<CodeLine>> m_vec_CodeLine;
			std::vector<std::shared_ptr<Variable>> m_vec_Variable;

			std::vector<std::string> m_Line;

			std::shared_ptr<Variable> m_Return;

			int m_Function;

			std::string m_MxName;

			std::shared_ptr<CodeLine> m_Start_CodeLine;
		};

	extern int agFind_FunctionType(std::string f_String);

};


#endif