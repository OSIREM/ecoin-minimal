/*

Cube&Bicycle - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"
//#include "Common\DirectXHelper.h"
#include "DirectXMath.h"

#include <math.h>

#include "Include/Cube.h"

#include "../Code/Work/Contract.h"
#include "../Code/Work/Schedular.h"

#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>

/*using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace Windows::Storage::Streams;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Media::Transcoding;
using namespace Windows::Media::MediaProperties;
using namespace Windows::UI::Xaml::Shapes;
using namespace Windows::UI::Xaml;
using namespace Windows::Storage::Provider;

using namespace Windows::Security::ExchangeActiveSyncProvisioning;
using namespace Windows::System::Profile;

using namespace concurrency;*/

using namespace Cube;
using namespace ecoin;

DirectX::XMVECTOR g_Origin;
BiMeshContainer* g_MeshContainer;
icSafeL* g_SafeL[3];

char* g_addrfield[60];
char* g_heshfield[60];
char* g_cubefield[60];
char* g_adifield[60];
char* g_sharefield[60];
char* g_blockfield[60];
char* g_transfield[60];
char* g_eventfield[60];
char* g_reffield[60];
char* g_chancefield[60];

int g_HeshFieldCount;
int g_CubeFieldCount;
int g_BlockFieldCount;
int g_TransFieldCount;

ULONGLONG g_TimeStamp;

std::random_device g_engine;

std::shared_ptr<CubeHESH> g_HESH_caddy;
bool g_GenerateCaddy = true;

namespace Cube
{
	picosha2::hash256_one_by_one g_hasha;

	float3 g_RandomSeed;
	int g_Fingat = CUBE_TRI_SHOT_A;
	float g_Float = 0.1;
	float g_swit = 0.75f;

	matrix g_model;
	matrix g_view;
	matrix g_projection;

	BiVector g_eye;
	BiVector g_at;

	std::vector<std::shared_ptr<Cube::CubeHESH>> g_HESH;

	BicycleContainer g_BicycleContainer[1];

	float3 g_offsetVec;

	unMutexCC g_Applog_Muti;
	unMutexCC g_Mysql_Muti;
	unMutexCC g_Socket_Muti;
	unMutexCC g_Count_Muti;
	unMutexCC g_Share_Muti;
	unMutexCC g_Other_Muti;

	int g_BiStyleID = 0;
	BiStyle* g_BiStyle;
	std::vector<BiStyle*> g_vec_BiStyles;

	void seedrand(int f_Seed)
		{
		srand(f_Seed);
		}

	int randTape(void)
		{
		return (int)rand();
		}

	int randomTape(void)
		{
		return (float)rand() / 32767;
		}

	int randomFac(void)
		{
		float f_Rand_Max = RAND_MAX;
		float f_Result = (float)Cube::random() * (float)f_Rand_Max;
		int f_Int = f_Result;
		return f_Int;
		}

	float random(void)
		{
		unsigned int f_x = g_engine();

		float f_xy = (float)((float)f_x / (float)UINT_MAX);

		return f_xy;
		}

	CubeKEY* ChooseKEY(int f_Count)
		{
		int f_Index = Cube::randomFac() % g_BicycleContainer[0].vec_Key.size();

		Cube::CubeKEY* f_KEY = g_BicycleContainer[0].vec_Key[f_Index];

		return f_KEY;
		}

	void BicycleContainer::ac_IsOK(void)
		{
		int f_StorePos = 0;
		for(int f_Jet = 0; f_Jet < g_BicycleContainer[0].vec_Key.size(); f_Jet++)
			{
			CubeKEY* f_Key = g_BicycleContainer[0].vec_Key[f_Jet];

			bool f_GradePass = true;

			if(f_Key->m_Link->vec_Vertex.size() != 8)
				{
				f_GradePass = false;
				}

			if(f_Key->m_Link->vec_Color.size() != 8)
				{
				f_GradePass = false;
				}

			if(!f_GradePass)
				{
				for(int f_Veh = f_Jet; f_Veh < g_BicycleContainer[0].vec_Key.size() - 1; f_Veh++)
					{
					g_BicycleContainer[0].vec_Key[f_Veh] = g_BicycleContainer[0].vec_Key[f_Veh + 1];
					}

				g_BicycleContainer[0].vec_Key.pop_back();
				}
			}
		}

	CubeHESH::CubeHESH(FILE* f_File)
		{
#if 0
		m_Timestamp = acBufreadValueUL(f_File);

		m_ID = acBufreadValueInteger(f_File);

		m_RotateX = acBufreadValueFloat(f_File);

		m_RotateY = acBufreadValueFloat(f_File);

		m_RotateZ = acBufreadValueFloat(f_File);

		int f_AdSize = acBufreadValueInteger(f_File);

		for(int f_I = 0; f_I < f_AdSize; f_I++)
			{
			int f_Ad = acBufreadValueInteger(f_File);
			m_adIndex.push_back(f_Ad);
			}

		int f_BiSize = acBufreadValueInteger(f_File);

		for(int f_I = 0; f_I < f_BiSize; f_I++)
			{
			shared_ptr<CubeBicycle> f_CB = new CubeBicycle(f_File);
			vec_Bicycle.push_back(f_CB);
			}

		m_ValueBank = acBufreadValueDouble(f_File);
#endif
		}

	CubeHESH::CubeHESH(std::string f_Buffer)
		{
#if 0
		m_Timestamp = acBufreadValueUL((char *)f_Buffer.c_str());

		m_ID = acBufreadValueInteger((char *)f_Buffer.c_str());

		m_RotateX = acBufreadValueFloat((char *)f_Buffer.c_str());

		m_RotateY = acBufreadValueFloat((char *)f_Buffer.c_str());

		m_RotateZ = acBufreadValueFloat((char *)f_Buffer.c_str());

		int f_AdSize = acBufreadValueInteger((char *)f_Buffer.c_str());

		for(int f_I = 0; f_I < f_AdSize; f_I++)
			{
			int f_Ad = acBufreadValueInteger((char *)f_Buffer.c_str());
			m_adIndex.push_back(f_Ad);
			}

		int f_BiSize = acBufreadValueInteger((char *)f_Buffer.c_str());

		for(int f_I = 0; f_I < f_BiSize; f_I++)
			{
			shared_ptr<CubeBicycle> f_CB = new CubeBicycle(f_Buffer);
			vec_Bicycle.push_back(f_CB);
			}

		m_ValueBank = acBufreadValueDouble((char *)f_Buffer.c_str());
#endif
		}

	void CubeHESH::acSerialise(std::string* f_String)
		{
		acBufwriteValueUL(f_String, m_Timestamp);

		acBufwriteValueInteger(f_String, m_ID);

		acBufwriteValueFloat(f_String, m_RotateX);

		acBufwriteValueFloat(f_String, m_RotateY);

		acBufwriteValueFloat(f_String, m_RotateZ);

		acBufwriteValueInteger(f_String, m_adIndex.size());

		for(int f_I = 0; f_I < m_adIndex.size(); f_I++)
			{
			acBufwriteValueInteger(f_String, m_adIndex[f_I]);
			}

		acBufwriteValueInteger(f_String, vec_Bicycle.size());

		for(int f_I = 0; f_I < vec_Bicycle.size(); f_I++)
			{
			vec_Bicycle[f_I]->acSerialise(f_String);
			}

		acBufwriteValueDouble(f_String, g_WALLETBANK);

		const char f_Char = '\n';

		*(f_String) = *(f_String)+f_Char;
		}

	void CubeBicycle::acSerialise(std::string* f_String)
		{
		acBufwriteValueInteger(f_String, vec_Vertex.size());

		for(int f_I = 0; f_I < vec_Vertex.size(); f_I++)
			{
			acBufwriteValueFloat(f_String, vec_Vertex[f_I].m_X);

			acBufwriteValueFloat(f_String, vec_Vertex[f_I].m_Y);

			acBufwriteValueFloat(f_String, vec_Vertex[f_I].m_Z);
			}

		acBufwriteValueInteger(f_String, vec_Color.size());

		for(int f_C = 0; f_C < vec_Color.size(); f_C++)
			{
			acBufwriteValueFloat(f_String, vec_Color[f_C].m_X);

			acBufwriteValueFloat(f_String, vec_Color[f_C].m_Y);

			acBufwriteValueFloat(f_String, vec_Color[f_C].m_Z);
			}
		}

	CubeBicycle::CubeBicycle(FILE* f_File)
		{
		int f_VertSize = acBufreadValueInteger(f_File);

		for(int f_I = 0; f_I < f_VertSize; f_I++)
			{
			Cube::BiVector f_Vector;

			f_Vector.m_X = acBufreadValueFloat(f_File);

			f_Vector.m_Y = acBufreadValueFloat(f_File);

			f_Vector.m_Z = acBufreadValueFloat(f_File);

			vec_Vertex.push_back(f_Vector);
			}

		int f_ColorSize = acBufreadValueInteger(f_File);

		for(int f_C = 0; f_C < f_ColorSize; f_C++)
			{
			Cube::BiVector f_Color;

			f_Color.m_X = acBufreadValueFloat(f_File);

			f_Color.m_Y = acBufreadValueFloat(f_File);

			f_Color.m_Z = acBufreadValueFloat(f_File);

			vec_Color.push_back(f_Color);
			}
		}

	CubeBicycle::CubeBicycle(std::string f_Buffer)
		{
		int f_VertSize = acBufreadValueInteger((char *)f_Buffer.c_str());

		for(int f_I = 0; f_I < f_VertSize; f_I++)
			{
			Cube::BiVector f_Vector;

			f_Vector.m_X = acBufreadValueFloat((char *)f_Buffer.c_str());

			f_Vector.m_Y = acBufreadValueFloat((char *)f_Buffer.c_str());

			f_Vector.m_Z = acBufreadValueFloat((char *)f_Buffer.c_str());

			vec_Vertex.push_back(f_Vector);
			}

		int f_ColorSize = acBufreadValueInteger((char *)f_Buffer.c_str());

		for(int f_C = 0; f_C < f_ColorSize; f_C++)
			{
			Cube::BiVector f_Color;

			f_Color.m_X = acBufreadValueFloat((char *)f_Buffer.c_str());

			f_Color.m_Y = acBufreadValueFloat((char *)f_Buffer.c_str());

			f_Color.m_Z = acBufreadValueFloat((char *)f_Buffer.c_str());

			vec_Color.push_back(f_Color);
			}
		}

	void agSave(std::shared_ptr<CubeHESH> f_HESH)
		{
#if 0
		g_Wallet->UpdateHesh();
#endif

#if 0
		if(g_File != nullptr)
			{
			// Prevent updates to the remote version of the g_File until we finish making changes and call CompleteUpdatesAsync.
			CachedFileManager::DeferUpdates(g_File);
			// write to file
			Concurrency::create_task(FileIO::AppendTextAsync(g_File, f_StringBuf)).then([]()
				{
				// Let Windows know that we're finished changing the g_File so the other app can update the remote version of the g_File.
				// Completing updates may require Windows to ask for user input.
				Concurrency::create_task(CachedFileManager::CompleteUpdatesAsync(g_File)).then([](FileUpdateStatus status)
					{
					int x = 5;
					});
				});
			}
#endif
		}

	void agSave(void)
		{
		//Windows::Storage::StorageFolder^ localFolder2 = Windows::Storage::ApplicationData::Current->LocalFolder;

		/*std::string f_LocalPathString2 = to_string(localFolder2->Path);
		std::string f_SettingsString2 = "bank1";
		std::string f_SettingsPathString2 = "\\";
		std::string f_BackString2 = "\\";
		std::string f_DotString2 = ".";
		std::string f_ExtensionString2 = "bank";

		std::string f_CombineResult2 = f_LocalPathString2 + f_SettingsPathString2 + f_SettingsString2 + f_DotString2 + f_ExtensionString2;

		FILE* f_FileADV = nullptr;

		fopen_s(&f_FileADV, f_CombineResult2.c_str(), "w");

		if(f_FileADV)
			{
			fprintf(f_FileADV, "%.15f %i \n", g_WALLETBANK, g_HESH.size());
			fclose(f_FileADV);
			}*/
		}

	bool agOpen(void)
		{
		/*Windows::Storage::StorageFolder^ localFolder2 = Windows::Storage::ApplicationData::Current->LocalFolder;

		std::string f_LocalPathString2 = to_string(localFolder2->Path);
		std::string f_SettingsString2 = "bank1";
		std::string f_SettingsPathString2 = "\\";
		std::string f_BackString2 = "\\";
		std::string f_DotString2 = ".";
		std::string f_ExtensionString2 = "bank";

		std::string f_CombineResult2 = f_LocalPathString2 + f_SettingsPathString2 + f_SettingsString2 + f_DotString2 + f_ExtensionString2;

		FILE* f_Char = NULL;
		fopen_s(&f_Char, f_CombineResult2.c_str(), "r");

		if(f_Char != NULL)
			{
			g_WALLETBANK = acBufreadValueDouble(f_Char);
			g_StoreWALLETBANK = g_WALLETBANK;

			g_ID = acBufreadValueInteger(f_Char);

			g_SelectedHeshID = acBufreadValueInteger(f_Char);

			fclose(f_Char);
			}
		else
			{
			agSave();

			return false;
			}

#if 1
		std::string f_SettingsString = "hesh1";
		std::string f_SettingsPathString = "\\";
		std::string f_BackString = "\\";
		std::string f_DotString = ".";
		std::string f_ExtensionString = "hesh";

		std::string f_CombineResult = f_LocalPathString2 + f_SettingsPathString + f_SettingsString + f_DotString + f_ExtensionString;

		f_Char = NULL;
		fopen_s(&f_Char, f_CombineResult2.c_str(), "r");

		if(f_Char != NULL)
			{
			for(int f_Count = 0; f_Count < g_ID; f_Count++)
				{
				std::shared_ptr<CubeHESH> f_HESH = new CubeHESH(f_Char);

				f_HESH->m_ID = f_Count;

				g_HESH.push_back(f_HESH);
				}

			fclose(f_Char);
			}

		g_SelectedHeshID = g_HESH.size() - 1;
		g_ID = g_SelectedHeshID;
#endif*/

		return true;
		}

	  /////////////////////////
	 /// START Cubetronics ///
	/////////////////////////

	float frac(float f_Float)
		{
		float f_Result = 0.0f;
#if 1
		f_Result = f_Float - truncf(f_Float);
#else
		f_Result = random();
#endif
		return f_Result;
		}

	float dot(float3 f_A, float3 f_B)
		{
		float f_Result;
		f_Result = (f_A.x * f_B.x) + (f_A.y * f_B.y) + (f_A.z * f_B.z);
		return f_Result;
		}
	
