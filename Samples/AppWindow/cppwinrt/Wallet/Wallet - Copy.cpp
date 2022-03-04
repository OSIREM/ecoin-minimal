/*

Wallet.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>

#include "pplawait.h"
#include "Wallet.h"
#include "Code\Hash\base58.h"

using namespace winrt;

namespace ecoin
{

std::shared_ptr<Wallet> g_Wallet;

bool g_WalletOpen = false;
int g_EmployeeID = -1;
double g_WALLETBANK;
double g_StoreWALLETBANK;
double g_EVALUE;
double g_ECOINPERSECOND;
int g_HESHSAVEID;
float g_TX = 0.0f;
float g_BossLVLMin = 0.0f;

Wallet::Wallet()
{
	std::string f_ref_CurrentPath = "Wallet::Wallet";

	m_Start = false;
	m_OK = false;

	m_Count = 0;
	m_CountYNG = true;
	m_HeshCount = 0;
	m_HeshRCount = 0;
	m_Repeat = false;
	m_ChangeIdx = 0;
	m_RefreshLVL = 2;
	m_RefreshCNT = 0;

	m_my_EGBP_pledge = 0.0f;
	m_my_ECN_pledge = 0.0f;
	m_my_Active_pledge = true;
	m_my_pledge_shareID = 0;
	m_pledge_Total = 0;

	m_current_IDX = 0;

	m_vec_blockledger.clear();
	m_vec_difficulty.clear();
	m_vec_eslid.clear();
	m_vec_targetid.clear();
	m_vec_blockid.clear();
	m_vec_score.clear();
	m_vec_maxvote.clear();
	m_vec_eslcode.clear();
	m_vec_pledgetype.clear();
	m_vec_maxpledge.clear();
	m_vec_targetbreach.clear();
	m_vec_owner.clear();
	m_vec_scoremax.clear();
	m_vec_markmax.clear();
	m_vec_markmin.clear();
	m_vec_jobboardid.clear();
	m_vec_blocktype.clear();
	m_vec_timebreach.clear();
	m_vec_bckred.clear();
	m_vec_bckgreen.clear();
	m_vec_bckblue.clear();
	m_vec_price.clear();

#ifdef ECOIN_OSI_MEMORY
	ac_Push(m_Bank_ecoin, f_ref_CurrentPath + g_ref_Div + "m_Bank_ecoin");
	ac_Push(m_Price, f_ref_CurrentPath + g_ref_Div + "m_Price");
	ac_Push(m_Unit, f_ref_CurrentPath + g_ref_Div + "m_Unit");
	ac_Push(m_TX, f_ref_CurrentPath + g_ref_Div + "m_TX");
	ac_Push(m_Circulationamt, f_ref_CurrentPath + g_ref_Div + "m_Circulationamt");
	ac_Push(m_Start, f_ref_CurrentPath + g_ref_Div + "m_Start");
	ac_Push(m_RefreshLVL, f_ref_CurrentPath + g_ref_Div + "m_RefreshLVL");
	ac_Push(m_Reward, f_ref_CurrentPath + g_ref_Div + "m_Reward");
	ac_Push(m_RewardID, f_ref_CurrentPath + g_ref_Div + "m_RewardID");
	ac_Push(m_my_EGBP_pledge, f_ref_CurrentPath + g_ref_Div + "m_my_EGBP_pledge");
	ac_Push(m_my_ECN_pledge, f_ref_CurrentPath + g_ref_Div + "m_my_ECN_pledge");
	ac_Push(m_my_Active_pledge, f_ref_CurrentPath + g_ref_Div + "m_my_Active_pledge");
	ac_Push(m_my_pledge_shareID, f_ref_CurrentPath + g_ref_Div + "m_my_pledge_shareID");
	ac_Push(m_pledge_Total, f_ref_CurrentPath + g_ref_Div + "m_pledge_Total");
	ac_Push(m_vec_blockledger, f_ref_CurrentPath + g_ref_Div + "m_vec_blockledger");
	ac_Push(m_vec_difficulty, f_ref_CurrentPath + g_ref_Div + "m_vec_difficulty");
	ac_Push(m_vec_eslid, f_ref_CurrentPath + g_ref_Div + "m_vec_eslid");
	ac_Push(m_vec_targetid, f_ref_CurrentPath + g_ref_Div + "m_vec_targetid");
	ac_Push(m_vec_blockid, f_ref_CurrentPath + g_ref_Div + "m_vec_blockid");
	ac_Push(m_vec_score, f_ref_CurrentPath + g_ref_Div + "m_vec_score");
	ac_Push(m_vec_maxvote, f_ref_CurrentPath + g_ref_Div + "m_vec_maxvote");
	ac_Push(m_vec_eslcode, f_ref_CurrentPath + g_ref_Div + "m_vec_eslcode");
	ac_Push(m_vec_pledgetype, f_ref_CurrentPath + g_ref_Div + "m_vec_pledgetype");
	ac_Push(m_vec_maxpledge, f_ref_CurrentPath + g_ref_Div + "m_vec_maxpledge");
	ac_Push(m_vec_targetbreach, f_ref_CurrentPath + g_ref_Div + "m_vec_targetbreach");
	ac_Push(m_vec_owner, f_ref_CurrentPath + g_ref_Div + "m_vec_owner");
	ac_Push(m_vec_scoremax, f_ref_CurrentPath + g_ref_Div + "m_vec_scoremax");
	ac_Push(m_vec_markmax, f_ref_CurrentPath + g_ref_Div + "m_vec_markmax");
	ac_Push(m_vec_markmin, f_ref_CurrentPath + g_ref_Div + "m_vec_markmin");
	ac_Push(m_vec_jobboardid, f_ref_CurrentPath + g_ref_Div + "m_vec_jobboardid");
	ac_Push(m_vec_blocktype, f_ref_CurrentPath + g_ref_Div + "m_vec_blocktype");
	ac_Push(m_vec_timebreach, f_ref_CurrentPath + g_ref_Div + "m_vec_timebreach");
	ac_Push(m_vec_bckred, f_ref_CurrentPath + g_ref_Div + "m_vec_bckred");
	ac_Push(m_vec_bckgreen, f_ref_CurrentPath + g_ref_Div + "m_vec_bckgreen");
	ac_Push(m_vec_bckblue, f_ref_CurrentPath + g_ref_Div + "m_vec_bckblue");
	ac_Push(m_vec_price, f_ref_CurrentPath + g_ref_Div + "m_vec_price");

	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acExec_preference_PayBlock", (ecom_base::ControllerMethod_void)&Wallet::acExec_preference_PayBlock);
	ac_PushFunction(f_ref_CurrentPath + g_ref_fun_Div + "acExec_preference_PayShare_Package", (ecom_base::ControllerMethod_void)&Wallet::acExec_preference_PayShare_Package);
#endif

#if 0
	printf("   //////////////////////////////////\n");
	printf("  // - ecoin a digital currency - //\n");
	printf(" // WELCOME TO YOUR ECOIN WALLET //\n");
	printf("//////////////////////////////////\n");
#endif

	m_CTX = std::make_shared<ECCVerifyHandle>();
}

Wallet::~Wallet()
{
	m_vec_Key.clear();
}

bool Wallet::acGet_assetContractbyID(float f_CostAmt, int f_ComID)
{			//using comid only capability
	return acGet_assetContractbyID(-1, f_CostAmt, f_ComID);
}

bool Wallet::acGet_assetContractbyID(int f_ShareID, float f_CostAmt, int f_ComID)
{
	if(f_ShareID <= 0)
		{
		return true;
		}

	if(f_ComID > 0)
		{
#if 0
		mutex_qcomdb.lock();
#endif

		char* modquery = ag_ClearChar(1000);
		::sprintf(modquery, "SELECT owner, cost FROM com WHERE id = %i", f_ComID);
		g_SafeL[2]->acSelectCommand(modquery, false, false);
		delete modquery;

		int f_ModLCount = 0;

		//ECN::Stat::: f_ModLCount
		if(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
			{
			f_ModLCount = 0;
			}
		else
			{
			f_ModLCount = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)]->size();
			}

		//checks
		if(f_ModLCount > 0)
			{
			std::string f_Owner = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)]->at(0)[0];
			float f_Cost = atof(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)]->at(0)[1].c_str());

			//my component
			if(f_Owner.compare(GetAdr()) == 0)
				{
#if 0
				mutex_qcomdb.unlock();
#endif

				return true;
				}

			//unproper costing
			if(f_CostAmt <= 0.0f)
				{
				if(f_Cost > 0.0f)
					{
					f_CostAmt = f_Cost;
					}
				else
					{
#if 0
					mutex_qcomdb.unlock();
#endif

					return true;
					}
				}
#if 1 //default load free
			else
				{
#if 0
				mutex_qcomdb.unlock();
#endif

				return true;
				}
#endif
			}
		else
			{ //not exist
#if 0
			mutex_qcomdb.unlock();
#endif

			return false;
			}

#if 0
		mutex_qcomdb.unlock();
#endif
		}
	else if(f_ShareID > 0)
		{
		char* modquery = ag_ClearChar(1000);
		::sprintf(modquery, "SELECT owner, price FROM share WHERE id = %i", f_ShareID);
		g_SafeL[0]->acSelectCommand(modquery, false, false);
		delete modquery;

		int f_ModLCount = 0;

		//ECN::Stat::: f_ModLCount
		if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
			{
			f_ModLCount = 0;
			}
		else
			{
			f_ModLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
			}

		//checks
		if(f_ModLCount > 0)
			{
			std::string f_Owner = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(f_ModLCount - 1)[0];
			float f_Cost = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(f_ModLCount - 1)[1].c_str());

			//my share
			if(f_Owner.compare(GetAdr()) == 0)
				{
				return true;
				}

			//unproper costing
			if(f_CostAmt <= 0.0f)
				{
				if(f_Cost > 0.0f)
					{
					f_CostAmt = f_Cost;
					}
				else
					{
					return true;
					}
				}
			else //default load free
				{
				return true;
				}
			}
		else
			{ //not exist
			return false;
			}
		}

	//-Assume proper pricing and cost value above zero

	char* modquery = ag_ClearChar(1000);
	::sprintf(modquery, "SELECT id, amtpay FROM modpay WHERE payowner = '%s' AND (shareid = %i OR comid = %i)", GetAdr().c_str(), f_ShareID, f_ComID);
	g_SafeL[0]->acSelectCommand(modquery, false, false);
	delete modquery;

	int f_ModLCount = 0;

	float f_PayMass = 0.0f;

	//ECN::Stat::: f_ModLCount
	if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
		{
		f_ModLCount = 0;
		}
	else
		{
		f_ModLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
		}

	if(f_ModLCount > 0)
		{
		for(int f_Jet = 0; f_Jet < f_ModLCount; f_Jet++)
			{
			int f_ID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(f_Jet)[0].c_str());

			if(f_ID > 0)
				{
				float f_PaidAmt = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(f_Jet)[1].c_str());

				if(f_PaidAmt > 0.0f)
					{
					f_PayMass += f_PaidAmt;
					}
				}
			}
		}
	
	//-common flow also check ECN transactions
	char* txquery = ag_ClearChar(1000);
	::sprintf(txquery, "SELECT id, amt FROM transactions WHERE status != -5 AND confirmation = 6 AND shareid = %i AND owner = '%s'", f_ShareID, GetAdr().c_str());
	g_SafeL[0]->acSelectCommand(txquery, false, false);
	delete txquery;

	int f_TXLCount = 0;

	//ECN::Stat::: f_TXLCount
	if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
		{
		f_TXLCount = 0;
		}
	else
		{
		f_TXLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
		}

	if(f_TXLCount > 0)
		{
		for(int f_Jet = 0; f_Jet < f_TXLCount; f_Jet++)
			{
			int f_ID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(f_Jet)[0].c_str());

			if(f_ID > 0)
				{
				float f_PaidAmt = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(f_Jet)[1].c_str());

				if(f_PaidAmt > 0.0f)
					{
					f_PayMass + -f_PaidAmt;

					if(f_PaidAmt >= f_CostAmt)
						{
						return true; //win conditions
						}
					}
				}
			}
		}
	
	return false;
}

float Wallet::acGet_assetContractbyID(int f_ShareID, int f_ComID)
{
	float f_CumulativeValue = 0.0f;

	char* modquery = ag_ClearChar(1000);
	::sprintf(modquery, "SELECT id, amtpay FROM modpay WHERE payowner = '%s' AND (shareid = %i OR comid = %i)", GetAdr().c_str(), f_ShareID, f_ComID);
	g_SafeL[0]->acSelectCommand(modquery, false, false);
	delete modquery;

	int f_ModLCount = 0;
		
	//ECN::Stat::: f_ModLCount
	if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
		{
		f_ModLCount = 0;
		}
	else
		{
		f_ModLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
		}

	//Already paid! return bill amount paid.
	if(f_ModLCount > 0)
		{
		for(int f_Jet = 0; f_Jet < f_ModLCount; f_Jet++)
			{
			int f_ID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].c_str());

			if(f_ID > 0)
				{
				f_CumulativeValue += atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[1].c_str());
				}
			}
		}

	//\/ cont. No previous payments for this item FRESH Check 1. com exists 2. !my com else return -5.0f 3. return com cost
	if(f_ShareID <= 0)
		{
		char* modquery2 = ag_ClearChar(1000);
		::sprintf(modquery2, "SELECT id, owner FROM com WHERE id = %i", f_ComID);
		g_SafeL[2]->acSelectCommand(modquery2, false, false);
		delete modquery2;

		int f_ModLCount2 = 0;

		//ECN::Stat::: f_ModLCount
		if(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
			{
			f_ModLCount2 = 0;
			}
		else
			{
			f_ModLCount2 = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)]->size();
			}

		if(f_ModLCount2 == 1) //com exists
			{
			int f_ID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].c_str());

			if(f_ID > 0) //com id good
				{
				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[1].compare(GetAdr()) == 0)
					{
					return -5.0f;
					}
				else
					{
					return f_CumulativeValue;
					}
				}
			}
		else
			{
			//add debug message
			}
		}
	else
		{
		char* modquery2 = ag_ClearChar(1000);
		::sprintf(modquery2, "SELECT id, owner FROM share WHERE id = %i", f_ShareID);
		g_SafeL[2]->acSelectCommand(modquery2, false, false);
		delete modquery2;

		int f_ModLCount2 = 0;

		//ECN::Stat::: f_ModLCount
		if(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
			{
			f_ModLCount2 = 0;
			}
		else
			{
			f_ModLCount2 = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)]->size();
			}

		if(f_ModLCount2 > 1)
			{	//my component
			if(GetAdr().compare(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)]->at(f_ModLCount2 - 1)[1]) == 0)
				{
				return -5.0f;
				}
			else
				{
				//-common flow also check ECN transactions
				char* txquery = ag_ClearChar(1000);
				::sprintf(txquery, "SELECT id, amt FROM transactions WHERE status != -5 AND confirmation = 6 AND shareid = %i AND owner = '%s'", f_ShareID, GetAdr().c_str());
				g_SafeL[0]->acSelectCommand(txquery, false, false);
				delete txquery;

				int f_TXLCount = 0;

				//ECN::Stat::: f_TXLCount
				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
					{
					f_TXLCount = 0;
					}
				else
					{
					f_TXLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
					}

				float f_PayMass = 0.0f;

				if(f_TXLCount > 0)
					{
					for(int f_Jet = 0; f_Jet < f_TXLCount; f_Jet++)
						{
						int f_ID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(f_Jet)[0].c_str());

						if(f_ID > 0)
							{
							float f_PaidAmt = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(f_Jet)[1].c_str());

							if(f_PaidAmt > 0.0f)
								{
								f_CumulativeValue += f_PaidAmt;
								}
							}
						}
					}

				return f_CumulativeValue;
				}
			}
		}

	//\/ cont. Return -1.0f for com ! exist
	
	return -1.0f;
}

bool Wallet::acBuy_ShareComID(int f_ComID, float f_PayAmt, float f_CostAmt, int f_ShareID)
{
	std::string f_ref_CurrentPath = "Wallet::acBuy_ShareComID";

	if(g_WalletOpen == true)
		{
		double f_BalanceCPS = GetBalanceCPS(true, 0);

		float f_PaidAmt = acGet_assetContractbyID(f_ShareID, f_ComID);

		float f_BillAmt = f_CostAmt - f_PaidAmt;

		if(f_PaidAmt < f_CostAmt)
			{
			if(f_BillAmt > f_BalanceCPS)
				{
				return false;
				}
			}
		else if(f_BillAmt <= 0.0f)
			{
			return true;
			}

		if(m_Bank_ecoin_constant > 0)
			{
			char* g_modpayvalue[11];
			char* g_modpayfield[11];

			for(int f_s = 0; f_s < 11; f_s++)
				{
				g_modpayvalue[f_s] = (char*)malloc(sizeof(char) * 512);
				g_modpayfield[f_s] = (char*)malloc(sizeof(char) * 512);
				}

			::sprintf(g_modpayfield[0], "payowner");
			::sprintf(g_modpayfield[1], "paypubkey");
			::sprintf(g_modpayfield[2], "payvsign");
			::sprintf(g_modpayfield[3], "status");
			::sprintf(g_modpayfield[4], "assetcontract");
			::sprintf(g_modpayfield[5], "qamid");
			::sprintf(g_modpayfield[6], "forkref");
			::sprintf(g_modpayfield[7], "shareid");
			::sprintf(g_modpayfield[8], "comid");
			::sprintf(g_modpayfield[9], "amtpay");
			::sprintf(g_modpayfield[10], "timet");

			std::string f_InputHash = "";

			//add extra data like status etc.
			f_InputHash += GetAdr();
			f_InputHash += m_vec_Key[0]->m_pubkey;
			char* f_Char = ag_ClearChar(5);
			::sprintf(f_Char, "%i", 0);
			f_InputHash += f_Char;
			delete f_Char;

			f_Char = ag_ClearChar(16);
			::sprintf(f_Char, "%i", f_ShareID);
			std::string f_newassetContract = "BUYSHAREID#";
			f_newassetContract += f_Char;
			delete f_Char;
			f_InputHash += f_newassetContract;

			f_Char = ag_ClearChar(16);
			::sprintf(f_Char, "%i", -1);
			f_InputHash += f_Char;
			delete f_Char;
			f_InputHash += "eslcode";

			f_Char = ag_ClearChar(32);
			::sprintf(f_Char, "%i", f_ShareID);
			f_InputHash += f_Char;
			delete f_Char;

			f_Char = ag_ClearChar(16);
			::sprintf(f_Char, "%i", f_ComID);
			f_InputHash += f_Char;
			delete f_Char;

			float f_ProductPrice = f_BillAmt;

			f_Char = ag_ClearChar(32);
			::sprintf(f_Char, "%f", f_ProductPrice);
			f_InputHash += f_Char;
			delete f_Char;

			time_t f_currentTime;
			time(&f_currentTime);

			f_Char = ag_ClearChar(64);
			::sprintf(f_Char, "%i", f_currentTime);
			f_InputHash += f_Char;
			delete f_Char;

			g_hasha.init(); //reset hasher state
			g_hasha.process(f_InputHash.begin(), f_InputHash.end());
			g_hasha.finish();

			std::string f_HashOutput = "00000000000000000000000000000000";

			picosha2::get_hash_hex_string(g_hasha, f_HashOutput);

			unsigned char k[32];

			Cube::ag_hex2bin(k, f_HashOutput.c_str(), 64);

			uint256& f_256uint = reinterpret_cast<uint256&>(k);

			std::vector<unsigned char> f_sig;

			bool f_res = m_vec_Key[0]->Sign(f_256uint, f_sig);

			char f_k[142];

			Cube::ag_bin2hex((char*)f_k, f_sig, 71);

			std::string f_vsign = "";

			for(int j2o = 0; j2o < 142; j2o++)
				{
				f_vsign.push_back(f_k[j2o]);
				}

			::sprintf(g_modpayvalue[0], "%s", GetAdr().c_str());
			::sprintf(g_modpayvalue[1], "%s", m_vec_Key[0]->m_pubkey.c_str());
			::sprintf(g_modpayvalue[2], "%s", f_vsign.c_str());
			::sprintf(g_modpayvalue[3], "%i", 0);
			::sprintf(g_modpayvalue[4], "%s", f_newassetContract.c_str());
			::sprintf(g_modpayvalue[5], "%i", -1);
			::sprintf(g_modpayvalue[6], "%s", "eslcode");
			::sprintf(g_modpayvalue[7], "%i", f_ShareID);
			::sprintf(g_modpayvalue[8], "%i", f_ComID);
			::sprintf(g_modpayvalue[9], "%f", f_PayAmt);
			::sprintf(g_modpayvalue[10], "%i", f_currentTime);

			int f_SyncUniqueID = g_SafeL[0]->Insert("modpay", (const char **)g_modpayfield, (const char **)g_modpayvalue, 11, true, false);

			for(int f_s = 0; f_s < 11; f_s++)
				{
				free(g_modpayvalue[f_s]);
				free(g_modpayfield[f_s]);
				}

			acPay_preference(f_ComID, f_PayAmt, ecoin_Preferences::ecoin_Pref_ShareCom);

			  //////////////////////////////
			 // setBalance version 5.1.3 //
			//////////////////////////////

			return acSet_ConstantBalance(GetAdr(), (f_PayAmt * -1));
			}
		else
			{
			return false;
			}
		}

	return false;
}

int Wallet::acSet_ConstantBalance(std::string f_owner, float f_AmtDiff)
{
	char* f_balancequery = ag_ClearChar(256);
	::sprintf(f_balancequery, "SELECT id, amt FROM employee WHERE owner = '%s'", f_owner.c_str());
	g_SafeL[0]->acSelectCommand(f_balancequery, true, false);
	delete f_balancequery;

	int f_ownersCount = 0;
		
	if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
		{
		f_ownersCount = 0;
		}
	else
		{
		f_ownersCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
		}

	if(f_ownersCount == 1)
		{
		int f_ID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].c_str());
		float f_amt = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[1].c_str());

		if(f_amt + f_AmtDiff < 0.0f)
			{
			return 0;
			}
		else
			{
			f_amt += f_AmtDiff;
			}

		char* f_ownervalue[3];
		char* f_ownerfield[3];
		char* f_ownerwhere[3];

		f_ownervalue[0] = (char*)malloc(sizeof(char) * 1024);
		f_ownerfield[0] = (char*)malloc(sizeof(char) * 1024);
		f_ownerwhere[0] = (char*)malloc(sizeof(char) * 1024);

		::sprintf(f_ownerfield[0], "amt");
		::sprintf(f_ownervalue[0], "%f", f_amt);
		::sprintf(f_ownerwhere[0], "id = %i", f_ID);

		g_SafeL[0]->Update("employee", (const char**)f_ownerfield, (const char**)f_ownervalue, 1, f_ownerwhere[0], true, false);

		free(f_ownervalue[0]);
		free(f_ownerfield[0]);
		free(f_ownerwhere[0]);

		return 1;
		}
	else if(f_ownersCount == 0)
		{
		char* g_syncvalue[5];
		char* g_syncfield[5];

		for(int f_s = 0; f_s < 5; f_s++)
			{
			g_syncvalue[f_s] = (char*)malloc(sizeof(char) * 256);
			g_syncfield[f_s] = (char*)malloc(sizeof(char) * 256);
			}

		::sprintf(g_syncfield[0], "owner");
		::sprintf(g_syncfield[1], "amt");
		::sprintf(g_syncfield[2], "bosslvlmin");
		::sprintf(g_syncfield[3], "toke_version");
		::sprintf(g_syncfield[4], "toke_currency");

		::sprintf(g_syncvalue[0], "%s", f_owner.c_str());

		if(f_AmtDiff > 0.0f)
			{
			::sprintf(g_syncvalue[1], "%f", f_AmtDiff);
			}
		else
			{
			::sprintf(g_syncvalue[1], "%f", 0.0f);
			}

		::sprintf(g_syncvalue[2], "%f", 0.0f);
		::sprintf(g_syncvalue[3], "%i", 1);
		::sprintf(g_syncvalue[4], "%s", "eGBP");

		int f_SyncUniqueID = g_SafeL[0]->Insert("employee", (const char **)g_syncfield, (const char **)g_syncvalue, 5, true, false);

		for(int f_s = 0; f_s < 5; f_s++)
			{
			free(g_syncvalue[f_s]);
			free(g_syncfield[f_s]);
			}

		if(f_AmtDiff >= 0.0f)
			{
			return 1;
			}
		else
			{
			return 0;
			}
		}

	return 0;
}

void Wallet::acPay_preference(int f_ShareID, float f_Amt, int f_TypeID)
{
	switch(f_TypeID)
		{
		case ecoin_Preferences::ecoin_Pref_TypeNameBlock: //fixme
			{
			acExec_preference_PayBlock();
			}break;

		case ecoin_Preferences::ecoin_Pref_VoteDriven: //fixme
			{
			acExec_preference_PayBlock();
			}break;

		case ecoin_Preferences::ecoin_Pref_TimedPledge: //fixme
			{
			g_QcomManager->m_preference_ShareID = f_ShareID;
			g_QcomManager->m_preference_Amt = f_Amt;

			acExec_preference_PayBlock();
			}break;

		case ecoin_Preferences::ecoin_Pref_MaxPledge:
			{
			g_QcomManager->m_preference_ShareID = f_ShareID;
			g_QcomManager->m_preference_Amt = f_Amt;

			acExec_preference_PayBlock();
			}break;

		case ecoin_Preferences::ecoin_Pref_ShareCom:
			{
			g_QcomManager->m_preference_ShareID = f_ShareID;
			g_QcomManager->m_preference_Amt = f_Amt;

			acExec_preference_PayShare_Package();
			}break;
		}
}

void Wallet::acExec_preference_PayBlock(void)
{
	char* f_payquery = ag_ClearChar(2048);
	::sprintf(f_payquery, "UPDATE quantumangel_cubex.employee SET employee.amt = employee.amt + ((SELECT IFNULL(SUM(access * pledge), 0.0) / (SELECT SUM(access) FROM reference WHERE blockid = %i) FROM reference WHERE reference.owner = employee.owner AND reference.blockid = %i) * (SELECT SUM(pledge) FROM reference WHERE blockid = %i));", g_JobID, g_JobID, g_JobID);
	g_SafeL[0]->UpdateQuery(f_payquery);
	delete f_payquery;
}

void Wallet::acExec_preference_PayShare_Package(void)
{
	int f_ShareID = g_QcomManager->m_preference_ShareID;
	float f_Amt = g_QcomManager->m_preference_Amt;

	if(f_ShareID > 0)
		{
		if((float)GetBalanceCPS(true, 0) - f_Amt < 0.0f)
			{
			char* f_payquery = ag_ClearChar(2048);

			::sprintf(f_payquery, "UPDATE quantumangel_cubex.employee SET employee.amt = employee.amt + ((SELECT IFNULL(SUM(access * pledge), 0.0) / (SELECT SUM(access) FROM reference WHERE shareid = %i) FROM reference WHERE reference.owner = employee.owner AND reference.shareid = %i) * (SELECT SUM(pledge) FROM reference WHERE shareid = %i));", f_ShareID, f_ShareID, f_ShareID);

			g_SafeL[0]->UpdateQuery(f_payquery);

		    delete f_payquery;

			SetBalanceCPS(f_Amt * -1.0f);

			g_PreComLock = true;
			}
		else
			{
			//add debug message
			}
		}
	else
		{
		//add debug message
		}
}

std::future<bool> Wallet::Open(void)
{
	std::string f_ref_CurrentPath = "Wallet::Open";

	g_CubeHeshExport = std::make_shared_reflect<Cube::CubeHeshExporter>();

	ag_StatusLive(f_ref_CurrentPath, "g_QcomManager", true);
	g_QcomManager = std::make_shared_reflect<QcomManager>();

	ag_StatusLive(f_ref_CurrentPath, "g_Schedular[0]", true);
	g_Schedular[0] = std::make_shared_reflect<Schedular>();
	ag_StatusLive(f_ref_CurrentPath, "g_Schedular[1]", true);
	g_Schedular[1] = std::make_shared_reflect<Schedular>();
	ag_StatusLive(f_ref_CurrentPath, "g_Schedular[2]", true);
	g_Schedular[2] = std::make_shared_reflect<Schedular>();

	bool f_Live = true;
	int f_Int = 1;

	if(!g_SafeL[0])
		{
		ag_StatusLive(f_ref_CurrentPath, "g_SafeL[0]", true);
		g_SafeL[0] = std::make_shared_reflect<icSafeL>(0);
		g_SafeL[0]->Initialize();

		f_Int = g_SafeL[0]->Connect("localhost", "root", "f", "gdb", 3306);
		}

	if(f_Int != 1)
		{
		f_Live = false;
		}

	if(!g_SafeL[1])
		{
		ag_StatusLive(f_ref_CurrentPath, "g_SafeL[1]", true);
		g_SafeL[1] = std::make_shared_reflect<icSafeL>(1);
		g_SafeL[1]->Initialize();

		f_Int = g_SafeL[1]->Connect("localhost", "root", "f", "gdb", 3306);
		}

	if(f_Int != 1)
		{
		f_Live = false;
		}

	if(!g_SafeL[2])
		{
		ag_StatusLive(f_ref_CurrentPath, "g_SafeL[2]", true);
		g_SafeL[2] = std::make_shared_reflect<icSafeL>(2);
		g_SafeL[2]->Initialize();

		f_Int = g_SafeL[2]->Connect("bo.com", "root", "OX", "gdb", 3306);
		}

	if(f_Int != 1)
		{
		f_Live = false;
		}

	if(f_Live == true)
		{
		g_ConnectedECD = true;
		}

	bool f_Sane = false;
	while(!f_Sane)
		{
		bool f_Un = ECC_Start();

		if(!f_Un)
			{
			if(ECC_InitSanityCheck())
				{
				f_Sane = true;
				}
			else
				{
				ECC_Stop();
				}
			}
		else
			{
			ECC_Stop();
			}
		}

#if 0
	printf("Sane = %i\n", f_Sane);
#endif

	m_RefreshLVL = 2;

	if(m_Start)
		{ //////////////
		 // Start
		//  Wallet
		std::string f_StringBuf = Prepare_Start();

		StartCPS();

		bool f_Scan = true;
		while(f_Scan == true)
			{
			::winrt::Windows::Storage::Pickers::FileSavePicker savePicker;

			savePicker.SuggestedStartLocation(::winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);

			// Dropdown of file types the user can save the file as
			savePicker.FileTypeChoices().Insert(L"ecoin Wallet", winrt::single_threaded_vector<winrt::hstring>({ L".eco" }))
				;
			// Default file name if the user does not type one in or select a file to replace
			savePicker.SuggestedFileName(L"ecoinWallet");

			::winrt::Windows::Storage::StorageFile file = co_await savePicker.PickSaveFileAsync();

			if(file != nullptr)
				{
				::winrt::Windows::Storage::CachedFileManager::DeferUpdates(file);

				// write to file
				await winrt::Windows::Storage::FileIO::WriteTextAsync(file, StrUsingStr(f_StringBuf));

				// Let Windows know that we're finished changing the file so the other app can update the remote version of the file.
				// Completing updates may require Windows to ask for user input.
				::winrt::Windows::Storage::Provider::FileUpdateStatus status = co_await ::winrt::Windows::Storage::CachedFileManager::CompleteUpdatesAsync(file);

				if(status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::Complete)
					{
					m_OK = true;
					m_Repeat = false;
					g_WalletOpen = true;
					f_Scan = false;
					}
				else if (status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::CompleteAndRenamed)
					{
					m_OK = true;
					m_Repeat = false;
					g_WalletOpen = true;
					f_Scan = false;
					}
				else
					{
					for(;;)
						{
						//.
						}
					}
				}
			}
		}
	else
		{
		bool f_Scan = true;
		while(f_Scan == true)
			{
			::winrt::Windows::Storage::Pickers::FileOpenPicker openPicker;
			openPicker.ViewMode(::winrt::Windows::Storage::Pickers::PickerViewMode::Thumbnail);
			openPicker.SuggestedStartLocation(::winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
			openPicker.FileTypeFilter().ReplaceAll({ L".eco" });
			::winrt::Windows::Storage::StorageFile file = co_await openPicker.PickSingleFileAsync();

			if(file != nullptr)
				{
				int f_WalletVersion = 0;

				winrt::hstring fileContent = co_await winrt::Windows::Storage::FileIO::ReadTextAsync(file);

				std::string f_Char = to_string(fileContent);

				uint* f_Chk = new uint(0);

				if(f_Char.length() > 1)
					{
					g_WALLETBANK = acBufreadValueDouble(f_Char, f_Chk);
					g_HESHSAVEID = acBufreadValueInteger(f_Char, f_Chk);
					acBufreadValueInteger(f_Char, f_Chk);

					if(*(f_Chk) == 0)
						{
						f_WalletVersion = 1;

						m_ChangeIdx = acBufreadValueInteger(f_Char, f_Chk);
						int f_KeyNom = acBufreadValueInteger(f_Char, f_Chk);

						if(f_KeyNom >= 5)
							{
							f_WalletVersion = 3;
							}

						if(f_KeyNom > 1)
							{
							f_WalletVersion = 3;

							int f_prefix = acBufreadValueInteger(f_Char, f_Chk);
							std::string f_keypass = acBufreadValueString(f_Char, f_Chk);
							std::string f_pubkey = acBufreadValueString(f_Char, f_Chk);
							std::string f_owner = acBufreadValueString(f_Char, f_Chk);

							unsigned char *f_p = new unsigned char[8];
							Cube::ag_hex2bin(f_p, f_keypass.c_str(), f_keypass.size());

							std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();

							for(int f_lm = 0; f_lm < 8; f_lm++)
								{
								key->keydata[f_lm] = f_p[f_lm];
								}

							key->m_prefix = f_prefix;
							key->m_owner = f_owner;
							key->m_pubkey = f_pubkey;
							m_Bank_Adr = f_owner;

							m_vec_Key.push_back(key);
							}
						else if(f_KeyNom == 1) //early version
							{
							f_WalletVersion = 2;

							std::string f_keypass = acBufreadValueString(f_Char, f_Chk);
							std::string f_pubkey = acBufreadValueString(f_Char, f_Chk);
							std::string f_owner = acBufreadValueString(f_Char, f_Chk);

							unsigned char *f_p = new unsigned char[8];
							Cube::ag_hex2bin(f_p, f_keypass.c_str(), f_keypass.size());

							std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();

							for(int f_lm = 0; f_lm < 8; f_lm++)
								{
								key->keydata[f_lm] = f_p[f_lm];
								}

							key->m_prefix = 1;
							key->m_owner = f_owner;
							key->m_pubkey = f_pubkey;
							m_Bank_Adr = f_owner;

							m_vec_Key.push_back(key);
							}
						
						for(int f_m = 1; f_m < f_KeyNom; f_m++)
							{
							int f_prefix = acBufreadValueInteger(f_Char, f_Chk);
							std::string f_keypass = acBufreadValueString(f_Char, f_Chk);
							std::string f_pubkey = acBufreadValueString(f_Char, f_Chk);
							std::string f_owner = acBufreadValueString(f_Char, f_Chk);

							unsigned char *f_p = new unsigned char[8];
							Cube::ag_hex2bin(f_p, f_keypass.c_str(), f_keypass.size());

							std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();

							for(int f_lm = 0; f_lm < 8; f_lm++)
								{
								key->keydata[f_lm] = f_p[f_lm];
								}

							key->m_prefix = f_prefix;
							key->m_owner = f_owner;
							key->m_pubkey = f_pubkey;

							m_vec_Key.push_back(key);
							}
						}

						//////////////////////////////
					   // ecoin Wallet
					  // check
					 // upgrade
					// save
					switch(f_WalletVersion)
						{
						case 1:	//empty broken
							{
							m_Bank_ecoin = 0.0f;
							m_Bank_ecoin_constant = 0.0f;
							g_WALLETBANK = 0.0f;
							g_HESHSAVEID = 0;

#ifndef DISABLE_ECC
							std::shared_ptr<CKey> f_1key = ag_GenerateAddress(1);

							m_vec_Key.push_back(f_1key);

							m_Bank_Adr = f_1key->m_owner;
#endif
							}
						case 2: //version 1
							{
							m_ChangeIdx = 0;

#ifndef DISABLE_ECC
							std::shared_ptr<CKey> f_key = ag_GenerateAddress(2);

							m_vec_Key.push_back(f_key);

							f_key = ag_GenerateAddress(2);

							m_vec_Key.push_back(f_key);

							f_key = ag_GenerateAddress(2);

							m_vec_Key.push_back(f_key);

							f_key = ag_GenerateAddress(2);

							m_vec_Key.push_back(f_key);
#endif

							m_Bank_ecoin = g_WALLETBANK;
							m_Bank_ecoin_constant = 0.0f;
							m_OK = true;
							m_Repeat = false;

#if 0
							printf("Wallet fully loaded OK updating...\n");
#endif

							Update();
							};
						case 3:
							{
							m_Bank_ecoin = g_WALLETBANK;
							m_Bank_ecoin_constant = 0.0f;
							m_OK = true;
							m_Repeat = false;

#if 0
							printf("Wallet fully loaded OK updating...\n");
#endif

							g_WalletOpen = true;
							f_Scan = false;
							}break;
						}
					}
				else
					{
					//fail
					m_OK = false;
					m_Repeat = true;
					}
				}
			else
				{
				m_OK = false;
				m_Repeat = true;
				}
			}
		}

	co_return m_OK;
}

std::string Wallet::Prepare(void)
{
	std::string f_Result;
	f_Result.clear();
	acBufwriteValueDouble(&f_Result, g_WALLETBANK);
	acBufwriteValueInteger(&f_Result, g_HESHSAVEID);
	acBufwriteValueInteger(&f_Result, 5000);
	acBufwriteValueInteger(&f_Result, m_ChangeIdx);
	acBufwriteValueInteger(&f_Result, m_vec_Key.size());

	for(int f_m = 0; f_m < m_vec_Key.size(); f_m++)
		{
		f_Result = f_Result + ag_Key_Serialize(m_vec_Key[f_m]);
		}

	m_Bank_ecoin = g_WALLETBANK;

	return f_Result;
}

std::string ag_Key_Serialize(std::shared_ptr<CKey> f_key)
{
	  /////////
	 // Pass
	//
	std::string f_Result;
	f_Result.clear();

	char *lx2 = (char*)malloc(f_key->keydata.size() * 2 * sizeof(char));

	int i2;
	for (i2 = 0; i2 < f_key->keydata.size(); i2++)
		{
		::sprintf(lx2 + (i2 * 2) , "%02x", f_key->keydata[i2]);
		}

	std::string f_OutputKey2(lx2);
	std::string f_OutputKey2v3;

	f_OutputKey2v3.clear();
	for(int f_g = 0; f_g < 16; f_g++)
		{
		f_OutputKey2v3.push_back(f_OutputKey2[f_g]);
		}

	acBufwriteValueInteger(&f_Result, f_key->m_prefix);

	f_Result = f_Result + f_OutputKey2v3;
	f_Result = f_Result + "::::";

	std::string f_PUBKEY = f_key->m_pubkey;
	f_Result = f_Result + f_PUBKEY + "::::";

	std::string f_ADR = f_key->m_owner;
	f_Result = f_Result + f_ADR + "::::";

	return f_Result;
}

std::string Wallet::Prepare_Start(void)
{
	std::string f_Result;
	f_Result.clear();

	acBufwriteValueDouble(&f_Result, 0.0f);
	acBufwriteValueInteger(&f_Result, 0);
	acBufwriteValueInteger(&f_Result, 5000);
	acBufwriteValueInteger(&f_Result, 0);
	acBufwriteValueInteger(&f_Result, 5);

	std::shared_ptr<CKey> f_1key = ag_GenerateAddress(1);

	m_vec_Key.push_back(f_1key);

	std::string f_ResultKey = ag_Key_Serialize(f_1key);
	f_Result = f_Result + f_ResultKey;

	std::shared_ptr<CKey> f_key = ag_GenerateAddress(2);

	m_vec_Key.push_back(f_key);

	f_ResultKey.clear();
	f_ResultKey = ag_Key_Serialize(f_key);
	f_Result = f_Result + f_ResultKey;

	f_key = ag_GenerateAddress(2);

	m_vec_Key.push_back(f_key);

	f_ResultKey.clear();
	f_ResultKey = ag_Key_Serialize(f_key);
	f_Result = f_Result + f_ResultKey;

	f_key = ag_GenerateAddress(2);

	m_vec_Key.push_back(f_key);

	f_ResultKey.clear();
	f_ResultKey = ag_Key_Serialize(f_key);
	f_Result = f_Result + f_ResultKey;

	f_key = ag_GenerateAddress(2);

	m_vec_Key.push_back(f_key);

	f_ResultKey.clear();
	f_ResultKey = ag_Key_Serialize(f_key);
	f_Result = f_Result + f_ResultKey;

	m_Bank_ecoin = 0.0f;
	m_Bank_ecoin_constant = 0.0f;
	m_Bank_Adr = f_1key->m_owner;

	return f_Result;
}

std::future<void> Wallet::Update(void)
{
	::winrt::Windows::Storage::Pickers::FileSavePicker savePicker;

	savePicker.SuggestedStartLocation(::winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);

	// Dropdown of file types the user can save the file as
	savePicker.FileTypeChoices().Insert(L"ecoin Wallet", winrt::single_threaded_vector<winrt::hstring>({ L".eco" }));

	// Default file name if the user does not type one in or select a file to replace
	savePicker.SuggestedFileName(L"ecoinWallet-Updated");

	::winrt::Windows::Storage::StorageFile file = co_await savePicker.PickSaveFileAsync();

	if(file != nullptr)
		{
		if(file.IsAvailable() == true)
			{
#if 0
			  //////////////
			 // Start
			//  Wallet
			StartCPS();
#endif

			std::string f_StringBuf = Prepare();

			::winrt::Windows::Storage::CachedFileManager::DeferUpdates(file);

			// write to file
			await winrt::Windows::Storage::FileIO::WriteTextAsync(file, StrUsingStr(f_StringBuf));

			// Let Windows know that we're finished changing the file so the other app can update the remote version of the file.
			// Completing updates may require Windows to ask for user input.
			::winrt::Windows::Storage::Provider::FileUpdateStatus status = co_await ::winrt::Windows::Storage::CachedFileManager::CompleteUpdatesAsync(file);

			if(status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::Complete)
				{
				m_OK = true;
				m_Repeat = false;
				g_WalletOpen = true;
				}
			else if(status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::CompleteAndRenamed)
				{
				m_OK = true;
				m_Repeat = false;
				g_WalletOpen = true;
				}
			else
				{
#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif //add debug message
				}
			}
		}
}

double Wallet::GetBalance(bool f_InDollars, int f_UI)
{
	if(f_InDollars)
		{
		return m_Bank_ecoin * GetEValue(f_UI);
		}

	if(m_RefreshLVL > 0)
		{
		m_Bank_ecoin = 0.0;

		if(m_RefreshLVL > 1)
			{
			//RefreshLVL == 2 rerun the verification
			}

		for(int f_I = 0; f_I < m_vec_Key.size(); f_I++)
			{
			char* f_balquery = ag_ClearChar(256);
			::sprintf(f_balquery, "SELECT amt FROM address WHERE owner = '%s'", m_vec_Key[f_I]->m_owner.c_str());
			g_SafeL[f_UI]->acSelectCommand(f_balquery, true, false);
			delete f_balquery;

			int f_ADRCount = 0;
		
			if(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
				{
				f_ADRCount = 0;
				}
			else
				{
				f_ADRCount = g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->size();
				}

			if(f_ADRCount > 0)

			m_Bank_ecoin += atof(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[0].c_str());
			}

		m_RefreshLVL = 0;
		}
	else
		{
		m_RefreshCNT++;
		if(m_RefreshCNT > 5)
			{
			m_RefreshCNT = 0;
			m_RefreshLVL = 2;
			}
		}

	return m_Bank_ecoin;
}

void Wallet::StartCPS(void)
{
	m_Bank_ecoin_constant = 0.0f;

	char* g_syncvalue[5];
	char* g_syncfield[5];

	for(int f_s = 0; f_s < 5; f_s++)
		{
		g_syncvalue[f_s] = (char*)malloc(sizeof(char) * 256);
		g_syncfield[f_s] = (char*)malloc(sizeof(char) * 256);
		}

	::sprintf(g_syncfield[0], "owner");
	::sprintf(g_syncfield[1], "amt");
	::sprintf(g_syncfield[2], "bosslvlmin");
	::sprintf(g_syncfield[3], "toke_version");
	::sprintf(g_syncfield[4], "toke_currency");

	::sprintf(g_syncvalue[0], "%s", GetAdr().c_str());
	::sprintf(g_syncvalue[1], "%f", m_Bank_ecoin_constant);
	::sprintf(g_syncvalue[2], "%f", g_BossLVLMin);
	::sprintf(g_syncvalue[3], "%i", 1);
	::sprintf(g_syncvalue[4], "%s", "eGBP");

	int f_SyncUniqueID = g_SafeL[0]->Insert("employee", (const char **)g_syncfield, (const char **)g_syncvalue, 5, true, false);

	for(int f_s = 0; f_s < 5; f_s++)
		{
		free(g_syncvalue[f_s]);
		free(g_syncfield[f_s]);
		}

	g_EmployeeID = f_SyncUniqueID;
}

void Wallet::SetBalanceCPS(float f_FloatBalance)
{
	char* f_constantupvalue[1];
	char* f_constantupfield[1];
	char* f_constantupwhere[1];

	f_constantupvalue[0] = (char*)malloc(sizeof(char) * 1024);
	f_constantupfield[0] = (char*)malloc(sizeof(char) * 1024);
	f_constantupwhere[0] = (char*)malloc(sizeof(char) * 1024);

	::sprintf(f_constantupfield[0], "amt");
	::sprintf(f_constantupvalue[0], "%f", f_FloatBalance);
	::sprintf(f_constantupwhere[0], "owner = '%s'", GetAdr().c_str());

	g_SafeL[0]->Update("employee", (const char**)f_constantupfield, (const char**)f_constantupvalue, 1, f_constantupwhere[0], true, false);

	free(f_constantupvalue[0]);
	free(f_constantupfield[0]);
	free(f_constantupwhere[0]);
}

double Wallet::GetBalanceCPS(bool f_InDollars, int f_UI)
{
	m_Bank_ecoin_constant = 0.0f;

	for(int f_I = 0; f_I < 1/*m_vec_Key.size()*/; f_I++)
		{
		char* f_balquery = ag_ClearChar(150);
		::sprintf(f_balquery, "SELECT id, amt FROM employee WHERE owner = '%s'", m_vec_Key[f_I]->m_owner.c_str());
		g_SafeL[f_UI]->acSelectCommand(f_balquery, true, false);
		delete f_balquery;

		int f_BalCount = 0;
		
		if(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
			{
			f_BalCount = 0;
			}
		else
			{
			f_BalCount = g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->size();
			}

		if(f_BalCount > 0)
			{
			g_EmployeeID = atoi(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[0].c_str());
			m_Bank_ecoin_constant += atof(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[1].c_str());
			}
#if 0
		else
			{
			StartCPS();
			}
#endif
		}

	return m_Bank_ecoin_constant;
}

