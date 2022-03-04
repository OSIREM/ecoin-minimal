/*

CodeLine - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CODELINE_H
#define CODELINE_H

#include <vector>
#include <math.h>

#include "MuType.h"
#include "Code.h"
#include "Variable.h"
#include "Operator.h"
#include "Condition.h"
#include "System.h"

namespace ecoin
{

	enum MuLine
	{
		MuLine_Init_Var, //1 V = 1
		MuLine_Init_ClassVar, //1-3 CV = 1 2
		MuLine_Assign, //2 V = V
		MuLine_Assign_Opr, //3 or more... V += V
		MuLine_Condition_Ajax, //3 V == V
		MuLine_For_Loop, //4 V = 1 if(V < 1) V++
		MuLine_Function, //1-4 V = fcn(V, V)
		MuLine_Function_Frame, //1-3 fundef(V, V)
		MuLine_Function_Custom, //1-3 fundef(V, V)
		MuLine_Function_Start, //1-3 fundef(V, V)
		MuLine_Function_Return, //1-2 return(V)
		MuLine_Template, //2 or more... template(V)
		MuLine_ClassDef, //1 clsdef
		MuLine_MAX
	};

	class ClassVar;
	class Function;

	class CodeLine : public MuType
	{
	public:
		CodeLine() { acClear(); };
		CodeLine(std::string f_Line, uint f_CHK, System* f_System);
		~CodeLine();

		void acClear(void)
			{
			m_vec_Code.clear();
			m_vec_Variable.clear();
			m_vec_Operator.clear();
			m_Result_V = nullptr;
			m_Result_CV = nullptr;
			m_CodeString.clear();
			m_Execute = true;
			m_Returning = false;
			}

		int acSearch_CodeType(uint f_TYPE);

		std::shared_ptr<ClassVar> ac_Execute(std::shared_ptr<Function> f_Function);
		std::string ac_Print(void);

		void ac_Variable_Align(void);

		std::vector<std::shared_ptr<Code>> m_vec_Code;
		std::vector<std::shared_ptr<Variable>> m_vec_Variable;
		std::vector<std::shared_ptr<Operator>> m_vec_Operator;

		std::shared_ptr<Variable> m_Result_V;
		std::shared_ptr<ClassVar> m_Result_CV;

		System* m_System;

		int m_ConditionCountID;

		std::string m_CodeString;

		bool m_Returning;

		uint m_CodeLine;
		uint m_ChkSRT;
		uint m_ChkEND;
		uint m_END;
		uint m_Chk;

		bool m_Execute;
	};

extern std::shared_ptr<ClassVar> g_BaseNode;
extern std::vector<std::shared_ptr<ClassVar>> g_vec_BaseNode;

};

#endif