	PixelShaderInput visualminer(VertexShaderInput input)
		{
		PixelShaderInput output;

		float3 f_Rand = float3(CUBE_RAND3);

		//float f_A = random() * 3.142 * ((atan2(random(), 1 - (random() + random()) * ((max(random(), random()) * random() * random()) * 3.142) + ((atan2(random(), random() + 3.142)))) * random()));

		float f_A = frac(sin(dot(f_Rand, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
		f_Rand = float3(CUBE_RAND3);

		float f_B = frac(sin(dot(f_Rand, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
		f_Rand = float3(CUBE_RAND3);

		float f_C = frac(sin(dot(f_Rand, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
		f_Rand = float3(CUBE_RAND3);

		float4 pos = float4(input.pos.x, input.pos.y, input.pos.z, 1.0f);

		// Transform the vertex position into projected space.
		//pos = g_model * pos;
		//pos = g_view * pos;
		//pos = g_projection * pos;

		f_Rand = float3(CUBE_RAND3);
		float f_A2 = frac(sin(dot(f_Rand, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
		f_Rand = float3(CUBE_RAND3);
		float f_B2 = frac(sin(dot(f_Rand, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
		f_Rand = float3(CUBE_RAND3);
		float f_C2 = frac(sin(dot(f_Rand, float3(12.9898, 78.233, 45.5432))) * 43758.5453);

		// Pass the color through without modification.
		output.color = float3(input.color.r * sin(f_B * f_C) * 5, input.color.g * sin(f_C * f_A) * 5, input.color.b * sin(f_B * f_B) * 5);

		//output.pos = float4(pos.x * f_C2 * 0.5, pos.y * f_B2 * 0.5, pos.z * f_A2 * 0.5, pos.w);

		output.pos = float4(pos.x + g_offsetVec.x, pos.y + g_offsetVec.y, pos.z + g_offsetVec.z, pos.w);

		input.pos.x = output.pos.x;
		input.pos.y = output.pos.y;
		input.pos.z = output.pos.z;
		input.color = output.color.r;
		input.color = output.color.g;
		input.color = output.color.b;

#if 1
		if(g_Contract)
			{
			output = g_Contract->getWork(input);
			}
#endif

		return output;
		}

	Carriage agRun_visualminer(float f_X, float f_Y, float f_Z)
		{
		Carriage f_Result;
		PixelShaderInput f_OUT;
		VertexShaderInput f_IN;

		f_IN.pos.x = f_X;
		f_IN.pos.y = f_Y;
		f_IN.pos.z = f_Z;
		f_IN.color.r = 0.0f;
		f_IN.color.g = 0.0f;
		f_IN.color.b = 0.0f;

		f_OUT = visualminer(f_IN);

		f_Result.m_X = f_OUT.pos.x;
		f_Result.m_Y = f_OUT.pos.y;
		f_Result.m_Z = f_OUT.pos.z;

		return f_Result;
		}

	void agSet_offsetvec(float3 f_Vector)
		{
		g_offsetVec = f_Vector;
		}

	void CubeKEY::acPush(int f_Type)
		{
		switch(f_Type)
			{
			case CUBE_LOG_PUSHBACK:
				{
				int f_Children = nom_Child;
				while (f_Children > 0)
					{
					m_Link->avPushBack(-1);
					vec_Log.push_back(CUBE_LOG_PUSHBACK);

#ifdef CUBE_LAYER
					vec_Child[f_Children]->acPush(CUBE_LOG_PUSHBACK);
#endif

					f_Children--;
					}
				}break;

			case CUBE_LOG_PULLFORD:
				{
				int f_Children = nom_Child;
				while (f_Children > 0)
					{
					m_Link->avPushBack(1);
					vec_Log.push_back(CUBE_LOG_PULLFORD);

#ifdef CUBE_LAYER
					vec_Child[f_Children]->acPush(CUBE_LOG_PULLFORD);
#endif

					f_Children--;
					}
				}break;

			case CUBE_LOG_GROW:
				{
				int f_Children = nom_Child;
				while (f_Children > 0)
					{
					m_Link->avGrow((Cube::random() + 1) * 5.0);
					vec_Log.push_back(CUBE_LOG_GROW);

#ifdef CUBE_LAYER
					vec_Child[f_Children]->acPush(CUBE_LOG_GROW);
#endif

					f_Children--;
					}
				}break;

			case CUBE_LOG_SHRINK:
				{
				int f_Children = nom_Child;
				while (f_Children > 0)
					{
					m_Link->avGrow(Cube::random());
					vec_Log.push_back(CUBE_LOG_SHRINK);

#ifdef CUBE_LAYER
					vec_Child[f_Children]->acPush(CUBE_LOG_SHRINK);
#endif

					f_Children--;
					}
				}break;
			}
		}

	void BicycleContainer::avStage(void)
		{
		unsigned int f_Puck = 0;
		while(f_Puck < CUBE_PUCK_BASE)
			{ /////////
			 /////////
			// Rand
			int f_RandBase = (Cube::randomFac() % 50);

			int f_RandAlpha = (Cube::randomFac() % vec_Key.size());
			int f_RandBeta = (Cube::randomFac() % vec_Key.size());
			int f_RandGamma = (Cube::randomFac() % vec_Key.size());
			int f_RandDelta = (Cube::randomFac() % vec_Key.size());

			if(f_RandBase >= 30)
				{
				vec_Key[f_RandAlpha]->acPush(CUBE_LOG_PUSHBACK);
				vec_Key[f_RandBeta]->acPush(CUBE_LOG_PULLFORD);
				vec_Key[f_RandGamma]->acPush(CUBE_LOG_GROW);
				vec_Key[f_RandDelta]->acPush(CUBE_LOG_SHRINK);
				}
			else
				{
				if(f_RandBase >= 0)
					{
					ag_AttachCube(vec_Key[f_RandAlpha], vec_Key[f_RandBeta], 0.2);
					ag_AttachCube(vec_Key[f_RandGamma], vec_Key[f_RandDelta], 0.2);
					ag_AttachCube(vec_Key[f_RandGamma], vec_Key[f_RandBeta], 0.2);
					}
				}

			if(f_RandBase >= 45)
				{
				f_Puck++;
				}
			}
		}

#if 0
	void CubeBicycle::acRefresh(void)
		{
		if (m_Refresh)
			{
			m_Refresh = false;

			GLfloat vertexPositions[] =
				{
				vec_Vertex[0].m_X, vec_Vertex[0].m_Y, vec_Vertex[0].m_Z, vec_Vertex[1].m_X, vec_Vertex[1].m_Y, vec_Vertex[1].m_Z, vec_Vertex[2].m_X, vec_Vertex[2].m_Y, vec_Vertex[2].m_Z,
				vec_Vertex[1].m_X, vec_Vertex[1].m_Y, vec_Vertex[1].m_Z, vec_Vertex[3].m_X, vec_Vertex[3].m_Y, vec_Vertex[3].m_Z, vec_Vertex[2].m_X, vec_Vertex[2].m_Y, vec_Vertex[2].m_Z,
				vec_Vertex[4].m_X, vec_Vertex[4].m_Y, vec_Vertex[4].m_Z, vec_Vertex[6].m_X, vec_Vertex[6].m_Y, vec_Vertex[6].m_Z, vec_Vertex[5].m_X, vec_Vertex[5].m_Y, vec_Vertex[5].m_Z,
				vec_Vertex[5].m_X, vec_Vertex[5].m_Y, vec_Vertex[5].m_Z, vec_Vertex[6].m_X, vec_Vertex[6].m_Y, vec_Vertex[6].m_Z, vec_Vertex[7].m_X, vec_Vertex[7].m_Y, vec_Vertex[7].m_Z,
				vec_Vertex[0].m_X, vec_Vertex[0].m_Y, vec_Vertex[0].m_Z, vec_Vertex[5].m_X, vec_Vertex[5].m_Y, vec_Vertex[5].m_Z, vec_Vertex[1].m_X, vec_Vertex[1].m_Y, vec_Vertex[1].m_Z,
				vec_Vertex[0].m_X, vec_Vertex[0].m_Y, vec_Vertex[0].m_Z, vec_Vertex[4].m_X, vec_Vertex[4].m_Y, vec_Vertex[4].m_Z, vec_Vertex[5].m_X, vec_Vertex[5].m_Y, vec_Vertex[5].m_Z,
				vec_Vertex[2].m_X, vec_Vertex[2].m_Y, vec_Vertex[2].m_Z, vec_Vertex[7].m_X, vec_Vertex[7].m_Y, vec_Vertex[7].m_Z, vec_Vertex[6].m_X, vec_Vertex[6].m_Y, vec_Vertex[6].m_Z,
				vec_Vertex[2].m_X, vec_Vertex[2].m_Y, vec_Vertex[2].m_Z, vec_Vertex[3].m_X, vec_Vertex[3].m_Y, vec_Vertex[3].m_Z, vec_Vertex[7].m_X, vec_Vertex[7].m_Y, vec_Vertex[7].m_Z,
				vec_Vertex[0].m_X, vec_Vertex[0].m_Y, vec_Vertex[0].m_Z, vec_Vertex[6].m_X, vec_Vertex[6].m_Y, vec_Vertex[6].m_Z, vec_Vertex[4].m_X, vec_Vertex[4].m_Y, vec_Vertex[4].m_Z,
				vec_Vertex[0].m_X, vec_Vertex[0].m_Y, vec_Vertex[0].m_Z, vec_Vertex[2].m_X, vec_Vertex[2].m_Y, vec_Vertex[2].m_Z, vec_Vertex[6].m_X, vec_Vertex[6].m_Y, vec_Vertex[6].m_Z,
				vec_Vertex[1].m_X, vec_Vertex[1].m_Y, vec_Vertex[1].m_Z, vec_Vertex[7].m_X, vec_Vertex[7].m_Y, vec_Vertex[7].m_Z, vec_Vertex[3].m_X, vec_Vertex[3].m_Y, vec_Vertex[3].m_Z,
				vec_Vertex[1].m_X, vec_Vertex[1].m_Y, vec_Vertex[1].m_Z, vec_Vertex[5].m_X, vec_Vertex[5].m_Y, vec_Vertex[5].m_Z, vec_Vertex[7].m_X, vec_Vertex[7].m_Y, vec_Vertex[7].m_Z
				};

			glGenBuffers(1, &mVertexPositionBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

			GLfloat vertexColors[] =
				{
				vec_Color[0].m_X, vec_Color[0].m_Y, vec_Color[0].m_Z, vec_Color[1].m_X, vec_Color[1].m_Y, vec_Color[1].m_Z, vec_Color[2].m_X, vec_Color[2].m_Y, vec_Color[2].m_Z,
				vec_Color[1].m_X, vec_Color[1].m_Y, vec_Color[1].m_Z, vec_Color[3].m_X, vec_Color[3].m_Y, vec_Color[3].m_Z, vec_Color[2].m_X, vec_Color[2].m_Y, vec_Color[2].m_Z,
				vec_Color[4].m_X, vec_Color[4].m_Y, vec_Color[4].m_Z, vec_Color[6].m_X, vec_Color[6].m_Y, vec_Color[6].m_Z, vec_Color[5].m_X, vec_Color[5].m_Y, vec_Color[5].m_Z,
				vec_Color[5].m_X, vec_Color[5].m_Y, vec_Color[5].m_Z, vec_Color[6].m_X, vec_Color[6].m_Y, vec_Color[6].m_Z, vec_Color[7].m_X, vec_Color[7].m_Y, vec_Color[7].m_Z,
				vec_Color[0].m_X, vec_Color[0].m_Y, vec_Color[0].m_Z, vec_Color[5].m_X, vec_Color[5].m_Y, vec_Color[5].m_Z, vec_Color[1].m_X, vec_Color[1].m_Y, vec_Color[1].m_Z,
				vec_Color[0].m_X, vec_Color[0].m_Y, vec_Color[0].m_Z, vec_Color[4].m_X, vec_Color[4].m_Y, vec_Color[4].m_Z, vec_Color[5].m_X, vec_Color[5].m_Y, vec_Color[5].m_Z,
				vec_Color[2].m_X, vec_Color[2].m_Y, vec_Color[2].m_Z, vec_Color[7].m_X, vec_Color[7].m_Y, vec_Color[7].m_Z, vec_Color[6].m_X, vec_Color[6].m_Y, vec_Color[6].m_Z,
				vec_Color[2].m_X, vec_Color[2].m_Y, vec_Color[2].m_Z, vec_Color[3].m_X, vec_Color[3].m_Y, vec_Color[3].m_Z, vec_Color[7].m_X, vec_Color[7].m_Y, vec_Color[7].m_Z,
				vec_Color[0].m_X, vec_Color[0].m_Y, vec_Color[0].m_Z, vec_Color[6].m_X, vec_Color[6].m_Y, vec_Color[6].m_Z, vec_Color[4].m_X, vec_Color[4].m_Y, vec_Color[4].m_Z,
				vec_Color[0].m_X, vec_Color[0].m_Y, vec_Color[0].m_Z, vec_Color[2].m_X, vec_Color[2].m_Y, vec_Color[2].m_Z, vec_Color[6].m_X, vec_Color[6].m_Y, vec_Color[6].m_Z,
				vec_Color[1].m_X, vec_Color[1].m_Y, vec_Color[1].m_Z, vec_Color[7].m_X, vec_Color[7].m_Y, vec_Color[7].m_Z, vec_Color[3].m_X, vec_Color[3].m_Y, vec_Color[3].m_Z,
				vec_Color[1].m_X, vec_Color[1].m_Y, vec_Color[1].m_Z, vec_Color[5].m_X, vec_Color[5].m_Y, vec_Color[5].m_Z, vec_Color[7].m_X, vec_Color[7].m_Y, vec_Color[7].m_Z
				};

			glGenBuffers(1, &mVertexColorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

			GLfloat vertexNormals[] =
				{
				-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
				-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
				0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
				0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
				0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
				};

			glGenBuffers(1, &mVertexNormalBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexNormals), vertexNormals, GL_STATIC_DRAW);

			short indices[] =
				{
				0, 1, 2, // -x
				3, 4, 5,
				6, 7, 8, // +x
				9, 10, 11,
				12, 13, 14, // -y
				15, 16, 17,
				18, 19, 20, // +y
				21, 22, 23,
				24, 25, 26, // -z
				27, 28, 29,
				30, 31, 32, // +z
				33, 34, 35,
				};

			glGenBuffers(1, &mIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			}
		}
#endif
#if 0
	void pMesh::compute_normals(float f_UVFactor, int mode)
		{
		int i,j,k;
		pVector v0,v1,v2;
		pVertex *vv0,*vv1,*vv2;

		if (mode&P_COMPUTE_FACENORM)
		{
			k=0;
			for( i=0;i<nface;i++,k+=3 )
			{
				vv0=&vert[facevert[k]];
				vv1=&vert[facevert[k+1]];
				vv2=&vert[facevert[k+2]];
				v0.vec(vv0->pos[0],vv0->pos[1],vv0->pos[2]);
				v1.vec(vv1->pos[0],vv1->pos[1],vv1->pos[2]);
				v2.vec(vv2->pos[0],vv2->pos[1],vv2->pos[2]);

				v1=v1-v0;
				v2=v2-v0;

				face[i].face_normal.cross(v1,v2);
				face[i].face_normal.normalize();
				face[i].face_normal.w=VECDOT(face[i].face_normal,v0);
			}
		}

		if (mode&P_COMPUTE_VERTNORM)
		{
			pVector d1,d2;
			float f;

			for( i=0;i<nvert;i++ )
				vert[i].norm[0]=vert[i].norm[1]=vert[i].norm[2]=0;

			k=0;
			for( i=0;i<nface;i++,k+=3 )
				for( j=0;j<3;j++ )
				{
					vv0=&vert[facevert[k+j]];
					vv1=&vert[facevert[k+((j+1)%3)]];
					vv2=&vert[facevert[k+((j+2)%3)]];
					v0.vec(vv0->pos[0],vv0->pos[1],vv0->pos[2]);
					v1.vec(vv1->pos[0],vv1->pos[1],vv1->pos[2]);
					v2.vec(vv2->pos[0],vv2->pos[1],vv2->pos[2]);

					d1=v1-v0;
					d2=v2-v0;
					d1.normalize();
					d2.normalize();
				
					f=VECDOT(d1,d2);
					f=acosf(f);
					vv0->norm[0]+=f*face[i].face_normal.x;
					vv0->norm[1]+=f*face[i].face_normal.y;
					vv0->norm[2]+=f*face[i].face_normal.z;
				}
		
			for( i=0;i<nvert;i++ )
			{
				f=sqrtf(
						vert[i].norm[0]*vert[i].norm[0]+
						vert[i].norm[1]*vert[i].norm[1]+
						vert[i].norm[2]*vert[i].norm[2]);
				if (f>0.01f)
				{
					f=1.0f/f;
					vert[i].norm[0]*=f;
					vert[i].norm[1]*=f;
					vert[i].norm[2]*=f;
				}
			}
		}

		if (mode&P_COMPUTE_TANGENTS)
			compute_tangents();

		if (mode&P_COMPUTE_CURVATURE)
			compute_curvature();

		if (mode&P_COMPUTE_BBOX)
		{
			bbox.reset();
			for( i=0;i<nvert;i++ )
				bbox.add_point(vert[i].pos);
		}

		update_buffers(f_UVFactor);
		}
#endif

	std::shared_ptr<CubeHESH> agGenerateHesh(void)
		{
		std::shared_ptr<CubeHESH> f_Hesh = std::make_shared<CubeHESH>();

		g_Schedular[0]->getWork(ESL_PATTERN_LAST);

		g_Contract->prepWork();

		for(int f_Int = 0; f_Int < CUBE_HESH_SIZE; f_Int++)
			{
			std::shared_ptr<CubeBicycle> f_Bicycle = std::make_shared<CubeBicycle>();

			// Load mesh vertices. Each vertex has a position and a color.
			Cube::BiRand f_BiRand;
			Cube::BiVector f_Vector1(-0.5f);
			f_Vector1.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector2(-0.5f, -0.5f, 0.5f);
			f_Vector2.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector3(-0.5f, 0.5f, -0.5f);
			f_Vector3.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector4(-0.5f, 0.5f, 0.5f);
			f_Vector4.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector5(0.5f, -0.5f, -0.5f);
			f_Vector5.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector6(0.5f, -0.5f, 0.5f);
			f_Vector6.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector7(0.5f, 0.5f, -0.5f);
			f_Vector7.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector8(0.5f, 0.5f, 0.5f);
			f_Vector8.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

			Cube::BiVector f_Color1(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color2(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color3(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color4(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color5(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color6(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color7(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color8(Cube::random(), Cube::random(), Cube::random());

			Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

			f_Vector1.acRun_visualminer();
			f_Vector2.acRun_visualminer();
			f_Vector3.acRun_visualminer();
			f_Vector4.acRun_visualminer();
			f_Vector5.acRun_visualminer();
			f_Vector6.acRun_visualminer();
			f_Vector7.acRun_visualminer();
			f_Vector8.acRun_visualminer();

			f_Bicycle->vec_Vertex.clear();

			f_Bicycle->vec_Vertex.push_back(f_Vector1);
			f_Bicycle->vec_Vertex.push_back(f_Vector2);
			f_Bicycle->vec_Vertex.push_back(f_Vector3);
			f_Bicycle->vec_Vertex.push_back(f_Vector4);
			f_Bicycle->vec_Vertex.push_back(f_Vector5);
			f_Bicycle->vec_Vertex.push_back(f_Vector6);
			f_Bicycle->vec_Vertex.push_back(f_Vector7);
			f_Bicycle->vec_Vertex.push_back(f_Vector8);

			f_Bicycle->vec_Color.clear();

			f_Bicycle->vec_Color.push_back(f_Color1);
			f_Bicycle->vec_Color.push_back(f_Color2);
			f_Bicycle->vec_Color.push_back(f_Color3);
			f_Bicycle->vec_Color.push_back(f_Color4);
			f_Bicycle->vec_Color.push_back(f_Color5);
			f_Bicycle->vec_Color.push_back(f_Color6);
			f_Bicycle->vec_Color.push_back(f_Color7);
			f_Bicycle->vec_Color.push_back(f_Color8);

#if 0
			f_Bicycle->acRefresh();
#endif

			f_Hesh->vec_Bicycle.push_back(f_Bicycle);
			}

		return f_Hesh;
		}

	void CubeBicycle::avGrow(float f_Amount)
		{
		for(int f_Count = 0; f_Count < vec_Vertex.size(); f_Count++)
			{
			vec_Vertex[f_Count] *= f_Amount;
			}
		}
		
	void CubeBicycle::avTranslate(Cube::BiVector f_Vector)
		{
		for(int f_Count = 0; f_Count < vec_Vertex.size(); f_Count++)
			{
			vec_Vertex[f_Count] += f_Vector;
			}
		}

	void CubeBicycle::avPushBack(int f_Step)
		{
		if (f_Step >= 0)
			{
			for(int f_Count = 0; f_Count < vec_Vertex.size(); f_Count++)
				{
				vec_Vertex[f_Count] += g_at - g_eye;
				}
			}
		else
			{
			for(int f_Count = 0; f_Count < vec_Vertex.size(); f_Count++)
				{
				vec_Vertex[f_Count] -= g_at - g_eye;
				}
			}
		}

	CubeKEY::CubeKEY(void)
		{
		m_aabb = new aabb();
		m_Link = nullptr;
		m_Served = false;
		vec_Log.clear();
		vec_Child.clear();
		vec_Parent.clear();
		nom_Child = 0;
		nom_Parent = 0;
		}

#if 0
	bool BiMesh::acInteract(DirectX::XMVECTOR rayOrigin, DirectX::XMVECTOR rayDirection)
		{
		// Now perform the ray-sphere intersection test.
		bool intersect = m_Sphere->RaySphereIntersect(rayOrigin, rayDirection);

		return intersect;
		}
#endif

	void BiMesh::acMark(int f_Type)
		{
		m_InteractionType = f_Type;
		g_Mesh = this;
		}

	void BiSphere::acPushRadius(float f_Length)
		{
		if(f_Length > m_Dist)
			{
			m_Dist = f_Length;
			}
		}

	void BiMeshContainer::acClearInteractions(void)
		{
		for(int f_Count = 0; f_Count < m_vec_Sphere.size(); f_Count++)
			{
			BiSphere* f_Sphere = m_vec_Sphere[f_Count];

			f_Sphere->m_Mesh->m_InteractionType = 0;
			}
		}

	void BiMeshContainer::acInteract(float f_MouseX, float f_MouseY)
		{
		float pointX, pointY;
		DirectX::XMMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
		DirectX::XMVECTOR direction, origin;
		DirectX::XMVECTOR f_Det;
		bool intersect, result;

#ifdef GENERIC_BUILD
		// Get the origin of the picking ray which is the position of the camera.
#if 1
		BiVector f_Origin(g_Origin.m128_f32[0] + (((2.0f * (float)f_MouseX) / (float)1366.0f) - 1.0f),
						  g_Origin.m128_f32[1] + ((((2.0f * (float)f_MouseY) / (float)768.0f) - 1.0f) * -1.0f),
						  g_Origin.m128_f32[2]);
#else
		BiVector f_Origin(g_Origin.m128_f32[0] + (((4.0f * (float)f_MouseX) / (float)1920.0f) - 2.0f),
						  (g_Origin.m128_f32[1] + ((((2.0f * (float)f_MouseY) / (float)1080.0f) - 1.0f) * -1.0f)) - 0.4f,
						  g_Origin.m128_f32[2]);
#endif
		BiVector f_Direction(g_viewIn.m128_f32[0] + (((2.0f * (float)f_MouseX) / (float)1366.0f) - 1.0f),
							 g_viewIn.m128_f32[1] + ((((2.0f * (float)f_MouseY) / (float)768.0f) - 1.0f) * -1.0f),
							 g_viewIn.m128_f32[2]);

		g_OriginBi = f_Origin;
		g_DirectionBi = f_Direction;

			// Normalize the ray direction.
		float f_DirDist = f_Direction.acNorm();

		acClearInteractions();

		int f_One = -5.0f;
		float f_Length = 500000.0f;
		bool f_lngResult = false;
		for(int f_Count = 0; f_Count < m_vec_Sphere.size(); f_Count++)
			{
			bool f_Result = false;
			BiSphere* f_Sphere = m_vec_Sphere[f_Count];

			BiVector f_Pos = f_Sphere->m_Pos;
			BiVector f_VecTo = f_Pos - f_Origin;
			float f_ToLength = f_VecTo.acLength();
			BiVector f_VecToNew(f_Origin.m_X + (f_Direction.m_X * f_ToLength), f_Origin.m_Y + (f_Direction.m_Y * f_ToLength), f_Origin.m_Z + (f_Direction.m_Z * f_ToLength));
			BiVector f_VecDist = f_VecToNew - f_Pos;
			float f_DistLength = f_VecDist.acLength();

			if(f_DistLength <= f_Sphere->m_Dist)
				{
				f_Result = true;
				}

			if(f_Result)
				{
				if(f_Sphere->m_Dist <= f_Length)
					{
					f_Length = f_Sphere->m_Dist;
					f_One = f_Count;
					}

				f_lngResult = f_Result;
				}
			}

		if(f_lngResult)
			{
			m_vec_Sphere[f_One]->m_Mesh->acMark(GEN_INT_TYPE_PRESS);
			}
#endif
		}

#if 0
	bool BiSphere::RaySphereIntersect(DirectX::XMVECTOR rayOrigin, DirectX::XMVECTOR rayDirection)
		{
		float a, b, c;
		float discriminant = 0.0f;

#ifdef GENERIC_BUILD
		// Calculate the a, b, and c coefficients.
		a = (rayDirection.m128_f32[0] * rayDirection.m128_f32[0]) + (rayDirection.m128_f32[1] * rayDirection.m128_f32[1]) + (rayDirection.m128_f32[2] * rayDirection.m128_f32[2]);
		b = ((rayDirection.m128_f32[0] * rayOrigin.m128_f32[0]) + (rayDirection.m128_f32[1] * rayOrigin.m128_f32[1]) + (rayDirection.m128_f32[2] * rayOrigin.m128_f32[2])) * 2.0f;
		c = ((rayOrigin.m128_f32[0] * rayOrigin.m128_f32[0]) + (rayOrigin.m128_f32[1] * rayOrigin.m128_f32[1]) + (rayOrigin.m128_f32[2] * rayOrigin.m128_f32[2])) - (m_Dist * m_Dist);


		// Find the discriminant.
		discriminant = (b * b) - (4 * a * c);
#endif
		// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
		if (discriminant < 0.0f)
			{
			return false;
			}

		return true;
		}
#endif

	void BiMeshCore::acPrepare(float f_Time)
		{
		}

	void BiMeshCore::acProcess(float f_Time)
		{
		switch(m_Type)
			{
			case CUBE_COM_TYPE_COMPONENT:
				{
				switch(m_Type)
					{
					case CUBE_COM_FACTORY_ADSR:
						{
						for(int f_Count = 0; f_Count < m_MidiInput[0].m_vec_NoteOn.size(); f_Count++)
							{
							  ////////////
							 // BiNote
							//
							BiNote* f_Note = m_MidiInput[0].m_vec_NoteOn[f_Count];

							 /////////////
							// Controls
							float f_Attack = m_Input[0];
							float f_Decay = m_Input[1];
							float f_Sustain = m_Input[2];
							float f_Release = m_Input[3];

							float f_MidHeight = m_Input[4];

							float f_Amp = 0.0f;

							float f_NoteLength = f_Note->m_TimeEnd - f_Note->m_TimeStart;
							float f_NotePlayed = f_Time - f_Note->m_TimeStart;
							float f_Percent = f_NotePlayed / f_NoteLength;

							if(f_Percent >= 0 && f_Percent < f_Attack)
								{
								f_Amp = (f_Percent / f_Attack);
								}
							else if(f_Percent >= f_Attack && f_Percent < f_Decay)
								{
								f_Amp = ((1 - ((f_Percent - f_Attack) / (f_Decay - f_Attack))) * (1.0f - f_MidHeight)) + f_MidHeight;
								}
							else if(f_Percent >= f_Decay && f_Percent < f_Sustain)
								{
								f_Amp = f_MidHeight;
								}
							else if(f_Percent >= f_Sustain && f_Percent < f_Release)
								{
								f_Amp = ((1 - ((f_Percent - f_Sustain) / (f_Release - f_Sustain))) * f_MidHeight);
								}

							m_VoltOutput[0].m_vec_Volt[f_Count] = f_Amp;
							}
						}break;

					case CUBE_COM_FACTORY_OSCILLATOR:
						{
						for(int f_Count = 0; f_Count < m_MidiInput[0].m_vec_NoteOn.size(); f_Count++)
							{
							  ////////////
							 // BiNote
							//
							BiNote* f_Note = m_MidiInput[0].m_vec_NoteOn[f_Count];

							 /////////////
							// Controls
							float f_Attack = m_Input[0];
							float f_Decay = m_Input[1];
							float f_Sustain = m_Input[2];
							float f_Release = m_Input[3];

							float f_MidHeight = m_Input[4];

							float f_Amp = 0.0f;

							float f_NoteLength = f_Note->m_TimeEnd - f_Note->m_TimeStart;
							float f_NotePlayed = f_Time - f_Note->m_TimeStart;
							float f_Percent = f_NotePlayed / f_NoteLength;

							if(f_Percent >= 0 && f_Percent < f_Attack)
								{
								f_Amp = (f_Percent / f_Attack);
								}
							else if(f_Percent >= f_Attack && f_Percent < f_Decay)
								{
								f_Amp = ((1 - ((f_Percent - f_Attack) / (f_Decay - f_Attack))) * (1.0f - f_MidHeight)) + f_MidHeight;
								}
							else if(f_Percent >= f_Decay && f_Percent < f_Sustain)
								{
								f_Amp = f_MidHeight;
								}
							else if(f_Percent >= f_Sustain && f_Percent < f_Release)
								{
								f_Amp = ((1 - ((f_Percent - f_Sustain) / (f_Release - f_Sustain))) * f_MidHeight);
								}

							m_VoltOutput[0].m_vec_Volt[f_Count] = f_Amp;
							}
						}break;
					}
				}break;
			}
		}

	std::shared_ptr<CubeHESH> ag_Hesh(std::string f_job)
		{
		  ////////////
		 // HESH   //
		////////////
		std::shared_ptr<CubeHESH> f_Hesh = std::make_shared<CubeHESH>();
		f_Hesh->m_ID = g_ID;
		g_ID++;

		f_Hesh->m_Timestamp = g_TimeStamp;

		f_Hesh->m_RotateX = 0.5f;
		f_Hesh->m_RotateY = 0.5f;
		f_Hesh->m_RotateZ = 0.5f;

		f_Hesh->m_ValueBank = 50;

		std::shared_ptr<Cube::CubeHASH_originstring> f_Hash = std::make_shared<Cube::CubeHASH_originstring>();

		   /////////////
		  /////////////
		 // getWork
		//
#if 1
		g_Schedular[0]->getWork(ESL_PATTERN_LAST);

		g_Contract->prepWork();

		for(int f_Int = 0; f_Int < 26; f_Int++)
			{
			std::shared_ptr<CubeBicycle> f_Bicycle = std::make_shared<CubeBicycle>();

			// Load mesh vertices. Each vertex has a position and a color.
			/*Cube::BiRand f_BiRand;
			Cube::BiVector f_Vector1(-0.5f);
			f_Vector1.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector2(-0.5f, -0.5f, 0.5f);
			f_Vector2.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector3(-0.5f, 0.5f, -0.5f);
			f_Vector3.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector4(-0.5f, 0.5f, 0.5f);
			f_Vector4.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector5(0.5f, -0.5f, -0.5f);
			f_Vector5.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector6(0.5f, -0.5f, 0.5f);
			f_Vector6.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector7(0.5f, 0.5f, -0.5f);
			f_Vector7.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);
			f_BiRand.acGet();
			Cube::BiVector f_Vector8(0.5f, 0.5f, 0.5f);
			f_Vector8.acPushRandSphere(Cube::g_swit, f_BiRand.m_Seed);

			Cube::BiVector f_Color1(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color2(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color3(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color4(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color5(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color6(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color7(Cube::random(), Cube::random(), Cube::random());
			Cube::BiVector f_Color8(Cube::random(), Cube::random(), Cube::random());

			/*Cube::agSet_offsetvec(Cube::float3(((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5), ((Cube::random() - 0.5) * 5)));

			f_Vector1.acRun_visualminer();
			f_Vector2.acRun_visualminer();
			f_Vector3.acRun_visualminer();
			f_Vector4.acRun_visualminer();
			f_Vector5.acRun_visualminer();
			f_Vector6.acRun_visualminer();
			f_Vector7.acRun_visualminer();
			f_Vector8.acRun_visualminer();*//*

			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector1.m_X);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector1.m_Y);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector1.m_Z);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector2.m_X);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector2.m_Y);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector2.m_Z);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector3.m_X);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector3.m_Y);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector3.m_Z);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector4.m_X);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector4.m_Y);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector4.m_Z);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector5.m_X);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector5.m_Y);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector5.m_Z);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector6.m_X);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector6.m_Y);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector6.m_Z);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector7.m_X);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector7.m_Y);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector7.m_Z);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector8.m_X);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector8.m_Y);
			f_Hash->m_vec_Input.push_back((unsigned int)f_Vector8.m_Z);

			/*f_Bicycle->vec_Vertex.clear();

			f_Bicycle->vec_Vertex.push_back(f_Vector1);
			f_Bicycle->vec_Vertex.push_back(f_Vector2);
			f_Bicycle->vec_Vertex.push_back(f_Vector3);
			f_Bicycle->vec_Vertex.push_back(f_Vector4);
			f_Bicycle->vec_Vertex.push_back(f_Vector5);
			f_Bicycle->vec_Vertex.push_back(f_Vector6);
			f_Bicycle->vec_Vertex.push_back(f_Vector7);
			f_Bicycle->vec_Vertex.push_back(f_Vector8);

			f_Bicycle->vec_Color.clear();

			f_Bicycle->vec_Color.push_back(f_Color1);
			f_Bicycle->vec_Color.push_back(f_Color2);
			f_Bicycle->vec_Color.push_back(f_Color3);
			f_Bicycle->vec_Color.push_back(f_Color4);
			f_Bicycle->vec_Color.push_back(f_Color5);
			f_Bicycle->vec_Color.push_back(f_Color6);
			f_Bicycle->vec_Color.push_back(f_Color7);
			f_Bicycle->vec_Color.push_back(f_Color8);

			f_Bicycle->m_indexCount = 8;

			f_Hesh->vec_Bicycle.push_back(f_Bicycle);*/
			}

		f_Hesh->m_adIndex.clear();

		int f_PORTcntr = 0;
		while(f_Hesh->m_adIndex.size() < 26)
			{
			Cube::g_Fingat = Cube::randomFac() % CUBE_TRI_SHOT_TOTAL;

			if(Cube::g_Fingat > Cube::g_BiStyle->m_AdIndexPercent)
				{
				int f_Finger = Cube::randomFac() % f_Hesh->vec_Bicycle.size();
				//f_Finger = f_PORTcntr;
				f_Hesh->m_adIndex.push_back(f_Finger);
				f_Hash->acPushInt((unsigned int)f_Finger);
				}

			f_PORTcntr++;
			}

			////////////
		   //
		  // Hash
		 //
		//char *lx = (char*)malloc(f_Hash->m_vec_Input.size() * 8 * sizeof(char));
		//ag_bin2hex(lx, f_Hash->m_vec_Input, f_Hash->m_vec_Input.size());
		std::string f_InputHash = f_Hash->m_str_Input;
		f_InputHash += f_job;
#else
		std::string f_InputHash("f21378asiasd7");
		f_InputHash += f_job;
#endif

		//hey you could add a nonce here

		g_hasha.init(); //reset hasher state
		g_hasha.process(f_InputHash.begin(), f_InputHash.end());
		g_hasha.finish();
		picosha2::get_hash_hex_string(g_hasha, f_Hash->m_OutputHash);

		f_Hesh->m_Hash = f_Hash;

		/*std::shared_ptr<classTarget> f_Target = new classTarget(f_Hesh);

		g_Result = g_Target->acCompare(f_Target, 50.95f, 850.0f, true);

		if(g_Result)
			{
			g_TargetedHesh = f_Hesh;
			}*/

		return f_Hesh;
		}

	bool ag_hex2bin(unsigned char *p, const char *hexstr, size_t len)
		{
		char hex_byte[3];
		char *ep;

		hex_byte[2] = '\0';

		while(*hexstr && len)
			{
			if(!hexstr[1])
				{
				printf("hex2bin str truncated");
				return false;
				}

			hex_byte[0] = hexstr[0];
			hex_byte[1] = hexstr[1];

			*p = (unsigned char)strtol(hex_byte, &ep, 16);

			if(*ep)
				{
				printf("hex2bin failed on '%s'", hex_byte);
				return false;
				}

			p++;
			hexstr += 2;
			len--;
			}

		return (len == 0 && *hexstr == 0) ? true : false;
		}

	void ag_bin2hex(char *s, std::vector<unsigned int> p, size_t len)
		{
		int i;
		for(i = 0; i < len; i++)
			{
			sprintf(s + (i * 2), "%02x", p[i]);
			}
		}

	void ag_bin2hex(char *s, std::vector<unsigned char> p, size_t len)
		{
		int i;
		for(i = 0; i < len; i++)
			{
			sprintf(s + (i * 2), "%02x", p[i]);
			}
		}

	void ag_bin2hex(char *s, float p)
		{ sprintf(s, "%02x", p); }

	char *phex(const void *p, size_t n)
		{
		const unsigned char *cp = (unsigned char*)p;              /* Access as bytes. */
		char *s = (char*)malloc(2*n + 1);       /* 2*n hex digits, plus NUL. */
		size_t k;

		/*
			* Just in case - if allocation failed.
			*/
		if(s == NULL)
			return s;

		for(k = 0; k < n; ++k)
			{
				/*
				* Convert one byte of data into two hex-digit characters.
				*/
			sprintf(s + 2*k, "%02X", cp[k]);
			}

			/*
			* Terminate the string with a NUL character.
			*/
		s[2*n] = '\0';

		return s;
		}

#if 0
derMiner.Util = {
  hex_to_uint32_array: function(hex) {
    var arr = [];
    for (var i = 0, l = hex.length; i < l; i += 8) {
        arr.push((parseInt(hex.substring(i, i+8), 16)));
    }
    return arr;
  },
  hex_to_uint16_array: function(hex) {
    var arr = [];
    for (var i = 0, l = hex.length; i < l; i += 4) {
        arr.push((parseInt(hex.substring(i, i+4), 16)));
    }
    return arr;
  },
  uint32_array_to_hex: function(arr) {
    var hex = '';
    for (var i = 0; i < arr.length; i++) {
      hex += derMiner.Util.byte_to_hex(arr[i] >>> 24);
      hex += derMiner.Util.byte_to_hex(arr[i] >>> 16);
      hex += derMiner.Util.byte_to_hex(arr[i] >>>  8);
      hex += derMiner.Util.byte_to_hex(arr[i]       );
    }
    return hex;
  },
  uint16_array_to_hex: function(arr) {
    var hex = '';
    for (var i = 0; i < arr.length; i++) {
      hex += derMiner.Util.byte_to_hex(arr[i] >>>  8);
      hex += derMiner.Util.byte_to_hex(arr[i]       );
    }
    return hex;
  },
  to_uint16_array: function(w) {
        return [(w & 0xffff0000) >> 16, (w & 0x0000ffff) ];
  },
  byte_to_hex: function(b) {
    var tab = '0123456789abcdef';
    b = b & 0xff;
    return tab.charAt(b / 16) +
           tab.charAt(b % 16);
  },
  reverseBytesInWord: function(w) {
    return ((w <<  24) & 0xff000000) |
           ((w <<   8) & 0x00ff0000) |
           ((w >>>  8) & 0x0000ff00) |
           ((w >>> 24) & 0x000000ff);
  },
  reverseBytesInInt: function(w) {
    return ((w << 8) & 0x0000ff00 |
            (w >> 8) & 0x000000ff);
  },
  reverseBytesInWords: function(words) {
    var reversed = [];
    for(var i = 0; i < words.length; i++)
      reversed.push(derMiner.Util.reverseBytesInWord(words[i]));
    return reversed;
  },
  reverseBytesInInts: function(words) {
    var reversed = [];
    for(var i = 0; i < words.length-1; i+=2) {
        reversed.push(derMiner.Util.reverseBytesInInt(words[i+1]));
        reversed.push(derMiner.Util.reverseBytesInInt(words[i]));
    }
    return reversed;
  },
  fromPoolString: function(hex, gl) {
    return gl
           ? derMiner.Util.reverseBytesInInts(derMiner.Util.hex_to_uint16_array(hex))
           : derMiner.Util.reverseBytesInWords(derMiner.Util.hex_to_uint32_array(hex));
  },
  toPoolString: function(data, gl) {
    return gl
           ? derMiner.Util.uint16_array_to_hex(derMiner.Util.reverseBytesInInts(data))
           : derMiner.Util.uint32_array_to_hex(derMiner.Util.reverseBytesInWords(data));
  },
  ToUInt32: function (x) {
    return x >>> 0;
  }
#endif

}; //END Cube

  //////////////////////////////////////////////////////////////////////////
 // Cube TX
//
bool ag_VerifyTXIN(CubeTXIN* f_txin, float f_amount)
{
	//trace source of wealth
	CubeTransaction* f_PrevTX = ag_get_TXfromvout(f_txin->m_vout);

	if(!f_PrevTX->isValid())
		{
		return false;
		}

	bool f_find = false;
	for(int f_Z = 0; f_Z < f_PrevTX->m_txout.size(); f_Z++)
		{
		CubeTXOUT* f_txout = f_PrevTX->m_txout[f_Z];

		if(f_txout->m_Flag == 1)
			{
			f_find = true;

			if(f_txout->m_owneramt < f_amount)
				{
				return false;
				}
			}
		}

	if(f_find == false)
		{
		return false;
		}
	else
		{
		return true;
		}
}

ShareContainer* ag_BuildPeerGraph(int f_JobID, int f_ServLay)
{
	   ////////////
	  // Rewards
	 // Full Count
	// Tier Based Payment Rewards
	char* fullquery;
	fullquery = (char*)malloc(sizeof(char) * 1024);

	sprintf(fullquery, "SELECT id, owner, score, dated FROM share WHERE jobid = %i", f_JobID);
	g_SafeL[f_ServLay]->acSelectCommand_PeerGraph(fullquery, false, false);

	int f_popPeerCount = g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)].size();

	int f_Index = 0;
	ShareContainer* f_ShareContainer = new ShareContainer();

	std::vector<std::string> f_vec_PeerString;
	std::vector<int> f_vec_Score;
	std::vector<int> f_vec_StringCount;

	f_vec_PeerString.clear();
	f_vec_Score.clear();
	f_vec_StringCount.clear();

	int f_ShareCounting = 0;
	int f_OwnPeerIndex = 0;

	for(int f_Int = 0; f_Int < f_popPeerCount - 2; f_Int++)
		{
		std::string f_peer = g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_Int][0].c_str();
		int f_score = atoi(g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_Int][1].c_str());
		int f_counter = atoi(g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_Int][2].c_str());

		f_ShareCounting += f_counter;

		bool f_Found = false;
		int f_Index = 0;
		for(int f_IntSearch = 0; f_IntSearch < f_vec_PeerString.size(); f_IntSearch++)
			{
			if(f_peer.compare(f_vec_PeerString[f_IntSearch]) == 0 && f_vec_Score[f_IntSearch] == f_score)
				{
				f_Found = true;
				f_Index = f_IntSearch;
				}
			}

		if(!f_Found)
			{
			f_vec_PeerString.push_back(f_peer);
			f_vec_Score.push_back(f_score);
			f_vec_StringCount.push_back(f_counter);

			if(f_peer.compare(g_Wallet->GetAdr()) == 0)
				{
				f_OwnPeerIndex = f_Index;
				}
			}
		else
			{
			f_vec_StringCount[f_Index]++;
			}
		}

	for(int f_PeerInc = 0; f_PeerInc < f_vec_PeerString.size(); f_PeerInc++)
		{
		std::string f_PeerStr = f_vec_PeerString[f_PeerInc];

		bool f_Found = false;
		for(int f_IntSearch = 0; f_IntSearch < f_ShareContainer->m_Peer.size(); f_IntSearch++)
			{
			if(f_PeerStr.compare(f_ShareContainer->m_Peer[f_IntSearch]->m_Owner) == 0)
				{
				f_Found = true;
				f_Index = f_IntSearch;
				}
			}

		if(!f_Found)
			{
			Cube::CubePeer* f_CPeer = new Cube::CubePeer();
			f_CPeer->m_Owner = f_PeerStr;
			Cube::CubeShare* f_CShare = new Cube::CubeShare();
			f_CShare->m_Owner = f_PeerStr;
			f_CShare->m_Score = f_vec_Score[f_PeerInc];
			f_CPeer->m_Share.push_back(f_CShare);
			f_ShareContainer->m_Peer.push_back(f_CPeer);
			
			for(int f_Puto = 1; f_Puto < f_vec_StringCount[f_PeerInc]; f_Puto++)
				{
				Cube::CubeShare* f_CShare = new Cube::CubeShare();
				f_CShare->m_Owner = f_PeerStr;
				f_CShare->m_Score = f_vec_Score[f_PeerInc];
				f_CPeer->m_Share.push_back(f_CShare);
				}
			}
		else
			{
			Cube::CubeShare* f_CShare = new Cube::CubeShare();
			f_CShare->m_Owner = f_PeerStr;
			f_CShare->m_Score = f_vec_Score[f_PeerInc];
			f_ShareContainer->m_Peer[f_Index]->m_Share.push_back(f_CShare);
			
			for(int f_Puto = 1; f_Puto < f_vec_StringCount[f_PeerInc]; f_Puto++)
				{
				Cube::CubeShare* f_CShare = new Cube::CubeShare();
				f_CShare->m_Owner = f_PeerStr;
				f_CShare->m_Score = f_vec_Score[f_PeerInc];
				f_ShareContainer->m_Peer[f_Index]->m_Share.push_back(f_CShare);
				}
			}
		}

	return f_ShareContainer;
}

ShareContainer* ag_SelectPeerGraph(int f_JobID, int f_ServLay, int f_ShareID, int f_ShareOffset, int f_PEER)
{
	int f_Int = 1;
	if(!g_SafeL[f_ServLay])
		{
		g_SafeL[f_ServLay] = new icSafeL(f_ServLay);
		g_SafeL[f_ServLay]->Initialize();

		f_Int = g_SafeL[f_ServLay]->Connect("localhost", "root", "fracTALIZe18", "globalscapedb", 3306);
		}

	printf("Connected to ecoin server...\n");

	//assume remote connection for windows
	if(f_Int)
		{
		   ////////////
		  // Rewards
		 // Full Count
		// Tier Based Payment Rewards
		char* fullquery;
		fullquery = (char*)malloc(sizeof(char) * 1024);

		sprintf(fullquery, "SELECT id, owner, score, dated FROM share WHERE jobid = %i", f_JobID);
		g_SafeL[f_ServLay]->acSelectCommand_PeerGraphSelect(fullquery, false, false, f_ShareID, f_ShareOffset, f_PEER);

		int f_popPeerCount = g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)].size();

		int f_Index = 0;
		ShareContainer* f_ShareContainer = new ShareContainer();

		std::vector<std::string> f_vec_PeerString;
		std::vector<int> f_vec_Score;
		std::vector<int> f_vec_StringCount;

		f_vec_PeerString.clear();
		f_vec_Score.clear();
		f_vec_StringCount.clear();

		int f_ShareCounting = 0;
		int f_OwnPeerIndex = 0;

		for(int f_Int = 0; f_Int < f_popPeerCount - 6; f_Int++)
			{
			std::string f_peer = g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_Int][0].c_str();
			int f_score = atoi(g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_Int][1].c_str());
			int f_counter = atoi(g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_Int][2].c_str());

			f_ShareCounting += f_counter;

			bool f_Found = false;
			int f_Index = 0;
			for(int f_IntSearch = 0; f_IntSearch < f_vec_PeerString.size(); f_IntSearch++)
				{
				if((f_peer.compare(f_vec_PeerString[f_IntSearch]) == 0) && (f_vec_Score[f_IntSearch] == f_score))
					{
					f_Found = true;
					f_Index = f_IntSearch;
					}
				}

			if(!f_Found)
				{
				f_vec_PeerString.push_back(f_peer);
				f_vec_Score.push_back(f_score);
				f_vec_StringCount.push_back(f_counter);

				if(f_peer.compare(g_Wallet->GetAdr()) == 0)
					{
					f_OwnPeerIndex = f_Index;
					}
				}
			else
				{
				f_vec_StringCount[f_Index]++;
				}
			}

		for(int f_PeerInc = 0; f_PeerInc < f_vec_PeerString.size(); f_PeerInc++)
			{
			std::string f_PeerStr = f_vec_PeerString[f_PeerInc];
			int f_ac_score = f_vec_Score[f_PeerInc];

			bool f_Found = false;
			for(int f_IntSearch = 0; f_IntSearch < f_ShareContainer->m_Peer.size(); f_IntSearch++)
				{
				if((f_PeerStr.compare(f_ShareContainer->m_Peer[f_IntSearch]->m_Owner) == 0) && (f_ac_score == f_ShareContainer->m_Peer[f_IntSearch]->m_Share[0]->m_Score))
					{
					f_Found = true;
					f_Index = f_IntSearch;
					}
				}

			if(!f_Found)
				{
				Cube::CubePeer* f_CPeer = new Cube::CubePeer();
				f_CPeer->m_Owner = f_PeerStr;
				Cube::CubeShare* f_CShare = new Cube::CubeShare();
				f_CShare->m_Owner = f_PeerStr;
				f_CShare->m_Score = f_vec_Score[f_PeerInc];
				f_CPeer->m_Share.push_back(f_CShare);
				f_ShareContainer->m_Peer.push_back(f_CPeer);
			
				for(int f_Puto = 1; f_Puto < f_vec_StringCount[f_PeerInc]; f_Puto++)
					{
					Cube::CubeShare* f_CShare = new Cube::CubeShare();
					f_CShare->m_Owner = f_PeerStr;
					f_CShare->m_Score = f_vec_Score[f_PeerInc];
					f_CPeer->m_Share.push_back(f_CShare);
					}
				}
			else
				{
				Cube::CubeShare* f_CShare = new Cube::CubeShare();
				f_CShare->m_Owner = f_PeerStr;
				f_CShare->m_Score = f_vec_Score[f_PeerInc];
				f_ShareContainer->m_Peer[f_Index]->m_Share.push_back(f_CShare);
			
				for(int f_Puto = 1; f_Puto < f_vec_StringCount[f_PeerInc]; f_Puto++)
					{
					Cube::CubeShare* f_CShare = new Cube::CubeShare();
					f_CShare->m_Owner = f_PeerStr;
					f_CShare->m_Score = f_vec_Score[f_PeerInc];
					f_ShareContainer->m_Peer[f_Index]->m_Share.push_back(f_CShare);
					}
				}
			}

		f_ShareContainer->m_espo_Owner = g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_popPeerCount - 6][0].c_str();
		f_ShareContainer->m_espo_Date = g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_popPeerCount - 5][0].c_str();
		f_ShareContainer->m_espo_ShareOffset = atoi(g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_popPeerCount - 4][0].c_str());
		f_ShareContainer->m_espo_Peer = atoi(g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_popPeerCount - 3][0].c_str());
		f_ShareContainer->m_espo_ID = atoi(g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_popPeerCount - 2][0].c_str());
		f_ShareContainer->m_espo_Score = atoi(g_Schedular[f_ServLay]->m_Entries[g_Schedular[f_ServLay]->ac_GetEntry(g_Schedular[f_ServLay]->m_Entries.size() - 1)][f_popPeerCount - 1][0].c_str());

		return f_ShareContainer;
		}
	else
		{
		return nullptr;
		}
}

bool ag_BuildVecTier(ShareContainer* f_ShareContainer)
{
	std::vector<Cube::CubeTier*> f_vec_Tier;
	f_vec_Tier.clear();

	Cube::CubeTier* f_Common0 = new Cube::CubeTier();
	f_vec_Tier.push_back(f_Common0);

	for(int f_Helly = 0; f_Helly < f_ShareContainer->m_Peer.size(); f_Helly++)
		{
		for(int f_Jet = 0; f_Jet < f_ShareContainer->m_Peer[f_Helly]->m_Share.size(); f_Jet++)
			{
			Cube::CubeShare* f_CubeShare = f_ShareContainer->m_Peer[f_Helly]->m_Share[f_Jet];

			if(f_CubeShare->m_Score == 0)
				{
				if(f_Common0)
					{
					f_Common0->m_vec_Share.push_back(f_CubeShare);
					f_CubeShare->m_Tier = f_Common0;
					}
				}
			else
				{
				if(f_vec_Tier.size() <= 1)
					{
					Cube::CubeTier* f_Tier = new Cube::CubeTier();
					f_vec_Tier.push_back(f_Tier);
					f_Tier->m_vec_Share.push_back(f_CubeShare);
					f_CubeShare->m_Tier = f_Tier;
					}
				else
					{
					bool f_Found = false;
					for(int f_Scan = 0; f_Scan < f_vec_Tier.size(); f_Scan++)
						{
						if(!f_Found)
							{
							Cube::CubeTier* f_ScanTier = f_vec_Tier[f_Scan];

							if(f_ScanTier->m_vec_Share.size() >= 1)
								{
								if(f_ScanTier->m_vec_Share[0]->m_Score == f_CubeShare->m_Score)
									{
									f_ScanTier->m_vec_Share.push_back(f_CubeShare);
									f_CubeShare->m_Tier = f_ScanTier;
									f_Found = true;
									f_Scan = f_vec_Tier.size();
									}
								else if(f_ScanTier->m_vec_Share[0]->m_Score > f_CubeShare->m_Score)
									{
									Cube::CubeTier* f_Tier = new Cube::CubeTier();

									  ////////
									 // Array
									// re-Order
									f_vec_Tier.push_back(f_vec_Tier[f_vec_Tier.size() - 1]);

									for(int f_i = f_Scan; f_i < (f_vec_Tier.size() - 1); f_i++)
										{
										f_vec_Tier[f_i + 1] = f_vec_Tier[f_i];
										}

									f_vec_Tier[f_Scan] = f_Tier;
									f_Tier->m_vec_Share.push_back(f_CubeShare);
									f_CubeShare->m_Tier = f_Tier;
									f_Found = true;
									f_Scan = f_vec_Tier.size();
									}
								}
							}
						}

					if(!f_Found)
						{
						Cube::CubeTier* f_Tier = new Cube::CubeTier();
						f_vec_Tier.push_back(f_Tier);
						f_Tier->m_vec_Share.push_back(f_CubeShare);
						f_CubeShare->m_Tier = f_Tier;
						}
					}
				}
			}
		}

	  ///////////
	 // Totals
	//
	float f_block_reward = 50.0f;
	float f_block_winreward = 25.0f;

#if 0
	printf("ECN::STAT::: max tid tiercount %i\n", f_vec_Tier.size());
#endif

	for(int f_tid = f_vec_Tier.size() - 1; f_tid >= 0; f_tid--)
		{
		Cube::CubeTier* f_CBTier = f_vec_Tier[f_tid];

		float f_share_reward = f_block_winreward / f_CBTier->m_vec_Share.size();

#if 0
		printf("|____CubeTier[%i]:::vec_Share.size = %i f_block_winreward %f f_share_reward %f\n", f_tid, f_CBTier->m_vec_Share.size(), f_block_winreward, f_share_reward);
#endif

		for(int f_aid = 0; f_aid < f_vec_Tier[f_tid]->m_vec_Share.size(); f_aid++)
			{
			f_vec_Tier[f_tid]->m_vec_Share[f_aid]->m_Amount = f_share_reward;

#if 0
			printf("|_______________CubeShare[%i]:::m_Amount = %f\n", f_aid, f_share_reward);
#endif
			}

		f_block_winreward /= 2;
		}

	return true;
}

	  //////////////////////////
	 // Calc for Owner Peer
	//
float ag_CalcOwnerGenesisTX(std::string f_Owner, int f_JobID)
{
	ShareContainer* f_ShareContainer = ag_BuildPeerGraph(f_JobID, 0);

	ag_BuildVecTier(f_ShareContainer);

	int f_ShareCounter = 0;

	float f_Amount = 0.0f;
	Cube::CubePeer* f_ownerPeer = f_ShareContainer->acPeerfromOwner(f_Owner);

	for (int f_shrid = 0; f_shrid < f_ownerPeer->m_Share.size(); f_shrid++)
		{
		Cube::CubeShare* f_CBShare = f_ownerPeer->m_Share[f_shrid];

		f_Amount += f_CBShare->m_Amount;

		f_ShareCounter++;
		}

	return f_Amount;
}

CubeTransaction* ag_getTX(int f_txid, int f_txoutid) //f_txoutid: optional, sets flag upon found for use later
{
	CubeTransaction* f_TX = new CubeTransaction();

	char txquery[1000];
	sprintf(txquery, "SELECT status, typed, hash, amt, fee, confirmation, jobid, reward, rewardid, hdid, gnshareid, owner FROM transactions WHERE id = %i", f_txid);

	g_SafeL[0]->acSelectCommand(txquery, false, false);
	int f_TxLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

	printf("ECN::Stat::: f_TxLCount %i\n", f_TxLCount);

	//assume remote connection for windows
	if(f_TxLCount > 0)
		{
		f_TX->m_txid = f_txid;
		f_TX->m_status = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].c_str());
		f_TX->m_type = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
		f_TX->m_Hash = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
		f_TX->m_confirmation = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][5].c_str());
		f_TX->m_amt = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][3].c_str());
		f_TX->m_fee = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][4].c_str());
		f_TX->m_jobid = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][6].c_str());
		f_TX->m_reward = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][7].c_str());
		f_TX->m_rewardid = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][8].c_str());
		f_TX->m_hdid = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][9];
		int f_gnsharesupport = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][10].c_str());
		f_TX->m_owner = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][11];

		//out
		char txoutquery[1000];
		sprintf(txoutquery, "SELECT id, adrid, owner, pubkey, txoutamt, owneramt, dated FROM txout WHERE transactionid = %i", f_txid);

		g_SafeL[0]->acSelectCommand(txoutquery, false, false);
		int f_TxoutLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

		printf("ECN::Stat::: f_TxinLCount %i\n", f_TxoutLCount);

		if(f_TxoutLCount > 0)
			{
			for(int f_jet = 0; f_jet < f_TxoutLCount; f_jet++)
				{
				CubeTXOUT* f_txout = new CubeTXOUT();

				f_txout->m_txid = f_txid;
				f_txout->m_txoutid = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][f_jet][0].c_str());
				f_txout->m_adrid = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][f_jet][1].c_str());
				f_txout->m_owner = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][f_jet][2];
				f_txout->m_pubkey = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][f_jet][3];
				f_txout->m_txoutamt = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][f_jet][4].c_str());
				f_txout->m_owneramt = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][f_jet][5].c_str());

				//verify flag
				if(f_txout->m_txoutid == f_txoutid)
					{
					f_txout->m_Flag = 1;
					}

				f_TX->m_txout.push_back(f_txout);
				}
			}

		//in
		char txinquery[1000];
		sprintf(txinquery, "SELECT id, vout, pubkey, vsign, amt, dated FROM txin WHERE transactionid = %i", f_txid);// WHERE name = '%s' AND pass = MD5('%s')", i_name, i_password);
																																		//Run the query
		g_SafeL[0]->acSelectCommand(txinquery, false, false);
		int f_TxinLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

		printf("ECN::Stat::: f_TxinLCount %i\n", f_TxinLCount);

		if(f_TxinLCount > 0)
			{
			for(int f_jet = 0; f_jet < f_TxinLCount; f_jet++)
				{
				CubeTXIN* f_txin = new CubeTXIN();

				f_txin->m_txinid = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].c_str());
				f_txin->m_vout = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1];
				f_txin->m_pubkey = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][2];
				f_txin->m_sigstr = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][3];
				float f_txinrow4 = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][4].c_str());

				  ///////////////////
				 // Detect Genesis
				// Tracking
				std::string f_vout = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1];

				if(f_vout.compare("Genesis Tracking") == 0)
					{ //generate coin
					if(f_TxoutLCount == 1)
						{
 						float f_Amount = ag_CalcOwnerGenesisTX(f_TX->m_txout[0]->m_owner, f_TX->m_jobid - 1);

						char* f_fiquery = new char[150];
						sprintf(f_fiquery, "SELECT id, amt FROM address WHERE owner = '%s'", f_TX->m_txout[0]->m_owner.c_str());
						g_SafeL[0]->acSelectCommand(f_fiquery, false, false);
						int f_AdrCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

						if(f_AdrCount > 0)
							{
							if(f_AdrCount > 1)
								{
								while(true)
									{
									printf("ECN::ADR ERROR\n");
									}
								}

							int f_peerID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].c_str());
							float f_peerAmount = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());

							float f_full_reward = f_peerAmount + f_Amount;
							f_TX->m_amt = f_Amount;
