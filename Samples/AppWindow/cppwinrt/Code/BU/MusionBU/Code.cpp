/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Code.h"
#include "Operator.h"
#include "Function.h"

using namespace ecoin;

namespace ecoin
{

Code::Code(std::string f_Line, uint f_CHK, uint f_Index, uint f_CodeType, uint f_VarType) : MuType(MuTYPE_Code), m_Index(f_Index)
{
	m_Code = f_CodeType;
	m_VarType = f_VarType;

	m_ContractID = -1;

	std::string f_StrCode = acBufreadCodeString(f_Line, f_CHK);

	const char f_Code_DigitA = f_StrCode.at(f_StrCode.length() - 2);
	const char f_Code_DigitB = f_StrCode.at(f_StrCode.length() - 1);

	m_Code_DigitA = f_Code_DigitA;
	m_Code_DigitB = f_Code_DigitB;

	m_Chk = f_CHK + f_StrCode.length();

	f_StrCode.pop_back();
	f_StrCode.pop_back();

	m_MxName = f_StrCode;

	printf("Code|DigitA %c|DigitB %c|StrCode %s\n", f_Code_DigitA, f_Code_DigitB, f_StrCode.c_str());

	if(f_Code_DigitA == '%')
		{
		if(f_Code_DigitB == '#')
			{
			m_END = false;
			}
		else
			{
			if(f_StrCode.compare("Var") == 0)
				{
				m_Code = MuCode_Var;

				m_MxVar = std::make_shared<Variable>("FreshVar", MuCode_Var);

				m_Type.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
				m_Chk = acDecide_MAX();

				m_VarType = m_Type[0]->m_VarType;

				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));

				m_Chk = acDecide_MAX();

				if(m_Chk < (f_Line.length() - 7))
					{
					std::shared_ptr<Code> f_Code = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var, m_VarType);
					f_Code->m_MxVar->m_MxName = m_Name[0]->m_MxName;

					m_Number.push_back(f_Code);

					m_Chk = acDecide_MAX();
					}
				}
			else if((f_StrCode.compare("Fcn") == 0) ||
					(f_StrCode.compare("Func") == 0) ||
					(f_StrCode.compare("Call") == 0) ||
				    (f_StrCode.compare("FunctionCall") == 0))
				{
				m_Code = MuCode_Function;

				m_MxVar = std::make_shared<Variable>("ReturnVar", MuCode_Var);

				m_Type.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
				m_Chk = acDecide_MAX();

				m_VarType = m_Type[0]->m_VarType;

				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
				m_Chk = acDecide_MAX();

				if(m_Chk < (f_Line.length() - 7))
					{
					m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
					m_Chk = acDecide_MAX();
					}
				
				if (m_Chk < (f_Line.length() - 7))
					{
					m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
					m_Chk = acDecide_MAX();
					}
				}
			else if((f_StrCode.compare("Fus") == 0) ||
					(f_StrCode.compare("Def") == 0) ||
					(f_StrCode.compare("FuncDef") == 0) ||
					(f_StrCode.compare("Function") == 0) ||
					(f_StrCode.compare("FuncStart") == 0) ||
				    (f_StrCode.compare("FunctionStart") == 0))
				{
				m_Code = MuCode_FunctionStart;
				m_MxVar = std::make_shared<Variable>("ReturnVar", MuCode_Var);

				m_Type.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
				m_Chk = acDecide_MAX();

				m_VarType = m_Type[0]->m_VarType;

				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Function));
				m_Chk = acDecide_MAX();

				if(m_Chk < (f_Line.length() - 7))
					{
					m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
					m_Chk = acDecide_MAX();
					}
				
				if(m_Chk < (f_Line.length() - 7))
					{
					m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
					m_Chk = acDecide_MAX();
					}
				//FIXME::EVENTUALLY LOOP HERE to select amount of parameters
				}
			else if(f_StrCode.compare("Sys") == 0)
				{
				m_Code = MuCode_System;
				m_MxVar = std::make_shared<Variable>("FreshVar", MuCode_Var);

				m_Type.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
				m_Chk = acDecide_MAX();

				m_VarType = m_Type[0]->m_VarType;

				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_System));
				m_Chk = acDecide_MAX();

				if(m_Chk < (f_Line.length() - 7))
					{
					std::shared_ptr<Code> f_Code = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var, m_VarType);
					f_Code->m_MxVar->m_MxName = m_Name[0]->m_MxName;

					m_Number.push_back(f_Code);

					m_Chk = acDecide_MAX();
					}
				}
			else if(f_StrCode.compare("Con") == 0)
				{
				m_Code = MuCode_Constant;
				m_MxVar = std::make_shared<Variable>("FreshVar", MuCode_Var);

				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Constant));
				m_Chk = acDecide_MAX();

				std::shared_ptr<Code> f_Code = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Constant);
				f_Code->m_MxVar = std::make_shared<Variable>(m_Name[0]->m_MxName, MuCode_Constant);
				f_Code->m_MxVar->m_MxName = m_Name[0]->m_MxName;

				m_Number.push_back(f_Code);
				m_Chk = acDecide_MAX();
				}
			else if(f_StrCode.compare("Opr") == 0)
				{
				m_Code = MuCode_Operator;

				std::shared_ptr<Code> f_Type = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Operator);
				m_Type.push_back(f_Type);
				m_VarType = f_Type->m_VarType;

				m_Chk = acDecide_MAX();

				if(m_Chk < (f_Line.length() - 7))
					{
					m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Operator));
					m_Chk = acDecide_MAX();
					}
				}
			else if((f_StrCode.compare("Ifs") == 0) ||
					(f_StrCode.compare("Cond") == 0) ||
					(f_StrCode.compare("Conditional") == 0))
				{
				m_Code = MuCode_Condition;

				std::shared_ptr<Code> f_Type = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Condition);
				m_Type.push_back(f_Type);
				m_VarType = f_Type->m_VarType;

				m_Chk = acDecide_MAX();

				if(m_Chk < (f_Line.length() - 7))
					{
					m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Condition));
					m_Chk = acDecide_MAX();
					}
				}
			else if((f_StrCode.compare("For") == 0) ||
					(f_StrCode.compare("for") == 0))
				{
				m_Code = MuCode_For_Loop;

				if(m_Chk < (f_Line.length() - 7))
					{
					m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_For_Loop));
					m_Chk = acDecide_MAX();
					}

				m_Chk = acDecide_MAX();

				if(m_Chk < (f_Line.length() - 7))
					{
					m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
					m_Chk = acDecide_MAX();
					}

				if(m_Chk < (f_Line.length() - 7))
					{
					m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
					m_Chk = acDecide_MAX();
					}
				}
			else
				{
				printf("ESL-Null name save.\n");
				}
			}
		}
	else if(f_Code_DigitA == '/' &&
			f_Code_DigitB == '/')
		{
		m_END = 5;
		}
	else if(f_Code_DigitA == '*' &&		//Verified as operator tag
			f_Code_DigitB == '*')
		{
		m_VarType = agFind_OprType(f_StrCode);
		}
	else if(f_Code_DigitA == '^' &&		//Verified as condition tag
			f_Code_DigitB == '^')
		{
		m_VarType = agFind_ConType(f_StrCode);
		}
	else if(f_Code_DigitA == '&' ||
			f_Code_DigitA == '#')
		{
		if(f_Code_DigitB == '&')
			{
			m_VarType = agFind_VarType(f_StrCode);
			}
		else if(f_Code_DigitB == '*')
			{
			m_VarType = agFind_FunctionType(f_StrCode);
			}
		else if(f_Code_DigitB == '%')
			{
			if(m_VarType == MuVar_Int ||
			   m_VarType == MuVar_uInt ||
			   m_VarType == MuVar_Int2 ||
			   m_VarType == MuVar_Int3 ||
			   m_VarType == MuVar_Int4 ||
			   m_VarType == MuVar_Bool ||
			   m_VarType == MuVar_Char)
				{
				m_MxVar = std::make_shared<Variable>("FreshVar", MuCode_Var);

				if(m_MxName.compare("Random") == 0)
					{
					m_MxVar->m_Action = MuAct_Random;
					}
				else if(m_MxName.compare("Rand") == 0)
					{
					m_MxVar->m_Action = MuAct_RandInt;
					}
				else
					{
					m_MxVar->m_Action = MuAct_Start;
					m_MxVar->set_Value(atoi(m_MxName.c_str()));
					}
				}
			else if(m_VarType == MuVar_Float ||
					m_VarType == MuVar_Float2 ||
					m_VarType == MuVar_Float3 ||
					m_VarType == MuVar_Float4)
				{
				m_MxVar = std::make_shared<Variable>("FreshVar", MuCode_Var);

				if(m_MxName.compare("Random") == 0)
					{
					m_MxVar->m_Action = MuAct_Random;
					}
				else if(m_MxName.compare("Rand") == 0)
					{
					m_MxVar->m_Action = MuAct_RandInt;
					}
				else
					{
					m_MxVar->m_Action = MuAct_Start;
					m_MxVar->set_Value((float)atof(m_MxName.c_str()));
					}
				}
			else if(m_VarType == MuVar_String)
				{
				m_MxVar = std::make_shared<Variable>("FreshVar", MuCode_Var);

				m_MxVar->m_Action = MuAct_Start;
				m_MxVar->set_Value(m_MxName);
				}

			m_END = true;
			}
		}
	}

