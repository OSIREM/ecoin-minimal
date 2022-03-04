/*

Function - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Function.h"

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
#if 0
		std::cerr << e.what() << '\n';
#endif
		return T(0);
		}
#else
	return boost::any_cast<T>(f_Any);
#endif
}

	std::shared_ptr<Variable> Function::acExecute(void)
		{
		//FIXME check and throw exceptions (or add debug messages) for variables out of bounds

		switch(m_Function)
			{
			case MuFunc_RandFloat:
				{
				std::shared_ptr<Variable> f_Var = m_vec_Variable[0];
				
				f_Var->m_Var = Cube::random();
				
				return f_Var;
				}break;

			case MuFunc_RandInt:
				{
				std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

				f_Var->m_Var = Cube::randomFac();

				return f_Var;
				}break;

			case MuFunc_Sin:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = sin(ag_any_cast<float>(m_vec_Variable[1]->m_Var));

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Float);
					}
				}break;

			case MuFunc_Cos:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = cos(ag_any_cast<float>(m_vec_Variable[1]->m_Var));

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Float);
					}
				}break;

			case MuFunc_Tan:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = tan(ag_any_cast<float>(m_vec_Variable[1]->m_Var));

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Float);
					}
				}break;

			case MuFunc_Log:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = log(ag_any_cast<float>(m_vec_Variable[1]->m_Var));

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Float);
					}
				}break;

			case MuFunc_InvSin:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = asin(ag_any_cast<float>(m_vec_Variable[1]->m_Var));

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Float);
					}
				}break;

			case MuFunc_InvCos:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = acos(ag_any_cast<float>(m_vec_Variable[1]->m_Var));

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Float);
					}
				}break;

			case MuFunc_InvTan:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = atan(ag_any_cast<float>(m_vec_Variable[1]->m_Var));

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Float);
					}
				}break;

			case MuFunc_Sqr:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = ag_any_cast<float>((m_vec_Variable[1] * m_vec_Variable[1])->m_Var);

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Float);
					}
				}break;

			case MuFunc_Sqrt:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = sqrt(ag_any_cast<float>(m_vec_Variable[1]->m_Var));

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Float);
					}
				}break;

			case MuFunc_ArcTan2:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = atan2(ag_any_cast<float>(m_vec_Variable[1]->m_Var), ag_any_cast<float>(m_vec_Variable[2]->m_Var));

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Float);
					}
				}break;

			case MuFunc_Gate_NOT:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = !ag_any_cast<float>(m_vec_Variable[1]->m_Var);

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Bool);
					}
				}break;

			case MuFunc_Gate_AND:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = ag_any_cast<bool>(m_vec_Variable[1]->m_Var) && ag_any_cast<bool>(m_vec_Variable[2]->m_Var);

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Bool);
					}
				}break;

			case MuFunc_Gate_OR:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_Var = m_vec_Variable[0];

					f_Var->m_Var = ag_any_cast<bool>(m_vec_Variable[1]->m_Var) || ag_any_cast<bool>(m_vec_Variable[2]->m_Var);

					return f_Var;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Bool);
					}
				}break;

			case MuFunc_Gate_XOR:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_VarR = m_vec_Variable[0];
					std::shared_ptr<Variable> f_VarA = m_vec_Variable[1];
					std::shared_ptr<Variable> f_VarB = m_vec_Variable[2];

					f_VarR->m_Var = ((ag_any_cast<bool>(f_VarA->m_Var) || ag_any_cast<bool>(f_VarB->m_Var)) && !(ag_any_cast<bool>(f_VarA->m_Var) && ag_any_cast<bool>(f_VarB->m_Var)));

					return f_VarR;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Bool);
					}
				}break;

			case MuFunc_Gate_NAND:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_VarR = m_vec_Variable[0];
					std::shared_ptr<Variable> f_VarA = m_vec_Variable[1];
					std::shared_ptr<Variable> f_VarB = m_vec_Variable[2];

					f_VarR->m_Var = !(ag_any_cast<bool>(f_VarA->m_Var) && ag_any_cast<bool>(f_VarB->m_Var));

					return f_VarR;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Bool);
					}
				}break;

			case MuFunc_Gate_NOR:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_VarR = m_vec_Variable[0];
					std::shared_ptr<Variable> f_VarA = m_vec_Variable[1];
					std::shared_ptr<Variable> f_VarB = m_vec_Variable[2];

					f_VarR->m_Var = !(ag_any_cast<bool>(f_VarA->m_Var) || ag_any_cast<bool>(f_VarB->m_Var));

					return f_VarR;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Bool);
					}
				}break;

			case MuFunc_Gate_XNOR:
				{
				if(m_vec_Variable.size() == 3)
					{
					std::shared_ptr<Variable> f_VarR = m_vec_Variable[0];
					std::shared_ptr<Variable> f_VarA = m_vec_Variable[1];
					std::shared_ptr<Variable> f_VarB = m_vec_Variable[2];

					f_VarR->m_Var = !((ag_any_cast<bool>(f_VarA->m_Var) || ag_any_cast<bool>(f_VarB->m_Var)) && !(ag_any_cast<bool>(f_VarA->m_Var) && ag_any_cast<bool>(f_VarB->m_Var)));

					return f_VarR;
					}
				else
					{
#ifdef ECOIN_SECURE
					throw;
#endif
					return av_Identity(MuVar_Bool);
					}
				}break;

			default:
				{
				for(int f_XY = 0; f_XY < m_vec_CodeLine.size(); f_XY++)
					{
					std::shared_ptr<CodeLine> f_CodeLine = m_vec_CodeLine[f_XY];

					std::shared_ptr<ClassVar> f_CV = f_CodeLine->ac_Execute((std::shared_ptr<Function>)this);

					if(f_CV != nullptr)
						{
						m_vec_ClassVar.push_back(f_CV);
						g_ClassVar.push_back(f_CV);

						f_XY = m_vec_CodeLine.size(); // return
						}
					else if(f_CodeLine->m_Result_V != nullptr)
						{
						m_Return_V = f_CodeLine->m_Result_V;

						f_XY = m_vec_CodeLine.size(); // return
						}
					else if(f_CodeLine->m_Result_CV != nullptr)
						{
						m_Return_CV = f_CodeLine->m_Result_CV;

						f_XY = m_vec_CodeLine.size(); // return
						}
					}
				}break;
			}

		return av_Identity(MuVar_Bool);
		}

	std::shared_ptr<Variable> ag_Find_Var(std::string f_VarName)
		{
		for(int f_Helly = 0; f_Helly < g_vec_GlobalScopeContract.size(); f_Helly++)
			{
			std::shared_ptr<Contract> f_Contract = g_vec_GlobalScopeContract[f_Helly];

			for(int f_Jet = 0; f_Jet < f_Contract->m_vec_Variable_Store.size(); f_Jet++)
				{
				std::shared_ptr<Variable> f_Var = f_Contract->m_vec_Variable_Store[f_Jet];

				if(f_Var->m_MxName.compare(f_VarName) == 0)
					{
					return f_Var;
					}
				}
			}

		return nullptr;
		}

	std::shared_ptr<ClassVar> ag_Find_ClassVar(std::string f_VarName)
		{
		for(int f_Helly = 0; f_Helly < g_vec_GlobalScopeContract.size(); f_Helly++)
			{
			std::shared_ptr<Contract> f_Contract = g_vec_GlobalScopeContract[f_Helly];

			for(int f_Jet = 0; f_Jet < f_Contract->m_vec_ClassVar.size(); f_Jet++)
				{
				std::shared_ptr<ClassVar> f_CVar = f_Contract->m_vec_ClassVar[f_Jet];

				if(f_CVar->m_MxName.compare(f_VarName) == 0)
					{
					return f_CVar;
					}
				}
			}

		return nullptr;
		}

	std::shared_ptr<Variable> Function::acFind_Var(std::string f_VarName)
		{
		for(int f_Jet = 0; f_Jet < m_vec_Variable.size(); f_Jet++)
			{
			std::shared_ptr<Variable> f_Var = m_vec_Variable[f_Jet];

			if(f_Var->m_MxName.compare(f_VarName) == 0)
				{
				return f_Var;
				}
			}

		return nullptr;
		}

	std::shared_ptr<ClassVar> Function::acFind_ClassVar(std::string f_VarName)
		{
		for(int f_Jet = 0; f_Jet < m_vec_ClassVar.size(); f_Jet++)
			{
			std::shared_ptr<ClassVar> f_CVar = m_vec_ClassVar[f_Jet];

			if(f_CVar->m_MxName.compare(f_VarName) == 0)
				{
				return f_CVar;
				}
			}

		return nullptr;
		}

	uint Function::acPrep_addVariable(std::shared_ptr<Variable> f_Var)
		{
		m_vec_Variable.push_back(f_Var);
		return m_vec_Variable.size() - 1;
		}

	int agFind_FunctionType(std::string f_String)
		{
		if(f_String.compare("EcomFrame") == 0 ||
		   f_String.compare("Frame") == 0 ||
		   f_String.compare("EcomNFrame") == 0 ||
		   f_String.compare("ENFrame") == 0 ||
		   f_String.compare("EcomNativeFrame") == 0)
			{
			return MuFunc_Frame;
			}
		else if(f_String.compare("RandFloat") == 0 ||
		   f_String.compare("RandF") == 0 ||
		   f_String.compare("Randfloat") == 0 ||
		   f_String.compare("Randf") == 0)
			{
			return MuFunc_RandFloat;
			}
		else if(f_String.compare("RandInteger") == 0 ||
				f_String.compare("RandInt") == 0 ||
				f_String.compare("Rand") == 0)
			{
			return MuFunc_RandInt;
			}
		else if(f_String.compare("Sin") == 0 ||
				f_String.compare("sin") == 0 ||
				f_String.compare("Sine") == 0 ||
				f_String.compare("sine") == 0)
			{
			return MuFunc_Sin;
			}
		else if(f_String.compare("Cos") == 0 ||
				f_String.compare("cos") == 0 ||
				f_String.compare("Cosine") == 0 ||
				f_String.compare("cosine") == 0)
			{
			return MuFunc_Cos;
			}
		else if(f_String.compare("Tan") == 0 ||
				f_String.compare("tan") == 0 ||
				f_String.compare("Tangent") == 0 ||
				f_String.compare("tangent") == 0)
			{
			return MuFunc_Tan;
			}
		else if(f_String.compare("Log") == 0 ||
				f_String.compare("log") == 0)
			{
			return MuFunc_Log;
			}
		else if(f_String.compare("InvSin") == 0 ||
				f_String.compare("Invsin") == 0 ||
				f_String.compare("invSin") == 0 ||
				f_String.compare("invsin") == 0 ||
				f_String.compare("InvSine") == 0 ||
				f_String.compare("Invsine") == 0 ||
				f_String.compare("invSine") == 0 ||
				f_String.compare("invsine") == 0)
			{
			return MuFunc_InvSin;
			}
		else if(f_String.compare("InvCos") == 0 ||
				f_String.compare("Invcos") == 0 ||
				f_String.compare("invCos") == 0 ||
				f_String.compare("invcos") == 0 ||
				f_String.compare("InvCosine") == 0 ||
				f_String.compare("Invcosine") == 0 ||
				f_String.compare("invCosine") == 0 ||
				f_String.compare("invCosine") == 0)
			{
			return MuFunc_InvCos;
			}
		else if(f_String.compare("InvTan") == 0 ||
				f_String.compare("Invtan") == 0 ||
				f_String.compare("invTan") == 0 ||
				f_String.compare("invtan") == 0 ||
				f_String.compare("InvTangent") == 0 ||
				f_String.compare("Invtangent") == 0 ||
				f_String.compare("invTangent") == 0 ||
				f_String.compare("invtangent") == 0)
			{
			return MuFunc_InvTan;
			}
		else if(f_String.compare("sqr") == 0 ||
				f_String.compare("SQR") == 0 ||
				f_String.compare("square") == 0 ||
				f_String.compare("SQUARE") == 0 ||
				f_String.compare("Square") == 0)
			{
			return MuFunc_Sqr;
			}
		else if(f_String.compare("sqrt") == 0 ||
				f_String.compare("SQRT") == 0 ||
				f_String.compare("squareroot") == 0 ||
				f_String.compare("SQUAREROOT") == 0 ||
				f_String.compare("SquareRoot") == 0 ||
				f_String.compare("Squareroot") == 0)
			{
			return MuFunc_Sqrt;
			}
		else if(f_String.compare("atan") == 0 || 
				f_String.compare("atan2") == 0 ||
				f_String.compare("ArcTan") == 0 ||
				f_String.compare("ArcTan2") == 0 ||
				f_String.compare("Arctan") == 0 ||
				f_String.compare("arctan") == 0 ||
				f_String.compare("arctan2") == 0)
			{
			return MuFunc_ArcTan2;
			}
		else if(f_String.compare("NOT") == 0 ||
				f_String.compare("Not") == 0 ||
				f_String.compare("not") == 0)
			{
			return MuFunc_Gate_NOT;
			}
		else if(f_String.compare("AND") == 0 ||
				f_String.compare("And") == 0 ||
				f_String.compare("and") == 0)
			{
			return MuFunc_Gate_AND;
			}
		else if(f_String.compare("OR") == 0 ||
				f_String.compare("Or") == 0 ||
				f_String.compare("or") == 0)
			{
			return MuFunc_Gate_OR;
			}
		else if(f_String.compare("XOR") == 0 ||
				f_String.compare("XOr") == 0 ||
				f_String.compare("Xor") == 0 ||
				f_String.compare("xor") == 0)
			{
			return MuFunc_Gate_XOR;
			}
		else if(f_String.compare("NAND") == 0 ||
				f_String.compare("Nand") == 0 ||
				f_String.compare("nand") == 0)
			{
			return MuFunc_Gate_NAND;
			}
		else if(f_String.compare("NOR") == 0 ||
				f_String.compare("Nor") == 0 ||
				f_String.compare("nor") == 0)
			{
			return MuFunc_Gate_NOR;
			}
		else if(f_String.compare("XNOR") == 0 ||
				f_String.compare("XNor") == 0 ||
				f_String.compare("Xnor") == 0 ||
				f_String.compare("xnor") == 0)
			{
			return MuFunc_Gate_XNOR;
			}
		else
			{
			return MuFunc_Custom;
			}

		return 0;
		}

};