#if 0
							char* g_peerfield[1];
							char* g_peervalue[1];
							char* g_peerwhere[1];

							for(int f_Count = 0; f_Count < 1; f_Count++)
								{
								g_peerfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
								g_peervalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
								g_peerwhere[f_Count] = (char*)malloc(sizeof(char) * 1024);
								}

							sprintf(g_peerfield[0], "amt");
							sprintf(g_peervalue[0], "%f", f_full_reward);
							sprintf(g_peerwhere[0], "id = %i", f_peerID);

							g_SafeL[0]->Update("address", (const char **)g_peerfield, (const char **)g_peervalue, 1, g_peerwhere[0]);
#endif

							f_txin->m_txid = f_txid;
							f_txin->m_amt = f_full_reward;
							f_txin->m_gnshareid = f_gnsharesupport;
							f_TX->m_txout[0]->m_txoutamt = f_Amount;
							f_TX->m_txout[0]->m_owneramt = f_full_reward;
							}
						else
							{
							for(;;)
								{
								printf("ECN::ADVWARN f_AdrCount = %i\n", f_AdrCount);
								}
							}
						}
					else
						{
						for(;;)
							{
							printf("ECN::ADVWARN txout for genesis coin invalid txid = %i\n", f_TX->m_txid);
							}
						}
					}
				else if(f_vout.compare("Genesis Coin") == 0)
					{ //generate coin
					if(f_TxoutLCount == 1)
						{
						float f_Amount = 1.0f;

						char* f_fiquery = new char[150];
						sprintf(f_fiquery, "SELECT id, amt FROM address WHERE owner = '%s'", f_TX->m_txout[0]->m_owner.c_str());
						g_SafeL[0]->acSelectCommand(f_fiquery, false, false);
						int f_AdrCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

						if(f_AdrCount > 0)
							{
							if(f_AdrCount > 1)
								{
								while(true)
									{
									printf("ECN::ADR ERROR\n");
									}
								}

							int f_peerID = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].c_str());
							float f_peerAmount = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());

							float f_full_reward = f_peerAmount + f_Amount;