uint Code::acName_MAX(void)
	{
	uint f_NAccumA = 0;

	for(uint f_Int = 0; f_Int < m_Name.size(); f_Int++)
		{
		f_NAccumA = m_Name[f_Int]->m_Chk;
		}

	return f_NAccumA;
	}

uint Code::acNumber_MAX(void)
	{
	uint f_NAccumB = 0;

	for(uint f_Int = 0; f_Int < m_Number.size(); f_Int++)
		{
		f_NAccumB = m_Number[f_Int]->m_Chk;
		}

	return f_NAccumB;
	}

uint Code::acType_MAX(void)
	{
	uint f_NAccumC = 0;

	for(uint f_Int = 0; f_Int < m_Type.size(); f_Int++)
		{
		f_NAccumC = m_Type[f_Int]->m_Chk;
		}

	return f_NAccumC;
	}

uint Code::acParam_MAX(void)
	{
	uint f_NAccumD = 0;

	for(uint f_Int = 0; f_Int < m_Param.size(); f_Int++)
		{
		f_NAccumD = m_Param[f_Int]->m_Chk;
		}

	return f_NAccumD;
	}

uint Code::acName_END(void)
	{
	uint f_END = 0;

	for(uint f_Int = 0; f_Int < m_Name.size(); f_Int++)
		{
		if(m_Name[f_Int]->m_END > f_END) f_END = m_Name[f_Int]->m_END;
		}

	return f_END;
	}

