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

#include "Class.h"

using namespace ecoin;

namespace ecoin
{
std::shared_ptr<ClassVar> g_BaseNode;
std::vector<std::shared_ptr<ClassVar>> g_vec_BaseNode;

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

		if((f_Code->m_Code_DigitB != '/') &&
			(f_Code->m_Code_DigitB != '#'))
			{
			switch(f_Code->m_Code)
				{
				case MuCode_Var:	//var socket...accepts Variable stdptr from result of either
					{
					f_Code->acPrepare_CallNames();

					if(f_Count == 0)
						{
						if(f_CodeSize == 3)
							{
							std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

							if(f_CodePositionOne->m_Code == MuCode_Condition)
								{
								m_CodeLine = MuLine_Condition_Ajax;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionOne->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;

								if(f_CodePositionOne->m_Code == MuCode_Function)
									{
									if(f_Code->m_Number.size() > 0)
										{
										//m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
										throw;
										}
									else
										{
										m_Result_V = std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code);

										m_Returning = true;
										}
									}
								}
							else if(f_CodePositionOne->m_Code == MuCode_Operator)
								{
								m_CodeLine = MuLine_Assign_Opr;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							}
						else if(f_CodeSize == 1)
							{
							m_CodeLine = MuLine_Init_Var;

							if(f_Code->m_Number.size() > 0)
								{
								m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
								}
							else
								{ //mebbe add debug message int var no number or ignore
								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							}
						else if(f_CodeSize == 2)
							{
							std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

							if(f_Code->m_Code == MuCode_Return)
								{
								m_CodeLine = MuLine_Function_Return; //not possible
								}
							else if(f_Code->m_Code == MuCode_Template)
								{
								m_CodeLine = MuLine_Template; //not possible
								}
							else if(f_CodePositionOne->m_Code == MuLine_Function)
								{
								m_CodeLine = MuLine_Function;

								if(f_Code->m_Number.size() > 0)
									{
									//m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									throw;
									}
								else
									{
									m_Result_V = std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code);

									m_Returning = true;
									}
								}
							else
								{
								m_CodeLine = MuLine_Assign;

								m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
								}
							}
						else if(f_CodeSize == 4)
							{
							std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

							if(f_CodePositionOne->m_Code == MuLine_Function)
								{
								m_CodeLine = MuLine_Function;

								if(f_Code->m_Number.size() > 0)
									{
									//m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									throw;
									}
								else
									{
									m_Result_V = std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code);

									m_Returning = true;
									}
								}
							else if(f_Code->m_Code == MuCode_For_Loop)
								{
								m_CodeLine = MuLine_For_Loop;
								}
							else
								{
								throw; //also line length exceeded
								}
							}
						else
							{
							throw; //add debug message multiple operators and conditions not yet implemented please reduce line length
							}
						}
					else if(f_Count == 1) //position one
						{
						if(f_CodeSize == 3)
							{
							std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];

							if(f_CodePositionZero->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_FunctionStart)
								{
								m_CodeLine = MuLine_Function_Custom;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_ClassVar)
								{
								m_CodeLine = MuLine_Init_ClassVar;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_Code->m_Code == MuCode_Operator)
								{
								m_CodeLine = MuLine_Assign_Opr;
								}
							}
						else if(f_CodeSize == 1)
							{
							throw; //add debug message impossible
							}
						else if(f_CodeSize == 2)
							{
							std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];

							if(f_CodePositionZero->m_Code == MuCode_Template)
								{
								m_CodeLine = MuLine_Template; //not possible

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_FunctionStart)
								{
								m_CodeLine = MuLine_Function_Custom;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_Return)
								{
								m_CodeLine = MuLine_Function_Return;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else
								{
								m_CodeLine = MuLine_Assign;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							}
						else if(f_CodeSize == 4)
							{
							std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];

							if(f_CodePositionZero->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_FunctionStart)
								{
								m_CodeLine = MuLine_Function_Custom;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_Return)
								{
								m_CodeLine = MuLine_Function_Return;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_For_Loop)
								{
								m_CodeLine = MuLine_For_Loop;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							}
						}
					else if(f_Count == 2)
						{
						if(f_CodeSize == 3)
							{
							std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];
							std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

							if(f_CodePositionOne->m_Code == MuCode_Condition)
								{
								m_CodeLine = MuLine_Condition_Ajax;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionOne->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_FunctionStart)
								{
								m_CodeLine = MuLine_Function_Custom;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_ClassVar)
								{
								m_CodeLine = MuLine_Init_ClassVar;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							}
						else if(f_CodeSize == 1)
							{
							throw; //add debug message impossible
							}
						else if(f_CodeSize == 2)
							{
							throw; //add debug message impossible
							}
						else if(f_CodeSize == 4)
							{
							std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

							if(m_CodeLine == MuLine_Function)
								{
								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_Code->m_Code == MuCode_For_Loop)
								{
								m_CodeLine = MuLine_For_Loop;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else
								{
								throw; //also line length exceeded
								}
							}
						else
							{
							throw; //add debug message multiple operators and conditions not yet implemented please reduce line length
							}
						}
					else if(f_Count == 3)
						{
						if(f_CodeSize == 3)
							{
							throw; //add debug messages impossible
							}
						else if(f_CodeSize == 1)
							{
							throw; //add debug message impossible
							}
						else if(f_CodeSize == 2)
							{
							throw; //add debug message impossible
							}
						else if(f_CodeSize == 4)
							{
							std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];
							std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[0];

							if((f_CodePositionOne->m_Code == MuCode_Function) || (f_CodePositionZero->m_Code == MuCode_Function))
								{
								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else if(f_CodePositionZero->m_Code == MuCode_For_Loop)
								{
								m_CodeLine = MuLine_For_Loop;

								if(f_Code->m_Number.size() > 0)
									{
									m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
									}
								else
									{
									m_vec_Variable.push_back(std::make_shared<Variable>(f_Code->m_Name[0]->m_MxName, f_Code->m_Code));
									}
								}
							else
								{
								throw; //also line length exceeded
								}
							}
						else
							{
							throw; //add debug message multiple operators and conditions not yet implemented please reduce line length
							}
						}
					else
						{
						throw; //add debug message
						}
					}break;

				case MuCode_ClassVar:
					{
					if(f_Count == 0)
						{
						if(f_CodeSize == 1)
							{
							m_CodeLine = MuLine_Init_ClassVar;
							}
						else if(f_CodeSize == 2)
							{
							std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[0];

							if(f_Code->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;
								}
							else if(f_CodePositionOne->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;
								}
							else
								{
								m_CodeLine = MuLine_Init_ClassVar;
								}
							}
						else if(f_CodeSize == 3)
							{
							if(f_Code->m_Code == MuCode_FunctionStart)
								{
								m_CodeLine = MuLine_Function;
								}
							}
						else if(f_CodeSize == 4)
							{
							m_CodeLine = MuLine_Function;
							}
						}
					else if(f_Count == 1)
						{
						if(f_CodeSize == 2)
							{
							std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];

							if(f_CodePositionZero->m_Code == MuCode_Return)
								{
								m_CodeLine = MuLine_Function_Return;

								m_Returning = true;
								}
							else if(f_CodePositionZero->m_Code == MuCode_Template)
								{
								m_CodeLine = MuLine_Template;
								}
							else if(f_CodePositionZero->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;
								}
							else
								{
								m_CodeLine = MuLine_Init_ClassVar;
								}
							}
						else if(f_CodeSize == 3)
							{
							std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];

							if(f_CodePositionZero->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;
								}
							else if(f_Code->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;
								}
							}
						else if(f_CodeSize == 1)
							{
							throw; //add debug message impossible
							}
						else if(f_CodeSize == 4)
							{
							m_CodeLine = MuLine_Function;
							}
						}
					else if(f_Count == 2)
						{
						if(f_CodeSize == 2)
							{
							throw; //add debug message impossible
							}
						else if(f_CodeSize == 3)
							{
							std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];
							std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];

							if(f_CodePositionZero->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;
								}
							else if(f_CodePositionOne->m_Code == MuCode_Function)
								{
								m_CodeLine = MuLine_Function;
								}
							}
						else if(f_CodeSize == 1)
							{
							throw; //add debug message impossible
							}
						else if(f_CodeSize == 4)
							{
							m_CodeLine = MuLine_Function;
							}
						}
					else if(f_Count == 3)
						{
						if(f_CodeSize == 2)
							{
							throw; //add debug message impossible
							}
						else if(f_CodeSize == 3)
							{
							throw; //add debug message
							}
						else if(f_CodeSize == 1)
							{
							throw; //add debug message impossible
							}
						else if(f_CodeSize == 4)
							{
							m_CodeLine = MuLine_Function;
							}
						}
					//pass no vars...?
					}break;

				case MuCode_Function:
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

					}break;

				case MuCode_FunctionStart:
					{
					m_CodeLine = MuLine_Function_Custom;

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

					}break;
					
				case MuCode_ClassDef:
					{
					m_CodeLine = MuLine_ClassDef;
					}break;

				case MuCode_System:
					{
					if(f_Count > 0)
						{
						if((m_CodeLine != MuLine_Init_ClassVar) && 
							(m_CodeLine != MuLine_Assign_Opr) &&
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
							if((m_CodeLine != MuLine_Init_ClassVar) && 
								(m_CodeLine != MuLine_Assign_Opr) &&
								(m_CodeLine != MuLine_Function) &&
								(m_CodeLine != MuLine_Function_Frame) &&
								(m_CodeLine != MuLine_Function_Custom) &&
								(m_CodeLine != MuLine_Condition_Ajax) &&
								(m_CodeLine != MuCode_For_Loop))
								{
								m_CodeLine = MuLine_Init_Var;
								}

							m_vec_Variable.push_back(f_Code->m_Number[0]->m_MxVar);
							}
						}
					else
						{
						if((m_CodeLine != MuLine_Init_ClassVar) && 
							(m_CodeLine != MuLine_Assign_Opr) &&
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
					if((m_CodeLine != MuLine_Init_ClassVar) && 
						(m_CodeLine != MuLine_Assign_Opr) &&
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
						if((m_CodeLine != MuLine_Init_ClassVar) && 
							(m_CodeLine != MuLine_Assign_Opr) &&
							(m_CodeLine != MuLine_Function) &&
							(m_CodeLine != MuLine_Function_Frame) &&
							(m_CodeLine != MuLine_Function_Custom) &&
							(m_CodeLine != MuLine_Condition_Ajax) &&
							(m_CodeLine != MuCode_For_Loop))
							{
							m_CodeLine = MuLine_Init_Var;
							}

						f_Var->CloneVar(f_Code->m_Number[0]->m_MxVar);
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

					std::string f_L_StrCode = f_LtCode->m_MxName;
					std::string f_R_StrCode = f_RtCode->m_MxName;
					std::string f_L_StrCodeName = f_LtCode->m_Name[0]->m_MxName;
					std::string f_R_StrCodeName = f_RtCode->m_Name[0]->m_MxName;

					if(f_LtCode->m_vec_NameCall.size() == 1)
						{
						if(f_L_StrCode.compare("Sys") == 0)
							{
							if(f_L_StrCodeName.compare("Pos") == 0)
								{
								f_Operator->leftHand = m_System->Pos;
								m_vec_Variable.push_back(m_System->Pos);
								}
							if(f_L_StrCodeName.compare("Posx") == 0)
								{
								f_Operator->leftHand = m_System->Posx;
								m_vec_Variable.push_back(m_System->Posx);
								}
							if(f_L_StrCodeName.compare("Posy") == 0)
								{
								f_Operator->leftHand = m_System->Posy;
								m_vec_Variable.push_back(m_System->Posy);
								}
							if(f_L_StrCodeName.compare("Posz") == 0)
								{
								f_Operator->leftHand = m_System->Posz;
								m_vec_Variable.push_back(m_System->Posz);
								}
							else if(f_L_StrCodeName.compare("Color") == 0)
								{
								f_Operator->leftHand = m_System->Color;
								m_vec_Variable.push_back(m_System->Color);
								}
							}
						else if(f_L_StrCode.compare("Var") == 0)
							{
							f_Operator->leftHand = std::make_shared<Variable>(f_LtCode->m_Name[0]->m_MxName, f_LtCode->m_Code);
							m_vec_Variable.push_back(f_Operator->leftHand);
							}
						else
							{
#ifdef ECOIN_SECURE
							throw;
#endif
							}
						}
					else if(f_LtCode->m_vec_NameCall.size() == 2) //assign to classvar var
						{
						if(f_L_StrCode.compare("Var") == 0)
							{
							f_Operator->leftHand = std::make_shared<Variable>(f_LtCode->m_Name[0]->m_MxName, f_LtCode->m_Code);

							for(int f_Jet = 0; f_Jet < f_LtCode->m_vec_NameCall.size(); f_Jet++)
								{
								f_Operator->leftHand->m_vec_NameCall.push_back(f_LtCode->m_vec_NameCall[f_Jet]);
								}

							m_vec_Variable.push_back(f_Operator->leftHand);
							}
						else
							{
#ifdef ECOIN_SECURE
							throw;
#endif
							}
						}
					else
						{
#ifdef ECOIN_SECURE
						throw;
#endif
						}

					if(f_RtCode->m_vec_NameCall.size() == 1)
						{
						if(f_R_StrCode.compare("Sys") == 0)
							{
							if(f_R_StrCodeName.compare("Pos") == 0)
								{
								f_Operator->rightHand = f_RtCode->m_Number[0]->m_MxVar;
								m_vec_Variable.push_back(f_Operator->rightHand);
#if 0
								f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
#endif
								}
							else if(f_R_StrCodeName.compare("Posx") == 0)
								{
#if 0
								f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
#endif
								f_Operator->rightHand = f_RtCode->m_Number[0]->m_MxVar;
								m_vec_Variable.push_back(f_Operator->rightHand);
								}
							else if(f_R_StrCodeName.compare("Posy") == 0)
								{
#if 0
								f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
#endif
								f_Operator->rightHand = f_RtCode->m_Number[0]->m_MxVar;
								m_vec_Variable.push_back(f_Operator->rightHand);
								}
							else if(f_R_StrCodeName.compare("Posz") == 0)
								{
#if 0
								f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
#endif
								f_Operator->rightHand = f_RtCode->m_Number[0]->m_MxVar;
								m_vec_Variable.push_back(f_Operator->rightHand);
								}
							else if(f_R_StrCodeName.compare("Color") == 0)
								{
#if 0
								f_Operator->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
#endif
								f_Operator->rightHand = f_RtCode->m_MxVar;
								m_vec_Variable.push_back(f_Operator->rightHand);
								}
							else
								{
								throw; //add system not found
								}
							}
						else if(f_R_StrCode.compare("Var") == 0)
							{
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
							throw; //
#endif
							}
						}
					else if(f_RtCode->m_vec_NameCall.size() == 2) //assign to classvar var
						{
						if(f_R_StrCode.compare("Var") == 0)
							{
							f_Operator->leftHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_LtCode->m_Code);

							for(int f_Jet = 0; f_Jet < f_RtCode->m_vec_NameCall.size(); f_Jet++)
								{
								f_Operator->leftHand->m_vec_NameCall.push_back(f_RtCode->m_vec_NameCall[f_Jet]);
								}

							m_vec_Variable.push_back(f_Operator->leftHand);
							}
						else
							{
#ifdef ECOIN_SECURE
							throw;
#endif
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
			{
			if(f_VarSize >= 1)
				{
				if(g_Function[m_vec_Code[1]->m_ContractID]->m_Return_V != nullptr)
					{
					g_Function[m_vec_Code[1]->m_ContractID]->m_Return_V = m_Result_V;

					for(int f_XY = 0; f_XY < g_Function[m_vec_Code[1]->m_ContractID]->m_vec_Variable.size(); f_XY++)
						{
						g_Function[m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY] = m_vec_Variable[f_XY];
						}
					}
				else if(g_Function[m_vec_Code[1]->m_ContractID]->m_Return_CV != nullptr)
					{
					g_Function[m_vec_Code[1]->m_ContractID]->m_Return_CV = m_Result_CV;

					for(int f_XY = 0; f_XY < g_Function[m_vec_Code[1]->m_ContractID]->m_vec_Variable.size(); f_XY++)
						{
						g_Function[m_vec_Code[1]->m_ContractID]->m_vec_Variable[f_XY] = m_vec_Variable[f_XY];
						}
					}
				else //no return
					{
					for(int f_XY = 0; f_XY < g_Function[m_vec_Code[0]->m_ContractID]->m_vec_Variable.size(); f_XY++)
						{
						g_Function[m_vec_Code[0]->m_ContractID]->m_vec_Variable[f_XY] = m_vec_Variable[f_XY];
						}
					}
				}
			}break;

		case MuLine_Function_Custom:
			{
			for(int f_XY = 0; f_XY < g_Function[m_vec_Code[0]->m_ContractID]->m_vec_Variable.size(); f_XY++)
				{
				g_Function[m_vec_Code[0]->m_ContractID]->m_vec_Variable[f_XY] = m_vec_Variable[f_XY];
				}
			}break;
		}
}

std::shared_ptr<Variable> Code::acCodeCall_Var(int f_Index, int f_MaxIndex, std::shared_ptr<Function> f_Function, int f_FindIndexInt)
{
	switch(m_vec_NameCallType[f_Index])
		{
		case MuNameCall_Type_VarVar:
			{
			if(f_FindIndexInt == 0)
				{
				std::shared_ptr<Variable> f_Var = f_Function->acFind_Var(m_vec_NameCall[f_Index]);

				if(f_Var == nullptr)
					{
					f_Var = ag_Find_Var(m_vec_NameCall[f_Index]);
					}

				if(f_Var == nullptr)
					{
					throw; //add debug message var not found
					}
				else
					{
					return f_Var;  //win!
					}
				}
			else  //is array index varint check for integer
				{
				throw;
				}
			}break;

		case MuNameCall_Type_VarIndexInt:
			{
			if(f_FindIndexInt == 0)
				{
				throw; //add debug message integer index var out of position
				}
			else if(f_FindIndexInt == 1)  //is array index varint check for integer
				{
				std::shared_ptr<Variable> f_VarIndexInt = f_Function->acFind_Var(m_vec_NameCall[f_Index]);

				if(f_VarIndexInt == nullptr)
					{
					f_VarIndexInt = ag_Find_Var(m_vec_NameCall[f_Index]);
					}

				if(f_VarIndexInt == nullptr)
					{
					throw; //add debug message var not found
					}
				else
					{
					f_FindIndexInt--;

					if(f_Index >= f_MaxIndex)	//win conditions!
						{
						int f_Ind = ag_any_cast<int>(f_VarIndexInt->m_Var);

						if((f_Ind < 0) || (f_Ind >= g_vec_BaseNode[g_vec_BaseNode.size() - 1]->m_Class->m_vec_Variable.size()))
							{
							throw; //add debug message array index out of bounds
							}

						return g_vec_BaseNode[g_vec_BaseNode.size() - 1]->m_Class->m_vec_Variable[f_Ind];
						}
					else
						{
						int f_Ind = ag_any_cast<int>(f_VarIndexInt->m_Var);

						if((f_Ind < 0) || (f_Ind >= g_BaseNode->m_Class->m_vec_ClassVar.size()))
							{
							throw; //add debug message classvar array index out of bounds
							}

						g_BaseNode = g_BaseNode->m_Class->m_vec_ClassVar[ag_any_cast<int>(f_VarIndexInt->m_Var)];

						g_vec_BaseNode.push_back(g_BaseNode);

						return acCodeCall_Var(f_Index + 1, f_MaxIndex, f_Function, f_FindIndexInt + 1);
						}

					return f_VarIndexInt;
					}
				}
			else
				{
				throw; //no native vector error
				}
			}break;

		case MuNameCall_Type_MemberVar:
			{
			if(f_Index == 0)	//1 place classvar
				{
				throw; //add debug message membervar not found
				}
			
			if(f_Index >= f_MaxIndex) //win conditions race winner
				{
				std::shared_ptr<Variable> f_Var = g_BaseNode->m_Class->acFindVar(m_vec_NameCall[f_Index]);

				if(f_Var == nullptr)
					{
					f_Var = ag_Find_Var(m_vec_NameCall[f_Index]);

					if(f_Var == nullptr)
						{
						throw; //add debug message variable member not found
						}
					else
						{
						return f_Var;
						}
					}
				else
					{
					return f_Var;
					}
				}
			else  //'assume' evector calculate number of indices
				{
				g_BaseNode = g_BaseNode->m_Class->acFindClassVar(m_vec_NameCall[f_Index]);

				g_vec_BaseNode.push_back(g_BaseNode);

				return acCodeCall_Var(f_Index + 1, f_MaxIndex, f_Function, f_FindIndexInt + 1);
				}
			}break;

		case MuNameCall_Type_MemberIndexInt:
			{
			if(f_FindIndexInt == 0)
				{
				throw; //add debug message integer index var out of position
				}
			else if(f_FindIndexInt == 1)  //is array index varint check for integer member var
				{
				std::shared_ptr<Variable> f_MemberVarIndexInt = g_BaseNode->m_Class->acFindVar(m_vec_NameCall[f_Index]);

				if(f_MemberVarIndexInt == nullptr)
					{
					throw; //add debug message var not found
					}
				else
					{
					f_FindIndexInt--;

					if(f_Index >= f_MaxIndex) //win conditions!
						{
						return g_vec_BaseNode[g_vec_BaseNode.size() - 1]->m_Class->m_vec_Variable[ag_any_cast<int>(f_MemberVarIndexInt->m_Var)];
						}
					else
						{
						g_BaseNode = g_BaseNode->m_Class->acFindClassVar(m_vec_NameCall[f_Index]);

						g_vec_BaseNode.push_back(g_BaseNode);

						return acCodeCall_Var(f_Index + 1, f_MaxIndex, f_Function, f_FindIndexInt);
						}
					}
				}
			else //findindexint runaway vector assignment error
				{
				throw; //add debug message no native array
				}
			}break;

		case MuNameCall_Type_ClassVar:
			{
			if(f_Index == 0)	//1 place classvar
				{
				std::shared_ptr<ClassVar> f_ClassVar = f_Function->acFind_ClassVar(m_vec_NameCall[f_Index]);

				if(f_ClassVar == nullptr)
					{
					f_ClassVar = ag_Find_ClassVar(m_vec_NameCall[f_Index]);
					}

				if(f_ClassVar == nullptr)
					{
					throw; //add debug message classvar not found
					}
				else
					{
					g_BaseNode = f_ClassVar;
					}
				}
			
			if(f_Index >= f_MaxIndex) //!!!win conditions!
				{
				if(f_FindIndexInt == 1)
					{
					throw; //add debuging message currently classvar at var socket syntax error
					}
				else if(f_FindIndexInt > 1)
					{
					throw; //add debuging message currently classvar at var socket syntax error
					}
				}
			else
				{
				if(f_FindIndexInt == 0)
					{
					g_BaseNode = g_BaseNode->m_Class->acFindClassVar(m_vec_NameCall[f_Index]);

					return acCodeCall_Var(f_Index + 1, f_MaxIndex, f_Function, f_FindIndexInt);
					}
				if(f_FindIndexInt == 1)
					{
					g_BaseNode = g_BaseNode->m_Class->acFindClassVar(m_vec_NameCall[f_Index]);

					return acCodeCall_Var(f_Index + 1, f_MaxIndex, f_Function, f_FindIndexInt);
					}
				else
					{
					throw; //add debuging message find index int above 1
					}
				}
			}break;
		}
}

std::shared_ptr<ClassVar> CodeLine::ac_Execute(std::shared_ptr<Function> f_Function)
{
	  //////////////////////
	 //////////////
	// Setup
	//
	//
	uint f_VarSize = m_vec_Code.size();

#if 0
	if(f_VarSize == 0 ||
	   f_VarSize == 1)
		{
#ifdef ECOIN_SECURE
#if 0
			throw;
#else
			return nullptr;
#endif
#endif
		}
#endif

#if 0
	printf("ESL_EXEC-f_VarSize %i m_CodeLine %i\n", f_VarSize, m_CodeLine);
#endif

	std::shared_ptr<Code> f_CodeL = m_vec_Code[0];
	std::shared_ptr<Code> f_CodeR = m_vec_Code[m_vec_Code.size() - 1];

	 //////////////////
	// Operator
	//
	if(m_CodeLine == MuLine_Assign_Opr)
		{
		if(m_vec_Operator.size() > 0)
			{
			std::shared_ptr<Variable> f_LeftHandSide = nullptr;
			std::shared_ptr<Variable> f_RightHandSide = nullptr;

			if(f_VarSize == 2)
				{
				uint f_OpSize = m_vec_Operator.size();

				uint f_Count = 0;
				while(f_Count < f_OpSize)
					{
					std::shared_ptr<Operator> f_Operator = m_vec_Operator[f_Count];

					std::shared_ptr<Variable> f_VarCall_L = f_CodeL->acCodeCall_Var(0, f_CodeL->m_vec_NameCall.size(), f_Function);
					std::shared_ptr<Variable> f_VarCall_R = f_CodeR->acCodeCall_Var(0, f_CodeR->m_vec_NameCall.size(), f_Function);

					if(f_VarCall_L == nullptr)
						{
						throw; //add debuging message variable assignation left hand variable not found
						}
					else
						{
						f_Operator->leftHand = f_VarCall_L;
						}

					if(f_VarCall_R == nullptr)
						{
						throw; //add debuging message variable assignation result hand variable not found
						}
					else
						{
						f_Operator->rightHand = f_VarCall_R;
						}

					f_Operator->ac_Execute();

					f_Count++;
					}
				}
			else
				{
				throw; //add debug message variable assignation var count out of range
				}
			}
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

				std::shared_ptr<Variable> f_VarCall_L = f_CodeL->acCodeCall_Var(0, f_CodeL->m_vec_NameCall.size(), f_Function);
				std::shared_ptr<Variable> f_VarCall_R = f_CodeR->acCodeCall_Var(0, f_CodeR->m_vec_NameCall.size(), f_Function);

				if(f_VarCall_L == nullptr)
					{
					throw; //add debuging message variable assignation left hand variable not found
					}

				if(f_VarCall_R == nullptr)
					{
					throw; //add debuging message variable assignation result hand variable not found
					}

				f_VarCall_L->CloneVar(f_VarCall_R);
				}
			else
				{
				if(f_VarSize == 3)
					{
					std::shared_ptr<Variable> f_VarA = m_vec_Variable[0];
					std::shared_ptr<Variable> f_VarB = m_vec_Variable[1];
					std::shared_ptr<Variable> f_VarC = m_vec_Variable[2];

					std::shared_ptr<Variable> f_VarCall_A = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), f_Function);
					std::shared_ptr<Variable> f_VarCall_B = m_vec_Code[1]->acCodeCall_Var(0, m_vec_Code[1]->m_vec_NameCall.size(), f_Function);
					std::shared_ptr<Variable> f_VarCall_C = m_vec_Code[2]->acCodeCall_Var(0, m_vec_Code[2]->m_vec_NameCall.size(), f_Function);

					if(f_VarCall_A == nullptr)
						{
						throw; //add debuging message variable assignation left hand variable not found
						}

					if(f_VarCall_B == nullptr)
						{
						throw; //add debuging message variable assignation mid hand variable not found
						}

					if(f_VarCall_C == nullptr)
						{
						throw; //add debuging message variable assignation result hand variable not found
						}

					f_VarCall_A->CloneVar(f_VarCall_B);
					f_VarCall_B->CloneVar(f_VarCall_C);
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

				std::shared_ptr<Variable> f_VarCall_L = f_CodeL->acCodeCall_Var(0, f_CodeL->m_vec_NameCall.size(), f_Function);
				std::shared_ptr<Variable> f_VarCall_R = f_CodeR->acCodeCall_Var(0, f_CodeR->m_vec_NameCall.size(), f_Function);

				if(f_VarCall_L == nullptr)
					{
					throw; //add debuging message variable assignation left hand variable not found
					}

				if(f_VarCall_R == nullptr)
					{
					throw; //add debuging message variable assignation result hand variable not found
					}

				f_VarCall_L->CloneVar(f_VarCall_R);
				}
			else
				{
				if(f_VarSize == 3)
					{
					std::shared_ptr<Variable> f_VarRes = m_vec_Variable[0];
					std::shared_ptr<Variable> f_VarB = m_vec_Variable[1];
					std::shared_ptr<Variable> f_VarC = m_vec_Variable[2];

					std::shared_ptr<Variable> f_VarCall_A = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), f_Function);
					std::shared_ptr<Variable> f_VarCall_B = m_vec_Code[1]->acCodeCall_Var(0, m_vec_Code[1]->m_vec_NameCall.size(), f_Function);
					std::shared_ptr<Variable> f_VarCall_C = m_vec_Code[2]->acCodeCall_Var(0, m_vec_Code[2]->m_vec_NameCall.size(), f_Function);

					if(f_VarCall_A == nullptr)
						{
						throw; //add debuging message variable assignation left hand variable not found
						}

					if(f_VarCall_B == nullptr)
						{
						throw; //add debuging message variable assignation mid hand variable not found
						}

					if(f_VarCall_C == nullptr)
						{
						throw; //add debuging message variable assignation result hand variable not found
						}

					f_VarCall_A->CloneVar(f_VarCall_B);
					f_VarCall_B->CloneVar(f_VarCall_C);
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
		if(m_vec_Code[0]->m_Code == MuCode_Function)
			{
			if((m_vec_Code[0]->m_Type[0]->m_VarType >= MuFunc_Custom) && (m_vec_Code[0]->m_Type[0]->m_VarType < MuSetGLOBAL_))
				{
				std::shared_ptr<Function> f_Function = m_vec_Code[0]->m_FunctionLink;

				f_Function->acExecute();

				m_Result_V = f_Function->m_Return_V;
				m_Result_CV = f_Function->m_Return_CV;
				}
			else
				{
				throw; //add debug message functype out of range
				}
			}
		else if(m_vec_Code[1]->m_Code == MuCode_Function)
			{
			if((m_vec_Code[1]->m_Type[0]->m_VarType >= MuFunc_Custom) && (m_vec_Code[1]->m_Type[1]->m_VarType < MuSetGLOBAL_))
				{
				std::shared_ptr<Function> f_Function = m_vec_Code[1]->m_FunctionLink;

				std::shared_ptr<Variable> f_Var = f_Function->acExecute();

				m_Result_V = f_Function->m_Return_V;
				m_Result_CV = f_Function->m_Return_CV;
				}
			else
				{
				throw; //add debug message functype out of range
				}
			}
		}
	else if(m_CodeLine == MuLine_Function_Return)
		{
		std::shared_ptr<Variable> f_VariableReturn = m_vec_Variable[0];

		if(f_VariableReturn != nullptr)
			{
			std::shared_ptr<Variable> f_Return = f_VariableReturn;
			}
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
				f_VarCountVar->set_Value(f_XY);

				f_Function->acExecute();
				}
			}
		else if(f_ParamCount == 3)
			{
			std::shared_ptr<Variable> f_VarStart = m_vec_Variable[0];
			std::shared_ptr<Variable> f_VarCount = m_vec_Variable[1];
			std::shared_ptr<Variable> f_VarMax = m_vec_Variable[2];

			int f_CountStart = 0;

			if(f_VarCount->m_Var.type() == typeid(int))
				{
				f_CountStart = ag_any_cast<int>(f_VarCount->m_Var);
				}
			else
				{
#ifdef ECOIN_SECURE
				throw;
#endif
				}

			if(f_CountStart < 0)
				{
#ifdef ECOIN_SECURE
				throw;
#endif
				}

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

			int f_CountMax = 0;

			if(f_VarCount->m_Var.type() == typeid(int))
				{
				f_CountMax = ag_any_cast<int>(f_VarCount->m_Var);
				}
			else
				{
#ifdef ECOIN_SECURE
				throw;
#endif
				}

			if(f_CountMax < 0)
				{
#ifdef ECOIN_SECURE
				throw;
#endif
				}

			std::shared_ptr<Function> f_Function = g_Function[m_vec_Code[0]->m_ContractID];

			for(int f_XY = f_CountStart; f_XY < f_Count; f_XY += f_CountMax)
				{
				f_VarStart->set_Value(f_XY);

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
	else if(m_CodeLine == MuLine_Init_ClassVar)
		{
		std::shared_ptr<Code> f_CodeZero = m_vec_Code[0];

		std::shared_ptr<Class> f_Class = nullptr;

		for(int f_Jet = 0; f_Jet < g_Class.size(); f_Jet++)
			{
			std::shared_ptr<Class> f_TestClass = g_Class[f_Jet];

#pragma message("Warning add debugability messages according to m_Type = result")

			if(f_TestClass->m_MxName.compare(m_vec_Code[0]->m_MxName) == 0)
				{
				f_Class = f_TestClass;
				}
			}

		if(!f_Class)
			{
			throw; //class not found
			}

		std::shared_ptr<ClassVar> f_ClassVar = std::make_shared<ClassVar>(f_Class);

		f_ClassVar->acCall_Constructor();

		return f_ClassVar;
		}

	return nullptr;
}

std::string CodeLine::ac_Print(void)
{
	return m_CodeString;
}

};