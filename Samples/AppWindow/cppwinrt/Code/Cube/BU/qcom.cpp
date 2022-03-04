/*

VoxelGrid.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "qcom.h"

#include "CLS/Target.h"

#ifdef QCOM_MIX
#include "MathHelper.h"

#pragma message ("-~~THE QUANTUM ANGEL CODEX~~-")

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"

#include "q-keydefinitions.h"

//#include "Render/FrustumG.h"

using namespace GVARS;
using namespace CubeBie;
using namespace std;

namespace CubeBie
{
#endif

using namespace Cube;
using namespace std;

namespace Cube
{

QcomManager* g_QcomManager;

std::shared_ptr<Qcom> g_PreCom = nullptr;
bool g_PreComBool = false;
bool g_PreComLock = false;
int g_PreComBoughtIN = 0;
bool g_PreComInclude = false;

float g_BossLVLMin = 0.0000;

int g_QcomMax = 0;

void ag_LoadQcom(void)
{
	int f_Int = 1;
	if(!g_SafeL[2])
		{
		g_SafeL[2] = new icSafeL(2);
		g_SafeL[2]->Initialize();

		f_Int = g_SafeL[2]->Connect("bitcoin-office.com", "root", "IntegerProperty18", "globalscapedb", 3306);
		printf("Connected to ecoin server...\n");
		}

	if(f_Int == 1)
		{
		char* f_comquery = new char[512];
		sprintf(f_comquery, "SELECT max(id) FROM com");
		g_SafeL[2]->acSelectCommand(f_comquery, false, false);

		if(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size())
			{
			g_QcomMax = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][0].c_str());
			}
		}
}

Qcom::Qcom()
{
	m_Save = true;

	Initialize();
}

Qcom::~Qcom()
{
	m_vec_Function.clear();

	m_vec_Qcom.clear();
	m_vec_Execute_Chain.clear();

	m_vec_Vertex.clear();
	m_vec_Normal.clear();
	m_vec_Color.clear();
	m_vec_Tex.clear();
	m_vec_Index.clear();

#if 1
	Unload();
#endif
}

// Initialize
void Qcom::Initialize()
{
	m_rebuild = true;
}

void Qcom::Unload(void)
{
	//if(mVertexPositionBuffer)
	//	{
	//	glDeleteBuffers(1, &mVertexPositionBuffer);
	//	}
	//if(mVertexNormalBuffer)
	//	{
	//	glDeleteBuffers(1, &mVertexNormalBuffer);
	//	}
	//if(mVertexColorBuffer)
	//	{
	//	glDeleteBuffers(1, &mVertexColorBuffer);
	//	}
	//if(mVertexTexCoordBuffer)
	//	{
	//	glDeleteBuffers(1, &mVertexTexCoordBuffer);
	//	}
}

void Qcom::GenerateBuffers(void)
{
	/*const unsigned int f_VertNom = m_vec_Vertex.size() * 3;
	const unsigned int f_ColorNom = m_vec_Color.size() * 4;
	const unsigned int f_UVNom = m_vec_Tex.size() * 2;
	const unsigned int f_IndexNom = m_vec_Index.size() * 3;

	GLfloat* f_Position = new GLfloat[f_VertNom];
	GLfloat* f_Normal = new GLfloat[f_VertNom];
	GLfloat* f_Color = new GLfloat[f_ColorNom];
	GLfloat* f_Tex = new GLfloat[f_UVNom];
	short* f_Index = new short[f_IndexNom];

	for (unsigned int f_VertexCount = 0; f_VertexCount < m_vec_Vertex.size(); f_VertexCount++)
		{
		f_Position[(f_VertexCount * 3)] = m_vec_Vertex[f_VertexCount]->m_X;
		f_Position[(f_VertexCount * 3) + 1] = m_vec_Vertex[f_VertexCount]->m_Y;
		f_Position[(f_VertexCount * 3) + 2] = m_vec_Vertex[f_VertexCount]->m_Z;
		}

	for (unsigned int f_NormalCount = 0; f_NormalCount < m_vec_Normal.size(); f_NormalCount++)
		{
		f_Normal[(f_NormalCount * 3)] = m_vec_Normal[f_NormalCount]->m_X;
		f_Normal[(f_NormalCount * 3) + 1] = m_vec_Normal[f_NormalCount]->m_Y;
		f_Normal[(f_NormalCount * 3) + 2] = m_vec_Normal[f_NormalCount]->m_Z;
		}

	for (unsigned int f_ColorCount = 0; f_ColorCount < m_vec_Color.size(); f_ColorCount++)
		{
		f_Color[(f_ColorCount * 4)] = m_vec_Color[f_ColorCount]->m_R;
		f_Color[(f_ColorCount * 4) + 1] = m_vec_Color[f_ColorCount]->m_G;
		f_Color[(f_ColorCount * 4) + 2] = m_vec_Color[f_ColorCount]->m_B;
		f_Color[(f_ColorCount * 4) + 3] = m_vec_Color[f_ColorCount]->m_A;
		}

	for (unsigned int f_TexCount = 0; f_TexCount < m_vec_Tex.size(); f_TexCount++)
		{
		f_Tex[(f_TexCount * 2)] = m_vec_Tex[f_TexCount]->m_U;
		f_Tex[(f_TexCount * 2) + 1] = m_vec_Tex[f_TexCount]->m_V;
		}

	for (unsigned int f_IndexCount = 0; f_IndexCount < m_vec_Index.size(); f_IndexCount++)
		{
		f_Index[(f_IndexCount * 3)] = m_vec_Index[f_IndexCount]->m_A;
		f_Index[(f_IndexCount * 3) + 1] = m_vec_Index[f_IndexCount]->m_B;
		f_Index[(f_IndexCount * 3) + 2] = m_vec_Index[f_IndexCount]->m_C;
		}

	glGenBuffers(1, &mVertexPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Position, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexNormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Normal, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_ColorNom, f_Color, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexTexCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexTexCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_UVNom, f_Tex, GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * f_IndexNom, f_Index, GL_STATIC_DRAW);*/
}

Qcom::Qcom(int f_ID, bool f_loadall)
{
	if(f_loadall)
		{
		m_ID = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][0].c_str());

		m_owner = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][1];
		m_name = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][2];
		m_overload = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][3];
		m_description = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][4];
		m_vision = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][5];
		m_NameGroup = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][6];
		m_VoteScore = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][7].c_str());
		m_seedinfo = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][8];
		m_parentcomid = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][9].c_str());
		m_parentx = atof(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][10].c_str());
		m_parenty = atof(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][11].c_str());
		m_birthcomid = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][12].c_str());
		m_QamLevel = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][13].c_str());
		m_QamID = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][14].c_str());
		m_typed = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][15].c_str());
		}
	else
		{
#if 0
		//g_VoxMuti.ac_Fire();

		int f_Int = 1;
		if(!g_SafeL[2])
			{
			g_SafeL[2] = new icSafeL(2);
			g_SafeL[2]->Initialize();

			f_Int = g_SafeL[2]->Connect("bitcoin-office.com", "root", "IntegerProperty18", "globalscapedb", 3306);
			printf("Connected to ecoin server...\n");
			}

		if(f_Int)
			{
#endif
			//Build the query
			char* f_comquery = new char[512];
			sprintf(f_comquery, "SELECT id, owner, name, overload, description, vision, namegroup, score, seedinfo, parentcomid, parentx, parenty, birthcomid, qamlevel, qamid, typed FROM com WHERE id = %i", f_ID);
			g_SafeL[2]->acSelectCommand(f_comquery, false, false);

			if(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size())
				{
				m_owner = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][1];
				m_name = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][2];
				m_overload = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][3];
				m_description = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][4];
				m_vision = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][5];
				m_NameGroup = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][6];
				m_VoteScore = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][7].c_str());
				m_seedinfo = g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][8];
				m_parentcomid = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][9].c_str());
				m_parentx = atof(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][10].c_str());
				m_parenty = atof(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][11].c_str());
				m_birthcomid = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][12].c_str());
				m_QamLevel = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][13].c_str());
				m_QamID = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][14].c_str());
				m_typed = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][15].c_str());
				}
