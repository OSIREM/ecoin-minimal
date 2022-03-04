/*

Contract - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "System.h"

#include "Code.h"

using namespace ecoin;

namespace ecoin
{

	System::System()
		{
		Pos = std::make_shared<Variable>("Pos", MuCode_System);
		Posx = std::make_shared<Variable>("Posx", MuCode_System);
		Posy = std::make_shared<Variable>("Posy", MuCode_System);
		Posz = std::make_shared<Variable>("Posz", MuCode_System);
		Color = std::make_shared<Variable>("Color", MuCode_System);
		Matrix1 = std::make_shared<Variable>("Matrix1", MuCode_System);
		Matrix2 = std::make_shared<Variable>("Matrix2", MuCode_System);
		Matrix3 = std::make_shared<Variable>("Matrix3", MuCode_System);
		Matrix4 = std::make_shared<Variable>("Matrix4", MuCode_System);
		nonce = std::make_shared<Variable>("nonce", MuCode_System);
		}

	System::~System()
		{
		}

	std::shared_ptr<Variable> System::av_Var(std::string f_String)
		{
		if(f_String.compare("Pos") == 0)
			{
			return Pos;
			}
		else if (f_String.compare("Posx") == 0)
			{
			return Posx;
			}
		else if (f_String.compare("Posy") == 0)
			{
			return Posy;
			}
		else if(f_String.compare("Posz") == 0)
			{
			return Posz;
			}
		else if(f_String.compare("Color") == 0)
			{
			return Color;
			}
		else if(f_String.compare("Matrix1") == 0)
			{
			return Matrix1;
			}
		else if (f_String.compare("Matrix2") == 0)
			{
			return Matrix2;
			}
		else if(f_String.compare("Matrix3") == 0)
			{
			return Matrix3;
			}
		else if(f_String.compare("Matrix4") == 0)
			{
			return Matrix4;
			}
		else if(f_String.compare("nonce") == 0)
			{
			return nonce;
			}

		return Pos;
		}

};