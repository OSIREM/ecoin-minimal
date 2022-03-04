/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Code.h"

using namespace ecoin;

namespace ecoin
{

Code::Code() : MuType(MuTYPE_Code), m_Index(0)
{
	std::string f_ref_CurrentPath = "Code::Code";

#ifdef ECOIN_OSI_MEMORY_FUNC
#ifdef ECOIN_OSI_MEM_MUSION
	ac_Push(m_Code, f_ref_CurrentPath + g_ref_Div + "m_Code");
	ac_Push(m_END, f_ref_CurrentPath + g_ref_Div + "m_END");
	ac_Push(m_Chk, f_ref_CurrentPath + g_ref_Div + "m_Chk");
	ac_Push(m_VarType, f_ref_CurrentPath + g_ref_Div + "m_VarType");
	ac_Push(m_MxName, f_ref_CurrentPath + g_ref_Div + "m_VarType");
	ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
	ac_Push(m_ContractID, f_ref_CurrentPath + g_ref_Div + "m_ContractID");
	ac_Push(m_Code_DigitA, f_ref_CurrentPath + g_ref_Div + "m_Code_DigitA");
	ac_Push(m_Code_DigitB, f_ref_CurrentPath + g_ref_Div + "m_Code_DigitB");
	ac_Push(m_Code_DigitC, f_ref_CurrentPath + g_ref_Div + "m_Code_DigitC");
	ac_Push(m_vec_Type, f_ref_CurrentPath + g_ref_Div + "m_vec_Type");
	ac_Push(m_vec_VarType, f_ref_CurrentPath + g_ref_Div + "m_vec_VarType");
	ac_Push(m_vec_NameCall, f_ref_CurrentPath + g_ref_Div + "m_vec_NameCall");
	ac_Push(m_vec_NameCallType, f_ref_CurrentPath + g_ref_Div + "m_vec_NameCallType");

	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (ecom_base::ControllerMethod_void)&Code::acClear);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_CallNames", (ecom_base::ControllerMethod_void)&Code::acPrepare_CallNames);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acCodeCall_Var", (ecom_base::ControllerMethod_void)&Code::acCodeCall_Var);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acCodeCall_Var", (ecom_base::ControllerMethod_void)&Code::acCodeMap_Var);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acName_MAX", (ecom_base::ControllerMethod_void)&Code::acName_MAX);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acName_END", (ecom_base::ControllerMethod_void)&Code::acName_END);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acNumber_MAX", (ecom_base::ControllerMethod_void)&Code::acNumber_MAX);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acNumber_END", (ecom_base::ControllerMethod_void)&Code::acNumber_END);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acType_MAX", (ecom_base::ControllerMethod_void)&Code::acType_MAX);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acType_END", (ecom_base::ControllerMethod_void)&Code::acType_END);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acParam_MAX", (ecom_base::ControllerMethod_void)&Code::acParam_MAX);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acParam_END", (ecom_base::ControllerMethod_void)&Code::acParam_END);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acDecide_MAX", (ecom_base::ControllerMethod_void)&Code::acDecide_MAX);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acDecide_END", (ecom_base::ControllerMethod_void)&Code::acDecide_END);

#if 0
	std::shared_ptr<Variable> m_MxVar;
	std::shared_ptr<Class> m_Class;
	std::shared_ptr<Function> m_FunctionLink;
	std::vector<std::shared_ptr<Code>> m_Name;
	std::vector<std::shared_ptr<Code>> m_Number;
	std::vector<std::shared_ptr<Code>> m_Type;
	std::vector<std::shared_ptr<Code>> m_Param;
	std::vector<std::shared_ptr<Condition>> m_Condition;
#endif
#endif
#endif
}