#if 0
							char* g_peerfield[1];
							char* g_peervalue[1];
							char* g_peerwhere[1];

							for(int f_Count = 0; f_Count < 1; f_Count++)
								{
								g_peerfield[f_Count] = (char*)malloc(sizeof(char) * 1024);
								g_peervalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
								g_peerwhere[f_Count] = (char*)malloc(sizeof(char) * 1024);
								}

							sprintf(g_peerfield[0], "amt");
							sprintf(g_peervalue[0], "%f", f_full_reward);
							sprintf(g_peerwhere[0], "id = %i", f_peerID);

							g_SafeL[0]->Update("address", (const char **)g_peerfield, (const char **)g_peervalue, 1, g_peerwhere[0]);
#endif

							f_txin->m_txid = f_txid;
							f_txin->m_amt = f_full_reward;
							f_TX->m_txout[0]->m_txoutamt = f_Amount;
							f_TX->m_txout[0]->m_owneramt = f_full_reward;
							}
						else
							{
							for(;;)
								{
								printf("ECN::ADVWARN f_AdrCount = %i\n", f_AdrCount);
								}
							}
						}
					else
						{
						for(;;)
							{
							printf("ECN::ADVWARN txout for genesis coin invalid txid = %i\n", f_TX->m_txid);
							}
						}
					}
				else
					{
					f_txin->m_txid = f_txid;
					f_txin->m_amt = f_txinrow4;
					f_txin->m_gnshareid = f_gnsharesupport;
					}

				f_TX->m_txin.push_back(f_txin);
				}
			}
		}

	return f_TX;
}