#if 0
			}

		//g_VoxMuti.ac_Free();
#endif
		}

	m_Save = false;
}

QcomInput::QcomInput(int f_ID, bool f_loadall)
{
}

QcomControl::QcomControl(int f_ID, bool f_loadall)
{
}

QcomOutput::QcomOutput(int f_ID, bool f_loadall)
{
}

Qcom_genScript::Qcom_genScript(int f_ID, bool f_loadall)
{
	m_ID = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][0].c_str());
	m_owner = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][1].c_str());
	m_name = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][2].c_str());
	m_description = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][3].c_str());
	m_vision = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][4].c_str());
	m_seedinfo = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][5].c_str());
	m_NameGroup = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][6].c_str());
	m_ComID = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][7].c_str());
	m_QamLevel = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][8].c_str());
	m_QamID = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][9].c_str());
	m_typed = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_ID][10].c_str());
}

Qcom_eslfunction::Qcom_eslfunction(int f_ID, bool f_loadall)
{

}

QcomWire::QcomWire(int f_ID, bool f_loadall)
{
}

void Qcom::ac_Save(void)
{
	int f_Int = 1;
	if(!g_SafeL[2])
		{
		g_SafeL[2] = new icSafeL(2);
		g_SafeL[2]->Initialize();

		f_Int = g_SafeL[2]->Connect("bitcoin-office.com", "root", "IntegerProperty18", "globalscapedb", 3306);
		printf("Connected to ecoin server...\n");
		}

	if(m_ID == -1551)
		{
		if(f_Int)
			{
			char* f_qcomfield[17];
			char* f_qcomvalue[17];

			for(int f_Count = 0; f_Count < 17; f_Count++)
				{
				f_qcomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_qcomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			sprintf(f_qcomfield[0], "owner");
			sprintf(f_qcomfield[1], "name");
			sprintf(f_qcomfield[2], "overload");
			sprintf(f_qcomfield[3], "description");
			sprintf(f_qcomfield[4], "vision");
			sprintf(f_qcomfield[5], "namegroup");
			sprintf(f_qcomfield[6], "score");
			sprintf(f_qcomfield[7], "seedinfo");
			sprintf(f_qcomfield[8], "parentcomid");
			sprintf(f_qcomfield[9], "parentx");
			sprintf(f_qcomfield[10], "parenty");
			sprintf(f_qcomfield[11], "birthcomid");
			sprintf(f_qcomfield[12], "qamlevel");
			sprintf(f_qcomfield[13], "qamid");
			sprintf(f_qcomfield[14], "typed");
			sprintf(f_qcomfield[15], "cost");
			sprintf(f_qcomfield[16], "bosslvlmin");

			sprintf(f_qcomvalue[0], "%s", m_owner.c_str());
			sprintf(f_qcomvalue[1], "%s", m_name.c_str());
			sprintf(f_qcomvalue[2], "%s", m_overload.c_str());
			sprintf(f_qcomvalue[3], "%s", m_description.c_str());
			sprintf(f_qcomvalue[4], "%s", m_vision.c_str());
			sprintf(f_qcomvalue[5], "%s", m_NameGroup.c_str());
			sprintf(f_qcomvalue[6], "%i", m_VoteScore);
			sprintf(f_qcomvalue[7], "%s", m_seedinfo.c_str());
			sprintf(f_qcomvalue[8], "%i", m_parentcomid);
			sprintf(f_qcomvalue[9], "%f", m_parentx);
			sprintf(f_qcomvalue[10], "%f", m_parenty);
			sprintf(f_qcomvalue[11], "%i", m_birthcomid);
			sprintf(f_qcomvalue[12], "%i", m_QamLevel);
			sprintf(f_qcomvalue[13], "%i", m_QamID);
			sprintf(f_qcomvalue[14], "%i", m_typed);
			sprintf(f_qcomvalue[15], "%f", m_Cost);
			sprintf(f_qcomvalue[16], "%f", m_BossLVLMin);

			int f_qcomUniqueID = g_SafeL[2]->Insert("com", (const char **)f_qcomfield, (const char **)f_qcomvalue, 17, false, false);

			m_ID = f_qcomUniqueID;

			m_genScript->m_ComID = m_ID;

			if(m_genScript->m_ID == -1551)
				{
				char* f_qcomINLfield[10];
				char* f_qcomINLvalue[10];

				for(int f_Count = 0; f_Count < 10; f_Count++)
					{
					f_qcomINLfield[f_Count] = (char*)malloc(sizeof(char) * 512);
					f_qcomINLvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
					}

				sprintf(f_qcomINLfield[0], "owner");
				sprintf(f_qcomINLfield[1], "name");
				sprintf(f_qcomINLfield[2], "description");
				sprintf(f_qcomINLfield[3], "vision");
				sprintf(f_qcomINLfield[4], "namegroup");
				sprintf(f_qcomINLfield[5], "seedinfo");
				sprintf(f_qcomINLfield[6], "comid");
				sprintf(f_qcomINLfield[7], "qamlevel");
				sprintf(f_qcomINLfield[8], "qamid");
				sprintf(f_qcomINLfield[9], "typed");

				sprintf(f_qcomINLvalue[0], "%s", m_genScript->m_owner.c_str());
				sprintf(f_qcomINLvalue[1], "%s", m_genScript->m_name.c_str());
				sprintf(f_qcomINLvalue[2], "%s", m_genScript->m_description.c_str());
				sprintf(f_qcomINLvalue[3], "%s", m_genScript->m_vision.c_str());
				sprintf(f_qcomINLvalue[4], "%s", m_genScript->m_NameGroup.c_str());
				sprintf(f_qcomINLvalue[5], "%s", m_genScript->m_seedinfo.c_str());
				sprintf(f_qcomINLvalue[6], "%i", m_genScript->m_ComID);
				sprintf(f_qcomINLvalue[7], "%i", m_genScript->m_QamLevel);
				sprintf(f_qcomINLvalue[8], "%i", m_genScript->m_QamID);
				sprintf(f_qcomINLvalue[9], "%i", m_genScript->m_typed);

				int f_qcomINLUniqueID = g_SafeL[2]->Insert("inlscript", (const char **)f_qcomINLfield, (const char **)f_qcomINLvalue, 10, false, false);

				m_genScript->m_ID = f_qcomINLUniqueID;

				for(int f_XY = 0; f_XY < m_genScript->m_vec_InitLineOrdered.size(); f_XY++)
					{
					char* f_qcomINLlinefield[8];
					char* f_qcomINLlinevalue[8];

					for(int f_Count = 0; f_Count < 8; f_Count++)
						{
						f_qcomINLlinefield[f_Count] = (char*)malloc(sizeof(char) * 2048);
						f_qcomINLlinevalue[f_Count] = (char*)malloc(sizeof(char) * 2048);
						}

					sprintf(f_qcomINLlinefield[0], "owner");
					sprintf(f_qcomINLlinefield[1], "namegroup");
					sprintf(f_qcomINLlinefield[2], "codestring");
					sprintf(f_qcomINLlinefield[3], "lineno");	
					sprintf(f_qcomINLlinefield[4], "inlscriptid");
					sprintf(f_qcomINLlinefield[5], "qamlevel");
					sprintf(f_qcomINLlinefield[6], "qamid");
					sprintf(f_qcomINLlinefield[7], "typed");

					sprintf(f_qcomINLlinevalue[0], "%s", m_genScript->m_owner.c_str());
					sprintf(f_qcomINLlinevalue[1], "%s", m_genScript->m_NameGroup.c_str());
					sprintf(f_qcomINLlinevalue[2], "%s", m_genScript->m_vec_InitLineOrdered[f_XY].c_str());
					sprintf(f_qcomINLlinevalue[3], "%i", f_XY);
					sprintf(f_qcomINLlinevalue[4], "%i", m_genScript->m_ID);
					sprintf(f_qcomINLlinevalue[5], "%i", m_genScript->m_QamLevel);
					sprintf(f_qcomINLlinevalue[6], "%i", m_genScript->m_QamID);
					sprintf(f_qcomINLlinevalue[7], "%i", m_genScript->m_typed);

					int f_qcomINLlineUniqueID = g_SafeL[2]->Insert("inlcodeline", (const char **)f_qcomINLlinefield, (const char **)f_qcomINLlinevalue, 8, false, false);
					m_genScript->m_vec_InitLineOrderedID.push_back(f_qcomINLlineUniqueID);
					}
				}
			}

		//g_VoxMuti.ac_Free();
		}
	else
		{
		if(m_Save)
			{
			char* f_qcomwhere[1];
			char* f_qcomfield[17];
			char* f_qcomvalue[17];

			for(int f_Count = 0; f_Count < 17; f_Count++)
				{
				f_qcomfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_qcomvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			f_qcomwhere[0] = (char*)malloc(sizeof(char) * 512);

			sprintf(f_qcomfield[0], "owner");
			sprintf(f_qcomfield[1], "name");
			sprintf(f_qcomfield[2], "overload");
			sprintf(f_qcomfield[3], "description");
			sprintf(f_qcomfield[4], "vision");
			sprintf(f_qcomfield[5], "namegroup");
			sprintf(f_qcomfield[6], "score");
			sprintf(f_qcomfield[7], "seedinfo");
			sprintf(f_qcomfield[8], "parentcomid");
			sprintf(f_qcomfield[9], "parentx");
			sprintf(f_qcomfield[10], "parenty");
			sprintf(f_qcomfield[11], "birthcomid");
			sprintf(f_qcomfield[12], "qamlevel");
			sprintf(f_qcomfield[13], "qamid");
			sprintf(f_qcomfield[14], "typed");
			sprintf(f_qcomfield[15], "cost");
			sprintf(f_qcomfield[16], "bosslvlmin");

			sprintf(f_qcomvalue[0], "%s", m_owner.c_str());
			sprintf(f_qcomvalue[1], "%s", m_name.c_str());
			sprintf(f_qcomvalue[2], "%s", m_overload.c_str());
			sprintf(f_qcomvalue[3], "%s", m_description.c_str());
			sprintf(f_qcomvalue[4], "%s", m_vision.c_str());
			sprintf(f_qcomvalue[5], "%s", m_NameGroup.c_str());
			sprintf(f_qcomvalue[6], "%i", m_VoteScore);
			sprintf(f_qcomvalue[7], "%s", m_seedinfo.c_str());
			sprintf(f_qcomvalue[8], "%i", m_parentcomid);
			sprintf(f_qcomvalue[9], "%f", m_parentx);
			sprintf(f_qcomvalue[10], "%f", m_parenty);
			sprintf(f_qcomvalue[11], "%i", m_birthcomid);
			sprintf(f_qcomvalue[12], "%i", m_QamLevel);
			sprintf(f_qcomvalue[13], "%i", m_QamID);
			sprintf(f_qcomvalue[14], "%i", m_typed);
			sprintf(f_qcomvalue[15], "%f", m_Cost);
			sprintf(f_qcomvalue[16], "%f", m_BossLVLMin);

			sprintf(f_qcomwhere[0], "id = %i", m_ID);

			//g_VoxMuti.ac_Fire();

			g_SafeL[2]->Update("com", (const char **)f_qcomfield, (const char **)f_qcomvalue, 17, f_qcomwhere[0], false, false);

			//g_VoxMuti.ac_Free();

			char* f_qcomINLwhere[1];
			char* f_qcomINLfield[10];
			char* f_qcomINLvalue[10];

			for(int f_Count = 0; f_Count < 10; f_Count++)
				{
				f_qcomINLfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_qcomINLvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			f_qcomINLwhere[0] = (char*)malloc(sizeof(char) * 512);

			sprintf(f_qcomINLfield[0], "owner");
			sprintf(f_qcomINLfield[1], "name");
			sprintf(f_qcomINLfield[2], "description");
			sprintf(f_qcomINLfield[3], "vision");
			sprintf(f_qcomINLfield[4], "namegroup");
			sprintf(f_qcomINLfield[5], "seedinfo");
			sprintf(f_qcomINLfield[6], "comid");
			sprintf(f_qcomINLfield[7], "qamlevel");
			sprintf(f_qcomINLfield[8], "qamid");
			sprintf(f_qcomINLfield[9], "typed");

			sprintf(f_qcomINLvalue[0], "%s", m_genScript->m_owner.c_str());
			sprintf(f_qcomINLvalue[1], "%s", m_genScript->m_name.c_str());
			sprintf(f_qcomINLvalue[2], "%s", m_genScript->m_description.c_str());
			sprintf(f_qcomINLvalue[3], "%s", m_genScript->m_vision.c_str());
			sprintf(f_qcomINLvalue[4], "%s", m_genScript->m_NameGroup.c_str());
			sprintf(f_qcomINLvalue[5], "%s", m_genScript->m_seedinfo.c_str());
			sprintf(f_qcomINLvalue[6], "%i", m_genScript->m_ComID);
			sprintf(f_qcomINLvalue[7], "%i", m_genScript->m_QamLevel);
			sprintf(f_qcomINLvalue[8], "%i", m_genScript->m_QamID);
			sprintf(f_qcomINLvalue[9], "%i", m_genScript->m_typed);

			sprintf(f_qcomINLwhere[0], "id = %i", m_genScript->m_ID);

			g_SafeL[2]->Update("inlscript", (const char **)f_qcomINLfield, (const char **)f_qcomINLvalue, 10, f_qcomINLwhere[0], false, false);

			for(int f_XY = 0; f_XY < m_genScript->m_vec_InitLineOrdered.size(); f_XY++)
				{
				if(m_genScript->m_vec_InitLineOrderedID[f_XY] == -5)
					{
					char* f_qcomINLlinefield[8];
					char* f_qcomINLlinevalue[8];

					for(int f_Count = 0; f_Count < 8; f_Count++)
						{
						f_qcomINLlinefield[f_Count] = (char*)malloc(sizeof(char) * 2048);
						f_qcomINLlinevalue[f_Count] = (char*)malloc(sizeof(char) * 2048);
						}

					sprintf(f_qcomINLlinefield[0], "owner");
					sprintf(f_qcomINLlinefield[1], "namegroup");
					sprintf(f_qcomINLlinefield[2], "codestring");
					sprintf(f_qcomINLlinefield[3], "lineno");	
					sprintf(f_qcomINLlinefield[4], "inlscriptid");
					sprintf(f_qcomINLlinefield[5], "qamlevel");
					sprintf(f_qcomINLlinefield[6], "qamid");
					sprintf(f_qcomINLlinefield[7], "typed");

					sprintf(f_qcomINLlinevalue[0], "%s", m_genScript->m_owner.c_str());
					sprintf(f_qcomINLlinevalue[1], "%s", m_genScript->m_NameGroup.c_str());
					sprintf(f_qcomINLlinevalue[2], "%s", m_genScript->m_vec_InitLineOrdered[f_XY].c_str());
					sprintf(f_qcomINLlinevalue[3], "%i", f_XY);
					sprintf(f_qcomINLlinevalue[4], "%i", m_genScript->m_ID);
					sprintf(f_qcomINLlinevalue[5], "%i", m_genScript->m_QamLevel);
					sprintf(f_qcomINLlinevalue[6], "%i", m_genScript->m_QamID);
					sprintf(f_qcomINLlinevalue[7], "%i", m_genScript->m_typed);

					int f_qcomINLlineUniqueID = g_SafeL[2]->Insert("inlcodeline", (const char **)f_qcomINLlinefield, (const char **)f_qcomINLlinevalue, 8, false, false);
					m_genScript->m_vec_InitLineOrderedID[f_XY] = f_qcomINLlineUniqueID;
					}
				else
					{
					char* f_qcomINLlinefield[8];
					char* f_qcomINLlinevalue[8];
					char* f_qcomINLlinewhere[1];

					for(int f_Count = 0; f_Count < 8; f_Count++)
						{
						f_qcomINLlinefield[f_Count] = (char*)malloc(sizeof(char) * 2048);
						f_qcomINLlinevalue[f_Count] = (char*)malloc(sizeof(char) * 2048);
						}

					sprintf(f_qcomINLlinefield[0], "owner");
					sprintf(f_qcomINLlinefield[1], "namegroup");
					sprintf(f_qcomINLlinefield[2], "codestring");
					sprintf(f_qcomINLlinefield[3], "lineno");	
					sprintf(f_qcomINLlinefield[4], "inlscriptid");
					sprintf(f_qcomINLlinefield[5], "qamlevel");
					sprintf(f_qcomINLlinefield[6], "qamid");
					sprintf(f_qcomINLlinefield[7], "typed");

					sprintf(f_qcomINLlinevalue[0], "%s", m_genScript->m_owner.c_str());
					sprintf(f_qcomINLlinevalue[1], "%s", m_genScript->m_NameGroup.c_str());
					sprintf(f_qcomINLlinevalue[2], "%s", m_genScript->m_vec_InitLineOrdered[f_XY].c_str());
					sprintf(f_qcomINLlinevalue[3], "%i", f_XY);
					sprintf(f_qcomINLlinevalue[4], "%i", m_genScript->m_ID);
					sprintf(f_qcomINLlinevalue[5], "%i", m_genScript->m_QamLevel);
					sprintf(f_qcomINLlinevalue[6], "%i", m_genScript->m_QamID);
					sprintf(f_qcomINLlinevalue[7], "%i", m_genScript->m_typed);

					sprintf(f_qcomINLlinewhere[0], "id = %i", m_genScript->m_vec_InitLineOrderedID[f_XY]);

					g_SafeL[2]->Update("inlcodeline", (const char **)f_qcomINLlinefield, (const char **)f_qcomINLlinevalue, 8, f_qcomINLlinewhere[0], false, false);
					}
				}

			m_Save = false;
			}
		}
}

void QcomManager::ac_LoadAll(int f_QamID, int f_QamLevel)
{
	//Build the query
	char* f_comquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_comquery, "SELECT id, owner, name, overload, description, vision, namegroup, score, seedinfo, parentcomid, parentx, parenty, birthcomid, qamlevel, qamid, typed FROM com WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_comquery, "SELECT id, owner, name, overload, description, vision, namegroup, score, seedinfo, parentcomid, parentx, parenty, birthcomid, qamlevel, qamid, typed FROM com WHERE qamid = %i", f_QamID);
		}

	g_SafeL[2]->acSelectCommand(f_comquery, false, false);

	for(int f_count = 0; f_count < g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size(); f_count++)
		{
		std::shared_ptr<Qcom> f_com = new Qcom(f_count, true);

		m_vec_Qcom.push_back(f_com);
		}

	//load all cominput
	//Build the query
	char* f_inputquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_inputquery, "SELECT id, owner, name, overload, description, vision, inputinitid, comid, icoid, qamlevel, qamid, typed FROM cominput WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_inputquery, "SELECT id, owner, name, overload, description, vision, inputinitid, comid, icoid, qamlevel, qamid, typed FROM cominput WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_inputquery, false, false);

	for(int f_count = 0; f_count < g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size(); f_count++)
		{
		QcomInput* f_comInput = new QcomInput(f_count, true);

		m_vec_Input.push_back(f_comInput);
		}

	//load all comoutput
	//Build the query
	char* f_outputquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_outputquery, "SELECT id, owner, name, overload, description, vision, outputinitid, comid, icoid, qamlevel, qamid, typed FROM comoutput WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_outputquery, "SELECT id, owner, name, overload, description, vision, outputinitid, comid, icoid, qamlevel, qamid, typed FROM comoutput WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_outputquery, false, false);

	for(int f_count = 0; f_count < g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size(); f_count++)
		{
		QcomOutput* f_comoutput = new QcomOutput(f_count, true);

		m_vec_Output.push_back(f_comoutput);
		}

	//load all Generation Scripts
	//Build the query
	char* f_initquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_initquery, "SELECT id, owner, name, overload, description, vision, targetstr, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM inlscript WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_initquery, "SELECT id, owner, name, overload, description, vision, targetstr, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM inlscript WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_initquery, false, false);

	for(int f_count = 0; f_count < g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size(); f_count++)
		{
		std::shared_ptr<Qcom_genScript> f_InitScript = std::make_shared<Qcom_genScript>(f_count, true);

		m_vec_GenScript.push_back(f_InitScript);
		}

	//load all com esl Functions
	//Build the query
	char* f_functionquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_functionquery, "SELECT id, owner, name, overload, description, vision, targetstr, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM eslfunction WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_functionquery, "SELECT id, owner, name, overload, description, vision, targetstr, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM eslfunction WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_functionquery, false, false);

	for(int f_count = 0; f_count < g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size(); f_count++)
		{
		std::shared_ptr<Qcom_eslfunction> f_Function = new Qcom_eslfunction(f_count, true);

		m_vec_ESLFunction.push_back(f_Function);
		}

	//load all comwire
	//Build the query
	char* f_comwirequery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_comwirequery, "SELECT id, owner, namegroup, outputid, inputid, typed, parentcomid, qamlevel, qamid FROM comwire WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_comwirequery, "SELECT id, owner, namegroup, outputid, inputid, typed, parentcomid, qamlevel, qamid FROM comwire WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_comwirequery, false, false);

	for(int f_count = 0; f_count < g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size(); f_count++)
		{
		QcomWire* f_comwire = new QcomWire(f_count, true);

		m_vec_ComWire.push_back(f_comwire);
		}

	ac_PlushScripts(f_QamID, f_QamLevel);

	ac_Wire(f_QamID, f_QamLevel);
}

