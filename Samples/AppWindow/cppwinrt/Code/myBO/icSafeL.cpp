/*

	icSafeL - SafeL Database Layer
	Copyright OSIREM (C) 2007
	bitolyl.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Code/Work/Schedular.h"
#include "Code/myBO/icSafeL.h"

using namespace ecoin;

std::shared_ptr<icSafeL> g_SafeL[3];

/*******************************
 * Implementation of icSafeL *
 *******************************/

/// Constructor.
icSafeL::icSafeL(int f_Layer_INDEX)
{
	m_LID = f_Layer_INDEX;

	std::string f_ref_CurrentPath = "icSafeL::icSafeL";

	//Management SG
#ifdef ECOIN_OSI_MEMORY_FUNC
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acSelectCommand", (ecom_base::ControllerMethod_void)&icSafeL::acSelectCommand);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acSelectCommand_PeerGraph", (ecom_base::ControllerMethod_void)&icSafeL::acSelectCommand_PeerGraph);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acSelectCommand_PeerGraphSelect", (ecom_base::ControllerMethod_void)&icSafeL::acSelectCommand_PeerGraphSelect);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acSelectCommand_GlobalStorageWealth", (ecom_base::ControllerMethod_void)&icSafeL::acSelectCommand_GlobalStorageWealth);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "Insert", (ecom_base::ControllerMethod_void)&icSafeL::Insert);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "Update", (ecom_base::ControllerMethod_void)&icSafeL::Update);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acCommand", (ecom_base::ControllerMethod_void)&icSafeL::acCommand);

#if 0
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "IssueSelectCommand", (ecom_base::ControllerMethod_void)&icSafeL::IssueSelectCommand);
#endif

	ac_Push(m_LID, f_ref_CurrentPath + g_ref_fun_Div + "m_LID");

#if 0
	ac_PushVar(static_cast<shared_ptr<icSafeL>>(this), f_ref_CurrentPath + g_ref_fun_Div + "this");
#endif
#endif
}

/// Destructor.
icSafeL::~icSafeL(void)
{
	//.
}

void icSafeL::Disconnect(void)
{
	//.
}

bool icSafeL::Initialize(void)
{
  return true;
}

bool icSafeL::Connect(const char* host, const char* username, const char* password, const char* database, unsigned short port)
{
	if(m_LID == 0)
		{
		g_Schedular[m_LID]->acNet_Client_Data();
		}
	else if(m_LID == 1)
		{
		g_Schedular[m_LID]->acNet_Client_Data_Gui();
		}
	else
		{
		g_Schedular[m_LID]->acNet_Client_Data_Angel();
		}
	
	printf("Connected to service-layer index %i\n", m_LID);

	return true;
}