uint Code::acNumber_END(void)
	{
	uint f_END = 0;

	for(uint f_Int = 0; f_Int < m_Number.size(); f_Int++)
		{
		if(m_Number[f_Int]->m_END > f_END) f_END = m_Number[f_Int]->m_END;
		}

	return f_END;
	}

uint Code::acType_END(void)
	{
	uint f_END = 0;

	for(uint f_Int = 0; f_Int < m_Type.size(); f_Int++)
		{
		if(m_Type[f_Int]->m_END > f_END) f_END = m_Type[f_Int]->m_END;
		}

	return f_END;
	}

uint Code::acParam_END(void)
	{
	uint f_END = 0;

	for(uint f_Int = 0; f_Int < m_Param.size(); f_Int++)
		{
		if(m_Param[f_Int]->m_END > f_END) f_END = m_Param[f_Int]->m_END;
		}

	return f_END;
	}

uint Code::acDecide_MAX(void)
	{
	uint f_NAccumA = acName_MAX();
	uint f_NAccumB = acNumber_MAX();
	uint f_NAccumC = acType_MAX();
	uint f_NAccumD = acParam_MAX();

	if(f_NAccumA > f_NAccumB)
		{
		if(f_NAccumA > f_NAccumC)
			{
			if(f_NAccumD > f_NAccumA)
				{
				return f_NAccumD;
				}
			else
				{
				return f_NAccumA;
				}
			}
		else
			{
			if(f_NAccumD > f_NAccumC)
				{
				return f_NAccumD;
				}
			else
				{
				return f_NAccumC;
				}
			}
		}
	else
		{
		if(f_NAccumB > f_NAccumC)
			{
			if(f_NAccumD > f_NAccumB)
				{
				return f_NAccumD;
				}
			else
				{
				return f_NAccumB;
				}
			}
		else
			{
			if(f_NAccumD > f_NAccumC)
				{
				return f_NAccumD;
				}
			else
				{
				return f_NAccumC;
				}
			}
		}

	return 0;
	}

uint Code::acDecide_END(void)
	{
	uint f_ENDA = acName_END();
	uint f_ENDB = acNumber_END();
	uint f_ENDC = acType_END();
	uint f_ENDD = acParam_END();

	if(f_ENDA > f_ENDB)
		{
		if(f_ENDA > f_ENDC)
			{
			if(f_ENDD > f_ENDA)
				{
				return f_ENDD;
				}
			else
				{
				return f_ENDA;
				}
			}
		else
			{
			if(f_ENDD > f_ENDC)
				{
				return f_ENDD;
				}
			else
				{
				return f_ENDC;
				}
			}
		}
	else
		{
		if(f_ENDB > f_ENDC)
			{
			if(f_ENDD > f_ENDB)
				{
				return f_ENDD;
				}
			else
				{
				return f_ENDB;
				}
			}
		else
			{
			if(f_ENDD > f_ENDC)
				{
				return f_ENDD;
				}
			else
				{
				return f_ENDC;
				}
			}
		}

	return 0;
	}

};