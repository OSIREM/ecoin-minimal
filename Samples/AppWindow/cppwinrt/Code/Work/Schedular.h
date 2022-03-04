/*

Function - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <vector>

#include "../Musion/MuType.h"
#include "../Musion/Variable.h"
#include "../Musion/Function.h"

#include "Code/myBO/icSafeL.h"

#include "Contract.h"

namespace winrt
{
	using namespace Windows;
	using namespace Windows::ApplicationModel::Core;
	using namespace Windows::Foundation;
	using namespace Windows::Foundation::Numerics;
	using namespace Windows::Foundation::Collections;
	using namespace Windows::UI;
	using namespace Windows::UI::Core;
	using namespace Windows::UI::Composition;
	using namespace Windows::UI::Xaml;
	using namespace Windows::UI::Xaml::Hosting;
	using namespace Windows::UI::Xaml::Navigation;
	using namespace Windows::UI::ViewManagement;
	using namespace Windows::UI::WindowManagement;
	using namespace Windows::UI::WindowManagement::Preview;
};

#define SCHEDULAR_MTX_OFF 0
#define SCHEDULAR_LISTEN_MTX_ON 1
#define SCHEDULAR_GATHER_MTX_ON 2
#define SCHEDULAR_RESULT_MTX_OFF 3

#define ECOIN_ENTRY_MAX 500
#define ECOIN_ENTRY_REFRESH_DEPTH 100

namespace ecoin
{
	enum ESL_Pattern
	{
		ESL_PATTERN_INTERLEAVED_O,
		ESL_PATTERN_INTERLEAVED_R,
		ESL_PATTERN_5_EACH_O,
		ESL_PATTERN_5_EACH_R,
		ESL_PATTERN_10_EACH_O,
		ESL_PATTERN_10_EACH_R,
		ESL_PATTERN_15_EACH_O,
		ESL_PATTERN_15_EACH_R,
		ESL_PATTERN_LAST,
		ESL_PATTERN_NOM
	};

	class Schedular : public ecom_base
		{
		public:
			Schedular();
			~Schedular();

			void acShutdown(bool f_MainMutex_Ext_ON = false);

			bool acSend_Query(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON = false);
			bool acSend_KeepAlive(char* f_Char, bool f_MainMutex_Ext_ON = false);
			bool acSend_Query_Angel(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON = false);
			bool acSend_KeepAlive_Angel(char* f_Char, bool f_MainMutex_Ext_ON = false);
			bool acSend_Query_PeerGraph(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON = false);
			bool acSend_Query_PeerGraphSelect(char* f_Char, int f_UI, bool f_End, int f_ShareID, int f_ShareOffset, int f_PEER, bool f_MainMutex_Ext_ON = false);
			bool acSend_Query_GlobalStorageWealth(char* f_Char, bool f_MainMutex_Ext_ON = false);
			bool acSend_Query_CMD(char* f_Char, int f_UI, bool f_End, bool f_Update = false, bool f_MainMutex_Ext_ON = false);
			bool acSend_Query_CMD_Angel(char* f_Char, int f_UI, bool f_End, bool f_Update = false, bool f_MainMutex_Ext_ON = false);

			int acNet_Client_Data(void);
			int acNet_Client_Data_Gui(void);
			int acNet_Client_Data_Angel(void);

			int ac_GetEntry(int f_EntryIdx);

			bool getWork(uint f_Pattern);

			void addContractESL(std::string f_Script);
			std::shared_ptr<Contract> getContractESL(std::string f_Script);
			void addnonceContractESL(std::string f_Script);
			void refreshContractESL(std::string f_Script);

			void DataFrame(void);
			void DataFrame_Gui(void);
			void DataFrame_Angel(void);
			void DataFramePush(void);

			void DataFrameExt(void);
			void DataFrame_GuiExt(void);
			void DataFrame_AngelExt(void);
			void PushFrameCombiner(void);

			uint m_G;
			uint m_F;

			std::shared_mutex m_MainMutex;
			std::shared_mutex m_SentMtx;
			std::shared_mutex m_PushMtx;
			std::shared_mutex m_EntrantMtx;
			bool m_SentMtx_ON;

			int m_PushThreadID;

			std::vector<std::shared_ptr<Contract>> m_vec_Contract;
			std::vector<std::shared_ptr<Contract>> m_vec_nonceContract;

			SocketSet* m_ClientSS;

			bool m_Scan;

			std::vector<std::shared_ptr<std::vector<std::vector<std::string>>>> m_Entries;
			std::vector<int> m_Entrant;

			std::vector<std::shared_ptr<std::string>> m_vec_Packet;

			int m_PushReceiveFgr;
			int m_SleepToken;

			std::shared_ptr<std::vector<std::vector<std::string>>> m_PushResult_Entry;
			std::vector<std::vector<std::shared_ptr<std::string>>> m_vec_PushPacket;
		};

	extern std::shared_ptr<Schedular> g_Schedular[3];

	extern std::string agsc_ReadElement_Sock(char* f_Charpntr, int* f_Cy, int iResult);
	extern std::string agsc_ReadElement_Sock(char* f_Charpntr, int* f_Cy);

	extern std::string agsc_ReadElement_Sock_V15(char* f_Charpntr, int* f_Cy, int iResult, bool f_isLastof = false);

	extern bool g_EntryReset;
	extern int g_QAccountID;
	extern int g_ShareID;
};

#endif