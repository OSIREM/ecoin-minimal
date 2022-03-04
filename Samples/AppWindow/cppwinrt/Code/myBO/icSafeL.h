/*

	icSafeL - SafeL Database Layer
	Copyright OSIREM (C) 2007
	bitolyl.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef icSafeL_h
#ifndef icMySQL_h
#define icSafeL_h
#define icMySQL_h

#include <string>
#include <vector>
#include <map>

#include <windows.h>
#include <winsock2.h>

#define SAFEL_RES int
#define SAFEL int
#define SAFEL_FIELD int

enum ACK_TYPE
{
	ACK_TYPE_SHARE,
	ACK_TYPE_BOND_ELEMENT,
	ACK_TYPE_VOTE_PLEDGE,
	ACK_TYPE_BLOCK,
	ACK_TYPE_REF,
	ACK_TYPE_TOTAL
};

class Ackent : public ecom_base
{
public:
	Ackent()
		{
		std::string f_ref_CurrentPath = "Ackent::Ackent";

		acClear();

		m_Type = 0;
		m_ShareID = 1;
		m_State = 0;
		m_Origin = 0;

#ifdef ECOIN_OSI_MEMORY
		ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
		ac_Push(m_ShareID, f_ref_CurrentPath + g_ref_Div + "m_ShareID");
		ac_Push(m_PeerID, f_ref_CurrentPath + g_ref_Div + "m_PeerID");
		ac_Push(m_ECN, f_ref_CurrentPath + g_ref_Div + "m_ECN");
		ac_Push(m_AppID, f_ref_CurrentPath + g_ref_Div + "m_AppID");
		ac_Push(m_BlockID, f_ref_CurrentPath + g_ref_Div + "m_BlockID");
		ac_Push(m_Score, f_ref_CurrentPath + g_ref_Div + "m_Score");
		ac_Push(m_Category, f_ref_CurrentPath + g_ref_Div + "m_Category");
		ac_Push(m_Owner, f_ref_CurrentPath + g_ref_Div + "m_Owner");
		ac_Push(m_Reward, f_ref_CurrentPath + g_ref_Div + "m_Reward");
		ac_Push(m_RewardID, f_ref_CurrentPath + g_ref_Div + "m_RewardID");
		ac_Push(m_Pledge, f_ref_CurrentPath + g_ref_Div + "m_Pledge");
		ac_Push(m_Fee, f_ref_CurrentPath + g_ref_Div + "m_Fee");
		ac_Push(m_State, f_ref_CurrentPath + g_ref_Div + "m_State");
		ac_Push(m_Origin, f_ref_CurrentPath + g_ref_Div + "m_Origin");
#endif
		};

	Ackent(int f_Type)
		{
		std::string f_ref_CurrentPath = "Ackent::Ackent";

		acClear();

		m_Type = f_Type;
		m_ShareID = 1;
		m_State = 0;
		m_Origin = 0;

#ifdef ECOIN_OSI_MEMORY
		ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
		ac_Push(m_ShareID, f_ref_CurrentPath + g_ref_Div + "m_ShareID");
		ac_Push(m_PeerID, f_ref_CurrentPath + g_ref_Div + "m_PeerID");
		ac_Push(m_ECN, f_ref_CurrentPath + g_ref_Div + "m_ECN");
		ac_Push(m_AppID, f_ref_CurrentPath + g_ref_Div + "m_AppID");
		ac_Push(m_BlockID, f_ref_CurrentPath + g_ref_Div + "m_BlockID");
		ac_Push(m_Score, f_ref_CurrentPath + g_ref_Div + "m_Score");
		ac_Push(m_Category, f_ref_CurrentPath + g_ref_Div + "m_Category");
		ac_Push(m_Owner, f_ref_CurrentPath + g_ref_Div + "m_Owner");
		ac_Push(m_Reward, f_ref_CurrentPath + g_ref_Div + "m_Reward");
		ac_Push(m_RewardID, f_ref_CurrentPath + g_ref_Div + "m_RewardID");
		ac_Push(m_Pledge, f_ref_CurrentPath + g_ref_Div + "m_Pledge");
		ac_Push(m_Fee, f_ref_CurrentPath + g_ref_Div + "m_Fee");
		ac_Push(m_State, f_ref_CurrentPath + g_ref_Div + "m_State");
		ac_Push(m_Origin, f_ref_CurrentPath + g_ref_Div + "m_Origin");
#endif
		};

	Ackent(int f_Type, int f_ShareID, int f_Peer)
		{
		std::string f_ref_CurrentPath = "Ackent::Ackent";

		acClear();

		m_Type = f_Type;
		m_ShareID = f_ShareID;
		m_PeerID = f_Peer;
		m_State = 0;
		m_Origin = 0;

#ifdef ECOIN_OSI_MEMORY
		ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
		ac_Push(m_ShareID, f_ref_CurrentPath + g_ref_Div + "m_ShareID");
		ac_Push(m_PeerID, f_ref_CurrentPath + g_ref_Div + "m_PeerID");
		ac_Push(m_ECN, f_ref_CurrentPath + g_ref_Div + "m_ECN");
		ac_Push(m_AppID, f_ref_CurrentPath + g_ref_Div + "m_AppID");
		ac_Push(m_BlockID, f_ref_CurrentPath + g_ref_Div + "m_BlockID");
		ac_Push(m_Score, f_ref_CurrentPath + g_ref_Div + "m_Score");
		ac_Push(m_Category, f_ref_CurrentPath + g_ref_Div + "m_Category");
		ac_Push(m_Owner, f_ref_CurrentPath + g_ref_Div + "m_Owner");
		ac_Push(m_Reward, f_ref_CurrentPath + g_ref_Div + "m_Reward");
		ac_Push(m_RewardID, f_ref_CurrentPath + g_ref_Div + "m_RewardID");
		ac_Push(m_Pledge, f_ref_CurrentPath + g_ref_Div + "m_Pledge");
		ac_Push(m_Fee, f_ref_CurrentPath + g_ref_Div + "m_Fee");
		ac_Push(m_State, f_ref_CurrentPath + g_ref_Div + "m_State");
		ac_Push(m_Origin, f_ref_CurrentPath + g_ref_Div + "m_Origin");
#endif
		};

	~Ackent()
		{
		std::string f_ref_CurrentPath = "Ackent::Ackent";

		acClear();

		m_Type = 0;
		m_ShareID = 0;
		m_State = 0;
		m_Origin = 0;

#ifdef ECOIN_OSI_MEMORY
		ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
		ac_Push(m_ShareID, f_ref_CurrentPath + g_ref_Div + "m_ShareID");
		ac_Push(m_PeerID, f_ref_CurrentPath + g_ref_Div + "m_PeerID");
		ac_Push(m_ECN, f_ref_CurrentPath + g_ref_Div + "m_ECN");
		ac_Push(m_AppID, f_ref_CurrentPath + g_ref_Div + "m_AppID");
		ac_Push(m_BlockID, f_ref_CurrentPath + g_ref_Div + "m_BlockID");
		ac_Push(m_Score, f_ref_CurrentPath + g_ref_Div + "m_Score");
		ac_Push(m_Category, f_ref_CurrentPath + g_ref_Div + "m_Category");
		ac_Push(m_Owner, f_ref_CurrentPath + g_ref_Div + "m_Owner");
		ac_Push(m_Reward, f_ref_CurrentPath + g_ref_Div + "m_Reward");
		ac_Push(m_RewardID, f_ref_CurrentPath + g_ref_Div + "m_RewardID");
		ac_Push(m_Pledge, f_ref_CurrentPath + g_ref_Div + "m_Pledge");
		ac_Push(m_Fee, f_ref_CurrentPath + g_ref_Div + "m_Fee");
		ac_Push(m_State, f_ref_CurrentPath + g_ref_Div + "m_State");
		ac_Push(m_Origin, f_ref_CurrentPath + g_ref_Div + "m_Origin");
#endif
		};

	void acClear(void)
		{
		m_Type = 0;
		m_ShareID = 0;
		m_PeerID = 0;
		m_ECN = 0.0f;

		m_AppID = 0;
		m_BlockID = 0;
		m_Score = 0;
		m_Category = 0;
		m_Owner.clear();
		m_Reward = 50.0f;
		m_RewardID = -1;
		m_Pledge = 0.0f;
		m_Fee = 0.0f;

		m_State = 0;
		m_Origin = 0;
		}

	int m_Type;
	int m_ShareID;
	int m_PeerID;
	float m_ECN;

	int m_AppID;
	int m_BlockID;
	int m_Score;
	int m_Category;
	std::string m_Owner;
	std::string m_PathOwner;
	float m_Reward;
	float m_RewardID;
	float m_Pledge;
	float m_Fee;

	int m_State;
	int m_Origin;
};

class icSafeL : public ecom_base
{
public:
	icSafeL(int f_Layer_INDEX);
	~icSafeL ();

	bool Initialize(void);
	bool Connect(const char* host, const char* username, const char* password, const char* database, unsigned short port);
	void Disconnect(void);

	void EscapeString(std::string& string, const char* data, unsigned long datalength);

	bool acSelectCommand(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON = false);
	bool acSelectCommand_PeerGraph(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON = false);
	bool acSelectCommand_PeerGraphSelect(const char* cmd, int f_UI, bool f_End, int f_ShareID, int f_ShareOffset, int f_PEER, bool f_Mtx_Ext_ON = false);
	bool acSelectCommand_GlobalStorageWealth(const char* cmd, bool f_Mtx_Ext_ON = false);

	unsigned int Insert(const char *table, const char **fields, const char **values, int fieldcount, int f_UI, bool f_End, bool f_Mtx_Ext_ON = false);
	unsigned int InsertM(const char* table, const char** fields, std::shared_ptr<std::vector<std::string>> f_values, int fieldcount, int cubecount, int f_UI, bool f_End, bool f_Mtx_Ext_ON = false);

	bool Update(const char* table, const char** fields, const char** values, int fieldcount, const char* whereclause, int f_UI, bool f_End, bool f_Mtx_Ext_ON = false);
	bool UpdateQuery(const char* f_querystring);

	long acCommand(const char* cmd, int f_UI, bool f_End, bool f_Update = false, bool f_Mtx_Ext_ON = false);

	bool acKeepAliveCommand(const char* cmd, bool f_Mtx_Ext_ON = false);

private:
    /// Internal version of acSelectCommand.
    bool IssueSelectCommand(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON = false);
	bool IssueKeepAliveCommand(const char* cmd, bool f_Mtx_Ext_ON = false);

	int m_LID;
};

extern std::shared_ptr<icSafeL> g_SafeL[3];

typedef bool (icSafeL::* icSafeLFn_char_int_bool_bool)(const char*, int, bool, bool) const;
typedef bool (icSafeL::* icSafeLFn_char_int_bool_int_int_int_bool)(const char*, int, bool, int, int, int, bool) const;
typedef bool (icSafeL::* icSafeLFn_char_bool)(const char*, bool) const;

typedef unsigned int (icSafeL::* icSafeLFn_Insert_Char)(const char*, const char**, const char**, int, int, bool, bool) const;
typedef bool (icSafeL::* icSafeLFn_Update_Char)(const char*, const char**, const char**, int, const char*, int, bool, bool) const;

bool icSafeL_exec_char_int_bool_bool(icSafeL& f_icSafeL, icSafeLFn_char_int_bool_bool p, const char* f_Char1, int f_Int1, bool f_Bool1, bool f_Bool2);
bool icSafeL_exec_char_int_bool_bool(icSafeL& f_icSafeL, icSafeLFn_char_int_bool_int_int_int_bool p, const char* f_Char1, int f_Int1, bool f_Bool1, int f_Int2, int f_Int3, int f_Int4, bool f_Bool2);
bool icSafeL_exec_char_bool(icSafeL& f_icSafeL, icSafeLFn_char_bool p, const char* f_Char1, bool f_Bool1);

unsigned int icSafeL_exec_Insert(icSafeL& f_icSafeL, icSafeLFn_Insert_Char p, const char* f_Char1, const char** f_Char2, const char** f_Char3, int f_Int1, int f_Int2, bool f_Bool1, bool f_Bool2);
bool icSafeL_exec_Update(icSafeL& f_icSafeL, icSafeLFn_Update_Char p, const char* f_Char1, const char** f_Char2, const char** f_Char3, int f_Int1, const char* f_Char4, int f_Int2, bool f_Bool1, bool f_Bool2);

#endif
#endif