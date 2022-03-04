/*

CodeLine - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Code/Work/Contract.h"

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

CodeLine::CodeLine(std::string f_Line, uint f_CHK, System* f_System)
	{   ////////////////
	   ////////////////
	  // Construct
	 //
	//
	acClear();
	m_CodeString = f_Line;
	m_Chk = f_CHK;
	m_System = f_System;

	bool f_Scan = true;
	int f_Size = f_Line.size();

	if(m_Chk < f_Size - 6)
		{
		std::shared_ptr<Code> f_CodeB = std::make_shared<Code>(f_Line, m_Chk, 0);

		if (f_CodeB->m_Code_DigitA == '#' ||
			f_CodeB->m_Code_DigitB == '#' ||
			f_CodeB->m_Code_DigitC == '#')
			{
			f_Scan = false;
			}
		else
			{
			m_vec_Code.push_back(f_CodeB);
			}

		  //////////
		 //////////
		// END
		if(f_Scan)
			{
			m_END = f_CodeB->acDecide_END();
			m_Chk = f_CodeB->acDecide_MAX();

			uint f_Cntr = 1;

			while(f_Scan)
				{
				if(m_Chk < f_Line.size() - 6)
					{
					std::shared_ptr<Code> f_CodeA = std::make_shared<Code>(f_Line, m_Chk, f_Cntr);

					m_Chk = f_CodeA->m_Chk;

					if(f_CodeA->m_Code_DigitA == '/' &&
						f_CodeA->m_Code_DigitB == '/')
						{
						f_Scan = false;
						}

					if (f_CodeA->m_Code_DigitA == '#' ||
						f_CodeA->m_Code_DigitB == '#' ||
						f_CodeA->m_Code_DigitC == '#')
						{
						f_Scan = false;
						}
					else
						{
						m_vec_Code.push_back(f_CodeA);
						}
					}
				else
					{
					f_Scan = false;
					}

				f_Cntr++;
				}
			}
		}

	  //////////////////////
	 //////////////
	// Setup
	//
	//
	uint f_CodeSize = m_vec_Code.size();

	uint f_Count = 0;
	while(f_Count < f_CodeSize)
		{
		std::shared_ptr<Code> f_Code = m_vec_Code[f_Count];

		if(f_Code->m_Code_DigitB != '/' &&
			f_Code->m_Code_DigitB != '#')
			{
			switch(f_Code->m_Code)
				{
				case MuCode_Var:
					{
					int f_Type = 0;
					if(m_vec_Code.size() > 1)
						{
						if(f_Count == 0)
							{
							if(m_vec_Code[1]->m_Code == MuCode_Condition)
								{
								f_Type = 2;
								}
							}
						}
					
					if(f_Type <= 1)
						{
						if((m_CodeLine != MuLine_Assign_Opr) &&
							(m_CodeLine != MuLine_Function) &&
							(m_CodeLine != MuLine_Function_Frame) &&
							(m_CodeLine != MuLine_Function_Custom) &&
							(m_CodeLine != MuLine_Condition_Ajax) &&
							(m_CodeLine != MuCode_For_Loop))
							{
							m_CodeLine = MuLine_Assign;
							}

						std::shared_ptr<Variable> f_Var = std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code);
						m_vec_Variable.push_back(f_Var);

						if((f_Code->m_Number.size() == 1) && ((f_CodeSize == 1) || (f_Count > 1)))
							{
							if((m_CodeLine != MuLine_Assign_Opr) &&
								(m_CodeLine != MuLine_Function) &&
								(m_CodeLine != MuLine_Condition_Ajax))
								{
								m_CodeLine = MuLine_Init_Var;
								}

							std::shared_ptr<Variable> f_VarFRT = std::make_shared<Variable>("Con", MuCode_Constant);
							*(f_VarFRT) = *(f_Code->m_Number[0]->m_MxVar);
							m_vec_Variable.push_back(f_VarFRT);
							}
						}
					else
						{
						m_CodeLine = MuLine_Condition_Ajax;

						std::shared_ptr<Variable> f_Var = std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code);
						m_vec_Variable.push_back(f_Var);
						}
					}break;

				case MuCode_Function:
				case MuCode_FunctionStart:
					{
					m_CodeLine = MuLine_Function;

					if(f_Code->m_Type[0]->m_VarType == MuFunc_Custom)
						{	//////////////////////
						   // Custom Function
						m_CodeLine = MuLine_Function_Custom;
						}
					else if (f_Code->m_Type[0]->m_VarType == MuFunc_Frame)
						{
						m_CodeLine = MuLine_Function_Frame;
						}
					else	//////////////////////////////////////////////
						{  // Math and System and Other (already storage) Function Calls
						m_CodeLine = MuLine_Function;
						}

#if 0
					m_vec_Variable.push_back(f_Code->m_MxVar);
					m_vec_Variable.push_back(m_vec_Code[f_Code->m_Index + 1]->m_MxVar);
					m_vec_Variable.push_back(m_vec_Code[f_Code->m_Index + 2]->m_MxVar);
#endif
					}break;

				case MuCode_System:
					{
					if(f_Count > 0)
						{
						if((m_CodeLine != MuLine_Assign_Opr) &&
							(m_CodeLine != MuLine_Function) &&
							(m_CodeLine != MuLine_Function_Frame) &&
							(m_CodeLine != MuLine_Function_Custom) &&
							(m_CodeLine != MuLine_Condition_Ajax) &&
							(m_CodeLine != MuCode_For_Loop))
							{
							m_CodeLine = MuLine_Assign;
							}

						std::shared_ptr<Variable> f_Var = m_System->av_Var(f_Code->m_Name[0]->m_MxName);
						m_vec_Variable.push_back(f_Var);

						if(f_Code->m_Number.size() == 1 && f_CodeSize == 1)
							{
							if((m_CodeLine != MuLine_Assign_Opr) &&
								(m_CodeLine != MuLine_Function) &&
								(m_CodeLine != MuLine_Function_Frame) &&
								(m_CodeLine != MuLine_Function_Custom) &&
								(m_CodeLine != MuLine_Condition_Ajax) &&
								(m_CodeLine != MuCode_For_Loop))
								{
								m_CodeLine = MuLine_Init_Var;
								}

							std::shared_ptr<Variable> f_VarFRT = std::make_shared<Variable>("Con", MuCode_Constant);
							*(f_VarFRT) = *(f_Code->m_Number[0]->m_MxVar);
							m_vec_Variable.push_back(f_VarFRT);
							}
						}
					else
						{
						if((m_CodeLine != MuLine_Assign_Opr) &&
							(m_CodeLine != MuLine_Function) &&
							(m_CodeLine != MuLine_Function_Frame) &&
							(m_CodeLine != MuLine_Function_Custom) &&
							(m_CodeLine != MuLine_Condition_Ajax) &&
							(m_CodeLine != MuCode_For_Loop))
							{
							m_CodeLine = MuLine_Init_Var;
							}

						std::shared_ptr<Variable> f_Var = m_System->av_Var(f_Code->m_Name[0]->m_MxName);
						m_vec_Variable.push_back(f_Var);
						}
					}break;

				case MuCode_Constant:
					{
					if((m_CodeLine != MuLine_Assign_Opr) &&
						(m_CodeLine != MuLine_Function) &&
						(m_CodeLine != MuLine_Function_Frame) &&
						(m_CodeLine != MuLine_Function_Custom) &&
						(m_CodeLine != MuLine_Condition_Ajax) &&
						(m_CodeLine != MuCode_For_Loop))
						{
						m_CodeLine = MuLine_Init_Var;
						}

					std::shared_ptr<Variable> f_Var = std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, MuCode_Constant);
					m_vec_Variable.push_back(f_Var);

					if(f_Code->m_Number.size() == 1 && f_CodeSize == 1)
						{
						if((m_CodeLine != MuLine_Assign_Opr) &&
							(m_CodeLine != MuLine_Function) &&
							(m_CodeLine != MuLine_Function_Frame) &&
							(m_CodeLine != MuLine_Function_Custom) &&
							(m_CodeLine != MuLine_Condition_Ajax) &&
							(m_CodeLine != MuCode_For_Loop))
							{
							m_CodeLine = MuLine_Init_Var;
							}

						std::shared_ptr<Variable> f_VarFRT = std::make_shared<Variable>("Con", MuCode_Constant);
						*(f_VarFRT) = *(f_Code->m_Number[0]->m_MxVar);
						m_vec_Variable.push_back(f_VarFRT);
						}
					else if(f_Code->m_Number.size() > 1)
						{
#ifdef ECOIN_SECURE
						throw;
#endif
						}
					}break;

				case MuCode_For_Loop:
					{
					m_CodeLine = MuLine_For_Loop;

					if(f_Code->m_Param.size() > 0)
						{
						std::shared_ptr<Variable> f_VarFRT = std::make_shared<Variable>(f_Code->m_Param[0]->m_MxName, MuCode_Var);
						*(f_VarFRT) = *(f_Code->m_Param[0]->m_MxVar);
						m_vec_Variable.push_back(f_VarFRT);
						}

					if(f_Code->m_Param.size() > 1)
						{
						std::shared_ptr<Variable> f_VarFRT = std::make_shared<Variable>(f_Code->m_Param[1]->m_MxName, MuCode_Var);
						*(f_VarFRT) = *(f_Code->m_Param[0]->m_MxVar);
						m_vec_Variable.push_back(f_VarFRT);
						}
					}break;

				case MuCode_Operator:
					{
					m_CodeLine = MuLine_Assign_Opr;

					std::shared_ptr<Code> f_LtCode = m_vec_Code[f_Code->m_Index - 1];
					std::shared_ptr<Code> f_OpCode = m_vec_Code[f_Code->m_Index];
					std::shared_ptr<Code> f_RtCode = m_vec_Code[f_Code->m_Index + 1];

					std::shared_ptr<Operator> f_Operator = std::make_shared<Operator>(f_OpCode->m_MxName);

					f_Operator->m_Operator = f_OpCode->m_Type[0]->m_VarType;

					std::string f_StrCode = f_LtCode->m_MxName;
					std::string f_StrCodeName = f_LtCode->m_Name[0]->m_MxName;

					if(f_StrCode.compare("Sys") == 0)
						{
						if(f_StrCodeName.compare("Pos") == 0)
							{
							f_Operator->resultHand = m_System->Pos;
							m_vec_Variable.push_back(m_System->Pos);

							f_Operator->leftHand = m_System->Pos;
							m_vec_Variable.push_back(m_System->Pos);

#if 0
							f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
#endif
							f_Operator->rightHand = f_RtCode->m_Number[0]->m_MxVar;
							m_vec_Variable.push_back(f_Operator->rightHand);
							}
						if(f_StrCodeName.compare("Posx") == 0)
							{
							f_Operator->resultHand = m_System->Posx;
							m_vec_Variable.push_back(m_System->Posx);

							f_Operator->leftHand = m_System->Posx;
							m_vec_Variable.push_back(m_System->Posx);

#if 0
							f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
#endif
							f_Operator->rightHand = f_RtCode->m_Number[0]->m_MxVar;
							m_vec_Variable.push_back(f_Operator->rightHand);
							}
						if(f_StrCodeName.compare("Posy") == 0)
							{
							f_Operator->resultHand = m_System->Posy;
							m_vec_Variable.push_back(m_System->Posy);

							f_Operator->leftHand = m_System->Posy;
							m_vec_Variable.push_back(m_System->Posy);

#if 0
							f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
#endif
							f_Operator->rightHand = f_RtCode->m_Number[0]->m_MxVar;
							m_vec_Variable.push_back(f_Operator->rightHand);
							}
						if(f_StrCodeName.compare("Posz") == 0)
							{
							f_Operator->resultHand = m_System->Posz;
							m_vec_Variable.push_back(m_System->Posz);

							f_Operator->leftHand = m_System->Posz;
							m_vec_Variable.push_back(m_System->Posz);

#if 0
							f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
#endif
							f_Operator->rightHand = f_RtCode->m_Number[0]->m_MxVar;
							m_vec_Variable.push_back(f_Operator->rightHand);
							}
						else if(f_StrCodeName.compare("Color") == 0)
							{
							f_Operator->resultHand = m_System->Color;
							m_vec_Variable.push_back(m_System->Color);

							f_Operator->leftHand = m_System->Color;
							m_vec_Variable.push_back(m_System->Color);

#if 0
							f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
#endif
							f_Operator->rightHand = f_RtCode->m_MxVar;
							m_vec_Variable.push_back(f_Operator->rightHand);
							}
						}
					else if(f_StrCode.compare("Var") == 0)
						{
						f_Operator->resultHand = std::make_shared<Variable>(f_LtCode->m_Name[0]->m_MxName, f_LtCode->m_Code);
						m_vec_Variable.push_back(f_Operator->resultHand);

						f_Operator->leftHand = std::make_shared<Variable>(f_LtCode->m_Name[0]->m_MxName, f_LtCode->m_Code);
						m_vec_Variable.push_back(f_Operator->leftHand);

						if(f_RtCode->m_Number.size() >= 1)
							{
							f_Operator->rightHand = f_RtCode->m_Number[0]->m_MxVar;
							m_vec_Variable.push_back(f_Operator->rightHand);
							}
						else
							{
							f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
							m_vec_Variable.push_back(f_Operator->rightHand);
							}
						}
					else
						{
#ifdef ECOIN_SECURE
						throw;
#endif
						}

					m_vec_Operator.push_back(f_Operator);
					}break;

				case MuCode_Condition:
					{
					m_CodeLine = MuLine_Condition_Ajax;
					}break;

				case MuCode_Override:
					{ /////////////
					 /// Pause ///
					/////////////
					}break;
				}
			}

		f_Count++;
		}
	}

CodeLine::~CodeLine()
	{
	m_vec_Code.clear();
	m_vec_Variable.clear();
	m_vec_Operator.clear();
	}

int CodeLine::acSearch_CodeType(uint f_TYPE)
	{
	for(uint f_CT = 0; f_CT < m_vec_Code.size(); f_CT++)
		{
		std::shared_ptr<Code> f_Code = m_vec_Code[f_CT];

		if(f_Code->m_Code == f_TYPE)
			{
			return f_CT;
			}
		}

	return -5;
	}

void CodeLine::ac_Variable_Align(void)
{
	uint f_VarSize = m_vec_Variable.size();

	switch(m_CodeLine)
		{
#if 0
		case MuLine_Assign:
		case MuLine_Assign_Opr:
		case MuLine_Init_Var:
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
			}break;
#endif

		case MuLine_Condition_Ajax:
			{
			if(f_VarSize == 5)
				{
				if(m_vec_Variable[2]->m_MxName.compare("Con") == 0)
					{
					m_vec_Code[0]->m_MxVar = m_vec_Variable[0];
					m_vec_Code[2]->m_MxVar = m_vec_Variable[2];
					m_vec_Code[1]->m_Condition[0]->leftHand = m_vec_Variable[3];
					m_vec_Code[1]->m_Condition[0]->rightHand = m_vec_Variable[4];
					}
				else
					{
					throw;
					}
				}
			else if(f_VarSize == 2)
				{
				m_vec_Code[0]->m_MxVar = m_vec_Variable[0];
				m_vec_Code[2]->m_MxVar = m_vec_Variable[1];
				m_vec_Code[1]->m_Condition[0]->leftHand = m_vec_Variable[0];
				m_vec_Code[1]->m_Condition[0]->rightHand = m_vec_Variable[1];
				}
			else if(f_VarSize == 4)
				{
				m_vec_Code[0]->m_MxVar = m_vec_Variable[0];
				m_vec_Code[2]->m_MxVar = m_vec_Variable[1];
				m_vec_Code[1]->m_Condition[0]->leftHand = m_vec_Variable[2];
				m_vec_Code[1]->m_Condition[0]->rightHand = m_vec_Variable[3];
				}
			else
				{
				throw;
				}
			}break;

		case MuLine_Function:
		case MuLine_Function_Custom:
			{
			if(f_VarSize >= 1)
				{
				g_Function[m_vec_Code[1]->m_ContractID]->m_Return = m_vec_Variable[0];

				for(int f_XY = 0; f_XY < g_Function[m_vec_Code[1]->m_ContractID]->m_vec_Variable.size(); f_XY++)
					{
					g_Function[m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY] = m_vec_Variable[f_XY + 1];
					}
				}
			}break;
		}
}

bool CodeLine::ac_Execute(void)
{
	  //////////////////////
	 //////////////
	// Setup
	//
	//
	uint f_VarSize = m_vec_Code.size();

	if(f_VarSize == 0 ||
	   f_VarSize == 1)
		{
#ifdef ECOIN_SECURE
#if 0
			throw;
#else
			return false;
#endif
#endif
		}

#if 0
	printf("ESL_EXEC-f_VarSize %i m_CodeLine %i\n", f_VarSize, m_CodeLine);
#endif

	 //////////////////
	// Operator
	//
	if(m_CodeLine == MuLine_Assign_Opr)
		{
		if(m_vec_Operator.size() > 0)
			{
			uint f_OpSize = m_vec_Operator.size();

			uint f_Count = 0;
			while(f_Count < f_OpSize)
				{
				std::shared_ptr<Operator> f_Operator = m_vec_Operator[f_Count];

				f_Operator->ac_Execute();

				f_Count++;
				}
			} /////////////
		else
			{
#ifdef ECOIN_SECURE
			throw;
#endif
			}
		}    // Assign
	else if(m_CodeLine == MuLine_Assign)
		{
		if(f_VarSize == 0 ||
		   f_VarSize == 1)
			{
#ifdef ECOIN_SECURE
			throw;
#endif
			}
		else
			{
			if(f_VarSize == 2)
				{
				std::shared_ptr<Variable> f_VarA = m_vec_Variable[0];
				std::shared_ptr<Variable> f_VarB = m_vec_Variable[1];

				*(f_VarA) = *(f_VarB);
				}
			else
				{
				if(f_VarSize == 3)
					{
					std::shared_ptr<Variable> f_VarA = m_vec_Variable[0];
					std::shared_ptr<Variable> f_VarB = m_vec_Variable[1];
					std::shared_ptr<Variable> f_VarC = m_vec_Variable[2];

					*(f_VarA) = *(f_VarB);
					*(f_VarC) = *(f_VarB);
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					}
				}
			}
		}
	else if(m_CodeLine == MuLine_Condition_Ajax)
		{
		std::shared_ptr<Condition> f_Condition = m_vec_Code[1]->m_Condition[0];
		f_Condition->ac_Execute();
		}
	else if(m_CodeLine == MuLine_Init_Var)
		{
		if(f_VarSize == 0 ||
		   f_VarSize == 1)
			{
#ifdef ECOIN_SECURE
			throw;
#endif
			}
		else
			{
			if(f_VarSize == 2)
				{
				std::shared_ptr<Variable> f_VarRes = m_vec_Variable[0];
				std::shared_ptr<Variable> f_VarB = m_vec_Variable[1];

				*(f_VarRes) = *(f_VarB);
				}
			else
				{
				if(f_VarSize == 3)
					{
					std::shared_ptr<Variable> f_VarRes = m_vec_Variable[0];
					std::shared_ptr<Variable> f_VarB = m_vec_Variable[1];
					std::shared_ptr<Variable> f_VarC = m_vec_Variable[2];

					*(f_VarRes) = *(f_VarB);
					*(f_VarB) = *(f_VarC);
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					}
				}
			}
		}
	else if(m_CodeLine == MuLine_Function)
		{
		std::shared_ptr<Function> f_Function = g_systemFunction[m_vec_Code[0]->m_ContractID];
		f_Function->acExecute();
		}
	else if(m_CodeLine == MuLine_Function_Custom)
		{
		std::shared_ptr<Function> f_Function = g_Function[m_vec_Code[0]->m_ContractID];
		f_Function->acExecute();
		}
	else if(m_CodeLine == MuLine_For_Loop)
		{
		int f_ParamCount = m_vec_Code[0]->m_Param.size();
		if(f_ParamCount == 1)
			{
			std::shared_ptr<Variable> f_VarCount = m_vec_Variable[0];

			int f_Count = 0;

			if(f_VarCount->m_Var.type() == typeid(int))
				{
				f_Count = ag_any_cast<int>(f_VarCount->m_Var);
				}
			else
				{
#ifdef ECOIN_SECURE
				throw;
#endif
				}

			if(f_Count < 0)
				{
#ifdef ECOIN_SECURE
				throw;
#endif
				}

			std::shared_ptr<Function> f_Function = g_Function[m_vec_Code[0]->m_ContractID];

			for(int f_XY = 0; f_XY < f_Count; f_XY++)
				{
				f_Function->acExecute();
				}
			}
		else if(f_ParamCount == 2)
			{
			std::shared_ptr<Variable> f_VarCountVar = m_vec_Variable[0];
			std::shared_ptr<Variable> f_VarCount = m_vec_Variable[1];

			int f_Count = 0;

			if(f_VarCount->m_Var.type() == typeid(int))
				{
				f_Count = ag_any_cast<int>(f_VarCount->m_Var);
				}
			else
				{
#ifdef ECOIN_SECURE
				throw;
#endif
				}

			if(f_Count < 0)
				{
#ifdef ECOIN_SECURE
				throw;
#endif
				}

			std::shared_ptr<Function> f_Function = g_Function[m_vec_Code[0]->m_ContractID];

			for(int f_XY = 0; f_XY < f_Count; f_XY++)
				{
				*(f_VarCountVar) = f_XY;
				f_Function->acExecute();
				}
			}
		else
			{
#ifdef ECOIN_SECURE
			throw;
#endif
			}
		}

	return true;
}

std::string CodeLine::ac_Print(void)
{
	return m_CodeString;
}

};