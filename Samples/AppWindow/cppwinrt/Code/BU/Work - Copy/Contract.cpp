/*

Contract - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "../Musion/Code.h"
#include "../Musion/CodeLine.h"
#include "../Musion/Function.h"
#include "../Musion/Class.h"

#include "Contract.h"

#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <vector>

std::shared_ptr<ecoin::Contract> g_Contract;

using namespace ecoin;

namespace ecoin
{
template<class T>
T ag_any_cast(boost::any f_Any)
{
#ifdef ECOIN_SECURE
	try
		{
		return boost::any_cast<T>(f_Any);
		}
	catch (boost::bad_any_cast &e)
		{
#if 1
		std::cerr << e.what() << '\n';
#endif
		for(;;)
			{
			//pause
			}
		}
#else
	return boost::any_cast<T>(f_Any);
#endif
}

std::vector<std::shared_ptr<Function>> g_Function;
std::vector<std::shared_ptr<Class>> g_Class;
std::vector<std::shared_ptr<ClassVar>> g_ClassVar;
std::vector<std::shared_ptr<Condition>> g_Condition;
std::vector<std::shared_ptr<Function>> g_systemFunction;

std::vector<std::shared_ptr<Contract>> g_vec_GlobalScopeContract;

int g_ContractID = 0;

Contract::Contract()
{
	m_ContractID = g_ContractID;
	g_ContractID++;

	m_Result_Variable = nullptr;
	m_Result_ClassVar = nullptr;

	m_Chk = 0;
	m_Count = 0;
	m_Str_Command.clear();

	acInit();

	m_System = new System();
}

Contract::Contract(std::string f_IN)
{
	m_ContractID = g_ContractID;
	g_ContractID++;

	m_Result_Variable = nullptr;
	m_Result_ClassVar = nullptr;

	m_Chk = 0;
	m_Count = 0;
	m_Str_Command = f_IN;

	acInit();

	m_System = new System();

	acExtractLines();

	acScan_Lines();
}

void Contract::acInit(void)
{
	printf("New ESL Shader Script Compile...\n");
}

Contract::~Contract()
{
	m_Chk = 0;
	m_Count = 0;
	m_Str_Command.clear();

	m_Result_Variable = nullptr;
	m_Result_ClassVar = nullptr;
}

bool Contract::acLoad_StrIn(std::string f_IN)
{
	m_Str_Command = f_IN;

	acExtractLines();

	acScan_Lines();

	return true;
}

bool Contract::acExtractLines(void)
{
	std::string f_Line;
	uint f_Chk = 0;

	bool f_Scan = true;
	while(f_Scan)
		{
		f_Line.clear();

		char f_Char = acFileReadChar(m_Str_Command, f_Chk);
		f_Chk++;
		while(f_Char != '/')
			{
			f_Line.push_back(f_Char);
			f_Char = acFileReadChar(m_Str_Command, f_Chk);
			f_Chk++;
			}

		char f_CharB = acFileReadChar(m_Str_Command, f_Chk);
		f_Chk++;
		char f_CharC = acFileReadChar(m_Str_Command, f_Chk);
		f_Chk++;
		char f_CharD = acFileReadChar(m_Str_Command, f_Chk);
		f_Chk++;

		if (f_CharB == '#' ||
			f_CharC == '#' ||
			f_CharD == '#')
			{
			f_Scan = false;
			}
		
		f_Line.push_back(f_Char);
		f_Line.push_back(f_CharB);
		f_Line.push_back(f_CharC);
		f_Line.push_back(f_CharD);

		m_Line.push_back(f_Line);
		}

	return true;
}

bool Contract::acScan_Str(void)
{
#if 0
	bool f_Scan = true;
	while(f_Scan == true)
		{ ////////////////
		 ////////////////
		// Line Detect
		std::shared_ptr<CodeLine> f_CodeLine = acScan_LineDetect(m_Str_Command);

		std::shared_ptr<Code> f_CodeAl = f_CodeLine->m_vec_Code[f_CodeLine->m_vec_Code.size() - 1];

		const char f_CharA = f_CodeAl->m_Code_DigitA;
		const char f_CharB = f_CodeAl->m_Code_DigitB;
		const char f_CharC = f_CodeAl->m_Code_DigitC;

		if(f_CharA == '#' ||
			f_CharB == '#' ||
			f_CharC == '#')
			{
			m_State.m_Verify_DL = true;
			m_State.m_Verify_Reading = true;
			m_State.m_Verify_UnWrapped = false;
			f_Scan = false;
			}
		else if(f_CharA == '/' &&
				 f_CharB == '/')
			{
			m_State.m_Verify_DL = true;
			m_State.m_Verify_Reading = true;
			m_State.m_Verify_UnWrapped = false;
			f_Scan = true;
			}
		else
			{
			m_State.m_Verify_DL = true;
			m_State.m_Verify_Reading = true;
			m_State.m_Verify_UnWrapped = false;
			f_Scan = true;
			}
		}
#endif

	return true;
}

bool Contract::acScan_Lines(void)
{
	for(int f_LineCount = 0; f_LineCount < m_Line.size(); f_LineCount++)
		{ ////////////////
		 ////////////////
		// Line Detect
		std::shared_ptr<CodeLine> f_CodeLine = acScan_LineDetect(m_Line[f_LineCount]);

#if 0
		std::shared_ptr<Code> f_CodeAl = f_CodeLine->m_vec_Code[f_CodeLine->m_vec_Code.size() - 1];
#endif
		}

	return true;
}

std::shared_ptr<CodeLine> Contract::acScan_LineDetect(std::string f_Line)
{
	std::shared_ptr<CodeLine> f_CodeLine = NULL;
	m_Chk = 0;

	//ESL::New Line::...

	while(m_Chk < f_Line.length() - 6)
		{
		f_CodeLine = std::make_shared<CodeLine>(f_Line, m_Chk, m_System);

		m_Chk = f_CodeLine->m_Chk;

		 /////////////////
		// Verify Entry
		if(f_CodeLine->m_CodeLine < 3)
			{
			if(g_Class.size() > 0)
				{
				g_Class[g_Class.size() - 1]->m_vec_CodeLine.push_back(f_CodeLine);

				for(int f_Jet = 0; f_Jet < f_CodeLine->m_vec_Variable.size(); f_Jet++)
					{
					std::shared_ptr<Variable> f_Var = f_CodeLine->m_vec_Variable[f_Jet];
					
					f_Var->m_LinkClass = g_Class[g_Class.size() - 1];
					g_Class[g_Class.size() - 1]->m_vec_Variable.push_back(f_Var);
					}
				}
			}
		else if(f_CodeLine->m_CodeLine == MuLine_Condition_Ajax)
			{
			std::shared_ptr<Code> f_LtCode = f_CodeLine->m_vec_Code[0];
			std::shared_ptr<Code> f_CnCode = f_CodeLine->m_vec_Code[1];
			std::shared_ptr<Code> f_RtCode = f_CodeLine->m_vec_Code[2];

			std::shared_ptr<Condition> f_Condition = std::make_shared<Condition>(f_CnCode->m_MxName);

			f_Condition->m_Condition = f_CnCode->m_Type[0]->m_VarType;
			f_Condition->m_VarType = f_LtCode->m_Type[0]->m_VarType;

			f_Condition->leftHand = std::make_shared<Variable>(f_LtCode->m_Name[0]->m_MxName, f_LtCode->m_Code);
			f_CodeLine->m_vec_Variable.push_back(f_Condition->leftHand);

			if(f_RtCode->m_Number.size() >= 1)
				{
				f_Condition->rightHand = f_RtCode->m_Number[0]->m_MxVar;
				f_CodeLine->m_vec_Variable.push_back(f_Condition->rightHand);
				}
			else
				{
				f_Condition->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
				f_CodeLine->m_vec_Variable.push_back(f_Condition->rightHand);
				}

			f_CnCode->m_Condition.push_back(f_Condition);
			g_Condition.push_back(f_Condition);
			}
		else if(f_CodeLine->m_CodeLine == MuLine_Function)
			{
			if(f_CodeLine->m_vec_Code[0]->m_Code == MuCode_Function)	//position zero
				{
				std::shared_ptr<Code> f_FnCode = f_CodeLine->m_vec_Code[0];

				std::shared_ptr<Function> f_Function = std::make_shared<Function>(f_FnCode->m_Type[0]->m_VarType);

				for(int f_Jet = 0; f_Jet < f_FnCode->m_Param.size(); f_Jet++)
					{
					std::shared_ptr<Code> f_ParamCode = f_FnCode->m_Param[f_Jet];

					f_Function->acPrep_addVariable(f_ParamCode->m_MxVar);
					}

				f_FnCode->m_FunctionLink = f_Function;
				}
			else if(f_CodeLine->m_vec_Code[1]->m_Code == MuCode_Function)	//position one
				{
				std::shared_ptr<Code> f_LHSCode = f_CodeLine->m_vec_Code[0];
				std::shared_ptr<Code> f_FnCode = f_CodeLine->m_vec_Code[1];

				std::shared_ptr<Function> f_Function = std::make_shared<Function>(f_FnCode->m_Type[0]->m_VarType);

				for(int f_Jet = 0; f_Jet < f_FnCode->m_Param.size(); f_Jet++)
					{
					std::shared_ptr<Code> f_ParamCode = f_FnCode->m_Param[f_Jet];

					f_Function->acPrep_addVariable(f_ParamCode->m_MxVar);
					}

				f_FnCode->m_FunctionLink = f_Function;
				}
			}
		else if(f_CodeLine->m_CodeLine == MuLine_Function_Custom)
			{
			std::shared_ptr<Code> f_Code = f_CodeLine->m_vec_Code[0];

			if(f_Code->m_Name[0]->m_MxName.compare("Success") == 0)
				{
				if(g_Function.size() >= 1 && g_Condition.size() >= 1)
					{
					std::shared_ptr<Function> f_Function = std::make_shared<Function>(MuFunc_Custom);
					
					f_Function->m_MxName = f_Code->m_Name[0]->m_MxName;

					if(f_Code->m_Name.size() >= 2)
						{
						for(int f_XY = 0; f_XY < g_Condition.size(); f_XY++)
							{
							if(g_Condition[f_XY]->m_MxName.compare(f_Code->m_Name[1]->m_MxName) == 0)
								{
								g_Condition[f_XY]->m_Success_Contract_FunctionID = g_Function.size();
								}
							}
						}
					else
						{
						g_Condition[g_Condition.size() - 1]->m_Success_Contract_FunctionID = g_Function.size();
						}

					f_Function->m_Start_CodeLine = f_CodeLine;

					f_Code->m_ContractID = g_Function.size();
					g_Function.push_back(f_Function);
					}
				}
			else if(f_Code->m_Name[0]->m_MxName.compare("Failure") == 0)
				{
				if(g_Function.size() >= 2 && g_Condition.size() >= 1)
					{
					std::shared_ptr<Function> f_Function = std::make_shared<Function>(MuFunc_Custom);
					
					f_Function->m_MxName = f_CodeLine->m_vec_Code[0]->m_Name[0]->m_MxName;

					if(f_Code->m_Name.size() >= 2)
						{
						for(int f_XY = 0; f_XY < g_Condition.size(); f_XY++)
							{
							if(g_Condition[f_XY]->m_MxName.compare(f_Code->m_Name[1]->m_MxName) == 0)
								{
								g_Condition[f_XY]->m_Failure_Contract_FunctionID = g_Function.size();
								}
							}
						}
					else
						{
						g_Condition[g_Condition.size() - 1]->m_Failure_Contract_FunctionID = g_Function.size();
						}

					f_Function->m_Start_CodeLine = f_CodeLine;

					f_Code->m_ContractID = g_Function.size();
					g_Function.push_back(f_Function);
					}
				}
			else
				{
				std::string f_Name = f_CodeLine->m_vec_Code[0]->m_Name[0]->m_MxName;

				if((f_Name.compare("Body") != 0) && (f_Name.length() > 0))
					{	// NEW Custom Function
					std::shared_ptr<Function> f_Function = std::make_shared<Function>(MuFunc_Custom);

					f_Function->m_MxName = f_Name;
					f_Function->m_Start_CodeLine = f_CodeLine;

					f_CodeLine->m_Execute = false;
					f_CodeLine->m_vec_Code[0]->m_ContractID = g_Function.size();

					m_Last_Function_ContractID = g_Function.size();

					if(g_Class.size() > 0)
						{
						f_Function->m_LinkClass = g_Class[g_Class.size() - 1];

						g_Class[g_Class.size() - 1]->m_vec_Function.push_back(f_Function);
						}

					g_Function.push_back(f_Function);
					}
				else	// CONTINUE Previous Function Body
					{
					f_CodeLine->m_vec_Code[0]->m_ContractID = m_Last_Function_ContractID;
					}
				}
			}
		else if(f_CodeLine->m_CodeLine == MuLine_Function_Frame)
			{
			std::shared_ptr<Code> f_Code = f_CodeLine->m_vec_Code[0];
			std::string f_Name = f_Code->m_Name[0]->m_MxName;

			m_Frame_Function = std::make_shared<Function>(MuFunc_Frame);

			m_Frame_Function->m_Start_CodeLine = f_CodeLine;
			m_Frame_Function->m_MxName = f_Name;

			f_CodeLine->m_Execute = false;
			f_CodeLine->m_vec_Code[0]->m_ContractID = g_Function.size();

			m_Last_Function_ContractID = g_Function.size();

			if(g_Class.size() > 0)
				{
				m_Frame_Function->m_LinkClass = g_Class[g_Class.size() - 1];

				g_Class[g_Class.size() - 1]->m_vec_Function.push_back(m_Frame_Function);
				}

			g_Function.push_back(m_Frame_Function);
			}
		else if (f_CodeLine->m_CodeLine == MuLine_For_Loop)
			{
			std::shared_ptr<Code> f_Code = f_CodeLine->m_vec_Code[0];
			std::string f_Name = f_Code->m_Name[0]->m_MxName;

			std::shared_ptr<Function> f_Function = std::make_shared<Function>(MuFunc_Custom);

			f_Function->m_Start_CodeLine = f_CodeLine;
			f_Function->m_MxName = f_Name;
			f_CodeLine->m_Execute = false;
			f_CodeLine->m_vec_Code[0]->m_ContractID = g_Function.size();

			m_Last_Function_ContractID = g_Function.size();

			g_Function.push_back(f_Function);
			}
		else if (f_CodeLine->m_CodeLine == MuLine_ClassDef)
			{
			std::shared_ptr<Code> f_Code = f_CodeLine->m_vec_Code[0];
			std::string f_Name = f_Code->m_Name[1]->m_MxName;

			std::shared_ptr<Class> f_Class = std::make_shared<Class>();

			f_Class->m_MxName = f_Name;

			g_Class.push_back(f_Class);
			}

		 ///////////////////
		// Storage
		if(g_Function.size() >= 1)
			{
			if((f_CodeLine->m_CodeLine != MuLine_Function_Custom) &&
				(f_CodeLine->m_CodeLine != MuLine_Function_Frame) &&
				(f_CodeLine->m_CodeLine != MuLine_For_Loop))
				{
				if(m_Last_Function_ContractID == g_Function.size() - 1)
					{	//CUSTOM
					g_Function[m_Last_Function_ContractID]->m_vec_CodeLine.push_back(f_CodeLine);
					}
				else
					{	//CONDITON SUCCESS or FAILURE
					g_Function[g_Function.size() - 1]->m_vec_CodeLine.push_back(f_CodeLine);
					}
				}
			}
		}

	return f_CodeLine;
}

std::shared_ptr<Variable> Contract::ac_VarByName(std::shared_ptr<Variable> f_Variable)
{
	for(int f_Jet = 0; f_Jet < g_vec_GlobalScopeContract.size(); f_Jet++)
		{
		std::shared_ptr<Contract> f_Contract = g_vec_GlobalScopeContract[f_Jet];

		uint f_CntStore = 0;
		while(f_CntStore < f_Contract->m_vec_Variable_Store.size())
			{
			std::shared_ptr<Variable> f_VariableStore = f_Contract->m_vec_Variable_Store[f_CntStore];

			if((f_VariableStore->m_MxName.compare(f_Variable->m_MxName.c_str()) == 0) &&
				(f_VariableStore->m_MxName.compare("Con") != 0))
				{
				return f_VariableStore;
				}

			f_CntStore++;
			}

		if(f_Contract->m_ContractID == m_ContractID)
			{
			if(f_Variable->m_MxName.compare("Con") != 0) //!constant
				{
				f_Contract->m_vec_Variable_Store.push_back(f_Variable);
				}
			}
		}

	return f_Variable;
}

void Contract::ac_SetupVars(void)
{
	//FIXME insert scope
	for(int f_XY = 0; f_XY < g_Function.size(); f_XY++)
		{
		uint f_CodeLineSize = g_Function[f_XY]->m_vec_CodeLine.size();

		uint f_CntCodeLine = 0;
		while(f_CntCodeLine < f_CodeLineSize)
			{
			std::shared_ptr<CodeLine> f_CodeLine = g_Function[f_XY]->m_vec_CodeLine[f_CntCodeLine];

			uint f_VarSize = f_CodeLine->m_vec_Variable.size();

			uint f_CntVar = 0;
			while(f_CntVar < f_VarSize)
				{
				std::shared_ptr<Variable> f_Variable = f_CodeLine->m_vec_Variable[f_CntVar];

				f_CodeLine->m_vec_Variable[f_CntVar] = ac_VarByName(f_Variable);

				f_CntVar++;
				}

			switch(f_CodeLine->m_CodeLine)
				{
				//case MuLine_Assign:
				case MuLine_Assign_Opr:
					{
					f_CodeLine->m_vec_Operator[0]->leftHand = ac_VarByName(f_CodeLine->m_vec_Operator[0]->leftHand);
					f_CodeLine->m_vec_Variable.push_back(f_CodeLine->m_vec_Operator[0]->leftHand);

					if(f_CodeLine->m_vec_Code[2]->m_Number.size() > 0)
						{
						f_CodeLine->m_vec_Operator[0]->rightHand = f_CodeLine->m_vec_Code[2]->m_Number[0]->m_MxVar;
						f_CodeLine->m_vec_Variable.push_back(f_CodeLine->m_vec_Operator[0]->rightHand);
						}
					else
						{
						f_CodeLine->m_vec_Operator[0]->rightHand = ac_VarByName(f_CodeLine->m_vec_Operator[0]->rightHand);
						f_CodeLine->m_vec_Variable.push_back(f_CodeLine->m_vec_Operator[0]->rightHand);
						}
					}break;

#if 0
				/*case MuLine_Init_Var:
					{
					if(f_VarSize == 1)
						{
						m_vec_Code[0]->m_MxVar = m_vec_Variable[0];
						}
					else if(f_VarSize == 2)
						{
						m_vec_Code[0]->m_MxVar = m_vec_Variable[0];
						m_vec_Code[1]->m_MxVar = m_vec_Variable[1];
						}
					else
						{
						throw;
						}
					}break;*/
