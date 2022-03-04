/*

Schedular - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Schedular.h"

using namespace ecoin;

namespace ecoin
{
#if 1
#define SCH_THR_DETACH
#endif

std::shared_ptr<Schedular> g_Schedular[3];

bool g_EntryReset = false;
int g_QAccountID = 0;
int g_ShareID = 0;

Schedular::Schedular(void)
{
	std::string f_ref_CurrentPath = "Schedular::Schedular";

	m_F = 0;
	m_G = 0;

	m_ClientSS = new SocketSet();

	m_ClientSS->m_IP = "192.64.112.79";
	m_ClientSS->m_IP_Gui = "192.64.112.79";
	m_ClientSS->m_IP_Angel = "192.64.112.79";

	m_ClientSS->m_PORT = DEFAULT_PORT;
	m_ClientSS->m_PORT_Gui = DEFAULT_PORT_GUI;
	m_ClientSS->m_PORT_Angel = DEFAULT_PORT_ANGEL;

	m_SentMtx_ON = false;

	m_PushReceiveFgr = 0;

	m_PushThreadID = 0;

	ac_Push(m_Entrant, f_ref_CurrentPath + g_ref_Div + "m_Entrant");
}

Schedular::~Schedular()
{
//...
};

void Schedular::acShutdown(bool f_MainMutex_Ext_ON)
{
#if 0
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }
#endif

	std::string f_String = "Xecoincd1:";
	f_String += "XXXXX";
	f_String += ":ecoincd1";

	m_EntrantMtx.lock();

	//register entrant
	int f_EntCount = m_Entries.size();

	if(f_EntCount > ECOIN_ENTRY_MAX)
		{
		f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
		}

	m_EntrantMtx.unlock();

	char* f_suffix = new char[2048];
	sprintf(f_suffix, ":%i", f_EntCount);

	std::string f_Result = f_String + f_suffix;
	delete[] f_suffix;

	int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)f_Result.length(), 0);

	for(int f_Jet = 0; f_Jet < m_ClientSS->m_vec_Socket.size(); f_Jet++)
		{
		iResult = send(m_ClientSS->m_vec_Socket[f_Jet], (char*)f_Result.c_str(), (int)f_Result.length(), 0);
		}

	Sleep(1500);

	closesocket(m_ClientSS->m_Socket);

	for(int f_Jet = 0; f_Jet < m_ClientSS->m_vec_Socket.size(); f_Jet++)
		{
		closesocket(m_ClientSS->m_vec_Socket[f_Jet]);
		}

	WSACleanup();

	m_Scan = false;

#if 0
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }
#endif
};

int Schedular::acNet_Client_Data(void)
{
	WSADATA wsaData;

	m_ClientSS->m_Socket = INVALID_SOCKET;

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if(iResult != 0)
		{
		printf("WSAStartup failed with error: %d\n", iResult);
		throw;
		}

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(m_ClientSS->m_IP.c_str(), m_ClientSS->m_PORT.c_str(), &hints, &result);

	if(iResult != 0)
		{
		WSACleanup();
		}

	for(ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
		// Create a SOCKET for connecting to server
		m_ClientSS->m_Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		
		if(m_ClientSS->m_Socket == INVALID_SOCKET)
			{
			WSACleanup();
			}

		// Connect to server.
		iResult = connect(m_ClientSS->m_Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		
		if(iResult == SOCKET_ERROR)
			{
			closesocket(m_ClientSS->m_Socket);

			m_ClientSS->m_Socket = INVALID_SOCKET;

			throw;
			}
		else
			{
			printf("ECN::SocketSet connection established.\n");
			}

		break;
		}

	freeaddrinfo(result);

	if(m_ClientSS->m_Socket == INVALID_SOCKET)
		{
		printf("Unable to connect to server!\n");

		WSACleanup();

		throw;
		}
	else
		{
		std::thread f_thread_DataDF(&Schedular::DataFrame, this);

#ifdef SCH_THR_DETACH
		f_thread_DataDF.detach();
#endif
		}

	for(int f_Jet = 0; f_Jet < ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_Jet++)
		{
		struct addrinfo *resultx = NULL,
			*ptrx = NULL,
			hintsx;

		ZeroMemory(&hintsx, sizeof(hintsx));

		hintsx.ai_family = AF_UNSPEC;
		hintsx.ai_socktype = SOCK_STREAM;
		hintsx.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iResult = getaddrinfo(m_ClientSS->m_IP.c_str(), m_ClientSS->m_PORT.c_str(), &hintsx, &resultx);

		if(iResult != 0)
			{
			WSACleanup();
			}

		// Attempt to connect to an address until one succeeds
		for(ptrx = resultx; ptrx != NULL; ptrx = ptrx->ai_next)
			{
			// Create a SOCKET for connecting to server
			SOCKET f_Socket = socket(ptrx->ai_family, ptrx->ai_socktype, ptrx->ai_protocol);
		
			if(f_Socket == INVALID_SOCKET)
				{
				WSACleanup();
				}

			// Connect to server.
			iResult = connect(f_Socket, ptrx->ai_addr, (int)ptrx->ai_addrlen);
		
			if(iResult == SOCKET_ERROR)
				{
				closesocket(f_Socket);

				f_Socket = INVALID_SOCKET;

				throw;
				}
			else
				{
				printf("ECN::SocketSet connection established.\n");
				}

			if(f_Socket == INVALID_SOCKET)
				{
				printf("Unable to connect to server!\n");

				WSACleanup();

				throw;
				}
			else
				{
				m_ClientSS->m_vec_Socket.push_back(f_Socket);

				std::vector<std::shared_ptr<std::string>> f_vec_Str;

				m_vec_PushPacket.push_back(f_vec_Str);
				}

			break;
			}

		freeaddrinfo(resultx);

		std::thread f_thread_Data(&Schedular::DataFramePush, this);

#ifdef SCH_THR_DETACH
		f_thread_Data.detach();
#endif
		}

	//single push combiner
	std::thread f_thread_Push_Ext(&Schedular::PushFrameCombiner, this);

#ifdef SCH_THR_DETACH
	f_thread_Push_Ext.detach();
#endif

	return 1;
}

// Create a task that will be run on a background thread.
void Schedular::DataFramePush(void)
{
	m_PushMtx.lock();

	int f_PushID = m_PushThreadID;

	m_PushThreadID++;

	m_vec_PushPacket[f_PushID].clear();

	m_PushMtx.unlock();

	m_Scan = true;
	while(m_Scan == true)
		{
		char f_recvbuf[DEFAULT_BUFLEN];

		ag_PrepareChar(f_recvbuf, DEFAULT_BUFLEN);

		int iResult = recv(m_ClientSS->m_vec_Socket[f_PushID], f_recvbuf, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			m_vec_PushPacket[f_PushID].push_back(std::make_shared<std::string>(f_recvbuf));
			}
		else
			{
			m_Scan = false;
			}
		}
}

// Create a task that will be run on a background thread.
void Schedular::DataFrame(void)
{
	std::thread f_thread_Ext(&Schedular::DataFrameExt, this);

#ifdef SCH_THR_DETACH
	f_thread_Ext.detach();
#endif

	m_vec_Packet.clear();

	m_Scan = true;
	while(m_Scan == true)
		{
		char recvbuf[DEFAULT_BUFLEN];

		ag_PrepareChar(recvbuf, DEFAULT_BUFLEN);

		int iResult = recv(m_ClientSS->m_Socket, recvbuf, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			m_vec_Packet.push_back(std::make_shared<std::string>(recvbuf));
			}
		else
			{
			m_Scan = false;
			}
		}
}

void Schedular::DataFrameExt(void)
{
	while(m_Scan == true)
		{
		if(m_vec_Packet.size() > 0)
			{
			Sleep(18);

			std::shared_ptr<std::string> f_current_Packet = m_vec_Packet[0];

			int iResult = f_current_Packet->length();

			if(f_current_Packet->at(0) == 'D')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_Entries.push_back(f_Entry);

				std::string f_Suffix = agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(f_Suffix.c_str()));

				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'O')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_Entries.push_back(f_Entry);

				std::string f_Suffix = agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(f_Suffix.c_str()));

				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'G')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_ModifEntry = std::make_shared<std::vector<std::vector<std::string>>>();

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry->push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry->push_back(f_vec_ElementA);
				f_ModifEntry->push_back(f_vec_ElementB);

				m_Entries.push_back(f_ModifEntry);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));

				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'R')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;

				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));

							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_ModifEntry = std::make_shared<std::vector<std::vector<std::string>>>();

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry->push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;
				std::vector<std::string> f_vec_ElementC;
				std::vector<std::string> f_vec_ElementD;
				std::vector<std::string> f_vec_ElementE;
				std::vector<std::string> f_vec_ElementF;
				std::vector<std::string> f_vec_ElementG;
				std::vector<std::string> f_vec_ElementH;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementC.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementD.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementE.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementF.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementG.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementH.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry->push_back(f_vec_ElementA);
				f_ModifEntry->push_back(f_vec_ElementB);
				f_ModifEntry->push_back(f_vec_ElementC);
				f_ModifEntry->push_back(f_vec_ElementD);
				f_ModifEntry->push_back(f_vec_ElementE);
				f_ModifEntry->push_back(f_vec_ElementF);
				f_ModifEntry->push_back(f_vec_ElementG);
				f_ModifEntry->push_back(f_vec_ElementH);

				m_Entries.push_back(f_ModifEntry);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));

				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'M')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();
				std::vector<std::string> f_vec_Element;

				f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_Entry->push_back(f_vec_Element);

				m_Entries.push_back(f_Entry);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));

				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'K')
				{
				//...
				}
			else
				{
				//...
				}

			//message pump reorder packet array
			for(int f_Int = 0; f_Int < m_vec_Packet.size() - 1; f_Int++)
				{
				m_vec_Packet[f_Int] = m_vec_Packet[f_Int + 1];
				}

			m_vec_Packet.pop_back();

			m_EntrantMtx.lock();

			//conditional entry reorder
			if(m_Entries.size() > ECOIN_ENTRY_MAX)
				{
				for(int f_Jet = (ECOIN_ENTRY_MAX - (ECOIN_ENTRY_REFRESH_DEPTH * 2)); f_Jet < (ECOIN_ENTRY_MAX - 1); f_Jet++)
					{
					for(int f_Int = f_Jet; f_Int < m_Entries.size() - 1; f_Int++)
						{
						m_Entries[f_Int] = m_Entries[f_Int + 1];
						}

					for(int f_Int = f_Jet; f_Int < m_Entrant.size() - 1; f_Int++)
						{
						m_Entrant[f_Int] = m_Entrant[f_Int + 1];
						}
					}

				for(int f_Jet = 0; f_Jet < ECOIN_ENTRY_REFRESH_DEPTH; f_Jet++)
					{
					m_Entrant.pop_back();
					m_Entries.pop_back();
					}
				}

			m_EntrantMtx.unlock();
			}
		}
}

void Schedular::PushFrameCombiner(void)
{
	int f_currentPosition_FieldIDX = 0;
	int f_currentPosition_RecordIDX = 0;
	int f_currentPosition_Field_Count = 0;
	int f_proPosition_FieldIDX = 0;
	int f_proPosition_RecordIDX = 0;
	std::string f_proPosition_Incomplete_FC;
	std::string f_proPosition_Incomplete_MS;
	bool f_onFieldCount = false;

	std::shared_ptr<std::vector<std::string>> f_svec_Element = nullptr;

	std::vector<int> f_vec_StartNew;

	f_vec_StartNew.clear();

	for(int f_Jet = 0; f_Jet < m_vec_PushPacket.size(); f_Jet++)
		{
		f_vec_StartNew.push_back(0);
		}

	m_PushResult_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

	int f_StartIDX = 0;
	int f_EndIDX = 0;
	int f_CountIDX = 0;

	std::string f_Prefix;
	std::string f_PreStartIDX;
	std::string f_PreEndIDX;
	std::string f_PreCountIDX;
	std::string f_PreSuffix;
	std::string f_String;

	int f_headMode = 0;

	bool f_Pref = false;
	bool f_EndFound = false;

	while(m_Scan == true)
		{
		if(m_vec_PushPacket[m_PushReceiveFgr].size() > 0)
			{
			std::shared_ptr<std::string> f_current_Packet = m_vec_PushPacket[m_PushReceiveFgr][0];
			
			if((f_current_Packet->at(0) == 'K') && (f_proPosition_RecordIDX == 0))
				{
				for(int f_XY = 0; f_XY < m_vec_PushPacket[m_PushReceiveFgr].size() - 1; f_XY++)
					{
					m_vec_PushPacket[m_PushReceiveFgr][f_XY] = m_vec_PushPacket[m_PushReceiveFgr][f_XY + 1];
					}

				m_vec_PushPacket[m_PushReceiveFgr].pop_back();

				m_SleepToken = 0;
				}
			else
				{
				int f_StartNew = f_vec_StartNew[m_PushReceiveFgr];

				if(f_StartNew < 0)
					{
					f_StartNew = 0;
					}

				int iResult = f_current_Packet->length();

				if(iResult > DEFAULT_BUFLEN)
					{
					iResult = DEFAULT_BUFLEN;
					}

				if((f_current_Packet->at(f_StartNew) == 'E') && (f_proPosition_RecordIDX == 0))
					{
					  /////////////////////////////////
					 // Element Procedure
					// START 'E' PACKAGE [0-30]
					f_Prefix.clear();
					f_PreStartIDX.clear();
					f_PreEndIDX.clear();
					f_PreCountIDX.clear();
					f_PreSuffix.clear();

					f_headMode = 0;

					f_Pref = false;

					f_StartNew++;
					}

				//clear string
				f_String.clear();
				f_EndFound = false;
				
				   /////////////////////////////////////
				  // Push MultiPart-Message Combiner
				 // Element Procedure
				// PRODUCE 'E' PACKAGE [X-30]
				for(int f_Count = f_StartNew; f_Count < iResult; f_Count++)
					{
					char f_CharC = f_current_Packet->at(f_Count);

					if(f_Pref == false)
						{
						if(f_CharC == ':')
							{
							f_headMode++;
							}
						else if(((f_CharC >= '0') && (f_CharC <= '9')) || ((f_CharC >= 'a') && (f_CharC <= 'z')) || ((f_CharC >= 'A') && (f_CharC <= 'Z')))
							{
							switch(f_headMode)
								{
								case 0:
									{
									f_Prefix.push_back(f_CharC);
									}break;

								case 1:
									{
									f_PreStartIDX.push_back(f_CharC);
									}break;

								case 2:
									{
									f_PreEndIDX.push_back(f_CharC);
									}break;

								case 3:
									{
									f_PreCountIDX.push_back(f_CharC);
									}break;

								case 4:
									{
									f_PreSuffix.push_back(f_CharC);
									}break;

								default:
									{
									f_String.push_back(f_CharC);

									f_Pref = true;
									}
								}
							}
						else
							{
							throw;
							}
						}
					else
						{
						if(f_CharC == '#')
							{
							if(f_Count >= iResult - 1)
								{
								f_StartNew = iResult;

								f_Count = iResult;

								iResult = f_String.length();

								f_EndFound = true;
								}
							else
								{
								f_StartNew = f_Count + 1;

								f_Count = iResult;
								}
							}
						else if(f_CharC == ':')
							{
							f_String.push_back(f_CharC);
							}
						else if(f_CharC == '-')
							{
							f_String.push_back(f_CharC);
							}
						else if(f_CharC == '.')
							{
							f_String.push_back(f_CharC);
							}
						else if((f_CharC >= '0') && (f_CharC <= '9'))
							{
							f_String.push_back(f_CharC);
							}
						else if((f_CharC >= 'a') && (f_CharC <= 'z'))
							{
							f_String.push_back(f_CharC);
							}
						else if((f_CharC >= 'A') && (f_CharC <= 'Z'))
							{
							f_String.push_back(f_CharC);
							}
						else
							{
							throw;
							}
						}

					if((f_Count == iResult - 1) && (f_EndFound == false))
						{
						f_StartNew = iResult;

						f_Count = iResult;

						iResult = f_String.length();
						}
					}

				f_StartIDX = atoi(f_PreStartIDX.c_str());
				f_EndIDX = atoi(f_PreEndIDX.c_str());
				f_CountIDX = atoi(f_PreCountIDX.c_str());

				int* f_Cy = new int;

				*(f_Cy) = 0;

				if(m_PushResult_Entry->size() != f_CountIDX)
					{
					m_PushResult_Entry->resize(f_CountIDX);
					}

				int f_FieldCount = 0;
				int f_RecordCount = f_EndIDX - f_StartIDX;
			
				bool f_OnLine = true;

				int f_CycleStart = 0;
				int f_CycleEnd = f_RecordCount;

				if(f_proPosition_RecordIDX > 0)
					{
					f_currentPosition_RecordIDX = f_proPosition_RecordIDX;

					f_CycleStart = f_proPosition_RecordIDX;
					f_CycleEnd = f_EndIDX;
					}
				else
					{
					f_CycleStart += f_StartIDX;
					f_CycleEnd = f_EndIDX;
					}

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = f_CycleStart; (f_RecCount < f_CycleEnd) && (f_OnLine == true); f_RecCount++)
						{
						std::shared_ptr<std::vector<std::string>> f_vec_Element = std::make_shared<std::vector<std::string>>();

						bool f_isLastof = false;

						if(f_proPosition_FieldIDX == 0)
							{
							std::string f_StringCount = agsc_ReadElement_Sock_V15((char*)f_String.c_str(), f_Cy, iResult, f_isLastof);

							if(f_StringCount.at(f_StringCount.length() - 1) != '&')
								{
								f_FieldCount = atoi(f_StringCount.c_str());

								f_currentPosition_FieldIDX = 0;
								f_currentPosition_Field_Count = f_FieldCount;

								for(int f_FldCount = 0; (f_FldCount < f_FieldCount) && (f_OnLine == true); f_FldCount++)
									{
									if((f_RecCount >= (f_CycleEnd - 1)) && (f_FldCount >= (f_FieldCount - 1)))
										{
										f_isLastof = true;
										}

									std::string f_StringField = agsc_ReadElement_Sock_V15((char*)f_String.c_str(), f_Cy, iResult, f_isLastof);

									if(f_StringField.at(f_StringField.length() - 1) != '&')
										{
										f_vec_Element->push_back(f_StringField);

										f_currentPosition_FieldIDX++;
										}
									else
										{
										if(f_StringField.at(f_StringField.length() - 2) == '&')
											{
											f_OnLine = false;

											f_proPosition_Incomplete_MS.clear();

											for(int f_Jet = 0; f_Jet < f_StringField.length(); f_Jet++)
												{
												char f_C = f_StringField.at(f_Jet);

												if(f_C == ':')
													{
													f_Jet = f_StringField.length();
													}
												else
													{
													if(f_C != '&')
														{
														f_proPosition_Incomplete_MS.push_back(f_C);
														}
													}
												}

											f_vec_Element->push_back(f_proPosition_Incomplete_MS);

											f_proPosition_Incomplete_MS.clear();

											f_currentPosition_FieldIDX++;

											f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
											f_proPosition_RecordIDX = f_currentPosition_RecordIDX;

											f_svec_Element = f_vec_Element;
											}
										else
											{
											f_OnLine = false;

											f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
											f_proPosition_RecordIDX = f_currentPosition_RecordIDX;

											f_proPosition_Incomplete_MS.clear();

											for(int f_Jet = 0; f_Jet < f_StringField.length(); f_Jet++)
												{
												char f_C = f_StringField.at(f_Jet);

												if(f_C == ':')
													{
													f_Jet = f_StringField.length();
													}
												else
													{
													if(f_C != '&')
														{
														f_proPosition_Incomplete_MS.push_back(f_C);
														}
													}
												}

											f_svec_Element = f_vec_Element;
											}
										}
									}

								if((f_vec_Element->size() == f_FieldCount) && (f_OnLine == true))
									{
									int f_AdIndex = atoi(f_vec_Element->at(f_vec_Element->size() - 4).c_str());

									if(m_PushResult_Entry->at(f_AdIndex).size() >= f_FieldCount)
										{
										f_AdIndex = f_RecCount;
										}
							
#ifdef ECOIN_DEBUG_BREAKS
									if((m_PushResult_Entry->at(f_AdIndex).size() >= f_FieldCount) || (f_AdIndex < 0) || (f_AdIndex >= m_PushResult_Entry->size()))
										{
										__debugbreak();
										}
									else
										{
#endif

										if((f_AdIndex >= 0) && (f_AdIndex < f_CountIDX))
											{
											for(int f_XYZ = 0; f_XYZ < f_vec_Element->size(); f_XYZ++)
												{
												m_PushResult_Entry->at(f_AdIndex).push_back(f_vec_Element->at(f_XYZ));
												}

											f_currentPosition_RecordIDX = f_AdIndex + 1;

											f_proPosition_FieldIDX = 0;
											f_proPosition_RecordIDX = 0;

											f_svec_Element = nullptr;
											}
#ifdef ECOIN_DEBUG_BREAKS
										}
#endif
									}
								}
							else
								{
								if(f_StringCount.at(f_StringCount.length() - 2) == '&')
									{
									f_OnLine = false;

									f_proPosition_Incomplete_FC.clear();

									for(int f_Jet = 0; f_Jet < f_StringCount.length(); f_Jet++)
										{
										char f_C = f_StringCount.at(f_Jet);

										if(f_C == ':')
											{
											f_Jet = f_StringCount.length();
											}
										else
											{
											if(f_C != '&')
												{
												f_proPosition_Incomplete_FC.push_back(f_C);
												}
											}
										}

									f_FieldCount = atoi(f_proPosition_Incomplete_FC.c_str());

									f_proPosition_Incomplete_FC.clear();

									f_currentPosition_FieldIDX = 0;
									f_currentPosition_Field_Count = f_FieldCount;

									f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
									f_proPosition_RecordIDX = f_currentPosition_RecordIDX;

									f_svec_Element = f_vec_Element;
									}
								else
									{
									f_OnLine = false;

									f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
									f_proPosition_RecordIDX = f_currentPosition_RecordIDX;

									f_proPosition_Incomplete_FC.clear();

									for(int f_Jet = 0; f_Jet < f_StringCount.length(); f_Jet++)
										{
										char f_C = f_StringCount.at(f_Jet);

										if(f_C != '&')
											{
											f_proPosition_Incomplete_FC.push_back(f_C);
											}
										}

									f_svec_Element = f_vec_Element;
									}
								}
							}
						else
							{
							f_FieldCount = f_currentPosition_Field_Count;

							if(f_proPosition_Incomplete_FC.length() > 0)
								{
								std::string f_StringFieldCount = agsc_ReadElement_Sock_V15((char*)f_String.c_str(), f_Cy, iResult, f_isLastof);

								if(f_StringFieldCount.length() > 0)
									{
									if(f_StringFieldCount.at(f_StringFieldCount.length() - 1) != '&')
										{
										std::string f_newFieldCount = f_proPosition_Incomplete_FC + f_StringFieldCount;

										f_FieldCount = atoi(f_newFieldCount.c_str());

										f_proPosition_Incomplete_MS.clear();
										f_proPosition_Incomplete_FC.clear();

										f_currentPosition_FieldIDX = 0;

										f_proPosition_FieldIDX = 0;
										f_proPosition_RecordIDX = 0;
										}
									else
										{
										if(f_StringFieldCount.at(f_StringFieldCount.length() - 2) == '&')
											{
											f_OnLine = false;

											f_proPosition_Incomplete_FC.clear();

											for(int f_Jet = 0; f_Jet < f_StringFieldCount.length(); f_Jet++)
												{
												char f_C = f_StringFieldCount.at(f_Jet);

												if(f_C == ':')
													{
													f_Jet = f_StringFieldCount.length();
													}
												else
													{
													if(f_C != '&')
														{
														f_proPosition_Incomplete_FC.push_back(f_C);
														}
													}
												}

											f_proPosition_Incomplete_MS.clear();
											f_proPosition_Incomplete_FC.clear();

											f_currentPosition_FieldIDX = 0;

											f_proPosition_FieldIDX = 0;
											f_proPosition_RecordIDX = 0;
											}
										else
											{
											f_OnLine = false;

											f_proPosition_FieldIDX = 0;
											f_proPosition_RecordIDX = 0;

											f_proPosition_Incomplete_FC.clear();

											for(int f_Jet = 0; f_Jet < f_StringFieldCount.length(); f_Jet++)
												{
												char f_C = f_StringFieldCount.at(f_Jet);

												if(f_C == ':')
													{
													f_Jet = f_StringFieldCount.length();
													}
												else
													{
													if(f_C != '&')
														{
														f_proPosition_Incomplete_MS.push_back(f_C);
														}
													}
												}
											}
										}
									}
								else
									{
									f_FieldCount = atoi(f_proPosition_Incomplete_FC.c_str());

									f_proPosition_Incomplete_MS.clear();
									f_proPosition_Incomplete_FC.clear();

									f_currentPosition_FieldIDX = 0;

									f_proPosition_FieldIDX = 0;
									f_proPosition_RecordIDX = 0;
									}
								}

							f_currentPosition_FieldIDX = f_proPosition_FieldIDX;

							for(int f_FldCount = f_proPosition_FieldIDX; (f_FldCount < f_FieldCount) && (f_OnLine == true); f_FldCount++)
								{
								if((f_RecCount >= (f_CycleEnd - 1)) && (f_FldCount >= (f_FieldCount - 1)))
									{
									f_isLastof = true;
									}

								std::string f_StringField = agsc_ReadElement_Sock_V15((char*)f_String.c_str(), f_Cy, iResult, f_isLastof);

								if(f_StringField.length() > 0)
									{
									if(f_StringField.at(f_StringField.length() - 1) != '&')
										{
										f_svec_Element->push_back(f_proPosition_Incomplete_MS + f_StringField);

										f_proPosition_Incomplete_MS.clear();
										f_proPosition_Incomplete_FC.clear();

										f_currentPosition_FieldIDX++;

										f_proPosition_FieldIDX = 0;
										f_proPosition_RecordIDX = 0;
										}
									else
										{
										if(f_StringField.at(f_StringField.length() - 1) != '&')
											{
											f_OnLine = false;

											f_svec_Element->push_back(f_proPosition_Incomplete_MS + f_StringField);

											f_proPosition_Incomplete_MS.clear();

											for(int f_Jet = 0; f_Jet < f_StringField.length(); f_Jet++)
												{
												char f_C = f_StringField.at(f_Jet);

												if(f_C == ':')
													{
													f_Jet = f_StringField.length();
													}
												else
													{
													if(f_C != '&')
														{
														f_proPosition_Incomplete_MS.push_back(f_C);
														}
													}
												}

											f_svec_Element->push_back(f_proPosition_Incomplete_MS);

											f_proPosition_Incomplete_MS.clear();
											f_proPosition_Incomplete_FC.clear();

											f_currentPosition_FieldIDX++;

											f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
											f_proPosition_RecordIDX = f_currentPosition_RecordIDX;
											}
										else
											{
											f_OnLine = false;

											f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
											f_proPosition_RecordIDX = f_currentPosition_RecordIDX;

											f_proPosition_Incomplete_MS.clear();
											f_proPosition_Incomplete_FC.clear();

											for(int f_Jet = 0; f_Jet < f_StringField.length(); f_Jet++)
												{
												char f_C = f_StringField.at(f_Jet);

												if(f_C == ':')
													{
													f_Jet = f_StringField.length();
													}
												else
													{
													if(f_C != '&')
														{
														f_proPosition_Incomplete_MS.push_back(f_C);
														}
													}
												}
											}
										}
									}
								else
									{
									f_svec_Element->push_back(f_proPosition_Incomplete_MS);

									f_proPosition_Incomplete_MS.clear();
									f_proPosition_Incomplete_FC.clear();

									f_currentPosition_FieldIDX++;

									f_proPosition_FieldIDX = 0;
									f_proPosition_RecordIDX = 0;
									}
								}

							if((f_svec_Element->size() == f_FieldCount) && (f_OnLine == true))
								{
								int f_AdIndex = atoi(f_svec_Element.get()->at(f_svec_Element->size() - 4).c_str());

								if(m_PushResult_Entry->at(f_AdIndex).size() >= f_FieldCount)
									{
									f_AdIndex = f_RecCount;
									}
							
#ifdef ECOIN_DEBUG_BREAKS
								if((m_PushResult_Entry->at(f_AdIndex).size() >= f_FieldCount) || (f_AdIndex < 0) || (f_AdIndex >= m_PushResult_Entry->size()))
									{
									__debugbreak();
									}
								else
									{
#endif

									if((f_AdIndex >= 0) && (f_AdIndex < f_CountIDX))
										{
										for(int f_XYZ = 0; f_XYZ < f_svec_Element->size(); f_XYZ++)
											{
											m_PushResult_Entry->at(f_AdIndex).push_back(f_svec_Element->at(f_XYZ));
											}

										f_currentPosition_RecordIDX = f_AdIndex + 1;

										f_proPosition_FieldIDX = 0;
										f_proPosition_RecordIDX = 0;

										f_svec_Element = nullptr;
										}
#ifdef ECOIN_DEBUG_BREAKS
									}
#endif
								}
							}
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));
					
					m_PushResult_Entry->at(0).push_back(f_vec_Element[0]);

					f_proPosition_FieldIDX = 0;
					f_proPosition_RecordIDX = 0;
					f_currentPosition_RecordIDX = 0;
					f_currentPosition_FieldIDX = 0;

					f_svec_Element = nullptr;

					f_OnLine = true;
					}

				if((f_OnLine == true) && (f_EndFound == false))
					{
					f_vec_StartNew[m_PushReceiveFgr] = f_StartNew;

					m_PushReceiveFgr++;

					if(m_PushReceiveFgr >= ECOIN_ELEMENT_PUSH_THREAD_COUNT)
						{
						m_PushReceiveFgr = 0;
						}
					}
				else
					{
					if(f_EndFound == false)
						{
						for(int f_XY = 0; f_XY < m_vec_PushPacket[m_PushReceiveFgr].size() - 1; f_XY++)
							{
							m_vec_PushPacket[m_PushReceiveFgr][f_XY] = m_vec_PushPacket[m_PushReceiveFgr][f_XY + 1];
							}

						m_vec_PushPacket[m_PushReceiveFgr].pop_back();

						f_vec_StartNew[m_PushReceiveFgr] = 0;
						}
					else
						{
						for(int f_XY = 0; f_XY < m_vec_PushPacket[m_PushReceiveFgr].size() - 1; f_XY++)
							{
							m_vec_PushPacket[m_PushReceiveFgr][f_XY] = m_vec_PushPacket[m_PushReceiveFgr][f_XY + 1];
							}

						m_vec_PushPacket[m_PushReceiveFgr].pop_back();

						f_vec_StartNew[m_PushReceiveFgr] = 0;
					
						m_PushReceiveFgr++;

						if(m_PushReceiveFgr >= ECOIN_ELEMENT_PUSH_THREAD_COUNT)
							{
							m_PushReceiveFgr = 0;
							}
						}
					}

				//count determine win conditions
				bool f_FullUp = true;

				for(int f_Jet = 0; f_Jet < f_CountIDX; f_Jet++)
					{
					if(m_PushResult_Entry->at(f_Jet).size() != f_FieldCount)
						{
						f_FullUp = false;
						}
					}

				if(f_FullUp == true) //win conditions!
					{
					m_Entries.push_back(m_PushResult_Entry);

					m_PushResult_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

					m_PushReceiveFgr = 0;

					int f_PossibleEntrant = atoi(f_PreSuffix.c_str());

					if(f_PossibleEntrant > ECOIN_ENTRY_MAX)
						{
						f_PossibleEntrant = f_PossibleEntrant - ECOIN_ENTRY_REFRESH_DEPTH;
						}

					m_Entrant.push_back(f_PossibleEntrant);

					for(int f_XY = 0; f_XY < m_vec_PushPacket.size(); f_XY++)
						{
						m_vec_PushPacket[f_XY].clear();

						f_vec_StartNew[f_XY] = 0;
						}
					}

				delete f_Cy;

				m_SleepToken = 0;
				}
			}
		else
			{
			if(m_SleepToken >= 5)
				{
				m_PushReceiveFgr++;

				if(m_PushReceiveFgr >= ECOIN_ELEMENT_PUSH_THREAD_COUNT)
					{
					m_PushReceiveFgr = 0;
					}

				m_SleepToken++;

				if(m_SleepToken >= 7)
					{
					m_SleepToken = 0;
					}
				}
			else
				{
				m_PushReceiveFgr = 0;

				Sleep(600);

				m_SleepToken++;
				}
			}
		}
}

int Schedular::acNet_Client_Data_Gui(void)
{
	WSADATA wsaData;

	m_ClientSS->m_Socket = INVALID_SOCKET;

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if(iResult != 0)
		{
		printf("WSAStartup failed with error: %d\n", iResult);

		throw;
		}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(m_ClientSS->m_IP_Gui.c_str(), m_ClientSS->m_PORT_Gui.c_str(), &hints, &result);

	if(iResult != 0)
		{
		WSACleanup();
		}

	// Attempt to connect to an address until one succeeds
	for(ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
		// Create a SOCKET for connecting to server
		m_ClientSS->m_Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		
		if(m_ClientSS->m_Socket == INVALID_SOCKET)
			{
			WSACleanup();
			}

		// Connect to server.
		iResult = connect(m_ClientSS->m_Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		
		if(iResult == SOCKET_ERROR)
			{
			closesocket(m_ClientSS->m_Socket);

			m_ClientSS->m_Socket = INVALID_SOCKET;

			throw;
			}
		else
			{
			printf("ECN::SocketSet connection established.\n");
			}

		break;
		}

	freeaddrinfo(result);

	if(m_ClientSS->m_Socket == INVALID_SOCKET)
		{
		printf("Unable to connect to server!\n");

		WSACleanup();

		throw;
		}
	else
		{
		std::thread f_thread_Data(&Schedular::DataFrame_Gui, this);

#ifdef SCH_THR_DETACH
		f_thread_Data.detach();
#endif
		}

	for(int f_Jet = 0; f_Jet < ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_Jet++)
		{
		struct addrinfo *resultx = NULL,
			*ptrx = NULL,
			hintsx;

		ZeroMemory(&hintsx, sizeof(hintsx));

		hintsx.ai_family = AF_UNSPEC;
		hintsx.ai_socktype = SOCK_STREAM;
		hintsx.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iResult = getaddrinfo(m_ClientSS->m_IP_Gui.c_str(), m_ClientSS->m_PORT_Gui.c_str(), &hintsx, &resultx);

		if(iResult != 0)
			{
			WSACleanup();
			}

		// Attempt to connect to an address until one succeeds
		for(ptrx = resultx; ptrx != NULL; ptrx = ptrx->ai_next)
			{
			// Create a SOCKET for connecting to server
			SOCKET f_Socket = socket(ptrx->ai_family, ptrx->ai_socktype, ptrx->ai_protocol);
		
			if(f_Socket == INVALID_SOCKET)
				{
				WSACleanup();
				}

			// Connect to server.
			iResult = connect(f_Socket, ptrx->ai_addr, (int)ptrx->ai_addrlen);
		
			if(iResult == SOCKET_ERROR)
				{
				closesocket(f_Socket);

				f_Socket = INVALID_SOCKET;

				throw;
				}
			else
				{
				printf("ECN::SocketSet connection established.\n");
				}

			if(f_Socket == INVALID_SOCKET)
				{
				printf("Unable to connect to server!\n");

				WSACleanup();

				throw;
				}
			else
				{
				m_ClientSS->m_vec_Socket.push_back(f_Socket);

				std::vector<std::shared_ptr<std::string>> f_vec_Str;

				m_vec_PushPacket.push_back(f_vec_Str);
				}

			break;
			}

		freeaddrinfo(resultx);

		std::thread f_thread_Data(&Schedular::DataFramePush, this);

#ifdef SCH_THR_DETACH
		f_thread_Data.detach();
#endif
		}

	//single push combiner
	std::thread f_thread_Push_Ext(&Schedular::PushFrameCombiner, this);

#ifdef SCH_THR_DETACH
	f_thread_Push_Ext.detach();
#endif

	return 1;
}

void Schedular::DataFrame_Gui(void)
{
	std::thread f_thread_Ext(&Schedular::DataFrame_GuiExt, this);

#ifdef SCH_THR_DETACH
	f_thread_Ext.detach();
#endif

	m_vec_Packet.clear();

	m_Scan = true;
	while(m_Scan == true)
		{
		char recvbuf[DEFAULT_BUFLEN];

		ag_PrepareChar(recvbuf, DEFAULT_BUFLEN);

		int iResult = recv(m_ClientSS->m_Socket, recvbuf, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			m_vec_Packet.push_back(std::make_shared<std::string>(recvbuf));
			}
		else
			{
			m_Scan = false;
			}
		}
}

void Schedular::DataFrame_GuiExt(void)
{
	while(m_Scan == true)
		{
		if(m_vec_Packet.size() > 0)
			{
			Sleep(18);

			std::shared_ptr<std::string> f_current_Packet = m_vec_Packet[0];

			int iResult = f_current_Packet->length();

			if(f_current_Packet->at(0) == 'D')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_Entries.push_back(f_Entry);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));

				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'G')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_ModifEntry = std::make_shared<std::vector<std::vector<std::string>>>();

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry->push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry->push_back(f_vec_ElementA);
				f_ModifEntry->push_back(f_vec_ElementB);

				m_Entries.push_back(f_ModifEntry);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));

				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'R')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_ModifEntry = std::make_shared<std::vector<std::vector<std::string>>>();

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry->push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;
				std::vector<std::string> f_vec_ElementC;
				std::vector<std::string> f_vec_ElementD;
				std::vector<std::string> f_vec_ElementE;
				std::vector<std::string> f_vec_ElementF;
				std::vector<std::string> f_vec_ElementG;
				std::vector<std::string> f_vec_ElementH;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementC.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementD.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementE.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementF.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementG.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementH.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry->push_back(f_vec_ElementA);
				f_ModifEntry->push_back(f_vec_ElementB);
				f_ModifEntry->push_back(f_vec_ElementC);
				f_ModifEntry->push_back(f_vec_ElementD);
				f_ModifEntry->push_back(f_vec_ElementE);
				f_ModifEntry->push_back(f_vec_ElementF);
				f_ModifEntry->push_back(f_vec_ElementG);
				f_ModifEntry->push_back(f_vec_ElementH);

				m_Entries.push_back(f_ModifEntry);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));

				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'M')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();
				std::vector<std::string> f_vec_Element;

				f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_Entry->push_back(f_vec_Element);

				m_Entries.push_back(f_Entry);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));

				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'K')
				{
				//...
				}
			else
				{
				//...
				}

			//message pump reorder packet array
			for(int f_Int = 0; f_Int < m_vec_Packet.size() - 1; f_Int++)
				{
				m_vec_Packet[f_Int] = m_vec_Packet[f_Int + 1];
				}

			m_vec_Packet.pop_back();

			m_EntrantMtx.lock();

			//conditional entry reorder
			if(m_Entries.size() > ECOIN_ENTRY_MAX)
				{
				for(int f_Jet = (ECOIN_ENTRY_MAX - (ECOIN_ENTRY_REFRESH_DEPTH * 2)); f_Jet < (ECOIN_ENTRY_MAX - 1); f_Jet++)
					{
					for(int f_Int = f_Jet; f_Int < m_Entries.size() - 1; f_Int++)
						{
						m_Entries[f_Int] = m_Entries[f_Int + 1];
						}

					for(int f_Int = f_Jet; f_Int < m_Entrant.size() - 1; f_Int++)
						{
						m_Entrant[f_Int] = m_Entrant[f_Int + 1];
						}
					}

				for(int f_Jet = 0; f_Jet < ECOIN_ENTRY_REFRESH_DEPTH; f_Jet++)
					{
					m_Entrant.pop_back();
					m_Entries.pop_back();
					}
				}

			m_EntrantMtx.unlock();
			}
		}
}

int Schedular::acNet_Client_Data_Angel(void)
{
	WSADATA wsaData;
	m_ClientSS->m_Socket = INVALID_SOCKET;

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if(iResult != 0)
		{
		printf("WSAStartup failed with error: %d\n", iResult);
		throw;
		}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(m_ClientSS->m_IP_Angel.c_str(), m_ClientSS->m_PORT_Angel.c_str(), &hints, &result);

	if(iResult != 0)
		{
		WSACleanup();
		}

	// Attempt to connect to an address until one succeeds
	for(ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
		// Create a SOCKET for connecting to server
		m_ClientSS->m_Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		
		if(m_ClientSS->m_Socket == INVALID_SOCKET)
			{
			WSACleanup();
			}

		// Connect to server.
		iResult = connect(m_ClientSS->m_Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		
		if(iResult == SOCKET_ERROR)
			{
			closesocket(m_ClientSS->m_Socket);

			m_ClientSS->m_Socket = INVALID_SOCKET;

			throw;
			}
		else
			{
			printf("ECN::SocketSet connection established.\n");
			}

		break;
		}

	freeaddrinfo(result);

	if(m_ClientSS->m_Socket == INVALID_SOCKET)
		{
		printf("Unable to connect to server!\n");

		WSACleanup();

		throw;
		}
	else
		{
		// Run task on a dedicated high priority background thread.
		std::thread f_thread_Data_Angel(&Schedular::DataFrame_Angel, this);

#ifdef SCH_THR_DETACH
		f_thread_Data_Angel.detach();
#endif
		}

	for(int f_Jet = 0; f_Jet < ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_Jet++)
		{
		struct addrinfo *resultx = NULL,
			*ptrx = NULL,
			hintsx;

		ZeroMemory(&hintsx, sizeof(hintsx));

		hintsx.ai_family = AF_UNSPEC;
		hintsx.ai_socktype = SOCK_STREAM;
		hintsx.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iResult = getaddrinfo(m_ClientSS->m_IP_Angel.c_str(), m_ClientSS->m_PORT_Angel.c_str(), &hintsx, &resultx);

		if(iResult != 0)
			{
			WSACleanup();
			}

		// Attempt to connect to an address until one succeeds
		for(ptrx = resultx; ptrx != NULL; ptrx = ptrx->ai_next)
			{
			// Create a SOCKET for connecting to server
			SOCKET f_Socket = socket(ptrx->ai_family, ptrx->ai_socktype, ptrx->ai_protocol);
		
			if(f_Socket == INVALID_SOCKET)
				{
				WSACleanup();
				}

			// Connect to server.
			iResult = connect(f_Socket, ptrx->ai_addr, (int)ptrx->ai_addrlen);
		
			if(iResult == SOCKET_ERROR)
				{
				closesocket(f_Socket);

				f_Socket = INVALID_SOCKET;

				throw;
				}
			else
				{
				printf("ECN::SocketSet connection established.\n");
				}

			if(f_Socket == INVALID_SOCKET)
				{
				printf("Unable to connect to server!\n");

				WSACleanup();

				throw;
				}
			else
				{
				m_ClientSS->m_vec_Socket.push_back(f_Socket);

				std::vector<std::shared_ptr<std::string>> f_vec_Str;

				m_vec_PushPacket.push_back(f_vec_Str);
				}

			break;
			}

		freeaddrinfo(resultx);

		std::thread f_thread_Data(&Schedular::DataFramePush, this);

#ifdef SCH_THR_DETACH
		f_thread_Data.detach();
#endif
		}

	//single push combiner
	std::thread f_thread_Push_Ext(&Schedular::PushFrameCombiner, this);

#ifdef SCH_THR_DETACH
	f_thread_Push_Ext.detach();
#endif

	return 1;
}

void Schedular::DataFrame_Angel(void)
{
	std::thread f_thread_Ext(&Schedular::DataFrame_AngelExt, this);

#ifdef SCH_THR_DETACH
	f_thread_Ext.detach();
#endif

	m_vec_Packet.clear();

	m_Scan = true;
	while(m_Scan == true)
		{
		char recvbuf[DEFAULT_BUFLEN];

		ag_PrepareChar(recvbuf, DEFAULT_BUFLEN);

		int iResult = recv(m_ClientSS->m_Socket, recvbuf, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			m_vec_Packet.push_back(std::make_shared<std::string>(recvbuf));
			}
		else
			{
			m_Scan = false;
			}
		}
}

void Schedular::DataFrame_AngelExt(void)
{
	while(m_Scan == true)
		{
		if(m_vec_Packet.size() > 0)
			{
			Sleep(18);

			std::shared_ptr<std::string> f_current_Packet = m_vec_Packet[0];

			int iResult = f_current_Packet->length();

			if(f_current_Packet->at(0) == 'D')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(f_current_Packet->at(f_Count));
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_Entries.push_back(f_Entry);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str()));

				m_EntrantMtx.unlock();

				g_EntryReset = true;
				}
			else if(f_current_Packet->at(0) == 'M')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(f_current_Packet->at(f_Count));
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();
				std::vector<std::string> f_vec_Element;

				f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy));
				f_Entry->push_back(f_vec_Element);

				m_Entries.push_back(f_Entry);

				m_EntrantMtx.lock();

				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str()));

				m_EntrantMtx.unlock();

				g_EntryReset = true;
				}
			else if(f_current_Packet->at(0) == 'A')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(f_current_Packet->at(f_Count));
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				g_QAccountID = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

				//////////////////////////////////////////////////////
				//WARNINGWARNINGWARNINGWARNINGWARNINGWARNINGWARNING
				//ADD THIS
				//g_qa_Radar = atoi(agsc_ReadElement_Sock((char*)f_String.c_str();
				//g_qa_ClientTime = 0;
				//g_qa_FrameRateLimiter = 0;
				}
			else if(f_current_Packet->at(0) == 'K')
				{
				//...
				}
			else
				{
				//...
				}

			//message pump reorder packet array
			for(int f_Int = 0; f_Int < m_vec_Packet.size() - 1; f_Int++)
				{
				m_vec_Packet[f_Int] = m_vec_Packet[f_Int + 1];
				}

			m_vec_Packet.pop_back();

			m_EntrantMtx.lock();

			//conditional entry reorder
			if(m_Entries.size() > ECOIN_ENTRY_MAX)
				{
				for(int f_Jet = (ECOIN_ENTRY_MAX - (ECOIN_ENTRY_REFRESH_DEPTH * 2)); f_Jet < (ECOIN_ENTRY_MAX - 1); f_Jet++)
					{
					for(int f_Int = f_Jet; f_Int < m_Entries.size() - 1; f_Int++)
						{
						m_Entries[f_Int] = m_Entries[f_Int + 1];
						}

					for(int f_Int = f_Jet; f_Int < m_Entrant.size() - 1; f_Int++)
						{
						m_Entrant[f_Int] = m_Entrant[f_Int + 1];
						}
					}

				for(int f_Jet = 0; f_Jet < ECOIN_ENTRY_REFRESH_DEPTH; f_Jet++)
					{
					m_Entrant.pop_back();
					m_Entries.pop_back();
					}
				}

			m_EntrantMtx.unlock();
			}
		}
}

std::string agsc_ReadElement_Sock(char* f_Charpntr, int* f_Cy, int iResult)
{
	bool f_Scan = true;
	int f_Cn = *(f_Cy);
	char f_A[4];

	std::string f_Res;
	f_Res.clear();

	if((f_Cn + 4) >= iResult)
		{
		return "";
		}

	f_A[0] = f_Charpntr[f_Cn];
	f_A[1] = f_Charpntr[f_Cn + 1];
	f_A[2] = f_Charpntr[f_Cn + 2];
	f_A[3] = f_Charpntr[f_Cn + 3];
	f_Cn += 4;
	*(f_Cy) += 4;

	if (f_A[0] == ':' &&
		f_A[1] == ':' &&
		f_A[2] == ':' &&
		f_A[3] == ':')
		{
		return "";
		}
	else
		{
		if(f_A[0] != ':')
			{
			f_Res.push_back(f_A[0]);
			}
		}

	while(f_Scan)
		{
		if((f_Cn + 1) >= iResult)
			{
			return "";
			}

		f_A[0] = f_A[1];
		f_A[1] = f_A[2];
		f_A[2] = f_A[3];
		f_A[3] = f_Charpntr[f_Cn];
		f_Cn++;
		*(f_Cy) += 1;

		if (f_A[0] == ':' &&
			f_A[1] == ':' &&
			f_A[2] == ':' &&
			f_A[3] == ':')
			{
			f_Scan = false;
			}
		else
			{
			if(f_A[0] != ':')
				{
				f_Res.push_back(f_A[0]);
				}
			}
		}

	return f_Res;
}

std::string agsc_ReadElement_Sock(char* f_Charpntr, int* f_Cy)
{
	bool f_Scan = true;
	int f_Cn = *(f_Cy);
	char f_A[4];

	std::string f_Res;
	f_Res.clear();

	f_A[0] = f_Charpntr[f_Cn];
	f_A[1] = f_Charpntr[f_Cn + 1];
	f_A[2] = f_Charpntr[f_Cn + 2];
	f_A[3] = f_Charpntr[f_Cn + 3];
	f_Cn += 4;
	*(f_Cy) += 4;

	if (f_A[0] == ':' &&
		f_A[1] == ':' &&
		f_A[2] == ':' &&
		f_A[3] == ':')
		{
		return "";
		}
	else
		{
		if(f_A[0] != ':')
			{
			f_Res.push_back(f_A[0]);
			}
		}

	while(f_Scan == true)
		{
		f_A[0] = f_A[1];
		f_A[1] = f_A[2];
		f_A[2] = f_A[3];
		f_A[3] = f_Charpntr[f_Cn];
		f_Cn++;
		*(f_Cy) += 1;

		if (f_A[0] == ':' &&
			f_A[1] == ':' &&
			f_A[2] == ':' &&
			f_A[3] == ':')
			{
			f_Scan = false;
			}
		else
			{
			if(f_A[0] != ':')
				{
				f_Res.push_back(f_A[0]);
				}
			}
		}

	return f_Res;
}

std::string agsc_ReadElement_Sock_V15(char* f_Charpntr, int* f_Cy, int iResult, bool f_isLastof)
{
	bool f_Scan = true;
	int f_Cn = *(f_Cy);
	char f_A[4];

	std::string f_Res;
	f_Res.clear();

	//added beef to the read socket
	std::string f_ReturnString = "";

	for(int f_Jet = 0; f_Jet < 4; f_Jet++)
		{
		int f_S = f_Cn + f_Jet;

		if(f_S < iResult)
			{
			f_ReturnString.push_back(f_Charpntr[f_S]);
			}
		else
			{
			f_ReturnString.push_back('&');

			*(f_Cy) += f_Jet;

			return f_ReturnString;
			}
		}

	f_ReturnString.clear();

	f_A[0] = f_Charpntr[f_Cn];
	f_A[1] = f_Charpntr[f_Cn + 1];
	f_A[2] = f_Charpntr[f_Cn + 2];
	f_A[3] = f_Charpntr[f_Cn + 3];

	f_Cn += 4;
	*(f_Cy) += 4;

	if(f_A[0] == ':' &&
		f_A[1] == ':' &&
		f_A[2] == ':' &&
		f_A[3] == ':')
		{
		return std::string("");
		}
	else
		{
		if(f_A[0] != ':')
			{
			f_Res.push_back(f_A[0]);
			}
		}

	while(f_Scan == true)
		{
		f_A[0] = f_A[1];
		f_A[1] = f_A[2];
		f_A[2] = f_A[3];
		f_A[3] = f_Charpntr[f_Cn];

		f_Cn++;
		*(f_Cy) += 1;

		if( f_A[0] == ':' &&
			f_A[1] == ':' &&
			f_A[2] == ':' &&
			f_A[3] == ':')
			{
			if((f_Cn >= iResult) && (f_isLastof == false))
				{
				f_Res += "&&";

				return f_Res;
				}

			f_Scan = false;
			}
		else
			{
			if(f_A[0] != ':')
				{
				f_Res.push_back(f_A[0]);
				}

			if(f_Cn >= iResult)
				{
				if(f_A[1] != ':')
					{
					f_Res.push_back(f_A[1]);
					}

				if(f_A[2] != ':')
					{
					f_Res.push_back(f_A[2]);
					}

				if(f_A[3] != ':')
					{
					f_Res.push_back(f_A[3]);
					}

				if( f_A[0] == ':' ||
					f_A[1] == ':' ||
					f_A[2] == ':' ||
					f_A[3] == ':')
					{
					f_Res += "&&";

					return f_Res;
					}

				f_Res.push_back('&');

				return f_Res;
				}
			}
		}

	return f_Res;
}

bool Schedular::acSend_Query_PeerGraph(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Pecoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			char* f_suffix = new char[2048];
			sprintf(f_suffix, ":%i", f_EntCount);

			std::string f_Result = f_String + f_suffix;
			delete[] f_suffix;

			char* f_popsuffix = new char[2048];
			sprintf(f_popsuffix, ":%i", g_ShareID);

			f_Result += f_popsuffix;
			delete[] f_popsuffix;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				return false;
				}

			bool f_Scan12 = true;
			while(f_Scan12 == true)
				{
				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						f_Scan12 = false;
						}
					}
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			m_EntrantMtx.unlock();

			while(g_ConnectedECD == false)
				{
				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						int f_X = 1;
						}
					}
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_PeerGraphSelect(char* f_Char, int f_UI, bool f_End, int f_ShareID, int f_ShareOffset, int f_PEER, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	bool f_Fill = false;

	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Hecoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			char* f_suffix = new char[2048];
			sprintf(f_suffix, ":%i", f_EntCount);

			std::string f_Result = f_String + f_suffix;
			delete[] f_suffix;

			char* f_popsuffix = new char[2048];
			sprintf(f_popsuffix, ":%i", f_ShareID);

			f_Result += f_popsuffix;
			delete[] f_popsuffix;

			char* f_pop2suffix = new char[2048];
			sprintf(f_pop2suffix, ":%i", f_ShareOffset);

			f_Result += f_pop2suffix;
			delete[] f_pop2suffix;

			char* f_pop3suffix = new char[2048];
			sprintf(f_pop3suffix, ":%i", f_PEER);

			f_Result += f_pop3suffix;
			delete[] f_pop3suffix;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				return false;
				}

			bool f_Scan13 = true;
			while(f_Scan13 == true)
				{
				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						f_Scan13 = false;
						}
					}
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			m_EntrantMtx.unlock();

			while(g_ConnectedECD == false)
				{
				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						int f_X = 1;
						}
					}
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_GlobalStorageWealth(char* f_Char, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	bool f_Fill = false;

	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "W:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			m_EntrantMtx.unlock();

			char* f_suffix = new char[2048];
			sprintf(f_suffix, ":%i", f_EntCount);

			std::string f_Result = f_String + f_suffix;
			delete[] f_suffix;

			//Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				return false;
				}

			bool f_Scan14 = true;
			while(f_Scan14 == true)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						f_Scan14 = false;
						}
					}

				m_EntrantMtx.unlock();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			int f_EntCount = 0;

			if(m_Entries.size() >= 500)
				{
				f_EntCount = m_Entries.size() - 1;
				}
			else
				{
				f_EntCount = m_Entries.size();
				}

			m_EntrantMtx.unlock();

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	bool f_Fill = false;

	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Secoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			m_EntrantMtx.unlock();

			char* f_suffix = new char[2048];
			sprintf(f_suffix, ":%i", f_EntCount);

			std::string f_Result = f_String + f_suffix;
			delete[] f_suffix;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				return false;
				}

			bool f_Scan15 = true;
			while(f_Scan15 == true)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						f_Scan15 = false;
						}
					}

				m_EntrantMtx.unlock();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			int f_EntCount = 0;

			if(m_Entries.size() >= 500)
				{
				f_EntCount = m_Entries.size() - 1;
				}
			else
				{
				f_EntCount = m_Entries.size();
				}

			m_EntrantMtx.unlock();

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_KeepAlive(char* f_Char, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	bool f_Fill = false;

	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Kecoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			m_EntrantMtx.unlock();

			char* f_suffix = new char[2048];
			sprintf(f_suffix, ":%i", f_EntCount);

			std::string f_Result = f_String + f_suffix;
			delete[] f_suffix;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				return false;
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			m_EntrantMtx.unlock();

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_Angel(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	bool f_Fill = false;

	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "S";
			f_String += f_Char;

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			m_EntrantMtx.unlock();

			char* f_suffix = new char[2048];
			sprintf(f_suffix, ":%i", f_EntCount);

			std::string f_Result = f_String + f_suffix;
			delete[] f_suffix;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				return false;
				}

			bool f_Scan16 = true;
			while(f_Scan16 == true)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						f_Scan16 = false;
						}
					}

				m_EntrantMtx.unlock();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			int f_EntCount = 0;

			if(m_Entries.size() >= 500)
				{
				f_EntCount = m_Entries.size() - 1;
				}
			else
				{
				f_EntCount = m_Entries.size();
				}

			m_EntrantMtx.unlock();

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_KeepAlive_Angel(char* f_Char, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	bool f_Fill = false;

	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "K";
			f_String += f_Char;

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			m_EntrantMtx.unlock();

			char* f_suffix = new char[2048];
			sprintf(f_suffix, ":%i", f_EntCount);

			std::string f_Result = f_String + f_suffix;
			delete[] f_suffix;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				return false;
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			int f_EntCount = 0;

			if(m_Entries.size() >= 500)
				{
				f_EntCount = m_Entries.size() - 1;
				}
			else
				{
				f_EntCount = m_Entries.size();
				}

			m_EntrantMtx.unlock();

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_CMD(char* f_Char, int f_UI, bool f_End, bool f_Update, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	bool f_Fill = false;

	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Mecoincd1:";

			if(f_Update == true)
				{
				f_String = "Uecoincd1:";
				}

			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			m_EntrantMtx.unlock();

			char* f_suffix = new char[2048];
			sprintf(f_suffix, ":%i", f_EntCount);

			std::string f_Result = f_String + f_suffix;
			delete[] f_suffix;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				return false;
				}

			if(f_Update == false)
				{
				bool f_Scan17 = true;
				while(f_Scan17 == true)
					{
					m_EntrantMtx.lock();

					if(m_Entrant.size() > 0)
						{
						if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
							{
							f_Scan17 = false;
							}
						}

					m_EntrantMtx.unlock();
					}
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			int f_EntCount = 0;

			if(m_Entries.size() >= 500)
				{
				f_EntCount = m_Entries.size() - 1;
				}
			else
				{
				f_EntCount = m_Entries.size();
				}

			m_EntrantMtx.unlock();

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_CMD_Angel(char* f_Char, int f_UI, bool f_End, bool f_Update, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	bool f_Fill = false;

	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "M";

			if(f_Update == true)
				{
				f_String = "U";
				}

			f_String += f_Char;

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			if(f_EntCount > ECOIN_ENTRY_MAX)
				{
				f_EntCount = f_EntCount - ECOIN_ENTRY_REFRESH_DEPTH;
				}

			m_EntrantMtx.unlock();

			char* f_suffix = new char[2048];
			sprintf(f_suffix, ":%i", f_EntCount);

			std::string f_Result = f_String + f_suffix;
			delete[] f_suffix;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				return false;
				}

			if(f_Update == false)
				{
				bool f_Scan18 = true;
				while(f_Scan18 == true)
					{
					m_EntrantMtx.lock();

					if(m_Entrant.size() > 0)
						{
						if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
							{
							f_Scan18 = false;
							}
						}

					m_EntrantMtx.unlock();
					}
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntrantMtx.lock();

			int f_EntCount = 0;

			if(m_Entries.size() >= 500)
				{
				f_EntCount = m_Entries.size() - 1;
				}
			else
				{
				f_EntCount = m_Entries.size();
				}

			m_EntrantMtx.unlock();

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::getWork(uint f_Pattern)
{
	return true;
}

void Schedular::addContractESL(std::string f_Script)
{
	std::string f_ref_CurrentPath = "Schedular::addContractESL";
	ag_StatusLive(f_ref_CurrentPath, "f_Contract");
	std::shared_ptr<Contract> f_Contract = std::make_shared_reflect<Contract>(f_Script);

	f_Contract->m_Active = true;

	m_vec_Contract.push_back(f_Contract);
}

std::shared_ptr<Contract> Schedular::getContractESL(std::string f_Script)
{
	std::string f_ref_CurrentPath = "Schedular::getContractESL";
	ag_StatusLive(f_ref_CurrentPath, "f_Contract");
	std::shared_ptr<Contract> f_Contract = std::make_shared_reflect<Contract>(f_Script);

	f_Contract->m_Active = true;

	m_vec_Contract.push_back(f_Contract);

	return f_Contract;
}

void Schedular::addnonceContractESL(std::string f_Script)
{
	std::string f_ref_CurrentPath = "Schedular::addnonceContractESL";
	ag_StatusLive(f_ref_CurrentPath, "f_Contract");
	std::shared_ptr<Contract> f_Contract = std::make_shared_reflect<Contract>(f_Script);

	f_Contract->m_Active = true;

	m_vec_nonceContract.push_back(f_Contract);
}

void Schedular::refreshContractESL(std::string f_Script)
{
	std::string f_ref_CurrentPath = "Schedular::refreshContractESL";
	ag_StatusLive(f_ref_CurrentPath, "f_Contract");
	std::shared_ptr<Contract> f_Contract = std::make_shared_reflect<Contract>(f_Script);

	f_Contract->m_Active = true;

	m_vec_Contract[0] = f_Contract;
}

int Schedular::ac_GetEntry(int f_EntryIdx)
{
	if(f_EntryIdx >= m_Entries.size())
		{
		f_EntryIdx = m_Entries.size() - 1;
		}

	if(f_EntryIdx < 0)
		{
		throw;

		return 0;
		}
	else
		{
		return f_EntryIdx;
		}
}

};