double Wallet::GetEValue(int f_UI)
{
	float f_Circulationamt = 0.0f;

	char* f_coinquery = ag_ClearChar(256);
	::sprintf(f_coinquery, "SELECT price, tx, unit, visits FROM coin WHERE id = 1");
	g_SafeL[f_UI]->acSelectCommand(f_coinquery, true, false);
	delete f_coinquery;

	int f_CoinCount = 0;
		
	if(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
		{
		f_CoinCount = 0;
		}
	else
		{
		f_CoinCount = g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->size();
		}

	if(f_CoinCount > 0)
		{
		int f_Visits = atoi(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[3].c_str());
		f_Visits++;

		g_EVALUE = atof(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[0].c_str());
		m_Unit = atof(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[2].c_str());
		m_TX = atof(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[1].c_str());
		m_Price = g_EVALUE;

		char* f_visitupvalue[1];
		char* f_visitupfield[1];
		char* f_visitupwhere[1];

		f_visitupvalue[0] = ag_ClearChar(1024);
		f_visitupfield[0] = ag_ClearChar(1024);
		f_visitupwhere[0] = ag_ClearChar(1024);

		::sprintf(f_visitupfield[0], "visits");
		::sprintf(f_visitupvalue[0], "%i", f_Visits);
		::sprintf(f_visitupwhere[0], "assetofficeid = %i", 3);

		g_SafeL[f_UI]->Update("coin", (const char **)f_visitupfield, (const char **)f_visitupvalue, 1, (const char*)f_visitupwhere[0], true, false);

		delete f_visitupvalue[0];
		delete f_visitupfield[0];
		delete f_visitupwhere[0];

		int f_CalcVisitsf = f_Visits % 75;

		if(f_CalcVisitsf == 75)
			{
			m_RefreshEValueLVL = 1;
			}
		else
			{
			m_RefreshEValueLVL = 0;
			}
		}
	else
		{
		m_RefreshEValueLVL = 1;
		}

	if(m_RefreshEValueLVL > 0)
		{
		char* f_circulationquery = ag_ClearChar(150);
		::sprintf(f_circulationquery, "SELECT amt FROM address WHERE amt > 0.0");
		g_SafeL[f_UI]->acSelectCommand_GlobalStorageWealth(f_circulationquery);
		delete f_circulationquery;

		int f_TotalEcoinAreas = atoi(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[2].c_str());

		f_Circulationamt += atof(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[0].c_str());;
		m_Circulationamt = f_Circulationamt;

		if(m_Circulationamt == 0)
			{
			m_Circulationamt += 50;
			}

		char* f_coinquery2 = ag_ClearChar(150);
		::sprintf(f_coinquery2, "SELECT price, tx, unit FROM coin WHERE assetofficeid = %i", 3);
		g_SafeL[f_UI]->acSelectCommand(f_coinquery2, true, true);
		delete f_coinquery2;

		int f_eleCount = 0;
		
		if(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
			{
			f_eleCount = 0;
			}
		else
			{
			f_eleCount = g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->size();
			}

		if(f_eleCount > 0)
			{
			g_EVALUE = atof(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[0].c_str());
			m_Unit = atof(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[2].c_str());
			m_TX = atof(g_Schedular[f_UI]->m_Entries[g_Schedular[f_UI]->ac_GetEntry(g_Schedular[f_UI]->m_Entries.size() - 1)]->at(0)[1].c_str());
			m_Price = g_EVALUE;

			if(g_TX < m_TX)
				{
				g_TX = m_TX;
				}
			}
		else //insert coin record - first time
			{
			char* g_syncvalue[5];
			char* g_syncfield[5];

			for(int f_s = 0; f_s < 5; f_s++)
				{
				g_syncvalue[f_s] = (char*)malloc(sizeof(char) * 256);
				g_syncfield[f_s] = (char*)malloc(sizeof(char) * 256);
				}

			::sprintf(g_syncfield[0], "assetofficeid");
			::sprintf(g_syncfield[1], "price");
			::sprintf(g_syncfield[2], "tx");
			::sprintf(g_syncfield[3], "unit");
			::sprintf(g_syncfield[4], "visits");

			::sprintf(g_syncvalue[0], "%i", 3);
			::sprintf(g_syncvalue[1], "%f", 1.0f);
			::sprintf(g_syncvalue[2], "%f", 5.09f);
			::sprintf(g_syncvalue[3], "%f", 5.09f);
			::sprintf(g_syncvalue[4], "%i", 1);

			int f_SyncUniqueID = g_SafeL[f_UI]->Insert("coin", (const char **)g_syncfield, (const char **)g_syncvalue, 5, true, false);

			for(int f_s = 0; f_s < 5; f_s++)
				{
				free(g_syncvalue[f_s]);
				free(g_syncfield[f_s]);
				}

			g_EVALUE = 0.0f;
			m_Unit = 5.09f;
			m_TX = 5.09f;
			m_Price = g_EVALUE;
			}

		  //////////////
		 //START COIN//
		//
		/*if(g_EVALUE <= 0.0f)
			{
			float f_StorageWealth = 50.0f;
			m_TX = 5.09;
			m_Price = (f_StorageWealth + m_TX) / f_Circulationamt;
			g_EVALUE = m_Price;
			}*/

		//Coin GunPrice Increase Range
		g_EVALUE = 15.0f / 500.0f;

		float f_Days_Active_Average = 120;
		float f_timeSpan = f_Days_Active_Average;

		//Calc TX over time within acceptable
		m_TX = f_Circulationamt / f_timeSpan;
		g_TX = m_TX;
		//When coin TX high ratio select tx.amt over datetime instead

		   ////////////////////
		  // Equation
		 // Storage Wealth
		// Value/Worth
		m_Price = (g_EVALUE * m_TX);
		g_EVALUE = m_Price;

		char* f_coinupvalue[3];
		char* f_coinupfield[3];
		char* f_coinupwhere[1];

		f_coinupvalue[0] = (char*)malloc(sizeof(char) * 1024);
		f_coinupfield[0] = (char*)malloc(sizeof(char) * 1024);
		f_coinupvalue[1] = (char*)malloc(sizeof(char) * 1024);
		f_coinupfield[1] = (char*)malloc(sizeof(char) * 1024);
		f_coinupvalue[2] = (char*)malloc(sizeof(char) * 1024);
		f_coinupfield[2] = (char*)malloc(sizeof(char) * 1024);
		f_coinupwhere[0] = (char*)malloc(sizeof(char) * 1024);

		::sprintf(f_coinupfield[0], "price");
		::sprintf(f_coinupfield[1], "tx");
		::sprintf(f_coinupfield[2], "unit");
		::sprintf(f_coinupvalue[0], "%f", m_Price);
		::sprintf(f_coinupvalue[1], "%f", m_TX);
		::sprintf(f_coinupvalue[2], "%f", m_Unit);
		::sprintf(f_coinupwhere[0], "assetofficeid = %i", 3);

		g_SafeL[f_UI]->Update("coin", (const char **)f_coinupfield, (const char **)f_coinupvalue, 3, f_coinupwhere[0], true, false);

		free(f_coinupvalue[0]);
		free(f_coinupfield[0]);
		free(f_coinupvalue[1]);
		free(f_coinupfield[1]);
		free(f_coinupvalue[2]);
		free(f_coinupfield[2]);
		free(f_coinupwhere[0]);
		}

	return m_Price;
}

std::shared_ptr<CKey> Wallet::GetNextChangeKey(void)
{
	std::shared_ptr<CKey> f_Key = m_vec_Key[1];

	int f_counter = m_ChangeIdx;

	m_ChangeIdx++;

	for(int f_helly = 1; f_helly < m_vec_Key.size(); f_helly++)
		{
		if(m_vec_Key[f_helly]->m_prefix == 2)
			{
			f_counter--;
			}

		if(f_counter < 0)
			{
			f_Key = m_vec_Key[f_helly];
			}
		}

	return f_Key;
}

bool Wallet::acFindChangeAdr(std::string f_Adr)
{
	for(int f_helly = 0; f_helly < m_vec_Key.size(); f_helly++)
		{
		if(m_vec_Key[f_helly]->m_prefix == 2)
			{
			if(m_vec_Key[f_helly]->m_owner.compare(f_Adr) == 0)
				{
				return true;
				}
			}
		}

	return false;
}

std::string Wallet::GetAdr(void)
{
	return m_vec_Key[0]->m_owner;
}

std::shared_ptr<CKey> ag_GenerateAddress(int f_Prefix)
{
	std::string f_ref_CurrentPath = "ag_GenerateAddress";

		///////////////
	   // Research
	  // Entropy
	 // Key
	// Privacy
	while(true)
		{
		std::string f_Address;
		f_Address.clear();

		ag_StatusLive(f_ref_CurrentPath, "key");
		std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>(f_Prefix);

		key->MakeNewKey(true);

		CPubKey pubkey = key->GetPubKey();
		bool f_keypass = key->VerifyPubKey(pubkey);

		std::vector<unsigned char, secure_allocator<unsigned char> > keydata;
		keydata.clear();
		for(int f_Jet = 0; f_Jet < 32; f_Jet++)
			{
			keydata.push_back(pubkey.vch[f_Jet]);
			}

		char *f_Char = new char[64];
		int i;
		for(i = 0; i < 32; i++)
			{
			::sprintf((char*)f_Char + (i * 2), "%02x", keydata[i]);
			}

		key->m_pubkey = f_Char;
		delete[] f_Char;

		//Bitcoin Serialized PubKey s(%i): %s\n", 64, f_Char);

		uint256 hash;
		CHash256().Write(&keydata[0], 32).Finalize(hash.begin());

		uint160 hash4;
		CHash160().Write(hash.begin(), 32).Finalize(hash4.begin());

#if 0
		//Bitcoin Serialized ripem(sha256()) PubKey s(%i): %s\n", 40, hash4.GetHex().c_str());
#endif

		std::vector<unsigned char> f_vec_UnsignedChar5;

		unsigned char *f_p5 = new unsigned char[20];

		Cube::ag_hex2bin(f_p5, hash4.GetHex().c_str(), hash4.GetHex().size());

		for(int f_lm5 = 0; f_lm5 < 20; f_lm5++)
			{
			f_vec_UnsignedChar5.push_back(f_p5[f_lm5]);
			}

		f_Address = ((std::string)EncodeBase58((const std::vector<unsigned char> &)f_vec_UnsignedChar5)).c_str();

		//GenerateAddress - f_Address);
		char* g_addrvalue[4];
		char* fg_addrfield[4];

		g_addrvalue[0] = (char*)malloc(sizeof(char) * 256);
		g_addrvalue[1] = (char*)malloc(sizeof(char) * 256);
		g_addrvalue[2] = (char*)malloc(sizeof(char) * 256);
		g_addrvalue[3] = (char*)malloc(sizeof(char) * 256);

		fg_addrfield[0] = (char*)malloc(sizeof(char) * 256);
		fg_addrfield[1] = (char*)malloc(sizeof(char) * 256);
		fg_addrfield[2] = (char*)malloc(sizeof(char) * 256);
		fg_addrfield[3] = (char*)malloc(sizeof(char) * 256);

		::sprintf(g_addrvalue[0], "%i", 1);
		::sprintf(g_addrvalue[1], "%i", 3);
		::sprintf(g_addrvalue[2], "%s", f_Address.c_str());
		::sprintf(g_addrvalue[3], "%f", 0.0f);

		::sprintf(fg_addrfield[0], "assetid");
		::sprintf(fg_addrfield[1], "assetofficeid");
		::sprintf(fg_addrfield[2], "owner");
		::sprintf(fg_addrfield[3], "amt");

		char* adrquery = ag_ClearChar(1000);
		::sprintf(adrquery, "SELECT id FROM address WHERE owner = '%s'", f_Address.c_str());
		g_SafeL[0]->acSelectCommand(adrquery, false, false);
		delete adrquery;

		int f_AdrLCount = 0;
		
		if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
			{
			f_AdrLCount = 0;
			}
		else
			{
			f_AdrLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
			}

		printf("ECN::Stat::: f_AdrLCount %i\n", f_AdrLCount);

		//assume remote connection for windows
		if(f_AdrLCount == 0)
			{
			int f_AddressUniqueID = g_SafeL[0]->Insert("address", (const char **)fg_addrfield, (const char **)g_addrvalue, 4, false, false);

			free(g_addrvalue[0]);
			free(g_addrvalue[1]);
			free(g_addrvalue[2]);
			free(g_addrvalue[3]);

			free(fg_addrfield[0]);
			free(fg_addrfield[1]);
			free(fg_addrfield[2]);
			free(fg_addrfield[3]);

			//Unique Payment Address Found Addresses - f_AddressUniqueID
			key->m_owner = f_Address;

			return key;
			}
		}
}

void Wallet::acPullHash(int f_NibCount)
{
	if(f_NibCount >= ECOIN_TX_BLOCK_NIB_COUNT) //win conditions nib count complete
		{
		if(m_current_IDX < m_vec_jobid.size())
			{
			char* txnibquery = ag_ClearChar(1000);
			::sprintf(txnibquery, "SELECT id, jobledger FROM share WHERE id = IFNULL(SELECT MAX(dated) FROM share WHERE (jobid = %i AND status = 1 AND confirmation = 6 AND jobledger != 'G'), 0) LIMIT 1", m_vec_jobid[m_current_IDX]);
			g_SafeL[0]->acSelectCommand(txnibquery, 2, false);
			delete txnibquery;

			int f_TxNibLCount = 0;
		
			if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
				{
				f_TxNibLCount = 0;
				}
			else
				{
				f_TxNibLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
				}

			if(f_TxNibLCount == 1)
				{
				if(m_current_IDX < m_vec_blockledger.size())
					{
					m_vec_blockledger[m_current_IDX] = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[1];
					}
				else
					{
					m_vec_blockledger.push_back(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[1]);
					}

				g_JobID = acSet_JobID(m_current_IDX, 1);
				}
			}
		}
}

void Wallet::acTestForBlock(int f_BlockType, std::shared_ptr<Cube::CubeResults> f_Results, bool f_SureBlock)
{
	std::string f_ref_CurrentPath = g_ref_global_start + "SecondaryAppWindowPageDX::acTestForBlock";

	switch(f_BlockType)
		{
		case ecoin_BlockType::ecoin_Block_Target_TypeName: //also called default block inputadd
			{
			if(f_SureBlock == true)
				{
				acPullHash(f_Results->m_HashNibCount);

				char* f_BlockQuery = ag_ClearChar(255);
				::sprintf(f_BlockQuery, "UPDATE quantumangel_cubex.address SET address.amt = address.amt + %f WHERE owner = '%s'", m_Reward, GetAdr().c_str());
				g_SafeL[0]->UpdateQuery(f_BlockQuery);
				delete f_BlockQuery;

				char* g_blockvalue[25];

				for(int f_Count = 0; f_Count < 25; f_Count++)
					{
					g_blockvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(g_blockvalue[0], "%i", m_vec_mark[m_current_IDX]);
				sprintf(g_blockvalue[1], "%i", 0);
				sprintf(g_blockvalue[2], "%i", 3);
				sprintf(g_blockvalue[3], "%i", m_vec_jobid[m_current_IDX]);
				sprintf(g_blockvalue[4], "%i", m_vec_eslid[m_current_IDX]);
				sprintf(g_blockvalue[5], "%i", m_vec_targetid[m_current_IDX]);
				sprintf(g_blockvalue[6], "%i", g_ShareID);
				sprintf(g_blockvalue[7], "%s", g_TypeName.c_str());
				sprintf(g_blockvalue[8], "%f", m_vec_difficulty[m_current_IDX]);
				sprintf(g_blockvalue[9], "%i", m_vec_score[m_current_IDX]);
				sprintf(g_blockvalue[10], "%i", m_vec_maxvote[m_current_IDX]);
				sprintf(g_blockvalue[11], "%s", m_vec_blockledger[m_current_IDX].c_str());
				sprintf(g_blockvalue[12], "%s", GetAdr().c_str());
				sprintf(g_blockvalue[13], "%i", 0);
				sprintf(g_blockvalue[14], "%f", m_vec_bckred[m_current_IDX]);
				sprintf(g_blockvalue[15], "%f", m_vec_bckgreen[m_current_IDX]);
				sprintf(g_blockvalue[16], "%f", m_vec_bckblue[m_current_IDX]);
				sprintf(g_blockvalue[17], "%f", m_Reward);
				sprintf(g_blockvalue[18], "%f", m_my_EGBP_pledge);
				sprintf(g_blockvalue[19], "%f", m_my_ECN_pledge);
				sprintf(g_blockvalue[20], "%f", ECN_TX_FEE);
				sprintf(g_blockvalue[21], "%f", m_vec_price[m_current_IDX]);
				sprintf(g_blockvalue[22], "%i", ecoin_BlockType::ecoin_Block_Target_TypeName);
				sprintf(g_blockvalue[23], "%i", m_vec_timebreach[m_current_IDX]);

				char* BlockDUPEquery = ag_ClearChar(1000);
				sprintf(BlockDUPEquery, "SELECT id FROM block WHERE blockledger = '%s'", m_vec_blockledger[m_current_IDX].c_str());
				g_SafeL[0]->acSelectCommand(BlockDUPEquery, false, false);
				delete BlockDUPEquery;

				int f_BlockDuplicationCount = 0;
		
				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
					{
					f_BlockDuplicationCount = 0;
					}
				else
					{
					f_BlockDuplicationCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
					}

				//ECN::Stat::: f_BlockDuplicationCount
				if(f_BlockDuplicationCount == 0)
					{
					int f_BlockUniqueID = g_SafeL[0]->Insert("block", (const char **)g_blockfield, (const char **)g_blockvalue, 24, false, false);

					for(int f_Count = 0; f_Count < 22; f_Count++)
						{
						free(g_blockvalue[f_Count]);
						}

					ag_StatusLive(f_ref_CurrentPath, "f_Ack");
					std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(ACK_TYPE::ACK_TYPE_BLOCK, g_ShareID, g_PEERCNT);
					f_Ack->m_ECN = 50.0f;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = GetAdr();
					g_Ackent.push_back(f_Ack);

					g_PEERCNT = 0;
					g_SHARECNT = 0;

#if 0
					ag_makeGenesisCoin();
#endif
					}
				else
					{
					for(int f_Count = 0; f_Count < 25; f_Count++)
						{
						free(g_blockvalue[f_Count]);
						}

					g_Found_Msg = 10;
					g_Found_Text = "Block Miss -Duplicate BlockLedger and -Duplicate Share";
					}
				}
			}break;

		case ecoin_BlockType::ecoin_Block_Target_VoteDriven:
			{
			if(f_SureBlock == true)
				{
				acPullHash(f_Results->m_HashNibCount);

				char* g_blockvalue[25];

				for(int f_Count = 0; f_Count < 25; f_Count++)
					{
					g_blockvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(g_blockvalue[0], "%i", m_vec_mark[m_current_IDX]);
				sprintf(g_blockvalue[1], "%i", 0);
				sprintf(g_blockvalue[2], "%i", 3);
				sprintf(g_blockvalue[3], "%i", m_vec_jobid[m_current_IDX]);
				sprintf(g_blockvalue[4], "%i", m_vec_eslid[m_current_IDX]);
				sprintf(g_blockvalue[5], "%i", m_vec_targetid[m_current_IDX]);
				sprintf(g_blockvalue[6], "%i", g_ShareID);
				sprintf(g_blockvalue[7], "%s", g_TypeName.c_str());
				sprintf(g_blockvalue[8], "%f", m_vec_difficulty[m_current_IDX]);
				sprintf(g_blockvalue[9], "%i", m_vec_score[m_current_IDX]);
				sprintf(g_blockvalue[10], "%i", m_vec_maxvote[m_current_IDX]);
				sprintf(g_blockvalue[11], "%s", m_vec_blockledger[m_current_IDX].c_str());
				sprintf(g_blockvalue[12], "%s", GetAdr().c_str());
				sprintf(g_blockvalue[13], "%i", 0);
				sprintf(g_blockvalue[14], "%f", m_vec_bckred[m_current_IDX]);
				sprintf(g_blockvalue[15], "%f", m_vec_bckgreen[m_current_IDX]);
				sprintf(g_blockvalue[16], "%f", m_vec_bckblue[m_current_IDX]);
				sprintf(g_blockvalue[17], "%f", m_Reward);
				sprintf(g_blockvalue[18], "%f", m_my_EGBP_pledge);
				sprintf(g_blockvalue[19], "%f", m_my_ECN_pledge);
				sprintf(g_blockvalue[20], "%f", ECN_TX_FEE);
				sprintf(g_blockvalue[21], "%f", m_vec_price[m_current_IDX]);
				sprintf(g_blockvalue[22], "%i", ecoin_BlockType::ecoin_Block_Target_VoteDriven);
				sprintf(g_blockvalue[23], "%i", m_vec_timebreach[m_current_IDX]);

				char* BlockDUPEquery = ag_ClearChar(1000);
				sprintf(BlockDUPEquery, "SELECT id FROM block WHERE blockledger = '%s'", m_vec_blockledger[m_current_IDX].c_str());
				g_SafeL[0]->acSelectCommand(BlockDUPEquery, false, false);
				delete BlockDUPEquery;

				int f_BlockDuplicationCount = 0;
		
				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
					{
					f_BlockDuplicationCount = 0;
					}
				else
					{
					f_BlockDuplicationCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
					}

				//ECN::Stat::: f_BlockDuplicationCount
				if(f_BlockDuplicationCount == 0)
					{
					int f_BlockUniqueID = g_SafeL[0]->Insert("block", (const char **)g_blockfield, (const char **)g_blockvalue, 24, false, false);

					for(int f_Count = 0; f_Count < 25; f_Count++)
						{
						free(g_blockvalue[f_Count]);
						}

					ag_StatusLive(f_ref_CurrentPath, "f_Ack");
					std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(ACK_TYPE::ACK_TYPE_BLOCK, g_ShareID, g_PEERCNT);
					f_Ack->m_ECN = 50.0f;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = GetAdr();
					g_Ackent.push_back(f_Ack);

					g_PEERCNT = 0;
					g_SHARECNT = 0;

					ag_makeGenesisCoin();
					}
				else
					{
					for(int f_Count = 0; f_Count < 25; f_Count++)
						{
						free(g_blockvalue[f_Count]);
						}

					g_Found_Msg = 10;
					g_Found_Text = "Block Miss -Duplicate BlockLedger and -Duplicate Share";
					}
				}
			}break;

		case ecoin_BlockType::ecoin_Block_Target_TimedVote:
			{
			time_t f_SingleTime;

			time(&f_SingleTime);

			if((f_SingleTime >= m_vec_timebreach[m_current_IDX]) && (f_SureBlock == true))
				{
				acPullHash(f_Results->m_HashNibCount);

				char* g_blockvalue[25];

				for(int f_Count = 0; f_Count < 25; f_Count++)
					{
					g_blockvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(g_blockvalue[0], "%i", m_vec_mark[m_current_IDX]);
				sprintf(g_blockvalue[1], "%i", 0);
				sprintf(g_blockvalue[2], "%i", 3);
				sprintf(g_blockvalue[3], "%i", m_vec_jobid[m_current_IDX]);
				sprintf(g_blockvalue[4], "%i", m_vec_eslid[m_current_IDX]);
				sprintf(g_blockvalue[5], "%i", m_vec_targetid[m_current_IDX]);
				sprintf(g_blockvalue[6], "%i", g_ShareID);
				sprintf(g_blockvalue[7], "%s", g_TypeName.c_str());
				sprintf(g_blockvalue[8], "%f", m_vec_difficulty[m_current_IDX]);
				sprintf(g_blockvalue[9], "%i", m_vec_score[m_current_IDX]);
				sprintf(g_blockvalue[10], "%i", m_vec_maxvote[m_current_IDX]);
				sprintf(g_blockvalue[11], "%s", m_vec_blockledger[m_current_IDX].c_str());
				sprintf(g_blockvalue[12], "%s", GetAdr().c_str());
				sprintf(g_blockvalue[13], "%i", 0);
				sprintf(g_blockvalue[14], "%f", m_vec_bckred[m_current_IDX]);
				sprintf(g_blockvalue[15], "%f", m_vec_bckgreen[m_current_IDX]);
				sprintf(g_blockvalue[16], "%f", m_vec_bckblue[m_current_IDX]);
				sprintf(g_blockvalue[17], "%f", m_Reward);
				sprintf(g_blockvalue[18], "%f", m_my_EGBP_pledge);
				sprintf(g_blockvalue[19], "%f", m_my_ECN_pledge);
				sprintf(g_blockvalue[20], "%f", ECN_TX_FEE);
				sprintf(g_blockvalue[21], "%f", m_vec_price[m_current_IDX]);
				sprintf(g_blockvalue[22], "%i", ecoin_BlockType::ecoin_Block_Target_TimedVote);
				sprintf(g_blockvalue[23], "%i", m_vec_timebreach[m_current_IDX]);

				char* BlockDUPEquery = ag_ClearChar(1000);
				sprintf(BlockDUPEquery, "SELECT id FROM block WHERE blockledger = '%s'", m_vec_blockledger[m_current_IDX].c_str());
				g_SafeL[0]->acSelectCommand(BlockDUPEquery, false, false);
				delete BlockDUPEquery;

				int f_BlockDuplicationCount = 0;
		
				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
					{
					f_BlockDuplicationCount = 0;
					}
				else
					{
					f_BlockDuplicationCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
					}

				//ECN::Stat::: f_BlockDuplicationCount
				if(f_BlockDuplicationCount == 0)
					{
					int f_BlockUniqueID = g_SafeL[0]->Insert("block", (const char **)g_blockfield, (const char **)g_blockvalue, 24, false, false);

					for(int f_Count = 0; f_Count < 25; f_Count++)
						{
						free(g_blockvalue[f_Count]);
						}

					ag_StatusLive(f_ref_CurrentPath, "f_Ack");
					std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(ACK_TYPE::ACK_TYPE_BLOCK, g_ShareID, g_PEERCNT);
					f_Ack->m_ECN = 50.0f;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = GetAdr();
					g_Ackent.push_back(f_Ack);

					g_PEERCNT = 0;
					g_SHARECNT = 0;

					ag_makeGenesisCoin();
					}
				else
					{
					for(int f_Count = 0; f_Count < 25; f_Count++)
						{
						free(g_blockvalue[f_Count]);
						}

					g_Found_Msg = 10;
					g_Found_Text = "Block Miss -Duplicate BlockLedger and -Duplicate Share";
					}
				}
			}break;

		case ecoin_BlockType::ecoin_Block_Target_SCP:
			{
			if(f_SureBlock == true)
				{
				acPullHash(f_Results->m_HashNibCount);

				char* g_blockvalue[23];

				for(int f_Count = 0; f_Count < 25; f_Count++)
					{
					g_blockvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(g_blockvalue[0], "%i", m_vec_mark[m_current_IDX]);
				sprintf(g_blockvalue[1], "%i", 0);
				sprintf(g_blockvalue[2], "%i", 3);
				sprintf(g_blockvalue[3], "%i", m_vec_jobid[m_current_IDX]);
				sprintf(g_blockvalue[4], "%i", m_vec_eslid[m_current_IDX]);
				sprintf(g_blockvalue[5], "%i", m_vec_targetid[m_current_IDX]);
				sprintf(g_blockvalue[6], "%i", g_ShareID);
				sprintf(g_blockvalue[7], "%s", g_TypeName.c_str());
				sprintf(g_blockvalue[8], "%f", m_vec_difficulty[m_current_IDX]);
				sprintf(g_blockvalue[9], "%i", m_vec_score[m_current_IDX]);
				sprintf(g_blockvalue[10], "%i", m_vec_maxvote[m_current_IDX]);
				sprintf(g_blockvalue[11], "%s", m_vec_blockledger[m_current_IDX].c_str());
				sprintf(g_blockvalue[12], "%s", GetAdr().c_str());
				sprintf(g_blockvalue[13], "%i", 0);
				sprintf(g_blockvalue[14], "%f", m_vec_bckred[m_current_IDX]);
				sprintf(g_blockvalue[15], "%f", m_vec_bckgreen[m_current_IDX]);
				sprintf(g_blockvalue[16], "%f", m_vec_bckblue[m_current_IDX]);
				sprintf(g_blockvalue[17], "%f", m_Reward);
				sprintf(g_blockvalue[18], "%f", m_my_EGBP_pledge);
				sprintf(g_blockvalue[19], "%f", m_my_ECN_pledge);
				sprintf(g_blockvalue[20], "%f", ECN_TX_FEE);
				sprintf(g_blockvalue[21], "%f", m_vec_price[m_current_IDX]);
				sprintf(g_blockvalue[22], "%i", ecoin_BlockType::ecoin_Block_Target_SCP);
				sprintf(g_blockvalue[23], "%i", m_vec_timebreach[m_current_IDX]);

				char* BlockDUPEquery = ag_ClearChar(1000);
				sprintf(BlockDUPEquery, "SELECT id FROM block WHERE blockledger = '%s'", m_vec_blockledger[m_current_IDX].c_str());
				g_SafeL[0]->acSelectCommand(BlockDUPEquery, false, false);
				delete BlockDUPEquery;

				int f_BlockDuplicationCount = 0;
		
				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
					{
					f_BlockDuplicationCount = 0;
					}
				else
					{
					f_BlockDuplicationCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
					}

				//ECN::Stat::: f_BlockDuplicationCount
				if(f_BlockDuplicationCount == 0)
					{
					int f_BlockUniqueID = g_SafeL[0]->Insert("block", (const char **)g_blockfield, (const char **)g_blockvalue, 24, false, false);

					for(int f_Count = 0; f_Count < 25; f_Count++)
						{
						free(g_blockvalue[f_Count]);
						}

					ag_StatusLive(f_ref_CurrentPath, "f_Ack");
					std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(ACK_TYPE::ACK_TYPE_BLOCK, g_ShareID, g_PEERCNT);
					f_Ack->m_ECN = 50.0f;
					f_Ack->m_Origin = 1;
					f_Ack->m_Owner = GetAdr();
					g_Ackent.push_back(f_Ack);

					g_PEERCNT = 0;
					g_SHARECNT = 0;

					ag_makeGenesisCoin();
					}
				else
					{
					for(int f_Count = 0; f_Count < 25; f_Count++)
						{
						free(g_blockvalue[f_Count]);
						}

					g_Found_Msg = 10;
					g_Found_Text = "Block Miss -Duplicate BlockLedger and -Duplicate Share";
					}
				}
			}break;

		case ecoin_BlockType::ecoin_Block_TimedPledge:
			{
			time_t f_SingleTime;

			time(&f_SingleTime);

			if((f_SingleTime >= m_vec_timebreach[m_current_IDX]) && (f_SureBlock == true))
				{
				acPullHash(f_Results->m_HashNibCount);

				int f_ShareVote = m_pledge_Total;

				char* f_GSharequery2 = ag_ClearChar(255);
				::sprintf(f_GSharequery2, "SELECT SUM(access * (pledge + (ecnpledge * %f))) FROM reference WHERE blockid = %i AND blocktype = %i", m_Price, g_JobID);
				g_SafeL[0]->acSelectCommand(f_GSharequery2, false, false);
				delete f_GSharequery2;

				int f_GShareCount = 0;

				if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
					{
					f_GShareCount = 0;
					}
				else
					{
					f_GShareCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
					}

				if(f_GShareCount == 1)
					{
					float f_SummationPledge = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].c_str());

					if(f_SummationPledge > 270.0f)
						{
						char* f_GSharequery3= ag_ClearChar(150);
						sprintf(f_GSharequery3, "SELECT mark, assetid, assetofficeid, jobid, eslid, targetid, eslcode, difficulty, score, maxvote, shareledger, jobledger, owner, bckred, bckgreen, bckblue, pledge FROM share WHERE id = %i", g_ShareID);
						g_SafeL[0]->acSelectCommand(f_GSharequery3, false, false);
						delete f_GSharequery3;

						int f_GShareCount2 = 0;
		
						if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
							{
							f_GShareCount2 = 0;
							}
						else
							{
							f_GShareCount2 = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
							}

						//copy entrant board
						std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)];

						if(f_GShareCount2 == 1)
							{
							acPullHash(f_Results->m_HashNibCount);

							char* g_blockvalue[25];

							for(int f_Count = 0; f_Count < 25; f_Count++)
								{
								g_blockvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
								}

							sprintf(g_blockvalue[0], "%i", atoi(f_Entry->at(0)[0].c_str()));
							sprintf(g_blockvalue[1], "%i", 0);
							sprintf(g_blockvalue[2], "%i", 3);
							sprintf(g_blockvalue[3], "%i", m_vec_jobid[m_current_IDX]);
							sprintf(g_blockvalue[4], "%i", atoi(f_Entry->at(0)[4].c_str()));
							sprintf(g_blockvalue[5], "%i", atoi(f_Entry->at(0)[5].c_str()));
							sprintf(g_blockvalue[6], "%i", g_ShareID);
							sprintf(g_blockvalue[7], "%s", "eslcode");
							sprintf(g_blockvalue[8], "%f", atof(f_Entry->at(0)[7].c_str()));
							sprintf(g_blockvalue[9], "%i", atoi(f_Entry->at(0)[8].c_str()));
							sprintf(g_blockvalue[10], "%i", atoi(f_Entry->at(0)[9].c_str()));
							sprintf(g_blockvalue[11], "%s", m_vec_blockledger[m_current_IDX].c_str());
							sprintf(g_blockvalue[12], "%s", GetAdr().c_str());
							sprintf(g_blockvalue[13], "%i", 0);
							sprintf(g_blockvalue[14], "%f", atof(f_Entry->at(0)[13].c_str()));
							sprintf(g_blockvalue[15], "%f", atof(f_Entry->at(0)[14].c_str()));
							sprintf(g_blockvalue[16], "%f", atof(f_Entry->at(0)[15].c_str()));
							sprintf(g_blockvalue[17], "%f", m_Reward);
							sprintf(g_blockvalue[18], "%f", m_my_EGBP_pledge);
							sprintf(g_blockvalue[19], "%f", m_my_ECN_pledge);
							sprintf(g_blockvalue[20], "%f", ECN_TX_FEE);
							sprintf(g_blockvalue[21], "%f", 0.1f);
							sprintf(g_blockvalue[22], "%i", ecoin_BlockType::ecoin_Block_TimedPledge);
							sprintf(g_blockvalue[23], "%i", m_vec_timebreach[m_current_IDX]);

							char* BlockDUPEquery = ag_ClearChar(1000);
							sprintf(BlockDUPEquery, "SELECT id FROM block WHERE blockledger = '%s'", g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 2)]->at(0)[11].c_str());
							g_SafeL[0]->acSelectCommand(BlockDUPEquery, false, false);
							delete BlockDUPEquery;

							int f_BlockDuplicationCount = 0;
		
							if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
								{
								f_BlockDuplicationCount = 0;
								}
							else
								{
								f_BlockDuplicationCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
								}

							//ECN::Stat::: f_BlockDuplicationCount
							if(f_BlockDuplicationCount == 0)
								{
								int f_BlockUniqueID = g_SafeL[0]->Insert("block", (const char **)g_blockfield, (const char **)g_blockvalue, 24, false, false);

								for(int f_Count = 0; f_Count < 25; f_Count++)
									{
									free(g_blockvalue[f_Count]);
									}

								ag_StatusLive(f_ref_CurrentPath, "f_Ack");
								std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(ACK_TYPE::ACK_TYPE_BLOCK, g_ShareID, g_PEERCNT);
								f_Ack->m_ECN = 50.0f;
								f_Ack->m_Origin = 1;
								f_Ack->m_Owner = GetAdr();
								g_Ackent.push_back(f_Ack);

								g_PEERCNT = 0;
								g_SHARECNT = 0;

								ag_makeGenesisCoin();

								acPay_preference(-1, -1.0, 0);
								}
							else
								{
								for(int f_Count = 0; f_Count < 25; f_Count++)
									{
									::free(g_blockvalue[f_Count]);
									}

								g_Found_Msg = 10;
								g_Found_Text = "Block Miss -Duplicate BlockLedger and -Duplicate Share";
								}
							}
						else
							{
							char* f_CharOP = ag_ClearChar(64);

							::sprintf(f_CharOP, "%i", g_ShareID);

							std::string f_Number = f_CharOP;

							delete f_CharOP;

							g_Found_Msg = 10;
							g_Found_Text = "Vote UP -ShareID(" + f_Number + ")...";
							}
						}
					}
				}
			}break;

		case ecoin_BlockType::ecoin_Block_MaxPledge:
			{
			int f_BlockID = 0;

			int f_shrscrCount = 0;
		
			int f_ShareVote = m_pledge_Total;

			char* f_GSharequery2 = ag_ClearChar(512);
			::sprintf(f_GSharequery2, "SELECT SUM(access * (pledge + (ecnpledge * %f))) FROM reference WHERE blockid = %i", m_Price, g_JobID);
			g_SafeL[0]->acSelectCommand(f_GSharequery2, false, false);
			delete f_GSharequery2;

			int f_GShareCount = 0;

			if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
				{
				f_GShareCount = 0;
				}
			else
				{
				f_GShareCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
				}

			if(f_GShareCount == 1)
				{
				float f_SummationPledge = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].c_str());

				if(f_SummationPledge > 270.0f)
					{
					char* f_GSharequery3 = ag_ClearChar(150);
					::sprintf(f_GSharequery3, "SELECT mark, assetid, assetofficeid, jobid, eslid, targetid, eslcode, difficulty, score, maxvote, shareledger, jobledger, owner, bckred, bckgreen, bckblue, pledge FROM share WHERE id = %i", g_ShareID);
					g_SafeL[0]->acSelectCommand(f_GSharequery3, false, false);
					delete f_GSharequery3;

					int f_GShareCount4 = 0;
		
					if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
						{
						f_GShareCount4 = 0;
						}
					else
						{
						f_GShareCount4 = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
						}

					//copy entrant board
					std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)];

					if(f_GShareCount4 == 1)
						{
						acPullHash(f_Results->m_HashNibCount);

						char* g_blockvalue[23];

						for(int f_Count = 0; f_Count < 23; f_Count++)
							{
							g_blockvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
							}

						::sprintf(g_blockvalue[0], "%i", atoi(f_Entry->at(0)[0].c_str()));
						::sprintf(g_blockvalue[1], "%i", 0);
						::sprintf(g_blockvalue[2], "%i", 3);
						::sprintf(g_blockvalue[3], "%i", m_vec_jobid[m_current_IDX]);
						::sprintf(g_blockvalue[4], "%i", atoi(f_Entry->at(0)[4].c_str()));
						::sprintf(g_blockvalue[5], "%i", atoi(f_Entry->at(0)[5].c_str()));
						::sprintf(g_blockvalue[6], "%i", g_ShareID);
						::sprintf(g_blockvalue[7], "%s", "eslcode");
						::sprintf(g_blockvalue[8], "%f", atof(f_Entry->at(0)[7].c_str()));
						::sprintf(g_blockvalue[9], "%i", atoi(f_Entry->at(0)[8].c_str()));
						::sprintf(g_blockvalue[10], "%i", atoi(f_Entry->at(0)[9].c_str()));
						::sprintf(g_blockvalue[11], "%s", m_vec_blockledger[m_current_IDX].c_str());
						::sprintf(g_blockvalue[12], "%s", GetAdr().c_str());
						::sprintf(g_blockvalue[13], "%i", 0);
						::sprintf(g_blockvalue[14], "%f", atof(f_Entry->at(0)[13].c_str()));
						::sprintf(g_blockvalue[15], "%f", atof(f_Entry->at(0)[14].c_str()));
						::sprintf(g_blockvalue[16], "%f", atof(f_Entry->at(0)[15].c_str()));
						::sprintf(g_blockvalue[17], "%f", m_Reward);
						::sprintf(g_blockvalue[18], "%f", m_my_EGBP_pledge);
						::sprintf(g_blockvalue[19], "%f", m_my_ECN_pledge);
						::sprintf(g_blockvalue[20], "%f", ECN_TX_FEE);
						::sprintf(g_blockvalue[21], "%f", 0.1f);
						::sprintf(g_blockvalue[22], "%i", ecoin_BlockType::ecoin_Block_MaxPledge);
						::sprintf(g_blockvalue[23], "%i", m_vec_timebreach[m_current_IDX]);

						char* BlockDUPEquery = ag_ClearChar(1000);
						sprintf(BlockDUPEquery, "SELECT id FROM block WHERE blockledger = '%s'", g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 2)]->at(0)[11].c_str());
						g_SafeL[0]->acSelectCommand(BlockDUPEquery, false, false);
						delete BlockDUPEquery;

						int f_BlockDuplicationCount = 0;
		
						if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
							{
							f_BlockDuplicationCount = 0;
							}
						else
							{
							f_BlockDuplicationCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)]->size();
							}

						//ECN::Stat::: f_BlockDuplicationCount
						if(f_BlockDuplicationCount == 0)
							{
							int f_BlockUniqueID = g_SafeL[0]->Insert("block", (const char **)g_blockfield, (const char **)g_blockvalue, 24, false, false);

							f_BlockID = f_BlockUniqueID;

							for(int f_Count = 0; f_Count < 25; f_Count++)
								{
								free(g_blockvalue[f_Count]);
								}

							ag_StatusLive(f_ref_CurrentPath, "f_Ack");
							std::shared_ptr<Ackent> f_Ack = std::make_shared_reflect<Ackent>(ACK_TYPE::ACK_TYPE_BLOCK, g_ShareID, g_PEERCNT);
							f_Ack->m_ECN = 50.0f;
							f_Ack->m_Origin = 1;
							f_Ack->m_Owner = GetAdr();
							g_Ackent.push_back(f_Ack);

							g_PEERCNT = 0;
							g_SHARECNT = 0;

							ag_makeGenesisCoin();

							acPay_preference(-1, -1.0, ecoin_Preferences::ecoin_Pref_MaxPledge);
							}
						else
							{
							for(int f_Count = 0; f_Count < 25; f_Count++)
								{
								free(g_blockvalue[f_Count]);
								}

							g_Found_Msg = 10;
							g_Found_Text = "Block Miss -Duplicate BlockLedger and -Duplicate Share";

							f_BlockID = 0;
							}
						}
					else
						{
						char* f_CharOP = ag_ClearChar(64);

						::sprintf(f_CharOP, "%i", g_ShareID);

						std::string f_Number = f_CharOP;

						delete f_CharOP;

						g_Found_Msg = 10;
						g_Found_Text = "Vote UP -ShareID(" + f_Number + ")...";
						}
					}
				}
			}break;
		}
}

