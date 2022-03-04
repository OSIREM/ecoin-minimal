/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef MUTYPE_H
#define MUTYPE_H

#include <vector>
#include <string>
#include <memory>

#include <math.h>
#include <regex>

#define uint unsigned int

#ifdef ecoin
using namespace ecoin;
#endif

namespace ecoin
{
	enum
	{
		MuTYPE_Function,
		MuTYPE_Variable,
		MuTYPE_System,
		MuTYPE_Code,
		MuTYPE_Operator,
		MuTYPE_Condition,
		MuTYPE_Any,
		MuTYPE_Total
	};

	class MuType
		{
		public:
			MuType() : m_Type(MuTYPE_Any) {};
			MuType(uint f_Type) : m_Type(f_Type) {};
			uint m_Type;
		};

#if 0
	class MuRNode
		{
		public:
			MuRNode() { acClear(); };
			~MuRNode() { acClear(); };

			void acClear(void);

			void acLockIN(bool f_Form_Structure);

			bool acMatchANY(std)
				{
				for(int f_Jet = 0; f_Jet < m_vec_Node.size(); f_Jet++)
					{
					std::shared_ptr<MuRNode> f_Node = m_vec_Node[f_Jet];

					if(f_Node->acMatchANY() == true)
						{

						}
					else
						{
						acMatch(f_Node);
						}
					}
				}

			bool acMatch(std::shared_ptr<MuRNode> f_NodeA, std::shared_ptr<MuRNode> f_NodeB)
				{
				cmatch f_match;
				bool f_bool = regex_match(f_NodeA->m_Node_String[0], f_NodeA->m_Node_String[f_NodeA->m_Node_String.size()], f_match, f_NodeB->m_Node_String[0]);

				if (std::regex_match(m_Node_Subject[0], std::regex("(sub)(.*)")))
					std::cout << "string literal matched\n";
				}

			std::vector<cmatch> m_Node_Match;
			std::vector<std::string> m_Node_Subject;
			std::vector<std::string> m_Node_String;

			std::vector<std::shared_ptr<MuRNode>> m_vec_Node;
		};

	class MuRegex
	{
	public:
		MuRegex() {};
		MuRegex(uint f_Type) {};

		std::vector<CodeLine> acCodeExpand(std::string f_MainLine)
			{

			}

		bool acUne(std::string f_A, std::string f_B)

		std::string acMatch(std::string f_String, )
			{
			bool regex_match(mystr, cm, str_expr);
			}

		

		std::vector<std::string> m_RegExp;
	};
#endif

}


#endif