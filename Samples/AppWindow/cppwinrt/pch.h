/*

pch.h - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <map>

namespace Cube
{

extern char* ag_ClearChar(int f_Size);

};

#define ECOIN_CONSENSUS_ID 6

#define ECOIN_CONSENSUS_FIRST_SANE_ID 6

#if 0 //not recomended or production deploy
#define ECOIN_SECURE_01 1
#endif

#if 1 //osi-memory
#define ECOIN_OSI_MEMORY 1
#endif

#if 1 //osi-memory base functions
#define ECOIN_OSI_MEMORY_FUNC 1
#endif

#if 1 //recomended
#define ECOIN_OSI_MEMORY_AUX 1
#endif

#if 1 //not required
#define ECOIN_OSI_MEM_MUSION 1
#endif

#if 1 //recommended
#define OSI_MEMORY_BICYCLE_REF 1
#endif

#if 1 //recommended
#define OSI_MEMORY_HESH_REF 1
#endif

#if 1 //recommended
#define OSI_MEMORY_BIVECTOR_REF 1
#endif

#if 1 //recommended
#define OSI_MEMORY_ELEMENT_REF 1
#endif

#if 1 
#define ECOIN_MEMORY_FULL_MUTEX 1
#endif

#if 0
#define ECOIN_PROCEDURE_UPLOAD 1
#endif

#if 1 //important: on production switch off
#define ECOIN_PROCEDURE_RESET 1
#endif

#if 0 //ecoin Experimental Reflection Tests, production code off
#define ECOIN_REFLECTION_EXP 1
#endif

#if 0 // test loadcom(1), production code off
#define TEST_VERIFY_SCP_BUILD_ECOM 1
#endif

#if 0 //load small, production code mebbe...
#define ECOIN_LOAD_ACKS 1
#endif

#if 0 //not support, production code off
#define ECOIN_OVERRIDE 1
#endif

#if 1 //mebbe ?, ya production code mebbe
#define ECOIN_BALANCE_PEER_EACH_ELEMENT 1
#endif

#if 1 //production code off / debug testing on
#define ECOIN_DEBUG_BREAKS 1
#endif

#if 1 //production code off / current testing breaks FULLY off
#define ECOIN_DBG_BREAK 1
#endif

#if 1 //production code off / debug testing ?//TX FULLY off
#define ECOIN_DEBUG_BREAKS_TX 1
#endif

#define ECOIN_SHARE_PROTOCOL_LENGTH 3000

#define g_ref_CurrentPath std::string(":")
#define g_ref_InOut_Var std::string("/")
#define g_ref_Div std::string(":::")
#define g_ref_global_Div std::string(":-:")
#define g_ref_global_start std::string(":G:")
#define g_ref_delegate_start std::string(":E:")
#define g_ref_flow_reset std::string(":F:")
#define g_ref_Path_Div std::string(":|:")
#define g_ref_fun_Div std::string("->>")
#define g_ref_fun_Append std::string("_pach")

class PathPosition
{
public:
	PathPosition()
		{
		m_X = -1;
		m_Y = -1;
		}

	PathPosition(int f_X, int f_Y)
		{
		m_X = f_X;
		m_Y = f_Y;
		}

	~PathPosition()
		{
		m_X = -1;
		m_Y = -1;
		}

	int m_X;
	int m_Y;
};

extern PathPosition g_PP;

extern std::vector<std::vector<std::string>> g_vec_Path;
extern std::vector<std::vector<std::string>> g_vec_PathLabel;

extern bool g_MutexLocked;

extern void ag_LockMutex(void);
extern void ag_UnLockMutex(void);

extern std::string ag_AcceptObjectName(void);

extern std::vector<std::vector<std::string>> g_VectorObjectName;
extern std::vector<int> g_Proll;

extern void ag_CentraliseCull(std::string f_CullStringPath);
extern void ag_StatusLive(std::string f_Path, std::string f_Label, bool f_Prepare = false, int f_VecIndex = 0);
extern void ag_StatusSync(std::string f_Path, std::string f_Label, bool f_Prepare = false, int f_VecIndex = 0);

extern void ag_Click(std::string f_ButtonName);

extern std::string ag_Build_Path(PathPosition f_PP);

extern void ag_DeleteMapObject(std::string f_MapNamePath);

#ifdef ECOIN_OSI_MEMORY_AUX
#include "Include\osimemory.h"
#else
#include <memory>
#endif

#include <boost/any.hpp>

template<class T>
T ag_any_cast_ex(boost::any f_Any)
{
	try
		{
		return boost::any_cast<T>(f_Any);
		}
	catch (boost::bad_any_cast& e)
		{
		std::cerr << e.what() << '\n';

#ifdef ECOIN_DBG_BREAK
		__debugbreak();
#endif //add debug message
		}

	return nullptr;
}

#ifdef ECOIN_OSI_MEMORY

class ecom_base_flap
{
public:
	ecom_base_flap()
		{
		}

	~ecom_base_flap()
		{
		}
};

   ////////////////////////
  // Reflection Utility //
 ////////////////////////
//
class FunctionBeam
{
	public:
		FunctionBeam() { ac_Clear(); };
		~FunctionBeam() { ac_Clear(); };

		void ac_Clear(void)
			{
			m_Norm_X = 0;
			m_Class_X = 0;
			m_vec_NormalArguments.clear();
			m_vec_ClassArguments.clear();
			m_NamePath.clear();
			m_Normal = true;
			}

		boost::any acGet_Line(void)
			{
			int f_IDX = m_Norm_X;

			m_Norm_X++;

			if(m_Norm_X >= m_vec_NormalArguments.size())
				{
				m_Normal = false;
				}

			return m_vec_NormalArguments[f_IDX];
			}

		boost::any acGet_Line(int f_Q)
			{
			int f_IDX = f_Q;

			m_Norm_X++;

			if(m_Norm_X >= m_vec_NormalArguments.size())
				{
				m_Normal = false;
				}

			return m_vec_NormalArguments[f_IDX];
			}

		std::string acGet_Line_Ref(void)
			{
			int f_IDX = m_Class_X;

			m_Class_X++;

			if(m_Class_X >= m_vec_ClassArguments.size())
				{
				m_Class_X--;

#ifdef ECOIN_DBG_BREAK
				__debugbreak();
#endif //add debug message
				}

			return m_vec_ClassArguments[f_IDX];
			}

		std::string acGet_Line_Ref(int f_Q)
			{
			int f_IDX = f_Q;

			m_Class_X++;

			if(m_Class_X >= m_vec_ClassArguments.size())
				{
				m_Class_X--;

#ifdef ECOIN_DBG_BREAK
				__debugbreak();
#endif //add debug message
				}

			return m_vec_ClassArguments[f_IDX];
			}

		void ac_PachON(boost::any f_any)
			{
			m_vec_NormalArguments.push_back(f_any);
			}

		void ac_PachOC(std::string f_Classname)
			{
			m_vec_ClassArguments.push_back(f_Classname);
			}

		  ///////////////////////
		 // unpaching visitor //
		///////////////////////
		template<class T>
		T ag_Pach_Entry(void)
			{
			m_Normal = true;

			boost::any f_AnyArg = acGet_Line();

			T f_Object = ag_any_cast_ex<T>(f_AnyArg);

			return f_Object;
			}

		template<class CT>
		std::shared_ptr<CT> ag_Pach_Entry_CLS(void)
			{
			m_Normal = false;

			std::string f_ClassArg = acGet_Line_Ref();

			if(g_vec_ecomRefBase.find(f_ClassArg) != g_vec_ecomRefBase.end())
				{
				std::shared_ptr<CT> f_ecom_base_varg = g_vec_ecomRefBase[f_ClassArg];

				return f_ecom_base_varg;
				}

			return nullptr;
			}

		std::string m_NamePath;
		boost::any m_FuncAny;

		std::vector<boost::any> m_vec_NormalArguments;
		std::vector<std::string> m_vec_ClassArguments;

		bool m_Normal;

	protected:
		int m_Norm_X;
		int m_Class_X;
};

class ecom_vector_layer1
{
public:
	ecom_vector_layer1()
		{
		}

	~ecom_vector_layer1()
		{
		}

	std::map<std::string, std::vector<bool>*> m_vec_Map_Bool;
	std::map<std::string, std::vector<float>*> m_vec_Map_Float;
	std::map<std::string, std::vector<double>*> m_vec_Map_Double;
	std::map<std::string, std::vector<int>*> m_vec_Map_Int;
	std::map<std::string, std::vector<unsigned int>*> m_vec_Map_UInt;
	std::map<std::string, std::vector<char>*> m_vec_Map_Char;
	std::map<std::string, std::vector<std::string>*> m_vec_Map_String;
};

class ecom_vector_layer2
{
public:
	ecom_vector_layer2()
		{
		}

	~ecom_vector_layer2()
		{
		}

	std::map<std::string, std::vector<std::vector<bool>>*> m_vec_vec_Map_Bool;
	std::map<std::string, std::vector<std::vector<float>>*> m_vec_vec_Map_Float;
	std::map<std::string, std::vector<std::vector<double>>*> m_vec_vec_Map_Double;
	std::map<std::string, std::vector<std::vector<int>>*> m_vec_vec_Map_Int;
	std::map<std::string, std::vector<std::vector<unsigned int>>*> m_vec_vec_Map_UInt;
	std::map<std::string, std::vector<std::vector<char>>*> m_vec_vec_Map_Char;
	std::map<std::string, std::vector<std::vector<std::string>>*> m_vec_vec_Map_String;
};

class ecom_vector_layer3
{
public:
	ecom_vector_layer3()
		{
		}

	~ecom_vector_layer3()
		{
		}

	std::map<std::string, std::vector<std::vector<std::vector<bool>>>*> m_vec_vec_vec_Map_Bool;
	std::map<std::string, std::vector<std::vector<std::vector<float>>>*> m_vec_vec_vec_Map_Float;
	std::map<std::string, std::vector<std::vector<std::vector<double>>>*> m_vec_vec_vec_Map_Double;
	std::map<std::string, std::vector<std::vector<std::vector<int>>>*> m_vec_vec_vec_Map_Int;
	std::map<std::string, std::vector<std::vector<std::vector<unsigned int>>>*> m_vec_vec_vec_Map_UInt;
	std::map<std::string, std::vector<std::vector<std::vector<char>>>*> m_vec_vec_vec_Map_Char;
	std::map<std::string, std::vector<std::vector<std::vector<std::string>>>*> m_vec_vec_vec_Map_String;
};

class ecom_base
{
public:
	ecom_base()
		{
		ecomClear();
		}

	~ecom_base()
		{
		ecomClear();
		}

	void ecomClear(void)
		{
		m_Map_Function.clear();

		m_Map_Bool.clear();
		m_Map_Float.clear();
		m_Map_Int.clear();
		m_Map_Char.clear();
		m_Map_String.clear();

		m_veclayer1 = nullptr;
		m_veclayer2 = nullptr;
		m_veclayer3 = nullptr;

		m_Status = 0;

		m_ActiveFuncBeam = nullptr;
		}

	bool acEmptyBase(void)
		{
		if(m_Map_Function.size() > 0)
			{
			return false;
			}

		if(m_Map_Float.size() > 0)
			{
			return false;
			}

		if(m_Map_Bool.size() > 0)
			{
			return false;
			}

		if(m_Map_Int.size() > 0)
			{
			return false;
			}

		if(m_Map_UInt.size() > 0)
			{
			return false;
			}

		if(m_Map_Char.size() > 0)
			{
			return false;
			}

		if(m_Map_String.size() > 0)
			{
			return false;
			}

		if(m_veclayer1 != nullptr)
			{
			return false;
			}

		if(m_veclayer2 != nullptr)
			{
			return false;
			}

		if(m_veclayer3 != nullptr)
			{
			return false;
			}

		return true;
		}

	typedef void (ecom_base::* ControllerMethod)(void);
	typedef void (ecom_base::* ControllerMethod_void)(void);
	
#if 0
	typedef void (ecom_base::* ControllerMethod)(int, int) const;
#endif

	void ac_Invoke(std::string f_ref_FuncStr, std::shared_ptr<FunctionBeam> f_funcBeam = nullptr);

	void ac_Push(bool& f_Var, std::string f_MemberVarName);
	void ac_Push(float& f_Var, std::string f_MemberVarName);
	void ac_Push(double& f_Var, std::string f_MemberVarName);
	void ac_Push(int& f_Var, std::string f_MemberVarName);
	void ac_Push(unsigned int& f_Var, std::string f_MemberVarName);
	void ac_Push(char& f_Var, std::string f_MemberVarName);
	void ac_Push(std::string& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<bool>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<float>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<double>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<int>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<unsigned int>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<char>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::string>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<bool>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<float>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<double>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<int>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<unsigned int>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<char>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::string>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<bool>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<float>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<double>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<int>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<unsigned int>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<char>>>& f_Var, std::string f_MemberVarName);
	void ac_Push(std::vector<std::vector<std::vector<std::string>>>& f_Var, std::string f_MemberVarName);

	void ac_PushFunction(std::string f_NameString, ecom_base::ControllerMethod_void f_FunctionRef);

	bool* ac_GetBLT(std::string f_MemberVarName);
	float* ac_GetFLT(std::string f_MemberVarName);
	int* ac_GetINT(std::string f_MemberVarName);
	std::string* ac_GetSTR(std::string f_MemberVarName);

	void* ac_Get(std::string f_MemberVarName, std::string f_TypeName)
		{
		if(f_TypeName == "int")
			{
			return m_Map_Int[f_MemberVarName];
			}
		else if(f_TypeName == "char")
			{
			return m_Map_Char[f_MemberVarName];
			}
		else if(f_TypeName == "float")
			{
			return m_Map_Float[f_MemberVarName];
			}
		else if(f_TypeName == "bool")
			{
			return m_Map_Int[f_MemberVarName];
			}
		else if(f_TypeName == "std::string")
			{
			return m_Map_String[f_MemberVarName];
			}
		}

	std::map<std::string, ControllerMethod_void> m_Map_Function;

	std::map<std::string, bool*> m_Map_Bool;
	std::map<std::string, float*> m_Map_Float;
	std::map<std::string, double*> m_Map_Double;
	std::map<std::string, int*> m_Map_Int;
	std::map<std::string, unsigned int*> m_Map_UInt;
	std::map<std::string, char*> m_Map_Char;
	std::map<std::string, std::string*> m_Map_String;

	std::shared_ptr<ecom_vector_layer1> m_veclayer1;
	std::shared_ptr<ecom_vector_layer2> m_veclayer2;
	std::shared_ptr<ecom_vector_layer3> m_veclayer3;

	std::shared_ptr<FunctionBeam> m_ActiveFuncBeam;

	int m_Status;

	//Decoy
	std::string m_PathName;
	int m_StackCount;
};

 ////////////////////////////////////////////
// Ecom SuperClass 'ecom_base' Main Spire //
extern std::map<std::string, std::shared_ptr<ecom_base>> g_vec_ecomRefBase;
extern std::map<std::string, int> g_vec_ecomRefCount;

 ////////////////////////////////////////////////
// [GLOBAL] Memory Referencing for reflection //
extern void ag_Push(bool& f_Var, std::string f_GlobalVarName);
extern void ag_Push(float& f_Var, std::string f_GlobalVarName);
extern void ag_Push(double& f_Var, std::string f_GlobalVarName);
extern void ag_Push(int& f_Var, std::string f_GlobalVarName);
extern void ag_Push(unsigned int& f_Var, std::string f_GlobalVarName);
extern void ag_Push(char& f_Var, std::string f_GlobalVarName);
extern void ag_Push(std::string& f_Var, std::string f_GlobalVarName);

std::map<std::string, bool*> g_Map_Bool;
std::map<std::string, float*> g_Map_Float;
std::map<std::string, double*> g_Map_Double;
std::map<std::string, int*> g_Map_Int;
std::map<std::string, unsigned int*> g_Map_UInt;
std::map<std::string, char*> g_Map_Char;
std::map<std::string, std::string*> g_Map_String;

//[END] #ifdef ~OSI_MEMORY~
#else

class ecom_base
{
public:
	ecom_base()
		{
		}

	~ecom_base()
		{
		}
};

class ecom_base_flap
{
public:
	ecom_base_flap()
	{
	}

	~ecom_base_flap()
	{
	}
};

#endif

#include <future>
#include <iostream>

#ifdef _RESUMABLE_FUNCTIONS_SUPPORTED
#include <experimental/resumable>
#endif

#include <unknwn.h>
#include "winrt/coroutine.h"
#include "winrt/Windows.ApplicationModel.Store.h"
#include "winrt/Windows.ApplicationModel.Activation.h"
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/Windows.Graphics.Display.h"
#include "winrt/Windows.Graphics.Imaging.h"
#include "winrt/Windows.Storage.h"
#include "winrt/Windows.Storage.Streams.h"
#include "winrt/Windows.Storage.AccessCache.h"
#include "winrt/Windows.Storage.Pickers.Provider.h"
#include "winrt/Windows.Storage.Pickers.h"
#include "winrt/Windows.Security.Cryptography.h"
#include "winrt/Windows.Security.ExchangeActiveSyncProvisioning.h"
#include "winrt/Windows.System.h"
#include "winrt/Windows.System.Threading.h"
#include "winrt/Windows.UI.Core.h"
#include "winrt/Windows.UI.Input.h"
#include "winrt/Windows.UI.ViewManagement.h"
#include "winrt/Windows.UI.WindowManagement.h"
#include "winrt/Windows.UI.WindowManagement.Preview.h"
#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Input.h"
#include "winrt/Windows.UI.Xaml.Automation.Peers.h"
#include "winrt/Windows.UI.Xaml.Controls.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "winrt/Windows.UI.Xaml.Documents.h"
#include "winrt/Windows.UI.Xaml.Hosting.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Media.h"
#include "winrt/Windows.UI.Xaml.Media.Imaging.h"
#include "winrt/Windows.UI.Xaml.Navigation.h"
#include "winrt/Windows.UI.Xaml.Shapes.h"
#include <windows.ui.xaml.media.dxinterop.h>

#pragma comment (lib, "WindowsApp.lib")

#include "Code/myBO/icSafeL.h"
#include "Wallet/Wallet.h"
#include "Code/Musion/Variable.h"
#include "Code/CLS/Target.h"
#include "Code/Cube/qcom.h"
#include "Code/Cube/predator.h"

using namespace Cube;
using namespace ecoin;
using namespace std;

template<typename f_A>
extern f_A ag_CheckBoth(f_A f_Input);

extern int ag_CheckInteger(std::string f_InputString);
extern float ag_CheckFloat(std::string f_InputString);

template<typename f_A>
extern void ag_FreshOn(std::vector<f_A>& f_AS, int f_IDX, f_A f_Resultance);

template<typename f_B>
extern void ag_Freshanon(std::vector<f_B>& f_AS, int f_IDX, f_B f_Resultance);

template<typename f_C>
extern f_C ag_FreshOnly(std::vector<f_C>& f_AS, int f_IDX, f_C f_Resultance);

template<typename f_D>
extern f_D ag_FreshAndOnly(std::vector<f_D>& f_AS, int f_IDX, f_D f_Resultance);

extern void ag_PrepareChar(char* f_Char, int f_ArraySize);
extern void FillChar(char* f_Char, int f_Max);
extern char acFileReadChar(std::string f_Buffer, size_t f_Count);
extern std::string acBufreadCodeString(std::string f_Buffer, unsigned int f_CHK);
extern winrt::hstring StrFromChar(char char_str[]);
extern winrt::hstring StrUsingStr(std::string f_string);
extern std::string to_string(const std::wstring& wtxt);
extern std::string to_string(winrt::hstring pstring);
extern std::string to_string(wchar_t* wstring);
extern std::string ag_StrUsingFloat(float f_Float);
extern int StringToWString(std::wstring& ws, const std::string& s);
extern int acBufreadValueInteger(const std::string& f_Buffer, uint* f_Chk);
extern float acBufreadValueFloat(const std::string& f_Buffer, uint* f_Chk);
extern double acBufreadValueDouble(const std::string& f_Buffer, uint* f_Chk);
extern double acBufreadValueDouble(const std::string& f_Buffer, uint* f_Chk);
extern std::string acBufreadValueString(const std::string& f_Buffer, uint* f_Chk);
extern void acBufwriteValueInteger(std::string* f_Buffer, int f_Int);
extern void acBufwriteValueDouble(std::string* f_Buffer, double f_Double);
extern void acBufwriteValueInt(std::string* f_Buffer, int f_Int);
extern void acBufwriteValueFloat(std::string* f_Buffer, float f_Float);
extern float ag_Unsign(float f_Input);

extern picosha2::hash256_one_by_one g_hasha;
extern int g_Viewing;
extern bool g_KeepShare;
extern int g_Found_Share;
extern int g_Found_Block;
extern int g_Found_Msg;
extern int g_CoolDown;
extern float g_CoolBoost;
extern int g_PEERCNT;
extern int g_SHARECNT;
extern bool g_GameOpen;
extern bool g_Editor_ON;
extern std::vector<std::vector<std::string>> g_CopyStack;
extern int g_CopyStackPageN;
extern float g_BoardPushHeightAdjust;
extern float g_ComPositionToPoint2fFactor;
extern float g_ComICOPositionToComPositionX;
extern float g_ComICOPositionToComPositionY;
extern float g_CarriageReturnX;
extern bool g_TXD_Scan;
extern int g_OCSCP_ThreadCount;
extern int g_Divine_ThreadCount;
extern bool g_ConnectedECD;
extern std::vector<std::shared_ptr<Ackent>> g_Ackent;
extern float g_LowtonMark;
extern int g_OCSCP_LowtonMark;
extern std::shared_ptr<Cube::CubeHESH> g_Lowton;
extern std::shared_ptr<Cube::CubeHASH_originstring> g_LowtonHash;
extern bool g_RenderHesh;
extern bool g_LowtonOn;
extern std::string g_Found_Text;
extern int g_espo_ShareOffset;
extern int g_espo_Peer;
extern float g_espo_Score;
extern float g_espo_Amount;
extern float g_espo_ECN_Amount;
extern std::string g_espo_Owner;
extern std::string g_espo_Date;
extern int g_CurrentComID;
extern float g_CurrentSharePrice;
extern int g_CurrentShareID;
extern bool g_Once;
extern int g_ShareCount;
extern int g_CurrentShareOffset;
extern int g_CurrentShareOffsetMAX;
extern int g_PEER;
extern int g_PEERMAX;
extern int g_EventOffset;
extern int g_GUItimer;
extern int g_SaveComplete_ThreadCount;
extern int g_Diviner_ThreadCount;
extern int g_Compressing;
extern bool g_BoughtCom;
extern bool g_MyOwnCom;