/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CODE_H
#define CODE_H

#include <vector>
#include <math.h>

#include "MuType.h"
#include "Variable.h"
#include "Condition.h"

namespace ecoin
{

	enum MuCode
	{
		MuCode_Var,
		MuCode_ClassVar,
		MuCode_System,
		MuCode_Constant,
		MuCode_Operator,
		MuCode_Condition,
		MuCode_For_Loop,
		MuCode_Function,
		MuCode_FunctionStart,
		MuCode_Parameter,
		MuCode_ClassDef,
		MuCode_Return,
		MuCode_Template,
		MuCode_Total,
		MuCode_Override
	};

	enum
	{
		MuNameCall_Type_VarVar,
		MuNameCall_Type_VarIndexInt,
		MuNameCall_Type_MemberVar,
		MuNameCall_Type_MemberIndexInt,
		MuNameCall_Type_ClassVar,
		MuNameCall_Type_Total
	};

	class Function;
	class Class;

	class Code : MuType
	{
	public:
		Code() : MuType(MuTYPE_Code) { acClear(); };
		Code(std::string f_Line, uint f_CHK, uint f_Index, uint f_CodeType = MuCode_Var, uint f_VarType = MuVar_Full);
		~Code()
			{ acClear(); };

		void acClear(void)
			{
			m_vec_Type.clear();
			m_vec_VarType.clear();
			m_Class = nullptr;
			m_MxName.clear();
			m_MxVar = nullptr;
			m_vec_Type.clear();
			m_vec_VarType.clear();
			m_Code = 0;
			m_END = 0;
			m_Chk = 0;
			m_Name.clear();
			m_Number.clear();
			m_Type.clear();
			m_Param.clear();
			m_Condition.clear();
			m_FunctionLink = nullptr;
			m_vec_NameCall.clear();
			m_vec_NameCallType.clear();
			m_ContractID = -1;
			}

		uint acName_MAX(void);
		uint acName_END(void);
		uint acNumber_MAX(void);
		uint acNumber_END(void);
		uint acType_MAX(void);
		uint acType_END(void);
		uint acParam_MAX(void);
		uint acParam_END(void);
		uint acDecide_MAX(void);
		uint acDecide_END(void);

		void acPrepare_CallNames(void);

		std::shared_ptr<Variable> acCodeCall_Var(int f_Index, int f_MaxIndex, std::shared_ptr<Function> f_Function, int f_FindIndexInt = 0);

		uint m_Code;
		uint m_END;
		uint m_Chk;

		int m_VarType;

		std::string m_MxName;
		std::shared_ptr<Variable> m_MxVar;

		//assigned class
		std::shared_ptr<Class> m_Class;

		//native vector
		std::vector<std::string> m_vec_Type;
		std::vector<int> m_vec_VarType;

		uint m_Index;

		int m_ContractID;

		char m_Code_DigitA;
		char m_Code_DigitB;
		char m_Code_DigitC;

		std::vector<std::shared_ptr<Code>> m_Name;
		std::vector<std::shared_ptr<Code>> m_Number;
		std::vector<std::shared_ptr<Code>> m_Type;
		std::vector<std::shared_ptr<Code>> m_Param;

		std::vector<std::shared_ptr<Condition>> m_Condition;

		std::shared_ptr<Function> m_FunctionLink;

		std::vector<std::string> m_vec_NameCall;
		std::vector<int> m_vec_NameCallType;
	};

};

#endif