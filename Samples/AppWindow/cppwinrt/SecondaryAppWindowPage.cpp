/*

SecondaryAppWindowPage.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"
#include "SecondaryAppWindowPage.h"
#include "SecondaryAppWindowPage.g.cpp"

#include "Scenario1_SecondaryWindow.h"

#include "Wallet/Wallet.h"

using namespace ecoin;

bool g_Pressed = false;

namespace winrt::SDKTemplate::implementation
{
    SecondaryAppWindowPage::SecondaryAppWindowPage()
	{
		InitializeComponent();

		for(int f_Count = 0; f_Count < 60; f_Count++)
			{
			g_cubefield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_adifield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_blockfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_sharefield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_jobfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_jobvarfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_transfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_addrfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_eventfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_chancefield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_reffield[f_Count] = (char*)malloc(sizeof(char) * 1024);
			g_addrfield[f_Count] = (char*)malloc(sizeof(char) * 256);
			g_txinsyncfield[f_Count] = (char*)malloc(sizeof(char) * 256);
			g_txoutsyncfield[f_Count] = (char*)malloc(sizeof(char) * 256);
			g_syncfield[f_Count] = (char*)malloc(sizeof(char) * 256);
			}

		sprintf(g_chancefield[0], "chance");
		sprintf(g_chancefield[1], "srcshareid");
		sprintf(g_chancefield[2], "resshareid");
		sprintf(g_chancefield[3], "srcblockid");
		sprintf(g_chancefield[4], "resblockid");

		sprintf(g_reffield[0], "assetid");
		sprintf(g_reffield[1], "assetofficeid");
		sprintf(g_reffield[2], "username");
		sprintf(g_reffield[3], "hdid");
		sprintf(g_reffield[4], "level");
		sprintf(g_reffield[5], "access");
		sprintf(g_reffield[6], "shareid");
		sprintf(g_reffield[7], "status");
		sprintf(g_reffield[8], "jobid");
		sprintf(g_reffield[9], "blockid");
		sprintf(g_reffield[10], "comid");
		sprintf(g_reffield[11], "comment");
		sprintf(g_reffield[12], "score");
		sprintf(g_reffield[13], "category");
		sprintf(g_reffield[14], "owner");
		sprintf(g_reffield[15], "pledge");
		sprintf(g_reffield[16], "ecnpledge");

		sprintf(g_eventfield[0], "appid");
		sprintf(g_eventfield[1], "type");
		sprintf(g_eventfield[2], "shareid");
		sprintf(g_eventfield[3], "blockid");
		sprintf(g_eventfield[4], "score");
		sprintf(g_eventfield[5], "category");
		sprintf(g_eventfield[6], "owner");
		sprintf(g_eventfield[7], "pathowner");
		sprintf(g_eventfield[8], "reward");
		sprintf(g_eventfield[9], "pledge");
		sprintf(g_eventfield[10], "fee");

		for(int f_Int2 = 0; f_Int2 < 8; f_Int2++)
			{
			sprintf(g_cubefield[f_Int2 * 3], "vert%ix", f_Int2 + 1);
			sprintf(g_cubefield[(f_Int2 * 3) + 1], "vert%iy", f_Int2 + 1);
			sprintf(g_cubefield[(f_Int2 * 3) + 2], "vert%iz", f_Int2 + 1);
			}

		for(int f_Int3 = 0; f_Int3 < 8; f_Int3++)
			{
			sprintf(g_cubefield[(24 + (f_Int3 * 3))], "vert%ir", f_Int3 + 1);
			sprintf(g_cubefield[(24 + (f_Int3 * 3)) + 1], "vert%ig", f_Int3 + 1);
			sprintf(g_cubefield[(24 + (f_Int3 * 3)) + 2], "vert%ib", f_Int3 + 1);
			}

		sprintf(g_cubefield[48], "blockid");
		sprintf(g_cubefield[49], "shareid");
		sprintf(g_cubefield[50], "jobid");
		sprintf(g_cubefield[51], "eslid");
		sprintf(g_cubefield[52], "targetid");
		sprintf(g_cubefield[53], "eslcode");
		sprintf(g_cubefield[54], "difficulty");

		sprintf(g_adifield[0], "adindex");
		sprintf(g_adifield[1], "cubeindex");
		sprintf(g_adifield[2], "heshid");
	
		sprintf(g_blockfield[0], "mark");
		sprintf(g_blockfield[1], "assetid");
		sprintf(g_blockfield[2], "assetofficeid");
		sprintf(g_blockfield[3], "jobid");
		sprintf(g_blockfield[4], "eslid");
		sprintf(g_blockfield[5], "targetid");
		sprintf(g_blockfield[6], "shareid");
		sprintf(g_blockfield[7], "eslcode");
		sprintf(g_blockfield[8], "difficulty");
		sprintf(g_blockfield[9], "score");
		sprintf(g_blockfield[10], "maxvote");
		sprintf(g_blockfield[11], "blockledger");
		sprintf(g_blockfield[12], "owner");
		sprintf(g_blockfield[13], "shares");
		sprintf(g_blockfield[14], "bckred");
		sprintf(g_blockfield[15], "bckgreen");
		sprintf(g_blockfield[16], "bckblue");
		sprintf(g_blockfield[17], "reward");
		sprintf(g_blockfield[18], "pledge");
		sprintf(g_blockfield[19], "ecnpledge");
		sprintf(g_blockfield[20], "fee");
		sprintf(g_blockfield[21], "price");
		sprintf(g_blockfield[22], "blocktype");
		sprintf(g_blockfield[23], "breach");

		sprintf(g_sharefield[0], "mark");
		sprintf(g_sharefield[1], "markfloat");
		sprintf(g_sharefield[2], "assetid");
		sprintf(g_sharefield[3], "assetofficeid");
		sprintf(g_sharefield[4], "jobid");
		sprintf(g_sharefield[5], "jobboardid");
		sprintf(g_sharefield[6], "eslid");
		sprintf(g_sharefield[7], "targetid");
		sprintf(g_sharefield[8], "eslcode");
		sprintf(g_sharefield[9], "difficulty");
		sprintf(g_sharefield[10], "score");
		sprintf(g_sharefield[11], "maxvote");
		sprintf(g_sharefield[12], "shareledger");
		sprintf(g_sharefield[13], "jobledger");
		sprintf(g_sharefield[14], "owner");
		sprintf(g_sharefield[15], "bckred");
		sprintf(g_sharefield[16], "bckgreen");
		sprintf(g_sharefield[17], "bckblue");
		sprintf(g_sharefield[18], "comid");
		sprintf(g_sharefield[19], "reward");
		sprintf(g_sharefield[20], "pledge");
		sprintf(g_sharefield[21], "ecnpledge");
		sprintf(g_sharefield[22], "fee");
		sprintf(g_sharefield[23], "price");
		sprintf(g_sharefield[24], "blocktype");

		sprintf(g_jobfield[0], "assetofficeid");
		sprintf(g_jobfield[1], "targetid");
		sprintf(g_jobfield[2], "blockid");
		sprintf(g_jobfield[3], "blocktype");
		sprintf(g_jobfield[4], "eslcode");
		sprintf(g_jobfield[5], "pledgetype");
		sprintf(g_jobfield[6], "pledgemax");
		sprintf(g_jobfield[7], "targetbreach");
		sprintf(g_jobfield[8], "startbreach");
		sprintf(g_jobfield[9], "owner");
		sprintf(g_jobfield[10], "scoremax");
		sprintf(g_jobfield[11], "markmax");
		sprintf(g_jobfield[12], "markmin");
		sprintf(g_jobfield[13], "reward");
		sprintf(g_jobfield[14], "rewardid");

		sprintf(g_jobvarfield[0], "jobid");
		sprintf(g_jobvarfield[1], "name");
		sprintf(g_jobvarfield[2], "groupname");
		sprintf(g_jobvarfield[3], "value");

		sprintf(g_transfield[0], "assetid");
		sprintf(g_transfield[1], "assetofficeid");
		sprintf(g_transfield[2], "sender");
		sprintf(g_transfield[3], "recipient");
		sprintf(g_transfield[4], "jobid");
		sprintf(g_transfield[5], "confirmed");

		sprintf(g_addrfield[0], "assetid");
		sprintf(g_addrfield[1], "assetofficeid");
		sprintf(g_addrfield[2], "owner");
		sprintf(g_addrfield[3], "amt");

		sprintf(g_txinsyncfield[0], "transactionid");
		sprintf(g_txinsyncfield[1], "vout");
		sprintf(g_txinsyncfield[2], "pubkey");
		sprintf(g_txinsyncfield[3], "vsign");
		sprintf(g_txinsyncfield[4], "amt");
		sprintf(g_txinsyncfield[5], "gnshareid");

		sprintf(g_txoutsyncfield[0], "transactionid");
		sprintf(g_txoutsyncfield[1], "adrid");
		sprintf(g_txoutsyncfield[2], "owner");
		sprintf(g_txoutsyncfield[3], "txoutamt");
		sprintf(g_txoutsyncfield[4], "owneramt");
		sprintf(g_txoutsyncfield[5], "myelementcount");

		sprintf(g_syncfield[0], "status");
		sprintf(g_syncfield[1], "locktime");
		sprintf(g_syncfield[2], "confirmation");
		sprintf(g_syncfield[3], "hdid");
		sprintf(g_syncfield[4], "shareid");
		sprintf(g_syncfield[5], "gnshareid");
		sprintf(g_syncfield[6], "jobid");
		sprintf(g_syncfield[7], "rewardid");
		sprintf(g_syncfield[8], "blocktype");
		sprintf(g_syncfield[9], "hash");
		sprintf(g_syncfield[10], "hashnib");
		sprintf(g_syncfield[11], "amt");
		sprintf(g_syncfield[12], "fee");
		sprintf(g_syncfield[13], "reward");
		sprintf(g_syncfield[14], "owner");
		sprintf(g_syncfield[15], "blockid");
		sprintf(g_syncfield[16], "typed");

		g_Pressed = false;

		std::string f_ref_CurrentPath = g_ref_global_start + "SecondaryAppWindowPage::SecondaryAppWindowPage";

		 /////////////////
		// ecoinWallet
		ag_StatusLive(f_ref_CurrentPath, "g_Wallet", true);
		g_Wallet = std::make_shared_reflect<Wallet>();

		g_CubeHeshExport = std::make_shared<Cube::CubeHeshExporter>();

		ag_StatusLive(f_ref_CurrentPath, "g_QcomManager", true);
		g_QcomManager = std::make_shared_reflect<QcomManager>();

		ag_StatusLive(f_ref_CurrentPath, "g_Schedular[0]", true);
		g_Schedular[0] = std::make_shared_reflect<Schedular>();
		ag_StatusLive(f_ref_CurrentPath, "g_Schedular[1]", true);
		g_Schedular[1] = std::make_shared_reflect<Schedular>();
		ag_StatusLive(f_ref_CurrentPath, "g_Schedular[2]", true);
		g_Schedular[2] = std::make_shared_reflect<Schedular>();

#ifdef ECOIN_REFLECTION_EXP

		     /////////////////////////////////////////////////////////////////////////////////
		    //// Qcom Script Driven String PathName for Variable or Function Reflection. ////
		   //// Execute Programmatic Instant Reflection From Gathered NamePath          ////
		  //// [AQUIRE] mamQcom from last generated in QcomMngr->ag_MotherCom()        ////
		 ////     Path Syntax Readability in Debugger -> ":G:classmember:|:m_Member"  ////
		/////////////////////////////////////////////////////////////////////////////////

		std::string f_mamQcom_String = g_ref_global_start + "SecondaryAppWindowPage::SecondaryAppWindowPage:|:QcomManager::QcomManager:|:ag_MotherCom" + g_ref_Path_Div + "g_QcomManager->mam_Qcom" + g_ref_Div + "class Cube::Qcom" + g_ref_Div + "0" + g_ref_Div;

		if(g_vec_ecomRefBase.find(f_mamQcom_String) != g_vec_ecomRefBase.end())
			{
			 //////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////
			std::shared_ptr<ecom_base> f_mamQcom = g_vec_ecomRefBase[f_mamQcom_String];
			
			  ////////////////////////////////////////////
			 ////////////////////////////////////////////
			// MamQcom Member Boolean "m_HighLighted" //
			std::string f_MamCom_HighLighted_Bool_Str = "Qcom::Qcom" + g_ref_Div + "m_HighLighted";

			bool* f_HighLighted = f_mamQcom->m_Map_Bool[f_MamCom_HighLighted_Bool_Str];

			  /////////////////////////////////////////
			 /////////////////////////////////////////
			// MamQcom Member Boolean "m_Selected" //
			std::string f_Mam_Selected_Bool_Str = "Qcom::Qcom" + g_ref_Div + "m_Selected";

			bool* f_Selected = f_mamQcom->m_Map_Bool[f_Mam_Selected_Bool_Str];

			  ///////////////////////////////////////////////////////////////////////////////////////
			 /////////////-=={{{[[[[FUNCTION REFERENCE POINTERS]]]]}}}==-///////////////////////////
			///////////////////////////////////////////////////////////////////////////////////////

			    //////////////////////////////////////////
			   //////////////////////////////////////////
			  // [AQUIRE1] function "acHighLight" //
			 //////////////////////////////////////
			//////////////////////////////////////
			std::string f_acHighLlight_pach = "Qcom::Qcom" + g_ref_fun_Div + "acHighLight" + g_ref_fun_Append;

			//[INPUT]
			bool f_BoolHighLight = true;

			std::shared_ptr<FunctionBeam> f_BeamHighLight = std::make_shared<FunctionBeam>();

			//[PACH]
			f_BeamHighLight->ac_PachON(f_BoolHighLight);

			//[EXEC]
			f_mamQcom->ac_Invoke(f_acHighLlight_pach, f_BeamHighLight);

			    ///////////////////////////////////
			   ///////////////////////////////////
			  // CHECK [MamCom->m_HighLighted] //
			 ///////////////////////////////////
			///////////////////////////////////

			if(*(f_HighLighted) == true) //correct = true
				{
				__debugbreak();

				*(f_HighLighted) = false;

				__debugbreak();
				}
			else
				{
				__debugbreak();

				*(f_HighLighted) = true;

				__debugbreak();
				}

			   //------------------//--------//----------------------//////
			  ////////////////////////////////////////////////////////////
			 //-=(([AQUIRE2]))=- //function// -===[{acSelect}]===- //
			////////////////////////////////////////////////////////
			std::string f_acSelect_pach = "Qcom::Qcom" + g_ref_fun_Div + "acSelect" + g_ref_fun_Append;

			//[INPUT]
			bool f_BoolSelect = true;

			//[]
			std::shared_ptr<FunctionBeam> f_BeamSelect = std::make_shared<FunctionBeam>();

			//[PACH]
			f_BeamSelect->ac_PachON(f_BoolSelect);

			//[EXEC]
			f_mamQcom->ac_Invoke(f_acSelect_pach, f_BeamSelect);

			    ////////////////////////////////
			   ////////////////////////////////
			  // CHECK [MamCom->f_Selected] //
			 ////////////////////////////////
			////////////////////////////////

			if(*(f_Selected) == true) //correct = true
				{
				__debugbreak();

				*(f_Selected) = false;

				__debugbreak();
				}
			else 
				{
				__debugbreak();

				*(f_Selected) = true;

				__debugbreak();
				}

			  /////////////////////////////////////////////////////
			 //[AQUIRE] function ---=={[acSelectNone]}==--- //////
			/////////////////////////////////////////////////
			std::string f_acSelectNone = "Qcom::Qcom" + g_ref_fun_Div + "acSelectNone";

			//['0'INPUT!]//
			//['0'PACH!]//
			  
			  ///////////////////////
			 ///////////////////////
			//[EXEC] Select None //
			f_mamQcom->ac_Invoke(f_acSelectNone);
			 ////////////////////////////////////////////////
			////////////////////////////////////////////////

			    ////////////////////////////////
			   ////////////////////////////////
			  // CHECK [MamCom->f_Selected] //
			 ////////////////////////////////
			////////////////////////////////

			if(*(f_Selected) == true) //correct = true
				{
				__debugbreak();

				*(f_Selected) = false;

				__debugbreak();
				}
			else 
				{
				__debugbreak();

				*(f_Selected) = true;

				__debugbreak();
				}

			   ///////////////////////////////////////////////////////////////////////////////
			  /// Full Any Primary Variable Type. Reflected Reference Counted Object from ///
			 /// Map String -> ":G:Qcom::Qcom:|:m_HighLighted" /////////////////////////////
			/// Shown dialing single com highlighted on/off   /////////////////////////////
			std::string f_HL_Bool_MapString = "Qcom::Qcom" + g_ref_Div + "m_HighLighted";

			if(f_mamQcom->m_Map_Bool.find(f_HL_Bool_MapString) != f_mamQcom->m_Map_Bool.end())
				{
				__debugbreak();

				bool* f_Bool = f_mamQcom->m_Map_Bool[f_HL_Bool_MapString];

				__debugbreak();

				*(f_Bool) = true;

				__debugbreak();

				if(*(f_Bool) == true)
					{
					__debugbreak();

					*(f_Bool) = false;

					__debugbreak();
					}
				}
			}

#endif

		bool f_Live = true;
		int f_Int = 1;

		if(!g_SafeL[0])
			{
			ag_StatusLive(f_ref_CurrentPath, "g_SafeL[2]", true);
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

#ifdef ECOIN_PROCEDURE_UPLOAD
#ifdef ECOIN_PROCEDURE_RESET
		ag_Upload_Procedures(true);
#else
		ag_Upload_Procedures();
#endif
#endif

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
	}

	void SecondaryAppWindowPage::acClick(std::string f_ButtonName)
	{
		ag_Click(f_ButtonName);
	}

	fire_and_forget SecondaryAppWindowPage::OnStartecoin(IInspectable const& sender, winrt::RoutedEventArgs const&)
		{
		if(g_Pressed == false)
			{
			g_Pressed = true;

			std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

			acClick(f_buttonName);

			auto lifetime = get_strong();

			g_Wallet->m_Start = true;

			::winrt::Windows::Storage::Pickers::FileSavePicker savePicker;

			savePicker.SuggestedStartLocation(::winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);

			// Dropdown of file types the user can save the file as
			savePicker.FileTypeChoices().Insert(L"ecoin Wallet", winrt::single_threaded_vector<winrt::hstring>({ L".eco" }));

			// Default file name if the user does not type one in or select a file to replace
			savePicker.SuggestedFileName(L"ecoinWallet");

			::winrt::Windows::Storage::StorageFile file = co_await savePicker.PickSaveFileAsync();

			if(file != nullptr)
				{
				if(file.IsAvailable() == true)
					{
					  //////////////
					 // Start ECN-CPS
					//  Wallet
					std::string f_StringBuf = g_Wallet->Prepare_Start();

					g_Wallet->StartCPS();

					::winrt::Windows::Storage::CachedFileManager::DeferUpdates(file);

					// write to file
					await winrt::Windows::Storage::FileIO::WriteTextAsync(file, StrUsingStr(f_StringBuf));

					// Let Windows know that we're finished changing the file so the other app can update the remote version of the file.
					// Completing updates may require Windows to ask for user input.
					::winrt::Windows::Storage::Provider::FileUpdateStatus status = co_await ::winrt::Windows::Storage::CachedFileManager::CompleteUpdatesAsync(file);

					if(status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::Complete)
						{
						g_Wallet->m_OK = true;
						g_Wallet->m_Repeat = false;
						g_WalletOpen = true;
						}
					else if(status == ::winrt::Windows::Storage::Provider::FileUpdateStatus::CompleteAndRenamed)
						{
						g_Wallet->m_OK = true;
						g_Wallet->m_Repeat = false;
						g_WalletOpen = true;
						}
					else
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak();
#endif //add debug message
						}

					this->Frame().Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPageDX>());
					}
				}

			g_Pressed = false;
			}
		}


	fire_and_forget SecondaryAppWindowPage::OnClickOpenecoin(IInspectable const& sender, winrt::RoutedEventArgs const&)
		{
		if(g_Pressed == false)
			{
			g_Pressed = true;

			std::string f_ref_CurrentPath = "SecondaryAppWindowPage::OnClickOpenecoin";

			std::string f_buttonName = to_string(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());

			acClick(f_buttonName);

			auto lifetime = get_strong();

			g_Wallet->m_Start = false;

			::winrt::Windows::Storage::Pickers::FileOpenPicker openPicker;

			openPicker.ViewMode(::winrt::Windows::Storage::Pickers::PickerViewMode::Thumbnail);
			openPicker.SuggestedStartLocation(::winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
			openPicker.FileTypeFilter().Append({ L".eco" });

			::winrt::Windows::Storage::StorageFile file = co_await openPicker.PickSingleFileAsync();

			if(file != nullptr)
				{
				if(file.IsAvailable() == true)
					{
					int f_WalletVersion = 0;

					winrt::hstring fileContent = co_await winrt::Windows::Storage::FileIO::ReadTextAsync(file);
					std::string f_Char = to_string(fileContent);

					uint* f_Chk = new uint(0);

					if(f_Char.length() > 1)
						{
						g_WALLETBANK = acBufreadValueDouble(f_Char, f_Chk);
						ecoin::g_HESHSAVEID = acBufreadValueInteger(f_Char, f_Chk);
						acBufreadValueInteger(f_Char, f_Chk);

						f_WalletVersion = 1;

						g_Wallet->m_ChangeIdx = acBufreadValueInteger(f_Char, f_Chk);
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

							ag_StatusLive(f_ref_CurrentPath, "key");
							std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();

							for(int f_lm = 0; f_lm < 8; f_lm++)
								{
								key->keydata[f_lm] = f_p[f_lm];
								}

							key->m_prefix = f_prefix;
							key->m_owner = f_owner;
							key->m_pubkey = f_pubkey;
							g_Wallet->m_Bank_Adr = f_owner;

							g_Wallet->m_vec_Key.push_back(key);
							}
						else if(f_KeyNom == 1) //early version
							{
							f_WalletVersion = 2;

							std::string f_keypass = acBufreadValueString(f_Char, f_Chk);
							std::string f_pubkey = acBufreadValueString(f_Char, f_Chk);
							std::string f_owner = acBufreadValueString(f_Char, f_Chk);

							unsigned char *f_p = new unsigned char[8];
							Cube::ag_hex2bin(f_p, f_keypass.c_str(), f_keypass.size());

							ag_StatusLive(f_ref_CurrentPath, "key");
							std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();

							for(int f_lm = 0; f_lm < 8; f_lm++)
								{
								key->keydata[f_lm] = f_p[f_lm];
								}

							key->m_prefix = 1;
							key->m_owner = f_owner;
							key->m_pubkey = f_pubkey;
							g_Wallet->m_Bank_Adr = f_owner;

							g_Wallet->m_vec_Key.push_back(key);
							}
						
						for(int f_m = 1; f_m < f_KeyNom; f_m++)
							{
							int f_prefix = acBufreadValueInteger(f_Char, f_Chk);
							std::string f_keypass = acBufreadValueString(f_Char, f_Chk);
							std::string f_pubkey = acBufreadValueString(f_Char, f_Chk);
							std::string f_owner = acBufreadValueString(f_Char, f_Chk);

							unsigned char *f_p = new unsigned char[8];
							Cube::ag_hex2bin(f_p, f_keypass.c_str(), f_keypass.size());

							ag_StatusLive(f_ref_CurrentPath, "key");
							std::shared_ptr<CKey> key = std::make_shared_reflect<CKey>();

							for(int f_lm = 0; f_lm < 8; f_lm++)
								{
								key->keydata[f_lm] = f_p[f_lm];
								}

							key->m_prefix = f_prefix;
							key->m_owner = f_owner;
							key->m_pubkey = f_pubkey;

							g_Wallet->m_vec_Key.push_back(key);
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
							g_Wallet->m_Bank_ecoin = 0.0f;
							g_Wallet->m_Bank_ecoin_constant = 0.0f;
							g_WALLETBANK = 0.0f;
							g_HESHSAVEID = 0;
							//m_Bank_egold = 5000;

#ifndef DISABLE_ECC
							std::shared_ptr<CKey> f_1key = ag_GenerateAddress(1);

							g_Wallet->m_vec_Key.push_back(f_1key);

							g_Wallet->m_Bank_Adr = f_1key->m_owner;
#endif
							}
						case 2: //version 1
							{
							g_Wallet->m_ChangeIdx = 0;

#ifndef DISABLE_ECC
							std::shared_ptr<CKey> f_key = ag_GenerateAddress(2);

							g_Wallet->m_vec_Key.push_back(f_key);

							f_key = ag_GenerateAddress(2);

							g_Wallet->m_vec_Key.push_back(f_key);

							f_key = ag_GenerateAddress(2);

							g_Wallet->m_vec_Key.push_back(f_key);

							f_key = ag_GenerateAddress(2);

							g_Wallet->m_vec_Key.push_back(f_key);
#endif

							g_Wallet->m_Bank_ecoin = g_WALLETBANK;
							g_Wallet->m_Bank_ecoin_constant = 0.0f;
							g_Wallet->m_OK = true;
							g_Wallet->m_Repeat = false;

							printf("Wallet fully loaded OK updating...\n");

							g_Wallet->Update();
							};
						case 3:
							{
							g_Wallet->m_Bank_ecoin = g_WALLETBANK;
							g_Wallet->m_Bank_ecoin_constant = 0.0f;
							g_Wallet->m_OK = true;
							g_Wallet->m_Repeat = false;

							printf("Wallet fully loaded OK updating...\n");

							g_WalletOpen = true;
							}break;
						}

					this->Frame().Navigate(xaml_typename<SDKTemplate::SecondaryAppWindowPageDX>());
					}
				else
					{
					g_Wallet->m_Repeat = true;
					}
				}

			g_Pressed = false;
			}
		}

};