Code::Code(std::string f_Line, uint f_CHK, uint f_Index, uint f_CodeType, uint f_VarType) : MuType(MuTYPE_Code), m_Index(f_Index)
{
	std::string f_ref_CurrentPath = "Code::Code";

	acClear();

#ifdef ECOIN_OSI_MEMORY_FUNC
#ifdef ECOIN_OSI_MEM_MUSION
	ac_Push(m_Code, f_ref_CurrentPath + g_ref_Div + "m_Code");
	ac_Push(m_END, f_ref_CurrentPath + g_ref_Div + "m_END");
	ac_Push(m_Chk, f_ref_CurrentPath + g_ref_Div + "m_Chk");
	ac_Push(m_VarType, f_ref_CurrentPath + g_ref_Div + "m_VarType");
	ac_Push(m_MxName, f_ref_CurrentPath + g_ref_Div + "m_VarType");
	ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
	ac_Push(m_ContractID, f_ref_CurrentPath + g_ref_Div + "m_ContractID");
	ac_Push(m_Code_DigitA, f_ref_CurrentPath + g_ref_Div + "m_Code_DigitA");
	ac_Push(m_Code_DigitB, f_ref_CurrentPath + g_ref_Div + "m_Code_DigitB");
	ac_Push(m_Code_DigitC, f_ref_CurrentPath + g_ref_Div + "m_Code_DigitC");
	ac_Push(m_vec_Type, f_ref_CurrentPath + g_ref_Div + "m_vec_Type");
	ac_Push(m_vec_VarType, f_ref_CurrentPath + g_ref_Div + "m_vec_VarType");
	ac_Push(m_vec_NameCall, f_ref_CurrentPath + g_ref_Div + "m_vec_NameCall");
	ac_Push(m_vec_NameCallType, f_ref_CurrentPath + g_ref_Div + "m_vec_NameCallType");

	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (ecom_base::ControllerMethod_void)&Code::acClear);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_CallNames", (ecom_base::ControllerMethod_void)&Code::acPrepare_CallNames);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acCodeCall_Var", (ecom_base::ControllerMethod_void)&Code::acCodeCall_Var);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acCodeCall_Var", (ecom_base::ControllerMethod_void)&Code::acCodeMap_Var);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acName_MAX", (ecom_base::ControllerMethod_void)&Code::acName_MAX);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acName_END", (ecom_base::ControllerMethod_void)&Code::acName_END);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acNumber_MAX", (ecom_base::ControllerMethod_void)&Code::acNumber_MAX);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acNumber_END", (ecom_base::ControllerMethod_void)&Code::acNumber_END);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acType_MAX", (ecom_base::ControllerMethod_void)&Code::acType_MAX);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acType_END", (ecom_base::ControllerMethod_void)&Code::acType_END);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acParam_MAX", (ecom_base::ControllerMethod_void)&Code::acParam_MAX);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acParam_END", (ecom_base::ControllerMethod_void)&Code::acParam_END);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acDecide_MAX", (ecom_base::ControllerMethod_void)&Code::acDecide_MAX);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acDecide_END", (ecom_base::ControllerMethod_void)&Code::acDecide_END);
