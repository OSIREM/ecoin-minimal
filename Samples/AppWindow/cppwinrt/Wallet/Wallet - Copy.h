/*

Wallet.h - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef WALLET_H
#define WALLET_H

#include "ecoinShop.h"
#include "picosha2.h"
#include "key.h"

#include "Code/Work/Schedular.h"
#include "Code/Cube/qcom.h"

namespace ecoin
{
	enum ecoin_BlockType
	{								  //when how where block activated
		ecoin_Block_Target_TypeName,  //test each target pass			     CCCX
		ecoin_Block_Target_VoteDriven,//L//when target pass check for block  CCCX
		ecoin_Block_Target_TimedVote, //democratic ECN reward when target pass check for block CCCX
		ecoin_Block_Target_SCP,		  //CCCX
		ecoin_Block_TimedPledge,	  //CCCX
		ecoin_Block_MaxPledge,		  //CCCX
		ecoin_Block_MaxTimedPledge,	  //CCCX
		ecoin_Block_MAX
	};

	enum ecoin_Preferences
	{
		ecoin_Pref_TypeNameBlock,
		ecoin_Pref_VoteDriven,
		ecoin_Pref_TimedPledge,
		ecoin_Pref_MaxPledge,
		ecoin_Pref_ShareCom,
		ecoin_Pref_MAX
	};

extern bool g_WalletOpen;
extern int g_EmployeeID;
extern double g_WALLETBANK;
extern double g_StoreWALLETBANK;
extern double g_EVALUE;
extern double g_ECOINPERSECOND;
extern int g_HESHSAVEID;

class CubeCKey : public ecom_base
{
public:
	CubeCKey()
		{
		m_str_Address.clear();
		}
	CubeCKey(CKey f_CKey)
		{
		m_str_Address.clear();
		m_Key = f_CKey;
		}
	~CubeCKey()
		{
		m_str_Address.clear();
		}

	CKey m_Key;
	CPubKey m_PubKey;
	std::string m_str_Address;
};

class Wallet : public ecom_base
	{
	public:
		Wallet();
		~Wallet();

		std::future<bool> Open(void);

		std::string Prepare(void);
		std::string Prepare_Start(void);

		void StartCPS(void);

		double GetBalance(bool f_InDollars, int f_UI = false);
		double GetBalanceCPS(bool f_InDollars, int f_UI = false);
		void SetBalanceCPS(float f_FloatBalance);

		std::string GetAdr(void);

		bool acFindChangeAdr(std::string f_Adr);

		bool acGet_assetContractbyID(float f_CostAmt, int f_ComID);
		bool acGet_assetContractbyID(int f_ShareID, float f_CostAmt, int f_ComID = -1);
		float acGet_assetContractbyID(int f_ShareID, int f_ComID = -1);

		bool acBuy_ShareComID(int f_ComID, float f_PayAmt, float f_CostAmt, int f_ShareID = -1);
		int acSet_ConstantBalance(std::string f_owner, float f_AmtDiff);

		void acPay_preference(int f_ShareID, float f_Amt, int f_TypeID = 0);
		void acExec_preference_PayBlock(void);
		void acExec_preference_PayShare_Package(void);

		void acTestForBlock(int f_BlockType, std::shared_ptr<Cube::CubeResults> f_Results, bool f_SureBlock = false);

		void acPushKey(std::shared_ptr<CKey> f_Key)
			{
			m_vec_Key.push_back(f_Key);

			Update();
			}

		int acGetKeySize(void)
			{
			return (int)m_vec_Key.size();
			}

		bool acGetKey(std::string f_Owner, std::shared_ptr<CKey> f_Key)
			{
			bool f_Found = false;
			int f_Index = 0;
			for(int f_Helly = 0; f_Helly < m_vec_Key.size(); f_Helly++)
				{
				if(m_vec_Key[f_Helly]->m_owner.size() >= 27)
					{
					if(m_vec_Key[f_Helly]->m_owner.compare(f_Owner) == 0)
						{
						f_Found = true;
						f_Index = f_Helly;
						}
					}
				}

			if(f_Found)
				{
				f_Key = m_vec_Key[f_Index];
				return true;
				}
			else
				{
				return false;
				}
			}

		std::shared_ptr<CKey> acGetKey(int f_Index)
			{
			return m_vec_Key[f_Index];
			}

		std::shared_ptr<CKey> GetNextChangeKey(void);

		double GetEValue(int f_UI = 0);

		std::future<void> Update(void);

		void acSet_IDX(int f_IDX);

		int acGet_JobID(int f_IDX, int f_Layer = 0);
		int acSet_JobID(int f_IDX, int f_Increment);

		void acPullHash(int f_NibCount);

		void acSave_currentJob(void);
		void acSave_currentJobVar(int f_Index, int f_JobIndex);

		float acSelect_JobVar(int f_IDX, std::string f_JobString);

		void acSave_currentBlock(void);

		 ////////
		// OK
		bool m_OK;
		bool m_Start;
		int m_Count;
		bool m_CountYNG;
		int m_HeshCount;
		int m_HeshRCount;
		bool m_Repeat;
		int m_ChangeIdx;
		int m_RefreshLVL;
		int m_RefreshCNT;
		int m_RefreshEValueLVL;
		double m_Bank_ecoin_constant;
		float m_my_EGBP_pledge;
		float m_my_ECN_pledge;
		bool m_my_Active_pledge;
		int m_my_pledge_shareID;
		int m_pledge_Total;
		int m_current_IDX;

		std::vector<int> m_vec_mark;
		std::vector<int> m_vec_eslid;
		std::vector<int> m_vec_targetid;
		std::vector<int> m_vec_blockid;
		std::vector<float> m_vec_difficulty;
		std::vector<int> m_vec_score;
		std::vector<int> m_vec_maxvote;
		std::vector<int> m_vec_jobboardid;
		std::vector<int> m_vec_blocktype;
		std::vector<int> m_vec_timebreach;
		std::vector<std::string> m_vec_blockledger;
		std::vector<float> m_vec_bckred;
		std::vector<float> m_vec_bckgreen;
		std::vector<float> m_vec_bckblue;
		std::vector<float> m_vec_price;
		std::vector<std::string> m_vec_eslcode;
		std::vector<std::string> m_vec_owner;
		std::vector<int> m_vec_pledgetype;
		std::vector<int> m_vec_maxpledge;
		std::vector<int> m_vec_targetbreach;
		std::vector<int> m_vec_startbreach;
		std::vector<int> m_vec_scoremax;
		std::vector<float> m_vec_markmax;
		std::vector<float> m_vec_markmin;
		std::vector<int> m_vec_jobid;
		std::vector<std::string> m_vec_prevblock;
		std::vector<std::vector<float>> m_vec_jobvar_value;
		std::vector<std::vector<std::string>> m_vec_jobvar_groupname;
		std::vector<std::vector<std::string>> m_vec_jobvar_name;
		std::vector<std::vector<int>> m_vec_jobvar_index;
		std::vector<std::vector<int>> m_vec_jobvarid;
		std::vector<std::vector<bool>> m_vec_jobvar_save;
		std::vector<std::vector<bool>> m_vec_jobvar_textupdate;
		std::vector<int> m_vec_jobvar_current_index;

	public:
		double m_Bank_ecoin;
		std::string m_Bank_Adr;
		std::vector<std::shared_ptr<CKey>> m_vec_Key;
		float m_Price;
		float m_Unit;
		float m_TX;
		float m_Circulationamt;
		float m_Reward;
		int m_RewardID;
		std::shared_ptr<ECCVerifyHandle> m_CTX;
	};

extern std::shared_ptr<Wallet> g_Wallet;

extern std::string ag_Key_Serialize(std::shared_ptr<CKey> f_key);

extern std::shared_ptr<CKey> ag_GenerateAddress(int f_Prefix);

extern float g_TX;
extern float g_BossLVLMin;

};

#endif