CubeTransaction* ag_get_TXfromvout(std::string f_vout)
{
	char txquery[1000];
	sprintf(txquery, "SELECT id, transactionid, dated FROM txout WHERE owner = '%s' ORDER BY dated DESC LIMIT 1", f_vout.c_str());

	g_SafeL[0]->acSelectCommand(txquery, false, false);
	int f_TxLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

	printf("ECN::Stat::: f_TxLCount %i\n", f_TxLCount);

	CubeTransaction* f_TX = new CubeTransaction();

	//assume remote connection for windows
	if(f_TxLCount > 0)
		{
		f_TX = ag_getTX(atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str()), atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].c_str()));
		}

	return f_TX;
}

float ag_OwnerBalance(std::string f_owner)
{
#pragma message("FIXME add date to verification, think ultra secure")

	char balquery[1000];
	sprintf(balquery, "SELECT id, amt, owner FROM address WHERE owner = '%s'", f_owner.c_str());

	g_SafeL[0]->acSelectCommand(balquery, true, false);
	int f_balCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

	printf("ECN::Stat::: f_balCount %i\n", f_balCount);

	//assume remote connection for windows
	if(f_balCount > 0)
		{
		float f_amt = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());
		return f_amt;
		}
	else
		{
		printf("ECN::Error address not found:: owner balance\n");
		}

	return -1.0f;
}

void ag_UpdateOwnerBalance(std::string f_Owner, float f_Amount)
{
	char* f_balupvalue[1];
	char* f_balupfield[1];
	char* f_balupwhere[1];

	f_balupvalue[0] = (char*)malloc(sizeof(char) * 1024);
	f_balupfield[0] = (char*)malloc(sizeof(char) * 1024);
	f_balupwhere[0] = (char*)malloc(sizeof(char) * 1024);

	sprintf(f_balupfield[0], "amt");
	sprintf(f_balupvalue[0], "%f", f_Amount);
	sprintf(f_balupwhere[0], "owner = '%s'", f_Owner.c_str());

	g_SafeL[0]->Update("address", (const char **)f_balupfield, (const char **)f_balupvalue, 1, f_balupwhere[0], 2, false);
}

std::string ag_GatherTransactions(int f_JobID)
{
	std::string f_Result;
	f_Result.clear();

	int f_Int = 1;
	if(!g_SafeL[0])
		{
		g_SafeL[0] = new icSafeL(0);
		g_SafeL[0]->Initialize();

		f_Int = g_SafeL[0]->Connect("localhost", "root", "fracTALIZe18", "globalscapedb", 3306);
		}

	printf("Connected to ecoin server...\n");

	char txquery[1000];
	sprintf(txquery, "SELECT id, hash, confirmation, owner, jobid, locktime, dated FROM transactions WHERE (jobid < %i AND status = 1 AND confirmation < 6) OR (jobid = %i AND status = 1) ORDER BY dated DESC LIMIT 3", f_JobID, f_JobID);
	g_SafeL[0]->acSelectCommand(txquery, 2, false);
	int f_TxLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

	printf("ECN::Stat::: f_TxLCount %i\n", f_TxLCount);

	int f_EntrantID_HashBoard = g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1);

	//assume remote connection for windows
	if((f_Int) && (f_TxLCount > 0))
		{
		int f_idx_vec_TX = 0;
		std::vector<CubeTransaction*> f_vec_TX;

		for(int f_roton = 0; f_roton < f_TxLCount; f_roton++)
 			{
			std::string f_hash = g_Schedular[0]->m_Entries[f_EntrantID_HashBoard][f_roton][1];

			printf("f_roton %i hash %s\n", f_roton, f_hash.c_str());

			CubeTransaction* f_Transaction = new CubeTransaction();

			f_Transaction->m_txid = atoi(g_Schedular[0]->m_Entries[f_EntrantID_HashBoard][f_roton][0].c_str());
			f_Transaction->m_Hash = g_Schedular[0]->m_Entries[f_EntrantID_HashBoard][f_roton][1];
			f_Transaction->m_confirmation = atoi(g_Schedular[0]->m_Entries[f_EntrantID_HashBoard][f_roton][1].c_str());
			f_Transaction->m_owner = g_Schedular[0]->m_Entries[f_EntrantID_HashBoard][f_roton][3];
			f_Transaction->m_jobid = atoi(g_Schedular[0]->m_Entries[f_EntrantID_HashBoard][f_roton][4].c_str());
			f_Transaction->m_locktime = atoi(g_Schedular[0]->m_Entries[f_EntrantID_HashBoard][f_roton][5].c_str());
			f_Transaction->m_status = 1;

			f_vec_TX.push_back(f_Transaction);
			f_idx_vec_TX++;
			}

		int f_TxLCountScan = f_TxLCount;
			
		for(int f_Jet = 0; f_Jet < f_TxLCountScan; f_Jet++)
			{
			int f_txid = f_vec_TX[f_Jet]->m_txid;
			std::string f_txowner = f_vec_TX[f_Jet]->m_owner;
			int f_txjobid = f_vec_TX[f_Jet]->m_jobid;
			int f_txlc = f_vec_TX[f_Jet]->m_locktime;
				
			for(int f_RM = 0; f_RM < f_TxLCountScan; f_RM++)
				{
				if(f_Jet != f_RM)
					{
					if(f_vec_TX[f_RM]->m_status != -5)
						{
						int f_RMid = f_vec_TX[f_RM]->m_txid;
						std::string f_RMowner = f_vec_TX[f_RM]->m_owner;
						int f_RMjobid = f_vec_TX[f_RM]->m_jobid;
						int f_RMlc = f_vec_TX[f_RM]->m_locktime;
							
						if(((f_txlc == 2) && (f_RMlc == 2)) && (f_txowner.compare(f_RMowner) == 0) && (f_txjobid == f_RMjobid))
							{
							if(f_txid > f_RMid)
								{
								f_vec_TX[f_RM]->m_status = -5;
									
								CubeTransaction* f_TransactionA = ag_getTX(f_RMid);

								f_TransactionA->m_fresh = VERIFY_FAIL;

								std::string f_null = ag_cont_VerifySingleTransaction(f_TransactionA, VERIFY_FAIL);
								}
							}
						}
					}
				}
			}

		std::string f_Result = ""; //gathered result tx
		int f_ResCount = 0;

		for(int f_t = 0; f_t < f_TxLCountScan; f_t++)
			{
			if(f_vec_TX[f_t]->m_status != -5)
				{
				CubeTransaction* f_TransactionA = ag_getTX(f_vec_TX[f_t]->m_txid);

				if(f_TransactionA->isValid() == true)
					{
					f_TransactionA->m_fresh = VERIFY_SUCCEEDING;

					f_Result += ag_cont_VerifySingleTransaction(f_TransactionA, VERIFY_SUCCEEDING);
					f_ResCount++;
					}
				else
					{
					f_TransactionA->m_fresh = VERIFY_FAIL;
					
					std::string f_null = ag_cont_VerifySingleTransaction(f_TransactionA, VERIFY_FAIL);
					}
				}
			}
		}

	return f_Result;
}