void QcomManager::ac_PlushScripts(int f_QamID, bool f_LoadAll, int f_QamLevel)
{
	//genScripts
	//Build the query
	char* f_initquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_initquery, "SELECT id, owner, namegroup, codestring, lineno, inlscriptid, typed, qamlevel, qamid FROM inlcodeline WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_initquery, "SELECT id, owner, namegroup, codestring, lineno, inlscriptid, typed, qamlevel, qamid FROM inlcodeline WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_initquery, false, false);

	int f_IDXLock = -1;
	for (int f_countLine = 0; f_countLine < g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size(); f_countLine++)
		{
		int f_LineIndex = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][5].c_str());

		if(f_IDXLock < 0 || m_vec_GenScript[f_IDXLock]->m_ID != f_IDXLock)
			{
			bool f_Found = false;
			bool f_Scan = true;
			int f_rai = 0;
			int f_Index = 0;

			while(f_Scan)
				{
				if(m_vec_GenScript[f_rai]->m_ID == f_LineIndex)
					{
					f_Scan = false;
					f_Index = f_rai;
					}

				f_rai++;

				if(f_rai >= m_vec_GenScript.size())
					{
					f_Scan = false;
					f_Index = -1;
					}
				}

			if(f_Index >= 0)
				{
				m_vec_GenScript[f_Index]->m_vec_InitLine.push_back(std::string(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][3]));
				m_vec_GenScript[f_Index]->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][4].c_str()));
				m_vec_GenScript[f_Index]->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][0].c_str()));
				f_IDXLock = f_Index;
				}
			else
				{
				m_vec_defGenScript->m_vec_InitLine.push_back(std::string(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][3]));
				m_vec_defGenScript->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][4].c_str()));
				m_vec_defGenScript->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][0].c_str()));
				f_IDXLock = -1;
				}
			}
		else
			{
			if(f_IDXLock >= 0)
				{
				m_vec_GenScript[f_IDXLock]->m_vec_InitLine.push_back(std::string(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][3]));
				m_vec_GenScript[f_IDXLock]->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][4].c_str()));
				m_vec_GenScript[f_IDXLock]->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][0].c_str()));
				}
			else
				{
				m_vec_defGenScript->m_vec_InitLine.push_back(std::string(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][3]));
				m_vec_defGenScript->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][4].c_str()));
				m_vec_defGenScript->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][0].c_str()));
				}
			}
		}

	//genScripts
	//Build the query
	char* f_eslquery = new char[512];

	if(f_QamLevel >= 0)
		{
		sprintf(f_eslquery, "SELECT id, owner, namegroup, codestring, lineno, inlscriptid, typed, qamlevel, qamid FROM eslfunction WHERE qamid = %i AND qamlevel = %i", f_QamID, f_QamLevel);
		}
	else
		{
		sprintf(f_eslquery, "SELECT id, owner, namegroup, codestring, lineno, inlscriptid, typed, qamlevel, qamid FROM eslfunction WHERE qamid = %i", f_QamID);
		}
	
	g_SafeL[2]->acSelectCommand(f_eslquery, false, false);

	f_IDXLock = -1;
	for (int f_countLine = 0; f_countLine < g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size(); f_countLine++)
		{
		int f_LineIndex = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][5].c_str());

		if(f_IDXLock < 0 || m_vec_GenScript[f_IDXLock]->m_ID != f_IDXLock)
			{
			bool f_Scan = true;
			int f_rai = 0;
			int f_Index = 0;

			while(f_Scan)
				{
				if(m_vec_GenScript[f_rai]->m_ID == f_LineIndex)
					{
					f_Scan = false;
					f_Index = f_rai;
					}

				f_rai++;

				if(f_rai >= m_vec_GenScript.size())
					{
					f_Scan = false;
					f_Index = -1;
					}
				}

			if(f_Index >= 0)
				{
				m_vec_ESLFunction[f_Index]->m_vec_InitLine.push_back(new std::string(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][3]));
				m_vec_ESLFunction[f_Index]->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][4].c_str()));
				m_vec_ESLFunction[f_Index]->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][0].c_str()));
				f_IDXLock = f_Index;
				}
			else
				{
				m_vec_defESLFunction->m_vec_InitLine.push_back(new std::string(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][3]));
				m_vec_defESLFunction->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][4].c_str()));
				m_vec_defESLFunction->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][0].c_str()));
				f_IDXLock = -1;
				}
			}
		else
			{
			if(f_IDXLock >= 0)
				{
				m_vec_ESLFunction[f_IDXLock]->m_vec_InitLine.push_back(new std::string(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][3]));
				m_vec_ESLFunction[f_IDXLock]->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][4].c_str()));
				m_vec_ESLFunction[f_IDXLock]->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][0].c_str()));
				}
			else
				{
				m_vec_defESLFunction->m_vec_InitLine.push_back(new std::string(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][3]));
				m_vec_defESLFunction->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][4].c_str()));
				m_vec_defESLFunction->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][0].c_str()));
				}
			}
		}

	for(int f_countScript = 0; f_countScript < m_vec_GenScript.size(); f_countScript++)
		{
		std::shared_ptr<Qcom_genScript> f_InitScript = m_vec_GenScript[f_countScript];
		
		for(int f_countLine = 0; f_countLine < f_InitScript->m_vec_InitLine.size(); f_countLine++)
			{
			for(int f_countOrder = 0; f_countOrder < f_InitScript->m_vec_InitLineOrder.size(); f_countLine++)
				{
				if (f_InitScript->m_vec_InitLineOrder[f_countOrder] == f_countLine)
					{
					f_InitScript->m_vec_InitLineOrdered.push_back(f_InitScript->m_vec_InitLine[f_countOrder]);
					f_InitScript->m_vec_InitLineOrderedID.push_back(f_InitScript->m_vec_InitLineOrderID[f_countOrder]);
					}
				}
			}

		if(f_InitScript->m_vec_InitLineOrdered.size() != f_InitScript->m_vec_InitLine.size())
			{
			throw;
			}
		}

	for(int f_countFunction = 0; f_countFunction < m_vec_ESLFunction.size(); f_countFunction++)
		{
		std::shared_ptr<Qcom_eslfunction> f_Function = m_vec_ESLFunction[f_countFunction];
		
		for(int f_countLine = 0; f_countLine < f_Function->m_vec_InitLine.size(); f_countLine++)
			{
			for(int f_countOrder = 0; f_countOrder < f_Function->m_vec_InitLineOrder.size(); f_countLine++)
				{
				if (f_Function->m_vec_InitLineOrder[f_countOrder] == f_countLine)
					{
					f_Function->m_vec_InitLineOrdered.push_back(f_Function->m_vec_InitLine[f_countOrder]);
					f_Function->m_vec_InitLineOrderedID.push_back(f_Function->m_vec_InitLineOrderID[f_countOrder]);
					}
				}
			}

		if(f_Function->m_vec_InitLineOrdered.size() != f_Function->m_vec_InitLine.size())
			{
			throw;
			}
		}

