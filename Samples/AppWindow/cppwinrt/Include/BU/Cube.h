/*

Cube.h - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#pragma once

#include <vector>
#include <string>

#ifdef JNI
#include <dxgi1_4.h>
#include <d3d11_3.h>
#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <dwrite_3.h>
#include "DeviceResources.h"
#include "ShaderStructures.h"
#else
#include "Common/DeviceResources.h"
#include "Content/ShaderStructures.h"
#endif

#include "Code\Musion\Code.h"
#include "Code\Musion\CodeLine.h"
#include "Code\Musion\Function.h"
#include "Code\Musion\MuType.h"
#include "Code\Musion\Operator.h"
#include "Code\Musion\System.h"
#include "Code\Musion\Variable.h"

#include <iostream>
#include <vector>
#include "math.h"

#include "key.h"

namespace ecoin
{
	class Contract;
}

#define PI 3.14159265

#define uint unsigned int

#if 1
#define ECOIN_ADMAX_MAX 1
#endif

#if 1
#define ECOIN_SECURE 1
#endif

#if 0
#define ECOIN_SAFE 1
#endif

#if 0
#define ECOIN_SCP_RECORD_FLOAT 1
#endif

#if 1
#define ECOIN_QCOM_UPDATE_FROM_HESH 1
#endif

#if 1
#define ECOIN_STORE_SIM 1
#endif

#if	0
#define ECOIN_PRE_RELEASE 1
#endif

#if 1
#define ECOIN_FULL_VERSION 1
#endif

///////////////
/// Globals ///
///////////////

extern char* g_heshfield[60];
extern char* g_cubefield[60];
extern char* g_adifield[60];
extern char* g_blockfield[60];
extern char* g_sharefield[60];
extern char* g_transfield[60];
extern char* g_addrfield[60];
extern char* g_eventfield[60];
extern char* g_reffield[60];
extern char* g_chancefield[60];
extern char* g_txinsyncfield[60];
extern char* g_txoutsyncfield[60];

extern int g_HeshFieldCount;
extern int g_CubeFieldCount;
extern int g_ShareFieldCount;
extern int g_BlockFieldCount;
extern int g_TransFieldCount;

extern time_t  g_Currtime;
extern time_t  g_Storetime;
extern time_t  g_CurrtimeSEC;
extern time_t  g_StoretimeSEC;
extern time_t  g_CurrentTime;
extern time_t  g_StorageTime;
extern time_t  g_currenttime;
extern time_t  g_storagetime;
extern time_t  g_txdCurrtime;
extern time_t  g_txdStoretime;
extern time_t  g_txdCurrtimeSEC;
extern time_t  g_txdStoretimeSEC;
extern int g_StorageCounter;
extern int g_timeDiff;
extern int g_timeActual;
extern int g_timeCnt;
extern int g_timeCntLast;
extern winrt::hstring g_timetext;
extern ULONGLONG g_TimeStamp;
extern float g_RADX;
extern float g_RADY;
extern float g_RADZ;

extern bool g_Hold;

extern std::vector<int> g_vec_Cube;

extern ULONGLONG g_TimeStamp;

extern bool g_HeshFull;
extern int g_Timer;
extern int g_ID;
extern bool g_FlipRefreshMiner;

extern char* g_AppLog;
extern std::string g_KHash;
extern std::string g_AddtoOut;

extern int g_nomHesh;

extern std::vector<int> g_vec_Bookmark;

extern float g_Add;

extern std::string g_FilePath;

extern int g_JobID;

extern int g_ADMAX;
extern int g_ADHIGH;
extern int g_ADLOW;

extern std::shared_ptr<ecoin::Contract> g_Contract;
extern std::shared_ptr<ecoin::Contract> g_nonceContract;

extern float g_nonce;

extern uint g_ElementCount;
extern double g_HeshPerSecond;
extern double g_AverageSaleValue;
extern double g_EcoinDifficulty;

extern std::string g_Tab[9];

extern int g_TabSelected;

extern int g_codeON;
extern int g_codemode;
extern std::string g_codeCMD;
extern winrt::hstring g_curr_Selection;
extern int g_curr_SelectionEnd;
extern int g_curr_SelectionStart;

extern int g_codeIndex;
extern std::string g_codeStorage[4];

extern int g_Var1Type;
extern std::string g_Var1Name;
extern float g_Var1Float;
extern int g_Var1Int;

extern int g_Var2Type;
extern std::string g_Var2Name;
extern float g_Var2Float;
extern int g_Var2Int;

extern int g_OprType;
extern std::string g_OprName;

extern int g_FuncType;
extern std::string g_FuncName;

extern int g_Arg1Type;
extern std::string g_Arg1Name;
extern float g_Arg1Float;
extern int g_Arg1Int;

extern int g_Arg2Type;
extern std::string g_Arg2Name;
extern float g_Arg2Float;
extern int g_Arg2Int;

#define ESL_COMMAND_CLOSE 0
#define ESL_COMMAND_OPEN 1

#define ESL_CMDMODE_VAR 0
#define ESL_CMDMODE_OPR 1
#define ESL_CMDMODE_FUNC 2

#define ECOIN_HESH_MINIMUM 2.0f

using namespace std;

namespace Cube
{
extern bool ag_hex2bin(unsigned char *p, const char *hexstr, size_t len);
extern void ag_bin2hex(char *s, std::vector<unsigned int> p, size_t len);
extern void ag_bin2hex(char *s, std::vector<unsigned char> p, size_t len);
extern void ag_bin2hex(char *s, float p);
extern char *phex(const void *p, size_t n);

extern char* ag_ClearChar(int f_Size);

  ///////////////////////////
 // Save Complete Publish //
//
#define SCP_FLT_SCALE 1.0f
#define SCP_PREC_UPP 500.0f
#define SCP_PREC_ONE 0.11072891f
#define SCP_PREC_TEN 1.51467891f
#define SCP_PREC_LGE 33.01435412f
#define SCP_LEN_AMP 3.47198474f
#define SCP_ELM_PUSH 2.57198474f
#define SCP_ELM_ONCE 3
#define SCP_ADD_ON 2.0f

#define CUBE_TX_TYPE_ATOB 1
#define CUBE_TX_TYPE_ATOBCHANGE 2
#define CUBE_TX_TYPE_GENESIS 3
#define CUBE_TX_TYPE_GENESIS_REWARD 4
#define CUBE_TX_TYPE_GENESIS_TRADE_REWARD 5
#define CUBE_TX_TYPE_TRADE_REWARD 6

#define VERIFY_FAIL false
#define VERIFY_SUCCEEDING true

#define CUBE_COM_TYPE_RACKLEVEL 0
#define CUBE_COM_TYPE_COMPONENT 1

#define CUBE_COM_FACTORY_OSCILLATOR 0
#define CUBE_COM_FACTORY_ADSR 1
#define CUBE_COM_FACTORY_HIPASSFILTER 2
#define CUBE_COM_FACTORY_LOPASSFILTER 3
#define CUBE_COM_FACTORY_DISTORTION 4
#define CUBE_COM_FACTORY_LFO 5
#define CUBE_COM_FACTORY_COMPRESSOR 6
#define CUBE_COM_FACTORY_CHORUS 7
#define CUBE_COM_FACTORY_REVERB 8
#define CUBE_COM_FACTORY_DELAY 9
#define CUBE_COM_FACTORY_FREQUENCER 10
#define CUBE_COM_FACTORY_SEQUENCER 11
#define CUBE_COM_FACTORY_PINBOARDSEQUENCER 12
#define CUBE_COM_FACTORY_LEVEL 13
#define CUBE_COM_FACTORY_MIDIIN 14
#define CUBE_COM_FACTORY_MIDIOUT 15
#define CUBE_COM_FACTORY_FLOATIN 16
#define CUBE_COM_FACTORY_FLOATOUT 17
#define CUBE_COM_FACTORY_VOLTIN 18
#define CUBE_COM_FACTORY_VOLTOUT 19
#define CUBE_COM_FACTORY_POSTIN 20
#define CUBE_COM_FACTORY_POSTOUT 21
#define CUBE_COM_FACTORY_MIDIPATCH 22
#define CUBE_COM_FACTORY_FLOATPATCH 23
#define CUBE_COM_FACTORY_VOLTPATCH 24
#define CUBE_COM_FACTORY_POSTPATCH 25
#define CUBE_COM_FACTORY_KNOB 26
#define CUBE_COM_FACTORY_VERTSLIDER 27
#define CUBE_COM_FACTORY_HORIZSLIDER 28
#define CUBE_COM_FACTORY_BUTTON 29

#define CUBE_TRI_SHOT_A 0
#define CUBE_TRI_SHOT_B 1
#define CUBE_TRI_SHOT_C 2
#define CUBE_TRI_SHOT_TOTAL 100

#define GEN_MAX_CON 8

#define CUBE_LOG_WELD_ATTACH 0
#define CUBE_LOG_SERVED 1
#define CUBE_LOG_POSITIONED 2
#define CUBE_LOG_PUSHBACK 3
#define CUBE_LOG_PULLFORD 4
#define CUBE_LOG_GROW 5
#define CUBE_LOG_SHRINK 6
#define CUBE_LOG_TRANSLATION 7
#define CUBE_LOG_TRANSFORMATION 8

#define CUBE_PUCK_BASE 10

#define CUBE_PORT_XNEG 0
#define CUBE_PORT_XPOS 1
#define CUBE_PORT_YNEG 2
#define CUBE_PORT_YPOS 3
#define CUBE_PORT_ZNEG 4
#define CUBE_PORT_ZPOS 5

#if 0
#define CUBE_AABB_USE_COLOR
#endif

#define CUBE_RND_WARM 35000
#define CUBE_RND_TOLL 500

#define CUBE_RAND3 1

#define CUBE_HESH_SIZE 26

#if 0
#define CUBE_OPEN true
#endif

#if 0
#define CUBE_LAYER true
#endif

#define CUBEBIT_DEFAULT_MAX_INT 65535
#define CUBEBIT_DEFAULT_MIN_INT 0
#define CUBEBIT_DEFAULT_MAX_FLOAT 1.0f
#define CUBEBIT_DEFAULT_MIN_FLOAT 0.0f
#define CUBEBIT_DEFAULT_TYPE 0

#define ACE 0
#define TWO 1
#define THREE 2
#define FOUR 3
#define FIVE 4
#define SIX 5
#define SEVEN 6
#define EIGHT 7
#define NINE 8
#define TEN 9
#define JACK 10
#define QUEEN 11
#define KING 12
#define BICARD_NOMCARD 13
#define BISUIT_CLUBS 0
#define BISUIT_HEARTS 1
#define BISUIT_SPADES 2
#define BISUIT_DIAMONDS 3
#define BISUIT_NOMSUITS 4

#define VECDOM(v1,v2) ((v1).m_X*(v2).m_X+(v1).m_Y*(v2).m_Y+(v1).m_Z*(v2).m_Z)

#define EPSILON 0.000001
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2];

#define ECOIN_CLS_COM 0
#define ECOIN_CLS_INPUT 1
#define ECOIN_CLS_OUTPUT 2
#define ECOIN_CLS_WIRE 3
#define ECOIN_CLS_COM_BIRTH 4
#define ECOIN_CLS_INPUT_BIRTH 5
#define ECOIN_CLS_OUTPUT_BIRTH 6
#define ECOIN_CLS_WIRE_BIRTH 7

	extern int randomFac(void);
	extern float random(void);
	extern int g_Fingat;
	extern float g_swit;

	class CubeBicycle;
	class float3;
	class float4;
	class aabb;
	class BiVector;

	class BiColor
		{
		public:
			BiColor()
				{
				m_R = 0;
				m_G = 0;
				m_B = 0;
				m_A = 0;
				}

			BiColor(float r, float g, float b, float a)
				{
				m_R = r;
				m_G = g;
				m_B = b;
				m_A = a;
				}
			~BiColor() {};

			float m_R;
			float m_G;
			float m_B;
			float m_A;
		};

	class BiTex
		{
		public:
			BiTex()
				{
				m_U = 0;
				m_V = 0;
				}

			BiTex(float u, float v)
				{
				m_U = u;
				m_V = v;
				}
			~BiTex() {};

			float m_U;
			float m_V;
		};

	struct Carriage
		{
		float m_X;
		float m_Y;
		float m_Z;
		};

	extern Carriage agRun_visualminer(float f_X, float f_Y, float f_Z);

	class CubeKEY
		{
		public:
			CubeKEY();

			void acPush(int f_Type);
			std::shared_ptr<BiVector> acCenter(void);

			std::shared_ptr<aabb> m_aabb;
			bool m_Served;

			std::shared_ptr<CubeBicycle> m_Link;

			int nom_Child;
			int nom_Parent;

			int acFindinLog(int f_Msg);
			std::vector<unsigned int> vec_Log;

			std::vector<CubeKEY*> vec_Child;
			std::vector<CubeKEY*> vec_Parent;
		};

	class CubeTXIN
		{
		public:
			CubeTXIN()
				{
				acClear();
				}

			~CubeTXIN()
				{
				acClear();
				}

			void acClear(void)
				{
				m_txid = -1;
				m_prvtxid = -1;
				m_prvtxoutid = -1;
				m_txinid = -1;
				m_gnshareid = -1;
				m_vout.clear();
				m_pubkey.clear();
				m_sig.clear();
				m_sigstr.clear();
				}

			int m_txid;
			int m_prvtxid;
			int m_prvtxoutid;
			int m_txinid;
			int m_gnshareid;
			std::string m_vout;
			std::string m_pubkey;
			std::vector<unsigned char> m_sig;
			std::string m_sigstr;
			float m_amt;
		};

	class CubeTXOUT
		{
		public:
			CubeTXOUT()
				{
				acClear();
				}

			~CubeTXOUT()
				{
				acClear();
				}

			void acClear(void)
				{
				m_txid = -1;
				m_txoutid = -1;
				m_adrid = -1;
				m_owner.clear();
				m_pubkey.clear();
				m_txoutamt = 0.0f;
				m_owneramt = 0.0f;
				m_Flag = 0;
				}

			int m_txid;
			int m_txoutid;
			int m_adrid;
			std::string m_owner;
			std::string m_pubkey;
			float m_txoutamt;
			float m_owneramt;
			int m_Flag;
		};

	class CubeTransaction
		{
		public:
			CubeTransaction()
				{
				m_txin.clear();
				m_txout.clear();
				}
			~CubeTransaction()
				{
				m_txin.clear();
				m_txout.clear();
				}
			CubeTransaction(std::string f_A, std::string f_B, float f_amt)
				{
				//assert sizes
				m_txin.clear();
				m_txout.clear();

				CubeTXIN* f_txin = new CubeTXIN();

				f_txin->m_vout = f_A;
				m_txin.push_back(f_txin);

				CubeTXOUT* f_txout = new CubeTXOUT();

				f_txout->m_owner = f_B;
				f_txout->m_txoutamt = f_amt;
				f_txout->m_owneramt = f_amt;
				m_amt = f_amt;
				m_txout.push_back(f_txout);
				}

			void acClear(void)
				{
				m_txin.clear();
				m_txout.clear();
				m_amt = 0.0f;
				}

			bool isValid(void)
				{
				bool f_Valid = true;

				if(m_txout.size() < 1)
					{
					return f_Valid = false;
					}

				if(m_txin.size() != 1)
					{
					CubeTXIN* f_txin = new CubeTXIN();

					f_txin->m_vout = "Genesis Tracking";
					m_txin.push_back(f_txin);

					char* g_txinsyncvalue[6];

					for(int f_s1 = 0; f_s1 < 6; f_s1++)
						{
						g_txinsyncvalue[f_s1] = (char*)malloc(sizeof(char) * 256);
						}

					printf("Connected to ecoin server...\n");

					sprintf(g_txinsyncvalue[0], "%i", m_txid);
					sprintf(g_txinsyncvalue[1], "%s", f_txin->m_vout.c_str());
					sprintf(g_txinsyncvalue[2], "");
					sprintf(g_txinsyncvalue[3], "");
					sprintf(g_txinsyncvalue[4], "%f", 0.0f);
					sprintf(g_txinsyncvalue[5], "%i", 1);

					int f_TXINID = g_SafeL[0]->Insert("txin", (const char **)g_txinsyncfield, (const char **)g_txinsyncvalue, 6, false, false);
					}

				if(m_txin[0]->m_txid == -1)
					{
					f_Valid = false;
					}

				if(m_txout[0]->m_txid == -1)
					{
					f_Valid = false;
					}

				return f_Valid;
				}

			std::vector<CubeTXIN*> m_txin;
			std::vector<CubeTXOUT*> m_txout;

			void acHash(void);
			void acSynchronize(void);
			void acUpdateSync(void);

			std::string m_Hash;
			std::string m_hdid;
			std::string m_owner;

			float m_amt;
			float m_fee;
			float m_reward;

			int m_status;
			int m_type;
			int m_txid;
			int m_jobid;
			int m_rewardid;
			int m_confirmation;
			int m_locktime;

			bool m_fresh;
		};

	class CubeCollision
		{
		public:
			CubeCollision()
				{
				m_BicycleIndex = 0;
				m_SideIndex = 0;
				}

			~CubeCollision()
				{
				m_BicycleIndex = 0;
				m_SideIndex = 0;
				}

			CubeCollision(int f_B, int f_S)
				{
				m_BicycleIndex = f_B;
				m_SideIndex = f_S;
				}

			int m_BicycleIndex;
			int m_SideIndex;
		};

	class CubeHASH_originstring
		{
		public:
			CubeHASH_originstring() { acClear(); };
			~CubeHASH_originstring() { acClear(); };

			void acClear()
				{
				m_str_Input.clear();
				m_OutputHash.clear();
				}

			void acPushInt(int f_Int)
				{
				char* f_Char = Cube::ag_ClearChar(128);
				sprintf(f_Char, "%i", f_Int);
				m_str_Input += f_Char;
				delete f_Char;
				}

			void acPushFloat(float f_Float)
				{
				char* f_Char = Cube::ag_ClearChar(128);
				sprintf(f_Char, "%f", f_Float);
				m_str_Input += f_Char;
				delete f_Char;
				}

			void acPushDouble(double f_Double)
				{
				char* f_Char = Cube::ag_ClearChar(128);
				sprintf(f_Char, "%u", f_Double);
				m_str_Input += f_Char;
				delete f_Char;
				}

			std::string acGetInput(void)
				{
				return m_str_Input;
				}

			int acSize(void)
				{
				return m_str_Input.size();
				}

			std::string m_str_Input;
			std::string m_OutputHash;
		};

	class CubeHASH
		{
		public:
			CubeHASH() { m_vec_Input.clear(); m_OutputHash.clear(); };
			~CubeHASH() { m_vec_Input.clear(); m_OutputHash.clear(); };

			std::vector<unsigned int> m_vec_Input;
			std::string m_OutputHash;
		};

	class unMutexCC
		{
		public:
			unMutexCC()
				{
				mBlock = false;
				mFired = false;
				}
			~unMutexCC() {};
	
			bool mBlock;
			bool mFired;

			void ac_Fire(void)
				{
				int f_x = 1;
				if(mFired == 5)
					{
					mFired = 0;
					}
				while(mFired) { /*wait*/ }
				mFired = true;
				printf("ac_Fire\n");
				}

			void ac_Free(void)
				{
				mFired = false;
				printf("ac_Free\n");
				}
		};

	class CubeTier;

	class CubeShare
		{
		public:
			CubeShare()
				{
				m_ID = 1;
				m_Score = 0;
				m_Owner.clear();
				m_Date.clear();
				m_Amount = 0.0f;
				m_Tier = nullptr;
				};
			~CubeShare()
				{
				m_ID = 1;
				m_Score = 0;
				m_Owner.clear();
				m_Date.clear();
				m_Amount = 0.0f;
				m_Tier = nullptr;
				};

			int m_ID;
			int m_Score;
			std::shared_ptr<CubeTier> m_Tier;
			std::string m_Owner;
			std::string m_Date;
			float m_Amount;
		};

	class CubeTier
		{
		public:
			CubeTier()
				{
				m_Level = 0;
				};
			~CubeTier()
				{
				m_Level = 0;
				};

			std::vector<CubeShare*> m_vec_Share;
			int m_Level;
		};

	class CubePeer
		{
		public:
			CubePeer()
				{
				m_Share.clear();
				m_Amount = 0.0f;
				}
			~CubePeer()
				{
				m_Share.clear();
				m_Amount = 0.0f;
				}

			std::vector<CubeShare*> m_Share;
			std::string m_Owner;
			float m_Amount;
		};

	class ShareContainer
		{
		public:
			ShareContainer()
			{
				m_espo_Owner.clear();
				m_espo_Date.clear();
				m_Peer.clear();
				m_espo_ShareOffset = 0;
				m_espo_Peer = 0;
				m_espo_ID = 0;
				m_espo_Score = 0;
			};

			~ShareContainer()
				{
				m_espo_Owner.clear();
				m_espo_Date.clear();
				m_Peer.clear();
				m_espo_ShareOffset = 0;
				m_espo_Peer = 0;
				m_espo_ID = 0;
				m_espo_Score = 0;
				};

			CubePeer* acPeerfromOwner(std::string f_Owner)
				{
				for(int f_Helly = 0; f_Helly < m_Peer.size(); f_Helly++)
					{
					CubePeer* f_Peer = m_Peer[f_Helly];

					if(f_Peer->m_Owner.compare(f_Owner) == 0)
						{
						return f_Peer;
						}
					}

				for(;;)
					{
					//ECN::ADVWARN::Peer not found using owner = f_Owner.c_str();
					}

				return nullptr;
				}

			std::vector<CubePeer*> m_Peer;
			int m_espo_ShareOffset;
			int m_espo_Peer;
			int m_espo_ID;
			int m_espo_Score;
			std::string m_espo_Owner;
			std::string m_espo_Date;
		};

	class BiRand
		{
		public:
			BiRand() { m_Seed = Cube::random(); m_ProgressCount = 0; m_Value = Cube::random(); }
			BiRand(float f_Seed)
				{ m_Seed = f_Seed; m_ProgressCount = 0;	m_Value = Cube::random(); }

			float acGet(void)
				{
				m_Value = Cube::random() * m_Seed;
				m_Seed = Cube::random();
				m_ProgressCount++;
				return m_Value;
				}

		float m_Seed;
		int m_ProgressCount;
		float m_Value;
		};

	class CubeCKey
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

			void acSavetoWallet(void);

			void acSerialize(void);
			void acDeSerialize(void);

			CKey m_Key;
			CPubKey m_PubKey;
			std::string m_str_Address;
		};

	class BiCard
		{
		public:
			BiCard()
				{
				m_Value = Cube::randomFac() % BICARD_NOMCARD;
				m_Suit = Cube::randomFac() % BISUIT_NOMSUITS;
				acCardColour();
				};
			~BiCard() {};

			void Draw(void)
				{
				m_Value = Cube::randomFac() % BICARD_NOMCARD;
				m_Suit = Cube::randomFac() % BISUIT_NOMSUITS;
				acCardColour();
				};

			void acCardColour(void)
				{
				switch(m_Suit)
					{
					case BISUIT_CLUBS:
						{
						m_ColourRed = false;
						m_ColourBlack = true;
						}break;

					case BISUIT_SPADES:
						{
						m_ColourRed = false;
						m_ColourBlack = true;
						}break;

					case BISUIT_DIAMONDS:
						{
						m_ColourRed = true;
						m_ColourBlack = false;
						}break;

					case BISUIT_HEARTS:
						{
						m_ColourRed = true;
						m_ColourBlack = false;
						}break;
					}
				}

			int m_Value;
			int m_Suit;
			bool m_ColourRed;
			bool m_ColourBlack;
		};

	class BiCardPad
		{
		public:
			BiCardPad() {};
			~BiCardPad() {};

			void Clear(void)
				{
				m_Card.clear();
				};

			void Compute(void)
				{
				m_Card.clear();
				};

			float Play(void)
				{
				float f_Result = 0.0f;
				return f_Result;
				};

			std::vector<BiCard> m_Card;
			bool f_Win;
		};

	class BiDeck
		{
		public:
			BiDeck() {};
			~BiDeck() {};

			/*void acShuffle(void)
				{
				for(int f_Index = 0; f_Index < 52; f_Index++)
					{
					m_Card[f_Index].Draw();
					}
				}*/

			BiCard acDealOne(void)
				{
				BiCard f_Card;
				return f_Card;
				}

		//BiCard m_Card[52];
		};

	class Bi21
		{
		public:
			Bi21(float f_Stake, int f_NomCardPads)
				{  //////////////////////
				  //
				 // Deal First Card
				//
				for(int f_Pad = 0; f_Pad < f_NomCardPads; f_Pad++)
					{
					m_CardPad[f_Pad].m_Card.push_back(m_Deck.acDealOne());
					}

				m_Dealer.m_Card.push_back(m_Deck.acDealOne());

				   //////////////////////
				  //
				 // Deal Second Card
				//
				for(int f_Pad = 0; f_Pad < f_NomCardPads; f_Pad++)
					{
					m_CardPad[f_Pad].m_Card.push_back(m_Deck.acDealOne());
					}

				m_Dealer.m_Card.push_back(m_Deck.acDealOne());
				};
			~Bi21() {};

			float acPlay(void)
				{  //////////////
				  //
				 // Play
				//
				float f_Result = 0.0f;
				for(int f_Pad = 0; f_Pad < m_NomCardPads; f_Pad++)
					{
					f_Result += m_CardPad[f_Pad].Play();
					}

				m_Dealer.Play();
				//if(m_Dealer.)
				};

			float m_Stake;
			int m_NomCardPads;
			BiDeck m_Deck;
			BiCardPad m_CardPad[15];
			BiCardPad m_Dealer;
		};

	class BiVector
		{
		public:
			BiVector()
				{ m_X = 0.0f; m_Y = 0.0f; m_Z = 0.0f; }

			BiVector(float f_X, float f_Y, float f_Z)
				{ m_X = f_X; m_Y = f_Y; m_Z = f_Z; }

			BiVector(float f_X, float f_Y, float f_Z, float f_W)
				{ m_X = f_X; m_Y = f_Y; m_Z = f_Z; }

			BiVector(float f_M)
				{ m_X = f_M; m_Y = f_M; m_Z = f_M; }

			void operator*=(const float &f)
				{
				m_X *= f;
				m_Y *= f;
				m_Z *= f;
				}

			BiVector operator*(const float &f)
				{
				BiVector f_Vector;
				f_Vector.m_X = m_X * f;
				f_Vector.m_X = m_Y * f;
				f_Vector.m_X = m_Z * f;
				return f_Vector;
				}

			void operator+=(const BiVector &v)
				{
				m_X += v.m_X;
				m_Y += v.m_Y;
				m_Z += v.m_Z;
				}

			BiVector operator+(const BiVector &v)
				{
				BiVector f_Vector;
				f_Vector.m_X = m_X + v.m_X;
				f_Vector.m_X = m_Y + v.m_Y;
				f_Vector.m_X = m_Z + v.m_Z;
				return f_Vector;
				}

			void operator-=(const BiVector &v)
				{
				m_X -= v.m_X;
				m_Y -= v.m_Y;
				m_Z -= v.m_Z;
				}

			BiVector operator-(const BiVector &v)
				{
				BiVector f_Vector;
				f_Vector.m_X = m_X - v.m_X;
				f_Vector.m_Y = m_Y - v.m_Y;
				f_Vector.m_Z = m_Z - v.m_Z;
				return f_Vector;
				}

			void cross(const BiVector &v1, const BiVector &v2)
				{
				m_X = v1.m_Y * v2.m_Z - v1.m_Z * v2.m_Y;
				m_Y = v1.m_Z * v2.m_X - v1.m_X * v2.m_Z;
				m_Z = v1.m_X * v2.m_Y - v1.m_Y * v2.m_X;
				}

			void acPushRandSphere(float f_Radius, float f_Seed)
				{
				f_Radius *= 1.5;

				for (int f_Cntr = 0; f_Cntr < 7; f_Cntr++)
					{
					BiRand f_BiRand(f_Seed);
					BiVector f_Vector((f_BiRand.acGet() - 0.5f) * f_Radius, (f_BiRand.acGet() - 0.5f) * f_Radius, (f_BiRand.acGet() - 0.5f) * f_Radius);
				
					m_X += f_Vector.m_X * f_Radius;
					m_Y += f_Vector.m_Y * f_Radius;
					m_Z += f_Vector.m_Z * f_Radius;
					}
				}

			void acRun_visualminer(int g_Verbose = false)
				{
				BiVector f_Result;
				Carriage f_Car;
				f_Car = Cube::agRun_visualminer(m_X, m_Y, m_Z);

				m_X = f_Car.m_X;
				m_Y = f_Car.m_Y;
				m_Z = f_Car.m_Z;
				}

			void acBoundaryRanging(void)
				{
				if((m_X < 1.0f) && (m_X > 0.0f))
					{
					while(m_X < 1.0f)
						{
						m_X += SCP_PREC_ONE;
						}
					}

				if((m_X > -1.0f) && (m_X < 0.0f))
					{
					while(m_X > -1.0f)
						{
						m_X -= SCP_PREC_ONE;
						}
					}

				if((m_Y < 1.0f) && (m_Y > 0.0f))
					{
					while(m_Y < 1.0f)
						{
						m_Y += SCP_PREC_ONE;
						}
					}

				if((m_Y > -1.0f) && (m_Y < 0.0f))
					{
					while(m_Y > -1.0f)
						{
						m_Y -= SCP_PREC_ONE;
						}
					}

				if((m_Z < 1.0f) && (m_Z > 0.0f))
					{
					while(m_Z < 1.0f)
						{
						m_Z += SCP_PREC_ONE;
						}
					}

				if((m_Z > -1.0f) && (m_Z < 0.0f))
					{
					while(m_Z > -1.0f)
						{
						m_Z -= SCP_PREC_ONE;
						}
					}

				while(m_X >= 10.0f)
					{
					m_X -= SCP_PREC_TEN;
					}

				while(m_X <= -10.0f)
					{
					m_X += SCP_PREC_TEN;
					}

				while(m_Y >= 10.0f)
					{
					m_Y -= SCP_PREC_TEN;
					}

				while(m_Y <= -10.0f)
					{
					m_Y += SCP_PREC_TEN;
					}

				while(m_Z >= 10.0f)
					{
					m_Z -= SCP_PREC_TEN;
					}

				while(m_Z <= -10.0f)
					{
					m_Z += SCP_PREC_TEN;
					}
				}

			void acLargeBoundaryRanging(void)
				{
				while(m_X >= SCP_PREC_UPP)
					{
					m_X -= SCP_PREC_LGE;
					}

				while(m_X <= (-1.0f * SCP_PREC_UPP))
					{
					m_X += SCP_PREC_LGE;
					}

				while(m_Y >= SCP_PREC_UPP)
					{
					m_Y -= SCP_PREC_LGE;
					}

				while(m_Y <= (-1.0f * SCP_PREC_UPP))
					{
					m_Y += SCP_PREC_LGE;
					}

				while(m_Z >= SCP_PREC_UPP)
					{
					m_Z -= SCP_PREC_LGE;
					}

				while(m_Z <= (-1.0f * SCP_PREC_UPP))
					{
					m_Z += SCP_PREC_LGE;
					}
				}

			void acResolve_precision(float f_Scale)
				{
#if 1
				acBoundaryRanging();
#else
				char* f_CharX = ag_ClearChar(150);

				sprintf(f_CharX, "%.8f", m_X);

				m_X = atof(f_CharX);

				delete f_CharX;

				char* f_CharY = ag_ClearChar(150);

				sprintf(f_CharY, "%.8f", m_Y);

				m_Y = atof(f_CharY);

				delete f_CharY;

				char* f_CharZ = ag_ClearChar(150);

				sprintf(f_CharZ, "%.8f", m_Z);

				m_Z = atof(f_CharZ);

				delete f_CharZ;
#endif

				m_X *= f_Scale;
				m_Y *= f_Scale;
				m_Z *= f_Scale;
				}

			void acPrepare(void)
				{
				BiVector f_Result(m_Z * -1, m_Y, m_X);

				m_X = f_Result.m_X;
				m_Y = f_Result.m_Y;
				m_Z = f_Result.m_Z;
				}

			void acStore(void)
				{
#if 0
				vec_Path_X.push_back(m_X);
				vec_Path_Y.push_back(m_Y);
				vec_Path_Z.push_back(m_Z);
#endif
				}

			float acDot(void)
				{
				return(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
				}

			float acDot(BiVector f_Vec2)
				{
				return(m_X * f_Vec2.m_X + m_Y * f_Vec2.m_Y + m_Z * f_Vec2.m_Z);
				}

			float acLength(void)
				{
				float f_Length = (float)sqrt(acDot());

				return f_Length;
				}

			BiVector acCross(BiVector f_Up)
				{
				BiVector f_Result(0);

				f_Result.m_X = m_Y * f_Up.m_Z - m_Z * f_Up.m_Y;
				f_Result.m_Y = m_Z * f_Up.m_X - m_X * f_Up.m_Z;
				f_Result.m_Z = m_X * f_Up.m_Y - m_Y * f_Up.m_X;

				return f_Result;
				}

			float acNorm(void)
				{
				float len = m_X * m_X + m_Y * m_Y + m_Z * m_Z;

				if(len > 0)
					{
					len = 1.0f / sqrtf(len);
					m_X *= len;
					m_Y *= len;
					m_Z *= len;
					}

				return len;
				}

		public:

			float m_X;
			float m_Y;
			float m_Z;

#if 0
			std::vector<float> vec_Path_X;
			std::vector<float> vec_Path_Y;
			std::vector<float> vec_Path_Z;
#endif
		};

	class Index
		{
		public:
			Index()	{ m_A = 0; m_B = 0;	m_C = 0; }

			BiVector m_FaceNormal;

			int m_A;
			int m_B;
			int m_C;
		};

	class BiPlane
		{
		public:
			BiPlane()
				{
				m_Dir.m_X = 0.0f;
				m_Dir.m_Y = 1.0f;
				m_Dir.m_Z = 0.0f;
				m_Dist = 0;
				};
			~BiPlane() {};

			BiVector m_Dir;
			float m_Dist;
		};

	class aabb
		{
		public:
			BiVector _min;
			BiVector _max;

			aabb();
			aabb(const BiVector &);

			bool collide(const aabb& b) const;
			bool isin(std::shared_ptr<aabb> b);
			bool collide(std::shared_ptr<aabb> b);
			bool inside(const BiVector &) const;

			aabb &operator += (const aabb &);
			aabb &operator += (const std::shared_ptr<BiVector> &p);

			float width()  const { return _max.m_X - _min.m_X; }
			float height() const { return _max.m_Y - _min.m_Y; }
			float depth()  const { return _max.m_Z - _min.m_Z; }

			BiVector center();
			BiVector centered();
			float volume();
			void empty();

#ifdef CUBE_AABB_USE_COLOR
			BiVector _color;
			void visualization();
#endif
		};

	class CubeBicycle
		{
		public:
			CubeBicycle()
				{
				acClear();

				vec_Vertex.reserve(8);
				vec_Color.reserve(8);
				};
			CubeBicycle(FILE* f_File);
			CubeBicycle(std::string f_Buffer);

			void acClear(void)
				{
				vec_Vertex.clear();
				vec_Color.clear();

				m_indexCount = 0;
				m_Refresh = 0;
				}

#if 0
			void acRefresh(void);
#endif

			void acRefresh(void);
			void avGrow(float f_Amount);
			void avTranslate(Cube::BiVector f_Vector);
			void avPushBack(int f_Step);
			void acSerialise(std::string* f_String);

			int ray_intersect(int f_Index, const BiVector& ro, const BiVector& rd, BiVector& ip, float& dist);
			int ray_triangle(int f_Index, const BiVector& ro, const BiVector& rd, BiVector& ip, float& dist);

			int m_indexCount;

			std::vector<std::shared_ptr<Cube::BiVector>> vec_Vertex;
			std::vector<std::shared_ptr<Cube::BiVector>> vec_Color;

			int m_Refresh;

#ifndef JNI
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
#else
			std::shared_ptr<aabb> m_aabb;

			GLuint mVertexPositionBuffer;
			GLuint mVertexColorBuffer;
			GLuint mVertexNormalBuffer;
			GLuint mIndexBuffer;
			GLuint mTexCoordBuffer;
#endif
		};

	class LogicGate
		{
		public:


		};

	class BiStyle
		{
		public:
			BiStyle() { m_AdIndexMode = 0; m_AdIndexCount = 0; m_AdIndexPercent = 0; };
			~BiStyle() { m_AdIndexMode = 0; m_AdIndexCount = 0; m_AdIndexPercent = 0; };

			int m_AdIndexMode;
			int m_AdIndexCount;
			int m_AdIndexPercent;
		};

	class CubeHESH
		{
		public:
			CubeHESH() { acClear(); }
			CubeHESH(int f_ADMAX, int f_ADHIGH, int f_ADLOW, int f_CountLM = -1)
				{
				acClear();

				m_ADMAX = f_ADMAX;
				m_ADHIGH = f_ADHIGH;
				m_ADLOW = f_ADLOW;

				m_CountLM = f_CountLM;
				}
			CubeHESH(FILE* f_File);
			CubeHESH(std::string f_Buffer);

			~CubeHESH()
				{
				acClear();
				}

			void acClear(void)
				{
				for(int f_XY = 0; f_XY < vec_Bicycle.size(); f_XY++)
					{
					vec_Bicycle[f_XY]->vec_Vertex.clear();
					vec_Bicycle[f_XY]->vec_Color.clear();
					}

				vec_Bicycle.clear();
				m_adIndex.clear();

				m_vec_Collision.clear();

				m_ADMAX = g_ADMAX;
				m_ADHIGH = g_ADHIGH;
				m_ADLOW = g_ADLOW;

				m_CountLM = -5;
				}

			void ac_IsOK(void)
				{
				if(m_adIndex.size() != vec_Bicycle.size())
					{
					if(m_adIndex.size() < vec_Bicycle.size())
						{
						int f_sindex = m_adIndex.size();

						while(m_adIndex.size() < vec_Bicycle.size())
							{
							m_adIndex.push_back(f_sindex);

							f_sindex++;
							}
						}
					else
						{
						while(m_adIndex.size() > vec_Bicycle.size())
							{
							m_adIndex.pop_back();
							}
						}
					}

				for(int f_Jet = 0; f_Jet < vec_Bicycle.size(); f_Jet++)
					{
					shared_ptr<CubeBicycle> f_Bike = vec_Bicycle[f_Jet];

					bool f_GradePass = true;

					if(f_Bike->vec_Vertex.size() != 8)
						{
						f_GradePass = false;
						}

					if(f_Bike->vec_Color.size() != 8)
						{
						if(f_Bike->vec_Color.size() > 8)
							{
							while(f_Bike->vec_Color.size() > 8)
								{
								f_Bike->vec_Color.pop_back();
								}
							}
						else
							{
							if(f_Bike->vec_Color.size() >= 1)
								{
								while(f_Bike->vec_Color.size() < 8)
									{
									f_Bike->vec_Color.push_back(f_Bike->vec_Color[0]);
									}
								}
							else
								{
								f_GradePass = false;
								}
							}
						}

					if(f_GradePass == false)
						{
						int f_Index = vec_Bicycle.size() - 1;

						while(vec_Bicycle.size() > f_Jet)
							{
							vec_Bicycle[f_Index]->acClear();

							vec_Bicycle.pop_back();
							m_adIndex.pop_back();

							f_Index--;
							}
						}
					}
				}

			void acSerialise(std::string* f_String);
			int ray_intersect(const BiVector& ro, const BiVector& rd, BiVector& ip, float& dist);

			int m_ID;
			unsigned long long m_Timestamp;

			float m_RotateX;
			float m_RotateY;
			float m_RotateZ;

			float m_bckred;
			float m_bckgreen;
			float m_bckblue;

			float m_ValueBank;

			int m_ADMAX;
			int m_ADHIGH;
			int m_ADLOW;

			int m_CountLM;

			std::vector<int> m_adIndex;
			std::vector<std::shared_ptr<CubeBicycle>> vec_Bicycle;
			std::vector<std::shared_ptr<CubeCollision>> m_vec_Collision;
			std::shared_ptr<Cube::CubeHASH_originstring> m_Hash;
		};

	class BicycleContainer
		{
		public:
			void avStage(void);
			void ac_IsOK(void);

			std::vector<CubeKEY*> vec_Key;
			int nom_Bicycle;
		};

	/////////////////////////
	/// START Cubetronics ///
	/////////////////////////

	class float3
		{
		public:
			float3() { x = 0; y = 0; z = 0; r = 0; g = 0; b = 0; }
			float3(float f_V) { x = f_V; y = f_V; z = f_V; r = f_V; g = f_V; b = f_V; }
			float3(float f_X, float f_Y, float f_Z) { x = f_X; y = f_Y; z = f_Z; r = 0.0f; g = 0.0f; b = 0.0f; }
			float3(int f_Type)
				{
				x = random() - 0.5;
				y = random() - 0.5;
				z = random() - 0.5;
				r = random();
				g = random();
				b = random();
				}

			float3 operator=(const BiVector &v) const
				{
				return float3(v.m_X, v.m_Y, v.m_Z);
				}

			bool operator==(const float3 &v) const
				{
				if (x != v.x) return false;
				if (y != v.y) return false;
				if (z != v.z) return false;
				return true;
				}

			void acNorm(void)
				{
				double len = x * x + y * y + z * z;
				if(len > 0.0)
					{
					len = 1.0 / sqrt(len);
					x *= len;
					y *= len;
					z *= len;
					}
				}

			float x, y, z;
			float r, g, b;
		};

	class float4
		{
		public:
			float4() { x = 0; y = 0; z = 0; w = 0; }
			float4(float f_V) { x = f_V; y = f_V; z = f_V; w = f_V; }
			float4(float f_X, float f_Y, float f_Z, float f_W) { x = f_X; y = f_Y; z = f_Z; w = f_W; }
			float4(float f_X, float3 f_Y) { x = f_X; y = f_Y.x; z = f_Y.y; w = f_Y.z; }

			float4 operator=(const BiVector &v) const
				{
				return float4(v.m_X, v.m_Y, v.m_Z, 1.0f);
				}

			float x, y, z, w;
		};

	class matrix
		{
		public:
			union
				{
				float m[4][4];	//!< matrix elements
				float mf[16];	//!< matrix elements
				};

			matrix()
				{
				mf[0] = mf[5] = mf[10] = mf[15] = 1.0f;
				mf[1] = mf[2] = mf[3] =
				mf[4] = mf[6] = mf[7] =
				mf[8] = mf[9] = mf[11] =
				mf[12] = mf[13] = mf[14] = 0.0f;
				}

			float3 operator*(const float3 &v) const
				{
				return float3(
					v.x*mf[0] + v.y*mf[4] + v.z*mf[8] + /*v.w*/mf[12],
					v.x*mf[1] + v.y*mf[5] + v.z*mf[9] + /*v.w*/mf[13],
					v.x*mf[2] + v.y*mf[6] + v.z*mf[10] + /*v.w*/mf[14]/*,
																	  v.x*mf[3] + v.y*mf[7] + v.z*mf[11] + v.w*mf[15]*/
					);
				}

			float4 operator*(const float4 &v) const
				{
				return float4(
					v.x*mf[0] + v.y*mf[4] + v.z*mf[8] + v.w*mf[12],
					v.x*mf[1] + v.y*mf[5] + v.z*mf[9] + v.w*mf[13],
					v.x*mf[2] + v.y*mf[6] + v.z*mf[10] + v.w*mf[14],
					v.x*mf[3] + v.y*mf[7] + v.z*mf[11] + v.w*mf[15]
					);
				}

			void operator*=(const matrix &m1)
				{
				matrix m2;

				m2.mf[0] = mf[0] * m1.mf[0] + mf[1] * m1.mf[4] + mf[2] * m1.mf[8];// + mf[ 3]*m1.mf[12];
				m2.mf[1] = mf[0] * m1.mf[1] + mf[1] * m1.mf[5] + mf[2] * m1.mf[9];// + mf[ 3]*m1.mf[13];
				m2.mf[2] = mf[0] * m1.mf[2] + mf[1] * m1.mf[6] + mf[2] * m1.mf[10];// + mf[ 3]*m1.mf[14];
				m2.mf[3] = 0.0f;//mf[ 0]*m1.mf[3] + mf[ 1]*m1.mf[7] + mf[ 2]*m1.mf[11] + mf[ 3]*m1.mf[15];

				m2.mf[4] = mf[4] * m1.mf[0] + mf[5] * m1.mf[4] + mf[6] * m1.mf[8];// + mf[ 7]*m1.mf[12];
				m2.mf[5] = mf[4] * m1.mf[1] + mf[5] * m1.mf[5] + mf[6] * m1.mf[9];// + mf[ 7]*m1.mf[13];
				m2.mf[6] = mf[4] * m1.mf[2] + mf[5] * m1.mf[6] + mf[6] * m1.mf[10];// + mf[ 7]*m1.mf[14];
				m2.mf[7] = 0.0f;//mf[ 4]*m1.mf[3] + mf[ 5]*m1.mf[7] + mf[ 6]*m1.mf[11] + mf[ 7]*m1.mf[15];

				m2.mf[8] = mf[8] * m1.mf[0] + mf[9] * m1.mf[4] + mf[10] * m1.mf[8];// + mf[11]*m1.mf[12];
				m2.mf[9] = mf[8] * m1.mf[1] + mf[9] * m1.mf[5] + mf[10] * m1.mf[9];// + mf[11]*m1.mf[13];
				m2.mf[10] = mf[8] * m1.mf[2] + mf[9] * m1.mf[6] + mf[10] * m1.mf[10];// + mf[11]*m1.mf[14];
				m2.mf[11] = 0.0f;//mf[ 8]*m1.mf[3] + mf[ 9]*m1.mf[7] + mf[10]*m1.mf[11] + mf[11]*m1.mf[15];

				m2.mf[12] = mf[12] * m1.mf[0] + mf[13] * m1.mf[4] + mf[14] * m1.mf[8] + /*mf[15]*/m1.mf[12];
				m2.mf[13] = mf[12] * m1.mf[1] + mf[13] * m1.mf[5] + mf[14] * m1.mf[9] + /*mf[15]*/m1.mf[13];
				m2.mf[14] = mf[12] * m1.mf[2] + mf[13] * m1.mf[6] + mf[14] * m1.mf[10] + /*mf[15]*/m1.mf[14];
				m2.mf[15] = 1.0f;//mf[12]*m1.mf[3] + mf[13]*m1.mf[7] + mf[14]*m1.mf[11] + mf[15]*m1.mf[15];

				*this = m2;
				}


#ifndef JNI
			void operator=(const DirectX::XMMATRIX &m1)
				{
				matrix m2;

#ifdef ARM_ARCH
				m2.mf[0] = m1.r->n128_f32[0];
				m2.mf[1] = m1.r->n128_f32[1];
				m2.mf[2] = m1.r->n128_f32[2];
				m2.mf[3] = m1.r->n128_f32[3];

				m2.mf[4] = m1.r->n128_f32[4];
				m2.mf[5] = m1.r->n128_f32[5];
				m2.mf[6] = m1.r->n128_f32[6];
				m2.mf[7] = m1.r->n128_f32[7];

				m2.mf[8] = m1.r->n128_f32[8];
				m2.mf[9] = m1.r->n128_f32[9];
				m2.mf[10] = m1.r->n128_f32[10];
				m2.mf[11] = m1.r->n128_f32[11];

				m2.mf[12] = m1.r->n128_f32[12];
				m2.mf[13] = m1.r->n128_f32[13];
				m2.mf[14] = m1.r->n128_f32[14];
				m2.mf[15] = m1.r->n128_f32[15];
#else
				m2.mf[0] = m1.r->m128_f32[0];
				m2.mf[1] = m1.r->m128_f32[1];
				m2.mf[2] = m1.r->m128_f32[2];
				m2.mf[3] = m1.r->m128_f32[3];

				m2.mf[4] = m1.r->m128_f32[4];
				m2.mf[5] = m1.r->m128_f32[5];
				m2.mf[6] = m1.r->m128_f32[6];
				m2.mf[7] = m1.r->m128_f32[7];

				m2.mf[8] = m1.r->m128_f32[8];
				m2.mf[9] = m1.r->m128_f32[9];
				m2.mf[10] = m1.r->m128_f32[10];
				m2.mf[11] = m1.r->m128_f32[11];

				m2.mf[12] = m1.r->m128_f32[12];
				m2.mf[13] = m1.r->m128_f32[13];
				m2.mf[14] = m1.r->m128_f32[14];
				m2.mf[15] = m1.r->m128_f32[15];
#endif

				*this = m2;
				}
#endif
		};

	// Per-vertex data used as input to the vertex shader.
	typedef struct VertexShaderInput
		{
		float3 pos;
		float3 color;
		};

	// Per-pixel color data passed through the pixel shader.
	typedef struct PixelShaderInput
		{
		float4 pos;
		float3 color;
		};

	class CubeHeshExporter
		{
		public:
			CubeHeshExporter() { acClear(); }
			~CubeHeshExporter() { acClear(); }

			void acClear(void)
				{
				m_vec_Result.clear();
				BiCount = 0;
				BiVectorCount = 0;
				};

			void acPrepare(void) { acClear(); }

			std::vector<PixelShaderInput> m_vec_Result;
			int BiCount;
			int BiVectorCount;
		};

	class BiMesh;
	class BiMeshData;

	class BiSphere
		{
		public:
			BiSphere()
				{
				m_Pos.m_X = 0;
				m_Pos.m_Y = 0;
				m_Pos.m_Z = 0;
				m_Dist = 0.0f;
				m_Mesh = nullptr;
				}
			BiSphere(BiMesh* f_Mesh)
				{
				m_Mesh = f_Mesh;
				m_Pos.m_X = 0;
				m_Pos.m_Y = 0;
				m_Pos.m_Z = 0;
				m_Dist = 0.0f;
				m_Mesh = nullptr;
				}
			BiSphere(BiVector f_Pos, float f_Dist)
				{
				m_Pos = f_Pos;
				m_Dist = f_Dist;
				m_Mesh = nullptr;
				}
			~BiSphere() {};

			void acPushRadius(float f_Length);

#if 0
			bool RaySphereIntersect(DirectX::XMVECTOR rayOrigin, DirectX::XMVECTOR rayDirection);
#endif

			BiMesh* m_Mesh;
			BiVector m_Pos;
			float m_Dist;
		};

	class BiNote
		{
		public:
			BiNote()
				{
				m_Note = 0;
				m_Velocity = 0.0f;
				m_Frequency = 0.0f;
				m_TimeStart = 0.0f;
				m_TimeEnd = 0.0f;
				}
			~BiNote()
				{
				m_Note = 0;
				m_Velocity = 0.0f;
				m_Frequency = 0.0f;
				m_TimeStart = 0.0f;
				m_TimeEnd = 0.0f;
				};

			int m_Note;
			float m_Velocity;
			float m_Frequency;

			float m_TimeStart;
			float m_TimeEnd;
		};

	class BiMidi
		{
		public:
			BiMidi()
				{
				m_vec_NoteOn.clear();
				}
			BiMidi(BiMesh* f_Mesh)
				{
				m_vec_NoteOn.clear();
				}
			BiMidi(BiVector f_Pos, float f_Dist)
				{
				m_vec_NoteOn.clear();
				}
			~BiMidi() {};

			std::vector<BiNote*> m_vec_NoteOn;
		};

	class BiVolt
		{
		public:
			BiVolt()
				{
				m_vec_Volt.clear();
				m_SourceType = 0;
				}
			~BiVolt()
				{
				m_vec_Volt.clear();
				m_SourceType = 0;
				};

			std::vector<double> m_vec_Volt;
			int m_SourceType;
		};

	class BiMesh
		{
		public:
			BiMesh() : /*m_Hash(random()),*/ m_Name("BiMesh")
				{
				m_OK = false;
				m_RotationZ = 0.0f;
				}
			BiMesh(std::string f_Name) : /*m_Hash(random()),*/ m_Name(f_Name)
				{
				m_OK = false;
				m_RotationZ = 0.0f;
				}
			~BiMesh()
				{
				//m_vertexShader.Reset();
				//m_pixelShader.Reset();
				//m_inputLayout.Reset();
				//m_vertexBuffer.Reset();
				//m_indexBuffer.Reset();
				m_vec_PathIN.clear();
				m_vec_PathOUT.clear();
				delete m_Sphere;
				}

			void acMark(int f_Type);

#if 0
			bool acInteract(DirectX::XMVECTOR rayOrigin, DirectX::XMVECTOR rayDirection);
#endif

			BiSphere* m_Sphere;

			std::vector<BiMesh*> m_vec_PathIN;
			std::vector<BiMesh*> m_vec_PathOUT;

			std::vector<BiMesh*> m_vec_Input;
			std::vector<BiMesh*> m_vec_Output;

			std::vector<BiMeshData*> m_vec_MeshData;

			int m_VertCount;
			int m_indexCount;

			//Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
			//Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
			//Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
			//Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
			//Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;

			float m_Finger;

			//Hash m_Hash;

			int m_InteractionType;

			std::string m_Name;
			std::string m_Path;

			int m_Type;
			int m_Factory;

			float m_RotationZ;

			float m_X;
			float m_Y;
			float m_Z;

			bool m_OK;
		};

	class BiMeshContainer
		{
		public:
			BiMeshContainer()
				{
				m_vec_AllMesh.clear();
				m_vec_LevelRack.clear();
				m_vec_Sphere.clear();
				m_Int = false;
				m_Action = nullptr;
				};

			~BiMeshContainer()
				{
				for(int f_Count = 0; f_Count > m_vec_AllMesh.size(); f_Count++)
					{
					delete m_vec_AllMesh[f_Count];
					}

				m_vec_AllMesh.clear();
				m_vec_LevelRack.clear();
				m_vec_Sphere.clear();
				m_Int = false;
				m_Action = nullptr;
				};

			void acClearInteractions(void);
			void acInteract(float f_MouseX, float f_MouseY);

			void acPushLevel(BiMesh* f_Mesh)
				{
				m_vec_AllMesh.push_back(f_Mesh);
				m_vec_Sphere.push_back(f_Mesh->m_Sphere);
				m_vec_LevelRack.push_back(f_Mesh);
				}

			void acPushCom(BiMesh* f_Mesh, int f_Level)
				{
				f_Mesh->m_vec_PathOUT.push_back(m_vec_LevelRack[f_Level]);
				m_vec_AllMesh.push_back(f_Mesh);
				m_vec_Sphere.push_back(f_Mesh->m_Sphere);
				m_vec_LevelRack[f_Level]->m_vec_PathIN.push_back(f_Mesh);
				}

			BiMesh* m_Action;
			bool m_Int;

			std::vector<BiMesh*> m_vec_AllMesh;
			std::vector<BiMesh*> m_vec_LevelRack;
			std::vector<BiSphere*> m_vec_Sphere;
		};

	class BiMeshCore
		{
		public:
			BiMeshCore()
				{
				m_Type = 0;
				m_Factory = 0;
				m_Time = 0.0f;
				};

			BiMeshCore(int f_Type, int f_Factory)
				{
				m_Type = f_Type;
				m_Factory = f_Factory;
				m_Time = 0.0f;
				};

			~BiMeshCore()
				{
				m_Type = 0;
				m_Factory = 0;
				m_Time = 0.0f;
				};

			void acPrepare(float f_Time);

			void acProcess(float f_Time);

			int m_Type;
			int m_Factory;

			float m_Time;

			std::vector<double> m_Input;
			std::vector<double> m_Output;
			std::vector<BiVolt> m_VoltInput;
			std::vector<BiVolt> m_VoltOutput;
			std::vector<BiMidi> m_MidiInput;
			std::vector<BiMidi> m_MidiOutput;

			 ////////////////////
			// ESL with speed
		};

	class BiUV
		{
		public:
			BiUV(float f_U, float f_V)
				{
				m_U = f_U;
				m_V = f_V;
				}; 
			
			BiUV()
				{
				m_U = 0.0f;
				m_V = 0.0f;
				};

			~BiUV()
				{
				m_U = 0.0f;
				m_V = 0.0f;
				};

			float m_U;
			float m_V;
		};

	class BiRGBA
		{
		public:
			BiRGBA(float f_R, float f_G, float f_B, float f_A)
				{
				m_R = f_R;
				m_G = f_G;
				m_B = f_B;
				m_A = f_A;
				};

			BiRGBA()
				{
				m_R = 0.0f;
				m_G = 0.0f;
				m_B = 0.0f;
				m_A = 0.0f;
				};

			~BiRGBA()
				{
				m_R = 0.0f;
				m_G = 0.0f;
				m_B = 0.0f;
				m_A = 0.0f;
				};

			float m_R;
			float m_G;
			float m_B;
			float m_A;
		};

	class BiMeshData
		{
		public:
			BiMeshData()
				{
				m_vec_Vertex.clear();
				m_vec_Color.clear();
				m_vec_Normal.clear();
				m_vec_UV.clear();
				m_vec_Index.clear();
				m_vec_FaceNorm.clear();
				m_VertNom = 0;
				m_FaceNom = 0;
				m_Status = 0;
				m_IndexNom = 0;
				}

			~BiMeshData()
				{
				m_vec_Vertex.clear();
				m_vec_Color.clear();
				m_vec_Normal.clear();
				m_vec_UV.clear();
				m_vec_Index.clear();
				m_vec_FaceNorm.clear();
				m_VertNom = 0;
				m_FaceNom = 0;
				m_Status = 0;
				m_IndexNom = 0;
				}

			int acAddVertex(BiVector f_Vertex)
				{
				m_vec_Vertex.push_back(f_Vertex);
				m_VertNom++;
				return m_VertNom - 1;
				}

			int acAddVertex(BiVector f_Vertex, BiVector f_Normal)
				{
				m_vec_Vertex.push_back(f_Vertex);
				m_vec_Normal.push_back(f_Normal);
				m_VertNom++;
				return m_VertNom - 1;
				}

			int acAddVertex(float f_X, float f_Y, float f_Z, float f_R, float f_G, float f_B, float f_A, BiVector f_Normal)
				{
#ifdef GENERIC_BUILD
				Generic::VertexPositionColor f_VC;
				f_VC.pos.x = f_X;
				f_VC.pos.y = f_Y;
				f_VC.pos.z = f_Z;
				f_VC.color.x = f_R;
				f_VC.color.y = f_G;
				f_VC.color.z = f_B;
				m_vec_VertexColor.push_back(f_VC);
				m_vec_Color.push_back(BiRGBA(f_R, f_G, f_B, f_A));
				m_vec_Vertex.push_back(BiVector(f_X, f_Y, f_Z));
				m_vec_Normal.push_back(f_Normal);
				m_VertNom++;
#endif

				return m_VertNom - 1;
				}

			void acAddColor(BiRGBA f_RGBA)
				{
				m_vec_Color.push_back(f_RGBA);
				}

			void acAddUV(BiUV f_UV)
				{
				m_vec_UV.push_back(f_UV);
				}

			void acAddNormal(BiVector f_Normal)
				{
				m_vec_Normal.push_back(f_Normal);
				}

			void acAddFace(int f_A, int f_B, int f_C)
				{
				m_vec_Index.push_back(f_A);
				m_vec_Index.push_back(f_B);
				m_vec_Index.push_back(f_C);
				m_FaceNom++;
				m_IndexNom += 3;
				}

			std::vector<BiVector> m_vec_Vertex;
#ifdef GENERIC_BUILD
			std::vector<Generic::VertexPositionColor> m_vec_VertexColor;
#endif
			std::vector<BiRGBA> m_vec_Color;
			std::vector<BiVector> m_vec_Normal;
			std::vector<BiUV> m_vec_UV;

			std::vector<unsigned short> m_vec_Index;
			std::vector<BiVector> m_vec_FaceNorm;

			int m_VertNom;
			int m_FaceNom;
			int m_IndexNom;
			int m_Status;
		};

	enum CUBE_BIT_TYPE
		{
			qbtyperandomfloat,
			qbtyperandomint,
			qbtypeprogressfloat,
			qbtypeprogressint,
			qbtypenull,
			qbtypeTotal
		};

	class cube_Bit
		{
		public:
			cube_Bit()
				{
				acClear();
				}

			cube_Bit(int f_StartInt, int f_MinInt, int f_MaxInt, int f_Type, int f_Prog, int f_Depth)
				{
				acClear();

				m_TraceInt = f_StartInt;
				m_TraceIntMax = f_MaxInt;
				m_TraceIntMin = f_MinInt;
				m_Type = f_Type;
				m_TraceIntProg = f_Prog;
				m_Depth = f_Depth;
				}

			cube_Bit(float f_StartFloat, float f_MinFloat, float f_MaxFloat, int f_Type, float f_Prog, int f_Depth)
				{
				acClear();

				m_TraceFloat = f_StartFloat;
				m_TraceFloatMax = f_MaxFloat;
				m_TraceFloatMin = f_MinFloat;
				m_Type = f_Type;
				m_TraceFloatProg = f_Prog;
				m_Depth = f_Depth;
				}

			cube_Bit(float f_StartFloat, float f_MinFloat, float f_MaxFloat)
				{
				acClear();

				m_TraceFloat = f_StartFloat;
				m_TraceFloatMax = f_MaxFloat;
				m_TraceFloatMin = f_MinFloat;
				m_Type = qbtyperandomfloat;
				m_TraceFloatProg = 1.0;
				m_Depth = 0;
				}

			~cube_Bit()
				{
				acClear();
				}

			void acClear(void)
				{
				m_TraceInt = 0;
				m_TraceIntMax = CUBEBIT_DEFAULT_MAX_INT;
				m_TraceIntMin = CUBEBIT_DEFAULT_MIN_INT;
				m_TraceFloat = 0.0;
				m_TraceFloatMax = CUBEBIT_DEFAULT_MAX_FLOAT;
				m_TraceFloatMin = CUBEBIT_DEFAULT_MIN_FLOAT;
				m_Type = CUBEBIT_DEFAULT_TYPE;
				m_TraceIntProg = 0;
				m_TraceFloatProg = 0.0f;
				m_cubeBit = nullptr;
				m_Depth = 0;
				}

			void acRandomise(void)
				{
				switch (m_Type)
					{
					case qbtyperandomfloat:
						{
						m_TraceFloat = m_TraceFloatMin + ((((float)rand() / 32767) * m_TraceFloatMax) + m_TraceFloatMin);
						}break;

					case qbtyperandomint:
						{
						m_TraceInt = m_TraceIntMin + ((rand() % m_TraceIntMax) + m_TraceIntMin);
						}break;
					}
				}

			void acProg(void)
				{
				switch(m_Type)
					{
					case qbtyperandomfloat:
						{
						m_TraceFloat = m_TraceFloatMin + ((((float)rand() / 32767) * m_TraceFloatMax) + m_TraceFloatMin);
						}break;

					case qbtyperandomint:
						{
						m_TraceInt = m_TraceIntMin + ((rand() % m_TraceIntMax) + m_TraceIntMin);
						}break;

					case qbtypeprogressfloat:
						{
						m_TraceFloat = m_TraceFloatProg;

						if(m_TraceFloat > m_TraceFloatMax)
							{
							m_TraceIntProg *= -1;
							m_TraceFloat = m_TraceFloatMax;
							}

						if(m_TraceFloat < m_TraceFloatMin)
							{
							m_TraceIntProg *= -1;
							m_TraceFloat = m_TraceFloatMin;
							}
						}break;

					case qbtypeprogressint:
						{
						m_TraceInt = m_TraceIntProg;

						if(m_TraceInt > m_TraceIntMax)
							{
							m_TraceIntProg *= -1;
							m_TraceInt = m_TraceIntMax;
							}

						if(m_TraceInt < m_TraceIntMin)
							{
							m_TraceIntProg *= -1;
							m_TraceInt = m_TraceIntMin;
							}
						}break;
					}
				}

			int m_Type;
			int m_TraceInt;
			int m_TraceIntMax;
			int m_TraceIntMin;
			int m_TraceIntProg;
			float m_TraceFloat;
			float m_TraceFloatMax;
			float m_TraceFloatMin;
			float m_TraceFloatProg;
			cube_Bit* m_cubeBit;
			int m_Depth;
		};

	class cube_Bit_container
		{
		public:
			cube_Bit_container()
				{
				m_vec_cube_Bit.clear();
				m_CurrentTrace = 0;
				m_CurrentSheet = 0;
				m_ChangeCount = 0;
				m_RefreshCount = 15;
				}

			cube_Bit_container(int f_RefreshCount)
				{
				m_vec_cube_Bit.clear();
				m_CurrentTrace = 0;
				m_CurrentSheet = 0;
				m_ChangeCount = 0;
				m_RefreshCount = f_RefreshCount;
				}

			~cube_Bit_container()
				{
				for(int count = 0; count < m_vec_cube_Bit.size(); count++)
					{
					delete m_vec_cube_Bit[count];
					}

				m_vec_cube_Bit.clear();
				m_CurrentTrace = 0;
				m_CurrentSheet = 0;
				m_ChangeCount = 0;
				}

			void acRefresh()
				{
				m_CurrentTrace = 0;
				m_CurrentSheet++;
				m_ChangeCount = 0;

				if(m_CurrentSheet > m_RefreshCount)
					{
					acReset();
					}
				else
					{
					for(int f_Count = 0; f_Count < (rand() % 5); f_Count++)
						{
						acProg();
						}
					}
				}

			void acReset()
				{
				for(int count = 0; count < m_vec_cube_Bit.size(); count++)
					{
					delete m_vec_cube_Bit[count];
					}

				m_vec_cube_Bit.clear();
				m_CurrentTrace = 0;
				m_CurrentSheet = 1;
				m_ChangeCount = 0;
				}

			void acRandomise()
				{
				for(int f_Count = 0; f_Count < m_vec_cube_Bit.size(); f_Count++)
					{
					m_vec_cube_Bit[f_Count]->acRandomise();
					}
				}

			void acProg()
				{
				for(int f_Count = 0; f_Count < m_vec_cube_Bit.size(); f_Count++)
					{
					m_vec_cube_Bit[f_Count]->acProg();
					}
				}
			
			std::vector<cube_Bit*> m_vec_cube_Bit;
			int m_CurrentTrace;
			int m_CurrentSheet;
			int m_ChangeCount;
			int m_RefreshCount;
		};

	extern float frac(float f_Float);
	extern float dot(float3 f_A, float3 f_B);
	extern PixelShaderInput visualminer(VertexShaderInput input);

	extern void agSet_offsetvec(float3 f_Vector);

	extern BicycleContainer g_BicycleContainer[1];
	extern std::vector<std::shared_ptr<CubeHESH>> g_HESH;

	extern void ag_AttachCube(CubeKEY* f_Target, CubeKEY* f_Subject, float f_Margin);

	extern CubeKEY* ChooseKEY(int f_Count = 1);

	extern bool agOpen(void);
	extern void agSave(void);
	extern void agSave(std::shared_ptr<CubeHESH> f_HESH);
	
	extern matrix g_model;
	extern matrix g_view;
	extern matrix g_projection;

	extern float3 g_RandomSeed;
	extern float3 g_offsetVec;

	extern float g_Float;

	extern BiVector g_eye;
	extern BiVector g_at;

	extern unMutexCC g_Applog_Muti;
	extern unMutexCC g_Mysql_Muti;
	extern unMutexCC g_Socket_Muti;
	extern unMutexCC g_Count_Muti;
	extern unMutexCC g_Share_Muti;
	extern unMutexCC g_Other_Muti;

	extern int g_BiStyleID;

	extern BiStyle* g_BiStyle;
	extern std::vector<BiStyle*> g_vec_BiStyles;

	extern std::shared_ptr<CubeHESH> ag_Hesh(std::string f_job);

	extern std::shared_ptr<Cube::CubeHESH> g_TargetedHesh;

	extern std::vector<Cube::CubeTransaction*> g_vec_Successfull_TX;

	extern Cube::CubeHeshExporter* g_CubeHeshExport;

	extern Cube::BiMeshContainer* g_MeshContainer;

	extern Cube::CubeTransaction* ag_getTX(int f_txid, int f_txoutid = -1);

	extern bool ag_VerifyTXIN(Cube::CubeTXIN* f_txin, float f_amount);

	extern Cube::CubeTransaction* ag_get_TXfromvout(std::string f_vout);

	extern float ag_OwnerBalance(std::string f_owner);

	extern void ag_UpdateOwnerBalance(std::string f_Owner, float f_Amount);

	extern std::shared_ptr<Cube::ShareContainer> ag_BuildPeerGraph(int f_JobID, int f_ServLay);

	extern std::shared_ptr<Cube::ShareContainer> ag_SelectPeerGraph(int f_JobID, int f_ServLay, int f_ShareID, int f_ShareOffset, int f_PEER);

	extern bool ag_BuildVecTier(std::shared_ptr<Cube::ShareContainer> f_ShareContainer);

	extern bool ag_makeGenesisCoin(void);

	extern bool ag_addGenesisTracking(int f_gnid);

	extern CKey* ag_GenerateAddressCube(int f_Prefix);

	extern int ag_GenerateTransaction(std::string f_A, std::string f_B, float f_amt, Cube::CubeTransaction* f_tx = nullptr);

	extern std::string ag_GatherTransactions(int f_JobID = 0);

	extern std::string ag_cont_VerifySingleTransaction(Cube::CubeTransaction* f_Transaction, bool f_initialVerified);

	extern std::string ag_cont_VerifyResult(Cube::CubeTransaction* f_Transaction, bool f_initialVerified);
};

#include "Code\Work\Contract.h"
#include "Code\Work\Schedular.h"

#include "Wallet\Wallet.h"