void Wallet::acSet_IDX(int f_IDX)
{
	m_current_IDX = f_IDX;
}

void Wallet::acSave_currentJob(void)
{
	if(m_vec_jobboardid[m_current_IDX] > 0) //update current owners job
		{
#if 0
		char* g_jobvalue[14];
		char* f_ownerwhere[1];

		for(int f_Jet = 0; f_Jet < 14; f_Jet++)
			{
			g_jobvalue[f_Jet] = (char*)malloc(sizeof(char) * 1024);
			}

		f_ownerwhere[0] = (char*)malloc(sizeof(char) * 1024);

		::sprintf(g_jobvalue[0], "%i", 3);
		::sprintf(g_jobvalue[1], "%i", m_vec_targetid[m_current_IDX]);
		::sprintf(g_jobvalue[2], "%i", m_vec_blocktype[m_current_IDX]);
		::sprintf(g_jobvalue[3], "%s", m_vec_eslcode[m_current_IDX].c_str());
		::sprintf(g_jobvalue[4], "%i", m_vec_pledgetype[m_current_IDX]);
		::sprintf(g_jobvalue[5], "%i", m_vec_maxpledge[m_current_IDX]);
		::sprintf(g_jobvalue[6], "%i", m_vec_targetbreach[m_current_IDX]);

#if 0
		time_t f_CurrentTime;
		time(&f_CurrentTime);

		::sprintf(g_jobvalue[7], "%i", f_CurrentTime);
#endif

		::sprintf(g_jobvalue[8], "%s", m_vec_owner[m_current_IDX].c_str());
		::sprintf(g_jobvalue[9], "%i", m_vec_scoremax[m_current_IDX]);
		::sprintf(g_jobvalue[10], "%f", m_vec_markmax[m_current_IDX]);
		::sprintf(g_jobvalue[11], "%f", m_vec_markmin[m_current_IDX]);
		::sprintf(g_jobvalue[12], "%f", m_Reward);
		::sprintf(g_jobvalue[13], "%i", m_RewardID);

		::sprintf(f_ownerwhere[0], "id = %i", m_vec_jobboardid[m_current_IDX]);

#if 0
		g_SafeL[0]->Update("job", (const char**)g_jobvalue, (const char**)g_jobfield, 14, f_ownerwhere[0], true, false);
#else
		g_SafeL[0]->Update("job", (const char**)g_jobvalue, (const char**)g_jobfield, 13, f_ownerwhere[0], true, false);
#endif

		for(int f_Jet = 0; f_Jet < 14; f_Jet++)
			{
			free(g_jobvalue[f_Jet]);
			}

		free(f_ownerwhere[0]);

		for(int f_Jet = 0; f_Jet < m_vec_jobvar_index[m_current_IDX].size(); f_Jet++)
			{
			int f_Index = m_vec_jobvar_index[m_current_IDX][f_Jet];

			if(m_vec_jobvar_save[m_current_IDX][f_Index] == true)
				{
				acSave_currentJobVar(f_Index, m_vec_jobboardid[m_current_IDX]);

				m_vec_jobvar_save[m_current_IDX][f_Jet] = false;
				m_vec_jobvar_textupdate[m_current_IDX][f_Jet] = false;
				}
			}
#endif
		}
	else
		{
		char* g_blockvalue[24];

		for(int f_Count = 0; f_Count < 24; f_Count++)
			{
			g_blockvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(g_blockvalue[0], "%i", 0);
		sprintf(g_blockvalue[1], "%i", 0);
		sprintf(g_blockvalue[2], "%i", 3);
		sprintf(g_blockvalue[3], "%i", m_vec_jobid[m_current_IDX]);
		sprintf(g_blockvalue[4], "%i", m_vec_eslid[m_current_IDX]);
		sprintf(g_blockvalue[5], "%i", m_vec_targetid[m_current_IDX]);
		sprintf(g_blockvalue[6], "%i", 0); //SET ON BLOCK FOUND
		sprintf(g_blockvalue[7], "%s", "BLKTYPENAME");
		sprintf(g_blockvalue[8], "%f", 0.0f);
		sprintf(g_blockvalue[9], "%i", 0);
		sprintf(g_blockvalue[10], "%i", 10);
		sprintf(g_blockvalue[11], "%s", m_vec_blockledger[m_current_IDX].c_str());
		sprintf(g_blockvalue[12], "%s", "BLKOWNER");
		sprintf(g_blockvalue[13], "%i", 0);
		sprintf(g_blockvalue[14], "%f", 0.5f);
		sprintf(g_blockvalue[15], "%f", 0.4f);
		sprintf(g_blockvalue[16], "%f", 0.97f);
		sprintf(g_blockvalue[17], "%f", m_Reward);
		sprintf(g_blockvalue[18], "%f", 0.0f);
		sprintf(g_blockvalue[19], "%f", 0.0f);
		sprintf(g_blockvalue[20], "%f", ECN_TX_FEE);
		sprintf(g_blockvalue[21], "%f", 0.0f);
		sprintf(g_blockvalue[22], "%i", m_vec_blocktype[m_current_IDX]);
		sprintf(g_blockvalue[23], "%i", 0);

		m_vec_blockid[m_current_IDX] = g_SafeL[0]->Insert("block", (const char **)g_blockfield, (const char **)g_blockvalue, 24, false, false);

		for(int f_Count = 0; f_Count < 24; f_Count++)
			{
			free(g_blockvalue[f_Count]);
			}

		char* g_jobvalue[15];

		for(int f_Count = 0; f_Count < 15; f_Count++)
			{
			g_jobvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		::sprintf(g_jobvalue[0], "%i", 3);
		::sprintf(g_jobvalue[1], "%i", m_vec_targetid[m_current_IDX]);
		::sprintf(g_jobvalue[2], "%i", m_vec_blockid[m_current_IDX]);
		::sprintf(g_jobvalue[3], "%i", m_vec_blocktype[m_current_IDX]);
		::sprintf(g_jobvalue[4], "%s", m_vec_eslcode[m_current_IDX].c_str());
		::sprintf(g_jobvalue[5], "%i", m_vec_pledgetype[m_current_IDX]);
		::sprintf(g_jobvalue[6], "%i", m_vec_maxpledge[m_current_IDX]);
		::sprintf(g_jobvalue[7], "%i", m_vec_targetbreach[m_current_IDX]);

		time_t f_CurrentTime;
		time(&f_CurrentTime);

		::sprintf(g_jobvalue[8], "%i", f_CurrentTime);
		::sprintf(g_jobvalue[9], "%s", m_vec_owner[m_current_IDX].c_str());
		::sprintf(g_jobvalue[10], "%i", m_vec_scoremax[m_current_IDX]);
		::sprintf(g_jobvalue[11], "%f", m_vec_markmax[m_current_IDX]);
		::sprintf(g_jobvalue[12], "%f", m_vec_markmin[m_current_IDX]);
		::sprintf(g_jobvalue[13], "%f", m_Reward);
		::sprintf(g_jobvalue[14], "%i", m_RewardID);

		m_vec_jobboardid[m_current_IDX] = g_SafeL[0]->Insert("job", (const char **)g_jobfield, (const char **)g_jobvalue, 15, false, false);

		for(int f_Count = 0; f_Count < 15; f_Count++)
			{
			free(g_jobvalue[f_Count]);
			}

		for(int f_Jet = 0; f_Jet < m_vec_jobvar_index[m_current_IDX].size(); f_Jet++)
			{
			int f_Index = m_vec_jobvar_index[m_current_IDX][f_Jet];

			acSave_currentJobVar(f_Index, m_vec_jobboardid[m_current_IDX]);

			m_vec_jobvar_save[m_current_IDX][f_Jet] = false;
			m_vec_jobvar_textupdate[m_current_IDX][f_Jet] = false;
			}
		}
}

void Wallet::acSave_currentJobVar(int f_Index, int f_JobIndex)
{
	if(m_vec_jobvarid[m_current_IDX][f_Index] > 0)
		{
		char* g_jobvarvalue[4];
		char* f_ownerwhere[1];

		for(int f_Jet = 0; f_Jet < 4; f_Jet++)
			{
			g_jobvarvalue[f_Jet] = (char*)malloc(sizeof(char) * 1024);
			}

		f_ownerwhere[0] = (char*)malloc(sizeof(char) * 1024);

		::sprintf(g_jobvarvalue[0], "%i", f_JobIndex);
		::sprintf(g_jobvarvalue[1], "%s", m_vec_jobvar_name[m_current_IDX][f_Index].c_str());
		::sprintf(g_jobvarvalue[2], "%s", m_vec_jobvar_groupname[m_current_IDX][f_Index].c_str());
		::sprintf(g_jobvarvalue[3], "%f", m_vec_jobvar_value[m_current_IDX][f_Index]);

		::sprintf(f_ownerwhere[0], "id = %i", m_vec_jobvarid[m_current_IDX][f_Index]);

		g_SafeL[0]->Update("jobvar", (const char**)g_jobvarvalue, (const char**)g_jobfield, 4, f_ownerwhere[0], true, false);

		for(int f_Jet = 0; f_Jet < 4; f_Jet++)
			{
			free(g_jobvarvalue[f_Jet]);
			}

		free(f_ownerwhere[0]);
		}
	else
		{
		char* g_jobvarvalue[4];

		for(int f_Count = 0; f_Count < 4; f_Count++)
			{
			g_jobvarvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		::sprintf(g_jobvarvalue[0], "%i", f_JobIndex);
		::sprintf(g_jobvarvalue[1], "%s", m_vec_jobvar_name[m_current_IDX][f_Index].c_str());
		::sprintf(g_jobvarvalue[2], "%s", m_vec_jobvar_groupname[m_current_IDX][f_Index].c_str());
		::sprintf(g_jobvarvalue[3], "%f", m_vec_jobvar_value[m_current_IDX][f_Index]);

		int f_JobUniqueID = g_SafeL[0]->Insert("jobvar", (const char **)g_jobvarfield, (const char **)g_jobvarvalue, 4, false, false);

		for(int f_Count = 0; f_Count < 4; f_Count++)
			{
			free(g_jobvarvalue[f_Count]);
			}
		}
}

void Wallet::acSave_currentBlock(void)
{
	if(m_vec_blockid[m_current_IDX] > 0) //update current owners job
		{
#if 0
		char* g_jobvalue[14];
		char* f_ownerwhere[1];

		for(int f_Jet = 0; f_Jet < 14; f_Jet++)
			{
			g_jobvalue[f_Jet] = (char*)malloc(sizeof(char) * 1024);
			}

		f_ownerwhere[0] = (char*)malloc(sizeof(char) * 1024);

		::sprintf(g_jobvalue[0], "%i", 3);
		::sprintf(g_jobvalue[1], "%i", m_vec_targetid[m_current_IDX]);
		::sprintf(g_jobvalue[2], "%i", m_vec_blocktype[m_current_IDX]);
		::sprintf(g_jobvalue[3], "%s", m_vec_eslcode[m_current_IDX].c_str());
		::sprintf(g_jobvalue[4], "%i", m_vec_pledgetype[m_current_IDX]);
		::sprintf(g_jobvalue[5], "%i", m_vec_maxpledge[m_current_IDX]);
		::sprintf(g_jobvalue[6], "%i", m_vec_targetbreach[m_current_IDX]);

#if 0
		time_t f_CurrentTime;
		time(&f_CurrentTime);

		::sprintf(g_jobvalue[7], "%i", f_CurrentTime);
#endif

		::sprintf(g_jobvalue[8], "%s", m_vec_owner[m_current_IDX].c_str());
		::sprintf(g_jobvalue[9], "%i", m_vec_scoremax[m_current_IDX]);
		::sprintf(g_jobvalue[10], "%f", m_vec_markmax[m_current_IDX]);
		::sprintf(g_jobvalue[11], "%f", m_vec_markmin[m_current_IDX]);
		::sprintf(g_jobvalue[12], "%f", m_Reward);
		::sprintf(g_jobvalue[13], "%i", m_RewardID);

		::sprintf(f_ownerwhere[0], "id = %i", m_vec_jobboardid[m_current_IDX]);

#if 0
		g_SafeL[0]->Update("job", (const char**)g_jobvalue, (const char**)g_jobfield, 14, f_ownerwhere[0], true, false);
#else
		g_SafeL[0]->Update("job", (const char**)g_jobvalue, (const char**)g_jobfield, 13, f_ownerwhere[0], true, false);
#endif

		for(int f_Jet = 0; f_Jet < 14; f_Jet++)
			{
			free(g_jobvalue[f_Jet]);
			}

		free(f_ownerwhere[0]);

		for(int f_Jet = 0; f_Jet < m_vec_jobvar_index[m_current_IDX].size(); f_Jet++)
			{
			int f_Index = m_vec_jobvar_index[m_current_IDX][f_Jet];

			if(m_vec_jobvar_save[m_current_IDX][f_Index] == true)
				{
				acSave_currentJobVar(f_Index, m_vec_jobboardid[m_current_IDX]);

				m_vec_jobvar_save[m_current_IDX][f_Jet] = false;
				m_vec_jobvar_textupdate[m_current_IDX][f_Jet] = false;
				}
			}
#endif
		}
	else
		{
		char* g_blockvalue[24];

		for(int f_Count = 0; f_Count < 24; f_Count++)
			{
			g_blockvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(g_blockvalue[0], "%i", 0);
		sprintf(g_blockvalue[3], "%i", m_vec_jobid[m_current_IDX]);
		sprintf(g_blockvalue[6], "%i", g_ShareID);
		sprintf(g_blockvalue[7], "%s", g_TypeName.c_str());
		sprintf(g_blockvalue[8], "%f", m_vec_difficulty[m_current_IDX]);
		sprintf(g_blockvalue[9], "%i", m_vec_score[m_current_IDX]);
		sprintf(g_blockvalue[10], "%i", 10);
		sprintf(g_blockvalue[11], "%s", m_vec_blockledger[m_current_IDX].c_str());
		sprintf(g_blockvalue[12], "%s", g_Wallet->GetAdr().c_str());
		//sprintf(g_blockvalue[13], "%i", 0); share count required?
		sprintf(g_blockvalue[14], "%f", m_vec_bckred[m_current_IDX]);
		sprintf(g_blockvalue[15], "%f", m_vec_bckgreen[m_current_IDX]);
		sprintf(g_blockvalue[16], "%f", m_vec_bckblue[m_current_IDX]);
		sprintf(g_blockvalue[17], "%f", m_Reward);
		sprintf(g_blockvalue[18], "%f", 0.0f);
		sprintf(g_blockvalue[19], "%f", 0.0f);
		sprintf(g_blockvalue[20], "%f", ECN_TX_FEE);
		sprintf(g_blockvalue[21], "%f", m_vec_price[m_current_IDX]);
		sprintf(g_blockvalue[22], "%i", m_vec_blocktype[m_current_IDX]);

		time_t f_CurrentTime;
		time(&f_CurrentTime);

		sprintf(g_blockvalue[23], "%i", f_CurrentTime);

		m_vec_blockid[m_current_IDX] = g_SafeL[0]->Insert("block", (const char **)g_blockfield, (const char **)g_blockvalue, 24, false, false);

		for(int f_Count = 0; f_Count < 24; f_Count++)
			{
			free(g_blockvalue[f_Count]);
			}

		char* g_jobvalue[15];

		for(int f_Count = 0; f_Count < 15; f_Count++)
			{
			g_jobvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		::sprintf(g_jobvalue[0], "%i", 3);
		::sprintf(g_jobvalue[1], "%i", m_vec_targetid[m_current_IDX]);
		::sprintf(g_jobvalue[2], "%i", m_vec_blockid[m_current_IDX]);
		::sprintf(g_jobvalue[3], "%i", m_vec_blocktype[m_current_IDX]);
		::sprintf(g_jobvalue[4], "%s", m_vec_eslcode[m_current_IDX].c_str());
		::sprintf(g_jobvalue[5], "%i", m_vec_pledgetype[m_current_IDX]);
		::sprintf(g_jobvalue[6], "%i", m_vec_maxpledge[m_current_IDX]);
		::sprintf(g_jobvalue[7], "%i", m_vec_targetbreach[m_current_IDX]);

		time_t f_CurrentTime;
		time(&f_CurrentTime);

		::sprintf(g_jobvalue[8], "%i", f_CurrentTime);
		::sprintf(g_jobvalue[9], "%s", m_vec_owner[m_current_IDX].c_str());
		::sprintf(g_jobvalue[10], "%i", m_vec_scoremax[m_current_IDX]);
		::sprintf(g_jobvalue[11], "%f", m_vec_markmax[m_current_IDX]);
		::sprintf(g_jobvalue[12], "%f", m_vec_markmin[m_current_IDX]);
		::sprintf(g_jobvalue[13], "%f", m_Reward);
		::sprintf(g_jobvalue[14], "%i", m_RewardID);

		m_vec_jobboardid[m_current_IDX] = g_SafeL[0]->Insert("job", (const char **)g_jobfield, (const char **)g_jobvalue, 15, false, false);

		for(int f_Count = 0; f_Count < 15; f_Count++)
			{
			free(g_jobvalue[f_Count]);
			}

		for(int f_Jet = 0; f_Jet < m_vec_jobvar_index[m_current_IDX].size(); f_Jet++)
			{
			int f_Index = m_vec_jobvar_index[m_current_IDX][f_Jet];

			acSave_currentJobVar(f_Index, m_vec_jobboardid[m_current_IDX]);

			m_vec_jobvar_save[m_current_IDX][f_Jet] = false;
			m_vec_jobvar_textupdate[m_current_IDX][f_Jet] = false;
			}
		}
}

float Wallet::acSelect_JobVar(int f_IDX, std::string f_JobString)
{
	if(f_IDX < g_Wallet->m_vec_jobvar_name.size())
		{
		for(int f_Jet = 0; f_Jet < g_Wallet->m_vec_jobvar_name[f_IDX].size(); f_Jet++)
			{
			if(f_JobString.compare(g_Wallet->m_vec_jobvar_name[f_IDX][f_Jet]) == 0)
				{
				return g_Wallet->m_vec_jobvar_value[f_IDX][f_Jet];
				}
			}
		}

	return 0.0f;
}

int Wallet::acGet_JobID(int f_IDX, int f_Layer)
{
	char* blokquery = ag_ClearChar(1000);

	::sprintf(blokquery, "SELECT id, jobid, blockledger, dated FROM block WHERE jobid = (SELECT MAX(jobid) FROM block) ORDER BY dated DESC LIMIT 1");

	g_SafeL[f_Layer]->acSelectCommand(blokquery, 2, false);

	delete blokquery;

	int f_blokLCount = 0;

	if(g_Schedular[f_Layer]->m_Entries[g_Schedular[f_Layer]->ac_GetEntry(g_Schedular[f_Layer]->m_Entries.size() - 1)]->at(0)[0].at(0) == '0')
		{
		f_blokLCount = 0;
		}
	else
		{
		f_blokLCount = g_Schedular[f_Layer]->m_Entries[g_Schedular[f_Layer]->ac_GetEntry(g_Schedular[f_Layer]->m_Entries.size() - 1)]->size();
		}

	if(f_blokLCount > 0)
		{
		if(f_IDX < m_vec_prevblock.size())
			{
			m_vec_jobid[f_IDX] = (atoi(g_Schedular[f_Layer]->m_Entries[g_Schedular[f_Layer]->ac_GetEntry(g_Schedular[f_Layer]->m_Entries.size() - 1)]->at(0)[1].c_str())) + 1;
			m_vec_prevblock[f_IDX] = g_Schedular[f_Layer]->m_Entries[g_Schedular[f_Layer]->ac_GetEntry(g_Schedular[f_Layer]->m_Entries.size() - 1)]->at(0)[2];
			}
		else
			{
			m_vec_jobid.push_back((atoi(g_Schedular[f_Layer]->m_Entries[g_Schedular[f_Layer]->ac_GetEntry(g_Schedular[f_Layer]->m_Entries.size() - 1)]->at(0)[1].c_str())) + 1);
			m_vec_prevblock.push_back(g_Schedular[f_Layer]->m_Entries[g_Schedular[f_Layer]->ac_GetEntry(g_Schedular[f_Layer]->m_Entries.size() - 1)]->at(0)[2]);
			}

		return m_vec_jobid[f_IDX];
		}
	else
		{
		if(f_IDX < m_vec_prevblock.size())
			{
			m_vec_jobid[f_IDX] = 0;
			m_vec_prevblock[f_IDX] = "0000000000000000000000000000000000000000000000000000000000000001";
			}
		else
			{
			m_vec_jobid.push_back(0);
			m_vec_prevblock.push_back("0000000000000000000000000000000000000000000000000000000000000001");
			}

		return 0;
		}

	return 0;
}

int Wallet::acSet_JobID(int f_IDX, int f_Increment)
{
	if(f_IDX < m_vec_jobid.size())
		{
		m_vec_jobid[f_IDX] += f_Increment;

		return m_vec_jobid[f_IDX];
		}
	else
		{
		m_vec_jobid.push_back(g_JobID + f_Increment);

		return m_vec_jobid[f_IDX];
		}
}

};