#pragma warning("FIXME:::Functionise")
}

void QcomManager::ac_Wire(int f_QamID, int f_QamLevel)
{
	for(int f_countCom = 0; f_countCom < m_vec_Qcom.size(); f_countCom++)
		{
		std::shared_ptr<Qcom> f_com = m_vec_Qcom[f_countCom];

		//if(f_com->
		}
}

void QcomManager::GenerateBuffers(void)
{
	/*float f_Z_offset = 250.0f;
	float f_Y_offset = 0.0f;

	// Then set up the cube geometry.
    GLfloat vertexPositions[] =
    {
        -360.0f, -200.0f + f_Y_offset, -4.0f + f_Z_offset,
        -360.0f, -200.0f + f_Y_offset,  4.0f + f_Z_offset,
        -360.0f,  200.0f + f_Y_offset, -4.0f + f_Z_offset,
        -360.0f,  200.0f + f_Y_offset,  4.0f + f_Z_offset,
         360.0f, -200.0f + f_Y_offset, -4.0f + f_Z_offset,
         360.0f, -200.0f + f_Y_offset,  4.0f + f_Z_offset,
         360.0f,  200.0f + f_Y_offset, -4.0f + f_Z_offset,
         360.0f,  200.0f + f_Y_offset,  4.0f + f_Z_offset,
    };

    glGenBuffers(1, &mVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    GLfloat vertexColors[] =
    {
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };

    glGenBuffers(1, &mVertexColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

    short indices[] =
    {
        0, 1, 2, // -x
        1, 3, 2,

        4, 6, 5, // +x
        5, 6, 7,

        0, 5, 1, // -y
        0, 4, 5,

        2, 7, 6, // +y
        2, 3, 7,
              
        0, 6, 4, // -z
        0, 2, 6,
              
        1, 7, 3, // +z
        1, 5, 7,
    };

    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glGenBuffers(1, &mVertexNormalBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_VertNom, f_Normal, GL_STATIC_DRAW);

	//glGenBuffers(1, &mVertexTexCoordBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, mVertexTexCoordBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_UVNom, f_Tex, GL_STATIC_DRAW);*/
}

