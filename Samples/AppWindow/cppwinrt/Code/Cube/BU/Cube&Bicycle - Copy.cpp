/*

Cube&Bicycle - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"
#include "Common\DirectXHelper.h"
#include "DirectXMath.h"

#include <math.h>

#include "Include/Cube.h"

#include "../Code/Work/Contract.h"
#include "../Code/Work/Schedular.h"

using namespace Platform;
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

using namespace concurrency;

using namespace Cube;
using namespace ecoin;

DirectX::XMVECTORF32 g_Origin;
BiMeshContainer* g_MeshContainer;

namespace Cube
{
	float3 g_RandomSeed;
	int g_Fingat = CUBE_TRI_SHOT_A;
	float g_Float = 0.1;
	float g_swit = 0.75f;

	matrix g_model;
	matrix g_view;
	matrix g_projection;

	BiVector g_eye;
	BiVector g_at;

	std::vector<Cube::CubeHESH*> g_HESH;

	BicycleContainer g_BicycleContainer[1];

	float3 g_offsetVec;

	unMutexCC g_Applog_Muti;

	int g_BiStyleID = 0;
	BiStyle* g_BiStyle;
	std::vector<BiStyle*> g_vec_BiStyles;

	int randomFac(void)
		{
		float f_Rand_Max = RAND_MAX;
		float f_Result = (float)Cube::random() * (float)f_Rand_Max;
		int f_Int = f_Result;
		return f_Int;
		}

	float random(void)
		{
		//if(g_Schedular->m_Nomnonce > 0)
		//	{
			//g_Schedular->nonceGetWork(ESL_PATTERN_LAST);
			//g_nonce = g_nonceContract->getnonce(g_nonce);

			//g_nonce = ((float)rand() / 32767);

			g_RandomSeed.x = g_nonce;//g_nonce;
			g_RandomSeed.y = g_nonce;//g_nonce;
			g_RandomSeed.z = g_nonce;//g_nonce;

			float f_Float = frac(sin(dot(g_RandomSeed, float3(12.9898, 78.233, 45.5432))) * 43758.5453);
			//g_RandomSeed.x += (f_Float - 0.5) * 2;
			//g_RandomSeed.y += (frac(sin(dot(g_RandomSeed, float3(12.9898, 78.233, 45.5432))) * 43758.5453) - 0.5) * 2;
			//g_RandomSeed.z += (frac(sin(dot(g_RandomSeed, float3(12.9898, 78.233, 45.5432))) * 43758.5453) - 0.5) * 2;
			//g_RandomSeed.acNorm();

			g_nonce += 1.0f;
			return f_Float;

			//f_Float = (f_Float * 2) - 1;
			//if(f_Float < 0)
			//	{
			//	f_Float *= -1;
			//	}

			/*if(f_Float > 1 || f_Float < 0)
				{
				f_Float = ((float)rand() / 32767);
				}*/

			//return f_Float;
			//}
		//else
		//	{
			//float f_Float = ((float)rand() / 32767);

		//	return f_Float;
		//	}
		}

	CubeKEY* ChooseKEY(int f_Count)
		{
		int f_Index = Cube::randomFac() % g_BicycleContainer[0].vec_Key.size();

		Cube::CubeKEY* f_KEY = g_BicycleContainer[0].vec_Key[f_Index];

		return f_KEY;
		}

	CubeHESH* agSaveHesh(void)
		{
		CubeHESH* f_HESH = new CubeHESH();
		f_HESH->m_ID = g_ID;
		g_ID++;
		g_SelectedHeshID = g_ID;

		f_HESH->m_Timestamp = g_TimeStamp;

		f_HESH->m_RotateX = g_RADX;
		f_HESH->m_RotateY = g_RADY;
		f_HESH->m_RotateZ = g_RADZ;

		f_HESH->m_ValueBank = g_WALLETBANK - g_StoreWALLETBANK;
		g_StoreWALLETBANK = g_WALLETBANK;

		for(int f_IntAd = 0; f_IntAd < g_vec_Cube.size(); f_IntAd++)
			{
			f_HESH->m_adIndex.push_back(g_vec_Cube[f_IntAd]);
			}

		for(int f_IntKey = 0; f_IntKey < g_BicycleContainer[0].vec_Key.size(); f_IntKey++)
			{
			CubeKEY* f_Key = g_BicycleContainer[0].vec_Key[f_IntKey];
			CubeBicycle* f_Bicycle = new CubeBicycle();

			f_Bicycle->m_indexBuffer = f_Key->m_Link->m_indexBuffer;
			f_Bicycle->m_vertexBuffer = f_Key->m_Link->m_vertexBuffer;
			f_Bicycle->m_indexCount = f_Key->m_Link->m_indexCount;

			for(int f_IntVertex = 0; f_IntVertex < f_Key->m_Link->vec_Vertex.size(); f_IntVertex++)
				{
				BiVector f_Vector = f_Key->m_Link->vec_Vertex[f_IntVertex];

				f_Bicycle->vec_Vertex.push_back(f_Vector);
				}

			for(int f_IntColor = 0; f_IntColor < f_Key->m_Link->vec_Vertex.size(); f_IntColor++)
				{
				BiVector f_Color = f_Key->m_Link->vec_Color[f_IntColor];

				f_Bicycle->vec_Color.push_back(f_Color);
				}

			f_HESH->vec_Bicycle.push_back(f_Bicycle);
			}

		if(g_HESH.size() >= 1500)
			{
			for(int f_Count = 0; f_Count < 5; f_Count++)
				{
				int K = 0;
				while(K < g_HESH.size())
					{
					g_HESH[K] = g_HESH[K + 1];
					K++;
					}

				g_HESH.pop_back();
				}

			g_SelectedHeshID = g_HESH.size();
			g_ID = g_SelectedHeshID;

			g_HeshFull = true;
			}
		else
			{
			g_HeshFull = false;
			}

		g_HESH.push_back(f_HESH);
		return f_HESH;
		}

	CubeHESH::CubeHESH(FILE* f_File)
		{
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
			CubeBicycle* f_CB = new CubeBicycle(f_File);
			vec_Bicycle.push_back(f_CB);
			}

		m_ValueBank = acBufreadValueDouble(f_File);
		}

	CubeHESH::CubeHESH(std::string f_Buffer)
		{
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
			CubeBicycle* f_CB = new CubeBicycle(f_Buffer);
			vec_Bicycle.push_back(f_CB);
			}

		m_ValueBank = acBufreadValueDouble((char *)f_Buffer.c_str());
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

		acBufwriteValueInteger(f_String, vec_Indices.size());

		for(int f_I = 0; f_I < vec_Indices.size(); f_I++)
			{
			acBufwriteValueInteger(f_String, vec_Indices[f_I].m_A);

			acBufwriteValueInteger(f_String, vec_Indices[f_I].m_B);

			acBufwriteValueInteger(f_String, vec_Indices[f_I].m_C);
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

		int f_IndexSize = acBufreadValueInteger(f_File);

		for(int f_I = 0; f_I < f_IndexSize; f_I++)
			{
			Cube::Index f_Index;

			f_Index.m_A = acBufreadValueInteger(f_File);

			f_Index.m_B = acBufreadValueInteger(f_File);

			f_Index.m_C = acBufreadValueInteger(f_File);

			vec_Indices.push_back(f_Index);
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

		int f_IndexSize = acBufreadValueInteger((char *)f_Buffer.c_str());

		for(int f_I = 0; f_I < f_IndexSize; f_I++)
			{
			Cube::Index f_Index;

			f_Index.m_A = acBufreadValueInteger((char *)f_Buffer.c_str());

			f_Index.m_B = acBufreadValueInteger((char *)f_Buffer.c_str());

			f_Index.m_C = acBufreadValueInteger((char *)f_Buffer.c_str());

			vec_Indices.push_back(f_Index);
			}
		}

	void agSave(CubeHESH* f_HESH)
		{
		g_Wallet->UpdateHesh();

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
		Windows::Storage::StorageFolder^ localFolder2 = Windows::Storage::ApplicationData::Current->LocalFolder;

		std::string f_LocalPathString2 = to_string(localFolder2->Path);
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
			}
		}

	bool agOpen(void)
		{
		Windows::Storage::StorageFolder^ localFolder2 = Windows::Storage::ApplicationData::Current->LocalFolder;

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
				CubeHESH* f_HESH = new CubeHESH(f_Char);

				f_HESH->m_ID = f_Count;

				g_HESH.push_back(f_HESH);
				}

			fclose(f_Char);
			}

		g_SelectedHeshID = g_HESH.size() - 1;
		g_ID = g_SelectedHeshID;