std::string ag_cont_VerifySingleTransaction(CubeTransaction* f_Transaction, bool f_initialVerified)
{
	int f_rotoner = 1;

	bool f_Verified = f_initialVerified;

	if(f_initialVerified == true)
		{
		if(f_Transaction->m_confirmation < 6)
			{
			float f_combin = 0.0f;

			for(int f_Jet = 0; f_Jet < f_Transaction->m_txin.size(); f_Jet++)
				{
				if((f_Transaction->m_txin[f_Jet]->m_gnshareid > 0) || (f_Transaction->m_txin[f_Jet]->m_vout.compare("Genesis Coin") == 0) || (f_Transaction->m_txin[f_Jet]->m_vout.compare("Genesis Tracking") == 0) || (f_Transaction->m_txin[f_Jet]->m_vout.compare("GenesisTX") == 0))
					{  //genesis share present
					if((f_Transaction->m_txin[f_Jet]->m_vout == "Genesis Tracking") || (f_Transaction->m_txin[f_Jet]->m_vout.compare("GenesisTX") == 0))
						{  //genesis reward
						char rewardquery[1000];

						sprintf(rewardquery, "SELECT reward FROM reward WHERE id = %i", f_Transaction->m_rewardid);

						g_SafeL[0]->acSelectCommand(rewardquery, 2, false);

						int f_RewardLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

						printf("ECN::Stat::: f_RewardLCount %i\n", f_RewardLCount);

						if(f_RewardLCount != 1)
							{
							f_Verified = VERIFY_FAIL;

							f_Transaction->m_fresh = VERIFY_FAIL;
							}
						else //One Reward Row
							{
							float f_Reward = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].c_str());

							if(f_Reward != f_Transaction->m_reward)
								{
								f_Verified = VERIFY_FAIL;

								f_Transaction->m_fresh = VERIFY_FAIL;
								}
							else //in sync, transaction and reward row
								{
								if(f_Reward <= 0.0f || f_Reward > 1000.0f)
									{
									f_Verified = VERIFY_FAIL;

									f_Transaction->m_fresh = VERIFY_FAIL;
									}
								else //resonable reward row
									{
									f_combin += f_Transaction->m_txin[f_Jet]->m_amt;
									}
								}
							}
						}
					}
				else
					{
					/*float f_combout = 0.0f; //gathered tx value
			
					for(int f_tro = 0; f_tro < f_Transaction->m_txout.size(); f_tro++)
						{
						f_combout += f_Transaction->m_txout[f_tro]->m_txoutamt;
					
						//temporary, amount of source check
						if(f_tro >= 1)
							{
							float f_txinvout_value = ag_OwnerBalance(f_Transaction->m_txin[f_Jet]->m_vout);

							if(f_combout > f_txinvout_value)
								{
								f_Verified = VERIFY_FAIL;

								f_Transaction->m_fresh = VERIFY_FAIL;
								}
							}
						else
							{
							if(f_combout > f_Transaction->m_amt)
								{
								f_Verified = VERIFY_FAIL;

								f_Transaction->m_fresh = VERIFY_FAIL;
								}
							}
						}*/
					f_combin += f_Transaction->m_txin[f_Jet]->m_amt;
					}
				}

			//tx Input size test
			if(f_combin != f_Transaction->m_amt)
				{
				f_Verified = VERIFY_FAIL;

				f_Transaction->m_fresh = VERIFY_FAIL;
				}

			float f_combout = 0.0f;

			for(int f_Jet = 0; f_Jet < f_Transaction->m_txout.size(); f_Jet++)
				{
				f_combout += f_Transaction->m_txout[f_Jet]->m_txoutamt;
				}

			//tx Output size test
			if(f_combout != f_Transaction->m_amt)
				{
				f_Verified = VERIFY_FAIL;

				f_Transaction->m_fresh = VERIFY_FAIL;
				}

			if((f_Verified == true) && (f_Transaction->m_txin[0]->m_gnshareid <= 0) && (f_Transaction->m_txin[0]->m_gnshareid != -2) && (f_Transaction->m_txin[0]->m_vout.compare("Genesis Coin") != 0) && (f_Transaction->m_txin[0]->m_vout.compare("Genesis Tracking") != 0))
				{
				for(int f_helly = 0; f_helly < f_Transaction->m_txin.size(); f_helly++)
					{
					CubeTXIN* f_txin = f_Transaction->m_txin[f_helly];

					if(f_txin->m_vout.compare("GenesisTX") != 0)
						{ //REAL A-TO-B
						f_Verified = ag_VerifyTXIN(f_txin, f_Transaction->m_amt);
						}
					else
						{ //Genesis TX Check Reward Board
						char rewardquery[1000];

						sprintf(rewardquery, "SELECT reward FROM reward WHERE id = %i", f_Transaction->m_rewardid);

						g_SafeL[0]->acSelectCommand(rewardquery, 2, false);

						int f_RewardLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

						printf("ECN::Stat::: f_RewardLCount %i\n", f_RewardLCount);

						if(f_RewardLCount != 1)
							{
							f_Verified = VERIFY_FAIL;

							f_Transaction->m_fresh = VERIFY_FAIL;
							}
						else //One Reward Row
							{
							float f_Reward = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].c_str());

							if(f_Reward != f_Transaction->m_reward)
								{
								f_Verified = VERIFY_FAIL;

								f_Transaction->m_fresh = VERIFY_FAIL;
								}
							else //in sync, transaction and reward row
								{
								if(f_Reward <= 0.0f || f_Reward > 1000.0f)
									{
									f_Verified = VERIFY_FAIL;

									f_Transaction->m_fresh = VERIFY_FAIL;
									}
								else //resonable reward row
									{
									if(f_Transaction->m_amt > (150.0f * f_Reward))
										{
										f_Verified = VERIFY_FAIL;

										f_Transaction->m_fresh = VERIFY_FAIL;
										}
									}
								}
							}
						}
					}
				}
			}
		else
			{
			f_Verified = VERIFY_SUCCEEDING;

			f_Transaction->m_fresh = VERIFY_FAIL;
			}
		}
		
	if(f_initialVerified == VERIFY_FAIL)
		{
		f_Verified = VERIFY_FAIL;
		
		f_Transaction->m_fresh = VERIFY_FAIL;
		}
		
	return ag_cont_VerifyResult(f_Transaction, f_Verified);
}

std::string ag_cont_VerifyResult(CubeTransaction* f_Transaction, bool f_initialVerified)
{
	if(f_initialVerified == true)
		{ //stack tx hash
		bool f_Verified = true;

		if(f_Transaction->m_fresh == true)
			{
			f_Transaction->m_confirmation++;

			if(f_Transaction->m_confirmation == 6)
				{	//final confirmation
				if(f_Transaction->m_txin[0]->m_gnshareid != -2)
					{ //not change transaction
					std::vector<float> f_vec_finalBalance;

					f_vec_finalBalance.clear();

					float f_combout = f_Transaction->m_amt;

					for(int f_Jet = 0; f_Jet < f_Transaction->m_txin.size(); f_Jet++)
						{ //TXIN
						float f_owner_value = ag_OwnerBalance(f_Transaction->m_txin[f_Jet]->m_vout);

						float f_finalBalance = f_owner_value - f_Transaction->m_txin[f_Jet]->m_amt;

						if(f_finalBalance < 0.0f) //not enough credit
							{
							f_Transaction->m_confirmation--;

							f_Verified = false;

							f_Transaction->m_fresh = false;
							}
						else
							{
							f_vec_finalBalance.push_back(f_finalBalance);
							}
						}

					if(f_Verified == true)
						{
						for(int f_Jet = 0; f_Jet < f_Transaction->m_txin.size(); f_Jet++)
							{ //TXIN
							ag_UpdateOwnerBalance(f_Transaction->m_txin[f_Jet]->m_vout, f_vec_finalBalance[f_Jet]);
							}
						}
					}

				if(f_Verified == true)
					{
					for(int f_Jet = 0; f_Jet < f_Transaction->m_txout.size(); f_Jet++)
						{ //TXOUT
						if(f_Transaction->m_txin[0]->m_gnshareid != -2)
							{
							if(f_Transaction->m_txout[f_Jet]->m_adrid >= 0)
								{
								float f_owner_value = ag_OwnerBalance(f_Transaction->m_txout[f_Jet]->m_owner);

								float f_finalBalance = f_owner_value + f_Transaction->m_txout[f_Jet]->m_txoutamt;

								ag_UpdateOwnerBalance(f_Transaction->m_txout[f_Jet]->m_owner, f_finalBalance);

								f_Transaction->m_txout[f_Jet]->m_owneramt = f_finalBalance;
								}
							else // insert fee owner - YOU
								{
								f_Transaction->m_txout[f_Jet]->m_adrid = -3;

								f_Transaction->m_txout[f_Jet]->m_owner = g_Wallet->GetAdr();

								float f_owner_value = ag_OwnerBalance(f_Transaction->m_txout[f_Jet]->m_owner);

								float f_finalBalance = f_owner_value + f_Transaction->m_txout[f_Jet]->m_txoutamt;

								ag_UpdateOwnerBalance(f_Transaction->m_txout[f_Jet]->m_owner, f_finalBalance);

								f_Transaction->m_txout[f_Jet]->m_owneramt = f_finalBalance;
								}
							}
						else
							{ // Change Transaction
							float f_owner_value = ag_OwnerBalance(f_Transaction->m_txout[f_Jet]->m_owner);

							float f_finalBalance = f_owner_value + f_Transaction->m_txout[f_Jet]->m_txoutamt;

							f_Transaction->m_txout[f_Jet]->m_owneramt = f_finalBalance;
							}
						}
					}
				}
			
			if(f_Verified == true)
				{
				f_Transaction->acHash();

				std::string f_Result = f_Transaction->m_Hash;

				f_Transaction->acUpdateSync();

				printf("ECN::Transaction Verified txid = %i\n", f_Transaction->m_txid);

				return f_Result;
				}
			else
				{
				if(f_Transaction->m_fresh == false)
					{
					//delete transaction or flag as suspicious
					printf("ECN::Transaction failed Verification txid = %i\n", f_Transaction->m_txid);

					char* f_txfailvalue[1];
					char* f_txfailfield[1];
					char* f_txfailwhere[1];

					f_txfailvalue[0] = (char*)malloc(sizeof(char) * 1024);
					f_txfailfield[0] = (char*)malloc(sizeof(char) * 1024);
					f_txfailwhere[0] = (char*)malloc(sizeof(char) * 1024);

					sprintf(f_txfailfield[0], "status");
					sprintf(f_txfailvalue[0], "%i", -5);
					sprintf(f_txfailwhere[0], "id = %i", f_Transaction->m_txid);

					g_SafeL[0]->Update("transactions", (const char **)f_txfailfield, (const char **)f_txfailvalue, 1, f_txfailwhere[0], 2, false);

					f_Transaction->m_status = -5;

					return "00000000000000000000000000000001";
					}
				else
					{	//unverified yet to be checked transaction hash of 1
					if(f_Transaction->m_confirmation < 6)
						{
						return "00000000000000000000000000000001";
						}
					else
						{
						return f_Transaction->m_Hash;
						}
					}
				}
			}
		else
			{
			return f_Transaction->m_Hash;
			}
		}
	else
		{
		if(f_Transaction->m_fresh == false)
			{
			//delete transaction or flag as suspicious
			printf("ECN::Transaction failed Verification txid = %i\n", f_Transaction->m_txid);

			char* f_txfailvalue[1];
			char* f_txfailfield[1];
			char* f_txfailwhere[1];

			f_txfailvalue[0] = (char*)malloc(sizeof(char) * 1024);
			f_txfailfield[0] = (char*)malloc(sizeof(char) * 1024);
			f_txfailwhere[0] = (char*)malloc(sizeof(char) * 1024);

			sprintf(f_txfailfield[0], "status");
			sprintf(f_txfailvalue[0], "%i", -5);
			sprintf(f_txfailwhere[0], "id = %i", f_Transaction->m_txid);

			g_SafeL[0]->Update("transactions", (const char **)f_txfailfield, (const char **)f_txfailvalue, 1, f_txfailwhere[0], 2, false);

			f_Transaction->m_status = -5;

			return "00000000000000000000000000000001";
			}
		else
			{	//unverified yet to be checked transaction hash of 1
			if(f_Transaction->m_confirmation < 6)
				{
				return "00000000000000000000000000000001";
				}
			else
				{
				return f_Transaction->m_Hash;
				}
			}
		}

	return "00000000000000000000000000000001";
}