#endif
#endif

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

	//ECN.Code|DigitA %c|DigitB %c|StrCode %s\n", f_Code_DigitA, f_Code_DigitB, f_StrCode.c_str());

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

				//ag_StatusLive(f_ref_CurrentPath, "m_Type");
				m_Type.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
				m_Chk = acDecide_MAX();

				m_VarType = m_Type[0]->m_VarType;

				//ag_StatusLive(f_ref_CurrentPath, "m_Name");
				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
				m_Chk = acDecide_MAX();

				if(m_Chk < (f_Line.length() - 7))
					{
					int f_Chk = m_Chk;
					//ag_StatusLive(f_ref_CurrentPath, "f_RHSorName");
					std::shared_ptr<Code> f_RHSorName = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var, m_VarType);

					if(f_RHSorName->m_Name.size() <= 0) //small type
						{
						f_RHSorName->m_MxVar->m_MxName = m_Name[0]->m_MxName;

						m_Number.push_back(f_RHSorName);

						m_Chk = acDecide_MAX();
						}
					else   //large type,. reset reload
						{
						m_Chk = f_Chk;
						}
					}
				}
			else if((f_StrCode.compare("ClassVar") == 0) ||
					(f_StrCode.compare("CV") == 0))
				{
				m_Code = MuCode_ClassVar;

				//ag_StatusLive(f_ref_CurrentPath, "m_Type");
				m_Type.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_ClassVar));
				m_Chk = acDecide_MAX();

				m_VarType = m_Type[0]->m_VarType;

				//ag_StatusLive(f_ref_CurrentPath, "m_Name");
				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_ClassVar));
				m_Chk = acDecide_MAX();
				}
			else if((f_StrCode.compare("Fcn") == 0) ||
					(f_StrCode.compare("Func") == 0) ||
					(f_StrCode.compare("Call") == 0) ||
				    (f_StrCode.compare("FunctionCall") == 0))
				{
				m_Code = MuCode_Function;

#pragma message("is this needed...?")
				//ag_StatusLive(f_ref_CurrentPath, "m_MxVar");
				m_MxVar = std::make_shared<Variable>("ReturnVar", MuCode_Var);

				//ag_StatusLive(f_ref_CurrentPath, "m_Type");
				m_Type.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Function));
				m_Chk = acDecide_MAX();

				m_VarType = m_Type[0]->m_VarType;

				//ag_StatusLive(f_ref_CurrentPath, "m_Name");
				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Function));
				m_Chk = acDecide_MAX();

				while(m_Chk < (f_Line.length() - 7))
					{
					int f_Chk = m_Chk;
					//ag_StatusLive(f_ref_CurrentPath, "f_RHSorName");
					std::shared_ptr<Code> f_RHSorName = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var, m_VarType);

					if(f_RHSorName->m_Name.size() <= 0) //small type
						{
						f_RHSorName->m_MxVar->m_MxName = m_Name[0]->m_MxName;

						m_Number.push_back(f_RHSorName);

						m_Chk = acDecide_MAX();
						}
					else   //large type,. reset reload
						{
						m_Param.push_back(f_RHSorName);

						m_Chk = acDecide_MAX();
						}
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

				//ag_StatusLive(f_ref_CurrentPath, "m_Name");
				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Function));
				m_Chk = acDecide_MAX();

				//ag_StatusLive(f_ref_CurrentPath, "m_Name");
				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Function));
				m_Chk = acDecide_MAX();

				while(m_Chk < (f_Line.length() - 7))
					{
					//ag_StatusLive(f_ref_CurrentPath, "m_Param");
					m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
					m_Chk = acDecide_MAX();
					}
				}
			else if(f_StrCode.compare("Sys") == 0)
				{
				m_Code = MuCode_System;

				//ag_StatusLive(f_ref_CurrentPath, "m_Type");
				m_Type.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
				m_Chk = acDecide_MAX();

				m_VarType = m_Type[0]->m_VarType;

				//ag_StatusLive(f_ref_CurrentPath, "m_Name");
				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_System));
				m_Chk = acDecide_MAX();

				bool f_Scan = true;
				while((m_Chk < (f_Line.length() - 7)) && (f_Scan == true))
					{
					int f_Chk = m_Chk;
					//ag_StatusLive(f_ref_CurrentPath, "f_RHSorName");
					std::shared_ptr<Code> f_RHSorName = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var, m_VarType);

					if(f_RHSorName->m_Name.size() <= 0) //small type
						{
						f_RHSorName->m_MxVar->m_MxName = m_Name[0]->m_MxName;

						m_Number.push_back(f_RHSorName);

						m_Chk = acDecide_MAX();
						}
					else   //large type,. reset reload
						{
						m_Chk = f_Chk;
						f_Scan = false;
						}
					}
				}
			else if(f_StrCode.compare("Con") == 0)
				{
				m_Code = MuCode_Constant;

				//ag_StatusLive(f_ref_CurrentPath, "m_Type");
				m_Type.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Constant));
				m_Chk = acDecide_MAX();

				//ag_StatusLive(f_ref_CurrentPath, "m_Name");
				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Constant));
				m_Chk = acDecide_MAX();

				//ag_StatusLive(f_ref_CurrentPath, "f_Code");
				std::shared_ptr<Code> f_Code = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Constant);

				//ag_StatusLive(f_ref_CurrentPath, "f_Code->m_MxVar");
				f_Code->m_MxVar = std::make_shared<Variable>(m_Name[0]->m_MxName, MuCode_Constant);
				f_Code->m_MxVar->m_MxName = m_Name[0]->m_MxName;

				m_Number.push_back(f_Code);

				m_Chk = acDecide_MAX();
				}
			else if(f_StrCode.compare("Opr") == 0)
				{
				m_Code = MuCode_Operator;

				//ag_StatusLive(f_ref_CurrentPath, "f_Type");
				std::shared_ptr<Code> f_Type = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Operator);

				m_VarType = f_Type->m_VarType;

				m_Type.push_back(f_Type);
				m_Chk = acDecide_MAX();

				if(m_Chk < (f_Line.length() - 7))
					{
					int f_Chk = m_Chk;
					//ag_StatusLive(f_ref_CurrentPath, "f_RHSorName");
					std::shared_ptr<Code> f_RHSorName = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Operator);

					if(f_RHSorName->m_Name.size() <= 0) //small type
						{
						m_Name.push_back(f_RHSorName); //push name
						m_Chk = acDecide_MAX();
						}
					else   //large type,. reset reload
						{
						m_Chk = f_Chk;
						}
					}
				}
			else if((f_StrCode.compare("Ifs") == 0) ||
					(f_StrCode.compare("Cond") == 0) ||
					(f_StrCode.compare("Conditional") == 0))
				{
				m_Code = MuCode_Condition;

				//ag_StatusLive(f_ref_CurrentPath, "f_Type");
				std::shared_ptr<Code> f_Type = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Condition);
				
				m_VarType = f_Type->m_VarType;

				m_Type.push_back(f_Type);
				m_Chk = acDecide_MAX();

				if(m_Chk < (f_Line.length() - 7))
					{
					int f_Chk = m_Chk;
					//ag_StatusLive(f_ref_CurrentPath, "f_RHSorName");
					std::shared_ptr<Code> f_RHSorName = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Condition);

					if(f_RHSorName->m_Name.size() <= 0) //small type
						{
						m_Name.push_back(f_RHSorName); //push name
						m_Chk = acDecide_MAX();
						}
					else   //large type,. reset reload
						{
						m_Chk = f_Chk;
						}
					}
				}
			else if((f_StrCode.compare("For") == 0) ||
					(f_StrCode.compare("for") == 0))
				{
				m_Code = MuCode_For_Loop;

				if(m_Chk < (f_Line.length() - 7))
					{
					int f_Chk = m_Chk;
					//ag_StatusLive(f_ref_CurrentPath, "f_RHSorName");
					std::shared_ptr<Code> f_RHSorName = std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Operator);

					if(f_RHSorName->m_Name.size() <= 0) //small type
						{
						m_Name.push_back(f_RHSorName); //push name
						m_Chk = acDecide_MAX();

						if(m_Chk < (f_Line.length() - 7))
							{
							//ag_StatusLive(f_ref_CurrentPath, "m_Param");
							m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
							m_Chk = acDecide_MAX();
							}

						if(m_Chk < (f_Line.length() - 7))
							{
							//ag_StatusLive(f_ref_CurrentPath, "m_Param");
							m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
							m_Chk = acDecide_MAX();
							}

						if(m_Chk < (f_Line.length() - 7))
							{
							//ag_StatusLive(f_ref_CurrentPath, "m_Param");
							m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
							m_Chk = acDecide_MAX();
							}
						}
					else   //large type,. reset reload
						{
						m_Param.push_back(f_RHSorName); //push param 1
						m_Chk = acDecide_MAX();

						if(m_Chk < (f_Line.length() - 7))
							{
							//ag_StatusLive(f_ref_CurrentPath, "m_Param");
							m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
							m_Chk = acDecide_MAX();
							}

						if(m_Chk < (f_Line.length() - 7))
							{
							//ag_StatusLive(f_ref_CurrentPath, "m_Param");
							m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
							m_Chk = acDecide_MAX();
							}

						if(m_Chk < (f_Line.length() - 7))
							{
							//ag_StatusLive(f_ref_CurrentPath, "m_Param");
							m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
							m_Chk = acDecide_MAX();
							}
						}
					}
				}
			else if (f_StrCode.compare("ClassDef") || f_StrCode.compare("Class"))
				{
				m_Code = MuCode_ClassDef;

				//ag_StatusLive(f_ref_CurrentPath, "m_Name");
				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_ClassDef, m_VarType));
				m_Chk = acDecide_MAX();

				//ag_StatusLive(f_ref_CurrentPath, "m_Name");
				m_Name.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_ClassDef, m_VarType));
				m_Chk = acDecide_MAX();
				}
			else if(f_StrCode.compare("Return") == 0)
				{
				m_Code = MuCode_Return;

				if(m_Chk < (f_Line.length() - 7))
					{
					//ag_StatusLive(f_ref_CurrentPath, "m_Param");
					m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
					m_Chk = acDecide_MAX();
					}
				//wanna add return any number of var or classvar
				}
			else if (f_StrCode.compare("Template") == 0)
				{
				m_Code = MuCode_Template;

				if(m_Chk < (f_Line.length() - 7))
					{
					//ag_StatusLive(f_ref_CurrentPath, "m_Param");
					m_Param.push_back(std::make_shared<Code>(f_Line, m_Chk, f_Index, MuCode_Var));
					m_Chk = acDecide_MAX();
					}
				}
			else
				{
				//ESL-Null name save...
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
			m_VarType = agFind_VarType(f_StrCode);	//find type of var
			}
		else if(f_Code_DigitB == '*')
			{
			m_VarType = agFind_FunctionType(f_StrCode);	//any function call
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
				//ag_StatusLive(f_ref_CurrentPath, "m_MxVar");
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
				//ag_StatusLive(f_ref_CurrentPath, "m_MxVar");
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
				//ag_StatusLive(f_ref_CurrentPath, "m_MxVar");
				m_MxVar = std::make_shared<Variable>("FreshVar", MuCode_Var);

				m_MxVar->m_Action = MuAct_Start;
				m_MxVar->set_Value(m_MxName);
				}

			m_END = true;
			}
		else if(f_Code_DigitB == '$')	//classvar
			{
			std::string f_VarTypeStr;

			f_VarTypeStr.clear();

			int f_HeadMode = 0;

			for(int f_Jet = 0; f_Jet < f_StrCode.length(); f_Jet++)
				{
				char f_c = f_StrCode.at(f_Jet);

				if(f_HeadMode == 0)
					{
					if(f_c == '<')
						{
						m_vec_Type.push_back(f_VarTypeStr);

						f_VarTypeStr.clear();
						}
					else if(f_c == '>')
						{
						m_vec_Type.push_back(f_VarTypeStr);

						f_VarTypeStr.clear();

						f_HeadMode = 1;
						}
					else
						{
						f_VarTypeStr.push_back(f_c);
						}

					if(f_Jet >= f_StrCode.length() - 1)
						{
						m_vec_Type.push_back(f_VarTypeStr);

						f_VarTypeStr.clear();
						}
					}
				}

			if(m_vec_Type.size() > 1) //vector
				{
				for(int f_XY = 0; f_XY < m_vec_Type.size(); f_XY++)
					{
					if((m_vec_Type[f_XY].compare("vector") == 0) ||
						(m_vec_Type[f_XY].compare("std::vector") == 0))
						{
						bool f_Found = false;

						for(int f_Jet = 0; f_Jet < g_Class.size() - 1; f_Jet++)
							{
							if(g_Class[f_Jet]->m_MxName.compare(m_vec_Type[f_XY + 1]) == 0)
								{
								f_Found = true;
								m_Class = g_Class[f_Jet];
								}
							}

						if(f_Found == true)
							{
							m_vec_VarType.push_back(f_XY);
							m_VarType = 1;
							}
						else
							{
							m_vec_VarType.push_back(-1);
							m_VarType = -1;
							}
						}
					}
				}
			else
				{
				bool f_Found = false;

				for(int f_XY = 0; f_XY < g_Class.size(); f_XY++)
					{
					if(g_Class[f_XY]->m_MxName.compare(m_vec_Type[f_XY]) == 0)
						{
						f_Found = true;
						m_Class = g_Class[f_XY];
						}
					}

				if(f_Found == true)
					{
					m_vec_VarType.push_back(0);
					m_VarType = 1;
					}
				else
					{
					m_vec_VarType.push_back(-1);
					m_VarType = -1;
					}
				}
			}
		}
	}

