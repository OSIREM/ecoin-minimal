/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Variable.h"
#include "Code.h"
#include "CodeLine.h"

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

Variable::Variable(std::string f_Stg, uint f_CodeType) : MuType(MuTYPE_Variable), m_MxName(f_Stg), m_CodeType(f_CodeType), m_PrecType(MuVar_Full)
{
	//m_Var = 0;
	m_Action = MuAct_Start;
}

std::shared_ptr<Variable> operator+ (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) + ag_any_cast<int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		v1->m_Var = ag_any_cast<float>(v1->m_Var) + ag_any_cast<float>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) + ag_any_cast<char>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(std::string))
        {
		v1->m_Var = ag_any_cast<std::string>(v1->m_Var) + ag_any_cast<std::string>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v2->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

        f_Var.m_X += f_AddtoVar.m_X;
        f_Var.m_X += f_AddtoVar.m_Y;
        f_Var.m_X += f_AddtoVar.m_Z;

		v1->m_Var = f_Var;
        }

    return v1;
}

std::shared_ptr<Variable> operator- (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) - ag_any_cast<int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		v1->m_Var = ag_any_cast<float>(v1->m_Var) - ag_any_cast<float>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) - ag_any_cast<char>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v2->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

        f_Var.m_X -= f_AddtoVar.m_X;
        f_Var.m_X -= f_AddtoVar.m_Y;
        f_Var.m_X -= f_AddtoVar.m_Z;

		v1->m_Var = f_Var;
        }

    return v1;
}

std::shared_ptr<Variable> operator* (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) * ag_any_cast<int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		v1->m_Var = ag_any_cast<float>(v1->m_Var) * ag_any_cast<float>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) * ag_any_cast<char>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v2->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

        f_Var.m_X *= f_AddtoVar.m_X;
        f_Var.m_X *= f_AddtoVar.m_Y;
        f_Var.m_X *= f_AddtoVar.m_Z;

		v1->m_Var = f_Var;
        }

    return v1;
}

std::shared_ptr<Variable> operator/ (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) / ag_any_cast<int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		v1->m_Var = ag_any_cast<float>(v1->m_Var) / ag_any_cast<float>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) / ag_any_cast<char>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v2->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

        f_Var.m_X /= f_AddtoVar.m_X;
        f_Var.m_X /= f_AddtoVar.m_Y;
        f_Var.m_X /= f_AddtoVar.m_Z;

		v1->m_Var = f_Var;
        }

    return v1;
}

std::shared_ptr<Variable> operator== (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) / ag_any_cast<int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		v1->m_Var = ag_any_cast<float>(v1->m_Var) / ag_any_cast<float>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) / ag_any_cast<char>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v2->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

        f_Var.m_X /= f_AddtoVar.m_X;
        f_Var.m_X /= f_AddtoVar.m_Y;
        f_Var.m_X /= f_AddtoVar.m_Z;

		v1->m_Var = f_Var;
        }

    return v1;
}

std::shared_ptr<Variable> operator<< (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) << ag_any_cast<int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) << ag_any_cast<char>(v2->m_Var);
        }

    return v1;
}

std::shared_ptr<Variable> operator>> (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) >> ag_any_cast<int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) >> ag_any_cast<char>(v2->m_Var);
        }

    return v1;
}

std::shared_ptr<Variable> operator% (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) % ag_any_cast<int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) % ag_any_cast<char>(v2->m_Var);
        }

    return v1;
}

int agFind_VarType(std::string f_String)
	{
	if(f_String.compare("float") == 0 ||
	   f_String.compare("Float") == 0 ||
	   f_String.compare("float1") == 0 ||
	   f_String.compare("Float1") == 0)
		{
		return MuVar_Float;
		}
	else if(f_String.compare("float2") == 0 ||
			f_String.compare("Float2") == 0)
		{
		return MuVar_Float2;
		}
	else if(f_String.compare("float3") == 0 ||
			f_String.compare("Float3") == 0)
		{
		return MuVar_Float3;
		}
	else if(f_String.compare("float4") == 0 ||
			f_String.compare("Float4") == 0)
		{
		return MuVar_Float4;
		}
	else if(f_String.compare("int") == 0 ||
	   f_String.compare("Int") == 0 ||
	   f_String.compare("int1") == 0 ||
	   f_String.compare("Int1") == 0)
		{
		return MuVar_Int;
		}
	else if(f_String.compare("int2") == 0 ||
			f_String.compare("Int2") == 0)
		{
		return MuVar_Int2;
		}
	else if(f_String.compare("int3") == 0 ||
			f_String.compare("Int3") == 0)
		{
		return MuVar_Int3;
		}
	else if(f_String.compare("int4") == 0 ||
			f_String.compare("Int4") == 0)
		{
		return MuVar_Int4;
		}
	else if(f_String.compare("uint") == 0 ||
			f_String.compare("uInt") == 0)
		{
		return MuVar_uInt;
		}
	else if(f_String.compare("bool") == 0 ||
			f_String.compare("Bool") == 0)
		{
		return MuVar_Bool;
		}
	else if(f_String.compare("char") == 0 ||
			f_String.compare("Char") == 0)
		{
		return MuVar_Char;
		}
	else if(f_String.compare("string") == 0 ||
			f_String.compare("String") == 0)
		{
		return MuVar_String;
		}

	return 0;
	}

int agFind_CurrentSpec_VarType(std::string f_String)
	{
	if(f_String.compare("float") == 0 ||
	   f_String.compare("Float") == 0 ||
	   f_String.compare("float1") == 0 ||
	   f_String.compare("Float1") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT;
		}
	else if(f_String.compare("float2") == 0 ||
			f_String.compare("Float2") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT;
		}
	else if(f_String.compare("float3") == 0 ||
			f_String.compare("Float3") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT;
		}
	else if(f_String.compare("float4") == 0 ||
			f_String.compare("Float4") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT;
		}
	else if(f_String.compare("int") == 0 ||
	   f_String.compare("Int") == 0 ||
	   f_String.compare("int1") == 0 ||
	   f_String.compare("Int1") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("int2") == 0 ||
			f_String.compare("Int2") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("int3") == 0 ||
			f_String.compare("Int3") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("int4") == 0 ||
			f_String.compare("Int4") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("uint") == 0 ||
			f_String.compare("uInt") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("bool") == 0 ||
			f_String.compare("Bool") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT;
		}
	else if(f_String.compare("char") == 0 ||
			f_String.compare("Char") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING;
		}
	else if(f_String.compare("string") == 0 ||
			f_String.compare("String") == 0)
		{
		return ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING;
		}

	return 0;
	}

boost::any Variable::get_Value(void)
	{
	return m_Var;
	}

void Variable::set_Value(boost::any f_Value)
	{
	m_Var = f_Value;
	}

std::shared_ptr<Variable> av_Identity(uint f_PrecType)
	{
	return std::make_shared<Variable>(f_PrecType);
	}
};