CKey* ag_GenerateAddress(int f_Prefix)
{
		///////////////
	   // Research
	  // Entropy
	 // Key
	// Privacy
#if 0
	// Pass in a random blinding seed to the secp256k1 context.
    std::vector<unsigned char> vseed;
	vseed.clear();

    std::random_device engine;
	for(int f_Jet = 0; f_Jet < 32; f_Jet++)
		{
		unsigned int f_x = engine();
		unsigned char f_ch[2];
		memcpy(f_ch, (char*)&f_x, sizeof(unsigned int));
		vseed.push_back(f_ch[0]);
		vseed.push_back(f_ch[1]);
		}

	printf("Random binary data: ");

	for(int f_JJ = 0; f_JJ < vseed.size(); f_JJ++)
		{
		printf("%c", vseed[f_JJ]);
		}
#endif

#if 0
	ECC_Start();

	printf("\nSanity = %i\n", ECC_InitSanityCheck());

	CKey key;
	key.MakeNewKey(true);

	printf("Private key is %i chars long: %s\n", key.size(), key.begin());
	printf("Private key WIF base58: %s\n", ((std::string)EncodeBase58((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)key.keydata)).c_str());

	CExtKey extkey;
	extkey.SetMaster((unsigned char *)key.begin(), key.size());
	CExtPubKey extpubkey = extkey.Neuter();
	printf("b58privatekey size(%i): %s\n", extkey.key.size(), extkey.key.begin());
	printf("b58publickey size(%i): %s\n", extpubkey.key.size(), extpubkey.key.begin());

	//unsigned char data[74];
	//extkey.Encode(data);
	//extpubkey.Encode(data);
	//CBitcoinExtKey b58key;
	//b58key.SetKey(extkey);
	//printf("b58privatekey: %s\n", b58key.ToString());

	//CPubKey pubkey = key.GetPubKey();
	

	//const unsigned char* f_MyPublicKeyunsigchar = pubkey.begin();

	//printf("KEY PASS %i\n", key.VerifyPubKey(pubkey));
	//printf("Public key is %i chars long: %s\n", pubkey.size(), f_MyPublicKeyunsigchar);

	//std::vector<unsigned char, secure_allocator<unsigned char> > keydata;
	//keydata.clear();
	//for(int f_Jet = 0; f_Jet < pubkey.size(); f_Jet++)
	//	{
	//	keydata.push_back(pubkey.vch[f_Jet]);
	//	}

	//printf("base58: %s\n", ((std::string)EncodeBase58((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)keydata)).c_str());

	//CBitcoinExtPubKey b58pubkey;
	//b58pubkey.SetKey(extpubkey);
	//printf("Bitcoin EXT Public Key Address: %s\n", b58pubkey.ToString());
#endif

	//ECC_Start();

#if 0
#if 0
	printf("\nSanity = %i\n", ECC_InitSanityCheck());
#endif

	CKey* key = new CKey(f_Prefix);
	key->MakeNewKey(true);

	CPubKey pubkey = key->GetPubKey();
	printf("KEY PASS %i\n", key->VerifyPubKey(pubkey));

	for(int f = 0; f < pubkey.size(); f++)
		{
		printf("%c", pubkey[f]);
		}

	printf("::::Length = %i\n", 65);

	std::vector<unsigned char, secure_allocator<unsigned char> > keydata;
	keydata.clear();
	for(int f_Jet = 0; f_Jet < 32; f_Jet++)
		{
		keydata.push_back(pubkey.vch[f_Jet]);
		}

	std::string f_Store;
	f_Store.clear();

	//ag_bin2hex((char*)f_Store.c_str(), keydata, keydata.size());
	char f_Char[64];
	int i;
	for(i = 0; i < 32; i++)
		{
		sprintf((char*)f_Char + (i * 2), "%02x", keydata[i]);
		}

	printf("Bitcoin Serialized PubKey s(%i): %s\n", 64, f_Char);

	uint256 hash;
	CHash256().Write(&keydata[0], 32).Finalize(hash.begin());
	
	char f_Char3[64];
	int i3;
	for(i3 = 0; i3 < 32; i3++)
		{
		sprintf((char*)f_Char3 + (i3 * 2), "%02x", (unsigned char *)hash.begin());
		}

	printf("Bitcoin Serialized PubKey s(%i): %s\n", 64, hash.GetHex().c_str());

	uint160 hash4;
	CHash160().Write(hash.begin(), 32).Finalize(hash4.begin());
	
	char f_Char4[40];
	int i4;
	for(i4 = 0; i4 < 20; i4++)
		{
		sprintf((char*)f_Char4 + (i4 * 2), "%02x", (unsigned char *)hash4.begin());
		}

	printf("Bitcoin Serialized ripem(sha256()) PubKey s(%i): %s\n", 40, hash4.GetHex().c_str());


	//Sign(hash, vchSig);
	//return pubkey.Verify(hash, vchSig);

	//uint160 h160 = Hash160(sha256((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)keydata));

	std::vector<unsigned char> f_vec_UnsignedChar5;

	unsigned char *f_p5 = new unsigned char[20];

	ag_hex2bin(f_p5, hash4.GetHex().c_str(), hash4.GetHex().size());

	for(int f_lm5 = 0; f_lm5 < 20; f_lm5++)
		{
		f_vec_UnsignedChar5.push_back(f_p5[f_lm5]);
		}

	printf("Bitcoin Address: %s\n", ((std::string)EncodeBase58((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)f_vec_UnsignedChar5)).c_str());

#if 0
	CPubKey pubkey = key->GetPubKey();
	printf("KEY PASS %i\n", key->VerifyPubKey(pubkey));

	for(int f = 0; f < pubkey.size(); f++)
		{
		printf("%c", pubkey[f]);
		}

	std::vector<unsigned char, secure_allocator<unsigned char> > keydata;
	keydata.clear();
	for(int f_Jet = 0; f_Jet < pubkey.size(); f_Jet++)
		{
		keydata.push_back(pubkey[f_Jet]);
		}

	printf("Bitcoin Address: %s\n", ((std::string)EncodeBase58((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)keydata)).c_str());
#endif
#endif

	while(true)
		{
		std::string f_Address;
		f_Address.clear();

		CKey* key = new CKey(f_Prefix);
		key->MakeNewKey(true);

		CPubKey pubkey = key->GetPubKey();
		bool f_keypass = key->VerifyPubKey(pubkey);

		CubeCKey* f_CCKey = new CubeCKey(*key);
		f_CCKey->m_PubKey = pubkey;

		std::vector<unsigned char, secure_allocator<unsigned char> > keydata;
		keydata.clear();
		for(int f_Jet = 0; f_Jet < 32; f_Jet++)
			{
			keydata.push_back(pubkey.vch[f_Jet]);
			}

#if 1
		char f_Char[64];
		int i;
		for(i = 0; i < 32; i++)
			{
			sprintf((char*)f_Char + (i * 2), "%02x", keydata[i]);
			}

		key->m_pubkey = f_Char;

		printf("Bitcoin Serialized PubKey s(%i): %s\n", 64, f_Char);
#endif

		uint256 hash;
		CHash256().Write(&keydata[0], 32).Finalize(hash.begin());

		uint160 hash4;
		CHash160().Write(hash.begin(), 32).Finalize(hash4.begin());

#if 0
		printf("Bitcoin Serialized ripem(sha256()) PubKey s(%i): %s\n", 40, hash4.GetHex().c_str());
#endif

		std::vector<unsigned char> f_vec_UnsignedChar5;

		unsigned char *f_p5 = new unsigned char[20];

		ag_hex2bin(f_p5, hash4.GetHex().c_str(), hash4.GetHex().size());

		for(int f_lm5 = 0; f_lm5 < 20; f_lm5++)
			{
			f_vec_UnsignedChar5.push_back(f_p5[f_lm5]);
			}

		f_CCKey->m_str_Address = ((std::string)EncodeBase58((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)f_vec_UnsignedChar5)).c_str();
		f_Address = f_CCKey->m_str_Address;
			
		printf("GenerateAddress-%s\n", f_Address.c_str());

		char* g_addrvalue[4];

		g_addrvalue[0] = (char*)malloc(sizeof(char) * 256);
		g_addrvalue[1] = (char*)malloc(sizeof(char) * 256);
		g_addrvalue[2] = (char*)malloc(sizeof(char) * 256);
		g_addrvalue[3] = (char*)malloc(sizeof(char) * 256);

		sprintf(g_addrvalue[0], "%i", 1);
		sprintf(g_addrvalue[1], "%i", 3);
		sprintf(g_addrvalue[2], "%s", f_Address.c_str());
		sprintf(g_addrvalue[3], "%f", 0.0f);

		g_addrfield[0] = (char*)malloc(sizeof(char) * 256);
		g_addrfield[1] = (char*)malloc(sizeof(char) * 256);
		g_addrfield[2] = (char*)malloc(sizeof(char) * 256);
		g_addrfield[3] = (char*)malloc(sizeof(char) * 256);

		sprintf(g_addrfield[0], "assetid");
		sprintf(g_addrfield[1], "assetofficeid");
		sprintf(g_addrfield[2], "owner");
		sprintf(g_addrfield[3], "amt");

		int f_Int = 1;
		if(!g_SafeL[0])
			{
			g_SafeL[0] = new icSafeL(0);
			g_SafeL[0]->Initialize();

			f_Int = g_SafeL[0]->Connect("localhost", "root", "fracTALIZe18", "globalscapedb", 3306);
			}

		printf("Connected to ecoin server...\n");

		Cube::g_Count_Muti.ac_Fire();
		Cube::g_Other_Muti.ac_Fire();
		Cube::g_Share_Muti.ac_Fire();

		char adrquery[1000];
		sprintf(adrquery, "SELECT id FROM address WHERE owner = '%s'", f_Address.c_str());// WHERE name = '%s' AND pass = MD5('%s')", i_name, i_password);
																										 //Run the query
		g_SafeL[0]->acSelectCommand(adrquery, false, false);
		int f_AdrLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

		printf("ECN::Stat::: f_AdrLCount %i\n", f_AdrLCount);

		//assume remote connection for windows
		if((f_Int) && (f_AdrLCount == 0))
			{
			int f_AddressUniqueID = g_SafeL[0]->Insert("address", (const char **)g_addrfield, (const char **)g_addrvalue, 4, false, false);

			printf("Unique Payment Address Found %i Addresses\n", f_AddressUniqueID);

			Cube::g_Count_Muti.ac_Free();
			Cube::g_Other_Muti.ac_Free();
			Cube::g_Share_Muti.ac_Free();

			key->m_owner = f_Address;

			return key;
			}

		Cube::g_Count_Muti.ac_Free();
		Cube::g_Other_Muti.ac_Free();
		Cube::g_Share_Muti.ac_Free();
		}
}

char* ag_ClearChar(int f_Size)
{
	char* f_Char = new char[f_Size];

	for(int f_XY = 0; f_XY < f_Size; f_XY++)
		{
		f_Char[f_XY] = 0;
		}

	return f_Char;
}

void Cube::CubeTransaction::acHash(void)
{
	std::string f_InputHash;
	f_InputHash.clear();

	for(int f_x = 0; f_x < m_txin.size(); f_x++)
		{
		char* f_Char = ag_ClearChar(32);
		sprintf(f_Char, "%i", m_txin[f_x]->m_txid);
		f_InputHash += f_Char;
		f_Char = ag_ClearChar(32);
		sprintf(f_Char, "%i", m_txin[f_x]->m_prvtxid);
		f_InputHash += f_Char;
		f_Char = ag_ClearChar(32);
		sprintf(f_Char, "%i", m_txin[f_x]->m_prvtxoutid);
		f_InputHash += f_Char;
		f_Char = ag_ClearChar(32);
		sprintf(f_Char, "%i", m_txin[f_x]->m_gnshareid);
		f_InputHash += f_Char;
		f_InputHash += m_txin[f_x]->m_vout;
		f_InputHash += m_txin[f_x]->m_pubkey;
		f_InputHash += m_txin[f_x]->m_sigstr;
		}

	for(int f_y = 0; f_y < m_txout.size(); f_y++)
		{
		char* f_Char = ag_ClearChar(32);
		sprintf(f_Char, "%i", m_txout[f_y]->m_txid);
		f_InputHash += f_Char;
		f_Char = ag_ClearChar(32);
		sprintf(f_Char, "%i", m_txout[f_y]->m_adrid);
		f_InputHash += f_Char;
		f_InputHash += m_txout[f_y]->m_owner;
		f_InputHash += m_txout[f_y]->m_pubkey;
		f_Char = ag_ClearChar(64);
		sprintf(f_Char, "%f", m_txout[f_y]->m_txoutamt);
		f_InputHash += f_Char;
		f_Char = ag_ClearChar(64);
		sprintf(f_Char, "%f", m_txout[f_y]->m_owneramt);
		f_InputHash += f_Char;
		}

	//add extra data like status etc.
	char* f_Char = ag_ClearChar(64);
	sprintf(f_Char, "%i", m_amt);
	f_InputHash += f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%f", m_fee);
	f_InputHash += f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_txid);
	f_InputHash += f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_jobid);
	f_InputHash += f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_confirmation);
	f_InputHash += f_Char;
	f_InputHash += m_hdid;

	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%f", m_reward);
	f_InputHash += f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_rewardid);
	f_InputHash += f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_type);
	f_InputHash += f_Char;

	g_hasha.init(); //reset hasher state
	g_hasha.process(f_InputHash.begin(), f_InputHash.end());
	g_hasha.finish();
	picosha2::get_hash_hex_string(g_hasha, m_Hash);

	printf("m_hash of transaction %s\n", m_Hash.c_str());
}

void Cube::CubeTransaction::acUpdateSync(void)
{
	char* g_syncvalue[6];
	char* g_syncfield[6];
	char* g_syncwhere[1];

	g_syncwhere[0] = (char*)malloc(sizeof(char) * 256);

	for(int f_s = 0; f_s < 6; f_s++)
		{
		g_syncvalue[f_s] = (char*)malloc(sizeof(char) * 256);
		g_syncfield[f_s] = (char*)malloc(sizeof(char) * 256);
		}

	char* g_txoutsyncvalue[4];
	char* g_txoutsyncfield[4];
	char* g_txoutsyncwhere[1];

	g_txoutsyncwhere[0] = (char*)malloc(sizeof(char) * 256);

	for(int f_s2 = 0; f_s2 < 4; f_s2++)
		{
		g_txoutsyncvalue[f_s2] = (char*)malloc(sizeof(char) * 256);
		g_txoutsyncfield[f_s2] = (char*)malloc(sizeof(char) * 256);
		}

	sprintf(g_syncfield[0], "shareid");
	sprintf(g_syncfield[1], "gnshareid");
	sprintf(g_syncfield[2], "jobid");
	sprintf(g_syncfield[3], "hash");
	sprintf(g_syncfield[4], "amt");
	sprintf(g_syncfield[5], "confirmation");

	sprintf(g_txoutsyncfield[0], "owner");
	sprintf(g_txoutsyncfield[0], "adrid");
	sprintf(g_txoutsyncfield[0], "txoutamt");
	sprintf(g_txoutsyncfield[1], "owneramt");

	sprintf(g_syncvalue[0], "%i", 0);
	sprintf(g_syncvalue[1], "%i", m_txin[0]->m_gnshareid);
	sprintf(g_syncvalue[2], "%i", m_jobid);
	sprintf(g_syncvalue[3], "%s", m_Hash.c_str());
	sprintf(g_syncvalue[4], "%f", m_amt);
	sprintf(g_syncvalue[5], "%i", m_confirmation);

	sprintf(g_syncwhere[0], "id = %i", m_txid);

	int f_Int = 1;
	if(!g_SafeL[0])
		{
		g_SafeL[0] = new icSafeL(0);
		g_SafeL[0]->Initialize();

		f_Int = g_SafeL[0]->Connect("bitcoin-office.com", "root", "IntegerProperty18", "globalscapedb", 3306);
		}

	printf("Connected to ecoin server...\n");

	//assume remote connection for windows
	if(f_Int)
		{
		g_SafeL[0]->Update("transactions", (const char **)g_syncfield, (const char **)g_syncvalue, 6, g_syncwhere[0], false, false);

		for(int f_Int = 0; f_Int < m_txout.size(); f_Int++)
			{
			sprintf(g_txoutsyncvalue[0], "%s", m_txout[f_Int]->m_owner.c_str());
			sprintf(g_txoutsyncvalue[0], "%i", m_txout[f_Int]->m_adrid);
			sprintf(g_txoutsyncvalue[0], "%f", m_txout[f_Int]->m_txoutamt);
			sprintf(g_txoutsyncvalue[1], "%f", m_txout[f_Int]->m_owneramt);

			sprintf(g_txoutsyncwhere[0], "id = %i", m_txout[f_Int]->m_txoutid);

			g_SafeL[0]->Update("txout", (const char **)g_txoutsyncfield, (const char **)g_txoutsyncvalue, 2, g_txoutsyncwhere[0], false, false);
			}
		}
}

void Cube::CubeTransaction::acSynchronize(void)
{
	char* g_syncvalue[14];
	char* g_syncfield[14];

	for(int f_s = 0; f_s < 14; f_s++)
		{
		g_syncvalue[f_s] = (char*)malloc(sizeof(char) * 256);
		g_syncfield[f_s] = (char*)malloc(sizeof(char) * 256);
		}

	char* g_txinsyncvalue[6];
	char* g_txinsyncfield[6];

	for(int f_s1 = 0; f_s1 < 6; f_s1++)
		{
		g_txinsyncvalue[f_s1] = (char*)malloc(sizeof(char) * 256);
		g_txinsyncfield[f_s1] = (char*)malloc(sizeof(char) * 256);
		}

	char* g_txoutsyncvalue[6];
	char* g_txoutsyncfield[6];

	for(int f_s2 = 0; f_s2 < 6; f_s2++)
		{
		g_txoutsyncvalue[f_s2] = (char*)malloc(sizeof(char) * 256);
		g_txoutsyncfield[f_s2] = (char*)malloc(sizeof(char) * 256);
		}

	sprintf(g_syncfield[0], "status");
	sprintf(g_syncfield[1], "locktime");
	sprintf(g_syncfield[2], "confirmation");
	sprintf(g_syncfield[3], "hdid");
	sprintf(g_syncfield[4], "shareid");
	sprintf(g_syncfield[5], "gnshareid");
	sprintf(g_syncfield[6], "jobid");
	sprintf(g_syncfield[7], "rewardid");
	sprintf(g_syncfield[8], "hash");
	sprintf(g_syncfield[9], "amt");
	sprintf(g_syncfield[10], "fee");
	sprintf(g_syncfield[11], "reward");
	sprintf(g_syncfield[12], "owner");
	sprintf(g_syncfield[13], "typed");

	sprintf(g_txinsyncfield[0], "transactionid");
	sprintf(g_txinsyncfield[1], "vout");
	sprintf(g_txinsyncfield[2], "pubkey");
	sprintf(g_txinsyncfield[3], "vsign");
	sprintf(g_txinsyncfield[4], "amt");
	sprintf(g_txinsyncfield[5], "gnshareid");

	sprintf(g_txoutsyncfield[0], "transactionid");
	sprintf(g_txoutsyncfield[1], "adrid");
	sprintf(g_txoutsyncfield[2], "owner");
	sprintf(g_txoutsyncfield[3], "pubkey");
	sprintf(g_txoutsyncfield[4], "txoutamt");
	sprintf(g_txoutsyncfield[5], "owneramt");

	sprintf(g_syncvalue[0], "%i", 1);
	sprintf(g_syncvalue[1], "%i", 1);// f_Address.c_str());
	sprintf(g_syncvalue[2], "%i", 0);
	sprintf(g_syncvalue[3], "%s", m_hdid.c_str());
	sprintf(g_syncvalue[4], "%i", 0);
	sprintf(g_syncvalue[5], "%i", m_txin[0]->m_gnshareid);
	sprintf(g_syncvalue[6], "%i", m_jobid);
	sprintf(g_syncvalue[7], "%i", m_rewardid);
	sprintf(g_syncvalue[8], "%s", m_Hash.c_str());
	sprintf(g_syncvalue[9], "%f", m_amt);
	sprintf(g_syncvalue[10], "%f", m_fee);
	sprintf(g_syncvalue[11], "%f", m_reward);
	sprintf(g_syncvalue[12], "%s", m_txout[0]->m_owner.c_str());
	sprintf(g_syncvalue[13], "%i", m_type);

	int f_Int = 1;
	if(!g_SafeL[0])
		{
		g_SafeL[0] = new icSafeL(0);
		g_SafeL[0]->Initialize();

		f_Int = g_SafeL[0]->Connect("bitcoin-office.com", "root", "IntegerProperty18", "globalscapedb", 3306);
		}

	printf("Connected to ecoin server...\n");

	char syncquery[1000];
	sprintf(syncquery, "SELECT id FROM transactions WHERE hash = '%s'", m_Hash.c_str());

	g_SafeL[0]->acSelectCommand(syncquery, false, false);
	int f_SyncLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

	printf("ECN::Stat::: f_SyncLCount %i\n", f_SyncLCount);

	//assume remote connection for windows
	if((f_Int) && (f_SyncLCount == 0))
		{
		int f_SyncUniqueID = g_SafeL[0]->Insert("transactions", (const char **)g_syncfield, (const char **)g_syncvalue, 14, false, false);

		printf("Unique Transaction Made ID %i\n", f_SyncUniqueID);

		sprintf(g_txinsyncvalue[0], "%i", f_SyncUniqueID);
		sprintf(g_txinsyncvalue[1], "%s", m_txin[0]->m_vout.c_str());
		sprintf(g_txinsyncvalue[2], "%s", m_txin[0]->m_pubkey.c_str());
		sprintf(g_txinsyncvalue[3], "%s", m_txin[0]->m_sigstr.c_str());// f_Address.c_str());
		sprintf(g_txinsyncvalue[4], "%f", m_amt);
		sprintf(g_txinsyncvalue[5], "%i", m_txin[0]->m_gnshareid);

		int f_TXINID = g_SafeL[0]->Insert("txin", (const char **)g_txinsyncfield, (const char **)g_txinsyncvalue, 6, false, false);

		for(int f_Int = 0; f_Int < m_txout.size(); f_Int++)
			{
			sprintf(g_txoutsyncvalue[0], "%i", f_SyncUniqueID);
			sprintf(g_txoutsyncvalue[1], "%i", m_txout[f_Int]->m_adrid);
			sprintf(g_txoutsyncvalue[2], "%s", m_txout[f_Int]->m_owner.c_str());
			sprintf(g_txoutsyncvalue[3], "%s", m_txout[f_Int]->m_pubkey.c_str());
			sprintf(g_txoutsyncvalue[4], "%f", m_txout[f_Int]->m_txoutamt);
			sprintf(g_txoutsyncvalue[5], "%f", m_txout[f_Int]->m_owneramt);

			int f_TXOUTID = g_SafeL[0]->Insert("txout", (const char **)g_txoutsyncfield, (const char **)g_txoutsyncvalue, 6, false, false);
			}
		}
}

