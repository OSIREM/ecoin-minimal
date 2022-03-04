/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <math.h>

#include "MuType.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>

#include <boost/any.hpp>

namespace ecoin
{
    class Class;

    enum Ecoin_Variable_Current_Precision_TypeA
		{
		ECN_FLOAT,
		ECN_INT,
		ECN_STRING,
		ECN_MAX
		};

	enum Ecoin_Variable_Type
		{
		ECN_VAR_FLOAT,
		ECN_VAR_INT,
		ECN_VAR_STRING,
		ECN_CLASS_BOOL,
		ECN_CLASS_FLOAT,
		ECN_CLASS_INT,
		ECN_CLASS_STRING,
		ECN_CLASS_VAR,
		ECN_VAR
		};

	enum Variable_Precision
		{
		MuVar_Start,
		MuVar_Float,
		MuVar_Float2,
		MuVar_Float3,
		MuVar_Float4,
		MuVar_uInt,
		MuVar_Int,
		MuVar_Int2,
		MuVar_Int3,
		MuVar_Int4,
		MuVar_Bool,
		MuVar_Char,
		MuVar_String,
		MuVar_Full,
		MuVar_Total
		};

	enum Variable_Action
		{
		MuAct_Start,
		MuAct_Random,
		MuAct_RandInt,
		MuAct_Reset,
		MuAct_Inc,
		MuAct_Dec,
		MuAct_Double,
        MuAct_Finish,
		MuAct_Total
		};

    typedef struct
        {
        float m_X;
        float m_Y;
        float m_Z;
        } float3;

    typedef struct
        {
        float m_X;
        float m_Y;
        float m_Z;
        float m_W;
        } float4;

	class Variable : public MuType
		{
		public:
            Variable();
			Variable(uint f_PrecType);
			Variable(std::string f_Stg, uint f_CodeType);
            Variable(std::string f_Stg, uint f_CodeType, uint f_PrecType);
			Variable(std::string f_Stg, uint f_CodeType, uint f_PrecType, uint f_Variable);

            ~Variable();

            void acClear(void)
                {
                m_Action = MuAct_Start;
                m_MxName.clear();
                m_PrecType = 0;
                m_CodeType = 0;
                m_Variable = 0;
                }

			boost::any m_Var;

            std::shared_ptr<ecoin::Class> m_LinkClass;

            boost::any get_Value(void);

			void set_Value(boost::any f_Value);

            std::shared_ptr<Variable> CloneVar(std::shared_ptr<Variable> v1);

			uint m_PrecType;
			uint m_CodeType;
			uint m_Variable;

			std::string m_MxName;
            std::vector<std::string> m_vec_NameCall;

			unsigned char m_Action;
		};

	extern int agFind_VarType(std::string f_String);

    extern int agFind_CurrentSpec_VarType(std::string f_String);

	extern int agFind_Variable_Type(int f_CurrentSpec);

	extern std::shared_ptr<Variable> av_Identity(uint f_PrecType);

    std::shared_ptr<Variable> operator+ (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator- (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator* (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator/ (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator<< (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator>> (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator% (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    bool operator==(const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    bool operator!=(const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
};


#endif