#endif

				case MuLine_Condition_Ajax:
					{
					f_CodeLine->m_vec_Code[1]->m_Condition[0]->leftHand = ac_VarByName(f_CodeLine->m_vec_Code[1]->m_Condition[0]->leftHand);

					if(f_CodeLine->m_vec_Variable[2]->m_MxName.compare("Con") != 0)
						{
						f_CodeLine->m_vec_Code[1]->m_Condition[0]->rightHand = ac_VarByName(f_CodeLine->m_vec_Code[1]->m_Condition[0]->rightHand);
						}

					}break;

				case MuLine_Function:
					{
					if(f_CodeLine->m_Result_V != nullptr)
						{
						g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_Return_V = ac_VarByName(f_CodeLine->m_Result_V);

						for(int f_XY = 0; f_XY < g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable.size(); f_XY++)
							{
							g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY] = ac_VarByName(g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY]);
							}
						}
					else if(f_CodeLine->m_Result_CV != nullptr)
						{
#if 0
						g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_Return_CV = ac_VarByName(f_CodeLine->m_Result_CV);

						for(int f_XY = 0; f_XY < g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable.size(); f_XY++)
							{
							g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY] = ac_VarByName(g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY]);
							}
#endif
						}
					else
						{
						g_Function[f_CodeLine->m_vec_Code[0]->m_ContractID]->m_Return_V = nullptr;

						for(int f_XY = 0; f_XY < g_Function[f_CodeLine->m_vec_Code[0]->m_ContractID]->m_vec_Variable.size(); f_XY++)
							{
							g_Function[f_CodeLine->m_vec_Code[0]->m_ContractID]->m_vec_Variable[f_XY] = ac_VarByName(g_Function[f_CodeLine->m_vec_Code[0]->m_ContractID]->m_vec_Variable[f_XY]);
							}
						}
					}break;
				}

			f_CntCodeLine++;
			}
		}

	uint f_CodeFSLineSize = m_Frame_Function->m_vec_CodeLine.size();

	uint f_CntCodeFSLine = 0;
	while(f_CntCodeFSLine < f_CodeFSLineSize)
		{
		std::shared_ptr<CodeLine> f_CodeLine = m_Frame_Function->m_vec_CodeLine[f_CntCodeFSLine];

		uint f_VarFSSize = f_CodeLine->m_vec_Variable.size();

		uint f_CntVarFS = 0;
		while(f_CntVarFS < f_VarFSSize)
			{
			std::shared_ptr<Variable> f_VariableFS = f_CodeLine->m_vec_Variable[f_CntVarFS];

			f_CodeLine->m_vec_Variable[f_CntVarFS] = ac_VarByName(f_VariableFS);

			f_CntVarFS++;
			}

		switch(f_CodeLine->m_CodeLine)
			{
			case MuLine_Function:
				{
				if(f_CodeLine->m_Result_V != nullptr)
					{
					g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_Return_V = ac_VarByName(f_CodeLine->m_Result_V);

					for(int f_XY = 0; f_XY < g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable.size(); f_XY++)
						{
						g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY] = ac_VarByName(g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY]);
						}
					}
				else if(f_CodeLine->m_Result_CV != nullptr)
					{
#if 0
					g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_Return_CV = ac_VarByName(f_CodeLine->m_Result_CV);

					for(int f_XY = 0; f_XY < g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable.size(); f_XY++)
						{
						g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY] = ac_VarByName(g_Function[f_CodeLine->m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY]);
						}
#endif
					}
				else
					{
					g_Function[f_CodeLine->m_vec_Code[0]->m_ContractID]->m_Return_V = nullptr;

					for(int f_XY = 0; f_XY < g_Function[f_CodeLine->m_vec_Code[0]->m_ContractID]->m_vec_Variable.size(); f_XY++)
						{
						g_Function[f_CodeLine->m_vec_Code[0]->m_ContractID]->m_vec_Variable[f_XY] = ac_VarByName(g_Function[f_CodeLine->m_vec_Code[0]->m_ContractID]->m_vec_Variable[f_XY]);
						}
					}
				}break;
			}

		f_CntCodeFSLine++;
		}

	 ///////////////
	// Actions
	for(int f_Index = 0; f_Index < m_vec_Variable_Store.size(); f_Index++)
		{
		std::shared_ptr<Variable> f_Var = m_vec_Variable_Store[f_Index];

		if(f_Var->m_Action == MuAct_Random)
			{
			*(f_Var) = Cube::random();
			}
		else if(f_Var->m_Action == MuAct_RandInt)
			{
			*(f_Var) = Cube::randomFac();
			}
		else if(f_Var->m_Action == MuAct_Start)
			{
			/* Do Nothing */
			}
		else
			{
#ifdef ECOIN_SECURE
			throw;
#endif
			}
		}

}