int ag_GenerateTransaction(std::string f_A, std::string f_B, float f_amt)
	{
		///////////////
	   // Research
	  // Entropy
	 // Key
	// Privacy
	Cube::g_Count_Muti.ac_Fire();
	Cube::g_Other_Muti.ac_Fire();
	Cube::g_Share_Muti.ac_Fire();

	//ECC_Start();

	CKey* key = nullptr;

	bool f_Found = false;
	int f_Index = 0;
	for(int f_Helly = 0; f_Helly < g_Wallet->m_vec_Key.size(); f_Helly++)
		{
		if(g_Wallet->m_vec_Key[f_Helly]->m_owner.size() >= 27)
			{
			if(g_Wallet->m_vec_Key[f_Helly]->m_owner.compare(f_A) == 0)
				{
				f_Found = true;
				f_Index = f_Helly;
				}
			}
		}

	if(f_Found)
		{
		key = g_Wallet->m_vec_Key[f_Index];
		}
	else
		{
		for(;;)
			{
			}
		}

	if(key)
		{  // OK pass key acquisition
		  // assums single in/out
		 /////////////////////
		// Prev Transaction
		CubeTransaction* f_prvTX = ag_get_TXfromvout(f_A.c_str());
		//fixme: set m_txid in transaction pull
																							//Run the query
		//icSafeLResultSet* prtxnresult = g_SafeL[0]->acSelectCommand(prtxnquery, false, false);
		//int f_prtxnLCount = prtxnresult->GetRecordCount();

		CubeTransaction* f_tx = new CubeTransaction(f_A, f_B, f_amt);

		f_tx->m_reward = 0.0f;
		f_tx->m_rewardid = -1;

		CubeTXOUT* f_txout_fee = new CubeTXOUT();

		f_txout_fee->m_adrid = -2;
		f_txout_fee->m_owner = "feeowner";
		f_txout_fee->m_pubkey = "feepubkey";
		f_txout_fee->m_txoutamt = 0.01;
		f_txout_fee->m_owneramt = 0;

		f_tx->m_txout.push_back(f_txout_fee);

		if(1)
			{
			//icDatabaseRecord prtxnrow = prtxnresult->NextRecord();
			//int f_transactionid = atoi(prtxnrow[1]);

			//char prtxn1query[1000];
			//sprintf(prtxn1query, "SELECT id, owneramt FROM txout WHERE transactionid = %s", f_transactionid);// WHERE name = '%s' AND pass = MD5('%s')", i_name, i_password);
																										//Run the query
			//icSafeLResultSet* prtxn1result = g_SafeL[0]->acSelectCommand(prtxn1query, false, false);
			//icDatabaseRecord prtxn1row = prtxnresult->NextRecord();

			float f_owneramt = ag_OwnerBalance(f_prvTX->m_txout[0]->m_owner);

			if(f_amt > f_owneramt)
				{
				printf("ECN::transaction failed not enough ecoin in prvout\n");

				Cube::g_Count_Muti.ac_Free();
				Cube::g_Other_Muti.ac_Free();
				Cube::g_Share_Muti.ac_Free();

				return 3;
				}
			else
				{	// Eviscerate the coin
				for(int f_Jet = 0; f_Jet < f_tx->m_txin.size(); f_Jet++)
					{
					char* f_balupvalue[1];
					char* f_balupfield[1];
					char* f_balupwhere[1];

					f_balupvalue[0] = (char*)malloc(sizeof(char) * 1024);
					f_balupfield[0] = (char*)malloc(sizeof(char) * 1024);
					f_balupwhere[0] = (char*)malloc(sizeof(char) * 1024);

					float f_OwnerBalance = ag_OwnerBalance(f_tx->m_txin[0]->m_vout);
					float f_finalBalance = f_OwnerBalance - f_amt;

					sprintf(f_balupfield[0], "amt");
					sprintf(f_balupvalue[0], "%f", f_finalBalance);
					sprintf(f_balupwhere[0], "owner = '%s'", f_tx->m_txin[0]->m_vout.c_str());

					g_SafeL[0]->Update("address", (const char **)f_balupfield, (const char **)f_balupvalue, 1, f_balupwhere[0], false, false);
					}

				if(f_amt != f_owneramt)
					{
					CubeTXOUT* f_txout = new CubeTXOUT();

					f_txout->m_owner = g_Wallet->GetNextChangeKey()->m_owner;
					f_txout->m_adrid = 3;

					float f_change_value = ag_OwnerBalance(f_txout->m_owner);

					f_change_value += f_owneramt - f_amt;
					
					f_txout->m_txoutamt = f_owneramt - f_amt;
					f_txout->m_owneramt = f_change_value;
					f_tx->m_txout.push_back(f_txout);

					CubeTransaction* f_changetoadrtx = new CubeTransaction(f_txout->m_owner, f_A, f_change_value);

					f_changetoadrtx->m_txin[0]->m_gnshareid = -2;

					f_changetoadrtx->acHash();

					unsigned char k[32];

					ag_hex2bin(k, f_changetoadrtx->m_Hash.c_str(), 64);

					uint256& f_256uint = reinterpret_cast<uint256&>(k);

					bool f_res = key->Sign(f_256uint, f_changetoadrtx->m_txin[0]->m_sig);

					char f_k[142];

					ag_bin2hex((char*)f_k, f_changetoadrtx->m_txin[0]->m_sig, 71);

					f_changetoadrtx->m_txin[0]->m_sigstr.clear();

					for(int j2o = 0; j2o < 142; j2o++)
						{
						f_changetoadrtx->m_txin[0]->m_sigstr.push_back(f_k[j2o]);
						}

					f_changetoadrtx->m_jobid = g_JobID;

					f_changetoadrtx->acSynchronize();

					printf("ECN::successfully completed synchronisation of return change transaction\n");
					}
				}
			}

		f_tx->acHash();

		unsigned char k[32];

		ag_hex2bin(k, f_tx->m_Hash.c_str(), 64);

		uint256& f_256uint = reinterpret_cast<uint256&>(k);

		bool f_res = key->Sign(f_256uint, f_tx->m_txin[0]->m_sig);

#if 0
		if(!f_res)
			{
			printf("ECN::Failed txvout sign\n");
			for(;;)
				{
				}
			}
#endif

#if 0
		printf("signiture : ");
		for(int j = 0; j < 32; j++)
			{
			printf("%c", f_tx->m_txin[0]->m_sig[j]);
			}
#endif

		char f_k[142];

		ag_bin2hex((char*)f_k, f_tx->m_txin[0]->m_sig, 71);

		f_tx->m_txin[0]->m_sigstr.clear();

		for(int j2o = 0; j2o < 142; j2o++)
			{
			f_tx->m_txin[0]->m_sigstr.push_back(f_k[j2o]);
			}

		f_tx->m_jobid = g_JobID;

		f_tx->acSynchronize();

		Cube::g_Count_Muti.ac_Free();
		Cube::g_Other_Muti.ac_Free();
		Cube::g_Share_Muti.ac_Free();

		printf("ECN::successfully completed synchronisation of transaction\n");
		return 1;
		}
	else
		{
		printf("ECN::transaction failed finding the wallet key for requested address\n");

		Cube::g_Count_Muti.ac_Free();
		Cube::g_Other_Muti.ac_Free();
		Cube::g_Share_Muti.ac_Free();

		return 2;
		}

#if 0
#if 0
	// Pass in a random blinding seed to the secp256k1 context.
    std::vector<unsigned char> vseed;
	vseed.clear();

    std::random_device engine;
	for(int f_Jet = 0; f_Jet < 32; f_Jet++)
		{
		unsigned int f_x = engine();
		unsigned char f_ch[2];
		memcpy(f_ch, (char*)&f_x, sizeof(unsigned int));
		vseed.push_back(f_ch[0]);
		vseed.push_back(f_ch[1]);
		}

	printf("Random binary data: ");

	for(int f_JJ = 0; f_JJ < vseed.size(); f_JJ++)
		{
		printf("%c", vseed[f_JJ]);
		}
#endif

#if 0
	ECC_Start();

	printf("\nSanity = %i\n", ECC_InitSanityCheck());

	CKey key;
	key.MakeNewKey(true);

	printf("Private key is %i chars long: %s\n", key.size(), key.begin());
	printf("Private key WIF base58: %s\n", ((std::string)EncodeBase58((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)key.keydata)).c_str());

	CExtKey extkey;
	extkey.SetMaster((unsigned char *)key.begin(), key.size());
	CExtPubKey extpubkey = extkey.Neuter();
	printf("b58privatekey size(%i): %s\n", extkey.key.size(), extkey.key.begin());
	printf("b58publickey size(%i): %s\n", extpubkey.key.size(), extpubkey.key.begin());

	//unsigned char data[74];
	//extkey.Encode(data);
	//extpubkey.Encode(data);
	//CBitcoinExtKey b58key;
	//b58key.SetKey(extkey);
	//printf("b58privatekey: %s\n", b58key.ToString());

	//CPubKey pubkey = key.GetPubKey();
	

	//const unsigned char* f_MyPublicKeyunsigchar = pubkey.begin();

	//printf("KEY PASS %i\n", key.VerifyPubKey(pubkey));
	//printf("Public key is %i chars long: %s\n", pubkey.size(), f_MyPublicKeyunsigchar);

	//std::vector<unsigned char, secure_allocator<unsigned char> > keydata;
	//keydata.clear();
	//for(int f_Jet = 0; f_Jet < pubkey.size(); f_Jet++)
	//	{
	//	keydata.push_back(pubkey.vch[f_Jet]);
	//	}

	//printf("base58: %s\n", ((std::string)EncodeBase58((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)keydata)).c_str());

	//CBitcoinExtPubKey b58pubkey;
	//b58pubkey.SetKey(extpubkey);
	//printf("Bitcoin EXT Public Key Address: %s\n", b58pubkey.ToString());
#endif

	//ECC_Start();

#if 0
#if 0
	printf("\nSanity = %i\n", ECC_InitSanityCheck());
#endif

	CKey key;
	key.MakeNewKey(true);

#if 0
	CPubKey pubkey = key.GetPubKey();
	printf("KEY PASS %i\n", key.VerifyPubKey(pubkey));

	for(int f = 0; f < pubkey.size(); f++)
		{
		printf("%c", pubkey[f]);
		}

	std::vector<unsigned char, secure_allocator<unsigned char> > keydata;
	keydata.clear();
	for(int f_Jet = 0; f_Jet < pubkey.size(); f_Jet++)
		{
		keydata.push_back(pubkey[f_Jet]);
		}

	printf("Bitcoin Address: %s\n", ((std::string)EncodeBase58((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)keydata)).c_str());
#endif
#endif

	while(true)
		{
		std::string f_Address;
		f_Address.clear();

		CKey key;
		key.MakeNewKey(true);

		CPubKey pubkey = key.GetPubKey();
		bool f_keypass = key.VerifyPubKey(pubkey);

		CubeCKey* f_CCKey(key);
		f_CCKey->m_PubKey = pubkey;

		std::vector<unsigned char, secure_allocator<unsigned char> > keydata;
		keydata.clear();
		for(int f_Jet = 0; f_Jet < pubkey.size(); f_Jet++)
			{
			keydata.push_back(pubkey[f_Jet]);
			}

		f_CCKey->m_str_Address = ((std::string)EncodeBase58((const std::vector<picosha2::byte_t, std::allocator<picosha2::byte_t>> &)keydata)).c_str());
		f_Address = f_CCKey->m_str_Address;
			
		printf("GenerateAddress-%s\n", f_Address.c_str());	
		}
#endif
}

bool ag_addGenesisTracking(int f_gnid)
{
#if 0
	EasClientDeviceInformation^ deviceInformation = ref new EasClientDeviceInformation();
	std::string Id = to_string(deviceInformation->Id.ToString());

	printf("Id = %s\n", Id.c_str());

	int f_jobid = g_JobID + 1;

	char hdquery[1000];
	sprintf(hdquery, "SELECT id FROM transactions WHERE hdid = '%s' AND jobid = %i AND gnshareid > -1 AND owner = '%s'", Id.c_str(), f_jobid, g_Wallet->GetAdr().c_str());

	g_SafeL[0]->acSelectCommand(hdquery, false, false);
	int f_hdLCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();

	printf("ECN::Stat::: f_hdLCount %i\n", f_hdLCount);

	if(f_hdLCount == 0)
		{
		CubeTransaction* f_tx = new CubeTransaction("Genesis Tracking", g_Wallet->GetAdr(), -1);

		f_tx->m_txin[0]->m_gnshareid = f_gnid;
		f_tx->m_jobid = g_JobID + 1;
		f_tx->m_hdid = Id;
		f_tx->m_fee = 0.0f;

		char rewardquery[1000];
		sprintf(rewardquery, "SELECT id, reward, dated FROM reward WHERE assetofficeid = 3 ORDER BY dated DESC LIMIT 1");

		g_SafeL[0]->acSelectCommand(rewardquery, 2, false);

		f_tx->m_rewardid = atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].c_str());
		f_tx->m_reward = atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][1].c_str());

		f_tx->acHash();

		f_tx->acSynchronize();

		return true;
		}
#endif

	return false;
}

bool ag_makeGenesisCoin(void)
{
#if 0
	EasClientDeviceInformation^ deviceInformation = ref new EasClientDeviceInformation();
	std::string Id = to_string(deviceInformation->Id.ToString());

	printf("Id = %s\n", Id.c_str());
#endif

	CubeTransaction* f_tx = new CubeTransaction("Genesis Coin", g_Wallet->GetAdr(), 1.0f);

	f_tx->m_txin[0]->m_gnshareid = -5;

	f_tx->m_jobid = g_JobID + 1;

	//f_tx->m_hdid = Id;

	f_tx->acHash();

	f_tx->acSynchronize();

	return true;
}

#if 0
	{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
	{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
	{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
	{ XMFLOAT3(0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
	{ XMFLOAT3(0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f) },

0, 2, 1, // -x
1, 2, 3,

4, 5, 6, // +x
5, 7, 6,

0, 1, 5, // -y
0, 5, 4,

2, 6, 7, // +y
2, 7, 3,

0, 4, 6, // -z
0, 6, 2,

1, 3, 7, // +z
1, 7, 5,
#endif