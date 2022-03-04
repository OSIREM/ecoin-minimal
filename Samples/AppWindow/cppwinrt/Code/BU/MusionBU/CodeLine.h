/*

CodeLine - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

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
		MuLine_Init_Var,
		MuLine_Assign,
		MuLine_Assign_Opr,
		MuLine_Condition_Ajax,
		MuLine_For_Loop,
		MuLine_Function,
		MuLine_Function_Frame,
		MuLine_Function_Custom,
		MuLine_Function_Start,
		MuLine_MAX
	};

	class CodeLine
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
			m_Result = nullptr;
			m_CodeString.clear();
			m_Execute = true;
			}

		int acSearch_CodeType(uint f_TYPE);

		bool ac_Execute(void);
		std::string ac_Print(void);

		void ac_Variable_Align(void);

		std::vector<std::shared_ptr<Code>> m_vec_Code;
		std::vector<std::shared_ptr<Variable>> m_vec_Variable;
		std::vector<std::shared_ptr<Operator>> m_vec_Operator;

		std::shared_ptr<Variable> m_Result;

		System* m_System;

		int m_ConditionCountID;

		std::string m_CodeString;

		uint m_CodeLine;
		uint m_ChkSRT;
		uint m_ChkEND;
		uint m_END;
		uint m_Chk;

		bool m_Execute;
	};

};

#endif