#endif

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

	CubeHESH* agGenerateHesh(void)
		{
		CubeHESH* f_Hesh = new CubeHESH();

		for(int f_Int = 0; f_Int < CUBE_HESH_SIZE; f_Int++)
			{
			CubeBicycle* f_Bicycle = new CubeBicycle();

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
			vec_Vertex[0] *= f_Amount;
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

	bool BiMesh::acInteract(DirectX::XMVECTOR rayOrigin, DirectX::XMVECTOR rayDirection)
		{
		// Now perform the ray-sphere intersection test.
		bool intersect = m_Sphere->RaySphereIntersect(rayOrigin, rayDirection);

		return intersect;
		}

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

	void BiMeshContainer::acInteract(float f_MouseX, float f_MouseY)
		{
		float pointX, pointY;
		DirectX::XMMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
		DirectX::XMVECTOR direction, origin, rayOrigin, rayDirection;
		DirectX::XMVECTOR f_Det;
		bool intersect, result;

		f_Det.m128_f32[0] = -1.0f;
		f_Det.m128_f32[1] = -1.0f;
		f_Det.m128_f32[2] = -1.0f;

		// Move the mouse cursor coordinates into the -1 to +1 range.
		pointX = ((2.0f * (1.0f - ((float)f_MouseX / (float)1366.0f))) - 1.0f) * -1.0f;
		pointY = (((2.0f * (float)f_MouseY) / (float)768.0f) - 1.0f) * -1.0f;

#if 1
		// Adjust the points using the projection matrix to account for the aspect ratio of the viewport.
		projectionMatrix = g_projMatrix;
		pointX = pointX / projectionMatrix.r[0].m128_f32[0];
		pointY = pointY / projectionMatrix.r[1].m128_f32[1];

		// Get the inverse of the view matrix.
		viewMatrix = g_viewMatrix;
		
		inverseViewMatrix = DirectX::XMMatrixInverse(&f_Det, viewMatrix);

		// Calculate the direction of the picking ray in view space.
		direction.m128_f32[0] = (pointX * inverseViewMatrix.r[0].m128_f32[0]) + (pointY * inverseViewMatrix.r[1].m128_f32[0]) + inverseViewMatrix.r[2].m128_f32[0];
		direction.m128_f32[1] = (pointX * inverseViewMatrix.r[0].m128_f32[1]) + (pointY * inverseViewMatrix.r[1].m128_f32[1]) + inverseViewMatrix.r[2].m128_f32[1];
		direction.m128_f32[2] = (pointX * inverseViewMatrix.r[0].m128_f32[2]) + (pointY * inverseViewMatrix.r[1].m128_f32[2]) + inverseViewMatrix.r[2].m128_f32[2];
#endif

		// Get the origin of the picking ray which is the position of the camera.
		origin = g_Origin;

		// Get the world matrix and translate to the location of the sphere.
#if 0
		m_D3D->GetWorldMatrix(worldMatrix);
		D3DXMatrixTranslation(&translateMatrix, -5.0f, 1.0f, 5.0f);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

		// Now get the inverse of the translated world matrix.
		D3DXMatrixInverse(&inverseWorldMatrix, NULL, &worldMatrix);

		// Now transform the ray origin and the ray direction from view space to world space.
		D3DXVec3TransformCoord(&rayOrigin, &origin, &inverseWorldMatrix);
		D3DXVec3TransformNormal(&rayDirection, &direction, &inverseWorldMatrix);

		DirectX::XMVector3TransformCoord
#endif

		rayOrigin = origin;
		rayDirection = direction;

			// Normalize the ray direction.
		direction = DirectX::XMVector3Normalize(direction);
		rayDirection = DirectX::XMVector3Normalize(rayDirection);

		int f_One = -5.0f;
		float f_Length = 500000.0f;
		bool f_lngResult = false;
		for(int f_Sphere = 0; f_Sphere < m_vec_Sphere.size(); f_Sphere++)
			{
			bool f_Result = false;

			// Get the world matrix and translate to the location of the sphere.
			DirectX::XMMATRIX f_TransWorld = DirectX::XMMatrixTranslation(m_vec_Sphere[f_Sphere]->m_Pos.m_X, m_vec_Sphere[f_Sphere]->m_Pos.m_Y, m_vec_Sphere[f_Sphere]->m_Pos.m_Z);
			DirectX::XMMATRIX f_TransWorldINV = DirectX::XMMatrixInverse(&f_Det, f_TransWorld);

			// Now transform the ray origin and the ray direction from view space to world space.
			rayOrigin = DirectX::XMVector3TransformCoord(origin, f_TransWorldINV);
			rayDirection = DirectX::XMVector3TransformNormal(direction, f_TransWorldINV);

			f_Result = m_vec_Sphere[f_Sphere]->RaySphereIntersect(rayOrigin, rayDirection);

			if(f_Result)
				{
				if(m_vec_Sphere[f_Sphere]->m_Dist <= f_Length)
					{
					f_Length = m_vec_Sphere[f_Sphere]->m_Dist;
					f_One = f_Sphere;
					}

				f_lngResult = f_Result;
				}
			}

		if(f_lngResult)
			{
			m_vec_Sphere[f_One]->m_Mesh->acMark(GEN_INT_TYPE_PRESS);
			}
		}

	bool BiSphere::RaySphereIntersect(DirectX::XMVECTOR rayOrigin, DirectX::XMVECTOR rayDirection)
		{
		float a, b, c, discriminant;

		// Calculate the a, b, and c coefficients.
		a = (rayDirection.m128_f32[0] * rayDirection.m128_f32[0]) + (rayDirection.m128_f32[1] * rayDirection.m128_f32[1]) + (rayDirection.m128_f32[2] * rayDirection.m128_f32[2]);
		b = ((rayDirection.m128_f32[0] * rayOrigin.m128_f32[0]) + (rayDirection.m128_f32[1] * rayOrigin.m128_f32[1]) + (rayDirection.m128_f32[2] * rayOrigin.m128_f32[2])) * 2.0f;
		c = ((rayOrigin.m128_f32[0] * rayOrigin.m128_f32[0]) + (rayOrigin.m128_f32[1] * rayOrigin.m128_f32[1]) + (rayOrigin.m128_f32[2] * rayOrigin.m128_f32[2])) - (m_Dist * m_Dist);

		// Find the discriminant.
		discriminant = (b * b) - (4 * a * c);

		// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
		if (discriminant < 0.0f)
			{
			return false;
			}

		return true;
		}

}; //END Cube

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