void QcomManager::GenerateBuffersGrid(void)
{
	/*float f_Z_offset = 252.5f;
	float f_Y_offset = 0.0f;

	float f_NomFactor = 1.0f;

	float f_DivideX = 36.0f * f_NomFactor;
	float f_DivideY = 20.0f * f_NomFactor;

	float f_xcross = (720.0f / f_DivideX);
	float f_ycross = (400.0f / f_DivideY);

	// Then set up the cube geometry.
    GLfloat vertexPositions[] =
		{
		//Y
        -360.0f, -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f, 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + f_xcross, -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + f_xcross, 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 2.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 2.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 3.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 3.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 4.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 4.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		//6
		-360.0f + (f_xcross * 5.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 5.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 6.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 6.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 7.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 7.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 8.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 8.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 9.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 9.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		//11
		-360.0f + (f_xcross * 10.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 10.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 11.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 11.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 12.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 12.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 13.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 13.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 14.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 14.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		//16
		-360.0f + (f_xcross * 15.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 15.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 16.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 16.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 17.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 17.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 18.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 18.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 19.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 19.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		//21
		-360.0f + (f_xcross * 20.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 20.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 21.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 21.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 22.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 22.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 23.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 23.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 24.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 24.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		//26
		-360.0f + (f_xcross * 25.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 25.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 26.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 26.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 27.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 27.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 28.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 28.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 29.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 29.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		//31
		-360.0f + (f_xcross * 30.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 30.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 31.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 31.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 32.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 32.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 33.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 33.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		-360.0f + (f_xcross * 34.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 34.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

		//36
		-360.0f + (f_xcross * 35.0f), -200.0f + f_Y_offset, 4.0f + f_Z_offset,
		-360.0f + (f_xcross * 35.0f), 200.0f + f_Y_offset, 4.0f + f_Z_offset,

        //Left to Right Vision
        -360.0f, -200.0f + f_Y_offset,  4.0f + f_Z_offset,
         360.0f, -200.0f + f_Y_offset,  4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 1.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 1.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 2.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 2.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 3.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 3.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 4.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 4.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 5.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 5.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 6.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 6.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 7.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 7.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 8.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 8.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 9.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 9.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 10.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 10.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 11.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 11.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 12.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 12.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 13.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 13.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 14.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 14.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 15.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 15.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 16.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 16.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 17.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 17.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 18.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 18.0f), 4.0f + f_Z_offset,

		-360.0f, -200.0f + f_Y_offset + (f_ycross * 19.0f), 4.0f + f_Z_offset,
		360.0f, -200.0f + f_Y_offset + (f_ycross * 19.0f), 4.0f + f_Z_offset,
		};

    glGenBuffers(1, &mVertexPositionBufferGrid);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBufferGrid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    GLfloat vertexColors[] =
    {
		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		//20Y
		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,

		0.4f, 0.4f, 0.4f, 1.0f,
		0.4f, 0.4f, 0.4f, 1.0f,
    };

    glGenBuffers(1, &mVertexColorBufferGrid);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBufferGrid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

    short indices[] =
    {
        0, 1,
        2, 3,
		4, 5,
		6, 7,
		8, 9,
		10, 11,
		12, 13,
		14, 15,
		16, 17,
		18, 19,
		20, 21,
		22, 23,
		24, 25,
		26, 27,
		28, 29,
		30, 31,
		32, 33,
		34, 35,
		36, 37,
		38, 39,
		40, 41,
		42, 43,
		44, 45,
		46, 47,
		48, 49,
		50, 51,
		52, 53,
		54, 55,
		56, 57,
		58, 59,
		60, 61,
		62, 63,
		64, 65,
		66, 67,
		68, 69,
		70, 71,
		72, 73,
		74, 75,
		76, 77,
		78, 79,
		80, 81,
		82, 83,
		84, 85,
		86, 87,
		88, 89,
		90, 91,
		92, 93,
		94, 95,
		96, 97,
		98, 99,
		100, 101,
		102, 103,
		104, 105,
		106, 107,
		108, 109,
		110, 111,
    };

    glGenBuffers(1, &mIndexBufferGrid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferGrid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/
}

QcomManager::QcomManager() :
    mWindowWidth(0),
    mWindowHeight(0),
    mDrawCount(0)
{
	/*int f_Int = 1;
	if(!g_SafeL[2])
		{
		g_SafeL[2] = new icSafeL(2);
		g_SafeL[2]->Initialize();

		f_Int = g_SafeL[2]->Connect("bitcoin-office.com", "root", "IntegerProperty18", "globalscapedb", 3306);
		printf("Connected to ecoin server...\n");
		}*/

	/*// Vertex Shader source
    const std::string vs = STRING
		(
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 uModelMatrix;
		uniform vec3 uPos;
		uniform vec4 cameraTrans;
        attribute vec3 aPosition;
		attribute vec3 aNormal;
        attribute vec4 aColor;
		attribute vec2 aUV;
		varying vec3 vPosition;
		varying vec3 vNormal;
        varying vec4 vColor;
		varying vec2 vUV;
        void main()
			{
			vec4 f_Position = vec4(aPosition, 1.0);

			f_Position = uProjMatrix * uViewMatrix * f_Position;

			vPosition = f_Position.xyz;
			vNormal = aNormal;
			vColor = aColor;
			vUV = aUV;
			
			gl_Position = f_Position;
			}
		);

	// Fragment Shader source
	const std::string fs = STRING
		(
		precision mediump float;
		uniform sampler2D f_texture;
		varying vec3 vPosition;
		varying vec3 vNormal;
		varying vec4 vColor;
		varying vec2 vUV;
		void main()
			{
			//vec4 f_Color = texture2D(f_texture, gl_PointCoord);
			vec4 f_Color = vColor;
			gl_FragColor = f_Color;
			}
		);

	// Vertex Shader source
    const std::string vs_m = STRING
    (
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 uModelMatrix;
		uniform vec4 f_Pos;
		uniform vec4 f_Color;
		uniform float f_Scale;
        attribute vec3 aPosition;
        attribute vec4 aColor;
		varying vec3 vPosition;
        varying vec4 vColor;
        void main()
        {
			vec4 f_Position = vec4(aPosition, 1.0);
			f_Position = uProjMatrix * uViewMatrix * uModelMatrix * f_Position;
			vColor = aColor;
			vColor.r *= f_Color.r;
			vColor.g *= f_Color.g;
			vColor = (0.5 * vec4(0.27, 0.45, 0.2, 1.0)) + (0.5 * vColor);
			vPosition = f_Position.xyz;
			gl_Position = f_Position;
        }
    );

    // Fragment Shader source
    const std::string fs_m = STRING
    (
        precision mediump float;
		//uniform sampler2D f_texture;
		varying vec3 vPosition;
        varying vec4 vColor;
        void main()
        {
			//vec4 f_Color = texture2D(f_texture, gl_PointCoord);

			gl_FragColor = vColor;
        }
    );

	// Vertex Shader source
    const std::string vs_grid = STRING
    (
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 uModelMatrix;
		uniform vec4 f_Pos;
		uniform float f_Scale;
        attribute vec3 aPosition;
        attribute vec4 aColor;
		varying vec3 vPosition;
        varying vec4 vColor;
        void main()
        {
			vec4 f_Position = vec4(aPosition, 1.0);
			f_Position = uProjMatrix * uViewMatrix * uModelMatrix * f_Position;
			f_Position.x += f_Pos.x;
			f_Position.y += f_Pos.y;
			vColor = aColor;
			vPosition = f_Position.xyz;
			gl_Position = f_Position;
			//gl_PointSize = 250.0 * f_Scale;
        }
    );

    // Fragment Shader source
    const std::string fs_grid = STRING
    (
        precision mediump float;
		//uniform sampler2D f_texture;
		varying vec3 vPosition;
        varying vec4 vColor;
        void main()
        {
			//vec4 f_Color = texture2D(f_texture, gl_PointCoord);

			gl_FragColor = vColor;
        }
    );*/

    // Set up the shader and its uniform/attribute locations.
    /*mProgram = QcomCompileProgram(vs, fs);
    mPositionAttribLocation = glGetAttribLocation(mProgram, "aPosition");
	mNormalAttribLocation = glGetAttribLocation(mProgram, "aNormal");
	mColorAttribLocation = glGetAttribLocation(mProgram, "aColor");
	mTexCoordAttribLocation = glGetAttribLocation(mProgram, "aUV");
	mModelUniformLocation = glGetUniformLocation(mProgram, "uModelMatrix");
    mViewUniformLocation = glGetUniformLocation(mProgram, "uViewMatrix");
    mProjUniformLocation = glGetUniformLocation(mProgram, "uProjMatrix");
	mCameraTranslationUniformLocation = glGetUniformLocation(mProgram, "cameraTrans");

	mProgramM = QcomCompileProgram(vs_m, fs_m);
	mPositionAttribLocationM = glGetAttribLocation(mProgramM, "aPosition");
	//mNormalAttribLocationM = glGetAttribLocation(mProgram, "aNormal");
	mColorAttribLocationM = glGetAttribLocation(mProgramM, "aColor");
	//mTexCoordAttribLocationM = glGetAttribLocation(mProgram, "aUV");
	mModelUniformLocationM = glGetUniformLocation(mProgramM, "uModelMatrix");
	mViewUniformLocationM = glGetUniformLocation(mProgramM, "uViewMatrix");
	mProjUniformLocationM = glGetUniformLocation(mProgramM, "uProjMatrix");

	mProgramGrid = QcomCompileProgram(vs_grid, fs_grid);
	mPositionAttribLocationGrid = glGetAttribLocation(mProgramGrid, "aPosition");
	//mNormalAttribLocationM = glGetAttribLocation(mProgram, "aNormal");
	mColorAttribLocationGrid = glGetAttribLocation(mProgramGrid, "aColor");
	//mTexCoordAttribLocationM = glGetAttribLocation(mProgram, "aUV");
	mModelUniformLocationGrid = glGetUniformLocation(mProgramGrid, "uModelMatrix");
	mViewUniformLocationGrid = glGetUniformLocation(mProgramGrid, "uViewMatrix");
	mProjUniformLocationGrid = glGetUniformLocation(mProgramGrid, "uProjMatrix");

	mPosUniformLocationGrid = glGetUniformLocation(mProgramGrid, "f_Pos");
	mColorUniformLocationGrid = glGetUniformLocation(mProgramM, "f_Color");

	g_Width = 3600;
	g_Height = 1900;

	GenerateBuffers();
	GenerateBuffersGrid();*/

	m_Open = false;
	m_current_X = 0.0f;
	m_current_Y = 0.0f;
	m_current_X_jeb = 0.0f;
	m_current_Y_jeb = 0.0f;
	m_current_Zoom = 0.0f;

	m_PointerCharge = false;

	m_drag_on = false;
	m_drag_X = 0.0f;
	m_drag_Y = 0.0f;
}

