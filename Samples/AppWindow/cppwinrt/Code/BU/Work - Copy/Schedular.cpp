/*

Schedular - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Schedular.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")

using namespace ecoin;

namespace ecoin
{

Schedular* g_Schedular[3];

bool g_EntryReset = false;
int iSendResult = 0;
int g_QAccountID = 0;
int g_ShareID = 0;
int g_NetMode = 0;

Schedular::Schedular(void)
{
	m_F = 0;
	m_G = 0;

	m_ClientSS = new SocketSet();

	m_ClientSS->m_IP = "192.64.112.79";
	m_ClientSS->m_IP_Gui = "192.64.112.79";
	m_ClientSS->m_IP_Angel = "192.64.112.79";

	m_ClientSS->m_PORT = DEFAULT_PORT;
	m_ClientSS->m_PORT_Gui = DEFAULT_PORT_GUI;
	m_ClientSS->m_PORT_Angel = DEFAULT_PORT_ANGEL;
}

Schedular::~Schedular()
{
	// No longer need server socket
	closesocket(m_ServerListenSocket);
};

int Schedular::acNet_Client(void)
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
			continue;
			}

		break;
		}

	freeaddrinfo(result);

	if(m_ClientSS->m_Socket == INVALID_SOCKET)
		{
		WSACleanup();
		}

	return 1;
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
			continue;
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
		}

	// Run task on a dedicated high priority background thread.

	std::thread f_thread_Data_Gui(&Schedular::DataFrame_Gui, this);

	f_thread_Data_Gui.detach();

	return 1;
}

void Schedular::DataFrame_Gui(void)
{
	bool f_Scan = true;

	while(f_Scan)
		{
		int iResult = recv(m_ClientSS->m_Socket, m_ClientSS->m_recvbuf, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			printf("ecoincc-%s", m_ClientSS->m_recvbuf);

			if(m_ClientSS->m_recvbuf[0] == 'D')
				{
				  ////////////
				 // Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(m_ClientSS->m_recvbuf[f_Count] == ':')
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
							f_Prefix.push_back(m_ClientSS->m_recvbuf[f_Count]);
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::vector<std::vector<std::string>> f_Entry;

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

						f_Entry.push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry.push_back(f_vec_Element);
					}

				m_Entries.push_back(f_Entry);
				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				}
			else if(m_ClientSS->m_recvbuf[0] == 'G')
				{
				  ////////////
				 // Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(m_ClientSS->m_recvbuf[f_Count] == ':')
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
							f_Prefix.push_back(m_ClientSS->m_recvbuf[f_Count]);
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::vector<std::vector<std::string>> f_ModifEntry;

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry.push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry.push_back(f_vec_ElementA);
				f_ModifEntry.push_back(f_vec_ElementB);

				m_Entries.push_back(f_ModifEntry);
				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				}
			else if(m_ClientSS->m_recvbuf[0] == 'R')
				{
				  ////////////
				 // Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(m_ClientSS->m_recvbuf[f_Count] == ':')
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
							f_Prefix.push_back(m_ClientSS->m_recvbuf[f_Count]);
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::vector<std::vector<std::string>> f_ModifEntry;

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry.push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;
				std::vector<std::string> f_vec_ElementC;
				std::vector<std::string> f_vec_ElementD;
				std::vector<std::string> f_vec_ElementE;
				std::vector<std::string> f_vec_ElementF;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementC.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementD.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementE.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementF.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry.push_back(f_vec_ElementA);
				f_ModifEntry.push_back(f_vec_ElementB);
				f_ModifEntry.push_back(f_vec_ElementC);
				f_ModifEntry.push_back(f_vec_ElementD);
				f_ModifEntry.push_back(f_vec_ElementE);
				f_ModifEntry.push_back(f_vec_ElementF);

				m_Entries.push_back(f_ModifEntry);
				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				}
			else if(m_ClientSS->m_recvbuf[0] == 'M')
				{
				  ////////////
				 // Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(m_ClientSS->m_recvbuf[f_Count] == ':')
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
							f_Prefix.push_back(m_ClientSS->m_recvbuf[f_Count]);
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				std::vector<std::vector<std::string>> f_Entry;
				std::vector<std::string> f_vec_Element;

				f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_Entry.push_back(f_vec_Element);

				m_Entries.push_back(f_Entry);
				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				}
			}
		else if(iResult == 0)
			{
			printf("Connection closing...\n");

			f_Scan = false;
			}
		else
			{
			printf("recv failed with error: %d recvbuffer = %s\n", WSAGetLastError(), m_ClientSS->m_recvbuf);

			f_Scan = false;
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
			continue;
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
		}

	// Run task on a dedicated high priority background thread.

	std::thread f_thread_Data_Angel(&Schedular::DataFrame_Angel, this);

	f_thread_Data_Angel.detach();

	return 1;
}

// Create a task that will be run on a background thread.
void Schedular::DataFrame_Angel(void)
{
	bool f_Scan = true;

	// Calculate the updated frame and render once per vertical blanking interval.
	while(f_Scan)
		{
		int iResult = recv(m_ClientSS->m_Socket, m_ClientSS->m_recvbuf, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			if(m_ClientSS->m_recvbuf[0] == 'D')
				{
				  ////////////
				 // Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

				std::vector<std::vector<std::string>> f_Entry;

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

						f_Entry.push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry.push_back(f_vec_Element);
					}

				g_Schedular[2]->m_Entries.push_back(f_Entry);
				g_Schedular[2]->m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str()));
				g_EntryReset = true;
				}
			else if(m_ClientSS->m_recvbuf[0] == 'M')
				{
					////////////
					// Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				std::vector<std::vector<std::string>> f_Entry;
				std::vector<std::string> f_vec_Element;

				f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy));
				f_Entry.push_back(f_vec_Element);

				g_Schedular[2]->m_Entries.push_back(f_Entry);
				g_Schedular[2]->m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str()));
				g_EntryReset = true;
				}
			else if(m_ClientSS->m_recvbuf[0] == 'A')
				{
				  ////////////
				 // Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
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
			}
		else if(iResult == 0)
			{
			printf("Connection closing...\n");
			f_Scan = false;
			closesocket(m_ClientSS->m_Socket);
			WSACleanup();
			}
		else
			{
			printf("recv failed with error: %d recvbuffer = %s\n", WSAGetLastError(), m_ClientSS->m_recvbuf);
			f_Scan = false;
			closesocket(m_ClientSS->m_Socket);
			WSACleanup();
			}
		}
}

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
		//printf("getaddrinfo failed with error: %d\n", iResult);
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
			continue;
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
		}
	else
		{
		g_NetMode = ECOIN_NET_DIVINER;
		}

	std::thread f_thread_Data(&Schedular::DataFrame, this);

	f_thread_Data.detach();

	return 1;
}

// Create a task that will be run on a background thread.
void Schedular::DataFrame(void)
{
	bool f_Scan = true;

	// Calculate the updated frame and render once per vertical blanking interval.
	while(f_Scan)
		{
		int iResult = recv(m_ClientSS->m_Socket, m_ClientSS->m_recvbuf, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			printf("ecoincd-%s", m_ClientSS->m_recvbuf);

			if(m_ClientSS->m_recvbuf[0] == 'D')
				{
				  ////////////
				 // Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(m_ClientSS->m_recvbuf[f_Count] == ':')
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
							f_Prefix.push_back(m_ClientSS->m_recvbuf[f_Count]);
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::vector<std::vector<std::string>> f_Entry;

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

						f_Entry.push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry.push_back(f_vec_Element);
					}

				m_Entries.push_back(f_Entry);

				std::string f_Suffix = agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult);

				m_Entrant.push_back(atoi(f_Suffix.c_str()));
				}
			else if(m_ClientSS->m_recvbuf[0] == 'G')
				{
				  ////////////
				 // Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(m_ClientSS->m_recvbuf[f_Count] == ':')
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
							f_Prefix.push_back(m_ClientSS->m_recvbuf[f_Count]);
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::vector<std::vector<std::string>> f_ModifEntry;

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry.push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry.push_back(f_vec_ElementA);
				f_ModifEntry.push_back(f_vec_ElementB);

				m_Entries.push_back(f_ModifEntry);
				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				}
			else if(m_ClientSS->m_recvbuf[0] == 'R')
				{
				  ////////////
				 // Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(m_ClientSS->m_recvbuf[f_Count] == ':')
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
							f_Prefix.push_back(m_ClientSS->m_recvbuf[f_Count]);
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::vector<std::vector<std::string>> f_ModifEntry;

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry.push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;
				std::vector<std::string> f_vec_ElementC;
				std::vector<std::string> f_vec_ElementD;
				std::vector<std::string> f_vec_ElementE;
				std::vector<std::string> f_vec_ElementF;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementC.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementD.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementE.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementF.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry.push_back(f_vec_ElementA);
				f_ModifEntry.push_back(f_vec_ElementB);
				f_ModifEntry.push_back(f_vec_ElementC);
				f_ModifEntry.push_back(f_vec_ElementD);
				f_ModifEntry.push_back(f_vec_ElementE);
				f_ModifEntry.push_back(f_vec_ElementF);

				m_Entries.push_back(f_ModifEntry);
				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				}
			else if(m_ClientSS->m_recvbuf[0] == 'M')
				{
				  ////////////
				 // Buffer
				//
				m_ClientSS->m_Buffer = m_ClientSS->m_recvbuf;

				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(m_ClientSS->m_recvbuf[f_Count] == ':')
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
							f_Prefix.push_back(m_ClientSS->m_recvbuf[f_Count]);
							f_Startof = f_Count;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(m_ClientSS->m_recvbuf[f_Count]);
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				std::vector<std::vector<std::string>> f_Entry;
				std::vector<std::string> f_vec_Element;

				f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_Entry.push_back(f_vec_Element);

				m_Entries.push_back(f_Entry);
				m_Entrant.push_back(atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				}
			}
		else if(iResult == 0)
			{
			printf("Connection closing...\n");
			
			f_Scan = false;
			}
		else
			{
			printf("recv failed with error: %d recvbuffer = %s\n", WSAGetLastError(), m_ClientSS->m_recvbuf);
			
			f_Scan = false;
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
		return "eof";
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
			return "eof";
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

	while(f_Scan)
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

bool Schedular::acSend_Query_PeerGraph(char* f_Char, int f_UI, bool f_End)
{
	std::string f_String = "Pecoincd1:";
	f_String += f_Char;
	f_String += ":ecoincd1";

	int f_EntCount = m_Entries.size();

	char* f_suffix = new char[2048];
	sprintf(f_suffix, ":%i", f_EntCount);

	std::string f_Result = f_String + f_suffix;

	char* f_popsuffix = new char[2048];
	sprintf(f_popsuffix, ":%i", g_ShareID);

	f_Result += f_popsuffix;

	// Send an initial buffer
	int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

	if(iResult == SOCKET_ERROR)
		{
		closesocket(m_ClientSS->m_Socket);
		WSACleanup();
		}

	int f_Count = 0;
	bool f_Scan = true;
	while(f_Scan)
		{
		printf("m_Entrant.size() %i\n", m_Entrant.size());
		if(m_Entrant.size() > 0)
			{
			if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
				{
				f_Scan = false;
				printf("f_EntCount %i m_Entrant[f_XY] %i\n", f_EntCount, m_Entrant[m_Entrant.size() - 1]);
				}
			else
				{
				printf("f_EntCount %i m_Entrant[f_XY] %i no match\n", f_EntCount, m_Entrant[m_Entrant.size() - 1]);
				}

			if(f_Scan && 0)
				{
				// Send an initial buffer
				iResult = send(m_ClientSS->m_Socket, (char*)f_String.c_str(), (int)strlen((char*)f_String.c_str()), 0);

				if(iResult == SOCKET_ERROR)
					{
					closesocket(m_ClientSS->m_Socket);
					WSACleanup();
					}
				}
			}
		}

	return true;
}

bool Schedular::acSend_Query_PeerGraphSelect(char* f_Char, int f_UI, bool f_End, int f_ShareID, int f_ShareOffset, int f_PEER)
{
	std::string f_String = "Hecoincd1:";
	f_String += f_Char;
	f_String += ":ecoincd1";

	int f_EntCount = m_Entries.size();

	char* f_suffix = new char[2048];
	sprintf(f_suffix, ":%i", f_EntCount);

	std::string f_Result = f_String + f_suffix;

	char* f_popsuffix = new char[2048];
	sprintf(f_popsuffix, ":%i", f_ShareID);

	f_Result += f_popsuffix;

	char* f_pop2suffix = new char[2048];
	sprintf(f_pop2suffix, ":%i", f_ShareOffset);

	f_Result += f_pop2suffix;

	char* f_pop3suffix = new char[2048];
	sprintf(f_pop3suffix, ":%i", f_PEER);

	f_Result += f_pop3suffix;

	// Send an initial buffer
	int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

	if(iResult == SOCKET_ERROR)
		{
		closesocket(m_ClientSS->m_Socket);
		WSACleanup();
		}

	int f_Count = 0;
	bool f_Scan = true;
	while(f_Scan)
		{
		printf("m_Entrant.size() %i\n", m_Entrant.size());
		if(m_Entrant.size() > 0)
			{
			if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
				{
				f_Scan = false;
				printf("f_EntCount %i m_Entrant[f_XY] %i\n", f_EntCount, m_Entrant[m_Entrant.size() - 1]);
				}
			else
				{
				printf("f_EntCount %i m_Entrant[f_XY] %i no match\n", f_EntCount, m_Entrant[m_Entrant.size() - 1]);
				}
			}
		}

	return true;
}

bool Schedular::acSend_Query_GlobalStorageWealth(char* f_Char)
{
	std::string f_String = "W:";
	f_String += f_Char;
	f_String += ":ecoincd1";

	int f_EntCount = m_Entries.size();

	char* f_suffix = new char[2048];
	sprintf(f_suffix, ":%i", f_EntCount);

	std::string f_Result = f_String + f_suffix;

	//Send an initial buffer
	int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

	if(iResult == SOCKET_ERROR)
		{
		closesocket(m_ClientSS->m_Socket);
		WSACleanup();
		}

	int f_Count = 0;
	bool f_Scan = true;
	while(f_Scan)
		{
		if(m_Entrant.size() > 0)
			{
			if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
				{
				f_Scan = false;
				}
			}
		}

#if 0
	f_EntCount = m_Entries.size();

	int f_TotalEcoinAreas = atoi(m_Entries[ac_GetEntry(m_Entries.size() - 1)][0][2].c_str());

	f_TotalEcoinAreas--;

	for (int f_Helly = 0; f_Helly < f_TotalEcoinAreas; f_Helly++)
		{
		f_Count = 0;
		f_Scan = true;

		while(f_Scan)
			{
			if(m_Entrant.size() > 0)
				{
				if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
					{
					f_Scan = false;
					}
				}
			}
		}
#endif

	return true;
}

bool Schedular::acSend_Query(char* f_Char, int f_UI, bool f_End)
{
	std::string f_String = "Secoincd1:";
	f_String += f_Char;
	f_String += ":ecoincd1";

	int f_EntCount = m_Entries.size();

	char* f_suffix = new char[2048];
	sprintf(f_suffix, ":%i", f_EntCount);

	std::string f_Result = f_String + f_suffix;

	// Send an initial buffer
	int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

	if(iResult == SOCKET_ERROR)
		{
		closesocket(m_ClientSS->m_Socket);
		WSACleanup();
		}

	int f_Count = 0;
	bool f_Scan = true;
	while(f_Scan)
		{
		printf("%i", m_Entrant.size());

		if(m_Entrant.size() > 0)
			{
			if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
				{
				f_Scan = false;
				}

			if(f_Scan && 0)
				{
				// Send an initial buffer
				iResult = send(m_ClientSS->m_Socket, (char*)f_String.c_str(), (int)strlen((char*)f_String.c_str()), 0);

				if(iResult == SOCKET_ERROR)
					{
					closesocket(m_ClientSS->m_Socket);
					WSACleanup();
					}
				}

			f_Count++;
			}
		}

	return true;
}

bool Schedular::acSend_Query_Angel(char* f_Char, int f_UI, bool f_End)
{
	std::string f_String = "S";
	f_String += f_Char;

	int f_EntCount = m_Entries.size();

	char* f_suffix = new char[2048];
	sprintf(f_suffix, ":%i", f_EntCount);

	std::string f_Result = f_String + f_suffix;

	// Send an initial buffer
	int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

	if(iResult == SOCKET_ERROR)
		{
		closesocket(m_ClientSS->m_Socket);
		WSACleanup();
		}

	int f_Count = 0;
	bool f_Scan = true;
	while(f_Scan)
		{
		printf("%i", m_Entrant.size());

		if(m_Entrant.size() > 0)
			{
			if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
				{
				f_Scan = false;
				}

			f_Count++;
			}
		}

	return true;
}

bool Schedular::acSend_Query_CMD(char* f_Char, int f_UI, bool f_End, bool f_Update)
{
	std::string f_String = "Mecoincd1:";

	if(f_Update)
		{
		f_String = "Uecoincd1:";
		}

	f_String += f_Char;
	f_String += ":ecoincd1";

	int f_EntCount = m_Entries.size();

	char* f_suffix = new char[2048];
	sprintf(f_suffix, ":%i", f_EntCount);

	std::string f_Result = f_String + f_suffix;

	// Send an initial buffer
	int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

	if(iResult == SOCKET_ERROR)
		{
		closesocket(m_ClientSS->m_Socket);
		WSACleanup();
		}

	if(!f_Update)
		{
		int f_Count = 0;
		bool f_Scan = true;
		while(f_Scan)
			{
			if(m_Entrant.size() > 0)
				{
				if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
					{
					f_Scan = false;
					}

				if(f_Scan && 0)
					{
					// Send an initial buffer
					iResult = send(m_ClientSS->m_Socket, (char*)f_String.c_str(), (int)strlen((char*)f_String.c_str()), 0);

					if(iResult == SOCKET_ERROR)
						{
						closesocket(m_ClientSS->m_Socket);
						WSACleanup();
						}
					}
				}
			}
		}

	return true;
}

bool Schedular::acSend_Query_CMD_Angel(char* f_Char, int f_UI, bool f_End, bool f_Update)
{
	std::string f_String = "M";

	if(f_Update)
		{
		f_String = "U";
		}

	f_String += f_Char;

	int f_EntCount = m_Entries.size();

	char* f_suffix = new char[2048];
	sprintf(f_suffix, ":%i", f_EntCount);

	std::string f_Result = f_String + f_suffix;

	// Send an initial buffer
	int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

	if(iResult == SOCKET_ERROR)
		{
		closesocket(m_ClientSS->m_Socket);
		WSACleanup();
		}

	if(!f_Update)
		{
		int f_Count = 0;
		bool f_Scan = true;
		while(f_Scan)
			{
			if(m_Entrant.size() > 0)
				{
				if(m_Entrant[m_Entrant.size() - 1] == f_EntCount)
					{
					f_Scan = false;
					printf("f_EntCount %i m_Entrant[f_XY] %i\n", f_EntCount, m_Entrant[m_Entrant.size() - 1]);
					}
				else
					{
					printf("f_EntCount %i m_Entrant[f_XY] %i no match\n", f_EntCount, m_Entrant[m_Entrant.size() - 1]);
					}

				if(f_Scan && 0)
					{
					// Send an initial buffer
					iResult = send(m_ClientSS->m_Socket, (char*)f_String.c_str(), (int)strlen((char*)f_String.c_str()), 0);

					if(iResult == SOCKET_ERROR)
						{
						closesocket(m_ClientSS->m_Socket);
						WSACleanup();
						}
					}
				}
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
	std::shared_ptr<Contract> f_Contract = std::make_shared<Contract>(f_Script);

	f_Contract->m_Active = true;

	m_vec_Contract.push_back(f_Contract);
}

std::shared_ptr<Contract> Schedular::getContractESL(std::string f_Script)
{
	std::shared_ptr<Contract> f_Contract = std::make_shared<Contract>(f_Script);

	f_Contract->m_Active = true;

	m_vec_Contract.push_back(f_Contract);

	return f_Contract;
}

void Schedular::addnonceContractESL(std::string f_Script)
{
	std::shared_ptr<Contract> f_Contract = std::make_shared<Contract>(f_Script);

	f_Contract->m_Active = true;

	m_vec_nonceContract.push_back(f_Contract);
}

void Schedular::refreshContractESL(std::string f_Script)
{
	std::shared_ptr<Contract> f_Contract = std::make_shared<Contract>(f_Script);

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
		return 0;
		}
	else
		{
		return f_EntryIdx;
		}
}

};