void Contract::ac_ClearVars(void)
{
	m_vec_Variable_Store.clear();

	m_vec_ClassVar.clear();
}

void Contract::ac_LoadVars(void)
{
	m_vec_Variable_Store.push_back(m_System->Pos);
	m_vec_Variable_Store.push_back(m_System->Posx);
	m_vec_Variable_Store.push_back(m_System->Posy);
	m_vec_Variable_Store.push_back(m_System->Posz);
	m_vec_Variable_Store.push_back(m_System->Color);
	m_vec_Variable_Store.push_back(m_System->Matrix1);
	m_vec_Variable_Store.push_back(m_System->Matrix2);
	m_vec_Variable_Store.push_back(m_System->Matrix3);
	m_vec_Variable_Store.push_back(m_System->Matrix4);
	m_vec_Variable_Store.push_back(m_System->nonce);
}

#if 0
Cube::PixelShaderInput Contract::getWork(Cube::VertexShaderInput f_IN)
{	 ////////////////////////
	// Run the Contract
	float3 f_F3POS;
	f_F3POS.m_X = f_IN.pos.x;
	f_F3POS.m_Y = f_IN.pos.y;
	f_F3POS.m_Z = f_IN.pos.z;
	m_System->Pos->m_Var = f_F3POS;

	m_System->Posx->m_Var = f_IN.pos.x;
	m_System->Posy->m_Var = f_IN.pos.y;
	m_System->Posz->m_Var = f_IN.pos.z;

	float3 f_F3POSC;
	f_F3POSC.m_X = f_IN.color.r;
	f_F3POSC.m_Y = f_IN.color.g;
	f_F3POSC.m_Z = f_IN.color.b;
	m_System->Color->m_Var = f_F3POSC;

#ifdef ESL_RUNTIME
	if(m_Count == 0)
		{
		// Clear
		ac_ClearVars();
		// Load
		ac_LoadVars();
		// Setup
		ac_SetupVars();
		}

	uint f_CodeLineSize = g_Function[0]->m_vec_CodeLine.size();

	uint f_Cnt = 0;
	while(f_Cnt < f_CodeLineSize)
		{
		std::shared_ptr<CodeLine> f_CodeLine = g_Function[0]->m_vec_CodeLine[f_Cnt];

		if(f_CodeLine->m_Execute)
			{
			f_CodeLine->ac_Execute();

#if 0
			printf("ESL-Execute Line %i\n", f_Cnt);
#endif
			}

		f_Cnt++;
		}
#endif

	Cube::PixelShaderInput f_OUT;

	if(ag_any_cast<float>(m_System->Posx->m_Var) != ag_any_cast<float3>(m_System->Pos->m_Var).m_X)
		{
		f_OUT.pos.x = ag_any_cast<float>(m_System->Posx->m_Var);
		}
	else
		{
		f_OUT.pos.x = ag_any_cast<float3>(m_System->Pos->m_Var).m_X;
		}

	if(ag_any_cast<float>(m_System->Posy->m_Var) != ag_any_cast<float3>(m_System->Pos->m_Var).m_Y)
		{
		f_OUT.pos.y = ag_any_cast<float>(m_System->Posy->m_Var);
		}
	else
		{
		f_OUT.pos.y = ag_any_cast<float3>(m_System->Pos->m_Var).m_X;
		}

	if(ag_any_cast<float>(m_System->Posz->m_Var) != ag_any_cast<float3>(m_System->Posz->m_Var).m_X)
		{
		f_OUT.pos.z = ag_any_cast<float>(m_System->Posz->m_Var);
		}
	else
		{
		f_OUT.pos.z = ag_any_cast<float3>(m_System->Pos->m_Var).m_Z;
		}

	f_OUT.pos.w = 1.0f;

	float3 f_Float3 = ag_any_cast<float3>(m_System->Color->m_Var);

	f_OUT.color.r = f_Float3.m_X;
	f_OUT.color.g = f_Float3.m_Y;
	f_OUT.color.b = f_Float3.m_Z;

	m_Count++;

	return f_OUT;
}
#endif