void Code::acPrepare_CallNames(void)
{
	std::string f_ClassVarName = m_Name[0]->m_MxName;

	int f_PointerClassMemberVar = 0;
	int f_IndexClassMemberVar = 0;

	std::vector<int> f_vec_PointerClassTypeMeM;
	std::vector<int> f_vec_IndexClassTypeMeM;

	f_vec_PointerClassTypeMeM.clear();
	f_vec_IndexClassTypeMeM.clear();

	std::string f_Carriage = "";

	m_vec_NameCall.clear();

	for(int f_Jet = 0; f_Jet < f_ClassVarName.length(); f_Jet++)
		{
		char f_c = f_ClassVarName.at(f_Jet);

		if(f_IndexClassMemberVar == 0)
			{
			if(f_PointerClassMemberVar == 0)
				{
				if(f_c == '-') //classvar-
					{
					f_PointerClassMemberVar = 1;
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_ClassVar);
					f_Carriage.clear();
					}
				else if(f_c == '[') //classvar[
					{
					throw; //add debug message no native vector error
					}
				else  //classv
					{
					f_Carriage.push_back(f_c);
					}

				if(f_Jet >= f_ClassVarName.length() - 1) //classvar
					{
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_VarVar);
					f_Carriage.clear();
					}
				}
			else if(f_PointerClassMemberVar == 1)
				{
				if(f_c == '>') //classvar->
					{
					f_PointerClassMemberVar = 2;
					}
				}
			else if(f_PointerClassMemberVar == 2)
				{
				if(f_c == '-') //classvar->classvar-
					{
					f_PointerClassMemberVar = 1;
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_ClassVar);
					f_Carriage.clear();
					}
				else if(f_c == '[') //classvar->membervar[ assume evector
					{
					f_IndexClassMemberVar = 1;
					f_PointerClassMemberVar = 0;
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_MemberVar);
					f_Carriage.clear();
					}
				else if(f_c == ']') //!!!classvar->classvar]
					{
					throw; //add debug message syntax error extra square close bracket
					}
				else
					{
					f_Carriage.push_back(f_c);
					}

				if(f_Jet >= f_ClassVarName.length() - 1) //classvar->membervar
					{
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_MemberVar);
					}
				}
			}
		else if(f_IndexClassMemberVar == 1)
			{
			if(f_PointerClassMemberVar == 0)
				{
				if(f_c == '-') //classvar->classvar[f_adindex-   //after -//classvar->classvar[f_adindex->m_ad[f_Jet-
					{
					f_PointerClassMemberVar = 1;
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_ClassVar);
					f_Carriage.clear();
					}
				else if(f_c == '[') //!!!classvar->classvar[f_adindex[   //after -//!!!classvar->classvar[f_adindex->m_ad[f_Jet[
					{
					throw; //add debug message no native vector error
					}
				else if(f_c == ']') //classvar->classvar[f_adindex] check for win length   //after -//classvar->classvar[f_adindex->m_ad[f_Jet]
					{
					f_IndexClassMemberVar = 2;
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_VarIndexInt);
					f_Carriage.push_back(f_c); //fixme check for native int at run-time
					}
				else
					{
					f_Carriage.push_back(f_c);
					}

				if((f_Jet >= f_ClassVarName.length() - 1) && (f_c != ']'))
					{
					throw;
					}
				}
			else if(f_PointerClassMemberVar == 1)
				{
				if(f_c == '>') //classvar->classvar[f_adindex->
					{
					f_PointerClassMemberVar = 2;
					f_Carriage.clear();
					}
				}
			else if(f_PointerClassMemberVar == 2)
				{
				if(f_c == '>') //!!!classvar->classvar[f_adindex->>
					{
					throw; //add debug message
					}
				if(f_c == '-') //classvar->classvar[f_adindex->m_ad-
					{
					f_PointerClassMemberVar = 1;
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_ClassVar);
					f_Carriage.clear();
					}
				else if(f_c == ']') //classvar->classvar[f_adindex->m_ad] check for win conditions
					{
					f_IndexClassMemberVar = 2;
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_MemberIndexInt);
					f_Carriage.clear();
					}
				else if(f_c == '[') //classvar->classvar[f_adindex->m_ad[
					{
					f_PointerClassMemberVar = 0;
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_MemberVar);
					f_Carriage.clear();
					}
				else
					{
					f_Carriage.push_back(f_c);
					}
									
				if((f_Jet >= f_ClassVarName.length() - 1) && (f_c != ']'))
					{
					throw; //add debugging message vector index syntax error
					}
				}
			else
				{
				throw; //add debug message
				}
			}
		else if(f_IndexClassMemberVar == 2)
			{
			if(f_PointerClassMemberVar == 0)
				{
				if(f_c == '-') //classvar->classvar[f_adindex]-
					{
					f_PointerClassMemberVar = 1;
					f_Carriage.clear();
					}
				else if(f_c == '[') //classvar->classvar[f_adindex][
					{
					f_IndexClassMemberVar = 1;
					f_Carriage.clear();
					}
				else
					{
					throw; //add debug message array index or close name only
					}
				}
			else if(f_PointerClassMemberVar == 1)
				{  //classvar->classvar[f_adindex]-
				if(f_c == '>')
					{
					f_PointerClassMemberVar = 2;
					}
				else
					{
					throw; //add debug message syntax error
					}
				}
			else if(f_PointerClassMemberVar == 2)
				{
				if(f_c == '-') //classvar->membervar[f_adindex]->m_var-
					{
					f_PointerClassMemberVar = 1;
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_ClassVar);
					f_Carriage.clear();
					}
				else if(f_c == '[')  //classvar->membervar[f_adindex]->m_var[
					{
					f_IndexClassMemberVar = 1;
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_MemberVar);
					f_Carriage.clear();
					}
				else if(f_c == ']')
					{
					throw; //add debug message syntax error vector array close symbol
					}
				else
					{
					f_Carriage.push_back(f_c);
					}

				if(f_Jet >= f_ClassVarName.length() - 1) //classvar->membervar[f_adindex]->m_membervar
					{
					m_vec_NameCall.push_back(f_Carriage);
					m_vec_NameCallType.push_back(MuNameCall_Type_MemberVar);
					f_Carriage.clear();
					}
				}
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
	}

};