long icSafeL::acCommand(const char *cmd, int f_UI, bool f_End, bool f_Update, bool f_Mtx_Ext_ON)
{
	fflush (stdout);

	if(m_LID < 2)
		{
		if(f_Update == true)
			{
			if(!g_Schedular[m_LID]->acSend_Query_CMD((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_CMD((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		else
			{
			if(!g_Schedular[m_LID]->acSend_Query_CMD((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_CMD((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		}
	else
		{
		if(f_Update)
			{
			if(!g_Schedular[m_LID]->acSend_Query_CMD_Angel((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_CMD_Angel((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		else
			{
			if(!g_Schedular[m_LID]->acSend_Query_CMD_Angel((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_CMD_Angel((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		}

	return true;
}

bool icSafeL::acSelectCommand(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	IssueSelectCommand (cmd, f_UI, f_End, f_Mtx_Ext_ON);

	return true;
}

bool icSafeL::acKeepAliveCommand(const char* cmd, bool f_Mtx_Ext_ON)
{
	IssueKeepAliveCommand(cmd, f_Mtx_Ext_ON);

	return true;
}

bool icSafeL::acSelectCommand_PeerGraph(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	if(!g_Schedular[m_LID]->acSend_Query_PeerGraph((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))
		{
		if(!g_Schedular[m_LID]->acSend_Query_PeerGraph((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))
			{
			return false;
			}
		}

	return true;
}

bool icSafeL::acSelectCommand_PeerGraphSelect(const char* cmd, int f_UI, bool f_End, int f_ShareID, int f_ShareOffset, int f_PEER, bool f_Mtx_Ext_ON)
{
	if(!g_Schedular[m_LID]->acSend_Query_PeerGraphSelect((char *)cmd, f_UI, f_End, f_ShareID, f_ShareOffset, f_PEER, f_Mtx_Ext_ON))
		{
		if(!g_Schedular[m_LID]->acSend_Query_PeerGraphSelect((char *)cmd, f_UI, f_End, f_ShareID, f_ShareOffset, f_PEER, f_Mtx_Ext_ON))
			{
			return false;
			}
		}

	return true;
}

bool icSafeL::acSelectCommand_GlobalStorageWealth(const char* cmd, bool f_Mtx_Ext_ON)
{
	if(!g_Schedular[m_LID]->acSend_Query_GlobalStorageWealth((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
		{
		//if command fails first time, try again - it should re-connect
		if(!g_Schedular[m_LID]->acSend_Query_GlobalStorageWealth((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			return false;
			}
		}

	return true;
}

bool icSafeL::IssueSelectCommand(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	if(m_LID < 2)
		{
		if(!g_Schedular[m_LID]->acSend_Query((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			//if command fails first time, try again - it should re-connect
			if(!g_Schedular[m_LID]->acSend_Query((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				return false;
				}
			}
		}
	else
		{
		if(!g_Schedular[m_LID]->acSend_Query_Angel((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			//if command fails first time, try again - it should re-connect
			if(!g_Schedular[m_LID]->acSend_Query_Angel((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				return false;
				}
			}
		}

	return true;
}

bool icSafeL::IssueKeepAliveCommand(const char* cmd, bool f_Mtx_Ext_ON)
{
	if(m_LID < 2)
		{
		if(!g_Schedular[m_LID]->acSend_KeepAlive((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			//if command fails first time, try again - it should re-connect
			if(!g_Schedular[m_LID]->acSend_KeepAlive((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				return false;
				}
			}
		}
	else
		{
		if(!g_Schedular[m_LID]->acSend_KeepAlive_Angel((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			//if command fails first time, try again - it should re-connect
			if(!g_Schedular[m_LID]->acSend_KeepAlive_Angel((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				return false;
				}
			}
		}

	return true;
}

unsigned int icSafeL::Insert(const char *table, const char **fields, const char **values, int fieldcount, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	char cmd[65535];
    int i;

	sprintf(cmd, "INSERT INTO %s (", table);

    for (i = 0; i < fieldcount; i++)
		{
        if(i > 0) strcat(cmd, ", ");
        strcat(cmd, fields[i]);
		}

	strcat(cmd, ") VALUES (");

    for(i = 0; i < fieldcount; i++)
		{
        if(i > 0) strcat(cmd, ",");
        if(values[i] != NULL)
			{
			strcat(cmd, "'");
            strcat(cmd, values[i]);
            strcat(cmd, "'");
			}
        else
			{
            strcat (cmd, "NULL");
			}
		}

    strcat (cmd, ")");

	//Do the SQL
    if(acCommand(cmd, f_UI, f_End, false, f_Mtx_Ext_ON) == -1)
        return 0;

    return atoi(g_Schedular[m_LID]->m_Entries[g_Schedular[m_LID]->ac_GetEntry(g_Schedular[m_LID]->m_Entries.size() - 1)]->at(0)[0].c_str());
}

unsigned int icSafeL::InsertM(const char *table, const char **fields, std::shared_ptr<std::vector<std::string>> f_values, int fieldcount, int cubecount, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	char cmd[155350];
    int i;

	sprintf(cmd, "INSERT INTO %s (", table);

    for(i = 0; i < fieldcount; i++)
		{
        if(i > 0) strcat(cmd, ", ");

        strcat(cmd, fields[i]);
		}

	strcat(cmd, ") VALUES (");

	int f_cs = 0;

    for(i = 0; i < fieldcount * cubecount; i++)
		{
		if((i > 0) && (f_cs > 0))
			{
			strcat(cmd, ",");
			}

        if(i < f_values->size())
			{
			strcat(cmd, "'");
            strcat(cmd, f_values->at(i).c_str());
            strcat(cmd, "'");
			}
        else
			{
            strcat(cmd, "NULL");
			}

		if(f_cs >= (fieldcount - 1))
			{
			f_cs = 0;

			if(i < ((fieldcount * cubecount) - 1))
				{
				strcat(cmd, "),(");
				}
			else
				{
				strcat(cmd, ");");
				}
			}
		else
			{
			f_cs++;
			}
		}

	//Do the SQL
	if(acCommand(cmd, f_UI, f_End, false, f_Mtx_Ext_ON) == -1)
		{
		return 0;
		}

	return 1;

    return atoi(g_Schedular[m_LID]->m_Entries[g_Schedular[m_LID]->ac_GetEntry(g_Schedular[m_LID]->m_Entries.size() - 1)]->at(0)[0].c_str());
}

bool icSafeL::Update(const char *table, const char **fields, const char **values, int fieldcount, const char *whereclause, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	char cmd[1000];
	int i;

	sprintf(cmd, "UPDATE %s SET ", table);

	for(i = 0; i < fieldcount; i++)
		{
		if (i > 0) strcat (cmd, ",");
		strcat (cmd, fields[i]);
		if(values[i] != "")
			{
			strcat(cmd, "='");
			strcat(cmd, values[i]); 
			strcat(cmd, "'");
			}
		else
			{
			strcat(cmd, "=NULL");
			}
		}

	strcat(cmd, " WHERE ");
	strcat(cmd, whereclause);

	if(acCommand(cmd, f_UI, f_End, true, f_Mtx_Ext_ON) == -1)
		{
		return false;
		}
	return true;
}

bool icSafeL::UpdateQuery(const char *f_querystring)
{
	return acCommand(f_querystring, 0, false, true, false);
}

void icSafeL::EscapeString(std::string& string, const char * data, unsigned long datalength)
{
  char* temp = (char*)malloc((datalength * 2) + 1);
  long templen = 0;// safel_real_escape_string(connection, temp, data, datalength);

#if 0
  string.empty();
#endif

  string.append(temp, templen);
  free(temp);
}

bool icSafeL_exec_char_int_bool_bool(icSafeL& f_icSafeL, icSafeLFn_char_int_bool_bool p, const char* f_Char1, int f_Int1, bool f_Bool1, bool f_Bool2)
{
	std::invoke(p, f_icSafeL, f_Char1, f_Int1, f_Bool1, f_Bool2);
}

bool icSafeL_exec_char_int_bool_bool(icSafeL& f_icSafeL, icSafeLFn_char_int_bool_int_int_int_bool p, const char* f_Char1, int f_Int1, bool f_Bool1, int f_Int2, int f_Int3, int f_Int4, bool f_Bool2)  // Use a typedef for pointer-to-member types
{
	std::invoke(p, f_icSafeL, f_Char1, f_Int1, f_Bool1, f_Int2, f_Int3, f_Int4, f_Bool2);
}

bool icSafeL_exec_char_bool(icSafeL& f_icSafeL, icSafeLFn_char_bool p, const char* f_Char1, bool f_Bool1)
{
	std::invoke(p, f_icSafeL, f_Char1, f_Bool1);
}

unsigned int icSafeL_exec_Insert(icSafeL& f_icSafeL, icSafeLFn_Insert_Char p, const char* f_Char1, const char** f_Char2, const char** f_Char3, int f_Int1, int f_Int2, bool f_Bool1, bool f_Bool2)
{
	std::invoke(p, f_icSafeL, f_Char1, f_Char2, f_Char3, f_Int1, f_Int2, f_Bool1, f_Bool2);
}

bool icSafeL_exec_Update(icSafeL& f_icSafeL, icSafeLFn_Update_Char p, const char* f_Char1, const char** f_Char2, const char** f_Char3, int f_Int1, const char* f_Char4, int f_Int2, bool f_Bool1, bool f_Bool2)
{
	std::invoke(p, f_icSafeL, f_Char1, f_Char2, f_Char3, f_Int1, f_Char4, f_Int2, f_Bool1, f_Bool2);
}