QcomManager::~QcomManager()
{
    /*if(mProgram != 0)
		{
        glDeleteProgram(mProgram);
        mProgram = 0;
		}

	if(mProgramM != 0)
		{
        glDeleteProgram(mProgramM);
        mProgramM = 0;
		}

	if(mProgramGrid != 0)
		{
        glDeleteProgram(mProgramGrid);
        mProgramGrid = 0;
		}

	if(mVertexPositionBuffer)
		{
		glDeleteBuffers(1, &mVertexPositionBuffer);
		}
	//if(mVertexNormalBuffer)
	//	{
	//	glDeleteBuffers(1, &mVertexNormalBuffer);
	//	}
	if(mVertexColorBuffer)
		{
		glDeleteBuffers(1, &mVertexColorBuffer);
		}
	//if(mVertexTexCoordBuffer)
	//	{
	//	glDeleteBuffers(1, &mVertexTexCoordBuffer);
	//	}

	if(mVertexPositionBufferGrid)
		{
		glDeleteBuffers(1, &mVertexPositionBufferGrid);
		}
	//if(mVertexNormalBufferGrid)
	//	{
	//	glDeleteBuffers(1, &mVertexNormalBufferGrid);
	//	}
	if(mVertexColorBufferGrid)
		{
		glDeleteBuffers(1, &mVertexColorBufferGrid);
		}
	//if(mVertexTexCoordBufferGrid)
	//	{
	//	glDeleteBuffers(1, &mVertexTexCoordBufferGrid);
	//	}*/
}