void Contract::acWork(void)
{
	if(m_Count == 0)
		{
		// Clear
		ac_ClearVars();
		// Load
		ac_LoadVars();
		// Setup
		ac_SetupVars();
		}

	uint f_CodeLineSize = m_Frame_Function->m_vec_CodeLine.size();
	uint f_Cnt = 0;

	bool f_Scan = true;
	while(f_Scan == true)
		{
		std::shared_ptr<CodeLine> f_CodeLine = m_Frame_Function->m_vec_CodeLine[f_Cnt];

		if(f_CodeLine->m_Execute == true)
			{
			std::shared_ptr<ClassVar> f_ClassVar = f_CodeLine->ac_Execute(m_Frame_Function);

			if(f_ClassVar != nullptr)
				{
				m_vec_ClassVar.push_back(f_ClassVar);
				g_ClassVar.push_back(f_ClassVar);
				}
			else if(f_CodeLine->m_Result_V != nullptr)
				{
				m_Result_Variable = f_CodeLine->m_Result_V;

				f_Scan = false;
				}
			else if(f_CodeLine->m_Result_CV != nullptr)
				{
				m_Result_ClassVar = f_CodeLine->m_Result_CV;

				f_Scan = false;
				}
			}

		f_Cnt++;

		if(f_Cnt >= f_CodeLineSize)
			{
			f_Scan = false;
			}
		}

	//clear function scope
	m_vec_ClassVar.clear();

	m_Count++;
}

};