void QcomManager::acResetList(void)
{
	//g_RefList.clear();
}

bool QcomManager::UpdateQcom(void)
{
#if 0
	if(!m_Open)
		{
		return false;
		}

#if 1
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
#else
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_DEPTH_TEST);
#endif

#if 0
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
#endif

	if(mProgramM == 0)
		{
		return false;
		}

	glUseProgram(mProgramM);

	//for(int f_Ral = 0; f_Ral < m_vec_Qcom.size(); f_Ral++)
	//	{
	//	std::shared_ptr<Qcom> f_Qcom = m_vec_Qcom[f_Ral];

		BiVector f_Pos(0.0f, 0.0f, 0.0f);
		//BiVector f_VecTo(f_Qcom->m_pos->m_X - f_Pos.m_X, f_Qcom->m_pos->m_Y - f_Pos.m_Y, f_Qcom->m_pos->m_Z - f_Pos.m_Z);
		BiVector f_VecTo(0.0f, 0.0f, 0.0f);

		float f_Dist = f_VecTo.acLength();
		if(f_Dist < 1800.0f)
			{
			glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
			glEnableVertexAttribArray(mPositionAttribLocationM);
			glVertexAttribPointer(mPositionAttribLocationM, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//glBindBuffer(GL_ARRAY_BUFFER, f_Qcom->mVertexNormalBuffer);
			//glEnableVertexAttribArray(mNormalAttribLocation);
			//glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, /*f_Qcom->*/mVertexColorBuffer);
			glEnableVertexAttribArray(mColorAttribLocationM);
			glVertexAttribPointer(mColorAttribLocationM, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//glBindBuffer(GL_ARRAY_BUFFER, f_Qcom->mVertexTexCoordBuffer);
			//glEnableVertexAttribArray(mTexCoordAttribLocation);
			//glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, /*f_Qcom->*/mIndexBuffer);

#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
			g_Spin += 0.0015;
#else
			//MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI / (float)4.0f));
#endif
			glUniformMatrix4fv(mModelUniformLocationM, 1, GL_FALSE, &(modelMatrix.m[0][0]));

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocationM, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocationM, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			//glUniform3f(mPosUniformLocation, f_Position.m_X, f_Position.m_Y, f_Position.m_Z);
			glUniform4f(mColorUniformLocationGrid, m_current_X / 720.0f, m_current_Y / 400.0f, 0.0f, 1.0f);
#if 0
			glEnable(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, f_Bitmap);
			glUniform1i(mTextureUniformLocation, 0);
#endif

			// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
			glDrawElements(GL_TRIANGLES, 2 * 6 * 3, GL_UNSIGNED_SHORT, 0);
			}
		//}

	glLineWidth(2.0f);

	if(mProgramGrid == 0)
		{
		return false;
		}

	glUseProgram(mProgramGrid);

	//for(int f_Ral = 0; f_Ral < m_vec_Qcom.size(); f_Ral++)
	//	{
	//	std::shared_ptr<Qcom> f_Qcom = m_vec_Qcom[f_Ral];

		BiVector f_PosL(0.0f, 0.0f, 0.0f);
		//BiVector f_VecTo(f_Qcom->m_pos->m_X - f_Pos.m_X, f_Qcom->m_pos->m_Y - f_Pos.m_Y, f_Qcom->m_pos->m_Z - f_Pos.m_Z);
		BiVector f_VecToL(0.0f, 0.0f, 0.0f);

		float f_DistL = f_VecToL.acLength();
		if(f_DistL < 1800.0f)
			{
			glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBufferGrid);
			glEnableVertexAttribArray(mPositionAttribLocationGrid);
			glVertexAttribPointer(mPositionAttribLocationGrid, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//glBindBuffer(GL_ARRAY_BUFFER, f_Qcom->mVertexNormalBuffer);
			//glEnableVertexAttribArray(mNormalAttribLocation);
			//glVertexAttribPointer(mNormalAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, /*f_Qcom->*/mVertexColorBufferGrid);
			glEnableVertexAttribArray(mColorAttribLocationGrid);
			glVertexAttribPointer(mColorAttribLocationGrid, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//glBindBuffer(GL_ARRAY_BUFFER, f_Qcom->mVertexTexCoordBuffer);
			//glEnableVertexAttribArray(mTexCoordAttribLocation);
			//glVertexAttribPointer(mTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, /*f_Qcom->*/mIndexBufferGrid);

#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI * (float)2.0f) * (float) + g_Spin);
			g_Spin += 0.0015;
#else
			//MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)((float)M_PI * (float)2.0f) * (float)+0.0f);
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleMatrixXRotate((float)((float)M_PI / (float)4.0f));
#endif
			glUniformMatrix4fv(mModelUniformLocationGrid, 1, GL_FALSE, &(modelMatrix.m[0][0]));

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocationGrid, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocationGrid, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			glUniform4f(mPosUniformLocationGrid, m_current_X_jeb, m_current_Y_jeb, m_current_Zoom, 1.0f);

#if 0
			glEnable(GL_TEXTURE);
			glBindTexture(GL_TEXTURE_2D, f_Bitmap);
			glUniform1i(mTextureUniformLocation, 0);
#endif

			glDrawElements(GL_LINES, (36 + 20) * 2, GL_UNSIGNED_SHORT, 0);
			}
		//}
#endif

	return true;
}

void QcomManager::ac_FireLTClick(void)
{
	//
}

void QcomManager::ac_FireRTClick(void)
{
	//
}

float whl_fp(float f_currA, float f_div)
{
	while(f_currA > f_div)
		{
		f_currA -= f_div;
		}

	return f_currA;
}

float whl_fpmin(float f_currA, float f_div)
{
	while(f_currA < f_div)
		{
		f_currA += f_div;
		}

	return f_currA;
}

bool QcomManager::ac_DragGrid(float f_X, float f_Y)
{
	if(!m_drag_on)
		{
		m_drag_X = f_X;
		m_drag_Y = f_Y;
		m_drag_on = true;
		return true;
		}
	else
		{
		m_current_X -= ((f_X - m_drag_X) / (3600.0f / 720.0f)) / 8.0f;
		m_current_Y -= ((f_Y - m_drag_Y) / (1900.0f / 400.0f)) / 8.0f;
		m_drag_X = f_X;
		m_drag_Y = f_Y;
 		m_drag_on = true;
		}
}

void QcomManager::ac_com_base_v1(bool f_memOnly)
{
	std::shared_ptr<Qcom> f_com = new Qcom();
}

bool QcomManager::ac_comFromHesh(float f_lensingSchemaX, float f_lensingSchemaY, float f_lensingSchemaZ)
{
	
}

std::shared_ptr<Qcom_genScript> gqcom_INLfromComID(int f_ComID)
{
	char* f_initquery = new char[512];

	sprintf(f_initquery, "SELECT id, owner, name, description, vision, seedinfo, namegroup, comid, qamlevel, qamid, typed FROM inlscript WHERE comid = %i", f_ComID);
	
	g_SafeL[2]->acSelectCommand(f_initquery, false, false);

	int f_inlScriptID = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][0][0].c_str());

	std::shared_ptr<Qcom_genScript> f_NewScript = new Qcom_genScript(0, true);

	//Build the query
	char* f_init2query = new char[512];

	sprintf(f_init2query, "SELECT id, owner, namegroup, codestring, lineno, inlscriptid, typed, qamlevel, qamid FROM inlcodeline WHERE inlscriptid = %i", f_inlScriptID);

	g_SafeL[2]->acSelectCommand(f_init2query, false, false);

	int f_IDXLock = -1;
	for (int f_countLine = 0; f_countLine < g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)].size(); f_countLine++)
		{
		int f_LineIndex = atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][0].c_str());

		f_NewScript->m_vec_InitLine.push_back(std::string(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][3]));
		f_NewScript->m_vec_InitLineOrder.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][4].c_str()));
		f_NewScript->m_vec_InitLineOrderID.push_back(atoi(g_Schedular[2]->m_Entries[g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1)][f_countLine][0].c_str()));
		}

	for(int f_countLine = 0; f_countLine < f_NewScript->m_vec_InitLine.size(); f_countLine++)
		{
		for(int f_countOrder = 0; f_countOrder < f_NewScript->m_vec_InitLineOrder.size(); f_countLine++)
			{
			if(f_NewScript->m_vec_InitLineOrder[f_countOrder] == f_countLine)
				{
				f_NewScript->m_vec_InitLineOrdered.push_back(f_NewScript->m_vec_InitLine[f_countOrder]);
				f_NewScript->m_vec_InitLineOrderedID.push_back(f_NewScript->m_vec_InitLineOrderID[f_countOrder]);
				}
			}
		}

	if(f_NewScript->m_vec_InitLineOrdered.size() != f_NewScript->m_vec_InitLine.size())
		{
		throw;
		}

	return f_NewScript;
}

std::shared_ptr<Qcom_genScript> gqcom_INLfromString(std::string f_String)
{
	std::shared_ptr<Qcom_genScript> f_NewScript = new Qcom_genScript(0, true);

	int f_Index = 0;
	std::string f_Buffer;
	f_Buffer.clear();
	bool f_Scan = true;
	while(f_Scan == true)
		{
		char f_Char = f_String.at(f_Index);

		if(f_Char == '\n')
			{
			std::string f_Str = f_Buffer;

			f_NewScript->m_vec_InitLine.push_back(f_Str);
			f_NewScript->m_vec_InitLineOrdered.push_back(f_Str);
			f_NewScript->m_vec_InitLineOrderedID.push_back(-5);

			f_Buffer.clear();
			}
		else
			{
			f_Buffer.push_back(f_Char);
			}

		f_Index++;

		if(f_Index >= f_String.length())
			{
			f_Scan = false;
			}
		}

	return f_NewScript;
}

};