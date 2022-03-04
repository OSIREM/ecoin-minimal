/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"
#include "Target.h"

#include <cctype>
#include <iostream>
#include <cstring>

int g_SchemaTop = 0;
Cube::BiVector g_SchemaRef[500];
int g_SchemaSize = 1;

int g_ComponentStamp = 0;

int g_TargetID = 0;

using namespace ecoin;

namespace ecoin
{
std::vector<int> g_ElementDivisor;
std::vector<float> g_ElementDivisorFloat;
std::shared_ptr<classCollection> g_Lowton_Collection;
std::shared_ptr<classLMap> g_classLMap;
int g_CountLM = 4;
std::shared_ptr<Qcom> g_ShuttleCom;

int g_FunctionStamp = 0;
std::shared_ptr<classTarget_JScript> g_MasterTarget = std::make_shared<classTarget_JScript>();

std::vector<std::string> g_vec_scrInputName;
int g_idx_vec_scrInputName = 0;

std::vector<std::string> g_vec_scrInputHTML;
int g_idx_vec_scrInputHTML = 0;

std::vector<int> g_vec_scrInputType;
int g_idx_vec_scrInputType;

std::vector<nameFuncPtr> g_vec_scrInputNameCuteFunc;
int g_idx_vec_scrInputNameCuteFunc = 0;

std::vector<FuncPtr> g_vec_scrInputTestCuteFunc;
int g_idx_vec_scrInputTestCuteFunc = 0;

std::vector<std::string> g_vec_scrControlName;
int g_idx_vec_scrControlName = 0;

std::vector<int> g_vec_scrControlType;
int g_idx_vec_scrControlType = 0;

std::vector<std::string> g_vec_scrOutputName;
int g_idx_vec_scrOutputName = 0;

std::vector<int> g_vec_scrOutputType;
int g_idx_vec_scrOutputType = 0;

std::vector<std::shared_ptr<classBridge>> g_vec_control_Bridge;
int g_idx_vec_control_Bridge = 0;

std::vector<std::shared_ptr<classBridge>> g_vec_output_Bridge;
int g_idx_vec_output_Bridge = 0;

bool g_EnablePR = false;
std::string g_ThisName = "Default_Insta";
int g_ThisType = ESL_INSTA_TYPE_FUNC_DEF;
std::shared_ptr<classInsta> g_This = std::make_shared<classInsta>(g_ThisName, g_ThisType);

bool g_Result = false;

std::shared_ptr<classTarget> g_Target_1;
std::shared_ptr<classTarget> g_Target_2;
std::shared_ptr<classTarget_Ecom> g_Target_3;
std::shared_ptr<classTarget_Ecom> g_Target_4;
std::shared_ptr<classTarget_ESL_Script> g_Target_5;
std::shared_ptr<classTarget_ESL_Script> g_Target_6;
std::shared_ptr<classTarget_Generation_Script> g_Target_7;
std::shared_ptr<classTarget_Generation_Script> g_Target_8;
std::shared_ptr<classTarget_JScript> g_Target_9;
std::shared_ptr<classTarget_JScript> g_Target_10;

std::shared_ptr<classTarget> gf_Target_1;
std::shared_ptr<classTarget> gf_Target_2;
std::shared_ptr<classTarget_Ecom> gf_Target_3;
std::shared_ptr<classTarget_Ecom> gf_Target_4;
std::shared_ptr<classTarget_ESL_Script> gf_Target_5;
std::shared_ptr<classTarget_ESL_Script> gf_Target_6;
std::shared_ptr<classTarget_Generation_Script> gf_Target_7;
std::shared_ptr<classTarget_Generation_Script> gf_Target_8;
std::shared_ptr<classTarget_JScript> gf_Target_9;
std::shared_ptr<classTarget_JScript> gf_Target_10;

std::shared_ptr<classTarget> g_LowtonTarget_1;
std::shared_ptr<classTarget> g_LowtonTarget_2;
std::shared_ptr<classTarget_Ecom> g_LowtonTarget_3;
std::shared_ptr<classTarget_Ecom> g_LowtonTarget_4;
std::shared_ptr<classTarget_ESL_Script> g_LowtonTarget_5;
std::shared_ptr<classTarget_ESL_Script> g_LowtonTarget_6;
std::shared_ptr<classTarget_Generation_Script> g_LowtonTarget_7;
std::shared_ptr<classTarget_Generation_Script> g_LowtonTarget_8;
std::shared_ptr<classTarget_JScript> g_LowtonTarget_9;
std::shared_ptr<classTarget_JScript> g_LowtonTarget_10;

std::shared_ptr<classTarget_Ecom> g_LowtonTarget;

bool g_currentLaunch = false;
int g_currentLaunchType = 0;
std::string g_currentLaunchPrefix = "";
std::string g_currentLaunchTypeName = "";

std::string g_ComputeText = "";
std::string g_ComputeText_Lowton = "";
int g_ComputeText_PrintMode = ECOIN_MUTEX_MODE_OFF;
int g_ComputeText_PrintMode_Lowton = ECOIN_MUTEX_MODE_OFF;
int g_Compute_PrintMode_Count = 0;

float ag_Get_current_Target_Mark(int f_Type)
{
	switch(f_Type)
		{
		case 0:
		case 1:
			{
			return gf_Target_1->m_Mark;
			}break;
		case 2:
			{
			return gf_Target_2->m_Mark;
			}break;
		case 3:
			{
			return gf_Target_3->m_Mark;
			}break;
		case 4:
			{
			return gf_Target_4->m_Mark;
			}break;
		case 5:
			{
			return gf_Target_5->m_Mark;
			}break;
		case 6:
			{
			return gf_Target_6->m_Mark;
			}break;
		case 7:
			{
			return gf_Target_7->m_Mark;
			}break;
		case 8:
			{
			return gf_Target_8->m_Mark;
			}break;
		case 9:
			{
			return gf_Target_9->m_Mark;
			}break;
		case 10:
			{
			return gf_Target_10->m_Mark;
			}break;
		}

	return FLT_MAX;
}

classTarget::classTarget(std::shared_ptr<CubeHESH> f_Hesh)
{
	m_Collection = std::make_shared<classCollection>();
	m_Collection->acClear();

	for(int f_Count = 0; f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
		{
		std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Hesh->vec_Bicycle[f_Count]);
		 
		f_Element->acStructuredAnalysis();

		if(f_Element->m_Result.m_SurfToLegRatio > 0.17)
			{
			std::shared_ptr<classSurface> f_Surface = std::make_shared<classSurface>(f_Element);

			if(f_Element->m_Result.m_LevelParent < 0)
				{
				f_Element->m_vec_Element.push_back(f_Element);
				f_Element->m_vec_Surface.push_back(f_Surface);
				m_Collection->m_vec_Element.push_back(f_Element);
				m_Collection->m_vec_Surface.push_back(f_Surface);
				}
			else
				{
				f_Element->m_vec_Element.push_back(f_Element);
				f_Element->m_vec_Surface.push_back(f_Surface);
				f_Element->m_Result.m_Parent->m_vec_Element.push_back(f_Element);
				f_Element->m_Result.m_Parent->m_vec_Surface.push_back(f_Surface);
				}
			}
		else
			{
			std::shared_ptr<classLeg> f_Leg = std::make_shared<classLeg>(f_Element);

			if(f_Element->m_Result.m_LevelParent < 0)
				{
				f_Element->m_vec_Element.push_back(f_Element);
				f_Element->m_vec_Leg.push_back(f_Leg);
				m_Collection->m_vec_Leg.push_back(f_Leg);
				m_Collection->m_vec_Element.push_back(f_Element);
				}
			else
				{
				f_Element->m_vec_Element.push_back(f_Element);
				f_Element->m_vec_Leg.push_back(f_Leg);
				f_Element->m_Result.m_Parent->m_vec_Element.push_back(f_Element);
				f_Element->m_Result.m_Parent->m_vec_Leg.push_back(f_Leg);
				}
			}
		}

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];

		for(int f_CountCollision = 0; f_CountCollision < m_Collection->m_vec_Element.size(); f_CountCollision++)
			{
			if(f_Count != f_CountCollision)
				{
				shared_ptr<classElement> f_ElementCollide = m_Collection->m_vec_Element[f_CountCollision];
				
				if(f_Element->m_aabb->collide(f_ElementCollide->m_aabb))
					{
					f_Element->m_vec_Collission.push_back(f_CountCollision);
					
					if(f_Element->m_aabb->inside(f_ElementCollide->m_Center))
						{
						f_ElementCollide->m_vec_IsIn.push_back(f_CountCollision);
						}

					if(f_ElementCollide->m_aabb->inside(f_Element->m_Center))
						{
						f_Element->m_vec_IsIn.push_back(f_Count);
						}
					}
				}
			}
		}

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];

		if(f_Element->m_vec_IsIn.size() == 1)
			{
			shared_ptr<classElement> f_ParentElement = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[0]];

			f_ParentElement->m_vec_Element.push_back(f_Element);

			// Leg
			if(f_Element->m_vec_Surface.size() == 0 && f_Element->m_vec_Leg.size() >= 1)
				{
				f_ParentElement->m_vec_Leg.push_back(f_Element->m_vec_Leg[0]);
				}
			else // Surface
				{
				if(f_Element->m_vec_Surface.size() == 0 && f_Element->m_vec_Leg.size() == 0)
					{
					//Do nothing
					}
				else // Surface
					{
					if(f_Element->m_vec_Surface.size() >= 1)
						{
						f_ParentElement->m_vec_Surface.push_back(f_Element->m_vec_Surface[0]);
						}
					}
				}

			classResult f_ParentResult = f_ParentElement->m_Result;
			classResult f_ElementResult = f_Element->m_Result;

			for(int f_Coyu = 0; f_Coyu < 8; f_Coyu++)
				{
				f_ParentResult.m_vec_Corner.push_back(f_ElementResult.m_vec_Corner[f_Coyu]);
				}

			classJoint f_Joint(f_ParentElement, f_Element);

			f_Element->m_vec_Joint.push_back(f_Joint);
			f_ParentElement->m_vec_Joint.push_back(f_Joint);
			}
		else if(f_Element->m_vec_IsIn.size() > 1)
			{
			float f_Size = 0.0f;
			int f_Index = f_Count;
			if(f_Count == 0)
				{
				f_Size = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[1]]->m_Volume;
				}
			else
				{
				f_Size = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[0]]->m_Volume;
				}

			for(int f_CountSize = 0; f_CountSize < m_Collection->m_vec_Element.size(); f_CountSize++)
				{
				if(f_Count != f_CountSize)
					{
					shared_ptr<classElement> f_SizeElement = m_Collection->m_vec_Element[f_CountSize];

					if(f_SizeElement->m_Volume < f_Size)
						{
						f_Size = f_SizeElement->m_Volume;
						f_Index = f_CountSize;
						}
					}
				}
			
			shared_ptr<classElement> f_ParentElement = m_Collection->m_vec_Element[f_Index];

			f_ParentElement->m_vec_Element.push_back(f_Element);

			// Leg
			if(f_Element->m_vec_Surface.size() == 0 && f_Element->m_vec_Leg.size() >= 1)
				{
				f_ParentElement->m_vec_Leg.push_back(f_Element->m_vec_Leg[0]);
				}
			else // Surface
				{
				if(f_Element->m_vec_Surface.size() == 0 && f_Element->m_vec_Leg.size() == 0)
					{
					//Do nothing
					}
				else // Surface
					{
					if(f_Element->m_vec_Surface.size() >= 1)
						{
						f_ParentElement->m_vec_Surface.push_back(f_Element->m_vec_Surface[0]);
						}
					}
				}

			classResult f_ParentResult = f_ParentElement->m_Result;
			classResult f_ElementResult = f_Element->m_Result;

			for(int f_Coyu = 0; f_Coyu < 8; f_Coyu++)
				{
				f_ParentResult.m_vec_Corner.push_back(f_ElementResult.m_vec_Corner[f_Coyu]);
				}

			classJoint f_Joint(f_ParentElement, f_Element);

			f_Element->m_vec_Joint.push_back(f_Joint);
			f_ParentElement->m_vec_Joint.push_back(f_Joint);
			}
		}

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];

		if(f_Element->m_vec_Collission.size() == 1)
			{
			shared_ptr<classElement> f_FriendlyElement = m_Collection->m_vec_Element[f_Element->m_vec_Collission[0]];

			if (f_Element->m_Volume >= f_FriendlyElement->m_Volume)
				{
				classJoint f_Joint(f_Element, f_FriendlyElement);

				f_Element->m_vec_Joint.push_back(f_Joint);
				f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
				}
			else
				{
				classJoint f_Joint(f_FriendlyElement, f_Element);

				f_Element->m_vec_Joint.push_back(f_Joint);
				f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
				}
			}
		else if(f_Element->m_vec_Collission.size() > 1)
			{
			for(int f_CountElement = 0; f_CountElement < f_Element->m_vec_Collission.size(); f_CountElement++)
				{
				if(f_Count != f_CountElement)
					{
					shared_ptr<classElement> f_FriendlyElement = m_Collection->m_vec_Element[f_Element->m_vec_Collission[f_CountElement]];

					if(f_Element->m_Volume >= f_FriendlyElement->m_Volume)
						{
						classJoint f_Joint(f_Element, f_FriendlyElement);

						f_Element->m_vec_Joint.push_back(f_Joint);
						f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
						}
					else
						{
						classJoint f_Joint(f_FriendlyElement, f_Element);

						f_Element->m_vec_Joint.push_back(f_Joint);
						f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
						}
					}
				}
			}
		}

	m_Mark = 0.0f;
}

classTargetScript::classTargetScript(std::shared_ptr<CubeHESH> f_Hesh)
{
	m_Collection = std::make_shared<classCollection>();
	m_Collection->acClear();

	m_CollectionScript = std::make_shared<classCollectionScript>();
	m_CollectionScript->acClear();

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Hesh->vec_Bicycle[f_Hesh->m_adIndex[f_Count]]);
		std::shared_ptr<classElementScript> f_ElementScript = std::make_shared<classElementScript>(f_Element);

		f_Element->acStructuredAnalysis();

		m_Collection->m_vec_Element.push_back(f_Element);
		m_CollectionScript->m_vec_ElementScript.push_back(f_ElementScript);
		}

#pragma message("FIXME::Add connect the variable same names to collection script for circuit")

	m_Mark = 0.0f;
}

void classTarget::acPrintStats(void)
{
	printf("classTarget Statistics");

}

bool classTarget::acCompare(std::shared_ptr<classTarget> f_Target, float f_QualityRank, float f_Grade, bool f_testVolumes)
{
	 /////////////////////
	//Prime Decision
	bool f_True = false;

	if(m_Collection->m_vec_Element.size() < f_Target->m_Collection->m_vec_Element.size())
		{
		f_Target->m_Mark = 0.0f;

		for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
			{
			shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];
			shared_ptr<classElement> f_TestElement = f_Target->m_Collection->m_vec_Element[f_Count];

			float f_Mark = f_Element->acCompare(f_TestElement, f_QualityRank, f_testVolumes);

			f_Target->m_Mark += f_Mark;
			}
		}
	else
		{
		f_Target->m_Mark = 0.0f;

		for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
			{
			float f_fakeMark = 0.0f;

			shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];
			shared_ptr<classElement> f_TestElement = f_Target->m_Collection->m_vec_Element[0];

			float f_Mark = f_Element->acCompare(f_TestElement, f_QualityRank, f_testVolumes);

			f_fakeMark = f_Mark;

			for(int f_Cam = 0; f_Cam < f_Target->m_Collection->m_vec_Element.size(); f_Cam++)
				{
				shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];
				shared_ptr<classElement> f_TestElement = f_Target->m_Collection->m_vec_Element[f_Cam];

				float f_Mark = f_Element->acCompare(f_TestElement, f_QualityRank, f_testVolumes);

				if(f_Mark < f_fakeMark)
					{
					f_fakeMark = f_Mark;
					}
				}

			f_Target->m_Mark += f_fakeMark;
			}
		}

	if(f_Target->m_Mark > 0.0f)
		{
		if(g_CoolDown <= 0)
			{
			if((f_Target->m_Mark <= (f_Grade + g_CoolBoost)) && (f_Target->m_Mark != 0.0f))
				{
				f_True = true;
				g_CoolDown = 20000;
				g_CoolBoost = 1.0f;
				}
			else
				{
				f_True = false;
				}

			//ecoin grade verify with Coolboost
			}
		else if(g_CoolDown > 7500)
			{
			if((f_Target->m_Mark <= (g_CoolBoost / 2.0f)) && (f_Target->m_Mark != 0.0f))
				{
				f_True = true;
				g_CoolDown = 20000;
				g_CoolBoost = 1.0f;
				}
			else
				{
				f_True = false;
				}

			//ecoin grade verify with minus boost
			}
		else
			{
			if((f_Target->m_Mark <= f_Grade) && (f_Target->m_Mark != 0.0f))
				{
				f_True = true;
				g_CoolDown = 20000;
				g_CoolBoost = 1.0f;
				}
			else
				{
				f_True = false;
				}

			//ecoin grade verify nominal
			}
		}

	g_CoolDown -= 1;
	g_CoolBoost += 0.01f;

	//CubeHESHGen(%i)QualityRank[%f]:Mark %f < Diff(%f) tVol=%i g_Boost(%f)\n", f_True, f_QualityRank, f_Target->m_Mark, f_Grade, f_testVolumes, g_CoolBoost

	return f_True;
}

float classTarget::acMatch(std::shared_ptr<classTarget> f_Target)
{
	float f_Mark = 0.0f;

	if(m_Collection->m_vec_Element.size() < f_Target->m_Collection->m_vec_Element.size())
		{
		for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
			{
			shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];
			shared_ptr<classElement> f_TestElement = f_Target->m_Collection->m_vec_Element[f_Count];

			for(int f_XY = 0; f_XY < 8; f_XY++)
				{
				BiVector f_Vector = f_Element->vec_Vertex[f_XY];
				BiVector f_TestVector = f_TestElement->vec_Vertex[f_XY];

				BiVector f_LengthVec = f_TestVector - f_Vector;

				float f_Length = f_LengthVec.acLength();

				f_Mark += f_Length * ECOIN_TARGET_MATCH_LENGTH_FACTOR;

				BiVector f_VectorC = f_Element->vec_Color[f_XY];
				BiVector f_TestVectorC = f_TestElement->vec_Color[f_XY];

				BiVector f_LengthVecC = f_TestVectorC - f_VectorC;

				float f_LengthC = f_LengthVecC.acLength();

				f_Mark += f_LengthC * ECOIN_TARGET_MATCH_COLOR_LENGTH_FACTOR;
				}
			}
		}
	else
		{
		for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
			{
			float f_fakeMark = 0.0f;

			shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];
			shared_ptr<classElement> f_TestElement = f_Target->m_Collection->m_vec_Element[0];

			for(int f_XY = 0; f_XY < 8; f_XY++)
				{
				BiVector f_Vector = f_Element->vec_Vertex[f_XY];
				BiVector f_TestVector = f_TestElement->vec_Vertex[f_XY];

				BiVector f_LengthVec = f_TestVector - f_Vector;

				float f_Length = f_LengthVec.acLength();

				f_Mark += f_Length * ECOIN_TARGET_MATCH_LENGTH_FACTOR;

				BiVector f_VectorC = f_Element->vec_Color[f_XY];
				BiVector f_TestVectorC = f_TestElement->vec_Color[f_XY];

				BiVector f_LengthVecC = f_TestVectorC - f_VectorC;

				float f_LengthC = f_LengthVecC.acLength();

				f_Mark += f_LengthC * ECOIN_TARGET_MATCH_COLOR_LENGTH_FACTOR;
				}
			}
		}

	if(f_Mark > 0.0f)
		{
		return f_Mark;
		}

	return FLT_MAX;
}

void classTarget::acGen_Humanoid(void)
{
	for(int f_XY = 0; f_XY < 1; f_XY++)
		{
		std::shared_ptr<classElement> f_Head = std::make_shared<classElement>(0.35f);
		std::shared_ptr<classElement> f_Torso = std::make_shared<classElement>(1.0f);
		std::shared_ptr<classElement> f_Pelvis = std::make_shared<classElement>(0.45f);
		std::shared_ptr<classElement> f_RightArm = std::make_shared<classElement>(0.35f);
		std::shared_ptr<classElement> f_LeftArm = std::make_shared<classElement>(0.35f);
		std::shared_ptr<classElement> f_RightLeg = std::make_shared<classElement>(0.55f);
		std::shared_ptr<classElement> f_LeftLeg = std::make_shared<classElement>(0.55f);

		f_Head->m_vec_Element.push_back(f_Head);
		f_Torso->m_vec_Element.push_back(f_Head);
		f_Pelvis->m_vec_Element.push_back(f_Head);
		f_RightArm->m_vec_Element.push_back(f_Head);
		f_LeftArm->m_vec_Element.push_back(f_Head);
		f_RightLeg->m_vec_Element.push_back(f_Head);
		f_LeftLeg->m_vec_Element.push_back(f_Head);

		f_Head->m_vec_Leg.push_back(std::make_shared<classLeg>(f_Head));
		f_Torso->m_vec_Leg.push_back(std::make_shared<classLeg>(f_Torso));
		f_Pelvis->m_vec_Leg.push_back(std::make_shared<classLeg>(f_Pelvis));
		f_RightArm->m_vec_Leg.push_back(std::make_shared<classLeg>(f_RightArm));
		f_LeftArm->m_vec_Leg.push_back(std::make_shared<classLeg>(f_LeftArm));
		f_RightLeg->m_vec_Leg.push_back(std::make_shared<classLeg>(f_RightLeg));
		f_LeftLeg->m_vec_Leg.push_back(std::make_shared<classLeg>(f_LeftLeg));

		f_Head->m_Index = f_XY + 0;
		m_Collection->m_vec_Element.push_back(f_Head);
		f_Torso->m_Index = f_XY + 1;
		m_Collection->m_vec_Element.push_back(f_Torso);
		f_Pelvis->m_Index = f_XY + 2;
		m_Collection->m_vec_Element.push_back(f_Pelvis);
		f_RightArm->m_Index = f_XY + 3;
		m_Collection->m_vec_Element.push_back(f_RightArm);
		f_LeftArm->m_Index = f_XY + 4;
		m_Collection->m_vec_Element.push_back(f_LeftArm);
		f_RightLeg->m_Index = f_XY + 5;
		m_Collection->m_vec_Element.push_back(f_RightLeg);
		f_LeftLeg->m_Index = f_XY + 6;
		m_Collection->m_vec_Element.push_back(f_LeftLeg);

		m_Collection->m_vec_Leg.push_back(f_Head->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_Torso->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_Pelvis->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_RightArm->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_LeftArm->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_RightLeg->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_LeftLeg->m_vec_Leg[0]);

		f_Torso->m_vec_Element.push_back(f_Head);
		f_Torso->m_vec_Leg.push_back(f_Head->m_vec_Leg[0]);

		f_Torso->m_vec_Element.push_back(f_Pelvis);
		f_Torso->m_vec_Leg.push_back(f_Pelvis->m_vec_Leg[0]);

		f_Pelvis->m_vec_Element.push_back(f_LeftLeg);
		f_Pelvis->m_vec_Leg.push_back(f_LeftLeg->m_vec_Leg[0]);

		f_Pelvis->m_vec_Element.push_back(f_RightLeg);
		f_Pelvis->m_vec_Leg.push_back(f_RightLeg->m_vec_Leg[0]);

		f_Torso->m_vec_Element.push_back(f_LeftArm);
		f_Torso->m_vec_Leg.push_back(f_LeftArm->m_vec_Leg[0]);

		f_Torso->m_vec_Element.push_back(f_RightArm);
		f_Torso->m_vec_Leg.push_back(f_RightArm->m_vec_Leg[0]);
		}

	m_Mark = 0.0f;
}

void classTarget::acGen_Vehicle_Ground(void)
{
	std::shared_ptr<classElement> f_Base = std::make_shared<classElement>(3.35f);
	std::shared_ptr<classElement> f_Front = std::make_shared<classElement>(1.0f);
	std::shared_ptr<classElement> f_Rear = std::make_shared<classElement>(1.45f);
	std::shared_ptr<classElement> f_Top = std::make_shared<classElement>(2.35f);
	std::shared_ptr<classElement> f_LeftFrontTire = std::make_shared<classElement>(0.35f);
	std::shared_ptr<classElement> f_RightFrontTire = std::make_shared<classElement>(0.35f);
	std::shared_ptr<classElement> f_LeftRearTire = std::make_shared<classElement>(0.35f);
	std::shared_ptr<classElement> f_RightRearTire = std::make_shared<classElement>(0.35f);

	f_Base->m_vec_Leg.push_back(std::make_shared<classLeg>(f_Base));
	f_Front->m_vec_Leg.push_back(std::make_shared<classLeg>(f_Front));
	f_Rear->m_vec_Leg.push_back(std::make_shared<classLeg>(f_Rear));
	f_Top->m_vec_Leg.push_back(std::make_shared<classLeg>(f_Top));
	f_LeftFrontTire->m_vec_Leg.push_back(std::make_shared<classLeg>(f_LeftFrontTire));
	f_RightFrontTire->m_vec_Leg.push_back(std::make_shared<classLeg>(f_RightFrontTire));
	f_LeftRearTire->m_vec_Leg.push_back(std::make_shared<classLeg>(f_LeftRearTire));
	f_RightRearTire->m_vec_Leg.push_back(std::make_shared<classLeg>(f_RightRearTire));

	f_Base->m_Index = 0;
	m_Collection->m_vec_Element.push_back(f_Base);
	f_Front->m_Index = 1;
	m_Collection->m_vec_Element.push_back(f_Front);
	f_Rear->m_Index = 2;
	m_Collection->m_vec_Element.push_back(f_Rear);
	f_Top->m_Index = 3;
	m_Collection->m_vec_Element.push_back(f_Top);
	f_LeftFrontTire->m_Index = 4;
	m_Collection->m_vec_Element.push_back(f_LeftFrontTire);
	f_RightFrontTire->m_Index = 5;
	m_Collection->m_vec_Element.push_back(f_RightFrontTire);
	f_LeftRearTire->m_Index = 6;
	m_Collection->m_vec_Element.push_back(f_LeftRearTire);
	f_RightRearTire->m_Index = 7;
	m_Collection->m_vec_Element.push_back(f_RightRearTire);

	m_Collection->m_vec_Leg.push_back(f_Base->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_Front->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_Rear->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_Top->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_LeftFrontTire->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_RightFrontTire->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_LeftRearTire->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_RightRearTire->m_vec_Leg[0]);

	f_Base->m_vec_Element.push_back(f_Top);
	f_Base->m_vec_Leg.push_back(f_Top->m_vec_Leg[0]);

	f_Base->m_vec_Element.push_back(f_Front);
	f_Base->m_vec_Leg.push_back(f_Front->m_vec_Leg[0]);

	f_Base->m_vec_Element.push_back(f_Rear);
	f_Base->m_vec_Leg.push_back(f_Rear->m_vec_Leg[0]);

	f_Front->m_vec_Element.push_back(f_LeftFrontTire);
	f_Front->m_vec_Leg.push_back(f_LeftFrontTire->m_vec_Leg[0]);

	f_Front->m_vec_Element.push_back(f_RightFrontTire);
	f_Front->m_vec_Leg.push_back(f_RightFrontTire->m_vec_Leg[0]);

	f_Rear->m_vec_Element.push_back(f_LeftRearTire);
	f_Rear->m_vec_Leg.push_back(f_LeftRearTire->m_vec_Leg[0]);

	f_Rear->m_vec_Element.push_back(f_RightRearTire);
	f_Rear->m_vec_Leg.push_back(f_RightRearTire->m_vec_Leg[0]);

	m_Mark = 0.0f;
}

void classTarget::acLoad_from_TargetID(int f_TargetID)
{
	int f_Int = 1;
	if(!g_SafeL[0])
		{
		g_SafeL[0] = new icSafeL(0);
		g_SafeL[0]->Initialize();

		f_Int = g_SafeL[0]->Connect("localhost", "root", "f", "gdb", 3306);
		}

	  ////////////////
	 // targets
	//
	if(f_TargetID > 0)
		{
		g_TargetID = f_TargetID;
		//ECN::Loading Target ID g_TargetID);

		char* elementquery;
		elementquery = (char*)malloc(sizeof(char) * 1024);

		::sprintf(elementquery, "SELECT id, volume FROM element WHERE targetid = %i", g_TargetID);

		g_SafeL[0]->acSelectCommand(elementquery, false, false);

		int f_eleCount = 0;
		
		if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
			{
			f_eleCount = 0;
			}
		else
			{
			f_eleCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
			}

		for(int f_EleID = 0; f_EleID < f_eleCount; f_EleID++)
			{
			std::shared_ptr<classElement> f_NewElement = std::make_shared<classElement>((float)atof(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][f_EleID][1].c_str()));

			f_NewElement->m_vec_Leg.push_back(std::make_shared<classLeg>(f_NewElement));
			f_NewElement->m_Index = f_EleID;

			m_Collection->m_vec_Element.push_back(f_NewElement);
			}

		char* elindexquery;
		elindexquery = (char*)malloc(sizeof(char) * 1024);
		::sprintf(elindexquery, "SELECT elementid, resultid FROM elindex WHERE targetid = %i", g_TargetID);
		delete elindexquery;

		g_SafeL[0]->acSelectCommand(elindexquery, false, false);

		int f_elindexCount = 0;
		
		if(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][0][0].at(0) == '0')
			{
			f_elindexCount = 0;
			}
		else
			{
			f_elindexCount = g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)].size();
			}

		for(int f_ElindexID = 0; f_ElindexID < f_elindexCount; f_ElindexID++)
			{
			shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][f_ElindexID][0].c_str())];
			shared_ptr<classElement> f_AElement = m_Collection->m_vec_Element[atoi(g_Schedular[0]->m_Entries[g_Schedular[0]->ac_GetEntry(g_Schedular[0]->m_Entries.size() - 1)][f_ElindexID][1].c_str())];
			
			f_Element->m_vec_Element.push_back(f_AElement);
			f_Element->m_vec_Leg.push_back(f_AElement->m_vec_Leg[0]);
			}

		m_Mark = 0.0f;
		}
}

void classTarget::acSaveCloud(std::string f_Name)
{
	  ////////////////
	 // targets
	//
	char* g_targetfield[5];
	char* g_targetvalue[5];

	for(int f_Count = 0; f_Count < 5; f_Count++)
		{
		g_targetfield[f_Count] = (char*)malloc(sizeof(char) * 64);
		g_targetvalue[f_Count] = (char*)malloc(sizeof(char) * 64);
		}

	::sprintf(g_targetfield[0], "name");
	::sprintf(g_targetfield[1], "difficulty");
	::sprintf(g_targetfield[2], "bckred");
	::sprintf(g_targetfield[3], "bckgreen");
	::sprintf(g_targetfield[4], "bckblue");

	::sprintf(g_targetvalue[0], "%s", f_Name.c_str());
	::sprintf(g_targetvalue[1], "%f", 89.75);
	::sprintf(g_targetvalue[2], "%f", Cube::random());
	::sprintf(g_targetvalue[3], "%f", Cube::random());
	::sprintf(g_targetvalue[4], "%f", Cube::random());

	int f_TargetID = g_SafeL[0]->Insert("target", (const char **)g_targetfield, (const char **)g_targetvalue, 5, false, false);

	for(int f_Count = 0; f_Count < 5; f_Count++)
		{
		delete g_targetfield[f_Count];
		delete g_targetvalue[f_Count];
		}

	for(int f_ElementID = 0; f_ElementID < m_Collection->m_vec_Element.size(); f_ElementID++)
		{
		  ////////////////
		 // element
		//
		char* g_elementfield[6];
		char* g_elementvalue[6];

		for(int f_Count = 0; f_Count < 6; f_Count++)
			{
			g_elementfield[f_Count] = (char*)malloc(sizeof(char) * 256);
			g_elementvalue[f_Count] = (char*)malloc(sizeof(char) * 256);
			}

		::sprintf(g_elementfield[0], "description");
		::sprintf(g_elementfield[1], "targetid");
		::sprintf(g_elementfield[2], "vert1x");
		::sprintf(g_elementfield[3], "vert1y");
		::sprintf(g_elementfield[4], "vert1z");
		::sprintf(g_elementfield[5], "volume");

		::sprintf(g_elementvalue[0], "%s", "Body Part");
		::sprintf(g_elementvalue[1], "%i", f_TargetID);
		::sprintf(g_elementvalue[2], "%f", 0.0f);
		::sprintf(g_elementvalue[3], "%f", 0.0f);
		::sprintf(g_elementvalue[4], "%f", 0.0f);
		::sprintf(g_elementvalue[5], "%f", m_Collection->m_vec_Element[f_ElementID]->m_Volume);

		g_SafeL[0]->Insert("element", (const char **)g_elementfield, (const char **)g_elementvalue, 6, false, false);

		for(int f_Count = 0; f_Count < 6; f_Count++)
			{
			delete g_elementfield[f_Count];
			delete g_elementvalue[f_Count];
			}
		}

	for(int f_ElementID2 = 0; f_ElementID2 < m_Collection->m_vec_Element.size(); f_ElementID2++)
		{
		for(int f_ElementID3 = 0; f_ElementID3 < m_Collection->m_vec_Element[f_ElementID2]->m_vec_Element.size(); f_ElementID3++)
			{
			  ////////////////
			 // elindex
			//
			char* g_elindexfield[3];
			char* g_elindexvalue[3];

			for(int f_Count = 0; f_Count < 3; f_Count++)
				{
				g_elindexfield[f_Count] = (char*)malloc(sizeof(char) * 256);
				g_elindexvalue[f_Count] = (char*)malloc(sizeof(char) * 256);
				}

			::sprintf(g_elindexfield[0], "targetid");
			::sprintf(g_elindexfield[1], "elementid");
			::sprintf(g_elindexfield[2], "resultid");

			::sprintf(g_elindexvalue[0], "%i", f_TargetID);
			::sprintf(g_elindexvalue[1], "%i", m_Collection->m_vec_Element[f_ElementID2]->m_Index);
			::sprintf(g_elindexvalue[2], "%i", m_Collection->m_vec_Element[f_ElementID2]->m_vec_Element[f_ElementID3]->m_Index);

			g_SafeL[0]->Insert("elindex", (const char **)g_elindexfield, (const char **)g_elindexvalue, 3, false, false);

			for(int f_Count = 0; f_Count < 3; f_Count++)
				{
				delete g_elindexfield[f_Count];
				delete g_elindexvalue[f_Count];
				}
			}
		}
}

void classTargetScript::ag_PrintScriptHeader(void)
{
	printf("|classTarget-Script Generated C Language|\n");
	printf("'''''''''''''''''''''''''''''''''''''''''\n");
	printf(".\n");
}

void classTargetScript::acPrint(void)
{
	ag_PrintScriptHeader();

	for(int f_XY = 0; f_XY < m_CollectionScript->m_vec_ElementScript.size(); f_XY++)
		{
		shared_ptr<classElementScript> f_ElementScript = m_CollectionScript->m_vec_ElementScript[f_XY];

		for(int f_Z = 0; f_Z < f_ElementScript->m_vec_Component.size(); f_Z++)
			{
			shared_ptr<classComponent> f_Component = f_ElementScript->m_vec_Component[f_Z];

			printf("%s\n", f_Component->m_String.c_str());
			}
		}
}

classTarget_JScript::classTarget_JScript()
{
	m_Collection = std::make_shared<classCollection>();
	m_Collection->acClear();

	m_vec_Function.clear();
	m_idx_vec_Function = 0;
	
	m_Mark = 0.0;
	
	m_vec_Name.clear();
	m_idx_vec_Name = 0;
	
	m_SchemaTop = 0;
	m_SchemaRef.clear();
	
	for(int f_Count = 0; f_Count < 18; f_Count++)
		{
		m_SchemaRef.push_back(std::make_shared<BiVector>(0.0f));
		}

	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;

	m_Factor.clear();

	for(int f_XY = 0; f_XY < INSTA_TYPE_COUNT; f_XY++)
		{
		m_Factor.push_back(std::make_shared<classFactor>());
		}

	m_Factor.push_back(std::make_shared<classFactor>());

	m_InstaCountMap = 0;

	m_String = "";

	  ////////////////////////////////////
	 // LEGACY of Structured Analysis
	//
	//m_vec_Result.clear();
	//m_idx_vec_Result = 0;
	
	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();
}

classTarget_ESL_Script::classTarget_ESL_Script()
{
	m_Collection = std::make_shared<classCollection>();
	m_Collection->acClear();
	
	m_Mark = 0.0;
	
	m_vec_Name.clear();
	m_idx_vec_Name = 0;
	
	m_SchemaTop = 0;
	m_SchemaRef.clear();
	
	for(int f_Count = 0; f_Count < 18; f_Count++)
		{
		m_SchemaRef.push_back(std::make_shared<BiVector>(0.0f));
		}

	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;

	m_Factor.clear();

	for(int f_XY = 0; f_XY < INSTA_TYPE_COUNT; f_XY++)
		{
		m_Factor.push_back(std::make_shared<classFactor>());
		}

	m_Factor.push_back(std::make_shared<classFactor>());

	m_String = "";

	  ////////////////////////////////////
	 // LEGACY of Structured Analysis
	//
	//m_vec_Result.clear();
	//m_idx_vec_Result = 0;
	
	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();
}

classTarget_Ecom::classTarget_Ecom()
{
	m_GlobalScope = true;

	m_Collection = std::make_shared<classCollection>();
	m_Collection->acClear();
	
	m_Mark = 0.0;
	
	m_vec_Name.clear();
	m_idx_vec_Name = 0;
	
	m_SchemaTop = 0;
	m_SchemaRef.clear();
	
	m_SchemaRef.push_back(std::make_shared<BiVector>(0.0f));
	
	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;

	m_Factor.clear();

	for(int f_XY = 0; f_XY < INSTA_TYPE_COUNT; f_XY++)
		{
		m_Factor.push_back(std::make_shared<classFactor>());
		}

	m_Factor.push_back(std::make_shared<classFactor>());

	m_String = "";

	  ////////////////////////////////////
	 // LEGACY of Structured Analysis
	//
	//m_vec_Result.clear();
	//m_idx_vec_Result = 0;
	
	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();
}

classTarget_Ecom::classTarget_Ecom(bool f_Scope)
{
	m_GlobalScope = f_Scope;

	m_Collection = std::make_shared<classCollection>();
	m_Collection->acClear();
	
	m_Mark = 0.0;
	
	m_vec_Name.clear();
	m_idx_vec_Name = 0;
	
	m_SchemaTop = 0;
	m_SchemaRef.clear();
	
	m_SchemaRef.push_back(std::make_shared<BiVector>(0.0f));

	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;

	m_Factor.clear();

	for(int f_XY = 0; f_XY < INSTA_TYPE_COUNT; f_XY++)
		{
		m_Factor.push_back(std::make_shared<classFactor>());
		}

	m_Factor.push_back(std::make_shared<classFactor>());

	m_String = "";
	
	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();
}

classTarget_Ecom::~classTarget_Ecom()
{
	m_Collection->acClear();
	
	m_Mark = 0.0;
	
	m_vec_Name.clear();
	m_idx_vec_Name = 0;
	
	m_SchemaTop = 0;
	m_SchemaRef.clear();

	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;

	m_Factor.clear();

	m_String = "";
	
	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();
}

void classTarget_JScript::acPowerDown(void)
{
	//...
}

void classTarget_Ecom::acPrepare_Lense(void)
{
	m_SchemaTop = 0;

	m_SchemaRef[0]->m_X = 0.120f;
	m_SchemaRef[0]->m_Y = 0.70f;
	m_SchemaRef[0]->m_Z = 0.95f;
}

clsName::clsName(std::string f_Name, int f_BitCount, int f_INSTA, int f_index_Insta, int f_index_Function)
{
	m_Name = f_Name;
	m_BitCount = f_BitCount;
	m_INSTA_Type = f_INSTA;
	m_index_Insta = f_index_Insta;
	m_index_Function = f_index_Function;

	m_vec_Name.clear();
	m_idx_vec_Name = 0;
}

classBridge::classBridge()
{
	m_vec_A.clear();
	m_vec_Type.clear();
	m_vec_LineType.clear();
	m_idx_vec = 0;
}

void classBridge::ac_add_Path(int f_A, int f_Type, int f_LineType)
{
	m_vec_A.push_back(f_A);
	m_vec_Type.push_back(f_Type);
	m_vec_LineType.push_back(f_LineType);
	m_idx_vec++;
}

classListI::classListI(int f_INSTA)
{
	m_vec_List.clear();
	m_idx_vec_List = 0;
	
	for(int f_Jet = 0; f_Jet < g_idx_vec_scrInputType; f_Jet++)
		{
		if(g_vec_scrInputType[f_Jet] == f_INSTA)
			{
			m_vec_List.push_back(g_vec_scrInputName[f_Jet]);
			m_idx_vec_List++;
			}
		}
}

classListC::classListC(int f_INSTA)
{
	m_vec_List.clear();
	m_idx_vec_List = 0;

	for(int f_Jet = 0; f_Jet < g_idx_vec_scrControlType; f_Jet++)
		{
		if(g_vec_scrControlType[f_Jet] == f_INSTA)
			{
			m_vec_List.push_back(g_vec_scrControlName[f_Jet]);
			m_idx_vec_List++;
			}
		}
}

classListO::classListO(int f_INSTA)
{
	m_vec_List.clear();
	m_idx_vec_List = 0;

	for(int f_Jet = 0; f_Jet < g_idx_vec_scrOutputType; f_Jet++)
		{
		if(g_vec_scrOutputType[f_Jet] == f_INSTA)
			{
			m_vec_List.push_back(g_vec_scrOutputName[f_Jet]);
			m_idx_vec_List++;
			}
		}
}

classList_Target_Name::classList_Target_Name(int f_INSTA, std::shared_ptr<classTarget_JScript> f_Target)
{
	m_vec_List.clear();
	m_idx_vec_List = 0;

	for(int f_Jet = 0; f_Jet < f_Target->m_idx_vec_Name; f_Jet++)
		{
		if(f_Target->m_vec_Name[f_Jet]->m_INSTA_Type == f_INSTA)
			{
			m_vec_List.push_back(f_Target->m_vec_Name[f_Jet]->m_Name);
			m_idx_vec_List++;
			}
		}
}

classList_Target_Name::classList_Target_Name(int f_INSTA, std::shared_ptr<classTarget_ESL_Script> f_Target)
{
	m_vec_List.clear();
	m_idx_vec_List = 0;

	for(int f_Jet = 0; f_Jet < f_Target->m_idx_vec_Name; f_Jet++)
		{
		if(f_Target->m_vec_Name[f_Jet]->m_INSTA_Type == f_INSTA)
			{
			m_vec_List.push_back(f_Target->m_vec_Name[f_Jet]->m_Name);
			m_idx_vec_List++;
			}
		}
}

classList_Target_Name::classList_Target_Name(int f_INSTA, std::shared_ptr<classTarget_Ecom> f_Target)
{
	m_vec_List.clear();
	m_idx_vec_List = 0;

	for(int f_Jet = 0; f_Jet < f_Target->m_idx_vec_Name; f_Jet++)
		{
		if(f_Target->m_vec_Name[f_Jet]->m_INSTA_Type == f_INSTA)
			{
			m_vec_List.push_back(f_Target->m_vec_Name[f_Jet]->m_Name);
			m_idx_vec_List++;
			}
		}
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classTarget_JScript::acMakeUnison(std::shared_ptr<classTarget_JScript> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, shared_ptr<classElement> f_Element, int f_index_Insta, int f_index_Function)
{
	if(f_INSTA == INSTA_TYPE_VAR_CALL)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared<classListI>(INSTA_TYPE_VAR_CALL);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_VAR_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);

					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_VAR_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_VAR_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_VAR_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_VAR_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared<classListC>(INSTA_TYPE_VAR_CALL);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared<classListO>(INSTA_TYPE_VAR_CALL);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_VAR_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else if(f_INSTA == INSTA_TYPE_FUNC_CALL)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared<classListI>(INSTA_TYPE_FUNC_CALL);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else
		{
		int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
		if(f_FingerFactorial >= 2)
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
		
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 5);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else
			{
			std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
			f_clsName->m_vec_Name.push_back(f_clsName);
			f_clsName->m_idx_vec_Name++;
			
			f_Target->m_vec_Name.push_back(f_clsName);
			f_Target->m_idx_vec_Name++;
			
			return f_Name;
			}
		}
		
	std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);

	f_clsName->m_vec_Name.push_back(f_clsName);
	f_clsName->m_idx_vec_Name++;
	
	f_Target->m_vec_Name.push_back(f_clsName);
	f_Target->m_idx_vec_Name++;
	
	return f_Name;
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classTarget_Ecom::acMakeUnison(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, int f_index_Insta, int f_index_Function)
{
#if 0
	if(f_INSTA == ESL_INSTA_TYPE_VAR_DEF)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared<classListI>(ESL_INSTA_TYPE_VAR_DEF);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);

					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(ESL_INSTA_TYPE_VAR_DEF, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(ESL_INSTA_TYPE_VAR_DEF, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else if(f_INSTA == INSTA_TYPE_FUNC_CALL)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared<classListI>(INSTA_TYPE_FUNC_CALL);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else
		{
		int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
		if(f_FingerFactorial >= 2)
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
		
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 5);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else
			{
			std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
			f_clsName->m_vec_Name.push_back(f_clsName);
			f_clsName->m_idx_vec_Name++;
			
			f_Target->m_vec_Name.push_back(f_clsName);
			f_Target->m_idx_vec_Name++;
			
			return f_Name;
			}
		}
#endif
		
	std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
	f_clsName->m_vec_Name.push_back(f_clsName);
	f_clsName->m_idx_vec_Name++;
	
	f_Target->m_vec_Name.push_back(f_clsName);
	f_Target->m_idx_vec_Name++;
	
	return f_Name;
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classTarget_Ecom::acMakeUnisonType(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_index_Insta, int f_index_Function, int f_TypeGiven, int f_FullDefinition)
{
#if 0
	if(f_INSTA == ESL_INSTA_TYPE_VAR_DEF)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared<classListI>(ESL_INSTA_TYPE_VAR_DEF);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);

					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(ESL_INSTA_TYPE_VAR_DEF, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(ESL_INSTA_TYPE_VAR_DEF, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else if(f_INSTA == INSTA_TYPE_FUNC_CALL)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared<classListI>(INSTA_TYPE_FUNC_CALL);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else
		{
		int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
		if(f_FingerFactorial >= 2)
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
		
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 5);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else
			{
			std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
			f_clsName->m_vec_Name.push_back(f_clsName);
			f_clsName->m_idx_vec_Name++;
			
			f_Target->m_vec_Name.push_back(f_clsName);
			f_Target->m_idx_vec_Name++;
			
			return f_Name;
			}
		}
#endif

	std::string f_TypeAndNameResult;
	f_TypeAndNameResult.clear();

	bool isClassVar = false;

	if(f_FullDefinition == true)
		{
		if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1))
			{	//Sys
			f_TypeAndNameResult += "Sys%%";
			}
		else
			{
			if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1))
				{	//Var
				f_TypeAndNameResult += "Var%%";
				}
			else
				{
				if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1))
					{	//ClassVar
					f_TypeAndNameResult += "ClassVar%%";

					isClassVar = true;
					}
				}
			}
		}

	if(isClassVar == false)
		{
		if(f_TypeGiven < 0)
			{
			if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
				{
				f_TypeAndNameResult += "float&&";
				}
			else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
				{
				f_TypeAndNameResult += "int&&";
				}
			else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
				{
				f_TypeAndNameResult += "String&&";
				}
			else
				{
				throw; //add debug message makeunisontype vartype unknown
				}
			}
		else
			{
			if(f_TypeGiven == MuVar_Float)
				{
				f_TypeAndNameResult += "float&&";
				}
			else if(f_TypeGiven == MuVar_Int)
				{
				f_TypeAndNameResult += "int&&";
				}
			else if(f_TypeGiven == MuVar_Int)
				{
				f_TypeAndNameResult += "String&&";
				}
			else
				{
				throw; //add debug message makeunisontype vartype unknown
				}
			}
		}
	else
		{
		std::string f_ClassVarType = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		f_TypeAndNameResult += f_ClassVarType + "&$";
		}

	f_TypeAndNameResult += f_Name + "%%";
		
	std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
	f_clsName->m_vec_Name.push_back(f_clsName);
	f_clsName->m_idx_vec_Name++;
	
	f_Target->m_vec_Name.push_back(f_clsName);
	f_Target->m_idx_vec_Name++;
	
	return f_TypeAndNameResult;
}

classLMap::classLMap()
{
	m_Mark = 0.0;

	m_LMap = make_shared<LMap>();

	acClear();

	m_SchemaTop = 0;
	m_SchemaRef.clear();
	g_ElementDivisor.clear();
	g_ElementDivisorFloat.clear();
}

void classLMap::acPrepareLense(int f_OCSCP_ThreadIndex)
{
	m_SchemaTop = 0;
	m_SchemaRef[f_OCSCP_ThreadIndex]->m_X = 0.120;
	m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y = 0.70;
	m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z = 0.95;
	g_SchemaSize = 3;

	g_ElementDivisor[f_OCSCP_ThreadIndex] = 0;
	g_ElementDivisorFloat[f_OCSCP_ThreadIndex] = 0.0f;
}

classLMap::~classLMap()
{
	acClear();
}

void classLMap::acClearAway(void)
{
	m_String.clear();

	m_idx_vec_Function = 0;
	m_idx_vec_Achievement = 0;
	m_idx_vec_CountLock = 0;
	m_idx_vec_Name = 0;

	m_SchemaTop = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();

	m_vec_Name.clear();
	m_SchemaRef.clear();
	m_Factor.clear();
	m_vec_CountLock.clear();
	m_vec_Achievement.clear();

	for(int f_Helly = 0; f_Helly < m_vec_Ecom.size(); f_Helly++)
		{
		m_vec_Ecom[f_Helly]->ac_Clear();
		}
	
	m_vec_Ecom.clear();
}

void classLMap::acClear(void)
{
	acClearAway();

	m_LMap->acClear();

	m_GlobalScope = false;
	m_Mark = 0.0f;
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classLMap::acMakeUnisonType(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, int f_index_Insta, int f_index_Function, std::string f_LineString, int f_LineStartIndex, int f_TypeGiven, bool f_FullDefinition)
{
#if 0
	if(f_INSTA == ESL_INSTA_TYPE_VAR_DEF)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared<classListI>(ESL_INSTA_TYPE_VAR_DEF);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);

					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(ESL_INSTA_TYPE_VAR_DEF, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(ESL_INSTA_TYPE_VAR_DEF, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else if(f_INSTA == INSTA_TYPE_FUNC_CALL)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared<classListI>(INSTA_TYPE_FUNC_CALL);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else
		{
		int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
		if(f_FingerFactorial >= 2)
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
		
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 5);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else
			{
			std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
			f_clsName->m_vec_Name.push_back(f_clsName);
			f_clsName->m_idx_vec_Name++;
			
			f_Target->m_vec_Name.push_back(f_clsName);
			f_Target->m_idx_vec_Name++;
			
			return f_Name;
			}
		}
#endif

	std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

	std::string f_TypeAndNameResult;
	f_TypeAndNameResult.clear();

	int f_ElementIndex = 0;

	bool isClassVar = false;

	if(f_FullDefinition == true)
		{
		char f_c = f_morfarray[f_LineStartIndex][0].at(0);

		if(f_c == 'S')
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, true, f_ElementIndex); //has system

			f_TypeAndNameResult += "Sys%%";
			}
		else
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, false, f_ElementIndex); //has no system

			if(f_c == 'V')
				{
				f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, true, f_ElementIndex); //has var

				f_TypeAndNameResult += "Var%%";
				}
			else
				{
				f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, false, f_ElementIndex); //has var

				if(f_c == 'C')
					{
					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, true, f_ElementIndex); //has var

					f_TypeAndNameResult += "ClassVar%%";

					isClassVar = true;
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, false, f_ElementIndex); //has no system
					}
				}
			}
		}

	if(isClassVar == false)
		{
		if(f_TypeGiven < 0)
			{
			int f_VarType = agFind_CurrentSpec_VarType(f_morfarray[f_LineStartIndex + 1][0]);

			bool f_Spec_Three[3];

			if(f_VarType == ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT)
				{
				f_Spec_Three[0] = true;
				f_Spec_Three[1] = false;
				f_Spec_Three[2] = false;
				}
			else if(f_VarType == ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT)
				{
				f_Spec_Three[0] = false;
				f_Spec_Three[1] = true;
				f_Spec_Three[2] = false;
				}
			else if(f_VarType == ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING)
				{
				f_Spec_Three[0] = false;
				f_Spec_Three[1] = false;
				f_Spec_Three[2] = true;
				}

			if(f_Spec_Three[0] == true)
				{
				f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(1, 1, true, f_ElementIndex);

				f_TypeAndNameResult += "float&&";
				}
			else
				{
				f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(1, 1, false, f_ElementIndex);

				if(f_Spec_Three[1] == true)
					{
					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(1, 1, true, f_ElementIndex);

					f_TypeAndNameResult += "int&&";
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(1, 1, false, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(1, 1, true, f_ElementIndex);

					f_TypeAndNameResult += "String&&";
					}
				}
			}
		else
			{
			if(f_TypeGiven == MuVar_Float)
				{
				f_TypeAndNameResult += "float&&";
				}
			else if(f_TypeGiven == MuVar_Int)
				{
				f_TypeAndNameResult += "int&&";
				}
			else
				{
				f_TypeAndNameResult += "String&&";
				}
			}
		}
	else
		{
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_TypeAndNameResult += ac_recordMeasurement(f_morfarray[f_LineStartIndex + 1][0] + "%%", f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, 1);
		}

	f_TypeAndNameResult += f_Name + "%%";
		
	std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
	f_clsName->m_vec_Name.push_back(f_clsName);
	f_clsName->m_idx_vec_Name++;
	
	f_Target->m_vec_Name.push_back(f_clsName);
	f_Target->m_idx_vec_Name++;
	
	return f_TypeAndNameResult;
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classTarget_ESL_Script::acMakeUnison(std::shared_ptr<classTarget_ESL_Script> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, shared_ptr<classElement> f_Element, int f_index_Insta, int f_index_Function)
{
	if(f_INSTA == ESL_INSTA_TYPE_VAR_DEF)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared<classListI>(ESL_INSTA_TYPE_VAR_DEF);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);

					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(ESL_INSTA_TYPE_VAR_DEF, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared<classListC>(ESL_INSTA_TYPE_VAR_DEF);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared<classListO>(ESL_INSTA_TYPE_VAR_DEF);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(ESL_INSTA_TYPE_VAR_DEF, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else if(f_INSTA == INSTA_TYPE_FUNC_CALL)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared<classListI>(INSTA_TYPE_FUNC_CALL);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared<classListC>(INSTA_TYPE_FUNC_CALL);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared<classListO>(INSTA_TYPE_FUNC_CALL);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else
		{
		int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
		if(f_FingerFactorial >= 2)
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
		
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 5);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else
			{
			std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
			f_clsName->m_vec_Name.push_back(f_clsName);
			f_clsName->m_idx_vec_Name++;
			
			f_Target->m_vec_Name.push_back(f_clsName);
			f_Target->m_idx_vec_Name++;
			
			return f_Name;
			}
		}
		
	std::shared_ptr<clsName> f_clsName = std::make_shared<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
	f_clsName->m_vec_Name.push_back(f_clsName);
	f_clsName->m_idx_vec_Name++;
	
	f_Target->m_vec_Name.push_back(f_clsName);
	f_Target->m_idx_vec_Name++;
	
	return f_Name;
}

void classTarget_JScript::acGatherNames(void)
{
	//FROZEN//
	//AJAX bitcoin-office.com for gathering names
	//presents Math functions feel free to edit
	m_vec_Name.push_back(std::make_shared<clsName>("Math.abs(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	/*m_vec_Name[m_idx_vec_Name]->m_Code = function(f_IN)
		 {
	     var f_Input = f_IN;
		 var f_Output = 
	     }*/
	m_vec_Name.push_back(std::make_shared<clsName>("Math.acos(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.acosh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.asin(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.asinh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.atan(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.atan2(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.atanh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.acosh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.cbrt(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.ceil(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.cos(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.atan2(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.atanh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.acosh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.cbrt(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.ceil(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.cosh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.exp(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.floor(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.log(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.max(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.min(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.pow(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.random(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.round(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.sin(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.sinh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.sqrt(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.tan(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.tanh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	m_vec_Name.push_back(std::make_shared<clsName>("Math.trunc(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
}

std::string classTarget_JScript::ac_next_InputName(int f_Type)
{
	bool f_BoolScan = true;
	
	while((g_vec_scrInputType[m_GRCinput[f_Type]] != f_Type) && (f_BoolScan == true))
		{
		m_GRCinput[f_Type]++;
		
		if(m_GRCinput[f_Type] >= g_idx_vec_scrInputType)
			{
			f_BoolScan = false;
			}
		}
		
	m_GRMinput[f_Type] = m_GRCinput[f_Type];
	m_GRMinput[f_Type]++;
	
	if(f_BoolScan == true)
		{
		while((g_vec_scrInputType[m_GRMinput[f_Type]] != f_Type) && (f_BoolScan == true))
			{
			m_GRMinput[f_Type]++;
			
			if(m_GRMinput[f_Type] >= g_idx_vec_scrInputType)
				{
				f_BoolScan = false;
				}
			}
		}
	else
		{
		throw("Should not reach this point");
		}
		
	if(f_BoolScan == true)
		{
		return g_vec_scrInputName[m_GRCinput[f_Type]];
		}
	else
		{
		m_GRMinput[f_Type] = -5;
		return g_vec_scrInputName[m_GRCinput[f_Type]];
		}
}

std::string classTarget_JScript::ac_next_ControlName(int f_Type)
{
	bool f_BoolScan = true;
	
	while((g_vec_scrControlType[m_GRCcontrol[f_Type]] != f_Type) && (f_BoolScan == true))
		{
		m_GRCcontrol[f_Type]++;
		
		if(m_GRCcontrol[f_Type] >= g_idx_vec_scrControlType)
			{
			f_BoolScan = false;
			}
		}
		
	m_GRMcontrol[f_Type] = m_GRCcontrol[f_Type];
	m_GRMcontrol[f_Type]++;
	
	if(f_BoolScan == true)
		{
		while((g_vec_scrControlType[m_GRMcontrol[f_Type]] != f_Type) && (f_BoolScan == true))
			{
			m_GRMcontrol[f_Type]++;
			
			if(m_GRMcontrol[f_Type] >= g_idx_vec_scrControlType)
				{
				f_BoolScan = false;
				}
			}
		}
	else
		{
		for(;;)
			{
			//.
			}
		}
		
	if(f_BoolScan == true)
		{
		return g_vec_scrControlName[m_GRCcontrol[f_Type]];
		}
	else
		{
		m_GRMcontrol[f_Type] = -5;
		return g_vec_scrControlName[m_GRCcontrol[f_Type]];
		}
}

std::string classTarget_JScript::ac_next_OutputName(int f_Type)
{
	bool f_BoolScan = true;
	
	while((g_vec_scrOutputType[m_GRCoutput[f_Type]] != f_Type) && (f_BoolScan == true))
		{
		m_GRCoutput[f_Type]++;
		
		if(m_GRCoutput[f_Type] >= g_idx_vec_scrOutputType)
			{
			f_BoolScan = false;
			}
		}
		
	m_GRMoutput[f_Type] = m_GRCoutput[f_Type];
	m_GRMoutput[f_Type]++;
	
	if(f_BoolScan == true)
		{
		while((g_vec_scrOutputType[m_GRMoutput[f_Type]] != f_Type) && (f_BoolScan == true))
			{
			m_GRMoutput[f_Type]++;
			
			if(m_GRMoutput[f_Type] >= g_idx_vec_scrOutputType)
				{
				f_BoolScan = false;
				}
			}
		}
	else
		{
		for(;;)
			{
			//.
			}
		}
		
	if(f_BoolScan == true)
		{
		return g_vec_scrOutputName[m_GRCoutput[f_Type]];
		}
	else
		{
		m_GRMoutput[f_Type] = -5;
		return g_vec_scrOutputName[m_GRCoutput[f_Type]];
		}
}

void classTarget_JScript::acMerge_ICOtoName(void)
{
	//Input
	for(int f_XY = 0; f_XY < g_idx_vec_scrInputName; f_XY++)
		{
		m_vec_Name.push_back(std::make_shared<clsName>(g_vec_scrInputName[f_XY], 0, g_vec_scrInputType[f_XY], 0, 0));
		m_idx_vec_Name++;
		}

	//Control
	for(int f_XY = 0; f_XY < g_idx_vec_scrControlName; f_XY++)
		{
		m_vec_Name.push_back(std::make_shared<clsName>(g_vec_scrControlName[f_XY], 0, g_vec_scrControlType[f_XY], 0, 0));
		m_idx_vec_Name++;
		}
		
	//Output
	for(int f_XY = 0; f_XY < g_idx_vec_scrOutputName; f_XY++)
		{
		m_vec_Name.push_back(std::make_shared<clsName>(g_vec_scrOutputName[f_XY], 0, g_vec_scrOutputType[f_XY], 0, 0));
		m_idx_vec_Name++;
		}
}

void classTarget_JScript::acGatherICO_default(void)
{
	 //////////////////////////
	// 
	g_vec_scrInputName.push_back("ac_takeMeasurementINTV1");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_X");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Y");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Z");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrControlName.push_back("Math.cos");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sin");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sqrt");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("if(");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_CONDITIONAL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrOutputName.push_back("");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("playSound");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
}

classBridgeResult::classBridgeResult()
{
	m_vec_LineIndex.clear();
	m_vec_Position_Equals.clear();
	m_vec_Position_Argument.clear();
	m_vec_String_Equal.clear();
	m_idx_vec = 0;
}

classCodeLine::classCodeLine()
{
	m_vec_Code.clear();
	m_idx_vec_Code = 0;
}

std::shared_ptr<classBridgeResult> classTarget_JScript::acScan_Code_Bridges(std::shared_ptr<classFunction> f_Function, std::string f_String)
{
	std::shared_ptr<classBridgeResult> f_Result = std::make_shared<classBridgeResult>();

	for(int f_XY = 0; f_XY < f_Function->m_idx_vec_CodeLineStorage; f_XY++)
		{
		std::shared_ptr<classCodeLine> f_Line = f_Function->m_vec_CodeLineStorage[f_XY];

		for(int f_I = 0; f_I < f_Line->m_idx_vec_Code; f_I++)
			{
			bool f_Found = true;

			for(int f_Grand = 0; (f_Grand < f_Line->m_vec_Code[f_I]->m_String.length()) && (f_Grand < f_String.length()); f_Grand++)
				{
				if(f_Line->m_vec_Code[f_I]->m_String.at(f_Grand) != f_String.at(f_Grand))
					{
					f_Found = false;
					}
				}
			
			if(f_Found == true)
				{
				f_Result->m_vec_LineIndex.push_back(f_XY);

				if(f_I == 0)
					{
					f_Result->m_vec_Position_Equals.push_back(f_I);
					f_Result->m_vec_Position_Argument.push_back(-5);
					f_Result->m_vec_String_Equal.push_back("E");
					}
				else
					{
					bool f_Function = false;
					int f_Index = 0;

					for(int f_Jet = 0; f_Jet < f_I; f_Jet++)
						{
						if(f_Line->m_vec_Code[f_Jet]->m_Type == INSTA_TYPE_FUNC_CALL)
							{
							f_Function = true;
							f_Index = f_Jet;
							}
						}

					if(f_Function == true)
						{
						f_Result->m_vec_Position_Equals.push_back(f_I);
						f_Result->m_vec_Position_Argument.push_back(f_I - f_Index);
						f_Result->m_vec_String_Equal.push_back("F");
						}
					else
						{
						f_Result->m_vec_Position_Equals.push_back(f_I);
						f_Result->m_vec_Position_Argument.push_back(-5);
						f_Result->m_vec_String_Equal.push_back(f_Line->m_vec_Code[0]->m_String);
						}
					}

				f_Result->m_idx_vec++;
				}
			}
		}

	return f_Result;
}

classTestArg::classTestArg()
{
	build_LastNameClose.clear();
	build_LastTypeClose.clear();
	f_indexInsta = 0;
	f_indexFunction = 0;
}

std::shared_ptr<classMark> classTarget_JScript::acMark_TestICO(std::shared_ptr<classTarget_JScript> f_Target)
{
	std::shared_ptr<classMark> f_Mark = std::make_shared<classMark>();
	
	std::shared_ptr<classFunction> f_Function = m_vec_Function[0];
	
	int f_Run = 0;
	for(int f_XY = 0; f_XY < f_Function->m_idx_vec_CodeLineStorage; f_XY++)
		{
		std::shared_ptr<classCodeLine> f_Line = f_Function->m_vec_CodeLineStorage[f_XY];

		for(int f_I = 0; f_I < f_Line->m_idx_vec_Code; f_I++)
			{
			g_This = f_Line->m_vec_Code[f_I];
			g_ThisType = f_Line->m_vec_Code[f_I]->m_Type;
			g_ThisName = f_Line->m_vec_Code[f_I]->m_String;
				
			std::shared_ptr<classTestArg> f_testARG = std::make_shared<classTestArg>();
			f_testARG->f_indexInsta = f_I;
			f_testARG->f_indexFunction = f_Run + f_I;
			
			for(int f_L = f_I - 1; f_L >= 0; f_L--)
				{
				f_testARG->build_LastNameClose.push_back(f_Line->m_vec_Code[f_L]->m_String);
				f_testARG->build_LastTypeClose.push_back(f_Line->m_vec_Code[f_L]->m_Type);
				}
			
			f_testARG->build_LastNameClose.push_back("-5");
			f_testARG->build_LastTypeClose.push_back(-5);
			
			for(int f_A = 0; f_A < g_idx_vec_scrInputTestCuteFunc; f_A++)
				{
				std::shared_ptr<classAchievement> f_Achievement = g_vec_scrInputTestCuteFunc[f_A](f_Target, f_testARG);
			
				f_Mark->acIncrement(f_Achievement->m_Mark);
			
				if(f_Achievement->m_Success == true)
					{
					m_vec_Achievement.push_back(f_Achievement);
					m_idx_vec_Achievement++;
					}
				}
			}
			
		f_Run += f_Line->m_idx_vec_Code;
		}

	return f_Mark;
}

std::shared_ptr<classMark> classTarget_JScript::acMark_Bridges(void)
{
	std::shared_ptr<classMark> f_Mark = std::make_shared<classMark>();
	
	std::vector<std::string> f_vec_Scanlist;
	int f_idx_vec_Scanlist = 0;
	
	std::shared_ptr<classFunction> f_Function = m_vec_Function[0];
	
	for(int f_Helly = 0; f_Helly < g_idx_vec_control_Bridge; f_Helly++)
		{
		std::shared_ptr<classBridge> f_Bridge = g_vec_control_Bridge[f_Helly];
		
		if(f_Bridge->m_vec_Type[0] == INSTA_TYPE_CONDITIONAL)
			{
			if((f_Bridge->m_vec_LineType[1] == LINE_TYPE_INPUT) &&
			   (f_Bridge->m_vec_LineType[2] == LINE_TYPE_INPUT))
				{
				//Scan, Search Wider			
				std::shared_ptr<classBridgeResult> f_BridgeResultB = acScan_Code_Bridges(f_Function, g_vec_scrInputName[f_Bridge->m_vec_A[1]]);
				std::shared_ptr<classBridgeResult> f_BridgeResultC = acScan_Code_Bridges(f_Function, g_vec_scrInputName[f_Bridge->m_vec_A[2]]);
				
				if(f_BridgeResultB->m_idx_vec == 0 &&
				   f_BridgeResultC->m_idx_vec == 0)
					{
					f_Mark->m_vec_Int[4] += 30;
					}
				else
					{
					if(f_BridgeResultB->m_idx_vec >= 1)
						{
						for(int f_Jet = 0; f_Jet < f_BridgeResultB->m_idx_vec; f_Jet++)
							{
							if(f_BridgeResultB->m_vec_Position_Equals[f_Jet] >= 1 ||
							   f_BridgeResultB->m_vec_Position_Argument[f_Jet] != -5)
								{
								f_Mark->m_vec_Int[6] += 3;
								
								f_vec_Scanlist.push_back(f_BridgeResultB->m_vec_String_Equal[f_Jet]);
								f_idx_vec_Scanlist++;
								}
							}
						}
					
					if(f_BridgeResultC->m_idx_vec >= 1)
						{
						for(int f_Jet = 0; f_Jet < f_BridgeResultC->m_idx_vec; f_Jet++)
							{
							if((f_BridgeResultC->m_vec_Position_Equals[f_Jet] >= 1) ||
							   (f_BridgeResultC->m_vec_Position_Argument[f_Jet] != -5))
								{
								f_Mark->m_vec_Int[6] += 3;
								
								f_vec_Scanlist.push_back(f_BridgeResultC->m_vec_String_Equal[f_Jet]);
								f_idx_vec_Scanlist++;
								}
							}
						}
					}
				}
			}
		}
		
	for(int f_Helly = 0; f_Helly < g_idx_vec_output_Bridge; f_Helly++)
		{
		std::shared_ptr<classBridge> f_Bridge = g_vec_output_Bridge[f_Helly];
		
		if(f_Bridge->m_vec_Type[0] == INSTA_TYPE_VAR_CALL)
			{
			if(f_Bridge->m_vec_LineType[1] == LINE_TYPE_INPUT &&
			   f_Bridge->m_vec_LineType[2] == LINE_TYPE_INPUT &&
			   f_Bridge->m_vec_LineType[3] == LINE_TYPE_INPUT)
				{
				//Scan, Search Wider
				std::shared_ptr<classBridgeResult> f_BridgeResultA = acScan_Code_Bridges(f_Function, g_vec_scrOutputName[f_Bridge->m_vec_A[0]]);
				
				if(f_BridgeResultA->m_idx_vec == 0)
					{
					f_Mark->m_vec_Int[4] += 15;
					}
				else
					{
					for(int f_Jet = 0; f_Jet < f_BridgeResultA->m_idx_vec; f_Jet++)
						{
						if((f_BridgeResultA->m_vec_Position_Equals[f_Jet] == 0) &&
						   (f_BridgeResultA->m_vec_Position_Argument[f_Jet] == -5))
							{
							f_Mark->m_vec_Int[5] += 3;
							}
						}
					}
					
				for(int f_XY = 0; f_XY < f_idx_vec_Scanlist; f_XY++)
					{
					std::shared_ptr<classBridgeResult> f_BridgeResult = acScan_Code_Bridges(f_Function, f_vec_Scanlist[f_XY]);
				
					if(f_BridgeResultA->m_idx_vec == 0)
						{
						f_Mark->m_vec_Int[4] += 15;
						}
					else
						{
						for(int f_Jet = 0; f_Jet < f_BridgeResultA->m_idx_vec; f_Jet++)
							{
							if((f_BridgeResultA->m_vec_Position_Equals[f_Jet] == 0) &&
							   (f_BridgeResultA->m_vec_Position_Argument[f_Jet] == -5))
								{
								f_Mark->m_vec_Int[5] += 3;
								}
							}
						}
					}
				}
			}
		if(f_Bridge->m_vec_A[1] == -5)
			{
			std::shared_ptr<classBridgeResult> f_ReturnBridgeResult = acScan_Code_Bridges(f_Function, g_vec_scrOutputName[f_Bridge->m_vec_A[0]]);
			
			if(f_ReturnBridgeResult->m_idx_vec == 0)
				{
				f_Mark->m_vec_Int[4] += 15;
				}
			else
				{
				for(int f_forge = 0; f_forge < f_ReturnBridgeResult->m_idx_vec; f_forge++)
					{
					if((f_ReturnBridgeResult->m_vec_Position_Equals[f_forge] == 0) &&
						(f_ReturnBridgeResult->m_vec_Position_Argument [f_forge] == -5))
						{
						f_Mark->m_vec_Int[6] += 5;
						}
					}
				}
			}
		}
		
	//console.log("f_Mark=" + JSON.stringify(f_Mark));

	return f_Mark;
}

void classTarget_JScript::acGatherICO_jscript_base(void)
{
	 //////////////////////////
	//
	g_vec_scrInputName.push_back("firstinput");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("<input type=\"number\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"1\" min=\"1\" max=\"5\">");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	
	g_vec_scrInputName.push_back("wwb_ecnbase_ac_takeMeasurementINTV1");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("Ex");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	
	g_vec_scrInputName.push_back("wwb_ecnbase_acMakeUnison");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("Ex");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_X");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("<input type=\"text\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\">");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Y");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("<input type=\"text\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\">");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Z");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("<input type=\"text\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\">");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrControlName.push_back("Math.cos");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sin");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sqrt");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("if(");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_CONDITIONAL);
	g_idx_vec_scrControlType++;
	
	std::shared_ptr<classBridge> f_ControlBridge1 = std::make_shared<classBridge>();
	
	f_ControlBridge1->ac_add_Path(g_idx_vec_scrControlName - 1, INSTA_TYPE_CONDITIONAL, LINE_TYPE_CONTROL);
	f_ControlBridge1->ac_add_Path(0, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	f_ControlBridge1->ac_add_Path(1, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	
	g_vec_control_Bridge.push_back(f_ControlBridge1);
	g_idx_vec_control_Bridge++;
	
	g_vec_scrOutputName.push_back("f_Result");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	std::shared_ptr<classBridge> f_OutputBridge1 = std::make_shared<classBridge>();
	
	f_OutputBridge1->ac_add_Path(g_idx_vec_scrOutputName - 1, INSTA_TYPE_VAR_CALL, LINE_TYPE_OUTPUT);
	f_OutputBridge1->ac_add_Path(0, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	f_OutputBridge1->ac_add_Path(1, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	f_OutputBridge1->ac_add_Path(-5, INSTA_TYPE_VAR_CALL, LINE_TYPE_NORMAL);
	
	g_vec_output_Bridge.push_back(f_OutputBridge1);
	g_idx_vec_output_Bridge++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_base_output1).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_navbar_output1).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_content1_output1).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_deploy_output1).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_mission_output1).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_mission_output2).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("return ");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
	
	std::shared_ptr<classBridge> f_OutputBridge2 = std::make_shared<classBridge>();
	
	f_OutputBridge2->ac_add_Path(g_idx_vec_scrOutputName - 1, INSTA_TYPE_FUNC_CALL, LINE_TYPE_OUTPUT);
	f_OutputBridge2->ac_add_Path(-5, INSTA_TYPE_VAR_DEF, LINE_TYPE_INPUT);
	
	g_vec_output_Bridge.push_back(f_OutputBridge2);
	g_idx_vec_output_Bridge++;
}

void classTarget_JScript::acGatherICO_html_base(void)
{
	 //////////////////////////
	// 
	g_vec_scrInputName.push_back("ac_takeMeasurementINTV1");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_X");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Y");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Z");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrControlName.push_back("Math.cos");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sin");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sqrt");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("if(");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_CONDITIONAL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrOutputName.push_back("");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("playSound");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
}

void classTarget_JScript::acGatherICO_php_base(void)
{
	 //////////////////////////
	// 
	g_vec_scrInputName.push_back("ac_takeMeasurementINTV1");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_X");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Y");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Z");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrControlName.push_back("Math.cos");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sin");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sqrt");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("if(");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_CONDITIONAL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrOutputName.push_back("$output +=");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("write(");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("playSound");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
}

void classTarget_JScript::acGen_SuperName(std::string f_GeoName)
{
	//m_vec_Name.push_back("wwb_" + f_GeoName);
	//m_idx_vec_Name++;
}

classFactor::classFactor()
{
	m_Use = 0;
}

void classTarget_JScript::acResetFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use = 0;
}

void classTarget_JScript::acDecFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use--;
}

void classTarget_ESL_Script::acDecFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use--;
}

void classTarget_JScript::acResetFactors(int f_Type)
{
	for(int f_XY = 0; f_XY < INSTA_TYPE_COUNT; f_XY++)
		{
		m_Factor[f_XY]->m_Use = 0;
		}
}

void classTarget_JScript::acResetLine(void)
{
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use = 0;
	m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use = 0;
	m_Factor[INSTA_TYPE_DATA]->m_Use = 0;
	m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use = 0;
	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;
}

void classTarget_Ecom::acDecFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use--;
}

void classLMap::acDecFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use--;
}

void classTarget_Ecom::acResetLine(void)
{
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use = 0;
	m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use = 0;
	m_Factor[INSTA_TYPE_DATA]->m_Use = 0;
	m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use = 0;
	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;
}

void classLMap::acResetLine(void)
{
#if 0
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use = 0;
	m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use = 0;
	m_Factor[INSTA_TYPE_DATA]->m_Use = 0;
	m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use = 0;
#endif
}

bool classTarget_JScript::acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, shared_ptr<classElement> f_Element)
{
	int f_Finger = ac_takeMeasurementINTV1(f_Element, 1, f_ProbabilityExt, 0, 3, 3);

	if(f_Finger >= f_AboveLine)
		{
		return f_Answer;
		}
	else
		{
		if(f_Answer == true)
			{
			return false;
			}
		else
			{
			return true;
			}
		}
}

bool classTarget_Ecom::acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	int f_Finger = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1, f_ProbabilityExt, 0, 3);

	if(f_Finger >= f_AboveLine)
		{
		return f_Answer;
		}
	else
		{
		if(f_Answer == true)
			{
			return false;
			}
		else
			{
			return true;
			}
		}
}

void classTarget_ESL_Script::acResetLine(void)
{
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use = 0;
	m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use = 0;
	m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use = 0;
	m_Factor[INSTA_TYPE_VAR_CALL]->m_Use = 0;
	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;
}

bool classTarget_ESL_Script::acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, shared_ptr<classElement> f_Element)
{
	int f_Finger = ac_takeMeasurementINTV1(f_Element, 1, f_ProbabilityExt, 0, 3, 3);

	if(f_Finger >= f_AboveLine)
		{
		return f_Answer;
		}
	else
		{
		if(f_Answer == true)
			{
			return false;
			}
		else
			{
			return true;
			}
		}
}

bool classTarget_ESL_Script::acFactorStrengthVar(int f_Type, std::shared_ptr<classFunction> f_Function, shared_ptr<classElement> f_Element)
{
	return true;
}

bool classLMap::acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	/*int f_Finger = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1, f_ProbabilityExt, 3, 3);

	if(f_Finger >= f_AboveLine)
		{
		return f_Answer;
		}
	else
		{
		if(f_Answer == true)
			{
			return false;
			}
		else
			{
			return true;
			}
		}*/
	throw;
}

bool classTarget_Ecom::acFactorStrengthVar(int f_Type, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	return ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 0);
}

bool classTarget_Ecom::acFactorStrengthVarString(int f_Type, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	return ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 0);
}

bool classLMap::acRecordStrengthVar(int f_Type, std::string f_LineString, float f_RecordResult, int f_ElementID, bool f_isRandom)
{
	switch(f_Type)
		{
		case VAR_DEF_TYPE_ZERO_TO_ONE:
			{
			if(f_isRandom == false)
				{
				if((f_RecordResult >= 0.0) && (f_RecordResult <= 1.0)) //hmmm is this nessassary, experiment
					{
					//###Position###
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_ONE_TO_HUNDRED:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 100.0 && f_RecordResult > 1.0)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 5000.0 && f_RecordResult > 100.0)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 50000000.0 && f_RecordResult > 5000.0)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_RANDOM:
			{
			if(f_isRandom == true)
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case VAR_DEF_TYPE_SYSTEM:
			{
			if(f_isRandom == false)
				{
				std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

				if(f_morf[0][0].at(0) == 'S')
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

#if 0
		case VAR_DEF_TYPE_VARCALL:
			{
			if(f_isRandom == false)
				{
				std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

				if(f_morf[0][0].at(0) == 'S')
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;
#endif
		}

	return false;
}

bool classLMap::acRecordStrengthVar(int f_Type, std::string f_LineString, int f_RecordResult, int f_ElementID, bool f_isRandom)
{
	switch(f_Type)
		{
		case VAR_DEF_TYPE_ZERO_TO_ONE:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 1 && f_RecordResult >= 0)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_ONE_TO_HUNDRED:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 100 && f_RecordResult > 1)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 5000 && f_RecordResult > 100)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 50000000 && f_RecordResult > 5000)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_RANDOM:
			{
			if(f_isRandom == true)
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case VAR_DEF_TYPE_SYSTEM:
			{
			if(f_isRandom == false)
				{
				std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

				if(f_morf[0][0].at(0) == 'S')
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

#if 0
		case VAR_DEF_TYPE_VARCALL:
			{
			if(f_isRandom == false)
				{
				std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

				if(f_morf[0][0].at(0) == 'S')
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;
#endif
		}

	return false;
}

bool classLMap::acRecordStrengthVarString(int f_Type, std::string f_LineString, std::string f_RecordResult, int f_ElementID)
{
	switch(f_Type)
		{
		case VAR_DEF_TYPE_ZERO_TO_ONE:
			{
			if((f_RecordResult.length() == 0) || (f_RecordResult.length() == 1))
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(f_RecordResult);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
#pragma message("WARNING redundant && greater than zero when a negative value should be catered for, please add.")
			}break;

		case VAR_DEF_TYPE_ONE_TO_HUNDRED:
			{
			if((f_RecordResult.length() > (ECOIN_DATA_CHUNK_LENGTH_COUNT * 5)) || (f_RecordResult.length() <= (ECOIN_DATA_CHUNK_LENGTH_COUNT * 6)))
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(f_RecordResult);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND:
			{
			if((f_RecordResult.length() > (ECOIN_DATA_CHUNK_LENGTH_COUNT * 15)) || (f_RecordResult.length() <= (ECOIN_DATA_CHUNK_LENGTH_COUNT * 16)))
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(f_RecordResult);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION:
			{
			if((f_RecordResult.length() > (ECOIN_DATA_CHUNK_LENGTH_COUNT * 20)) || (f_RecordResult.length() <= (ECOIN_DATA_CHUNK_LENGTH_COUNT * 21)))
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(f_RecordResult);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		 case VAR_DEF_TYPE_SYSTEM:
			{
			std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

			if(f_morf[0][0].at(0) == 'S')
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

#if 0
		case VAR_DEF_TYPE_VARCALL:
			{
			if(f_isRandom == false)
				{
				std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

				if(f_morf[0][0].at(0) == 'S')
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;
#endif

		}

	return false;
}

bool classLMap::acRecordStrength(int f_Type, std::string f_LineString, int f_ElementID)
{
	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	switch(f_Type)
		{
		case ESL_INSTA_TYPE_VAR_DEF:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();
			std::string f_Var_First_TypeName = ac_ext_eslLine_morf_array(f_LineString)[0][0];

			if(f_Var_First_TypeName.compare("Var"))
				{
				//generate lense recording
				shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(2, 0, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case ESL_INSTA_TYPE_SYS_DEF:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();
			std::string f_Var_First_TypeName = ac_ext_eslLine_morf_array(f_LineString)[0][0];

			if(f_Var_First_TypeName.compare("Sys") == 0)
				{
				//generate lense recording
				shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(2, 0, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case ESL_INSTA_TYPE_FUNC_DEF:
			{
#if 0
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();
			std::string f_Var_First_TypeName = ac_ext_eslLine_morf_array(f_LineString)[0][0];

			if(f_Var_First_TypeName.compare("Var") == 0)
				{

				}
			else if(f_Var_First_TypeName.compare("Sys") == 0)
				{

				}
			else if(f_Var_First_TypeName.compare("Sys") == 0)
				{

				}
			if((f_Var_Code_Size >= ESL_INSTA_TYPE_FUNC_DEF_MORF_COUNT) && (f_Var_Code_Size >= ESL_INSTA_TYPE_FUNC_DEF_MORF_COUNT +))
				{
				//generate lense recording
				shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(2, 0, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
#else
			return true;
#endif
			}break;

		case ESL_INSTA_TYPE_FUNC_CALL:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

			if(f_Var_Code_Size >= ESL_INSTA_TYPE_FUNC_CALL_MORF_COUNT)
				{
				char f_Var_Second_Char = ac_ext_eslLine_morf_array(f_LineString)[6][1].at(1);

				if(f_Var_Second_Char == '*')
					{
					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(2, 0, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case ESL_INSTA_TYPE_CONDITIONAL:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

			if(f_Var_Code_Size >= ESL_INSTA_TYPE_FUNC_CALL_MORF_COUNT)
				{
				char f_Var_Second_Char = ac_ext_eslLine_morf_array(f_LineString)[6][1].at(1);

				if(f_Var_Second_Char == '^')
					{
					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(2, 0, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case ESL_INSTA_TYPE_LOOP_DEF:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

			if(f_Var_Code_Size == ESL_INSTA_TYPE_LOOP_DEF_MORF_COUNT)
				{
				if((ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("For") == 0) || (ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("for") == 0))
					{
					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(2, 0, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case ESL_INSTA_TYPE_CLASS_DEF:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

			if(f_Var_Code_Size == ESL_INSTA_TYPE_CLASS_DEF_MORF_COUNT)
				{
				if((ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("ClassDef") == 0) || (ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("Class") == 0))
					{
					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(2, 0, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case ESL_INSTA_TYPE_CLASSVAR_DEF:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

			if(f_Var_Code_Size >= ESL_INSTA_TYPE_CLASS_VAR_MORF_COUNT)
				{
				if(ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("ClassVar") == 0)
					{
					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(2, 0, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;
		}

	//generate lense recording
	shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(2, 0, false);

	//save
	m_LMap->m_vec_Measure.push_back(f_Measure);

	//return
	return false;
}

int classLMap::acRecordLine(std::string f_LineString)
{
	int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

	if(f_Var_Code_Size == ESL_INSTA_TYPE_VAR_DEF_MORF_COUNT)
		{
		char f_Var_First_Char = ac_ext_eslLine_morf_array(f_LineString)[0][0].at(0);

		if(f_Var_First_Char == 'V')
			{
			return ESL_INSTA_TYPE_VAR_DEF;
			}
		else if (f_Var_First_Char == 'S')
			{
			return ESL_INSTA_TYPE_SYS_DEF;
			}
		else if (f_Var_First_Char == 'C')
			{
			char f_Var_Position_One_First_Char = ac_ext_eslLine_morf_array(f_LineString)[3][0].at(0);

			if((f_Var_Position_One_First_Char == 'V') || (f_Var_Position_One_First_Char == 'C') || (f_Var_Position_One_First_Char == 'S'))
				{
				return ESL_INSTA_TYPE_CLASSVAR_DEF;
				}

			}
		}
	else if(f_Var_Code_Size == ESL_INSTA_TYPE_FUNC_DEF_MORF_COUNT)
		{
		return ESL_INSTA_TYPE_FUNC_DEF;
		}
	else if(f_Var_Code_Size >= ESL_INSTA_TYPE_FUNC_CALL_MORF_COUNT)
		{
		char f_Var_Second_Char = ac_ext_eslLine_morf_array(f_LineString)[6][1].at(1);

		if(f_Var_Second_Char == '*')
			{
			return ESL_INSTA_TYPE_FUNC_CALL;
			}
		}
	else if(f_Var_Code_Size >= ESL_INSTA_TYPE_FUNC_CALL_MORF_COUNT)
		{
		char f_Var_Second_Char = ac_ext_eslLine_morf_array(f_LineString)[6][1].at(1);

		if(f_Var_Second_Char == '^')
			{
			return ESL_INSTA_TYPE_CONDITIONAL;
			}
		}
	else if(f_Var_Code_Size == ESL_INSTA_TYPE_LOOP_DEF_MORF_COUNT)
		{
		if((ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("For") == 0) || (ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("for") == 0))
			{
			return ESL_INSTA_TYPE_LOOP_DEF;
			}
		}
	else if(ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("Return") == 0)
		{
		return ESL_INSTA_TYPE_RETURN;
		}

	return -1;
}

bool classTarget_JScript::acFactorStrength(int f_Type, std::shared_ptr<classFunction> f_Function, shared_ptr<classElement> f_Element)
{
	m_LastTypeII = m_LastType;
	m_LastTypeIII = m_LastTypeII;
	
	if(f_Type == INSTA_TYPE_VAR_DEF)
		{
		if(m_Factor[INSTA_TYPE_VAR_DEF]->m_Use > 0)
			{
			return false;
			}
		
		if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_VAR_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_DATA]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use > 0)
			{
			return false;
			}
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_VAR_CALL)
		{
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_FUNC_DEF)
		{
		bool f_Found = false;
		for(int f_XY = 0; f_XY < m_idx_vec_Function; f_XY++)
			{
			for(int f_helly = 0; f_helly < m_vec_Function[f_XY]->m_idx_vec_Insta; f_helly++)
				{
				std::shared_ptr<classInsta> f_searchInsta = m_vec_Function[f_XY]->m_vec_Insta[f_helly];
				
				if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
					{
					f_Found = true;
					}
				}
			}
			
		for(int f_helly = 0; f_helly < f_Function->m_idx_vec_Insta; f_helly++)
			{
			std::shared_ptr<classInsta> f_searchInsta = f_Function->m_vec_Insta[f_helly];
			
			if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
				{
				f_Found = true;
				}
			}
		
		if(f_Found == true)
			{
			return false;
			}
		else
			{
			if(acFactorise(true, 4, 5, f_Element) == true)
				{
				m_LastType = f_Type;
				m_Factor[f_Type]->m_Use++;
				return true;
				}
			else
				{
				return false;
				}
			}
		}
	else if(f_Type == INSTA_TYPE_FUNC_CALL)
		{
		if(acFactorise(true, 5, 6, f_Element) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_CONDITIONAL)
		{
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_CALL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
		    return false;
		    }
			
		if(m_LastType != -5)
			{
		    return false;
		    }
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_LOOP_DEF)
		{
		if(m_LastType != -5)
		    {
		    return false;
		    }
			
		if(acFactorise(true, 9, 10, f_Element) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_DATA)
		{
		if(m_LastType == -5)
		    {
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
		
	return true;
}

bool classTarget_ESL_Script::acFactorStrength(int f_Type, std::shared_ptr<classFunction> f_Function, shared_ptr<classElement> f_Element)
{
	m_LastTypeII = m_LastType;
	m_LastTypeIII = m_LastTypeII;
	
	if(f_Type == INSTA_TYPE_VAR_DEF)
		{
		if(m_Factor[INSTA_TYPE_VAR_DEF]->m_Use > 0)
			{
			return false;
			}
		
		if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_VAR_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_DATA]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use > 0)
			{
			return false;
			}
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_VAR_CALL)
		{
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_FUNC_DEF)
		{
		bool f_Found = false;
		for(int f_XY = 0; f_XY < m_idx_vec_Function; f_XY++)
			{
			for(int f_helly = 0; f_helly < m_vec_Function[f_XY]->m_idx_vec_Insta; f_helly++)
				{
				std::shared_ptr<classInsta> f_searchInsta = m_vec_Function[f_XY]->m_vec_Insta[f_helly];
				
				if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
					{
					f_Found = true;
					}
				}
			}
			
		for(int f_helly = 0; f_helly < f_Function->m_idx_vec_Insta; f_helly++)
			{
			std::shared_ptr<classInsta> f_searchInsta = f_Function->m_vec_Insta[f_helly];
			
			if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
				{
				f_Found = true;
				}
			}
		
		if(f_Found == true)
			{
			return false;
			}
		else
			{
			if(acFactorise(true, 4, 5, f_Element) == true)
				{
				m_LastType = f_Type;
				m_Factor[f_Type]->m_Use++;
				return true;
				}
			else
				{
				return false;
				}
			}
		}
	else if(f_Type == INSTA_TYPE_FUNC_CALL)
		{	
		if(acFactorise(true, 5, 6, f_Element) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_CONDITIONAL)
		{
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_CALL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
		    return false;
		    }
			
		if(m_LastType != -5)
			{
		    return false;
		    }
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_LOOP_DEF)
		{
		if(m_LastType != -5)
		    {
		    return false;
		    }
			
		if(acFactorise(true, 9, 10, f_Element) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_DATA)
		{
		if(m_LastType == -5)
		    {
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
		
	return true;
}

bool classTarget_Ecom::acFactorStrength(int f_Type, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
#if 0
	m_LastTypeII = m_LastType;
	m_LastTypeIII = m_LastTypeII;
	
	if(f_Type == INSTA_TYPE_VAR_DEF)
		{
		if(m_Factor[INSTA_TYPE_VAR_DEF]->m_Use > 0)
			{
			return false;
			}
		
		if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_VAR_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_DATA]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use > 0)
			{
			return false;
			}
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_VAR_CALL)
		{
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_FUNC_DEF)
		{
		bool f_Found = false;
		for(int f_XY = 0; f_XY < m_idx_vec_Function; f_XY++)
			{
			/*for(int f_helly = 0; f_helly < m_vec_Function[f_XY]->m_idx_vec_Insta; f_helly++)
				{
				std::shared_ptr<classInsta> f_searchInsta = m_vec_Function[f_XY]->m_vec_Insta[f_helly];
				
				if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
					{
					f_Found = true;
					}
				}*/
			}
			
		for(int f_helly = 0; f_helly < f_Function->m_idx_vec_Insta; f_helly++)
			{
			std::shared_ptr<classInsta> f_searchInsta = f_Function->m_vec_Insta[f_helly];
			
			if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
				{
				f_Found = true;
				}
			}
		
		if(f_Found == true)
			{
			return false;
			}
		else
			{			
			if(acFactorise(true, 4, 5, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
				{
				m_LastType = f_Type;
				m_Factor[f_Type]->m_Use++;
				return true;
				}
			else
				{
				return false;
				}
			}
		}
	else if(f_Type == INSTA_TYPE_FUNC_CALL)
		{	
		if(acFactorise(true, 5, 6, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_CONDITIONAL)
		{
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_CALL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
		    return false;
		    }
			
		if(m_LastType != -5)
			{
		    return false;
		    }
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_LOOP_DEF)
		{
		if(m_LastType != -5)
		    {
		    return false;
		    }
			
		if(acFactorise(true, 9, 10, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_DATA)
		{
		if(m_LastType == -5)
		    {
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
#endif

	return ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 2);
}

bool classTarget_Ecom::acFactorStrengthAff(int f_Type, std::shared_ptr<classFunction> f_Function, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	m_LastTypeII = m_LastType;
	m_LastTypeIII = m_LastTypeII;
	
	if(f_Type == INSTA_TYPE_VAR_DEF)
		{
		if(m_Factor[INSTA_TYPE_VAR_DEF]->m_Use > 0)
			{
			return false;
			}
		
		if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_VAR_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_DATA]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use > 0)
			{
			return false;
			}
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_VAR_CALL)
		{
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_FUNC_DEF)
		{
		bool f_Found = false;
		for(int f_XY = 0; f_XY < m_idx_vec_Function; f_XY++)
			{
			/*for(int f_helly = 0; f_helly < m_vec_Function[f_XY]->m_idx_vec_Insta; f_helly++)
				{
				std::shared_ptr<classInsta> f_searchInsta = m_vec_Function[f_XY]->m_vec_Insta[f_helly];
				
				if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
					{
					f_Found = true;
					}
				}*/
			}
			
		for(int f_helly = 0; f_helly < f_Function->m_idx_vec_Insta; f_helly++)
			{
			std::shared_ptr<classInsta> f_searchInsta = f_Function->m_vec_Insta[f_helly];
			
			if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
				{
				f_Found = true;
				}
			}
		
		if(f_Found == true)
			{
			return false;
			}
		else
			{			
			if(acFactorise(true, 4, 5, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
				{
				m_LastType = f_Type;
				m_Factor[f_Type]->m_Use++;
				return true;
				}
			else
				{
				return false;
				}
			}
		}
	else if(f_Type == INSTA_TYPE_FUNC_CALL)
		{	
		if(acFactorise(true, 5, 6, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_CONDITIONAL)
		{
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_CALL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
		    return false;
		    }
			
		if(m_LastType != -5)
			{
		    return false;
		    }
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_LOOP_DEF)
		{
		if(m_LastType != -5)
		    {
		    return false;
		    }
			
		if(acFactorise(true, 9, 10, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_DATA)
		{
		if(m_LastType == -5)
		    {
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
		
	return true;
}

classCountLock::classCountLock(int f_Count, std::string f_StringC, int f_Type)
{
	m_Count = f_Count;
	m_String = f_StringC;
	m_Factor = f_Type;
}

void classTarget_JScript::acFromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_JScript> f_Target)
{
	for(int f_Count = 0; f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
		{
		std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Hesh->vec_Bicycle[f_Count]);

		m_Collection->m_vec_Element.push_back(f_Element);
		m_Collection->m_idx_vec_Element++;
		}
		
	m_SchemaTop = 0;
	m_SchemaRef[0]->m_X = 0.120;
	m_SchemaRef[0]->m_Y = 0.70;
	m_SchemaRef[0]->m_Z = 0.95;
	m_SchemaRef[1]->m_X = 0.120;
	m_SchemaRef[1]->m_Y = 0.70;
	m_SchemaRef[1]->m_Z = 0.95;
	m_SchemaRef[2]->m_X = 0.120;
	m_SchemaRef[2]->m_Y = 0.70;
	m_SchemaRef[2]->m_Z = 0.95;
	m_SchemaRef[3]->m_X = 0.120;
	m_SchemaRef[3]->m_Y = 0.70;
	m_SchemaRef[3]->m_Z = 0.95;
	m_SchemaRef[4]->m_X = 0.120;
	m_SchemaRef[4]->m_Y = 0.70;
	m_SchemaRef[4]->m_Z = 0.95;
	m_SchemaRef[5]->m_X = 0.120;
	m_SchemaRef[5]->m_Y = 0.70;
	m_SchemaRef[5]->m_Z = 0.95;
	m_SchemaRef[6]->m_X = 0.120;
	m_SchemaRef[6]->m_Y = 0.70;
	m_SchemaRef[6]->m_Z = 0.95;
	m_SchemaRef[7]->m_X = 0.120;
	m_SchemaRef[7]->m_Y = 0.70;
	m_SchemaRef[7]->m_Z = 0.95;
	m_SchemaRef[8]->m_X = 0.120;
	m_SchemaRef[8]->m_Y = 0.70;
	m_SchemaRef[8]->m_Z = 0.95;
	m_SchemaRef[9]->m_X = 0.120;
	m_SchemaRef[9]->m_Y = 0.70;
	m_SchemaRef[9]->m_Z = 0.95;
	m_SchemaRef[10]->m_X = 0.120;
	m_SchemaRef[10]->m_Y = 0.70;
	m_SchemaRef[10]->m_Z = 0.95;
	m_SchemaRef[11]->m_X = 0.120;
	m_SchemaRef[11]->m_Y = 0.70;
	m_SchemaRef[11]->m_Z = 0.95;
	m_SchemaRef[12]->m_X = 0.120;
	m_SchemaRef[12]->m_Y = 0.70;
	m_SchemaRef[12]->m_Z = 0.95;
	m_SchemaRef[13]->m_X = 0.120;
	m_SchemaRef[13]->m_Y = 0.70;
	m_SchemaRef[13]->m_Z = 0.95;
	m_SchemaRef[14]->m_X = 0.120;
	m_SchemaRef[14]->m_Y = 0.70;
	m_SchemaRef[14]->m_Z = 0.95;
	m_SchemaRef[15]->m_X = 0.120;
	m_SchemaRef[15]->m_Y = 0.70;
	m_SchemaRef[15]->m_Z = 0.95;
	m_SchemaRef[16]->m_X = 0.120;
	m_SchemaRef[16]->m_Y = 0.70;
	m_SchemaRef[16]->m_Z = 0.95;
	m_SchemaRef[17]->m_X = 0.120;
	m_SchemaRef[17]->m_Y = 0.70;
	m_SchemaRef[17]->m_Z = 0.95;
	g_SchemaSize = 3;
	
	shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[0];
	
	int f_FunctionCount = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 1);

	for(int f_Jet = 0; f_Jet < f_FunctionCount; f_Jet++)
		{
		m_vec_CountLock.clear();

		int f_FunctionType = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 2);
		int f_ArgumentCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 2, 3, 3);
		int f_InstaCountMap = ac_takeMeasurementINTV1(f_Element, 1, 500, 20, 3, 4);
		m_InstaCountMap = f_InstaCountMap;
		
		std::shared_ptr<classCodeLine> f_vec_CodeLine = std::make_shared<classCodeLine>();
		std::shared_ptr<classFunction> f_Function = std::make_shared<classFunction>();

		f_Function->m_Type = f_FunctionType;
		f_Function->m_Name = ac_takeMeasurement(f_Element);
		
		std::string f_StringA = "function " + f_Function->m_Name + "(";
		std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringA, INSTA_TYPE_FUNC_DEF);

		f_Function->m_vec_Insta.push_back(f_Insta);
		f_Function->m_idx_vec_Insta++;
		
		for(int f_Int = 0; f_Int < f_ArgumentCount; f_Int++)
			{
			if(f_Int > 0)
				{
				f_StringA += ", ";
				}
				
			std::string f_VarNameA = acMakeUnison(f_Target, ac_takeMeasurement(f_Element), 1, INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

			std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_VarNameA, INSTA_TYPE_VAR_CALL);

			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;
			
			f_StringA += f_VarNameA;
			}

		f_Function->m_vec_String += f_StringA;
		f_Function->m_vec_String += ")\n	{\n";
		
		acResetLine();
		
		m_idx_vec_CountLock = 0;
	
		m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_InstaCountMap, "\n}//endfunc " + f_Function->m_Name + "\n", INSTA_TYPE_FUNC_DEF));
		m_idx_vec_CountLock++;

		int f_ElementID = 0;
		
		while(m_InstaCountMap > 0)
			{
			f_Element = m_Collection->m_vec_Element[f_ElementID];
			
			f_ElementID++;
			
			if(f_ElementID >= m_Collection->m_idx_vec_Element)
				{
				f_ElementID = 0;
				}
				
			bool f_Contact = false;
				
			int f_InstaType = ac_takeMeasurementINTV1(f_Element, 0, INSTA_TYPE_COUNT, 2, 3, 6);

			if(f_InstaType == INSTA_TYPE_VAR_DEF)
				{
				if(acFactorStrength(INSTA_TYPE_VAR_DEF, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(f_Element), 1, INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_StringB = "var " + f_Name + " = ";
					std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringB, INSTA_TYPE_VAR_DEF);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;

					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					
					//std::shared_ptr<classInsta> f_InstaCount = ac_takeMeasurementINTV1(f_Element, 1, 4, 3, 3, 6);
					
					//m_vec_CountLock.push_back(std::make_shared<classCountLock(f_InstaCount, ";\n", INSTA_TYPE_VAR_DEF));
					//m_idx_vec_CountLock++;
					f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_VAR_CALL)
				{
				if(acFactorStrength(INSTA_TYPE_VAR_CALL, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					 ///////////////////
					// preleah
					if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}
							
						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 1, 3, 2);
								
							if(f_fingerCount <= 1)
								{
								f_Function->m_vec_String += " == ";
								}
							else if(f_fingerCount == 2)
								{
								f_Function->m_vec_String += " >= ";
								}
							else if(f_fingerCount == 3)
								{
								f_Function->m_vec_String += " <= ";
								}
							else if(f_fingerCount == 4)
								{
								f_Function->m_vec_String += " > ";
								}
							else if(f_fingerCount >= 5)
								{
								f_Function->m_vec_String += " < ";
								}
							}
						else
							{
							if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 1)
								{
								if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
									{
									f_Function->m_vec_String += ", ";
									}

								if(m_LastTypeII == INSTA_TYPE_DATA)
									{
									f_Function->m_vec_String += ", ";
									}
								}
							}
						}
					else if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}

						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else
					    {
						if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
						    {
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
								
								m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
								
								if(f_fingerCount <= 1)
									{
									f_Function->m_vec_String += " = ";
									}
								else if(f_fingerCount == 2)
									{
									f_Function->m_vec_String += " -= ";
									}
								else if(f_fingerCount == 3)
									{
									f_Function->m_vec_String += " *= ";
									}
								else if(f_fingerCount == 4)
									{
									f_Function->m_vec_String += " /= ";
									}
								else if(f_fingerCount >= 5)
									{
									f_Function->m_vec_String += " += ";
									}
								}
							}
						else
							{
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
									{
									int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
									
									m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
									
									if(f_fingerCount <= 1)
										{
										f_Function->m_vec_String += " = ";
										}
									else if(f_fingerCount == 2)
										{
										f_Function->m_vec_String += " -= ";
										}
									else if(f_fingerCount == 3)
										{
										f_Function->m_vec_String += " *= ";
										}
									else if(f_fingerCount == 4)
										{
										f_Function->m_vec_String += " /= ";
										}
									else if(f_fingerCount >= 5)
										{
										f_Function->m_vec_String += " += ";
										}
									}
								else
									{
									int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
									
									if(f_fingerCount <= 1)
										{
										f_Function->m_vec_String += " - ";
										}
									else if(f_fingerCount == 2)
										{
										f_Function->m_vec_String += " * ";
										}
									else if(f_fingerCount == 3)
										{
										f_Function->m_vec_String += " / ";
										}
									else if(f_fingerCount >= 4)
										{
										f_Function->m_vec_String += " + ";
										}
									}
								}
							}
						}
						
					std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(f_Element), 1, INSTA_TYPE_VAR_CALL, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_StringB = f_Name;
					std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringB, INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;

					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_CONDITIONAL)
				{
				if(acFactorStrength(INSTA_TYPE_CONDITIONAL, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					std::string f_StringB = "if(";
					std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringB, INSTA_TYPE_CONDITIONAL);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;

					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					
					int f_InstaCount = 2 + ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 5);
					
					std::vector<int> f_conInstaCount;
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 0, 2, 0, 3, 4));
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 1, 12, 0, 3, 5));
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 2, 25, 4, 3, 6));
					int f_Select = ac_takeMeasurementINTV1(f_Element, 0, 3, 1, 3, 3);
					
					m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_conInstaCount[f_Select], "\n}\n", INSTA_TYPE_CONDITIONAL));
					m_idx_vec_CountLock++;
					
					m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_InstaCount, ")\n	{", INSTA_TYPE_CONDITIONAL));
					m_idx_vec_CountLock++;
					f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_LOOP_DEF)
				{
				if(acFactorStrength(INSTA_TYPE_LOOP_DEF, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(f_Element), 1, INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_forVarName = ac_takeMeasurement(f_Element);
					std::string f_Str = "for(int " + f_forVarName + " = 0; " + f_forVarName + " < " + f_Name + "; " + f_forVarName + "++)\n	{\n 	";
					std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_Str, INSTA_TYPE_LOOP_DEF);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_Str;
					m_InstaCountMap--;
					
					int f_loopInstaCount = ac_takeMeasurementINTV1(f_Element, 8, 105, 8, 3, 1);
					
					m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_loopInstaCount, "\n}\n", INSTA_TYPE_LOOP_DEF));
					m_idx_vec_CountLock++;
					f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_FUNC_CALL)
				{
				if(acFactorStrength(INSTA_TYPE_FUNC_CALL, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					 ///////////////////
					// preleah
					if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}
							
						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							int f_FingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 1, 3, 2);
								
							if(f_FingerCount <= 1)
								{
								f_Function->m_vec_String += " == ";
								}
							else if(f_FingerCount == 2)
								{
								f_Function->m_vec_String += " >= ";
								}
							else if(f_FingerCount == 3)
								{
								f_Function->m_vec_String += " <= ";
								}
							else if(f_FingerCount == 4)
								{
								f_Function->m_vec_String += " > ";
								}
							else if(f_FingerCount >= 5)
								{
								f_Function->m_vec_String += " < ";
								}
							}
						else
							{
							if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 1)
								{
								if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
									{
									f_Function->m_vec_String += ", ";
									}

								if(m_LastTypeII == INSTA_TYPE_DATA)
									{
									f_Function->m_vec_String += ", ";
									}
								}
							}
						}
					else if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 2)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}

						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else
					    {
						if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
						    {
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								int f_FingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
								
								m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
								
								if(f_FingerCount <= 1)
									{
									f_Function->m_vec_String += " = ";
									}
								else if(f_FingerCount == 2)
									{
									f_Function->m_vec_String += " -= ";
									}
								else if(f_FingerCount == 3)
									{
									f_Function->m_vec_String += " *= ";
									}
								else if(f_FingerCount == 4)
									{
									f_Function->m_vec_String += " /= ";
									}
								else if(f_FingerCount >= 5)
									{
									f_Function->m_vec_String += " += ";
									}
								}
							}
						else
							{
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
									{
									int f_FingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
									
									m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
									
									if(f_FingerCount <= 1)
										{
										f_Function->m_vec_String += " = ";
										}
									else if(f_FingerCount == 2)
										{
										f_Function->m_vec_String += " -= ";
										}
									else if(f_FingerCount == 3)
										{
										f_Function->m_vec_String += " *= ";
										}
									else if(f_FingerCount == 4)
										{
										f_Function->m_vec_String += " /= ";
										}
									else if(f_FingerCount >= 5)
										{
										f_Function->m_vec_String += " += ";
										}
									}
								else
									{
									int f_FingerCount = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
									
									if(f_FingerCount <= 1)
										{
										f_Function->m_vec_String += " - ";
										}
									else if(f_FingerCount == 2)
										{
										f_Function->m_vec_String += " * ";
										}
									else if(f_FingerCount == 3)
										{
										f_Function->m_vec_String += " / ";
										}
									else if(f_FingerCount >= 4)
										{
										f_Function->m_vec_String += " + ";
										}
									}
								}
							}
						}
						
					//target restriction point
					std::string f_FunctionName = acMakeUnison(f_Target, ac_takeMeasurement(f_Element), 1, INSTA_TYPE_FUNC_CALL, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_StringB = f_FunctionName + "(";
					
					std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringB, INSTA_TYPE_FUNC_CALL);
							
					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					
					int f_arguInstaCount = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 4);
					
					m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_arguInstaCount, ")", INSTA_TYPE_FUNC_CALL));
					m_idx_vec_CountLock++;
				    f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_DATA)
				{
				if(acFactorStrength(INSTA_TYPE_DATA, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					 ///////////////////
					// preleah
					if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}
							
						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 1, 3, 2);
								
							if(f_fingerCount <= 1)
								{
								f_Function->m_vec_String += " == ";
								}
							else if(f_fingerCount == 2)
								{
								f_Function->m_vec_String += " >= ";
								}
							else if(f_fingerCount == 3)
								{
								f_Function->m_vec_String += " <= ";
								}
							else if(f_fingerCount == 4)
								{
								f_Function->m_vec_String += " > ";
								}
							else if(f_fingerCount >= 5)
								{
								f_Function->m_vec_String += " < ";
								}
							}
						else
							{
							if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 1)
								{
								if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
									{
									f_Function->m_vec_String += ", ";
									}

								if(m_LastTypeII == INSTA_TYPE_DATA)
									{
									f_Function->m_vec_String += ", ";
									}
								}
							}
						}
					else if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}

						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else
					    {
						if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
						    {
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
								
								m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
								
								if(f_fingerCount <= 1)
									{
									f_Function->m_vec_String += " = ";
									}
								else if(f_fingerCount == 2)
									{
									f_Function->m_vec_String += " -= ";
									}
								else if(f_fingerCount == 3)
									{
									f_Function->m_vec_String += " *= ";
									}
								else if(f_fingerCount == 4)
									{
									f_Function->m_vec_String += " /= ";
									}
								else if(f_fingerCount >= 5)
									{
									f_Function->m_vec_String += " += ";
									}
								}
							}
						else
							{
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
									{
									int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
									
									m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
									
									if(f_fingerCount <= 1)
										{
										f_Function->m_vec_String += " = ";
										}
									else if(f_fingerCount == 2)
										{
										f_Function->m_vec_String += " -= ";
										}
									else if(f_fingerCount == 3)
										{
										f_Function->m_vec_String += " *= ";
										}
									else if(f_fingerCount == 4)
										{
										f_Function->m_vec_String += " /= ";
										}
									else if(f_fingerCount >= 5)
										{
										f_Function->m_vec_String += " += ";
										}
									}
								else
									{
									int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
									
									if(f_fingerCount <= 1)
										{
										f_Function->m_vec_String += " - ";
										}
									else if(f_fingerCount == 2)
										{
										f_Function->m_vec_String += " * ";
										}
									else if(f_fingerCount == 3)
										{
										f_Function->m_vec_String += " / ";
										}
									else if(f_fingerCount >= 4)
										{
										f_Function->m_vec_String += " + ";
										}
									}
								}
							}
						}

					//target restriction point
					std::string f_StringB = "";
					int f_Scale = 32;
					int f_VarType = ac_takeMeasurementINTV1(f_Element, 0, 3, 4, 3, 1);
					int f_VarSize = ac_takeMeasurementINTV1(f_Element, 1, f_Scale, 7, 3, 0);
					
					if(f_VarType == VAR_TYPE_INT)
						{
						f_StringB += ac_takeMeasurementINTV1(f_Element, 1, 10, 2, 3, 7) * f_VarSize;
						}
					else if(f_VarType >= VAR_TYPE_FLT)
						{
						f_StringB += (float)(ac_takeMeasurementINTV1(f_Element, 1, 10, 2, 3, 7)) * (float)(f_VarSize);
						}
					/*else if(f_VarType == VAR_TYPE_HEX)
						{
						for(int f_Flx = 0; f_Flx < f_VarSize; f_Flx++)
							{
							f_StringB += ac_takeMeasurement(f_Element);
							}
						}
					else if(f_VarType == VAR_TYPE_BIN)
						{
						for(int f_Flx = 0; f_Flx < f_VarSize; f_Flx++)
							{
							f_StringB += ac_takeMeasurement(f_Element);
							}
						}*/
					
					std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringB, INSTA_TYPE_DATA);
							
					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_FUNC_DEF)
				{
				/*if(acFactorStrength(INSTA_TYPE_FUNC_DEF, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta(f_StringB, INSTA_TYPE_FUNC_DEF);
							
					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					}*/
				}
				
			  ///////////////////
			 //
			// Count Map
			if(f_Contact == true)
				{
				f_vec_CodeLine->m_vec_Code.push_back(f_Function->m_vec_Insta[f_Function->m_idx_vec_Insta - 1]);
				f_vec_CodeLine->m_idx_vec_Code++;
					
#if 0
				if(m_idx_vec_CountLock > 0)
					{
					for(int f_cv = m_idx_vec_CountLock - 1; f_cv >= 0; f_cv--)
					     {
					     int f_Caramel = f_cv;

					     m_vec_CountLock[f_Caramel]->m_Count--;
					
					     if(m_vec_CountLock[f_Caramel]->m_Count <= 0)
							{
							bool f_on = true;

							if(f_Caramel < (m_idx_vec_CountLock - 1))
								{
								f_on = false;
								}
								
							if(f_on == true)
								{
								std::shared_ptr<classCountLock> f_Lock = m_vec_CountLock[f_Caramel];

								f_Function->m_vec_String += f_Lock->m_String;

								if(f_Lock->m_String.compare("\n") != 0)
									{
									acResetLine();
									f_Function->m_vec_CodeLineStorage.push_back(f_vec_CodeLine);
									f_Function->m_idx_vec_CodeLineStorage++;

									f_vec_CodeLine->m_vec_Code.clear();
									f_vec_CodeLine->m_idx_vec_Code = 0;
									}

								acDecFactor(f_Lock->m_Factor);

								m_idx_vec_CountLock--;
								
								for(int f_XY = f_Caramel; f_XY < m_idx_vec_CountLock; f_XY++)
									{
									m_vec_CountLock[f_XY] = m_vec_CountLock[f_XY + 1];
									}
								
								if(f_Lock->m_String.compare(")") == 0)
									{
									bool f_ont = true;
									
									for(int f_cv1 = 1; f_cv1 < m_idx_vec_CountLock; f_cv1++)
										{
										for(int f_cv3 = 0; f_cv3 < m_vec_CountLock[f_cv1]->m_String.length(); f_cv3++)
											{
											if(m_vec_CountLock[f_cv1]->m_String.at(f_cv3) == ')')
												{
												f_ont = false;
												}
											}
										}
										
									if(f_ont == true)
										{
										acResetLine();
										f_Function->m_vec_CodeLineStorage.push_back(f_vec_CodeLine);
										f_Function->m_idx_vec_CodeLineStorage++;
										f_Function->m_vec_String += ";\n";

										f_vec_CodeLine->m_vec_Code.clear();
										f_vec_CodeLine->m_idx_vec_Code = 0;
										}
									}

								m_vec_CountLock.pop_back();
								}
							else
								{
								m_vec_CountLock[f_Caramel]->m_Count = 1;
								}
							}
						}
					}
#endif
				}
			}

		m_String += f_Function->m_vec_String;

		m_vec_Function.push_back(f_Function);
		m_idx_vec_Function++;
		}
}

std::string classTarget_Ecom::acGen_genline_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_Line[5];
	int f_LineLength = 4;

	f_Line[0] = "Insert ";
	f_Line[1] = "SysVar ";
	f_Line[2] = "PosX ";
	f_Line[3] = "//System Position Variable";

	std::string f_LinePR;
	f_LinePR.clear();

	for(int f_Helly = 0; f_Helly < f_LineLength; f_Helly++)
		{
		f_LinePR += f_Line[f_Helly];
		}

	return f_LinePR;
}

std::string classLMap::acGen_genline_FromEcom(std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_Line[5];
	int f_LineLength = 4;

	f_Line[0] = "Insert ";
	f_Line[1] = "SysVar ";
	f_Line[2] = "PosX ";
	f_Line[3] = "//System Position Variable";

	std::string f_LinePR;
	f_LinePR.clear();

	//int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	for(int f_Helly = 0; f_Helly < f_LineLength; f_Helly++)
		{
		f_LinePR += f_Line[f_Helly];
		}

	return f_LinePR;
}

int classTarget_Ecom::ac_printMeasurementINTS(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_RangeWidth, int f_WeightRangetoStart)
{
	std::string f_Result = "";
	int f_Finishing = 0;

	for(int f_XY = 0; f_XY < f_RangeWidth; f_XY++)
		{
#pragma message("Consider weighting booleans false or inverse negative weight lift true")
		if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
			{
			if(f_Finishing > 0)
				{
				f_Result.push_back('0');
				f_Finishing = 0;
				}

			char f_Char[150];
			FillChar(f_Char, 150);

			::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 10, 0, 0));
			}
		else
			{
			f_Finishing++;
			}
		}

	return atoi(f_Result.c_str());
}

int classLMap::ac_recordMeasurementINTS(int f_RangeWidth, int f_WeightRangetoStart, int f_RecordResult, int f_ElementID)
{
	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	//generate lense recording
	shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(f_RangeWidth, f_WeightRangetoStart, f_RecordResult);

	//save
	m_LMap->m_vec_Measure.push_back(f_Measure);

	//return
	return f_RecordResult;
}

std::shared_ptr<Qcom_genScript> classTarget_Ecom::acGen_gen_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::shared_ptr<Qcom_genScript> f_gen = std::make_shared<Qcom_genScript>();

	std::string f_VarNameA = ac_takeMeasurement(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	f_gen->m_birthcomid = -1;

	f_gen->m_ID = -5;

	f_gen->m_name = f_VarNameA;

	f_gen->m_owner = g_Wallet->m_vec_Key[0]->m_owner;

	f_gen->m_description = "";

	f_gen->m_Save = true;

	  ////////////////////////////
	 //
	// Generation Script Gen
	int f_LinesCount = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, ECOM_GEN_LINES_MIN, ECOM_GEN_LINES_MAX, ECOM_GEN_LINES_WEIGHT, 3);

	//Insert Change Element restriction or other share entirely at this point
	for(int f_XY = 0; f_XY < f_LinesCount; f_XY++)
		{
		f_gen->m_vec_InitLine.push_back(acGen_genline_FromHesh(f_Hesh, (f_Hesh->vec_Bicycle.size() / f_LinesCount) * f_XY, (f_Hesh->vec_Bicycle.size() / f_LinesCount) * (f_XY + 1), f_ElementMax, f_Depth, f_Target));
		}

	return f_gen;
}

std::shared_ptr<Qcom_genScript> classLMap::acGen_gen_FromEcom(std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::shared_ptr<Qcom_genScript> f_gen = std::make_shared<Qcom_genScript>();

	int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	std::string f_VarNameA = ac_recordMeasurement(f_Save_Com->m_genScript->m_name, f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	f_gen->m_birthcomid = -1;

	f_gen->m_ID = -5;

	f_gen->m_name = f_VarNameA;

	f_gen->m_owner = g_Wallet->m_vec_Key[0]->m_owner;

	f_gen->m_description = "";

	f_gen->m_Save = true;

	  ////////////////////////////
	 //
	// Generation Script Gen
	f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	int f_LinesCount = ac_recordMeasurementINTV1(ECOM_GEN_LINES_MIN, ECOM_GEN_LINES_MAX, ECOM_GEN_LINES_WEIGHT, 3, 1, f_Save_Com->m_genScript->m_vec_InitLineOrdered.size(), f_ElementIndex);

	//Insert Change Element restriction or other share entirely at this point
	for(int f_XY = 0; f_XY < f_LinesCount; f_XY++)
		{
		f_gen->m_vec_InitLine.push_back(acGen_genline_FromEcom(f_Save_Com, (f_ElementMax / f_LinesCount) * f_XY, (f_ElementMax / f_LinesCount) * (f_XY + 1), f_ElementMax, f_Depth, f_Target));
		}

	return f_gen;
}

std::shared_ptr<Qcom> classTarget_Ecom::acGen_com_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	while(m_Collection->m_vec_Element.size() < f_Hesh->m_adIndex.size())
		{
		std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Hesh->vec_Bicycle[m_Collection->m_idx_vec_Element]);

		m_Collection->m_vec_Element.push_back(f_Element);
		m_Collection->m_idx_vec_Element++;
		}

	if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1) || (true))
		{
		std::shared_ptr<Qcom> f_com = std::make_shared<Qcom>();

		std::string f_VarNameA = ac_takeMeasurement(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_com->m_birthcomid = -1;

		f_com->m_BossLVLMin = g_BossLVLMin;

		f_com->m_Cost = 1.0f;

		f_com->m_ID = -5;

		f_com->m_name = f_VarNameA;

		f_com->m_owner = g_Wallet->m_vec_Key[0]->m_owner;

		f_com->m_description = "";

		f_com->m_parentcomid = -5;

		f_com->m_rebuild = true;

		f_com->m_Save = true;

		f_com->m_VoteScore = 0;

		  ////////////////////////////
		 //
		// Generation Script Gen
		f_com->m_genScript = acGen_gen_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);
		g_QcomManager->m_vec_GenScript.push_back(f_com->m_genScript);

		//Insert Change Element restriction or other share entirely at this point
		if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1))
			{
			std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

			f_com->m_Frame_ESLFunction = f_Function;
			g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
			}

#if 0
		int f_FunctionCount = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 0, ECOM_FUNCTION_GEN_MAX, 0, 3);

		for(int f_XY = 0; f_XY < f_FunctionCount; f_XY++)
			{
			std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

			f_com->m_vec_Function.push_back(f_Function);
			g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
			}
#endif

		int f_InputCount = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, ECOM_ICO_MIN, ECOM_ICO_MAX, ECOM_ICO_WEIGHT, 3);
		
		for(int f_Helly = 0; f_Helly < f_InputCount; f_Helly++)
			{ //dive in levels of element selection range
			std::shared_ptr<QcomInput> f_COM_Input = acGen_com_input_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target, f_WireContractOverride);

			if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1))
				{
				std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

				f_COM_Input->m_InputFunction = f_Function;
				g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
				}

			f_com->m_vec_Input.push_back(f_COM_Input);
			g_QcomManager->m_vec_Input.push_back(f_COM_Input);
			}

		int f_OutputCount = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, ECOM_ICO_MIN, ECOM_ICO_MAX, ECOM_ICO_WEIGHT, 3);

		for(int f_Helly = 0; f_Helly < f_OutputCount; f_Helly++)
			{ //dive in levels of element selection range
			std::shared_ptr<QcomOutput> f_COM_Output = acGen_com_output_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target, f_WireContractOverride);

			if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1))
				{
				std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

				f_COM_Output->m_OutputFunction = f_Function;
				g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
				}

			f_com->m_vec_Output.push_back(f_COM_Output);
			g_QcomManager->m_vec_Output.push_back(f_COM_Output);
			}

		//f_com->acWire(f_Hesh, 0, f_Hesh->vec_Bicycle.size());

		int f_EcomCount = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, ECOM_COM_GEN_MIN, ECOM_COM_GEN_MAX, ECOM_COM_GEN_WEIGHT, 3);

		//Insert Change Element restriction or other share entirely at this point
		for(int f_XY = 0; f_XY < f_EcomCount; f_XY++)
			{
			std::shared_ptr<Qcom> f_com_B = acGen_com_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

			f_com->m_vec_Qcom.push_back(f_com_B);
			g_QcomManager->m_vec_Qcom.push_back(f_com_B);
			}

		return f_com;
		}
	else //comid structure build
		{
		//obtain qcom db index
		int f_ComID = ac_printMeasurementINTS(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 5, 0);

		if((m_GlobalScope == true) && (f_ComID > 0)) //global built from share and ids
			{
			std::shared_ptr<Qcom> f_com = std::make_shared<Qcom>(f_ComID);
			//add bosslvl check to Qcom load

			return f_com;
			}
#if 0
		else
			{
			std::shared_ptr<Qcom> f_com = std::make_shared<Qcom>();

			std::string f_VarNameA = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_DEF, f_Element, 1, 1);

			f_com->m_ID = f_ComID;

			return f_com;
			}
#endif
		}

	std::shared_ptr<Qcom> f_com = std::make_shared<Qcom>();
	//appeasement return
	return f_com;
}

std::shared_ptr<QcomInput> classTarget_Ecom::acGen_com_input_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::shared_ptr<QcomInput> f_comInput = std::make_shared<QcomInput>();

	std::string f_VarNameA = ac_takeMeasurement(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	f_comInput->m_birthcomid = -1;

	f_comInput->m_ID = -5;

	f_comInput->m_name = f_VarNameA;

	f_comInput->m_owner = g_Wallet->m_vec_Key[0]->m_owner;

	f_comInput->m_description = "";

	f_comInput->m_rebuild = true;

	f_comInput->m_Save = true;

	return f_comInput;
}

std::shared_ptr<QcomOutput> classTarget_Ecom::acGen_com_output_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::shared_ptr<QcomOutput> f_comOutput = std::make_shared<QcomOutput>();

	std::string f_VarNameA = ac_takeMeasurement(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	f_comOutput->m_birthcomid = -1;

	f_comOutput->m_ID = -5;

	f_comOutput->m_name = f_VarNameA;

	f_comOutput->m_owner = g_Wallet->m_vec_Key[0]->m_owner;

	f_comOutput->m_description = "";

	f_comOutput->m_rebuild = true;

	f_comOutput->m_Save = true;

	return f_comOutput;
}

void classTarget_Ecom::acFromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	for(int f_Count = 0; f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
		{
		std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Hesh->vec_Bicycle[f_Count]);

		m_Collection->m_vec_Element.push_back(f_Element);
		m_Collection->m_idx_vec_Element++;
		}

	int f_StartAD = 0;
	int f_EndAD = m_Collection->m_vec_Element.size();
	int f_ElementMax = m_Collection->m_vec_Element.size();
	int f_Depth = 1;
		
	m_SchemaTop = 0;
	m_SchemaRef[0]->m_X = 0.120;
	m_SchemaRef[0]->m_Y = 0.70;
	m_SchemaRef[0]->m_Z = 0.95;
	m_SchemaRef[1]->m_X = 0.120;
	m_SchemaRef[1]->m_Y = 0.70;
	m_SchemaRef[1]->m_Z = 0.95;
	m_SchemaRef[2]->m_X = 0.120;
	m_SchemaRef[2]->m_Y = 0.70;
	m_SchemaRef[2]->m_Z = 0.95;
	m_SchemaRef[3]->m_X = 0.120;
	m_SchemaRef[3]->m_Y = 0.70;
	m_SchemaRef[3]->m_Z = 0.95;
	m_SchemaRef[4]->m_X = 0.120;
	m_SchemaRef[4]->m_Y = 0.70;
	m_SchemaRef[4]->m_Z = 0.95;
	m_SchemaRef[5]->m_X = 0.120;
	m_SchemaRef[5]->m_Y = 0.70;
	m_SchemaRef[5]->m_Z = 0.95;
	m_SchemaRef[6]->m_X = 0.120;
	m_SchemaRef[6]->m_Y = 0.70;
	m_SchemaRef[6]->m_Z = 0.95;
	m_SchemaRef[7]->m_X = 0.120;
	m_SchemaRef[7]->m_Y = 0.70;
	m_SchemaRef[7]->m_Z = 0.95;
	m_SchemaRef[8]->m_X = 0.120;
	m_SchemaRef[8]->m_Y = 0.70;
	m_SchemaRef[8]->m_Z = 0.95;
	m_SchemaRef[9]->m_X = 0.120;
	m_SchemaRef[9]->m_Y = 0.70;
	m_SchemaRef[9]->m_Z = 0.95;
	m_SchemaRef[10]->m_X = 0.120;
	m_SchemaRef[10]->m_Y = 0.70;
	m_SchemaRef[10]->m_Z = 0.95;
	m_SchemaRef[11]->m_X = 0.120;
	m_SchemaRef[11]->m_Y = 0.70;
	m_SchemaRef[11]->m_Z = 0.95;
	m_SchemaRef[12]->m_X = 0.120;
	m_SchemaRef[12]->m_Y = 0.70;
	m_SchemaRef[12]->m_Z = 0.95;
	m_SchemaRef[13]->m_X = 0.120;
	m_SchemaRef[13]->m_Y = 0.70;
	m_SchemaRef[13]->m_Z = 0.95;
	m_SchemaRef[14]->m_X = 0.120;
	m_SchemaRef[14]->m_Y = 0.70;
	m_SchemaRef[14]->m_Z = 0.95;
	m_SchemaRef[15]->m_X = 0.120;
	m_SchemaRef[15]->m_Y = 0.70;
	m_SchemaRef[15]->m_Z = 0.95;
	m_SchemaRef[16]->m_X = 0.120;
	m_SchemaRef[16]->m_Y = 0.70;
	m_SchemaRef[16]->m_Z = 0.95;
	m_SchemaRef[17]->m_X = 0.120;
	m_SchemaRef[17]->m_Y = 0.70;
	m_SchemaRef[17]->m_Z = 0.95;
	g_SchemaSize = 3;
	
	int f_EcomCount = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1, 3, 0, 3);

	int f_WireContract = -5;

	if(f_WireContractOverride >= 0)
		{
		f_WireContract = f_WireContractOverride;
		}
	else
		{
#if 0
		f_WireContract = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 1);
#endif
		}

	for(int f_Jet = 0; f_Jet < f_EcomCount; f_Jet++)
		{
		std::shared_ptr<Qcom> f_com = acGen_com_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target, f_WireContractOverride);

		//first push to target
		m_vec_Ecom.push_back(f_com);

#ifdef ECOIN_QCOM_UPDATE_FROM_HESH
		//next push to manager mega list
		g_QcomManager->m_vec_Qcom.push_back(f_com);

		//finally conditionally update current board, pending perhaps
		g_QcomManager->m_Qcom->m_vec_Qcom.push_back(f_com);
#endif
		}
}

int classLMap::acPull_gen_ElementID(int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, int f_OCSCP_ThreadIndex)
{
	return ag_Pull_gen_Element(f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_OCSCP_ThreadIndex);
}

void classLMap::acRangeAD(void)
{
	int f_CountElement = 0;
	int f_CountFinger = 0;
	
	for(int f_Jet = 0; f_Jet < m_LMap->m_vec_Measure.size(); f_Jet++)
		{
		f_CountFinger++;

		if(f_CountFinger > g_CountLM)
			{
			f_CountFinger -= g_CountLM;

			f_CountElement++;
			}
		}

	m_ADHIGH = f_CountElement;
	m_ADLOW = f_CountElement;
	m_ADMAX = m_ADHIGH;

	if(f_CountElement > 50)
		{
		g_ADMAX = m_ADHIGH;
		}
}

std::shared_ptr<Qcom> classLMap::acGen_com_FromEcom(std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	if(ac_recordMeasurementBLTV1(1, 1, true /*(f_Save_Com->m_ID > 0) ? true : false*/, f_ElementIndex))
		{
		std::shared_ptr<Qcom> f_com = std::make_shared<Qcom>();

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		std::string f_VarNameA = ac_recordMeasurement(f_Save_Com->m_name, f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_com->m_birthcomid = -1;

		f_com->m_BossLVLMin = g_BossLVLMin;

		f_com->m_Cost = 1.0f;

		f_com->m_ID = -5;

		f_com->m_name = f_VarNameA;

		f_com->m_owner = g_Wallet->m_vec_Key[0]->m_owner;

		f_com->m_description = "";

		f_com->m_parentcomid = -5;

		f_com->m_rebuild = true;

		f_com->m_Save = true;

		f_com->m_VoteScore = 0;

		  ////////////////////////////
		 //
		// Generation Script Gen
		f_com->m_genScript = acGen_gen_FromEcom(f_Save_Com, 0, f_ElementMax, f_ElementMax, f_Depth, f_Target);
		g_QcomManager->m_vec_GenScript.push_back(f_com->m_genScript);

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		if(ac_recordMeasurementBLTV1(1, 1, (f_Save_Com->m_Frame_ESLFunction != nullptr) ? true : false, f_ElementIndex))
			{
			std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromEcom(f_Save_Com->m_Frame_ESLFunction, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

			f_com->m_Frame_ESLFunction = f_Function;
			g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
			}

#if 0
		int f_FunctionCount = ac_recordMeasurementINTV1(0, ECOM_FUNCTION_GEN_MAX, 0, 3, 1, f_Save_Com->m_vec_Function.size(), f_ElementIndex);

		//Insert Change Element restriction or other share entirely at this point
		for(int f_XY = 0; f_XY < f_FunctionCount; f_XY++)
			{
			std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromEcom(f_Save_Com->m_vec_Function[f_XY], f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);
			
			f_com->m_vec_Function.push_back(f_Function);
			g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
			}
#endif

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_InputCount = ac_recordMeasurementINTV1(ECOM_ICO_MIN, ECOM_ICO_MAX, ECOM_ICO_WEIGHT, 3, 3, f_Save_Com->m_vec_Input.size(), f_ElementIndex);
		
		for(int f_Helly = 0; f_Helly < f_InputCount; f_Helly++)
			{ //dive in levels of element selection range
			std::shared_ptr<QcomInput> f_COM_Input = acGen_com_input_FromEcom(f_Save_Com->m_vec_Input[f_Helly], f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target, f_WireContractOverride);

			if(ac_recordMeasurementBLTV1(1, 1, (f_Save_Com->m_vec_Input[f_Helly]->m_InputFunction != nullptr) ? true : false, f_ElementIndex))
				{
				std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromEcom(f_Save_Com->m_vec_Input[f_Helly]->m_InputFunction, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

				f_COM_Input->m_InputFunction = f_Function;
				g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
				}

			f_com->m_vec_Input.push_back(f_COM_Input);
			g_QcomManager->m_vec_Input.push_back(f_COM_Input);
			}

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_OutputCount = ac_recordMeasurementINTV1(ECOM_ICO_MIN, ECOM_ICO_MAX, ECOM_ICO_WEIGHT, 3, 3, f_Save_Com->m_vec_Output.size(), f_ElementIndex);

		for(int f_Helly = 0; f_Helly < f_OutputCount; f_Helly++)
			{ //dive in levels of element selection range
			std::shared_ptr<QcomOutput> f_COM_Output = acGen_com_output_FromEcom(f_Save_Com->m_vec_Output[f_Helly], f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target, f_WireContractOverride);

			if(ac_recordMeasurementBLTV1(1, 1, (f_Save_Com->m_vec_Output[f_Helly]->m_OutputFunction != nullptr) ? true : false, f_ElementIndex))
				{
				std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromEcom(f_Save_Com->m_vec_Output[f_Helly]->m_OutputFunction, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

				f_COM_Output->m_OutputFunction = f_Function;
				g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
				}

			f_com->m_vec_Output.push_back(f_COM_Output);
			g_QcomManager->m_vec_Output.push_back(f_COM_Output);
			}

		//f_com->acWire(f_Hesh, 0, f_ElementMax);

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_EcomCount = ac_recordMeasurementINTV1(ECOM_COM_GEN_MIN, ECOM_COM_GEN_MAX, ECOM_COM_GEN_WEIGHT, 3, 1, f_Save_Com->m_vec_Qcom.size(), f_ElementIndex);

		//Insert Change Element restriction or other share entirely at this point
		for(int f_XY = 0; f_XY < f_EcomCount; f_XY++)
			{
			std::shared_ptr<Qcom> f_Add_Com = acGen_com_FromEcom(f_Save_Com->m_vec_Qcom[f_XY], f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

			f_com->m_vec_Qcom.push_back(f_Add_Com);
			g_QcomManager->m_vec_Qcom.push_back(f_Add_Com);
			}

		return f_com;
		}
	else //comid structure build
		{
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		//obtain qcom db index
		int f_ComID = ac_recordMeasurementINTS(5, 0, f_Save_Com->m_ID, f_ElementIndex);

		if((m_GlobalScope == true) && (f_ComID > 0)) //global built from share and ids
			{
			std::shared_ptr<Qcom> f_com = std::make_shared<Qcom>(f_ComID);
			//add bosslvl check to Qcom load

			return f_com;
			}
		}

	std::shared_ptr<Qcom> f_com = std::make_shared<Qcom>();
	//appeasement return

	return f_com;
}

std::shared_ptr<QcomInput> classLMap::acGen_com_input_FromEcom(std::shared_ptr<QcomInput> f_Save_Input, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::shared_ptr<QcomInput> f_comInput = std::make_shared<QcomInput>();

	int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	std::string f_VarNameA = ac_recordMeasurement(f_Save_Input->m_name, f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	f_comInput->m_birthcomid = -1;

	f_comInput->m_ID = -5;

	f_comInput->m_name = f_VarNameA;

	f_comInput->m_owner = g_Wallet->m_vec_Key[0]->m_owner;

	f_comInput->m_description = "";

	f_comInput->m_rebuild = true;

	f_comInput->m_Save = true;

	return f_comInput;
}

std::shared_ptr<QcomOutput> classLMap::acGen_com_output_FromEcom(std::shared_ptr<QcomOutput> f_Save_Output, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::shared_ptr<QcomOutput> f_comOutput = std::make_shared<QcomOutput>();

	int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	std::string f_VarNameA = ac_recordMeasurement(f_Save_Output->m_name, f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	f_comOutput->m_birthcomid = -1;

	f_comOutput->m_ID = -5;

	f_comOutput->m_name = f_VarNameA;

	f_comOutput->m_owner = g_Wallet->m_vec_Key[0]->m_owner;

	f_comOutput->m_description = "";

	f_comOutput->m_rebuild = true;

	f_comOutput->m_Save = true;

	return f_comOutput;
}

std::string classTarget_Ecom::ac_ext_Make_VarType(int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 3) == true)
		{
		return "float&&";
		}
	else if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 3) == true)
		{
		return "int&&";
		}
	
	return "String&&";
}

std::string classLMap::ac_ext_Make_VarType(std::string f_LineString, int f_VertexID)
{
	
	
	return "String&&";
}

std::shared_ptr<Qcom_eslfunction> classTarget_Ecom::acGen_com_function_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target)
{
	if(m_Collection->m_vec_Element.size() < f_Hesh->m_adIndex.size())
		{
		for(int f_Count = m_Collection->m_vec_Element.size(); f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
			{
			std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Hesh->vec_Bicycle[f_Count]);

			m_Collection->m_vec_Element.push_back(f_Element);
			m_Collection->m_idx_vec_Element++;
			}
		}

	int f_FunctionType = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 3, 0, 3);

	int f_ArgumentCount = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 2, 0, 3);

	int f_LineCount = 0;

	std::shared_ptr<classFunction> f_Function = std::make_shared<classFunction>();

	f_Function->m_Type = f_FunctionType;
	f_Function->m_Name = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	std::string f_StringA = "FuncDef%%" + f_Function->m_Name + "&*ECNMiner_Affinity%%////";
	f_StringA += ESL_LINE_ENDING;

	std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringA, ESL_INSTA_TYPE_FUNC_DEF);

	f_Function->m_vec_Insta.push_back(f_Insta);
	f_Function->m_idx_vec_Insta++;

	for(int f_Int = 0; f_Int < f_ArgumentCount; f_Int++)
		{
		std::string f_ArgParam = acGen_Var_fromHesh();
		}

	f_Function->m_vec_String += f_StringA;
		
	acResetLine();

	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	int f_ElementID = 0;

	bool f_Scan = true;
	while(f_Scan == true)// || ((f_LineIndexCount > 0) && (m_vec_CountLock.size() > 0)))
		{
		bool f_Contact = false;
				
		int f_InstaType = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, ESL_INSTA_TYPE_COUNT, 2, 3);

		if(f_InstaType == ESL_INSTA_TYPE_VAR_DEF)
			{
			if(1)//acFactorStrength(ESL_INSTA_TYPE_VAR_DEF, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
				{
				std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

				char f_Char[5000];
				FillChar(f_Char, 5000);

				std::string f_StringB;
				f_StringB.clear();

				if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2) == true)
					{
					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0.0f, 1.0f, 0.0f, 2));

						f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1.0f, 100.0f, 0.0f, 2));

						f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2));

						f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2));

						f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "Random");

						f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else
						{
#if 0
						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							std::string f_StringC = "Var%%float&&" + f_Name + "%%0.0&%////" + ESL_LINE_ENDING;

							std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringC, ESL_INSTA_TYPE_VAR_DEF);

							f_Function->m_vec_Insta.push_back(f_Insta);
							f_Function->m_idx_vec_Insta++;

							f_Function->m_vec_String += f_StringC;
							f_LineCount++;
							}
#endif

						std::string f_VarCallName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						std::string f_VarNameFA = acMakeUnisonType(f_Target, f_VarCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, MuVar_Float, true);

						std::string f_VarVarSys = "";
						std::string f_VarType = "";
						std::string f_VarName = "";

						int f_Stage = 0;

						for(int f_Helly = 0; f_Helly < f_VarNameFA.length(); f_Helly++)
							{
							char f_c = f_VarNameFA.at(f_Helly);

							if(f_c == '&' || f_c == '%')
								{
								f_Stage++;
								}
							else
								{
								if(f_Stage == 0)
									{
									f_VarVarSys.push_back(f_c);
									}
								else if(f_Stage >= 2)
									{
									f_VarType.push_back(f_c);
									}
								else
									{
									f_VarName.push_back(f_c);
									}
								}
							}

						char f_1 = f_VarVarSys.at(0);

						float f_condAssignValurRHS = 0.0f;

						if(f_VarName.compare(f_VarCallName) == 0)
							{
							if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0.0f, 1.0f, 0.0f, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1.0f, 100.0f, 0.0f, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2);
								}
							else
								{
								if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::random() * ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2);
									}
								else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::random() * ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2);
									}
								else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::random() * ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
									}
								else
									{
									f_condAssignValurRHS = Cube::random() * ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
									}
								}
							}

						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%f&%Opr%%Plus**Fork1plus%%%s%f&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%f&%Opr%%Minus**Fork1minus%%%sf&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%f&%Opr%%Equals**Fork1equals%%%s%f&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%f&%Opr%%Mul**Fork1multiply%%%s%f&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else
							{
							::sprintf(f_Char, "%f&%Opr%%Div**Fork1divide%%%s%f&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}

						f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char;
						}
					}
				else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2) == true)
					{
					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2));

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2));

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2));

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2));

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "Random");

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
						}
					else
						{
#if 0
						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							std::string f_StringC = "Var%%int&&" + f_Name + "%%0&%////" + ESL_LINE_ENDING;

							std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringC, ESL_INSTA_TYPE_VAR_DEF);

							f_Function->m_vec_Insta.push_back(f_Insta);
							f_Function->m_idx_vec_Insta++;

							f_Function->m_vec_String += f_StringC;
							f_LineCount++;
							}
#endif

						std::string f_VarCallName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						std::string f_VarNameFA = acMakeUnisonType(f_Target, f_VarCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, MuVar_Float, true);

						std::string f_VarVarSys = "";
						std::string f_VarType = "";
						std::string f_VarName = "";

						int f_Stage = 0;

						for(int f_Helly = 0; f_Helly < f_VarNameFA.length(); f_Helly++)
							{
							char f_c = f_VarNameFA.at(f_Helly);

							if(f_c == '&' || f_c == '%')
								{
								f_Stage++;
								}
							else
								{
								if(f_Stage == 0)
									{
									f_VarVarSys.push_back(f_c);
									}
								else if(f_Stage >= 2)
									{
									f_VarType.push_back(f_c);
									}
								else
									{
									f_VarName.push_back(f_c);
									}
								}
							}

						char f_1 = f_VarVarSys.at(0);

						float f_condAssignValurRHS = 0.0f;

						if(f_VarName.compare(f_VarCallName) == 0)
							{
							if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
								}
							else
								{
								if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::randomFac() % ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2);
									}
								else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::randomFac() % ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2);
									}
								else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::randomFac() % ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
									}
								else
									{
									f_condAssignValurRHS = Cube::randomFac() % ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
									}
								}
							}

						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%i&%Opr%%Plus**Fork1plus%%%s%i&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%i&%Opr%%Minus**Fork1minus%%%s%i&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%i&%Opr%%Equals**Fork1equals%%%s%i&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%i&%Opr%%Mul**Fork1multiply%%%s%i&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else
							{
							::sprintf(f_Char, "%i&%Opr%%Div**Fork1divide%%%s%i&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char;
						}
					}
				else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2) == true)
					{
					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%s", ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth).at(0));

						f_StringB += "Var%%String&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 5, 0, 2);

						for(int f_XY = 0; f_XY < f_Count; f_XY++)
							{
							f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
							}

						f_StringB += "Var%%String&&" + f_Name + "%%" + f_AddString + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 3, 15, 0, 2);

						for(int f_XY = 0; f_XY < f_Count; f_XY++)
							{
							f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
							}

						f_StringB += "Var%%String&&" + f_Name + "%%" + f_AddString + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 5, 20, 0, 2);

						for(int f_XY = 0; f_XY < f_Count; f_XY++)
							{
							f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
							}

						f_StringB += "Var%%String&&" + f_Name + "%%" + f_AddString + "&%";
						}
					else
						{
						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							std::string f_StringC = "Var%%String&&" + f_Name + "%%Empty&%////" + ESL_LINE_ENDING;

							std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringC, ESL_INSTA_TYPE_VAR_DEF);

							f_Function->m_vec_Insta.push_back(f_Insta);
							f_Function->m_idx_vec_Insta++;

							f_Function->m_vec_String += f_StringC;
							f_LineCount++;
							}

						std::string f_VarCallName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						std::string f_VarNameFA = acMakeUnisonType(f_Target, f_VarCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, MuVar_Float, true);

						std::string f_VarVarSys = "";
						std::string f_VarType = "";
						std::string f_VarName = "";

						int f_Stage = 0;

						for(int f_Helly = 0; f_Helly < f_VarNameFA.length(); f_Helly++)
							{
							char f_c = f_VarNameFA.at(f_Helly);

							if(f_c == '&' || f_c == '%')
								{
								f_Stage++;
								}
							else
								{
								if(f_Stage == 0)
									{
									f_VarVarSys.push_back(f_c);
									}
								else if(f_Stage >= 2)
									{
									f_VarType.push_back(f_c);
									}
								else
									{
									f_VarName.push_back(f_c);
									}
								}
							}

						char f_1 = f_VarVarSys.at(0);

						std::string f_condAssignValurRHS = "Empty";

						if(f_VarName.compare(f_VarCallName) == 0)
							{
							f_condAssignValurRHS.clear();

							if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 5, 0, 2);

								for(int f_XY = 0; f_XY < f_Count; f_XY++)
									{
									f_condAssignValurRHS += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
									}
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 3, 10, 0, 2);

								for(int f_XY = 0; f_XY < f_Count; f_XY++)
									{
									f_condAssignValurRHS += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
									}
								}
							else
								{
								int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 6, 20, 0, 2);

								for(int f_XY = 0; f_XY < f_Count; f_XY++)
									{
									f_condAssignValurRHS += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
									}
								}
							}

						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%s&%Opr%%Plus**Fork1plus%%%s%s&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else
							{
							::sprintf(f_Char, "%s&%Opr%%Equals**Fork1equals%%%s%s&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}

						f_StringB += "Var%%String&&" + f_Name + "%%" + f_Char;
						}
					}

				f_StringB += ESL_LINE_ENDING;

				std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringB, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_Function->m_vec_String += f_StringB;
				f_LineCount++;
					
				f_Contact = true;
				}
			}
		else if(f_InstaType == ESL_INSTA_TYPE_SYS_DEF)
			{
			if(1)//acFactorStrength(ESL_INSTA_TYPE_SYS_DEF, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
				{
				std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_SYS_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

				char f_Char[5000];
				FillChar(f_Char, 5000);

				std::string f_StringB;
				f_StringB.clear();

				if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2) == true)
					{
					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0.0f, 1.0f, 0.0f, 2));

						f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1.0f, 100.0f, 0.0f, 2));

						f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2));

						f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2));

						f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "Random");

						f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else
						{
						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							std::string f_StringC = "Sys%%float&&" + f_Name + "%%0.0&%////" + ESL_LINE_ENDING;

							std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringC, ESL_INSTA_TYPE_SYS_DEF);

							f_Function->m_vec_Insta.push_back(f_Insta);
							f_Function->m_idx_vec_Insta++;

							f_Function->m_vec_String += f_StringC;
							f_LineCount++;
							}

						std::string f_VarCallName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						std::string f_VarNameFA = acMakeUnisonType(f_Target, f_VarCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, MuVar_Float, true);

						std::string f_VarVarSys = "";
						std::string f_VarType = "";
						std::string f_VarName = "";

						int f_Stage = 0;

						for(int f_Helly = 0; f_Helly < f_VarNameFA.length(); f_Helly++)
							{
							char f_c = f_VarNameFA.at(f_Helly);

							if(f_c == '&' || f_c == '%')
								{
								f_Stage++;
								}
							else
								{
								if(f_Stage == 0)
									{
									f_VarVarSys.push_back(f_c);
									}
								else if(f_Stage >= 2)
									{
									f_VarType.push_back(f_c);
									}
								else
									{
									f_VarName.push_back(f_c);
									}
								}
							}

						char f_1 = f_VarVarSys.at(0);

						float f_condAssignValurRHS = 0.0f;

						if(f_VarName.compare(f_VarCallName) == 0)
							{
							if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0.0f, 1.0f, 0.0f, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1.0f, 100.0f, 0.0f, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2);
								}
							else
								{
								if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::random() * ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2);
									}
								else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::random() * ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2);
									}
								else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::random() * ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
									}
								else
									{
									f_condAssignValurRHS = Cube::random() * ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
									}
								}
							}

						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%f&%Opr%%Plus**Fork1plus%%%s%f&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%f&%Opr%%Minus**Fork1minus%%%sf&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%f&%Opr%%Equals**Fork1equals%%%s%f&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%f&%Opr%%Mul**Fork1multiply%%%s%f&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else
							{
							::sprintf(f_Char, "%f&%Opr%%Div**Fork1divide%%%s%f&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}

						f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char;
						}
					}
				else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2) == true)
					{
					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2));

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2));

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2));

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2));

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "Random");

						f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
						}
					else
						{
						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							std::string f_StringC = "Var%%int&&" + f_Name + "%%0&%////" + ESL_LINE_ENDING;

							std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringC, ESL_INSTA_TYPE_VAR_DEF);

							f_Function->m_vec_Insta.push_back(f_Insta);
							f_Function->m_idx_vec_Insta++;

							f_Function->m_vec_String += f_StringC;
							f_LineCount++;
							}

						std::string f_VarCallName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						std::string f_VarNameFA = acMakeUnisonType(f_Target, f_VarCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, MuVar_Int, true);

						std::string f_VarVarSys = "";
						std::string f_VarType = "";
						std::string f_VarName = "";

						int f_Stage = 0;

						for(int f_Helly = 0; f_Helly < f_VarNameFA.length(); f_Helly++)
							{
							char f_c = f_VarNameFA.at(f_Helly);

							if(f_c == '&' || f_c == '%')
								{
								f_Stage++;
								}
							else
								{
								if(f_Stage == 0)
									{
									f_VarVarSys.push_back(f_c);
									}
								else if(f_Stage >= 2)
									{
									f_VarType.push_back(f_c);
									}
								else
									{
									f_VarName.push_back(f_c);
									}
								}
							}

						char f_1 = f_VarVarSys.at(0);

						float f_condAssignValurRHS = 0.0f;

						if(f_VarName.compare(f_VarCallName) == 0)
							{
							if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
								}
							else
								{
								if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::randomFac() % ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2);
									}
								else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::randomFac() % ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2);
									}
								else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
									{
									f_condAssignValurRHS = Cube::randomFac() % ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
									}
								else
									{
									f_condAssignValurRHS = Cube::randomFac() % ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2);
									}
								}
							}

						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%i&%Opr%%Plus**Fork1plus%%%s%i&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%i&%Opr%%Minus**Fork1minus%%%s%i&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%i&%Opr%%Equals**Fork1equals%%%s%i&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%i&%Opr%%Mul**Fork1multiply%%%s%i&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else
							{
							::sprintf(f_Char, "%i&%Opr%%Div**Fork1divide%%%s%i&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}

						f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char;
						}
					}
				else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2) == true)
					{
					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%s", ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth).at(0));

						f_StringB += "Var%%String&&" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 5, 0, 2);

						for(int f_XY = 0; f_XY < f_Count; f_XY++)
							{
							f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
							}

						f_StringB += "Var%%String&&" + f_Name + "%%" + f_AddString + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 3, 15, 0, 2);

						for(int f_XY = 0; f_XY < f_Count; f_XY++)
							{
							f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
							}

						f_StringB += "Var%%String&&" + f_Name + "%%" + f_AddString + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 5, 20, 0, 2);

						for(int f_XY = 0; f_XY < f_Count; f_XY++)
							{
							f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
							}

						f_StringB += "Var%%String&&" + f_Name + "%%" + f_AddString + "&%";
						}
					else
						{
						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							std::string f_StringC = "Var%%String&&" + f_Name + "%%Empty&%////" + ESL_LINE_ENDING;

							std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringC, ESL_INSTA_TYPE_VAR_DEF);

							f_Function->m_vec_Insta.push_back(f_Insta);
							f_Function->m_idx_vec_Insta++;

							f_Function->m_vec_String += f_StringC;
							f_LineCount++;
							}

						std::string f_VarCallName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						std::string f_VarNameFA = acMakeUnisonType(f_Target, f_VarCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, MuVar_String, true);

						std::string f_VarVarSys = "";
						std::string f_VarType = "";
						std::string f_VarName = "";

						int f_Stage = 0;

						for(int f_Helly = 0; f_Helly < f_VarNameFA.length(); f_Helly++)
							{
							char f_c = f_VarNameFA.at(f_Helly);

							if(f_c == '&' || f_c == '%')
								{
								f_Stage++;
								}
							else
								{
								if(f_Stage == 0)
									{
									f_VarVarSys.push_back(f_c);
									}
								else if(f_Stage >= 2)
									{
									f_VarType.push_back(f_c);
									}
								else
									{
									f_VarName.push_back(f_c);
									}
								}
							}

						char f_1 = f_VarVarSys.at(0);

						std::string f_condAssignValurRHS = "Empty";

						if(f_VarName.compare(f_VarCallName) == 0)
							{
							f_condAssignValurRHS.clear();

							if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								f_condAssignValurRHS = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 5, 0, 2);

								for(int f_XY = 0; f_XY < f_Count; f_XY++)
									{
									f_condAssignValurRHS += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
									}
								}
							else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
								{
								int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 3, 10, 0, 2);

								for(int f_XY = 0; f_XY < f_Count; f_XY++)
									{
									f_condAssignValurRHS += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
									}
								}
							else
								{
								int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 6, 20, 0, 2);

								for(int f_XY = 0; f_XY < f_Count; f_XY++)
									{
									f_condAssignValurRHS += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
									}
								}
							}

						if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
							{
							::sprintf(f_Char, "%s&%Opr%%Plus**Fork1plus%%%s%s&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}
						else
							{
							::sprintf(f_Char, "%s&%Opr%%Equals**Fork1equals%%%s%s&%////\n", 0.0f, f_VarNameFA, f_condAssignValurRHS);
							}

						f_StringB += "Sys%%String" + f_Name + "%%" + f_Char;
						}
					}

				f_StringB += ESL_LINE_ENDING;

				std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringB, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_Function->m_vec_String += f_StringB;
				f_LineCount++;
					
				f_Contact = true;
				}
			}
		else if(f_InstaType == ESL_INSTA_TYPE_CONDITIONAL)
			{
			if(1)//acFactorStrength(ESL_INSTA_TYPE_CONDITIONAL, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
				{
				//Place LHS
				std::string f_StringAB = "Var%%";

				std::string f_VarACallName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarANameAndType = acMakeUnisonType(f_Target, f_VarACallName, 1, ESL_INSTA_TYPE_CONDITIONAL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

				std::string f_VarAName = "";

				std::string f_VarAType = "";

				int f_Stage = 0;
				for(int f_Helly = 0; f_Helly < f_VarANameAndType.length(); f_Helly++)
					{
					char f_c = f_VarANameAndType.at(f_Helly);

					if(f_c == '&' || f_c == '%')
						{
						f_Stage++;
						}
					else
						{
						if(f_Stage == 0)
							{
							f_VarAType.push_back(f_c);
							}
						else if(f_Stage >= 2)
							{
							f_VarAName.push_back(f_c);
							}
						}
					}

				int f_MuVarAType = agFind_VarType(f_VarAType);

				if(f_MuVarAType == MuVar_Float)
					{
					f_StringAB += f_VarANameAndType + "0.0&%";
					}
				else if(f_MuVarAType == MuVar_Float)
					{
					f_StringAB += f_VarANameAndType + "0&%";
					}
				else
					{
					f_StringAB += f_VarANameAndType + "Empty&%";
					}

				std::shared_ptr<classInsta> f_InstaA = std::make_shared<classInsta>(f_StringAB, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaA);
				f_Function->m_idx_vec_Insta++;

				std::string f_StringB = f_StringAB + "Cond%%";

				std::string f_Name = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
				std::shared_ptr<classInsta> f_InstaAB = std::make_shared<classInsta>(f_StringB, ESL_INSTA_TYPE_CONDITIONAL);

				f_Function->m_vec_Insta.push_back(f_InstaAB);
				f_Function->m_idx_vec_Insta++;

				int f_FingerCount = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 6, 1, 3);
								
				if(f_FingerCount <= MuCon_Equal)
					{
					f_StringB += "==^^";
					}
				else if(f_FingerCount == MuCon_NotEqual)
					{
					f_StringB += "!=^^";
					}
				else if(f_FingerCount == MuCon_SmallThan)
					{
					f_StringB += "<<^^";
					}
				else if(f_FingerCount == MuCon_GreatThan)
					{
					f_StringB += ">>^^";
					}
				else if(f_FingerCount == MuCon_SmallThanorEqual)
					{
					f_StringB += "<=^^";
					}
				else
					{
					f_StringB += ">=^^";
					}

				f_StringB += f_Name + "%%";

				std::string f_VarBCallName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarBNameAndType = acMakeUnisonType(f_Target, f_VarBCallName, 1, ESL_INSTA_TYPE_CONDITIONAL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_MuVarAType);

				std::string f_VarBName = "";

				int f_StageBK = 0;
				for(int f_Helly = 0; f_Helly < f_VarBNameAndType.length(); f_Helly++)
					{
					char f_c = f_VarBNameAndType.at(f_Helly);

					if(f_c == '&' || f_c == '%')
						{
						f_StageBK++;
						}
					else
						{
						if(f_StageBK >= 4)
							{
							f_VarBName.push_back(f_c);
							}
						}
					}

				char f_Char[5000];
				FillChar(f_Char, 5000);

				std::string f_StringFS = "";

				if(f_VarBName.compare(f_VarBCallName) == 0)
					{
					if(f_MuVarAType == MuVar_Float)
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0.0f, 1.0f, 0.0f, 2));

							f_StringFS += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1.0f, 100.0f, 0.0f, 2));

							f_StringFS += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2));

							f_StringFS += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2));

							f_StringFS += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "Random");

							f_StringFS += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						}
					else if(f_MuVarAType == MuVar_Int)
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2));

							f_StringFS += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2));

							f_StringFS += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2));

							f_StringFS += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2));

							f_StringFS += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "Random");

							f_StringFS += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						}
					else
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%s", ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth).at(0));

							f_StringFS += "Var%%String&&" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 5, 0, 2);

							for(int f_XY = 0; f_XY < f_Count; f_XY++)
								{
								f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringFS += "Var%%String&&" + f_VarBNameAndType + f_AddString + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 3, 15, 0, 2);

							for(int f_XY = 0; f_XY < f_Count; f_XY++)
								{
								f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringFS += "Var%%String&&" + f_VarBNameAndType + f_AddString + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 5, 20, 0, 2);

							for(int f_XY = 0; f_XY < f_Count; f_XY++)
								{
								f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringFS += "Var%%String&&" + f_VarBNameAndType + f_AddString + "&%";
							}
						}
					}
				else
					{
					if(f_MuVarAType == MuVar_Float)
						{
						f_StringFS += "Var%%" + f_VarBNameAndType + "0.0&%";
						}
					else if(f_MuVarAType == MuVar_Int)
						{
						f_StringFS += "Var%%" + f_VarBNameAndType + "0&%";
						}
					else
						{
						f_StringFS += "Var%%" + f_VarBNameAndType + "Empty&%";
						}
					}

				std::shared_ptr<classInsta> f_InstaB = std::make_shared<classInsta>(f_StringFS, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaB);
				f_Function->m_idx_vec_Insta++;

				f_StringB += f_StringFS;

				f_Function->m_vec_String += f_StringB;
				f_LineCount++;

#if 0
				int f_InstaCount = 2 + ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 3, 0, 3);

				std::vector<int> f_conInstaCount;
				f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 2, 0, 3));
				f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 12, 0, 3));
				f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2, 25, 4, 3));
				int f_Select = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 3, 1, 3);
					
				m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_conInstaCount[f_Select], "ECNMiner_Affinity", ESL_INSTA_TYPE_CONDITIONAL));
				m_idx_vec_CountLock++;
#endif

				f_Contact = true;
				}
			}
		else if(f_InstaType == ESL_INSTA_TYPE_LOOP_DEF)
			{
			if(1)//acFactorStrength(ESL_INSTA_TYPE_LOOP_DEF, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
				{
				std::string f_forName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
				std::string f_StringF = "For%% " + f_forName + "%%";

				std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringF, ESL_INSTA_TYPE_LOOP_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				std::string f_VarBCallName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarBNameAndType = acMakeUnisonType(f_Target, f_VarBCallName, 1, ESL_INSTA_TYPE_LOOP_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

				std::string f_VarBName = "";

				std::string f_VarBType = "";

				int f_Stage = 0;
				for(int f_Helly = 0; f_Helly < f_VarBNameAndType.length(); f_Helly++)
					{
					char f_c = f_VarBNameAndType.at(f_Helly);

					if(f_c == '&' || f_c == '%')
						{
						f_Stage++;
						}
					else
						{
						if(f_Stage == 0)
							{
							f_VarBType.push_back(f_c);
							}
						if(f_Stage >= 2)
							{
							f_VarBName.push_back(f_c);
							}
						}
					}

				char f_Char[5000];
				FillChar(f_Char, 5000);

				int f_MuVarBType = agFind_VarType(f_VarBType);

				std::string f_StringFY = "";

				if(f_VarBName.compare(f_VarBCallName) == 0)
					{
					if(f_MuVarBType == MuVar_Float)
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0.0f, 1.0f, 0.0f, 2));

							f_StringFY += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1.0f, 100.0f, 0.0f, 2));

							f_StringFY += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2));

							f_StringFY += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2));

							f_StringFY += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "Random");

							f_StringFY += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						}
					else if(f_MuVarBType == MuVar_Int)
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2));

							f_StringFY += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2));

							f_StringFY += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2));

							f_StringFY += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2));

							f_StringFY += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "Random");

							f_StringFY += "Var%%" + f_VarBNameAndType + f_Char + "&%";
							}
						}
					else
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_Char, "%s", ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth).at(0));

							f_StringFY += "Var%%String&&" + f_VarBNameAndType + f_Char + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 5, 0, 2);

							for(int f_XY = 0; f_XY < f_Count; f_XY++)
								{
								f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringFY += "Var%%String&&" + f_VarBNameAndType + f_AddString + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 3, 15, 0, 2);

							for(int f_XY = 0; f_XY < f_Count; f_XY++)
								{
								f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringFY += "Var%%String&&" + f_VarBNameAndType + f_AddString + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 5, 20, 0, 2);

							for(int f_XY = 0; f_XY < f_Count; f_XY++)
								{
								f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringFY += "Var%%String&&" + f_VarBNameAndType + f_AddString + "&%";
							}
						}
					}
				else
					{
					if(f_MuVarBType == MuVar_Float)
						{
						f_StringFY += "Var%%" + f_VarBNameAndType + "0.0&%";
						}
					else if(f_MuVarBType == MuVar_Int)
						{
						f_StringFY += "Var%%" + f_VarBNameAndType + "0&%";
						}
					else
						{
						f_StringFY += "Var%%" + f_VarBNameAndType + "Empty&%";
						}
					}

				std::shared_ptr<classInsta> f_InstaB = std::make_shared<classInsta>(f_StringFY, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaB);
				f_Function->m_idx_vec_Insta++;

				f_StringF += f_StringFY;

				std::string f_VarCCallName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarCNameAndType = acMakeUnisonType(f_Target, f_VarCCallName, 1, ESL_INSTA_TYPE_LOOP_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

				std::string f_VarCName = "";

				std::string f_VarCType = "";

				int f_StageC = 0;
				for(int f_Helly = 0; f_Helly < f_VarCNameAndType.length(); f_Helly++)
					{
					char f_c = f_VarCNameAndType.at(f_Helly);

					if(f_c == '&' || f_c == '%')
						{
						f_StageC++;
						}
					else
						{
						if(f_StageC == 0)
							{
							f_VarCType.push_back(f_c);
							}
						if(f_StageC >= 2)
							{
							f_VarCName.push_back(f_c);
							}
						}
					}

				char f_CharC[5000];
				FillChar(f_CharC, 5000);

				int f_MuVarCType = agFind_VarType(f_VarCType);

				std::string f_StringFK = "";

				if(f_VarCName.compare(f_VarCCallName) == 0)
					{
					if(f_MuVarCType == MuVar_Float)
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0.0f, 1.0f, 0.0f, 2));

							f_StringFK += "Var%%" + f_VarCNameAndType + f_CharC + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1.0f, 100.0f, 0.0f, 2));

							f_StringFK += "Var%%" + f_VarCNameAndType + f_CharC + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2));

							f_StringFK += "Var%%" + f_VarCNameAndType + f_CharC + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "%f", ac_takeMeasurementFLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100.0f, 5000.0f, 0.0f, 2));

							f_StringFK += "Var%%" + f_VarCNameAndType + f_CharC + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "Random");

							f_StringFK += "Var%%" + f_VarCNameAndType + f_CharC + "&%";
							}
						}
					else if(f_MuVarCType == MuVar_Int)
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 1, 0, 2));

							f_StringFK += "Var%%" + f_VarCNameAndType + f_CharC + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 100, 0, 2));

							f_StringFK += "Var%%" + f_VarCNameAndType + f_CharC + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2));

							f_StringFK += "Var%%" + f_VarCNameAndType + f_CharC + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "%i", ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 100, 5000, 0, 2));

							f_StringFK += "Var%%" + f_VarCNameAndType + f_CharC + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "Random");

							f_StringFK += "Var%%" + f_VarCNameAndType + f_CharC + "&%";
							}
						}
					else
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							::sprintf(f_CharC, "%s", ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth).at(0));

							f_StringFK += "Var%%String&&" + f_VarCNameAndType + f_CharC + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 5, 0, 2);

							for(int f_XY = 0; f_XY < f_Count; f_XY++)
								{
								f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringFK += "Var%%String&&" + f_VarCNameAndType + f_AddString + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 3, 15, 0, 2);

							for(int f_XY = 0; f_XY < f_Count; f_XY++)
								{
								f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringFK += "Var%%String&&" + f_VarCNameAndType + f_AddString + "&%";
							}
						else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
							{
							std::string f_AddString = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 5, 20, 0, 2);

							for(int f_XY = 0; f_XY < f_Count; f_XY++)
								{
								f_AddString += ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringFK += "Var%%String&&" + f_VarCNameAndType + f_AddString + "&%";
							}
						}
					}
				else
					{
					if(f_MuVarCType == MuVar_Float)
						{
						f_StringFK += "Var%%" + f_VarCNameAndType + "0.0&%";
						}
					else if(f_MuVarCType == MuVar_Int)
						{
						f_StringFK += "Var%%" + f_VarCNameAndType + "0&%";
						}
					else
						{
						f_StringFK += "Var%%" + f_VarCNameAndType + "Empty&%";
						}
					}

				std::shared_ptr<classInsta> f_InstaC = std::make_shared<classInsta>(f_StringFK, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaC);
				f_Function->m_idx_vec_Insta++;

				f_StringF += f_StringFK;
					
				f_Function->m_vec_String += f_StringF;
				f_LineCount++;
				
#if 0
				int f_loopLineCount = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 8, 105, 8, 3);

				m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_loopLineCount, "ECNMiner_Affinity", ESL_INSTA_TYPE_LOOP_DEF));
				m_idx_vec_CountLock++;
#endif

				f_Contact = true;
				}
			}
		else if(f_InstaType == ESL_INSTA_TYPE_FUNC_CALL)
			{
			if(1)//acFactorStrength(ESL_INSTA_TYPE_FUNC_CALL, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
				{
				std::string f_StringB = "";

				if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
					{
					std::string f_ReturnVarTypeName = acMakeUnisonType(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, -100, true);

					std::shared_ptr<classInsta> f_InstaR = std::make_shared<classInsta>(f_ReturnVarTypeName, ESL_INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaR);
					f_Function->m_idx_vec_Insta++;

					f_StringB += "Var%%" + f_ReturnVarTypeName + "%%1.0&%";
					}
				else
					{
					if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
						{
						std::string f_ReturnVarTypeName = acMakeUnisonType(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_CLASS_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, -100, true);

						std::shared_ptr<classInsta> f_InstaR = std::make_shared<classInsta>(f_ReturnVarTypeName, ESL_INSTA_TYPE_VAR_CALL);

						f_Function->m_vec_Insta.push_back(f_InstaR);
						f_Function->m_idx_vec_Insta++;

						f_StringB += "ClassVar%%" + f_ReturnVarTypeName + "%%";
						}
					}
				
				std::string f_FunctionName1 = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
				std::string f_FunctionName2 = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

				std::string f_FunctionString = "Fcn%%" + f_FunctionName1 + "&*" + f_FunctionName2 + "%%";

				std::shared_ptr<classInsta> f_InstaB = std::make_shared<classInsta>(f_FunctionString, ESL_INSTA_TYPE_FUNC_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaB);
				f_Function->m_idx_vec_Insta++;

				f_StringB += f_FunctionString;

				if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)	//arg1 is var
					{
					std::string f_Var1NameFA = acMakeUnisonType(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, -100, true);

					std::shared_ptr<classInsta> f_InstaA1 = std::make_shared<classInsta>(f_Var1NameFA, ESL_INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaA1);
					f_Function->m_idx_vec_Insta++;

					f_StringB += f_Var1NameFA + "%%1.0&%";
					}
				else
					{
					if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true) //arg1 is classvar
						{
						std::string f_Var1NameFA = acMakeUnisonType(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_CLASS_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, -100, true);

						std::shared_ptr<classInsta> f_InstaA1 = std::make_shared<classInsta>(f_Var1NameFA, ESL_INSTA_TYPE_CLASS_VAR_CALL);

						f_Function->m_vec_Insta.push_back(f_InstaA1);
						f_Function->m_idx_vec_Insta++;

						f_StringB += f_Var1NameFA + "%%";
						}
					}

				if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)	//arg2 is var
					{
					std::string f_Var2NameFA = acMakeUnisonType(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, -100, true);

					std::shared_ptr<classInsta> f_InstaA2 = std::make_shared<classInsta>(f_Var2NameFA, ESL_INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaA2);
					f_Function->m_idx_vec_Insta++;

					f_StringB += f_Var2NameFA + "%%1.0&%";
					}
				else
					{
					if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true) //arg2 is classvar
						{
						std::string f_Var2NameFA = acMakeUnisonType(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_CLASS_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, -100, true);

						std::shared_ptr<classInsta> f_InstaA2 = std::make_shared<classInsta>(f_Var2NameFA, ESL_INSTA_TYPE_CLASS_VAR_CALL);

						f_Function->m_vec_Insta.push_back(f_InstaA2);
						f_Function->m_idx_vec_Insta++;

						f_StringB += f_Var2NameFA + "%%";
						}
					}

				f_StringB += "////" + ESL_LINE_ENDING;
					
				f_Function->m_vec_String += f_StringB;

				f_LineCount++;
					
				f_Contact = true;
				}
			}
		else if(f_InstaType == ESL_INSTA_TYPE_FUNC_DEF)
			{
			if(1)//acFactorStrength(ESL_INSTA_TYPE_FUNC_DEF, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
				{
				std::string f_FunctionDefName1 = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
				std::string f_FunctionDefName2 = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

				std::string f_StringE = "FuncDef%%" + f_FunctionDefName1 + "%%" + f_FunctionDefName2 + "%%////";

				std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringE, ESL_INSTA_TYPE_FUNC_DEF);
				
				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringE += ESL_LINE_ENDING;

				f_Function->m_vec_String += f_StringE;
				f_LineCount++;

				f_Contact = true;
				}
			}
		else if(f_InstaType == ESL_INSTA_TYPE_CLASS_DEF)
			{
			if(1)//acFactorStrength(ESL_INSTA_TYPE_CLASS_DEF, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
				{
				std::string f_ClassDefName = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
				std::string f_ClassDefName2 = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

				std::string f_StringE = "ClassDef%%" + f_ClassDefName + "&*" + f_ClassDefName2 + "%%////";
				f_StringE += ESL_LINE_ENDING;

				std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringE, ESL_INSTA_TYPE_CLASS_DEF);
				
				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;
				
				f_Function->m_vec_String += f_StringE;
				f_LineCount++;

				f_Contact = true; //?
				}
			}
		else if(f_InstaType == ESL_INSTA_TYPE_CLASSVAR_DEF)
			{
			if(1)//acFactorStrength(ESL_INSTA_TYPE_CLASSVAR_DEF, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
				{
				std::string f_ClassVarType = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_CLASSVAR_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
				std::string f_ClassVarName = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_CLASSVAR_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

				std::string f_StringE = "ClassVar%%" + f_ClassVarType + "&$" + f_ClassVarName + "%%////";

				std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringE, ESL_INSTA_TYPE_CLASSVAR_DEF);
				
				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringE += ESL_LINE_ENDING;
				
				f_Function->m_vec_String += f_StringE;
				f_LineCount++;

				f_Contact = true;
				}
			}
		else
			{
			throw;
			}

		  ///////////////////
		 //
		// Count Map
		if(f_Contact == true)
			{
#if 0
			f_vec_CodeLine->m_vec_Code.push_back(f_Function->m_vec_Insta[f_Function->m_idx_vec_Insta - 1]);
			f_vec_CodeLine->m_idx_vec_Code++;
#endif
#if 0
			if(m_idx_vec_CountLock > 0)
				{
				for(int f_cv = m_idx_vec_CountLock - 1; f_cv >= 0; f_cv--)
					{
					int f_Caramel = f_cv;

					m_vec_CountLock[f_Caramel]->m_Count--;
					
					if(m_vec_CountLock[f_Caramel]->m_Count <= 0)
						{
						bool f_on = true;

						if(f_Caramel < (m_idx_vec_CountLock - 1))
							{
							f_on = false;
							}
								
						if(f_on == true)
							{
							std::shared_ptr<classCountLock> f_Lock = m_vec_CountLock[f_Caramel];

							if(f_Lock->m_String.compare("ECNMiner_Affinity") == 0)
								{
								f_Function->m_vec_String += "Function%%EcomNative&*ECNMiner_Affinity%%////";
								f_LineCount++;

								//acResetLine();
								//f_Function->m_vec_CodeLineStorage.push_back(f_vec_CodeLine);
								//f_Function->m_idx_vec_CodeLineStorage++;

								//f_vec_CodeLine->m_vec_Code.clear();
								//f_vec_CodeLine->m_idx_vec_Code = 0;
								}

							acDecFactor(f_Lock->m_Factor);

							m_idx_vec_CountLock--;
								
							for(int f_XY = f_Caramel; f_XY < m_idx_vec_CountLock; f_XY++)
								{
								m_vec_CountLock[f_XY] = m_vec_CountLock[f_XY + 1];
								}

							m_vec_CountLock.pop_back();
							}
						else
							{
							m_vec_CountLock[f_Caramel]->m_Count = 1;
							}
						}
					}
				}
#endif
			}

		f_Scan = ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 7);
		}

	f_Function->m_vec_String.pop_back();

	f_Function->m_vec_String += "####";

	std::shared_ptr<Qcom_eslfunction> f_func = f_Function->acConvert();
#pragma message("WARNING possible optimization point for any use other then not often")

	return f_func;
}

shared_ptr<Qcom_eslfunction> classFunction::acConvert(void)
{
	shared_ptr<Qcom_eslfunction> f_ESLfunc = make_shared<Qcom_eslfunction>();

	f_ESLfunc->m_ID = -1551;
	f_ESLfunc->m_Save = true;

	f_ESLfunc->m_owner = g_Wallet->GetAdr();
	f_ESLfunc->m_name = m_Name;

	bool f_Some = false;
	bool f_StartLine = true;
	std::string f_Carriage = "";

	for(int f_XY = 0; f_XY < m_vec_String.length(); f_XY++)
		{
		char f_c = m_vec_String.at(f_XY);

		if((f_c == '\n') || (f_c == '\r') || (f_XY >= (m_vec_String.length() - 1)))
			{
			if(f_StartLine == true)
				{
				if(f_Some == true)
					{
					f_ESLfunc->m_vec_InitLineOrdered.push_back(f_Carriage);
					f_Carriage.clear();
					f_Some = false;
					}
				}
			else
				{
				if(f_Some == true)
					{
					f_ESLfunc->m_vec_InitLineOrdered.push_back(f_Carriage);
					f_Carriage.clear();
					f_Some = false;
					}
				}
			}
		else
			{
			f_Carriage.push_back(f_c);
			f_Some = true;
			}
		}

	return f_ESLfunc;
}

bool classLMap::ac_ext_Typing_isEqual(int f_Var_Typing, int f_Var_Current_Code)
{
	if(f_Var_Current_Code == ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT)
		{
		if ((f_Var_Typing == MuVar_Float) ||
			(f_Var_Typing == MuVar_Float2) ||
			(f_Var_Typing == MuVar_Float3) ||
			(f_Var_Typing == MuVar_Float4))
			{
			return true;
			}
		else
			{

#ifdef ECOIN_SECURE
#if 1
			ecoin::ag_EcoinSecure_Inf_Loop_Assert_EQ(f_Var_Typing, MuVar_Full);
#pragma message("WARNING non-production runtime code")
#endif
#endif

			return false;
			}
		}
	else if (f_Var_Current_Code == ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING)
		{
		if ((f_Var_Typing == MuVar_String) ||
			(f_Var_Typing == MuVar_Char))
			{
			return true;
			}
		else
			{

#ifdef ECOIN_SECURE
#if 1
			ecoin::ag_EcoinSecure_Inf_Loop_Assert_EQ(f_Var_Typing, MuVar_Full);
#pragma message("WARNING non-production runtime code")
#endif
#endif

			return false;
			}
		}
	else if(f_Var_Current_Code == ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT)
		{
		if ((f_Var_Typing == MuVar_uInt) ||
			(f_Var_Typing == MuVar_Int) ||
			(f_Var_Typing == MuVar_Int2) ||
			(f_Var_Typing == MuVar_Int3) ||
			(f_Var_Typing == MuVar_Int4) ||
			(f_Var_Typing == MuVar_Bool))
			{
			return true;
			}
		else
			{

#ifdef ECOIN_SECURE
#if 1
			ecoin::ag_EcoinSecure_Inf_Loop_Assert_EQ(f_Var_Typing, MuVar_Full);
#pragma message("WARNING non-production runtime code")
#endif
#endif

			return false;
			}
		}

	return false;
}

std::vector<std::vector<std::string>> classLMap::ac_ext_eslLine_morf_array(std::string f_LineString)
{
	bool f_SomeC = false;
	std::string f_TextCarriage = "";
	std::string f_CodeCarriage = "";
	std::vector<std::string> f_VecBit;
	std::vector<std::vector<std::string>> f_String_Vector;

	for(int f_XY = 0; f_XY < f_LineString.length(); f_XY++)
		{
		char f_c = f_LineString.at(f_XY);

		if(((f_c == '&') || (f_c == '%') ||
			(f_c == '#') || (f_c == '/') ||
			(f_c == '*') || (f_c == '^') || (f_c == '$')) && (f_XY < (f_LineString.length() - 1)))
			{
			f_CodeCarriage.push_back(f_c);
			f_SomeC = true;
			}
		else
			{
			if(f_SomeC == true)
				{
				f_VecBit.clear();
				f_VecBit.push_back(f_TextCarriage);
				f_VecBit.push_back(f_CodeCarriage);
				f_String_Vector.push_back(f_VecBit);
				f_TextCarriage.clear();
				f_CodeCarriage.clear();
				f_SomeC = false;
				}

			f_TextCarriage.push_back(f_c);
			}
		}

	return f_String_Vector;
}

int classLMap::ac_ext_Scan_Lines_Keyword_Next(int f_LineCount, int f_morf1, int f_morf2, std::shared_ptr<Qcom_eslfunction> f_Save_Com_Function, std::string f_Keyword)
{
	for(int f_LineNo = f_LineCount; f_LineNo < f_Save_Com_Function->m_vec_InitLineOrdered.size(); f_LineNo++)
		{
		std::string f_LineString = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineNo];

		std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

		if(f_morfarray[f_morf1][f_morf2].compare(f_Keyword) == 0)
			{
			return f_LineNo - f_LineCount;
			}
		}

	return -1;
}

std::string classLMap::acGen_Var_fromEcom(int f_Line_Index, int f_Prec_Type, bool f_Value_Given_Bool, std::string f_Line, std::string f_Var_Type_String, std::string f_Var_Name_String, std::string f_Var_Value_String)
{
	int f_SingIndex = f_Line_Index;
	int f_SIndex_Typ = f_Prec_Type;
	bool f_SValueOn = f_Value_Given_Bool;

	std::string f_ValueString = f_Var_Value_String;

	int f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

	std::string f_NameString = ac_recordMeasurement(f_NameString, f_ElementIndex, -1, -1, -1, -1);

	int f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

	std::string f_TypeString = ac_recordMeasurement(f_Var_Type_String, f_ElementIndex, -1, -1, -1, -1);

	std::string f_VarName = f_NameString;

	f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

	ac_recordMeasurementBLTV1(2, 0, f_SValueOn, f_ElementIndex);
	//END Input

	std::string f_StringA = "";

	//Varso...!
	if(f_SIndex_Typ == ESL_MORF_TYPE_VAR)
		{
		f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

		ac_recordMeasurementBLTV1(2, 0, true, f_ElementIndex);

		if(f_SValueOn == true)
			{
			char f_Char[150];
			FillChar(f_Char, 150);

			f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

			ac_recordMeasurementBLTV1(2, 0, true, f_ElementIndex);

			f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

			//Float Parameter
			if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT), f_ElementIndex) == true)
				{
				float f_ValueNr = atof(f_ValueString.c_str());

				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
					{
					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

					f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);
						
					if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

						f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

							f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex, true))
									{
									::sprintf(f_Char, "Random");

									f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									throw; //add debug message variable value range not found, empty var recording
#if 0
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									if(acRecordStrengthVar(VAR_DEF_TYPE_SYSTEM, f_Line, f_ValueNr, f_ElementIndex))
										{
										std::string f_SysName = f_NameString;

										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
											{
											f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

											::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
											}
										else
											{
											f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

											if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
												{
												f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

												::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

												if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex))
															{
															::sprintf(f_Char, "Random");
															}
														else
															{
															throw; //add debug message sys var not processed
															}
														}
													}
												}
											}

										f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
										}
#endif
									}
								}
							}
						}
					}
				}
			else
				{
				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				//Int Parameter
				if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
					{
					int f_ValueNr = atoi(f_ValueString.c_str());

					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(0, 1, 0, 2, 3, f_ValueNr, f_ElementIndex));

						f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);
						
						if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(1, 100, 0, 2, 3, f_ValueNr, f_ElementIndex));

							f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex, true))
										{
										::sprintf(f_Char, "Random");

										f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										throw; //add debug message variable value range not found, empty var recording
#if 0
										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										if(acRecordStrengthVar(VAR_DEF_TYPE_SYSTEM, f_Line, f_ValueNr, f_ElementIndex))
											{
											std::string f_SysName = f_NameString;

											f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

											if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
												{
												f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

												::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

												if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

															::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

															if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex))
																{
																::sprintf(f_Char, "Random");
																}
															else
																{
																throw; //add debug message sys var not processed
																}
															}
														}
													}
												}

											f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
											}
#endif
										}
									}
								}
							}
						}
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					//String Parameter
					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING), f_ElementIndex) == true)
						{
						std::string f_ValueNr = f_ValueString;

						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(0, 1, 0, 2, 3, f_ValueNr, f_ElementIndex));

							f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);
						
							if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(1, 100, 0, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(100, 5000, 0, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

										f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										if(acRecordStrengthVarString(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex, true))
											{
											::sprintf(f_Char, "Random");

											f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											throw; //add debug message variable value range not found, empty var recording
#if 0
											f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

											if(acRecordStrengthVarString(VAR_DEF_TYPE_SYSTEM, f_Line, f_ValueNr, f_ElementIndex))
												{
												std::string f_SysName = f_NameString;

												f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

												if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

															::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

															if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

																::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

																if(acRecordStrengthVarString(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex))
																	{
																	::sprintf(f_Char, "Random");
																	}
																else
																	{
																	throw; //add debug message sys var not processed
																	}
																}
															}
														}
													}

												f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
												}
#endif
											}
										}
									}
								}
							}
						}
					}
				}
			}
		else // no value number
			{
			char f_Char[150];
			FillChar(f_Char, 150);

			f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

			ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

			f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

			//Float Parameter no raw value
			if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT), f_ElementIndex) == true)
				{
				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%";
				}
			else
				{
				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				//Int Parameter no raw value
				if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
					{
					f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%";
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					//String Parameter no raw value
					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%";
						}
					else
						{
						throw; //add debug message type slicing
						}
					}
				}
			} //end no number
		} //END TYPE 'Var'
	else
		{ //Systema...! 'Sys'
		f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

		ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

		if(f_SIndex_Typ == ESL_MORF_TYPE_SYS)
			{
			f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

			ac_recordMeasurementBLTV1(2, 0, true, f_ElementIndex);

			if(f_SValueOn == true)
				{
				char f_Char[150];
				FillChar(f_Char, 150);

				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				ac_recordMeasurementBLTV1(2, 0, true, f_ElementIndex);

				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				//Float Parameter
				if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT), f_ElementIndex) == true)
					{
					float f_ValueNr = atof(f_ValueString.c_str());

					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

						f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);
						
						if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

							f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex, true))
										{
										::sprintf(f_Char, "Random");

										f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										throw; //add debug message variable value range not found, empty var recording
#if 0
										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										if(acRecordStrengthVar(VAR_DEF_TYPE_SYSTEM, f_Line, f_ValueNr, f_ElementIndex))
											{
											std::string f_SysName = f_NameString;

											f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

											if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
												{
												f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

												::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

												if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

															::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

															if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex))
																{
																::sprintf(f_Char, "Random");
																}
															else
																{
																throw; //add debug message sys var not processed
																}
															}
														}
													}
												}

											f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
											}
#endif
										}
									}
								}
							}
						}
					}
				else //INT SYS
					{
					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					//Int Parameter
					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
						{
						int f_ValueNr = atoi(f_ValueString.c_str());

						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(0, 1, 0, 2, 3, f_ValueNr, f_ElementIndex));

							f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);
						
							if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(1, 100, 0, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

										f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex, true))
											{
											::sprintf(f_Char, "Random");

											f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											throw; //add debug message variable value range not found, empty var recording
#if 0
											f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

											if(acRecordStrengthVar(VAR_DEF_TYPE_SYSTEM, f_Line, f_ValueNr, f_ElementIndex))
												{
												std::string f_SysName = f_NameString;

												f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

												if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

															::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

															if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

																::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

																if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex))
																	{
																	::sprintf(f_Char, "Random");
																	}
																else
																	{
																	throw; //add debug message sys var not processed
																	}
																}
															}
														}
													}

												f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
												}
#endif
											}
										}
									}
								}
							}
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						//String Parameter
						if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING), f_ElementIndex) == true)
							{
							std::string f_ValueNr = f_ValueString;

							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(0, 1, 0, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);
						
								if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(1, 100, 0, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(100, 5000, 0, 2, 3, f_ValueNr, f_ElementIndex));

										f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
											{
											f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

											::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

											f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

											if(acRecordStrengthVarString(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex, true))
												{
												::sprintf(f_Char, "Random");

												f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
												}
											else
												{
#if 0
												f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

												if(acRecordStrengthVarString(VAR_DEF_TYPE_SYSTEM, f_Line, f_ValueNr, f_ElementIndex))
													{
													std::string f_SysName = f_NameString;

													f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

													if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Line, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

														if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Line, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

															::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

															if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Line, f_ValueNr, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

																::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

																if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Line, f_ValueNr, f_ElementIndex))
																	{
																	f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

																	::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																	}
																else
																	{
																	f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

																	if(acRecordStrengthVarString(VAR_DEF_TYPE_RANDOM, f_Line, f_ValueNr, f_ElementIndex))
																		{
																		::sprintf(f_Char, "Random");
																		}
																	else
																		{
																		throw; //add debug message sys var not processed
																		}
																	}
																}
															}
														}

													f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
													}
#endif
												}
											}
										}
									}
								}
							}
						}
					}
				}
			else // no value number
				{
				char f_Char[150];
				FillChar(f_Char, 150);

				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				//Float Parameter no raw value
				if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT), f_ElementIndex) == true)
					{
					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%";
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					//Int Parameter no raw value
					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
						{
						f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%";
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						//String Parameter no raw value
						if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%";
							}
						else
							{
							throw; //add debug message type slicing
							}
						}
					}
				} //end no number
			} // END TYPE 'Sys'
		else
			{ // ClassVar Singles
			f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

			ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

			if(f_SIndex_Typ == ESL_MORF_TYPE_CLSVAR)
				{
				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				ac_recordMeasurementBLTV1(2, 0, true, f_ElementIndex);

				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				f_StringA += "ClassVar%%" + f_TypeString + "&&" + f_VarName + "%%";
				}
			else
				{
				throw; //add debug message SIndex Type out of bounds
				}
			}
		}

	return f_StringA;
}

std::string classTarget_Ecom::acGen_Var_fromHesh(void)
{	
	std::string f_NameString = ac_takeMeasurement(-1, -1, -1, -1);
	std::string f_TypeString = ac_takeMeasurement(-1, -1, -1, -1);

	std::string f_VarName = f_NameString;

	bool f_SValueOn = ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1);
	//END Input

	std::string f_StringA = "";

	//Varso...!
	if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
		{
		if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
			{
			char f_Char[150];
			FillChar(f_Char, 150);

			//Float Parameter
			if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
				{
				if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, -1, -1, -1, -1))
					{
					::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(-1, -1, -1, -1, 0.0f, 1.0f, 0.0f, 2));

					f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
					}
				else
					{
					if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, -1, -1, -1, -1))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(-1, -1, -1, -1, 1.0f, 100.0f, 0.0f, 2));

						f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, -1, -1, -1, -1))
							{
							::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(, -1, -1, -1, -1, 100.0f, 5000.0f, 0.0f, 2));

							f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, -1, -1, -1, -1))
								{
								::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(-1, -1, -1, -1, 100.0f, 5000.0f, 0.0f, 2));

								f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, -1, -1, -1, -1))
									{
									::sprintf(f_Char, "Random");

									f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									throw; //add debug message variable value range not found, empty var recording
									}
								}
							}
						}
					}
				}
			else
				{
				//Int Parameter
				if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
					{
					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, -1, -1, -1, -1))
						{
						::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(-1, -1, -1, -1, 0, 1, 0, 2));

						f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, -1, -1, -1, -1))
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(-1, -1, -1, -1, 1, 100, 0, 2));

							f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, -1, -1, -1, -1))
								{
								::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(-1, -1, -1, -1, 100, 5000, 0, 2));

								f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, -1, -1, -1, -1))
									{
									::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(-1, -1, -1, -1, 100.0f, 5000.0f, 0.0f, 2));

									f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, -1, -1, -1, -1))
										{
										::sprintf(f_Char, "Random");

										f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										throw; //add debug message variable value range not found, empty var recording
										}
									}
								}
							}
						}
					}
				else
					{ //String Parameter
					if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
						{
						if(acFactorStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, -1, -1, -1, -1))
							{
							::sprintf(f_Char, "%s", ac_takeMeasurementINTV1(-1, -1, -1, -1, 0, 1, 0, 2));

							f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							if(acFactorStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, -1, -1, -1, -1))
								{
								::sprintf(f_Char, "%s", ac_takeMeasurementINTV1(-1, -1, -1, -1, 1, 100, 0, 2));

								f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								if(acFactorStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, -1, -1, -1, -1))
									{
									::sprintf(f_Char, "%s", ac_takeMeasurementINTV1(-1, -1, -1, -1, 100, 5000, 0, 2));

									f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									if(acFactorStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, -1, -1, -1, -1))
										{
										::sprintf(f_Char, "%s", ac_takeMeasurementINTV1(-1, -1, -1, -1, 100.0f, 5000.0f, 0.0f, 2));

										f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										if(acFactorStrengthVarString(VAR_DEF_TYPE_RANDOM, -1, -1, -1, -1))
											{
											::sprintf(f_Char, "Random");

											f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											throw; //add debug message variable value range not found, empty var recording
											}
										}
									}
								}
							}
						}
					}
				}
			}
		else  // no value number
			{ // Float Parameter no raw value
			if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
				{
				f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%";
				}
			else
				{ //Int Parameter no raw value
				if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
					{
					f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%";
					}
				else
					{ //String Parameter no raw value
					if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
						{
						f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%";
						}
					else
						{
						throw; //add debug message type slicing
						}
					}
				}
			} //end no number
		} //END TYPE 'Var'
	else
		{ //Systema...! 'Sys'
		if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
			{
			if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
				{
				char f_Char[150];
				FillChar(f_Char, 150);

				//Float Parameter
				if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
					{
					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, -1, -1, -1, -1))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(-1, -1, -1, -1, 0.0f, 1.0f, 0.0f, 2));

						f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, -1, -1, -1, -1))
							{
							::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(-1, -1, -1, -1, 1.0f, 100.0f, 0.0f, 2));

							f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, -1, -1, -1, -1))
								{
								::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(-1, -1, -1, -1, 100.0f, 5000.0f, 0.0f, 2));

								f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, -1, -1, -1, -1))
									{
									::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(-1, -1, -1, -1, 100.0f, 5000.0f, 0.0f, 2));

									f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, -1, -1, -1, -1))
										{
										::sprintf(f_Char, "Random");

										f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										throw; //add debug message variable value range not found, empty var recording
										}
									}
								}
							}
						}
					}
				else //INT SYS
					{//Int Parameter
					if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
						{
						if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, -1, -1, -1, -1))
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(-1, -1, -1, -1, 0, 1, 0, 2));

							f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, -1, -1, -1, -1))
								{
								::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(-1, -1, -1, -1, 1, 100, 0, 2));

								f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, -1, -1, -1, -1))
									{
									::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(-1, -1, -1, -1, 100, 5000, 0, 2));

									f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, -1, -1, -1, -1))
										{
										::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(-1, -1, -1, -1, 100.0f, 5000.0f, 0.0f, 2));

										f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, -1, -1, -1, -1))
											{
											::sprintf(f_Char, "Random");

											f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											throw; //add debug message variable value range not found, empty var recording
											}
										}
									}
								}
							}
						}
					else
						{ //String Parameter
						if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
							{
							if(acFactorStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, -1, -1, -1, -1))
								{
								::sprintf(f_Char, "%s", ac_takeMeasurementINTV1(-1, -1, -1, -1, 0, 1, 0, 2));

								f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								if(acFactorStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, -1, -1, -1, -1))
									{
									::sprintf(f_Char, "%s", ac_takeMeasurementINTV1(-1, -1, -1, -1, 1, 100, 0, 2));

									f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									if(acFactorStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, -1, -1, -1, -1))
										{
										::sprintf(f_Char, "%s", ac_takeMeasurementINTV1(-1, -1, -1, -1, 100, 5000, 0, 2));

										f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										if(acFactorStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, -1, -1, -1, -1))
											{
											::sprintf(f_Char, "%s", ac_takeMeasurementINTV1(-1, -1, -1, -1, 100.0f, 5000.0f, 0.0f, 2));

											f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											if(acFactorStrengthVarString(VAR_DEF_TYPE_RANDOM, -1, -1, -1, -1))
												{
												::sprintf(f_Char, "Random");

												f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
												}
											else
												{
												throw; //add wild debug message
												}
											}
										}
									}
								}
							}
						}
					}
				}
			else // no value number
				{ //Float Parameter no raw value
				if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
					{
					f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%";
					}
				else
					{ //Int Parameter no raw value
					if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
						{
						f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%";
						}
					else
						{ //String Parameter no raw value
						if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
							{
							f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%";
							}
						else
							{
							throw; //add debug message type slicing
							}
						}
					}
				} //end no number
			} // END TYPE 'Sys'
		else
			{ // ClassVar Singles
			if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
				{
				f_StringA += "ClassVar%%" + f_TypeString + "&&" + f_VarName + "%%";
				}
			else
				{
				throw; //add debug message SIndex Type out of bounds
				}
			}
		}

	return f_StringA;
}

std::shared_ptr<Qcom_eslfunction> classLMap::acGen_com_function_FromEcom(std::shared_ptr<Qcom_eslfunction> f_Save_Com_Function, int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target)
{
	int f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	int f_FunctionType = ac_recordMeasurementINTV1(1, 3, 0, 3, 2, 1/*f_Save_Com_Function->m_typed-UNUSED*/, f_ElementStartAD);

	int f_StartLineCount = f_Save_Com_Function->m_vec_InitLineOrdered.size();
		
	std::shared_ptr<classFunction> f_Function = std::make_shared<classFunction>();

	f_Function->m_Type = f_FunctionType;

	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	f_Function->m_Name = ac_recordMeasurement(f_Save_Com_Function->m_name, f_ElementStartAD, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
		
	std::string f_StringA = "FuncDef%%" + f_Function->m_Name + "&*ECNMiner_Affinity%%";
	//f_StringA += ESL_LINE_ENDING;

	std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringA, ESL_INSTA_TYPE_FUNC_DEF);

	f_Function->m_vec_Insta.push_back(f_Insta);
	f_Function->m_idx_vec_Insta++;

	std::string f_StartLine = f_Save_Com_Function->m_StartLine;

	std::vector<std::vector<std::string>> f_StartMorf = ac_ext_eslLine_morf_array(f_StartLine);

	std::vector<int> f_vec_SingleVCVS;
	f_vec_SingleVCVS.clear();

	std::vector<int> f_vec_SingleVCVS_Typ;
	f_vec_SingleVCVS_Typ.clear();

	std::vector<bool> f_vec_SingleVCVS_Number;
	f_vec_SingleVCVS_Number.clear();

	int f_ArgumentCount = 0;
	int f_SingleIndex = 3;

	while(f_SingleIndex < f_StartMorf.size())
		{
		std::string f_PositionOne = f_StartMorf[f_SingleIndex][0];

		if((f_PositionOne.compare("Var") == 0))
			{
			f_ArgumentCount++;

			f_vec_SingleVCVS.push_back(f_SingleIndex);
			f_vec_SingleVCVS_Typ.push_back(ESL_MORF_TYPE_VAR);

			f_SingleIndex += 3;

			if(f_SingleIndex < f_StartMorf.size())
				{
				std::string f_PositionNumber = f_StartMorf[f_SingleIndex][1];

				if(f_PositionNumber.compare("&%") == 0)
					{
					f_vec_SingleVCVS_Number.push_back(true);

					f_SingleIndex++;
					}
				else
					{
					f_vec_SingleVCVS_Number.push_back(false);
					}
				}
			}
		else if (f_PositionOne.compare("Sys") == 0)
			{
			f_ArgumentCount++;

			f_vec_SingleVCVS.push_back(f_SingleIndex);
			f_vec_SingleVCVS_Typ.push_back(ESL_MORF_TYPE_SYS);

			if(f_SingleIndex < f_StartMorf.size())
				{
				std::string f_PositionNumber = f_StartMorf[f_SingleIndex][1];

				if(f_PositionNumber.compare("&%") == 0)
					{
					f_vec_SingleVCVS_Number.push_back(true);

					f_SingleIndex++;
					}
				else
					{
					f_vec_SingleVCVS_Number.push_back(false);
					}
				}
			}
		else if (f_PositionOne.compare("ClassVar") == 0)
			{
			f_ArgumentCount++;

			f_vec_SingleVCVS.push_back(f_SingleIndex);
			f_vec_SingleVCVS_Typ.push_back(ESL_MORF_TYPE_CLSVAR);
			f_vec_SingleVCVS_Number.push_back(false);

			f_SingleIndex += 3;
			}
		else
			{
			f_SingleIndex++;
			}
		}

	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	f_ArgumentCount = ac_recordMeasurementINTV1(0, 2, 0, 3, 4, f_ArgumentCount, f_ElementIndex);

	for(int f_Int = 0; f_Int < f_ArgumentCount; f_Int++)
		{
		int f_SingIndex = f_vec_SingleVCVS[f_Int];
		int f_SIndex_Typ = f_vec_SingleVCVS_Typ[f_Int];
		std::string f_TypeString = f_StartMorf[f_SingIndex + 1][0];
		std::string f_NameString = f_StartMorf[f_SingIndex + 2][0];
		std::string f_ValueString = "";

		if(f_vec_SingleVCVS_Number[f_Int] == true)
			{
			f_ValueString = f_StartMorf[f_SingIndex + 3][0];
			}

		std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_NameString, ESL_INSTA_TYPE_VAR_DEF);

		f_Function->m_vec_Insta.push_back(f_Insta);
		f_Function->m_idx_vec_Insta++;

		std::string f_StringA = acGen_Var_fromEcom(f_SingIndex, f_SIndex_Typ, f_vec_SingleVCVS_Number[f_Int],

#if 0
		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		std::string f_VarName = ac_recordMeasurement(f_NameString, f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_VarName, ESL_INSTA_TYPE_VAR_DEF);

		f_Function->m_vec_Insta.push_back(f_Insta);
		f_Function->m_idx_vec_Insta++;

		//Varso...!
		if(f_SIndex_Typ == ESL_MORF_TYPE_VAR)
			{
			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementBLTV1(2, 0, true, f_ElementIndex);

			if(f_vec_SingleVCVS_Number[f_Int] == true)
				{
				char f_Char[150];
				FillChar(f_Char, 150);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(2, 0, true, f_ElementIndex);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				//Float Parameter
				if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT), f_ElementIndex) == true)
					{
					float f_ValueNr = atof(f_ValueString.c_str());

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

						f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
						
						if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

							f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex, true))
										{
										::sprintf(f_Char, "Random");

										f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										throw; //add debug message variable value range not found, empty var recording
#if 0
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_SYSTEM, f_StartLine, f_ValueNr, f_ElementIndex))
											{
											std::string f_SysName = f_NameString;

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex))
																{
																::sprintf(f_Char, "Random");
																}
															else
																{
																throw; //add debug message sys var not processed
																}
															}
														}
													}
												}

											f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
											}
#endif
										}
									}
								}
							}
						}
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					//Int Parameter
					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
						{
						int f_ValueNr = atoi(f_ValueString.c_str());

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(0, 1, 0, 2, 3, f_ValueNr, f_ElementIndex));

							f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
						
							if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(1, 100, 0, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

										f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex, true))
											{
											::sprintf(f_Char, "Random");

											f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											throw; //add debug message variable value range not found, empty var recording
#if 0
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(acRecordStrengthVar(VAR_DEF_TYPE_SYSTEM, f_StartLine, f_ValueNr, f_ElementIndex))
												{
												std::string f_SysName = f_NameString;

												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex))
																	{
																	::sprintf(f_Char, "Random");
																	}
																else
																	{
																	throw; //add debug message sys var not processed
																	}
																}
															}
														}
													}

												f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
												}
#endif
											}
										}
									}
								}
							}
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						//String Parameter
						if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING), f_ElementIndex) == true)
							{
							std::string f_ValueNr = f_ValueString;

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(0, 1, 0, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
						
								if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(1, 100, 0, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(100, 5000, 0, 2, 3, f_ValueNr, f_ElementIndex));

										f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

											f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(acRecordStrengthVarString(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex, true))
												{
												::sprintf(f_Char, "Random");

												f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
												}
											else
												{
												throw; //add debug message variable value range not found, empty var recording
#if 0
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVarString(VAR_DEF_TYPE_SYSTEM, f_StartLine, f_ValueNr, f_ElementIndex))
													{
													std::string f_SysName = f_NameString;

													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																	}
																else
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	if(acRecordStrengthVarString(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex))
																		{
																		::sprintf(f_Char, "Random");
																		}
																	else
																		{
																		throw; //add debug message sys var not processed
																		}
																	}
																}
															}
														}

													f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
													}
#endif
												}
											}
										}
									}
								}
							}
						}
					}
				}
			else // no value number
				{
				char f_Char[150];
				FillChar(f_Char, 150);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				//Float Parameter no raw value
				if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT), f_ElementIndex) == true)
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%";
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					//Int Parameter no raw value
					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
						{
						f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%";
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						//String Parameter no raw value
						if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							f_StringA += "Var%%" + f_TypeString + "&&" + f_VarName + "%%";
							}
						else
							{
							throw; //add debug message type slicing
							}
						}
					}
				} //end no number
			} //END TYPE 'Var'
		else
			{ //Systema...! 'Sys'
			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

			if(f_SIndex_Typ == ESL_MORF_TYPE_SYS)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(2, 0, true, f_ElementIndex);

				if(f_vec_SingleVCVS_Number[f_Int] == true)
					{
					char f_Char[150];
					FillChar(f_Char, 150);

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(2, 0, true, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					//Float Parameter
					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT), f_ElementIndex) == true)
						{
						float f_ValueNr = atof(f_ValueString.c_str());

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

							f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
						
							if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

										f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex, true))
											{
											::sprintf(f_Char, "Random");

											f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											throw; //add debug message variable value range not found, empty var recording
#if 0
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(acRecordStrengthVar(VAR_DEF_TYPE_SYSTEM, f_StartLine, f_ValueNr, f_ElementIndex))
												{
												std::string f_SysName = f_NameString;

												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex))
																	{
																	::sprintf(f_Char, "Random");
																	}
																else
																	{
																	throw; //add debug message sys var not processed
																	}
																}
															}
														}
													}

												f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
												}
#endif
											}
										}
									}
								}
							}
						}
					else //INT SYS
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						//Int Parameter
						if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
							{
							int f_ValueNr = atoi(f_ValueString.c_str());

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(0, 1, 0, 2, 3, f_ValueNr, f_ElementIndex));

								f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
						
								if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(1, 100, 0, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 3, f_ValueNr, f_ElementIndex));

										f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

											f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex, true))
												{
												::sprintf(f_Char, "Random");

												f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
												}
											else
												{
												throw; //add debug message variable value range not found, empty var recording
#if 0
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVar(VAR_DEF_TYPE_SYSTEM, f_StartLine, f_ValueNr, f_ElementIndex))
													{
													std::string f_SysName = f_NameString;

													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	::sprintf(f_Char, "%i", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																	}
																else
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex))
																		{
																		::sprintf(f_Char, "Random");
																		}
																	else
																		{
																		throw; //add debug message sys var not processed
																		}
																	}
																}
															}
														}

													f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
													}
#endif
												}
											}
										}
									}
								}
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							//String Parameter
							if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING), f_ElementIndex) == true)
								{
								std::string f_ValueNr = f_ValueString;

								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(0, 1, 0, 2, 3, f_ValueNr, f_ElementIndex));

									f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
						
									if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(1, 100, 0, 2, 3, f_ValueNr, f_ElementIndex));

										f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(100, 5000, 0, 2, 3, f_ValueNr, f_ElementIndex));

											f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												::sprintf(f_Char, "%s", ac_recordMeasurementINTV1(100.0f, 5000.0f, 0.0f, 2, 3, f_ValueNr, f_ElementIndex));

												f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVarString(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex, true))
													{
													::sprintf(f_Char, "Random");

													f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%" + f_Char + "&%";
													}
												else
													{
#if 0
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVarString(VAR_DEF_TYPE_SYSTEM, f_StartLine, f_ValueNr, f_ElementIndex))
														{
														std::string f_SysName = f_NameString;

														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_StartLine, f_ValueNr, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_StartLine, f_ValueNr, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_StartLine, f_ValueNr, f_ElementIndex))
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																	}
																else
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_StartLine, f_ValueNr, f_ElementIndex))
																		{
																		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																		::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
																		}
																	else
																		{
																		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																		if(acRecordStrengthVarString(VAR_DEF_TYPE_RANDOM, f_StartLine, f_ValueNr, f_ElementIndex))
																			{
																			::sprintf(f_Char, "Random");
																			}
																		else
																			{
																			throw; //add debug message sys var not processed
																			}
																		}
																	}
																}
															}

														f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
														}
#endif
													}
												}
											}
										}
									}
								}
							}
						}
					}
				else // no value number
					{
					char f_Char[150];
					FillChar(f_Char, 150);

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					//Float Parameter no raw value
					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT), f_ElementIndex) == true)
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%";
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						//Int Parameter no raw value
						if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
							{
							f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							//String Parameter no raw value
							if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_TypeString), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								f_StringA += "Sys%%" + f_TypeString + "&&" + f_VarName + "%%";
								}
							else
								{
								throw; //add debug message type slicing
								}
							}
						}
					} //end no number
				} // END TYPE 'Sys'
			else
				{ // ClassVar Singles
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(2, 0, false, f_ElementIndex);

				if(f_SIndex_Typ == ESL_MORF_TYPE_CLSVAR)
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(2, 0, true, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					f_StringA += "ClassVar%%" + f_TypeString + "&&" + f_VarName + "%%";
					}
				else
					{
					throw; //add debug message SIndex Type out of bounds
					}
				}
			}
#endif
		}

	f_StringA += "////";
	f_StringA += ESL_LINE_ENDING; //END Function Definition and Parameters

	f_Function->m_vec_String += f_StringA;
		
	acResetLine();

	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	int f_LineIndexCount = 1;
	int f_ElementID = 0;

	bool f_Scan = true;
	while(f_Scan == true)// || ((f_LineIndexCount > 0) && (m_vec_CountLock.size() > 0)))
		{
		bool f_Contact = false;

		std::string f_LineString = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount];

		int f_LineInstaType = acRecordLine(f_LineString);

		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
				
		int f_LineType = ac_recordMeasurementINTV1(0, ESL_INSTA_TYPE_COUNT, 2, 3, 6, f_LineInstaType, f_ElementIndex);

		if(f_LineType == ESL_INSTA_TYPE_VAR_DEF)
			{
#if 0
			//f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			if(1)//acRecordStrength(ESL_INSTA_TYPE_VAR_DEF, f_LineString, f_ElementIndex) == true)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_Name = ac_recordMeasurement(ac_ext_eslLine_morf_array(f_LineString)[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				char f_Char[5000];
				FillChar(f_Char, 5000);

				std::string f_StringB;
				f_StringB.clear();

				 /////////////////////////////////////////////////////////////////////////////
				// Short Hand Extentions for getting ESL info like variable type initially //
				std::string f_Var_Typing_String = ac_ext_eslLine_morf_array(f_LineString)[1][0];
				std::string f_Var_Value_String = ac_ext_eslLine_morf_array(f_LineString)[3][0];

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_Var_Typing_String), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT), f_ElementIndex) == true)
					{
					float f_FloatValue = atof(f_Var_Value_String.c_str());

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

						f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

							f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char + "&%";
							}
						else
							{
							if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

								f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char + "&%";
								}
							else
								{
								if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));
								
									f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char + "&%";
									}
								else
									{
									if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
										{
										::sprintf(f_Char, "Random");

										f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char + "&%";
										}
									else
										{
										std::vector<std::vector<std::string>> f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);
#if 0
										bool f_StanVar = false;

										if(f_morfarray1.size() == ESL_INSTA_TYPE_VAR_DEF_MORF_COUNT)
											{
											if(f_morfarray1[0][0].at(0) == 'V')
												{
												if(f_morfarray2.size() >= ESL_INSTA_TYPE_VAR_DEF_OPER_MORF_COUNT)
													{
													if(f_morfarray2[6][1].at(0) == '*')
														{
														f_StanVar = true;
														}
													}
												}
											}

										if(f_StanVar == true)
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(ac_recordMeasurementBLTV1(1, 0, true, f_ElementIndex) == true)
												{
												std::string f_StringC = "Var%%float&&" + f_Name + "%%0.0&%////" + ESL_LINE_ENDING;

												f_Function->m_vec_String += f_StringC;
												f_LineCount--;
												f_LineIndexCount++;

												f_LineString = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount];
												f_LineString2 = "";

												f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

												if(f_LineIndexCount <= f_Save_Com_Function->m_vec_InitLineOrdered.size() - 2)
													{
													f_LineString2 = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount + 1];
													f_morfarray2 = ac_ext_eslLine_morf_array(f_LineString2);
													}
												}
											}
										else
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											ac_recordMeasurementBLTV1(1, 0, false, f_ElementIndex);
											}
#endif

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										std::string f_VarBCallName = ac_recordMeasurement(f_morfarray1[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										//...?\/
										std::string f_VarBNameFA = acMakeUnisonType(f_Target, f_VarBCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, MuVar_Float, true);

										std::string f_VarBVarSys = "";
										std::string f_VarBType = "";
										std::string f_VarBName = "";

										int f_Stage = 0;

										for(int f_Helly = 0; f_Helly < f_VarBNameFA.length(); f_Helly++)
											{
											char f_c = f_VarBNameFA.at(f_Helly);

											if(f_c == '&' || f_c == '%')
												{
												f_Stage++;
												}
											else
												{
												if(f_Stage == 0)
													{
													f_VarBVarSys.push_back(f_c);
													}
												else if(f_Stage >= 2)
													{
													f_VarBType.push_back(f_c);
													}
												else
													{
													f_VarBName.push_back(f_c);
													}
												}
											}

										char f_1 = f_VarBVarSys.at(0);

										float f_condAssignValurRHS = 0.0f;

										FillChar(f_Char, 5000);

										if(f_VarBName.compare(f_VarBCallName) == 0)
											{
											float f_FloatValue = 0.0f;

											if(f_StanVar == true)
												{
												f_FloatValue = atof(f_morfarray1[3][0].c_str());
												}
											else
												{
												f_FloatValue = atof(f_morfarray1[10][0].c_str());
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												f_condAssignValurRHS = ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex);
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													f_condAssignValurRHS = ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex);
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														f_condAssignValurRHS = ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex);
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															f_condAssignValurRHS = ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex);
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_FloatValue, f_ElementIndex);
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
												
																	f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_FloatValue, f_ElementIndex);
																	}
																else
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
																		{
																		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																		f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_FloatValue, f_ElementIndex);
																		}
																	else
																		{
																		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																		f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_FloatValue, f_ElementIndex);
																		}
																	}
																}
															}
														}
													}
												}
											}

										int f_OperType = agFind_OprType(f_morfarray1[5][0]);

										bool f_Oper_Five[5];

										if(f_OperType == MuOpr_Plus)
											{
											f_Oper_Five[0] = true;
											f_Oper_Five[1] = false;
											f_Oper_Five[2] = false;
											f_Oper_Five[3] = false;
											f_Oper_Five[4] = false;
											}
										else if(f_OperType == MuOpr_Minus)
											{
											f_Oper_Five[0] = false;
											f_Oper_Five[1] = true;
											f_Oper_Five[2] = false;
											f_Oper_Five[3] = false;
											f_Oper_Five[4] = false;
											}
										else if(f_OperType == MuOpr_Equals)
											{
											f_Oper_Five[0] = false;
											f_Oper_Five[1] = false;
											f_Oper_Five[2] = true;
											f_Oper_Five[3] = false;
											f_Oper_Five[4] = false;
											}
										else if(f_OperType == MuOpr_Multiply)
											{
											f_Oper_Five[0] = false;
											f_Oper_Five[1] = false;
											f_Oper_Five[2] = false;
											f_Oper_Five[3] = true;
											f_Oper_Five[4] = false;
											}
										else if(f_OperType == MuOpr_Divide)
											{
											f_Oper_Five[0] = false;
											f_Oper_Five[1] = false;
											f_Oper_Five[2] = false;
											f_Oper_Five[3] = false;
											f_Oper_Five[4] = true;
											}

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[0], f_ElementIndex) == true)
											{
											::sprintf(f_Char, "%f&%Opr%%Plus**Fork1plus%%%s%%%f&%////\n", 0.0f, f_VarBNameFA.c_str(), f_condAssignValurRHS);
											}
										else
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[1], f_ElementIndex) == true)
												{
												::sprintf(f_Char, "%f&%Opr%%Minus**Fork1minus%%%s%%%f&%////\n", 0.0f, f_VarBNameFA.c_str(), f_condAssignValurRHS);
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[2], f_ElementIndex) == true)
													{
													::sprintf(f_Char, "%f&%Opr%%Equals**Fork1equals%%%s%%%f&%////\n", 0.0f, f_VarBNameFA.c_str(), f_condAssignValurRHS);
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[3], f_ElementIndex) == true)
														{
														::sprintf(f_Char, "%f&%Opr%%Mul**Fork1multiply%%%s%%%f&%////\n", 0.0f, f_VarBNameFA.c_str(), f_condAssignValurRHS);
														}
													else
														{
														::sprintf(f_Char, "%f&%Opr%%Div**Fork1divide%%%s%%%f&%////\n", 0.0f, f_VarBNameFA.c_str(), f_condAssignValurRHS);
														}
													}
												}
											}

										f_StringB += "Var%%float&&" + f_Name + "%%" + f_Char;
										}
									}
								}
							}
						}
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_Var_Typing_String), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
						{
						float f_IntValue = atof(f_Var_Value_String.c_str());

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_IntValue, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_IntValue, f_ElementIndex));

							f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_IntValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_IntValue, f_ElementIndex));

								f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_IntValue, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex));

									f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_IntValue, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex));

										f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_LineString, f_IntValue, f_ElementIndex))
											{
											::sprintf(f_Char, "Random");

											f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char + "&%";
											}
										else
											{
											std::vector<std::vector<std::string>> f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

#if 0
											bool f_StanVar = false;

											if(f_morfarray1.size() == ESL_INSTA_TYPE_VAR_DEF_MORF_COUNT)
												{
												if(f_morfarray1[0][0].at(0) == 'V')
													{
													if(f_morfarray2.size() >= ESL_INSTA_TYPE_VAR_DEF_OPER_MORF_COUNT)
														{
														if(f_morfarray2[6][1].at(0) == '*')
															{
															f_StanVar = true;
															}
														}
													}
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(f_StanVar == true)
												{
												if(ac_recordMeasurementBLTV1(1, 0, true, f_ElementIndex) == true)
													{
													std::string f_StringC = "Var%%int&&" + f_Name + "%%0.0&%////" + ESL_LINE_ENDING;

													f_Function->m_vec_String += f_StringC;
													f_LineCount--;
													f_LineIndexCount++;

													f_LineString = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount];
													f_LineString2 = "";

													f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

													if(f_LineIndexCount <= f_Save_Com_Function->m_vec_InitLineOrdered.size() - 2)
														{
														f_LineString2 = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount + 1];
														f_morfarray2 = ac_ext_eslLine_morf_array(f_LineString2);
														}
													}
												}
											else
												{
												ac_recordMeasurementBLTV1(1, 0, false, f_ElementIndex);
												}
#endif

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_VarBCallName = ac_recordMeasurement(f_morfarray1[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_VarBNameFA = acMakeUnisonType(f_Target, f_VarBCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, MuVar_Int, true);

											std::string f_VarBVarSys = "";
											std::string f_VarBType = "";
											std::string f_VarBName = "";

											int f_Stage = 0;

											for(int f_Helly = 0; f_Helly < f_VarBNameFA.length(); f_Helly++)
												{
												char f_c = f_VarBNameFA.at(f_Helly);

												if(f_c == '&' || f_c == '%')
													{
													f_Stage++;
													}
												else
													{
													if(f_Stage == 0)
														{
														f_VarBVarSys.push_back(f_c);
														}
													else if(f_Stage >= 2)
														{
														f_VarBType.push_back(f_c);
														}
													else
														{
														f_VarBName.push_back(f_c);
														}
													}
												}

											char f_1 = f_VarBVarSys.at(0);

											int f_condAssignValurRHS = 0;

											FillChar(f_Char, 5000);

											if(f_VarBName.compare(f_VarBCallName) == 0)
												{
												int f_IntValue = 0;

												if(f_StanVar == true)
													{
													f_IntValue = atoi(f_morfarray1[3][0].c_str());
													}
												else
													{
													f_IntValue = atoi(f_morfarray1[10][0].c_str());
													}

												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_IntValue, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													f_condAssignValurRHS = ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_IntValue, f_ElementIndex);
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_IntValue, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														f_condAssignValurRHS = ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_IntValue, f_ElementIndex);
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_IntValue, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															f_condAssignValurRHS = ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex);
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_IntValue, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
															
																f_condAssignValurRHS = ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex);
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_IntValue, f_ElementIndex))
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_IntValue, f_ElementIndex);
																	}
																else
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_IntValue, f_ElementIndex))
																		{
																		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																		f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_IntValue, f_ElementIndex);
																		}
																	else
																		{
																		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																		if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_IntValue, f_ElementIndex))
																			{
																			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																			f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex);
																			}
																		else
																			{
																			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																			f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex);
																			}
																		}
																	}
																}
															}
														}
													}
												}

											int f_OperType = agFind_OprType(f_morfarray1[5][0]);

											bool f_Oper_Five[5];

											if(f_OperType == MuOpr_Plus)
												{
												f_Oper_Five[0] = true;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Minus)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = true;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Equals)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = true;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Multiply)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = true;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Divide)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = true;
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[0], f_ElementIndex) == true)
												{
												::sprintf(f_Char, "%i&%Opr%%Plus**Fork1plus%%%s%%%i&%////\n", 0, f_VarBNameFA.c_str(), f_condAssignValurRHS);
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[1], f_ElementIndex) == true)
													{
													::sprintf(f_Char, "%i&%Opr%%Minus**Fork1minus%%%s%%%i&%////\n", 0, f_VarBNameFA.c_str(), f_condAssignValurRHS);
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[2], f_ElementIndex) == true)
														{
														::sprintf(f_Char, "%i&%Opr%%Equals**Fork1equals%%%s%%%i&%////\n", 0, f_VarBNameFA.c_str(), f_condAssignValurRHS);
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[3], f_ElementIndex) == true)
															{
															::sprintf(f_Char, "%i&%Opr%%Mul**Fork1multiply%%%s%%%i&%////\n", 0, f_VarBNameFA.c_str(), f_condAssignValurRHS);
															}
														else
															{
															::sprintf(f_Char, "%i&%Opr%%Div**Fork1divide%%%s%%%i&%////\n", 0, f_VarBNameFA.c_str(), f_condAssignValurRHS);
															}
														}
													}
												}

											f_StringB += "Var%%int&&" + f_Name + "%%" + f_Char;
											}
										}
									}
								}
							}
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_Var_Typing_String), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING), f_ElementIndex) == true)
							{
							std::string f_StringValue = f_Var_Value_String;

							std::vector<std::vector<std::string>> f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);
							std::vector<std::vector<std::string>> f_morfarray2 = ac_ext_eslLine_morf_array(f_LineString2);

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_StringValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%c", ac_recordMeasurement(f_StringValue.c_str(), f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth).at(0));

								f_StringB += "Var%%String&&" + f_Name + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_StringValue, f_ElementIndex))
									{
									std::vector<std::string> f_morfStrings;
									f_morfStrings.clear();
									int f_Count = 0;
									std::string f_Carriage;
									f_Carriage.clear();
									for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
										{
										char f_c = f_StringValue.at(f_XY);

										f_Carriage.push_back(f_c);
										f_Count++;

										if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
											{
											f_morfStrings.push_back(f_Carriage);
											f_Carriage.clear();
											}
										}

									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									std::string f_AddString = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

									for(int f_XY = 0; f_XY < f_Count1; f_XY++)
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										f_AddString += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
										}

									f_StringB += "Var%%String&&" + f_Name + "%%" + f_AddString + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_StringValue, f_ElementIndex))
										{
										std::vector<std::string> f_morfStrings;
										f_morfStrings.clear();
										int f_Count = 0;
										std::string f_Carriage;
										f_Carriage.clear();

										for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
											{
											char f_c = f_StringValue.at(f_XY);

											f_Carriage.push_back(f_c);
											f_Count++;

											if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
												{
												f_morfStrings.push_back(f_Carriage);
												f_Carriage.clear();
												}
											}

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										std::string f_AddString = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

										for(int f_XY = 0; f_XY < f_Count1; f_XY++)
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											f_AddString += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex,f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
											}

										f_StringB += "Var%%String&&" + f_Name + "%%" + f_AddString + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_StringValue, f_ElementIndex))
											{
											std::vector<std::string> f_morfStrings;
											f_morfStrings.clear();
											int f_Count = 0;
											std::string f_Carriage;
											f_Carriage.clear();
											for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
												{
												char f_c = f_StringValue.at(f_XY);

												f_Carriage.push_back(f_c);
												f_Count++;

												if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
													{
													f_morfStrings.push_back(f_Carriage);
													f_Carriage.clear();
													}
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_AddString = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

											for(int f_XY = 0; f_XY < f_Count1; f_XY++)
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												f_AddString += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
												}

											f_StringB += "Var%%String&&" + f_Name + "%%" + f_AddString + "&%";
											}
										else
											{
											std::vector<std::vector<std::string>> f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

#if 0
											bool f_StanVar = false;

											if(f_morfarray1.size() == ESL_INSTA_TYPE_VAR_DEF_MORF_COUNT)
												{
												if(f_morfarray1[0][0].at(0) == 'V')
													{
													if(f_morfarray2.size() >= ESL_INSTA_TYPE_VAR_DEF_OPER_MORF_COUNT)
														{
														if(f_morfarray2[6][1].at(0) == '*')
															{
															f_StanVar = true;
															}
														}
													}
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(f_StanVar == true)
												{
												if(ac_recordMeasurementBLTV1(1, 0, true, f_ElementIndex) == true)
													{
													std::string f_StringC = "Var%%String&&" + f_Name + "%%Empty&%////" + ESL_LINE_ENDING;

													std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringC, ESL_INSTA_TYPE_VAR_DEF);

													f_Function->m_vec_Insta.push_back(f_Insta);
													f_Function->m_idx_vec_Insta++;

													f_Function->m_vec_String += f_StringC;
													f_LineCount--;
													f_LineIndexCount++;

													f_LineString = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount];
													f_LineString2 = "";

													f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

													if(f_LineIndexCount <= f_Save_Com_Function->m_vec_InitLineOrdered.size() - 2)
														{
														f_LineString2 = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount + 1];
														f_morfarray2 = ac_ext_eslLine_morf_array(f_LineString2);
														}
													}
												}
											else
												{
												ac_recordMeasurementBLTV1(1, 0, false, f_ElementIndex);
												}
#endif

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_VarBCallName = ac_recordMeasurement(f_morfarray1[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_VarBNameFA = acMakeUnisonType(f_Target, f_VarBCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, MuVar_Int, true);

											std::string f_VarBVarSys = "";
											std::string f_VarBType = "";
											std::string f_VarBName = "";

											int f_Stage = 0;

											for(int f_Helly = 0; f_Helly < f_VarBNameFA.length(); f_Helly++)
												{
												char f_c = f_VarBNameFA.at(f_Helly);

												if(f_c == '&' || f_c == '%')
													{
													f_Stage++;
													}
												else
													{
													if(f_Stage == 0)
														{
														f_VarBVarSys.push_back(f_c);
														}
													else if(f_Stage >= 2)
														{
														f_VarBType.push_back(f_c);
														}
													else
														{
														f_VarBName.push_back(f_c);
														}
													}
												}

											char f_1 = f_VarBVarSys.at(0);

											std::string f_condAssignValurRHS = "";

											FillChar(f_Char, 5000);

											if(f_VarBName.compare(f_VarBCallName) == 0)
												{
												std::string f_StringValue = "";

												/*if(f_StanVar == true)
													{
													f_StringValue = f_morfarray2[3][0];
													}
												else
													{*/
													f_StringValue = f_morfarray2[10][0];
													//}

												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_StringValue, f_ElementIndex))
													{
													std::string f_AddString;
													f_AddString.clear();
													std::vector<std::string> f_morfStrings;
													f_morfStrings.clear();
													int f_Count = 0;
													std::string f_Carriage;
													f_Carriage.clear();
													for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
														{
														char f_c = f_StringValue.at(f_XY);

														f_Carriage.push_back(f_c);
														f_Count++;

														if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
															{
															f_morfStrings.push_back(f_Carriage);
															f_Carriage.clear();
															}
														}

													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

													for(int f_XY = 0; f_XY < f_Count1; f_XY++)
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
														}

													f_condAssignValurRHS = f_AddString1;
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_StringValue, f_ElementIndex))
														{
														std::string f_AddString;
														f_AddString.clear();
														std::vector<std::string> f_morfStrings;
														f_morfStrings.clear();
														int f_Count = 0;
														std::string f_Carriage;
														f_Carriage.clear();
														for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
															{
															char f_c = f_StringValue.at(f_XY);

															f_Carriage.push_back(f_c);
															f_Count++;

															if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
																{
																f_morfStrings.push_back(f_Carriage);
																f_Carriage.clear();
																}
															}

														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

														for(int f_XY = 0; f_XY < f_Count1; f_XY++)
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
															}

														f_condAssignValurRHS = f_AddString;
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_StringValue, f_ElementIndex))
															{
															std::string f_AddString;
															f_AddString.clear();
															std::vector<std::string> f_morfStrings;
															f_morfStrings.clear();
															int f_Count = 0;
															std::string f_Carriage;
															f_Carriage.clear();
															for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
																{
																char f_c = f_StringValue.at(f_XY);

																f_Carriage.push_back(f_c);
																f_Count++;

																if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
																	{
																	f_morfStrings.push_back(f_Carriage);
																	f_Carriage.clear();
																	}
																}

															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

															for(int f_XY = 0; f_XY < f_Count1; f_XY++)
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
																}

															f_condAssignValurRHS = f_AddString;
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_StringValue, f_ElementIndex))
																{
																std::string f_AddString;
																f_AddString.clear();
																std::vector<std::string> f_morfStrings;
																f_morfStrings.clear();
																int f_Count = 0;
																std::string f_Carriage;
																f_Carriage.clear();
																for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
																	{
																	char f_c = f_StringValue.at(f_XY);

																	f_Carriage.push_back(f_c);
																	f_Count++;

																	if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
																		{
																		f_morfStrings.push_back(f_Carriage);
																		f_Carriage.clear();
																		}
																	}

																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

																for(int f_XY = 0; f_XY < f_Count1; f_XY++)
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
																	}

																f_condAssignValurRHS = f_AddString1;
																}
															}
														}
													}
												}

											int f_OperType = agFind_OprType(f_morfarray1[5][0]);

											bool f_Oper_Five[5];

											if(f_OperType == MuOpr_Plus)
												{
												f_Oper_Five[0] = true;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Minus)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = true;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Equals)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = true;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Multiply)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = true;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Divide)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = true;
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[0], f_ElementIndex) == true)
												{
												::sprintf(f_Char, "%s&%Opr%%Plus**Fork1plus%%%s%%%s&%////\n", "Empty", f_VarBNameFA.c_str(), f_condAssignValurRHS);
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[1], f_ElementIndex) == true)
													{
													::sprintf(f_Char, "%s&%Opr%%Minus**Fork1minus%%%s%%%s&%////\n", "Empty", f_VarBNameFA.c_str(), f_condAssignValurRHS);
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[2], f_ElementIndex) == true)
														{
														::sprintf(f_Char, "%s&%Opr%%Equals**Fork1equals%%%s%%%s&%////\n", "Empty", f_VarBNameFA.c_str(), f_condAssignValurRHS);
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[3], f_ElementIndex) == true)
															{
															::sprintf(f_Char, "%s&%Opr%%Mul**Fork1multiply%%%s%%%s&%////\n", "Empty", f_VarBNameFA.c_str(), f_condAssignValurRHS);
															}
														else
															{
															::sprintf(f_Char, "%s&%Opr%%Div**Fork1divide%%%s%%%s&%////\n", "Empty", f_VarBNameFA.c_str(), f_condAssignValurRHS);
															}

														f_StringB += "Var%%String&&" + f_Name + "%%" + f_Char;
														}
													}
												}
											}

										f_StringB += ESL_LINE_ENDING;

										std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringB, ESL_INSTA_TYPE_VAR_DEF);

										f_Function->m_vec_Insta.push_back(f_Insta);
										f_Function->m_idx_vec_Insta++;

										f_Function->m_vec_String += f_StringB;
										f_LineCount--;
					
										f_Contact = true;
										}
									}
								}
							}
						}
					}
				}
			}
		else if(f_LineType == ESL_INSTA_TYPE_SYS_DEF)
			{
			//f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			if(1)//acRecordStrength(ESL_INSTA_TYPE_SYS_DEF, f_Function, f_LineString, f_ElementIndex) == true)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_Name = ac_recordMeasurement(ac_ext_eslLine_morf_array(f_LineString)[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				char f_Char[5000];
				FillChar(f_Char, 5000);

				std::string f_StringB;
				f_StringB.clear();

					/////////////////////////////////////////////////////////////////////////////
				// Short Hand Extentions for getting ESL info like variable type initially //
				std::string f_Var_Typing_String = ac_ext_eslLine_morf_array(f_LineString)[1][0];
				std::string f_Var_Value_String = ac_ext_eslLine_morf_array(f_LineString)[3][0];

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_Var_Typing_String), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT), f_ElementIndex) == true)
					{
					float f_FloatValue = atof(f_Var_Value_String.c_str());

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

						f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char + "&%";
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

							f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

								f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

									f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
										{
										::sprintf(f_Char, "Random");

										f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char + "&%";
										}
									else
										{
										std::vector<std::vector<std::string>> f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

#if 0
										bool f_StanVar = false;

										if(f_morfarray1.size() == ESL_INSTA_TYPE_SYS_DEF_MORF_COUNT)
											{
											if(f_morfarray1[0][0].at(0) == 'V')
												{
												if(f_morfarray2.size() >= ESL_INSTA_TYPE_SYS_DEF_OPER_MORF_COUNT)
													{
													if(f_morfarray2[6][1].at(0) == '*')
														{
														f_StanVar = true;
														}
													}
												}
											}

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(f_StanVar == true)
											{
											if(ac_recordMeasurementBLTV1(1, 0, true, f_ElementIndex) == true)
												{
												std::string f_StringC = "Sys%%float&&" + f_Name + "%%0.0&%////" + ESL_LINE_ENDING;

												std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringC, ESL_INSTA_TYPE_SYS_DEF);

												f_Function->m_vec_Insta.push_back(f_Insta);
												f_Function->m_idx_vec_Insta++;

												f_Function->m_vec_String += f_StringC;
												f_LineCount--;
												f_LineIndexCount++;

												f_LineString = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount];
												f_LineString2 = "";

												f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

												if(f_LineIndexCount <= f_Save_Com_Function->m_vec_InitLineOrdered.size() - 2)
													{
													f_LineString2 = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount + 1];
													f_morfarray2 = ac_ext_eslLine_morf_array(f_LineString2);
													}
												}
											}
										else
											{
											ac_recordMeasurementBLTV1(1, 0, false, f_ElementIndex);
											}
#endif

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										std::string f_VarBCallName = ac_recordMeasurement(f_morfarray1[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										std::string f_VarBNameFA = acMakeUnisonType(f_Target, f_VarBCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, MuVar_Float, true);

										std::string f_VarBVarSys = "";
										std::string f_VarBType = "";
										std::string f_VarBName = "";

										int f_Stage = 0;

										for(int f_Helly = 0; f_Helly < f_VarBNameFA.length(); f_Helly++)
											{
											char f_c = f_VarBNameFA.at(f_Helly);

											if(f_c == '&' || f_c == '%')
												{
												f_Stage++;
												}
											else
												{
												if(f_Stage == 0)
													{
													f_VarBVarSys.push_back(f_c);
													}
												else if(f_Stage >= 2)
													{
													f_VarBType.push_back(f_c);
													}
												else
													{
													f_VarBName.push_back(f_c);
													}
												}
											}

										char f_1 = f_VarBVarSys.at(0);

										float f_condAssignValurRHS = 0.0f;

										FillChar(f_Char, 5000);

										if(f_VarBName.compare(f_VarBCallName) == 0)
											{
											float f_FloatValue = 0.0f;

											if(f_StanVar == true)
												{
												f_FloatValue = atof(f_morfarray2[3][0].c_str());
												}
											else
												{
												f_FloatValue = atof(f_morfarray2[10][0].c_str());
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												f_condAssignValurRHS = ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex);
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													f_condAssignValurRHS = ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex);
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														f_condAssignValurRHS = ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex);
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															f_condAssignValurRHS = ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex);
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_FloatValue, f_ElementIndex);
																}
															else
																{
																if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_FloatValue, f_ElementIndex);
																	}
																else
																	{
																	if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
																		{
																		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																		f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_FloatValue, f_ElementIndex);
																		}
																	else
																		{
																		f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_FloatValue, f_ElementIndex);
																		}
																	}
																}
															}
														}
													}
												}
											}

										int f_OperType = agFind_OprType(f_morfarray1[5][0]);

										bool f_Oper_Five[5];

										if(f_OperType == MuOpr_Plus)
											{
											f_Oper_Five[0] = true;
											f_Oper_Five[1] = false;
											f_Oper_Five[2] = false;
											f_Oper_Five[3] = false;
											f_Oper_Five[4] = false;
											}
										else if(f_OperType == MuOpr_Minus)
											{
											f_Oper_Five[0] = false;
											f_Oper_Five[1] = true;
											f_Oper_Five[2] = false;
											f_Oper_Five[3] = false;
											f_Oper_Five[4] = false;
											}
										else if(f_OperType == MuOpr_Equals)
											{
											f_Oper_Five[0] = false;
											f_Oper_Five[1] = false;
											f_Oper_Five[2] = true;
											f_Oper_Five[3] = false;
											f_Oper_Five[4] = false;
											}
										else if(f_OperType == MuOpr_Multiply)
											{
											f_Oper_Five[0] = false;
											f_Oper_Five[1] = false;
											f_Oper_Five[2] = false;
											f_Oper_Five[3] = true;
											f_Oper_Five[4] = false;
											}
										else if(f_OperType == MuOpr_Divide)
											{
											f_Oper_Five[0] = false;
											f_Oper_Five[1] = false;
											f_Oper_Five[2] = false;
											f_Oper_Five[3] = false;
											f_Oper_Five[4] = true;
											}

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[0], f_ElementIndex) == true)
											{
											::sprintf(f_Char, "%f&%Opr%%Plus**Fork1plus%%%s%%%f&%////\n", 0.0f, f_VarBNameFA.c_str(), f_condAssignValurRHS);
											}
										else
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[1], f_ElementIndex) == true)
												{
												::sprintf(f_Char, "%f&%Opr%%Minus**Fork1minus%%%s%%%f&%////\n", 0.0f, f_VarBNameFA.c_str(), f_condAssignValurRHS);
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[2], f_ElementIndex) == true)
													{
													::sprintf(f_Char, "%f&%Opr%%Equals**Fork1equals%%%s%%%f&%////\n", 0.0f, f_VarBNameFA.c_str(), f_condAssignValurRHS);
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[3], f_ElementIndex) == true)
														{
														::sprintf(f_Char, "%f&%Opr%%Mul**Fork1multiply%%%s%%%f&%////\n", 0.0f, f_VarBNameFA.c_str(), f_condAssignValurRHS);
														}
													else
														{
														::sprintf(f_Char, "%f&%Opr%%Div**Fork1divide%%%s%%%f&%////\n", 0.0f, f_VarBNameFA.c_str(), f_condAssignValurRHS);
														}
													}
												}
											}

										f_StringB += "Sys%%float&&" + f_Name + "%%" + f_Char;
										}
									}
								}
							}
						}
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_Var_Typing_String), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT), f_ElementIndex) == true)
						{
						float f_IntValue = atof(f_Var_Value_String.c_str());

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_IntValue, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_IntValue, f_ElementIndex));

							f_StringB += "Sys%%int&&" + f_Name + "%%" + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_IntValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_IntValue, f_ElementIndex));

								f_StringB += "Sys%%int&&" + f_Name + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_IntValue, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex));

									f_StringB += "Sys%%int&&" + f_Name + "%%" + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_IntValue, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex));

										f_StringB += "Sys%%int&&" + f_Name + "%%" + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_LineString, f_IntValue, f_ElementIndex))
											{
											::sprintf(f_Char, "Random");

											f_StringB += "Sys%%int&&" + f_Name + "%%" + f_Char + "&%";
											}
										else
											{
											std::vector<std::vector<std::string>> f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

#if 0
											bool f_StanVar = false;

											if(f_morfarray1.size() == ESL_INSTA_TYPE_SYS_DEF_MORF_COUNT)
												{
												if(f_morfarray1[0][0].at(0) == 'V')
													{
													if(f_morfarray2.size() >= ESL_INSTA_TYPE_SYS_DEF_OPER_MORF_COUNT)
														{
														if(f_morfarray2[6][1].at(0) == '*')
															{
															f_StanVar = true;
															}
														}
													}
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(f_StanVar == true)
												{
												if(ac_recordMeasurementBLTV1(1, 0, true, f_ElementIndex) == true)
													{
													std::string f_StringC = "Sys%%int&&" + f_Name + "%%0.0&%////" + ESL_LINE_ENDING;

													std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringC, ESL_INSTA_TYPE_SYS_DEF);

													f_Function->m_vec_Insta.push_back(f_Insta);
													f_Function->m_idx_vec_Insta++;

													f_Function->m_vec_String += f_StringC;
													f_LineCount--;
													f_LineIndexCount++;

													f_LineString = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount];
													f_LineString2 = "";

													f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

													if(f_LineIndexCount <= f_Save_Com_Function->m_vec_InitLineOrdered.size() - 2)
														{
														f_LineString2 = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount + 1];
														f_morfarray2 = ac_ext_eslLine_morf_array(f_LineString2);
														}
													}
												}
											else
												{
												ac_recordMeasurementBLTV1(1, 0, false, f_ElementIndex);
												}
#endif

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_VarBCallName = ac_recordMeasurement(f_morfarray1[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_VarBNameFA = acMakeUnisonType(f_Target, f_VarBCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, MuVar_Int, true);

											std::string f_VarBVarSys = "";
											std::string f_VarBType = "";
											std::string f_VarBName = "";

											int f_Stage = 0;

											for(int f_Helly = 0; f_Helly < f_VarBNameFA.length(); f_Helly++)
												{
												char f_c = f_VarBNameFA.at(f_Helly);

												if(f_c == '&' || f_c == '%')
													{
													f_Stage++;
													}
												else
													{
													if(f_Stage == 0)
														{
														f_VarBVarSys.push_back(f_c);
														}
													else if(f_Stage >= 2)
														{
														f_VarBType.push_back(f_c);
														}
													else
														{
														f_VarBName.push_back(f_c);
														}
													}
												}

											char f_1 = f_VarBVarSys.at(0);

											int f_condAssignValurRHS = 0;

											FillChar(f_Char, 5000);

											if(f_VarBName.compare(f_VarBCallName) == 0)
												{
												int f_IntValue = 0;

												/*if(f_StanVar == true)
													{
													f_IntValue = atoi(f_morfarray2[3][0].c_str());
													}
												else
													{*/
													f_IntValue = atoi(f_morfarray2[10][0].c_str());
													//}

												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_IntValue, f_ElementIndex))
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													f_condAssignValurRHS = ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_IntValue, f_ElementIndex);
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_IntValue, f_ElementIndex))
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														f_condAssignValurRHS = ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_IntValue, f_ElementIndex);
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_IntValue, f_ElementIndex))
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															f_condAssignValurRHS = ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex);
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_IntValue, f_ElementIndex))
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																f_condAssignValurRHS = ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex);
																}
															else
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_IntValue, f_ElementIndex))
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_IntValue, f_ElementIndex);
																	}
																else
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_IntValue, f_ElementIndex))
																		{
																		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																		f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_IntValue, f_ElementIndex);
																		}
																	else
																		{
																		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																		if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_IntValue, f_ElementIndex))
																			{
																			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																			f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex);
																			}
																		else
																			{
																			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																			f_condAssignValurRHS = Cube::random() * ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex);
																			}
																		}
																	}
																}
															}
														}
													}
												}

											int f_OperType = agFind_OprType(f_morfarray1[5][0]);

											bool f_Oper_Five[5];

											if(f_OperType == MuOpr_Plus)
												{
												f_Oper_Five[0] = true;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Minus)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = true;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Equals)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = true;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Multiply)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = true;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Divide)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = true;
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[0], f_ElementIndex) == true)
												{
												::sprintf(f_Char, "%i&%Opr%%Plus**Fork1plus%%%s%%%i&%////\n", 0, f_VarBNameFA.c_str(), f_condAssignValurRHS);
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[1], f_ElementIndex) == true)
													{
													::sprintf(f_Char, "%i&%Opr%%Minus**Fork1minus%%%s%%%i&%////\n", 0, f_VarBNameFA.c_str(), f_condAssignValurRHS);
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[2], f_ElementIndex) == true)
														{
														::sprintf(f_Char, "%i&%Opr%%Equals**Fork1equals%%%s%%%i&%////\n", 0, f_VarBNameFA.c_str(), f_condAssignValurRHS);
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[3], f_ElementIndex) == true)
															{
															::sprintf(f_Char, "%i&%Opr%%Mul**Fork1multiply%%%s%%%i&%////\n", 0, f_VarBNameFA.c_str(), f_condAssignValurRHS);
															}
														else
															{
															::sprintf(f_Char, "%i&%Opr%%Div**Fork1divide%%%s%%%i&%////\n", 0, f_VarBNameFA.c_str(), f_condAssignValurRHS);
															}

														f_StringB += "Sys%%int&&" + f_Name + "%%" + f_Char;
														}
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
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(agFind_CurrentSpec_VarType(f_Var_Typing_String), ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING), f_ElementIndex) == true)
							{
							std::string f_StringValue = f_Var_Value_String;

							std::vector<std::vector<std::string>> f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_StringValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%c", ac_recordMeasurement(f_StringValue.c_str(), f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth).at(0));

								f_StringB += "Sys%%String&&" + f_Name + "%%" + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_StringValue, f_ElementIndex))
									{
									std::vector<std::string> f_morfStrings;
									f_morfStrings.clear();
									int f_Count = 0;
									std::string f_Carriage;
									f_Carriage.clear();
									for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
										{
										char f_c = f_StringValue.at(f_XY);

										f_Carriage.push_back(f_c);
										f_Count++;

										if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
											{
											f_morfStrings.push_back(f_Carriage);
											f_Carriage.clear();
											}
										}

									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									std::string f_AddString = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

									for(int f_XY = 0; f_XY < f_Count1; f_XY++)
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										f_AddString += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
										}

									f_StringB += "Sys%%String&&" + f_Name + "%%" + f_AddString + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_StringValue, f_ElementIndex))
										{
										std::vector<std::string> f_morfStrings;
										f_morfStrings.clear();
										int f_Count = 0;
										std::string f_Carriage;
										f_Carriage.clear();
										for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
											{
											char f_c = f_StringValue.at(f_XY);

											f_Carriage.push_back(f_c);
											f_Count++;

											if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
												{
												f_morfStrings.push_back(f_Carriage);
												f_Carriage.clear();
												}
											}

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										std::string f_AddString = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

										for(int f_XY = 0; f_XY < f_Count1; f_XY++)
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											f_AddString += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
											}

										f_StringB += "Sys%%String&&" + f_Name + "%%" + f_AddString + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_StringValue, f_ElementIndex))
											{
											std::vector<std::string> f_morfStrings;
											f_morfStrings.clear();
											int f_Count = 0;
											std::string f_Carriage;
											f_Carriage.clear();
											for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
												{
												char f_c = f_StringValue.at(f_XY);

												f_Carriage.push_back(f_c);
												f_Count++;

												if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
													{
													f_morfStrings.push_back(f_Carriage);
													f_Carriage.clear();
													}
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_AddString = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

											for(int f_XY = 0; f_XY < f_Count1; f_XY++)
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												f_AddString += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
												}

											f_StringB += "Sys%%String&&" + f_Name + "%%" + f_AddString + "&%";
											}
										else
											{
											std::vector<std::vector<std::string>> f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

#if 0
											bool f_StanVar = false;

											if(f_morfarray1.size() == ESL_INSTA_TYPE_SYS_DEF_MORF_COUNT)
												{
												if(f_morfarray1[0][0].at(0) == 'V')
													{
													if(f_morfarray2.size() >= ESL_INSTA_TYPE_SYS_DEF_OPER_MORF_COUNT)
														{
														if(f_morfarray2[6][1].at(0) == '*')
															{
															f_StanVar = true;
															}
														}
													}
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(f_StanVar == true)
												{
												if(ac_recordMeasurementBLTV1(1, 0, true, f_ElementIndex) == true)
													{
													std::string f_StringC = "Sys%%String&&" + f_Name + "%%Empty&%////" + ESL_LINE_ENDING;

													std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringC, ESL_INSTA_TYPE_SYS_DEF);

													f_Function->m_vec_Insta.push_back(f_Insta);
													f_Function->m_idx_vec_Insta++;

													f_Function->m_vec_String += f_StringC;
													f_LineCount--;
													f_LineIndexCount++;

													f_LineString = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount];
													f_LineString2 = "";

													f_morfarray1 = ac_ext_eslLine_morf_array(f_LineString);

													if(f_LineIndexCount <= f_Save_Com_Function->m_vec_InitLineOrdered.size() - 2)
														{
														f_LineString2 = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount + 1];
														f_morfarray2 = ac_ext_eslLine_morf_array(f_LineString2);
														}
													}
												}
											else
												{
												ac_recordMeasurementBLTV1(1, 0, false, f_ElementIndex);
												}
#endif

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_VarBCallName = ac_recordMeasurement(f_morfarray1[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_VarBNameFA = acMakeUnisonType(f_Target, f_VarBCallName, 1, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, MuVar_Int, true);

											std::string f_VarBVarSys = "";
											std::string f_VarBType = "";
											std::string f_VarBName = "";

											int f_Stage = 0;

											for(int f_Helly = 0; f_Helly < f_VarBNameFA.length(); f_Helly++)
												{
												char f_c = f_VarBNameFA.at(f_Helly);

												if(f_c == '&' || f_c == '%')
													{
													f_Stage++;
													}
												else
													{
													if(f_Stage == 0)
														{
														f_VarBVarSys.push_back(f_c);
														}
													else if(f_Stage >= 2)
														{
														f_VarBType.push_back(f_c);
														}
													else
														{
														f_VarBName.push_back(f_c);
														}
													}
												}

											char f_1 = f_VarBVarSys.at(0);

											std::string f_condAssignValurRHS = "";

											FillChar(f_Char, 5000);

											if(f_VarBName.compare(f_VarBCallName) == 0)
												{
												std::string f_StringValue = "";

												/*if(f_StanVar == true)
													{
													f_StringValue = f_morfarray2[3][0];
													}
												else
													{*/
													f_StringValue = f_morfarray2[10][0];
													//}

												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_StringValue, f_ElementIndex))
													{
													std::string f_AddString;
													f_AddString.clear();
													std::vector<std::string> f_morfStrings;
													f_morfStrings.clear();
													int f_Count = 0;
													std::string f_Carriage;
													f_Carriage.clear();
													for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
														{
														char f_c = f_StringValue.at(f_XY);

														f_Carriage.push_back(f_c);
														f_Count++;

														if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
															{
															f_morfStrings.push_back(f_Carriage);
															f_Carriage.clear();
															}
														}

													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

													for(int f_XY = 0; f_XY < f_Count1; f_XY++)
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
														}

													f_condAssignValurRHS = f_AddString;
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_StringValue, f_ElementIndex))
														{
														std::string f_AddString;
														f_AddString.clear();
														std::vector<std::string> f_morfStrings;
														f_morfStrings.clear();
														int f_Count = 0;
														std::string f_Carriage;
														f_Carriage.clear();
														for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
															{
															char f_c = f_StringValue.at(f_XY);

															f_Carriage.push_back(f_c);
															f_Count++;

															if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
																{
																f_morfStrings.push_back(f_Carriage);
																f_Carriage.clear();
																}
															}

														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

														for(int f_XY = 0; f_XY < f_Count1; f_XY++)
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
															}

														f_condAssignValurRHS = f_AddString1;
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_StringValue, f_ElementIndex))
															{
															std::string f_AddString;
															f_AddString.clear();
															std::vector<std::string> f_morfStrings;
															f_morfStrings.clear();
															int f_Count = 0;
															std::string f_Carriage;
															f_Carriage.clear();
															for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
																{
																char f_c = f_StringValue.at(f_XY);

																f_Carriage.push_back(f_c);
																f_Count++;

																if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
																	{
																	f_morfStrings.push_back(f_Carriage);
																	f_Carriage.clear();
																	}
																}

															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

															for(int f_XY = 0; f_XY < f_Count1; f_XY++)
																{
																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
																}

															f_condAssignValurRHS = f_AddString1;
															}
														else
															{
															f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

															if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_StringValue, f_ElementIndex))
																{
																std::string f_AddString;
																f_AddString.clear();
																std::vector<std::string> f_morfStrings;
																f_morfStrings.clear();
																int f_Count = 0;
																std::string f_Carriage;
																f_Carriage.clear();
																for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
																	{
																	char f_c = f_StringValue.at(f_XY);

																	f_Carriage.push_back(f_c);
																	f_Count++;

																	if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
																		{
																		f_morfStrings.push_back(f_Carriage);
																		f_Carriage.clear();
																		}
																	}

																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

																for(int f_XY = 0; f_XY < f_Count1; f_XY++)
																	{
																	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

																	f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
																	}

																f_condAssignValurRHS = f_AddString;
																}
															}
														}
													}
												}

											int f_OperType = agFind_OprType(f_morfarray1[5][0]);

											bool f_Oper_Five[5];

											if(f_OperType == MuOpr_Plus)
												{
												f_Oper_Five[0] = true;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Minus)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = true;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Equals)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = true;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Multiply)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = true;
												f_Oper_Five[4] = false;
												}
											else if(f_OperType == MuOpr_Divide)
												{
												f_Oper_Five[0] = false;
												f_Oper_Five[1] = false;
												f_Oper_Five[2] = false;
												f_Oper_Five[3] = false;
												f_Oper_Five[4] = true;
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[0], f_ElementIndex) == true)
												{
												::sprintf(f_Char, "%s&%Opr%%Plus**Fork1plus%%%s%%%s&%////\n", "Empty", f_VarBNameFA.c_str(), f_condAssignValurRHS);
												}
											else
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[1], f_ElementIndex) == true)
													{
													::sprintf(f_Char, "%s&%Opr%%Minus**Fork1minus%%%s%%%s&%////\n", "Empty", f_VarBNameFA.c_str(), f_condAssignValurRHS);
													}
												else
													{
													f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

													if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[2], f_ElementIndex) == true)
														{
														::sprintf(f_Char, "%s&%Opr%%Equals**Fork1equals%%%s%%%s&%////\n", "Empty", f_VarBNameFA.c_str(), f_condAssignValurRHS);
														}
													else
														{
														f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

														if(ac_recordMeasurementBLTV1(1, 0, f_Oper_Five[3], f_ElementIndex) == true)
															{
															::sprintf(f_Char, "%s&%Opr%%Mul**Fork1multiply%%%s%%%s&%////\n", "Empty", f_VarBNameFA.c_str(), f_condAssignValurRHS);
															}
														else
															{
															::sprintf(f_Char, "%s&%Opr%%Div**Fork1divide%%%s%%%s&%////\n", "Empty", f_VarBNameFA.c_str(), f_condAssignValurRHS);
															}
														}
													}
												}

											f_StringB += "Sys%%String&&" + f_Name + "%%" + f_Char;
											}
										}

									f_StringB += ESL_LINE_ENDING;

									std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringB, ESL_INSTA_TYPE_SYS_DEF);

									f_Function->m_vec_Insta.push_back(f_Insta);
									f_Function->m_idx_vec_Insta++;

									f_Function->m_vec_String += f_StringB;
									f_LineCount--;
									f_LineIndexCount++;
					
									f_Contact = true;
									}
								}
							}
						}
					}
				}
			}	
		else if(f_LineType == ESL_INSTA_TYPE_CONDITIONAL)
			{
			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			if(1)//acRecordStrength(ESL_INSTA_TYPE_CONDITIONAL, f_Function, f_LineString, f_ElementIndex) == true)
				{
				std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

				std::string f_VarACallName = ac_recordMeasurement(f_morfarray[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarANameFA = acMakeUnisonType(f_Target, f_VarACallName, 1, ESL_INSTA_TYPE_CONDITIONAL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, -100, true);

				std::string f_VarAName = "";

				std::string f_VarAType = "";

				int f_Stage = 0;
				for(int f_Helly = 0; f_Helly < f_VarANameFA.length(); f_Helly++)
					{
					char f_c = f_VarANameFA.at(f_Helly);

					if(f_c == '&' || f_c == '%')
						{
						f_Stage++;
						}
					else
						{
						if(f_Stage == 0)
							{
							f_VarAType.push_back(f_c);
							}
						else if(f_Stage >= 2)
							{
							f_VarAName.push_back(f_c);
							}
						}
					}

				int f_MuVarAType = agFind_VarType(f_VarAType);

				std::string f_StringAB = "";

				if(f_MuVarAType == MuVar_Float)
					{
					f_StringAB += f_VarANameFA + "0.0&%";
					}
				else if(f_MuVarAType == MuVar_Float)
					{
					f_StringAB += f_VarANameFA + "0&%";
					}
				else
					{
					f_StringAB += f_VarANameFA + "Empty&%";
					}

				std::shared_ptr<classInsta> f_InstaA = std::make_shared<classInsta>(f_StringAB, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaA);
				f_Function->m_idx_vec_Insta++;

				std::string f_StringB = f_StringAB + "Cond%%";

				std::shared_ptr<classInsta> f_InstaAB = std::make_shared<classInsta>(f_StringB, ESL_INSTA_TYPE_CONDITIONAL);

				f_Function->m_vec_Insta.push_back(f_InstaAB);
				f_Function->m_idx_vec_Insta++;

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_Name = ac_recordMeasurement(f_morfarray[6][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				int f_FingerCount = ac_recordMeasurementINTV1(0, 6, 1, 3, 2, agFind_ConType(f_morfarray[6][0]), f_ElementIndex);

				if(f_FingerCount <= MuCon_Equal)
					{
					f_StringB += "==^^";
					}
				else if(f_FingerCount == MuCon_NotEqual)
					{
					f_StringB += "!=^^";
					}
				else if(f_FingerCount == MuCon_SmallThan)
					{
					f_StringB += "<<^^";
					}
				else if(f_FingerCount == MuCon_GreatThan)
					{
					f_StringB += ">>^^";
					}
				else if(f_FingerCount == MuCon_SmallThanorEqual)
					{
					f_StringB += "<=^^";
					}
				else
					{
					f_StringB += ">=^^";
					}

				f_StringB += f_Name + "%%";

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarBCallName = ac_recordMeasurement(f_morfarray[9][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarBNameFA = acMakeUnisonType(f_Target, f_VarBCallName, 1, ESL_INSTA_TYPE_CONDITIONAL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, f_MuVarAType, true);

				std::string f_VarBName = "";

				int f_StageBR = 0;
				for(int f_Helly = 0; f_Helly < f_VarBNameFA.length(); f_Helly++)
					{
					char f_c = f_VarBNameFA.at(f_Helly);

					if(f_c == '&' || f_c == '%')
						{
						f_StageBR++;
						}
					else
						{
						if(f_StageBR >= 4)
							{
							f_VarBName.push_back(f_c);
							}
						}
					}

				char f_Char[5000];
				FillChar(f_Char, 5000);

				std::string f_StringF = "";

				if(f_VarBName.compare(f_VarBCallName) == 0)
					{
					if(f_MuVarAType == MuVar_Float)
						{
						float f_FloatValue = atof(f_morfarray[10][0].c_str());

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

							f_StringF += f_VarBNameFA + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

								f_StringF += f_VarBNameFA + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

									f_StringF += f_VarBNameFA + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

										f_StringF += f_VarBNameFA + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
											{
											::sprintf(f_Char, "Random");

											f_StringF += f_VarBNameFA + f_Char + "&%";
											}
										}
									}
								}
							}
						}
					else if(f_MuVarAType == MuVar_Int)
						{
						int f_IntValue = atoi(f_morfarray[10][0].c_str());

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_IntValue, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_IntValue, f_ElementIndex));

							f_StringF += f_VarBNameFA + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_IntValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_IntValue, f_ElementIndex));

								f_StringF += f_VarBNameFA + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_IntValue, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex));

									f_StringF += f_VarBNameFA + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_IntValue, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex));

										f_StringF += f_VarBNameFA + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_LineString, f_IntValue, f_ElementIndex))
											{
											::sprintf(f_Char, "Random");

											f_StringF += f_VarBNameFA + f_Char + "&%";
											}
										}
									}
								}
							}
						}
					else
						{
						std::string f_StringValue = f_morfarray[10][0];

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_StringValue, f_ElementIndex))
							{
							std::string f_AddString;
							f_AddString.clear();
							std::vector<std::string> f_morfStrings;
							f_morfStrings.clear();
							int f_Count = 0;
							std::string f_Carriage;
							f_Carriage.clear();
							for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
								{
								char f_c = f_StringValue.at(f_XY);

								f_Carriage.push_back(f_c);
								f_Count++;

								if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
									{
									f_morfStrings.push_back(f_Carriage);
									f_Carriage.clear();
									}
								}

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

							for(int f_XY = 0; f_XY < f_Count1; f_XY++)
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringF += f_VarBNameFA + f_AddString1 + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_StringValue, f_ElementIndex))
								{
								std::string f_AddString;
								f_AddString.clear();
								std::vector<std::string> f_morfStrings;
								f_morfStrings.clear();
								int f_Count = 0;
								std::string f_Carriage;
								f_Carriage.clear();
								for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
									{
									char f_c = f_StringValue.at(f_XY);

									f_Carriage.push_back(f_c);
									f_Count++;

									if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
										{
										f_morfStrings.push_back(f_Carriage);
										f_Carriage.clear();
										}
									}

								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

								for(int f_XY = 0; f_XY < f_Count1; f_XY++)
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
									}

								f_StringF += f_VarBNameFA + f_AddString1 + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_StringValue, f_ElementIndex))
									{
									std::string f_AddString;
									f_AddString.clear();
									std::vector<std::string> f_morfStrings;
									f_morfStrings.clear();
									int f_Count = 0;
									std::string f_Carriage;
									f_Carriage.clear();
									for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
										{
										char f_c = f_StringValue.at(f_XY);

										f_Carriage.push_back(f_c);
										f_Count++;

										if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
											{
											f_morfStrings.push_back(f_Carriage);
											f_Carriage.clear();
											}
										}

									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

									for(int f_XY = 0; f_XY < f_Count1; f_XY++)
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
										}

									f_StringF += f_VarBNameFA + f_AddString1 + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_StringValue, f_ElementIndex))
										{
										std::string f_AddString;
										f_AddString.clear();
										std::vector<std::string> f_morfStrings;
										f_morfStrings.clear();
										int f_Count = 0;
										std::string f_Carriage;
										f_Carriage.clear();
										for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
											{
											char f_c = f_StringValue.at(f_XY);

											f_Carriage.push_back(f_c);
											f_Count++;

											if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
												{
												f_morfStrings.push_back(f_Carriage);
												f_Carriage.clear();
												}
											}

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

										for(int f_XY = 0; f_XY < f_Count1; f_XY++)
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
											}

										f_StringF += f_VarBNameFA + f_AddString1 + "&%";
										}
									}
								}
							}
						}
					}
				else
					{
					if(f_MuVarAType == MuVar_Float)
						{
						f_StringF += f_VarBNameFA + "0.0&%";
						}
					else if(f_MuVarAType == MuVar_Int)
						{
						f_StringF += f_VarBNameFA + "0&%";
						}
					else
						{
						f_StringF += f_VarBNameFA + "Empty&%";
						}
					}

				std::shared_ptr<classInsta> f_InstaB = std::make_shared<classInsta>(f_StringF, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaB);
				f_Function->m_idx_vec_Insta++;

				f_StringB += f_StringF;

				f_Function->m_vec_String += f_StringB;
				f_LineCount--;
				f_LineIndexCount++;

				std::string f_StringFB = "Function%%EcomNative&*Success%%////";

				std::shared_ptr<classInsta> f_InstaC = std::make_shared<classInsta>(f_StringFB, ESL_INSTA_TYPE_FUNC_DEF);

				f_Function->m_vec_Insta.push_back(f_InstaC);
				f_Function->m_idx_vec_Insta++;

				f_Function->m_vec_String += f_StringFB;
				f_LineCount--;
				f_LineIndexCount++;

				//int f_SuccessLineLength = ac_ext_Scan_Lines_Keyword_Next(f_LineCount, 0, 0, f_Save_Com_Function, "Function");

#if 0 //hmmm could this be usefull...
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
				
				std::vector<int> f_conInstaCount;
				int f_Select = 0;
				if(f_SuccessLineLength > 0 && f_SuccessLineLength <= 4)
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_conInstaCount.push_back(ac_recordMeasurementINTV1(1, 4, 0, 3, 4, f_SuccessLineLength, f_ElementIndex));
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_conInstaCount.push_back(ac_recordMeasurementINTV1(4, 20, 0, 3, 5, f_SuccessLineLength, f_ElementIndex, false));
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_conInstaCount.push_back(ac_recordMeasurementINTV1(20, 40, 4, 3, 6, f_SuccessLineLength, f_ElementIndex, false));
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_Select = ac_recordMeasurementINTV1(0, 3, 1, 3, 3, 0, f_ElementIndex);
					}
				else if(f_SuccessLineLength > 4 && f_SuccessLineLength <= 20)
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_conInstaCount.push_back(ac_recordMeasurementINTV1(1, 4, 0, 3, 4, f_SuccessLineLength, f_ElementIndex, false));
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_conInstaCount.push_back(ac_recordMeasurementINTV1(4, 20, 0, 3, 5, f_SuccessLineLength, f_ElementIndex));
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_conInstaCount.push_back(ac_recordMeasurementINTV1(20, 40, 4, 3, 6, f_SuccessLineLength, f_ElementIndex, false));
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_Select = ac_recordMeasurementINTV1(0, 3, 1, 3, 3, 1, f_ElementIndex);
					}
				else if(f_SuccessLineLength > 20 && f_SuccessLineLength <= 40)
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_conInstaCount.push_back(ac_recordMeasurementINTV1(1, 4, 0, 3, 4, f_SuccessLineLength, f_ElementIndex, false));
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_conInstaCount.push_back(ac_recordMeasurementINTV1(4, 20, 0, 3, 5, f_SuccessLineLength, f_ElementIndex, false));
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_conInstaCount.push_back(ac_recordMeasurementINTV1(20, 40, 4, 3, 6, f_SuccessLineLength, f_ElementIndex, false));
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					f_Select = ac_recordMeasurementINTV1(0, 3, 1, 3, 3, 2, f_ElementIndex);
					}
					
				m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_conInstaCount[f_Select], "ECNMiner_Affinity", ESL_INSTA_TYPE_CONDITIONAL));
				m_idx_vec_CountLock++;
#endif
					
				f_Contact = true;
				}
			}
		else if(f_LineType == ESL_INSTA_TYPE_LOOP_DEF)
			{
			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			if(1)//acRecordStrength(ESL_INSTA_TYPE_LOOP_DEF, f_Function, f_LineString, f_ElementIndex) == true)
				{
				std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_forName = ac_recordMeasurement(f_morfarray[1][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
				std::string f_StringF = "For%% " + f_forName + "%%";

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarACallName = ac_recordMeasurement(f_morfarray[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarANameFA = acMakeUnisonType(f_Target, f_VarACallName, 1, ESL_INSTA_TYPE_CONDITIONAL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, -100, true);

				std::string f_VarAName = "";

				std::string f_VarAType = "";

				int f_Stage = 0;
				for(int f_Helly = 0; f_Helly < f_VarANameFA.length(); f_Helly++)
					{
					char f_c = f_VarANameFA.at(f_Helly);

					if(f_c == '&' || f_c == '%')
						{
						f_Stage++;
						}
					else
						{
						if(f_Stage == 0)
							{
							f_VarAType.push_back(f_c);
							}
						else if(f_Stage >= 2)
							{
							f_VarAName.push_back(f_c);
							}
						}
					}

				int f_MuVarAType = agFind_VarType(f_VarAType);

				std::string f_StringAB = "";

				if(f_MuVarAType == MuVar_Float)
					{
					f_StringAB += f_VarANameFA + "0.0&%";
					}
				else if(f_MuVarAType == MuVar_Int)
					{
					f_StringAB += f_VarANameFA + "0&%";
					}
				else
					{
					f_StringAB += f_VarANameFA + "Empty&%";
					}

				std::shared_ptr<classInsta> f_InstaA = std::make_shared<classInsta>(f_StringAB, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaA);
				f_Function->m_idx_vec_Insta++;

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarBCallName = ac_recordMeasurement(f_morfarray[9][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarBNameFA = acMakeUnisonType(f_Target, f_VarBCallName, 1, ESL_INSTA_TYPE_CONDITIONAL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, -100, true);

				std::string f_VarBName = "";

				int f_StageBR = 0;
				for(int f_Helly = 0; f_Helly < f_VarBNameFA.length(); f_Helly++)
					{
					char f_c = f_VarBNameFA.at(f_Helly);

					if(f_c == '&' || f_c == '%')
						{
						f_StageBR++;
						}
					else
						{
						if(f_StageBR >= 4)
							{
							f_VarBName.push_back(f_c);
							}
						}
					}

				char f_Char[5000];
				FillChar(f_Char, 5000);

				std::string f_StringFS = "";

				if(f_VarBName.compare(f_VarBCallName) == 0)
					{
					if(f_MuVarAType == MuVar_Float)
						{
						float f_FloatValue = atof(f_morfarray[10][0].c_str());

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

							f_StringFS += f_VarBNameFA + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

								f_StringFS += f_VarBNameFA + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

									f_StringFS += f_VarBNameFA + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

										f_StringFS += f_VarBNameFA + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											::sprintf(f_Char, "Random");

											f_StringFS += f_VarBNameFA + f_Char + "&%";
											}
										}
									}
								}
							}
						}
					else
						{
						if(f_MuVarAType == MuVar_Int)
							{
							int f_IntValue = atoi(f_morfarray[10][0].c_str());

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_IntValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_IntValue, f_ElementIndex));

								f_StringFS += f_VarBNameFA + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_IntValue, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_IntValue, f_ElementIndex));

									f_StringFS += f_VarBNameFA + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_IntValue, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex));

										f_StringFS += f_VarBNameFA + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_IntValue, f_ElementIndex))
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex));

											f_StringFS += f_VarBNameFA + f_Char + "&%";
											}
										else
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_LineString, f_IntValue, f_ElementIndex))
												{
												::sprintf(f_Char, "Random");

												f_StringFS += f_VarBNameFA + f_Char + "&%";
												}
											}
										}
									}
								}
							}
						else
							{
							std::string f_StringValue = f_morfarray[10][0];

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_StringValue, f_ElementIndex))
								{
								std::string f_AddString;
								f_AddString.clear();
								std::vector<std::string> f_morfStrings;
								f_morfStrings.clear();
								int f_Count = 0;
								std::string f_Carriage;
								f_Carriage.clear();
								for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
									{
									char f_c = f_StringValue.at(f_XY);

									f_Carriage.push_back(f_c);
									f_Count++;

									if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
										{
										f_morfStrings.push_back(f_Carriage);
										f_Carriage.clear();
										}
									}

								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

								for(int f_XY = 0; f_XY < f_Count1; f_XY++)
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
									}

								f_StringFS += f_VarBNameFA + f_AddString1 + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_StringValue, f_ElementIndex))
									{
									std::string f_AddString;
									f_AddString.clear();
									std::vector<std::string> f_morfStrings;
									f_morfStrings.clear();
									int f_Count = 0;
									std::string f_Carriage;
									f_Carriage.clear();
									for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
										{
										char f_c = f_StringValue.at(f_XY);

										f_Carriage.push_back(f_c);
										f_Count++;

										if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
											{
											f_morfStrings.push_back(f_Carriage);
											f_Carriage.clear();
											}
										}

									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

									for(int f_XY = 0; f_XY < f_Count1; f_XY++)
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
										}

									f_StringFS += f_VarBNameFA + f_AddString1 + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_StringValue, f_ElementIndex))
										{
										std::string f_AddString;
										f_AddString.clear();
										std::vector<std::string> f_morfStrings;
										f_morfStrings.clear();
										int f_Count = 0;
										std::string f_Carriage;
										f_Carriage.clear();
										for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
											{
											char f_c = f_StringValue.at(f_XY);

											f_Carriage.push_back(f_c);
											f_Count++;

											if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
												{
												f_morfStrings.push_back(f_Carriage);
												f_Carriage.clear();
												}
											}

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

										for(int f_XY = 0; f_XY < f_Count1; f_XY++)
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
											}

										f_StringFS += f_VarBNameFA + f_AddString1 + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_StringValue, f_ElementIndex))
											{
											std::string f_AddString;
											f_AddString.clear();
											std::vector<std::string> f_morfStrings;
											f_morfStrings.clear();
											int f_Count = 0;
											std::string f_Carriage;
											f_Carriage.clear();
											for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
												{
												char f_c = f_StringValue.at(f_XY);

												f_Carriage.push_back(f_c);
												f_Count++;

												if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
													{
													f_morfStrings.push_back(f_Carriage);
													f_Carriage.clear();
													}
												}

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

											for(int f_XY = 0; f_XY < f_Count1; f_XY++)
												{
												f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

												f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
												}

											f_StringFS += f_VarBNameFA + f_AddString1 + "&%";
											}
										}
									}
								}
							}
						}
					}
				else
					{
					if(f_MuVarAType == MuVar_Float)
						{
						f_StringFS += f_VarBNameFA + "0.0&%";
						}
					else if(f_MuVarAType == MuVar_Int)
						{
						f_StringFS += f_VarBNameFA + "0&%";
						}
					else
						{
						f_StringFS += f_VarBNameFA + "Empty&%";
						}
					}

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarASCallName = ac_recordMeasurement(f_morfarray[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarASNameFA = acMakeUnisonType(f_Target, f_VarASCallName, 1, ESL_INSTA_TYPE_CONDITIONAL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, -100, true);

				std::string f_VarASName = "";

				std::string f_VarASType = "";

				int f_StageS = 0;
				for(int f_Helly = 0; f_Helly < f_VarASNameFA.length(); f_Helly++)
					{
					char f_c = f_VarASNameFA.at(f_Helly);

					if(f_c == '&' || f_c == '%')
						{
						f_StageS++;
						}
					else
						{
						if(f_StageS == 0)
							{
							f_VarASType.push_back(f_c);
							}
						else if(f_StageS >= 2)
							{
							f_VarASName.push_back(f_c);
							}
						}
					}

				int f_MuVarASType = agFind_VarType(f_VarASType);

				std::string f_StringABS = "";

				if(f_MuVarASType == MuVar_Float)
					{
					f_StringABS += f_VarASNameFA + "0.0&%";
					}
				else if(f_MuVarASType == MuVar_Float)
					{
					f_StringABS += f_VarASNameFA + "0&%";
					}
				else
					{
					f_StringABS += f_VarASNameFA + "Empty&%";
					}

				std::shared_ptr<classInsta> f_InstaAS = std::make_shared<classInsta>(f_StringABS, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaAS);
				f_Function->m_idx_vec_Insta++;

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarBSCallName = ac_recordMeasurement(f_morfarray[9][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_VarBSNameFA = acMakeUnisonType(f_Target, f_VarBSCallName, 1, ESL_INSTA_TYPE_CONDITIONAL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, -100, true);

				std::string f_VarBSName = "";

				int f_StageBS = 0;
				for(int f_Helly = 0; f_Helly < f_VarBSNameFA.length(); f_Helly++)
					{
					char f_c = f_VarBSNameFA.at(f_Helly);

					if(f_c == '&' || f_c == '%')
						{
						f_StageBS++;
						}
					else
						{
						if(f_StageBS >= 4)
							{
							f_VarBSName.push_back(f_c);
							}
						}
					}

				FillChar(f_Char, 5000);

				std::string f_StringFSB = "";

				if(f_VarBSName.compare(f_VarBSCallName) == 0)
					{
					if(f_MuVarASType == MuVar_Float)
						{
						float f_FloatValue = atof(f_morfarray[10][0].c_str());

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(0.0f, 1.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

							f_StringFSB += f_VarBSNameFA + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(1.0f, 100.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

								f_StringFSB += f_VarBSNameFA + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

									f_StringFSB += f_VarBSNameFA + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%f", ac_recordMeasurementFLTV1(100.0f, 5000.0f, 0.0f, 2, 0, f_FloatValue, f_ElementIndex));

										f_StringFSB += f_VarBSNameFA + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_LineString, f_FloatValue, f_ElementIndex))
											{
											::sprintf(f_Char, "Random");

											f_StringFSB += f_VarBSNameFA + f_Char + "&%";
											}
										}
									}
								}
							}
						}
					else if(f_MuVarASType == MuVar_Int)
						{
						int f_IntValue = atoi(f_morfarray[10][0].c_str());

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_IntValue, f_ElementIndex))
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(0, 1, 0, 2, 0, f_IntValue, f_ElementIndex));

							f_StringFSB += f_VarBSNameFA + f_Char + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_IntValue, f_ElementIndex))
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(1, 100, 0, 2, 0, f_IntValue, f_ElementIndex));

								f_StringFSB += f_VarBSNameFA + f_Char + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_IntValue, f_ElementIndex))
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex));

									f_StringFSB += f_VarBSNameFA + f_Char + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_IntValue, f_ElementIndex))
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										::sprintf(f_Char, "%i", ac_recordMeasurementINTV1(100, 5000, 0, 2, 0, f_IntValue, f_ElementIndex));

										f_StringFSB += f_VarBSNameFA + f_Char + "&%";
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										if(acRecordStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_LineString, f_IntValue, f_ElementIndex))
											{
											::sprintf(f_Char, "Random");

											f_StringFSB += f_VarBSNameFA + f_Char + "&%";
											}
										}
									}
								}
							}
						}
					else
						{
						std::string f_StringValue = f_morfarray[10][0];

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						if(acRecordStrengthVarString(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_LineString, f_StringValue, f_ElementIndex))
							{
							std::string f_AddString;
							f_AddString.clear();
							std::vector<std::string> f_morfStrings;
							f_morfStrings.clear();
							int f_Count = 0;
							std::string f_Carriage;
							f_Carriage.clear();
							for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
								{
								char f_c = f_StringValue.at(f_XY);

								f_Carriage.push_back(f_c);
								f_Count++;

								if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
									{
									f_morfStrings.push_back(f_Carriage);
									f_Carriage.clear();
									}
								}

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

							for(int f_XY = 0; f_XY < f_Count1; f_XY++)
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
								}

							f_StringFSB += f_VarBSNameFA + f_AddString1 + "&%";
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

							if(acRecordStrengthVarString(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_LineString, f_StringValue, f_ElementIndex))
								{
								std::string f_AddString;
								f_AddString.clear();
								std::vector<std::string> f_morfStrings;
								f_morfStrings.clear();
								int f_Count = 0;
								std::string f_Carriage;
								f_Carriage.clear();
								for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
									{
									char f_c = f_StringValue.at(f_XY);

									f_Carriage.push_back(f_c);
									f_Count++;

									if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
										{
										f_morfStrings.push_back(f_Carriage);
										f_Carriage.clear();
										}
									}

								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

								for(int f_XY = 0; f_XY < f_Count1; f_XY++)
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
									}

								f_StringFSB += f_VarBSNameFA + f_AddString1 + "&%";
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

								if(acRecordStrengthVarString(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_LineString, f_StringValue, f_ElementIndex))
									{
									std::string f_AddString;
									f_AddString.clear();
									std::vector<std::string> f_morfStrings;
									f_morfStrings.clear();
									int f_Count = 0;
									std::string f_Carriage;
									f_Carriage.clear();
									for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
										{
										char f_c = f_StringValue.at(f_XY);

										f_Carriage.push_back(f_c);
										f_Count++;

										if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
											{
											f_morfStrings.push_back(f_Carriage);
											f_Carriage.clear();
											}
										}

									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

									for(int f_XY = 0; f_XY < f_Count1; f_XY++)
										{
										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
										}

									f_StringFSB += f_VarBSNameFA + f_AddString1 + "&%";
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

									if(acRecordStrengthVarString(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_LineString, f_StringValue, f_ElementIndex))
										{
										std::string f_AddString;
										f_AddString.clear();
										std::vector<std::string> f_morfStrings;
										f_morfStrings.clear();
										int f_Count = 0;
										std::string f_Carriage;
										f_Carriage.clear();
										for(int f_XY = 0; f_XY < f_StringValue.length(); f_XY++)
											{
											char f_c = f_StringValue.at(f_XY);

											f_Carriage.push_back(f_c);
											f_Count++;

											if(f_Count == ECOIN_DATA_CHUNK_LENGTH_COUNT)
												{
												f_morfStrings.push_back(f_Carriage);
												f_Carriage.clear();
												}
											}

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										std::string f_AddString1 = ac_recordMeasurement(f_morfStrings[0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

										int f_Count1 = ac_recordMeasurementINTV1(1, 5, 0, 2, 0, (int)(f_StringValue.length() / ECOIN_DATA_CHUNK_LENGTH_COUNT), f_ElementIndex);

										for(int f_XY = 0; f_XY < f_Count1; f_XY++)
											{
											f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

											f_AddString1 += ac_recordMeasurement(f_morfStrings[f_XY], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
											}

										f_StringFSB += f_VarBSNameFA + f_AddString1 + "&%";
										}
									}
								}
							}
						}
					}
				else
					{
					if(f_MuVarASType == MuVar_Float)
						{
						f_StringFSB += f_VarBSNameFA + "0.0&%";
						}
					else if(f_MuVarASType == MuVar_Int)
						{
						f_StringFSB += f_VarBSNameFA + "0&%";
						}
					else
						{
						f_StringFSB += f_VarBSNameFA + "Empty&%";
						}
					}

				std::shared_ptr<classInsta> f_InstaB = std::make_shared<classInsta>(f_StringFSB, ESL_INSTA_TYPE_LOOP_DEF);

				f_Function->m_vec_Insta.push_back(f_InstaB);
				f_Function->m_idx_vec_Insta++;

				f_Function->m_vec_String += f_StringFSB;
				f_LineCount--;
				f_LineIndexCount++;

				std::string f_StringFB = "Function%%EcomNative&*" + f_forName + "%%////";

				std::shared_ptr<classInsta> f_InstaC = std::make_shared<classInsta>(f_StringFB, ESL_INSTA_TYPE_FUNC_DEF);

				f_Function->m_vec_Insta.push_back(f_InstaC);
				f_Function->m_idx_vec_Insta++;

				f_Function->m_vec_String += f_StringFB;
				f_LineCount--;
				f_LineIndexCount++;

#if 0
				f_LineCount = ac_ext_Scan_Lines_Keyword_Next(f_LineCount, 0, 0, f_Save_Com_Function, f_Save_Com_Function->m_name);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
					
				int f_loopLineCount = ac_recordMeasurementINTV1(8, 105, 8, 3, 1, f_LineCount, f_ElementIndex);

				m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_loopLineCount, "ECNMiner_Affinity", ESL_INSTA_TYPE_LOOP_DEF));
				m_idx_vec_CountLock++;
#endif

				f_Contact = true;
				}
			}
		else if(f_LineType == ESL_INSTA_TYPE_FUNC_CALL)
			{
			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			if(1)//acRecordStrength(ESL_INSTA_TYPE_FUNC_CALL, f_Function, f_LineString, f_ElementIndex) == true)
				{
				std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

				std::string f_ReturnVarNameFA = "";
				std::string f_FunctionNameFA = "";
				std::string f_Var1NameFA = "";
				std::string f_Var2NameFA = "";

				int f_OffsetIntReturn = 0;
				int f_OffsetIntArg = 0;

				std::string f_StringB = "";

				if(f_morfarray[0][0].compare("Var") == 0)	//Return arg is Var
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, true, f_ElementIndex); //has return

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					f_ReturnVarNameFA = acMakeUnisonType(f_Target, ac_recordMeasurement(f_morfarray[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, 0, -100, true);
					f_OffsetIntReturn += 4;

					std::shared_ptr<classInsta> f_InstaR = std::make_shared<classInsta>(f_ReturnVarNameFA, ESL_INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaR);
					f_Function->m_idx_vec_Insta++;

					f_StringB += f_ReturnVarNameFA + "%%1.0&%";
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex); //has no var return

					if(f_morfarray[0][0].compare("ClassVar") == 0)	//Return arg is ClassVar
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, true, f_ElementIndex); //has classvar return

						f_ReturnVarNameFA = acMakeUnisonType(f_Target, ac_recordMeasurement(f_morfarray[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_CLASS_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, 0, -100, true);
						f_OffsetIntReturn += 3;

						std::shared_ptr<classInsta> f_InstaR = std::make_shared<classInsta>(f_ReturnVarNameFA, ESL_INSTA_TYPE_CLASS_VAR_CALL);

						f_Function->m_vec_Insta.push_back(f_InstaR);
						f_Function->m_idx_vec_Insta++;

						f_StringB += f_ReturnVarNameFA + "%%";
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex); //has no classvar return
						}
					}

				f_OffsetIntArg = f_OffsetIntReturn;

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_FunctionName1FA = acMakeUnisonType(f_Target, ac_recordMeasurement(f_morfarray[f_OffsetIntReturn + 1][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function, f_LineString, 3, -100, true);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_FunctionName2FA = acMakeUnisonType(f_Target, ac_recordMeasurement(f_morfarray[f_OffsetIntReturn + 2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function, f_LineString, 3, -100, true);

				std::shared_ptr<classInsta> f_InstaB = std::make_shared<classInsta>(f_FunctionName1FA, ESL_INSTA_TYPE_FUNC_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaB);
				f_Function->m_idx_vec_Insta++;

				f_StringB += "Fcn%%" + f_FunctionName1FA + "&*" + f_FunctionName2FA + "%%";

				f_OffsetIntArg += 3;

				if(f_morfarray[f_OffsetIntArg + 3][0].compare("Var") == 0)	//arg is Var
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, true, f_ElementIndex); //has var arg

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					f_Var1NameFA = acMakeUnisonType(f_Target, ac_recordMeasurement(f_morfarray[f_OffsetIntArg + 3][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, 0, -100, true);

					std::shared_ptr<classInsta> f_InstaA1 = std::make_shared<classInsta>(f_Var1NameFA, ESL_INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaA1);
					f_Function->m_idx_vec_Insta++;

					f_StringB += f_Var1NameFA + "%%1.0&%";

					f_OffsetIntArg += 4;
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex); //has no var arg

					if(f_morfarray[f_OffsetIntArg + 3][0].compare("ClassVar") == 0)	//arg is ClassVar
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, true, f_ElementIndex); //has classvar return

						f_Var1NameFA = acMakeUnisonType(f_Target, ac_recordMeasurement(f_morfarray[f_OffsetIntArg + 3][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_CLASS_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, 0, -100, true);

						std::shared_ptr<classInsta> f_InstaA1 = std::make_shared<classInsta>(f_Var1NameFA, ESL_INSTA_TYPE_CLASS_VAR_CALL);

						f_Function->m_vec_Insta.push_back(f_InstaA1);
						f_Function->m_idx_vec_Insta++;

						f_StringB += f_Var1NameFA;

						f_OffsetIntArg += 3;
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex); //has no classvar return
						}
					}

				if(f_morfarray[f_OffsetIntArg][0].compare("Var") == 0)	//arg is Var
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, true, f_ElementIndex); //has var arg

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					f_Var2NameFA = acMakeUnisonType(f_Target, ac_recordMeasurement(f_morfarray[f_OffsetIntArg][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, 0, -100, true);

					std::shared_ptr<classInsta> f_InstaA1 = std::make_shared<classInsta>(f_Var2NameFA, ESL_INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaA1);
					f_Function->m_idx_vec_Insta++;

					f_StringB += f_Var2NameFA + "%%1.0&%";

					f_OffsetIntArg += 4;
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex); //has no var arg

					if(f_morfarray[f_OffsetIntArg][0].compare("ClassVar") == 0)	//arg is ClassVar
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, true, f_ElementIndex); //has classvar return

						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						f_Var2NameFA = acMakeUnisonType(f_Target, ac_recordMeasurement(f_morfarray[f_OffsetIntArg][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_CLASS_VAR_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta, m_idx_vec_Function, f_LineString, 0, -100, true);

						std::shared_ptr<classInsta> f_InstaA1 = std::make_shared<classInsta>(f_Var2NameFA, ESL_INSTA_TYPE_CLASS_VAR_CALL);

						f_Function->m_vec_Insta.push_back(f_InstaA1);
						f_Function->m_idx_vec_Insta++;

						f_StringB += f_Var2NameFA;

						f_OffsetIntArg += 3;
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

						ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex); //has no classvar return
						}
					}

				f_StringB += "////" + ESL_LINE_ENDING;
					
				f_Function->m_vec_String += f_StringB;

				f_LineCount--;
				f_LineIndexCount++;

				f_Contact = true;
				}
			}
		else if(f_LineType == ESL_INSTA_TYPE_FUNC_DEF)
			{
			if(1)//acRecordStrength(ESL_INSTA_TYPE_FUNC_DEF, f_Function, f_LineString, f_ElementIndex) == true)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_FunctionDefName1 = ac_recordMeasurement(ac_ext_eslLine_morf_array(f_LineString)[1][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_FunctionDefName2 = ac_recordMeasurement(ac_ext_eslLine_morf_array(f_LineString)[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_StringE = "FuncDef%%" + f_FunctionDefName1 + "&&" + f_FunctionDefName1 + "%%////";

				std::shared_ptr<classInsta> f_InstaVs = std::make_shared<classInsta>(f_StringE, ESL_INSTA_TYPE_FUNC_DEF);
							
				f_Function->m_vec_Insta.push_back(f_InstaVs);
				f_Function->m_idx_vec_Insta++;

				f_StringE += ESL_LINE_ENDING;
					
				f_Function->m_vec_String += f_StringE;

				f_LineCount--;
				f_LineIndexCount++;

				f_Contact = true;
				}
			}
		else if(f_LineType == ESL_INSTA_TYPE_CLASS_DEF)
			{
			if(1)//acRecordStrength(ESL_INSTA_TYPE_CLASS_DEF, f_Function, f_LineString, f_ElementIndex) == true)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_FunctionDefName1 = ac_recordMeasurement(ac_ext_eslLine_morf_array(f_LineString)[1][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_FunctionDefName2 = ac_recordMeasurement(ac_ext_eslLine_morf_array(f_LineString)[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_StringE = "FuncDef%%" + f_FunctionDefName1 + "%%" + f_FunctionDefName2 + "%%////";

				std::shared_ptr<classInsta> f_InstaVs = std::make_shared<classInsta>(f_StringE, ESL_INSTA_TYPE_FUNC_DEF);
							
				f_Function->m_vec_Insta.push_back(f_InstaVs);
				f_Function->m_idx_vec_Insta++;

				f_StringE += ESL_LINE_ENDING;
					
				f_Function->m_vec_String += f_StringE;
				f_LineCount--;
				f_LineIndexCount++;

				f_Contact = true;
				}
			}
		else if(f_LineType == ESL_INSTA_TYPE_CLASSVAR_DEF)
			{
			if(1)//acRecordStrength(ESL_INSTA_TYPE_CLASSVAR_DEF, f_Function, f_LineString, f_ElementIndex) == true)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_FunctionDefName1 = ac_recordMeasurement(ac_ext_eslLine_morf_array(f_LineString)[1][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_FunctionDefName2 = ac_recordMeasurement(ac_ext_eslLine_morf_array(f_LineString)[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_StringE = "FuncDef%%" + f_FunctionDefName1 + "&$" + f_FunctionDefName2 + "%%////";

				std::shared_ptr<classInsta> f_InstaVs = std::make_shared<classInsta>(f_StringE, ESL_INSTA_TYPE_FUNC_DEF);
							
				f_Function->m_vec_Insta.push_back(f_InstaVs);
				f_Function->m_idx_vec_Insta++;

				f_StringE += ESL_LINE_ENDING;
					
				f_Function->m_vec_String += f_StringE;
				f_LineCount--;
				f_LineIndexCount++;
				}
			}
		else
			{
			throw; //add debug message esl_insta_type out of bounds
			}

		  ///////////////////
		 //
		// Count Map
		if(f_Contact == true)
			{
#if 0
			if(m_idx_vec_CountLock > 0)
				{
				for(int f_cv = m_idx_vec_CountLock - 1; f_cv >= 0; f_cv--)
					{
					int f_Caramel = f_cv;

					m_vec_CountLock[f_Caramel]->m_Count--;
					
					if(m_vec_CountLock[f_Caramel]->m_Count <= 0)
						{
						bool f_on = true;

						if(f_Caramel < (m_idx_vec_CountLock - 1))
							{
							f_on = false;
							}
								
						if(f_on == true)
							{
							std::shared_ptr<classCountLock> f_Lock = m_vec_CountLock[f_Caramel];

							if(f_Lock->m_String.compare("ECNMiner_Affinity") == 0)
								{
								f_Function->m_vec_String += "Function%%EcomNative&*ECNMiner_Affinity%%////";
								f_LineCount--;

								//acResetLine();
								//f_Function->m_vec_CodeLineStorage.push_back(f_vec_CodeLine);
								//f_Function->m_idx_vec_CodeLineStorage++;

								//f_vec_CodeLine->m_vec_Code.clear();
								//f_vec_CodeLine->m_idx_vec_Code = 0;
								}

							acDecFactor(f_Lock->m_Factor);

							m_idx_vec_CountLock--;
								
							for(int f_XY = f_Caramel; f_XY < m_idx_vec_CountLock; f_XY++)
								{
								m_vec_CountLock[f_XY] = m_vec_CountLock[f_XY + 1];
								}

							m_vec_CountLock.pop_back();
							}
						else
							{
							m_vec_CountLock[f_Caramel]->m_Count = 1;
							}
						}
					}
				}
#endif
			}

		bool f_ExtraLines = true;

		if(f_LineCount < 0)
			{
			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_ExtraLines = ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex);
			}
		else
			{
			f_ExtraLines = true;
			}

		if(f_ExtraLines == false)
			{
			f_Scan = false;
			}
		}

	f_Function->m_vec_String.pop_back();

	f_Function->m_vec_String += "####";

	std::shared_ptr<Qcom_eslfunction> f_func = f_Function->acConvert();
#pragma message("WARNING possible optimization point for any use other then not often")

#ifdef ECOIN_SECURE
#if 1
	ecoin::ag_EcoinSecure_Inf_Loop_Assert(f_func->m_vec_InitLineOrdered.size(), f_LineCount);
#pragma message("WARNING non-production runtime code")
#endif
#endif

	return f_func;
}

#if 1
void classTarget_ESL_Script::acFromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_ESL_Script> f_Target)
{
#if 0
	for(int f_Count = 0; f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
		{
		std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Hesh->vec_Bicycle[f_Count]);

		m_Collection->m_vec_Element.push_back(f_Element);
		m_Collection->m_idx_vec_Element++;
		}

	int f_ElementStartAD = 0;
	int f_EndAD = 0;
		
	m_SchemaTop = 0;
	m_SchemaRef[0]->m_X = 0.120;
	m_SchemaRef[0]->m_Y = 0.70;
	m_SchemaRef[0]->m_Z = 0.95;
	m_SchemaRef[1]->m_X = 0.120;
	m_SchemaRef[1]->m_Y = 0.70;
	m_SchemaRef[1]->m_Z = 0.95;
	m_SchemaRef[2]->m_X = 0.120;
	m_SchemaRef[2]->m_Y = 0.70;
	m_SchemaRef[2]->m_Z = 0.95;
	m_SchemaRef[3]->m_X = 0.120;
	m_SchemaRef[3]->m_Y = 0.70;
	m_SchemaRef[3]->m_Z = 0.95;
	m_SchemaRef[4]->m_X = 0.120;
	m_SchemaRef[4]->m_Y = 0.70;
	m_SchemaRef[4]->m_Z = 0.95;
	m_SchemaRef[5]->m_X = 0.120;
	m_SchemaRef[5]->m_Y = 0.70;
	m_SchemaRef[5]->m_Z = 0.95;
	m_SchemaRef[6]->m_X = 0.120;
	m_SchemaRef[6]->m_Y = 0.70;
	m_SchemaRef[6]->m_Z = 0.95;
	m_SchemaRef[7]->m_X = 0.120;
	m_SchemaRef[7]->m_Y = 0.70;
	m_SchemaRef[7]->m_Z = 0.95;
	m_SchemaRef[8]->m_X = 0.120;
	m_SchemaRef[8]->m_Y = 0.70;
	m_SchemaRef[8]->m_Z = 0.95;
	m_SchemaRef[9]->m_X = 0.120;
	m_SchemaRef[9]->m_Y = 0.70;
	m_SchemaRef[9]->m_Z = 0.95;
	m_SchemaRef[10]->m_X = 0.120;
	m_SchemaRef[10]->m_Y = 0.70;
	m_SchemaRef[10]->m_Z = 0.95;
	m_SchemaRef[11]->m_X = 0.120;
	m_SchemaRef[11]->m_Y = 0.70;
	m_SchemaRef[11]->m_Z = 0.95;
	m_SchemaRef[12]->m_X = 0.120;
	m_SchemaRef[12]->m_Y = 0.70;
	m_SchemaRef[12]->m_Z = 0.95;
	m_SchemaRef[13]->m_X = 0.120;
	m_SchemaRef[13]->m_Y = 0.70;
	m_SchemaRef[13]->m_Z = 0.95;
	m_SchemaRef[14]->m_X = 0.120;
	m_SchemaRef[14]->m_Y = 0.70;
	m_SchemaRef[14]->m_Z = 0.95;
	m_SchemaRef[15]->m_X = 0.120;
	m_SchemaRef[15]->m_Y = 0.70;
	m_SchemaRef[15]->m_Z = 0.95;
	m_SchemaRef[16]->m_X = 0.120;
	m_SchemaRef[16]->m_Y = 0.70;
	m_SchemaRef[16]->m_Z = 0.95;
	m_SchemaRef[17]->m_X = 0.120;
	m_SchemaRef[17]->m_Y = 0.70;
	m_SchemaRef[17]->m_Z = 0.95;
	g_SchemaSize = 3;
	
	shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[0];
	
	int f_FunctionCount = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 1);
	f_FunctionCount = 1;

	for(int f_Jet = 0; f_Jet < f_FunctionCount; f_Jet++)
		{
		m_vec_CountLock.clear();

		int f_FunctionType = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 2);
		//int f_ArgumentCount = ac_takeMeasurementINTV1(f_Element, 0, 2, 2, 3, 3);
		int f_LineCount = ac_takeMeasurementINTV1(f_Element, 1, 500, 20, 3, 4);
		//f_LineCount = f_InstaCountMap;
		
		std::shared_ptr<classCodeLine> f_vec_CodeLine = std::make_shared<classCodeLine>();

		std::shared_ptr<classFunction> f_Function = std::make_shared<classFunction>();
		f_Function->m_Type = f_FunctionType;
		f_Function->m_Name = ac_takeMeasurement(f_Element);
		
		std::string f_StringA = "FuncDef%%" + f_Function->m_Name + "&*ECNMiner_Affinity%%////";
		f_StringA += ESL_LINE_ENDING;

		std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringA, ESL_INSTA_TYPE_FUNC_DEF);

		f_Function->m_vec_Insta.push_back(f_Insta);
		f_Function->m_idx_vec_Insta++;
		
		/*for(int f_Int = 0; f_Int < f_ArgumentCount; f_Int++)
			{
			std::string f_VarNameA = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
			std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_VarNameA, ESL_INSTA_TYPE_VAR_DEF);

			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;

			if(ac_takeMeasurementBLTV1(f_Element, 2, 0))
				{
				char f_Char[150];
				FillChar(f_Char, 150);

				if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));

					f_StringA += "Var%%" + f_VarNameA + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));

					f_StringA += "Var%%" + f_VarNameA + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));

					f_StringA += "Var%%" + f_VarNameA + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));

					f_StringA += "Var%%" + f_VarNameA + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					::sprintf(f_Char, "Random");

					f_StringA += "Var%%" + f_VarNameA + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_SYSTEM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					std::string f_SysName = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "Random");
						}

					f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_VARCALL, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					std::string f_VarName = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

					f_StringA += "Var%%" + f_VarName + "%%";
					}

				f_StringA += "////";
				}
			else
				{
				f_StringA += "Var%%" + f_VarNameA + "%%////";
				}

			f_StringA += ESL_LINE_ENDING;
			}

		f_Function->m_vec_String += f_StringA;
		
		acResetLine();*/
		
		m_idx_vec_CountLock = 0;
		
		while(f_LineCount > 0)
			{
			bool f_Contact = false;
				
			int f_InstaType = ac_takeMeasurementINTV1(f_Element, 0, ESL_INSTA_TYPE_COUNT, 2, 3, 6);

			if(f_InstaType == ESL_INSTA_TYPE_VAR_DEF)
				{
				if(acFactorStrength(ESL_INSTA_TYPE_VAR_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

					char f_Char[150];
					FillChar(f_Char, 150);

					std::string f_StringB;
					f_StringB.clear();

					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 0.0f, 1.0f, 0.0f, 2));

						f_StringB += "Var%%" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 1.0f, 100.0f, 0.0f, 2));

						f_StringB += "Var%%" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2));

						f_StringB += "Var%%" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2));

						f_StringB += "Var%%" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "Random");

						f_StringB += "Var%%" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_VARCALL, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						f_StringB += "Var%%" + f_Name + "%%0.0&%////";

						std::string f_VarName = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

						::sprintf(f_Char, "Opr%%Plus**Fork1%%Sys%%%s", f_VarName);

						f_StringB += "Var%%" + f_VarName + "%%" + f_Char + "%%";
						}

					f_StringB += ESL_LINE_ENDING;

					std::shared_ptr<classInsta> f_InstaVs = std::make_shared<classInsta>(f_StringB, ESL_INSTA_TYPE_VAR_DEF);

					f_Function->m_vec_Insta.push_back(f_InstaVs);
					f_Function->m_idx_vec_Insta++;

					f_Function->m_vec_String += f_StringB;
					f_LineCount--;
					
					f_Contact = true;
					}
				}
			else if(f_InstaType == ESL_INSTA_TYPE_CONDITIONAL)
				{
				if(acFactorStrength(ESL_INSTA_TYPE_CONDITIONAL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					std::string f_StringB = "Cond%%";
					std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta>(f_StringB, ESL_INSTA_TYPE_CONDITIONAL);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;

					int f_FingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 1, 3, 2);
								
					if(f_FingerCount <= 1)
						{
						f_StringB += "==^^";
						}
					else if(f_FingerCount == 2)
						{
						f_StringB += "!=^^";
						}
					else if(f_FingerCount == 3)
						{
						f_StringB += "<<^^";
						}
					else if(f_FingerCount == 4)
						{
						f_StringB += ">>^^";
						}
					else if(f_FingerCount == 5)
						{
						f_StringB += "<=^^";
						}
					else
						{
						f_StringB += ">=^^";
						}

					f_Function->m_vec_String += f_StringB;
					f_LineCount--;
					
					std::vector<int> f_conInstaCount;
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 0, 2, 0, 3, 4));
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 1, 12, 0, 3, 5));
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 2, 25, 4, 3, 6));
					int f_Select = ac_takeMeasurementINTV1(f_Element, 0, 3, 1, 3, 3);
					
					m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_conInstaCount[f_Select], "ECNMiner_Affinity", ESL_INSTA_TYPE_CONDITIONAL));
					m_idx_vec_CountLock++;
					
					f_Contact = true;
					}
				}
			else if(f_InstaType == ESL_INSTA_TYPE_LOOP_DEF)
				{
				/*if(acFactorStrength(ESL_INSTA_TYPE_LOOP_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_forVarName = ac_takeMeasurement(f_Element);
					std::string f_Str = "for(int " + f_forVarName + " = 0; " + f_forVarName + " < " + f_Name + "; " + f_forVarName + "++)\n	{\n 	";
					std::shared_ptr<classInsta> f_Insta = std::make_shared<classInsta(f_Str, ESL_INSTA_TYPE_LOOP_DEF);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_Str;
					f_LineCount--;
					
					int f_loopInstaCount = ac_takeMeasurementINTV1(f_Element, 8, 105, 8, 3, 1);
					
					m_vec_CountLock.push_back(std::make_shared<classCountLock(f_loopInstaCount, "\n}\n", ESL_INSTA_TYPE_LOOP_DEF));
					m_idx_vec_CountLock++;
					f_Contact = true;
					}*/
				}
			else if(f_InstaType == ESL_INSTA_TYPE_FUNC_CALL)
				{
				if(acFactorStrength(ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					//target restriction point
					std::string f_ReturnVarName = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_FunctionName = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_Element, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
					std::string f_Var1Name = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_Element, f_Function->m_idx_vec_Insta + 2, m_idx_vec_Function);
					std::string f_Var2Name = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_Element, f_Function->m_idx_vec_Insta + 3, m_idx_vec_Function);

					std::string f_StringB = "Var%%" + f_ReturnVarName + "%%1.0&%Fcn%%" + f_FunctionName + "&*" + f_FunctionName + "FUNCCALL%%Var%%" + f_Var1Name + "%%1.0&%Var%%" + f_Var2Name + "%%0.0&%////";
					f_StringB += ESL_LINE_ENDING;
					
					std::shared_ptr<classInsta> f_InstaR = std::make_shared<classInsta>(f_ReturnVarName, ESL_INSTA_TYPE_VAR_CALL);
					std::shared_ptr<classInsta> f_InstaA1 = std::make_shared<classInsta>(f_Var1Name, ESL_INSTA_TYPE_VAR_CALL);
					std::shared_ptr<classInsta> f_InstaA2 = std::make_shared<classInsta>(f_Var2Name, ESL_INSTA_TYPE_VAR_CALL);
					std::shared_ptr<classInsta> f_InstaB = std::make_shared<classInsta>(f_FunctionName, ESL_INSTA_TYPE_FUNC_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaR);
					f_Function->m_idx_vec_Insta++;
					f_Function->m_vec_Insta.push_back(f_InstaB);
					f_Function->m_idx_vec_Insta++;
					f_Function->m_vec_Insta.push_back(f_InstaA1);
					f_Function->m_idx_vec_Insta++;
					f_Function->m_vec_Insta.push_back(f_InstaA2);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_StringB;
					f_LineCount--;
					
					int f_arguInstaCount = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 4);
					
				    f_Contact = true;
					}
				}
			else if(f_InstaType == ESL_INSTA_TYPE_FUNC_DEF)
				{
				if(acFactorStrength(ESL_INSTA_TYPE_FUNC_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					std::string f_FunctionDefName = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_Element, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

					std::string f_StringE = "FuncDef%%" + f_FunctionDefName + "&*ECNMiner_Affinity%%////";
					f_StringA += ESL_LINE_ENDING;

					std::shared_ptr<classInsta> f_InstaVs = std::make_shared<classInsta>(f_StringE, ESL_INSTA_TYPE_FUNC_DEF);
							
					f_Function->m_vec_Insta.push_back(f_InstaVs);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_StringE;
					f_LineCount--;
					}
				}
				
			  ///////////////////
			 //
			// Count Map
			if(f_Contact == true)
				{
				f_vec_CodeLine->m_vec_Code.push_back(f_Function->m_vec_Insta[f_Function->m_idx_vec_Insta - 1]);
				f_vec_CodeLine->m_idx_vec_Code++;
					
				if(m_idx_vec_CountLock > 0)
					{
					for(int f_cv = m_idx_vec_CountLock - 1; f_cv >= 0; f_cv--)
					     {
					     int f_Caramel = f_cv;

					     m_vec_CountLock[f_Caramel]->m_Count--;
					
					     if(m_vec_CountLock[f_Caramel]->m_Count <= 0)
							{
							bool f_on = true;

							if(f_Caramel < (m_idx_vec_CountLock - 1))
								{
								f_on = false;
								}
								
							if(f_on == true)
								{
								std::shared_ptr<classCountLock> f_Lock = m_vec_CountLock[f_Caramel];

								f_Function->m_vec_String += f_Lock->m_String;

								if(f_Lock->m_String.compare("\n") != 0)
									{
									acResetLine();
									f_Function->m_vec_CodeLineStorage.push_back(f_vec_CodeLine);
									f_Function->m_idx_vec_CodeLineStorage++;

									f_vec_CodeLine->m_vec_Code.clear();
									f_vec_CodeLine->m_idx_vec_Code = 0;
									}

								acDecFactor(f_Lock->m_Factor);

								m_idx_vec_CountLock--;
								
								for(int f_XY = f_Caramel; f_XY < m_idx_vec_CountLock; f_XY++)
									{
									m_vec_CountLock[f_XY] = m_vec_CountLock[f_XY + 1];
									}
								
								if(f_Lock->m_String.compare(")") == 0)
									{
									bool f_ont = true;
									
									for(int f_cv1 = 1; f_cv1 < m_idx_vec_CountLock; f_cv1++)
										{
										for(int f_cv3 = 0; f_cv3 < m_vec_CountLock[f_cv1]->m_String.length(); f_cv3++)
											{
											if(m_vec_CountLock[f_cv1]->m_String.at(f_cv3) == ')')
												{
												f_ont = false;
												}
											}
										}
										
									if(f_ont == true)
										{
										acResetLine();
										f_Function->m_vec_CodeLineStorage.push_back(f_vec_CodeLine);
										f_Function->m_idx_vec_CodeLineStorage++;
										f_Function->m_vec_String += ";\n";

										f_vec_CodeLine->m_vec_Code.clear();
										f_vec_CodeLine->m_idx_vec_Code = 0;
										}
									}

								m_vec_CountLock.pop_back();
								}
							else
								{
								m_vec_CountLock[f_Caramel]->m_Count = 1;
								}
							}
						}
					}
				}
			}

		f_Function->m_vec_String.pop_back();

		f_Function->m_vec_String += "####";

		m_String += f_Function->m_vec_String;

		m_vec_Function.push_back(f_Function);
		m_idx_vec_Function++;
		}
#endif
}
#endif

void classTarget_JScript::acMergeUpper(void)
{
	/*for(int f_XY = 0; f_XY < m_CollectionScript->m_idx_vec_ElementScript; f_XY++)
		{
		//m_CollectionScript->m_vec_Element[m_CollectionScript->m_idx_vec_Element] = g_MasterTarget->m_CollectionScript->m_vec_Element[f_XY];
		//m_CollectionScript->m_idx_vec_Element++;
		//m_CollectionScript->m_vec_ElementScript[m_CollectionScript->m_idx_vec_ElementScript] = g_MasterTarget->m_CollectionScript->m_vec_ElementScript[f_XY];
		//m_CollectionScript->m_idx_vec_ElementScript++;
		}*/
	
	for(int f_Count = 0; f_Count < g_MasterTarget->m_idx_vec_Name; f_Count++)
		{
		m_vec_Name.push_back(g_MasterTarget->m_vec_Name[f_Count]);
		m_idx_vec_Name++;
		}
}
			
void classTarget_JScript::acMergeSave(void)
{
	/*for(int f_XY = 0; f_XY < m_CollectionScript->m_idx_vec_ElementScript; f_XY++)
		{
		g_MasterTarget->m_CollectionScript->m_vec_Element[g_MasterTarget->m_CollectionScript->m_idx_vec_Element] = m_CollectionScript->m_vec_Element[f_XY];
		g_MasterTarget->m_CollectionScript->m_idx_vec_Element++;
		//g_MasterTarget->m_CollectionScript->m_vec_ElementScript[g_MasterTarget->m_CollectionScript->m_idx_vec_ElementScript] = m_CollectionScript->m_vec_ElementScript[f_XY];
		//g_MasterTarget->m_CollectionScript->m_idx_vec_ElementScript++;
		}*/
		
	for(int f_CAP = 0; f_CAP < m_idx_vec_Name; f_CAP++)
		{
		g_MasterTarget->m_vec_Name.push_back(m_vec_Name[f_CAP]);
		g_MasterTarget->m_idx_vec_Name++;
		}
		
	g_MasterTarget->m_String += m_String;
}

bool classTarget_Ecom::acCompare(std::shared_ptr<classTarget_Ecom> f_Target, float f_QualityRank, float f_Grade)
{

	return false;
}

bool classLMap::acCompute(std::shared_ptr<classCollection> f_Collection, int f_OCSCP_ThreadIndex, bool f_Lowton)
{
	bool f_Success = true;

	if(f_Lowton == true)
		{
		if(g_ComputeText_PrintMode_Lowton == ECOIN_MUTEX_MODE_OFF)
			{
			g_ComputeText_PrintMode_Lowton = ECOIN_MUTEX_MODE_GATHER;
			g_ComputeText_Lowton.clear();

			acPrepareLense(f_OCSCP_ThreadIndex);

			int f_CorrectCount = 0;

			for(int f_Helly = 0; f_Helly < m_LMap->m_vec_Measure.size(); f_Helly++)
				{
#if 0
				int f_ElementIndex = m_LMap->m_vec_ElementID[f_ElementIndex];
#else
				int f_ElementIndex = acPull_gen_ElementID(0, f_Collection->m_vec_Element.size(), f_Collection->m_vec_Element.size(), 1, f_OCSCP_ThreadIndex);
#endif

				if(f_ElementIndex < f_Collection->m_vec_Element.size())
					{
					std::shared_ptr<LMeasure> f_LMeasure = m_LMap->m_vec_Measure[f_Helly];
					std::shared_ptr<classElement> f_Element = f_Collection->m_vec_Element[f_ElementIndex];

					if(f_Success == true)
						{
						switch(f_LMeasure->m_LMType)
							{
							case LMTYPE_Measurement:
								{
#if 0
								std::string f_MeasureString = ac_takeMeasurement(f_Element);

								if(f_MeasureString.compare(f_LMeasure->m_Measurement) != 0)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}
					
								g_ComputeText_Lowton += f_MeasureString + " - " +  + "-" + f_LMeasure->m_Measurement + " - " + "\n";
#endif
								}break;

							case LMTYPE_MeasurementINTV1:
								{
								int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

								if(f_MeasureInteger != f_LMeasure->m_MeasurementINTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}
								else
									{
									f_CorrectCount++;
									}
						
								char* f_Char = ag_ClearChar(32);

								::sprintf(f_Char, "%i * %i | %i * %i\n", f_MeasureInteger, f_LMeasure->m_EndRange, f_LMeasure->m_MeasurementINTV1, f_LMeasure->m_EndRange);

								g_ComputeText_Lowton += f_Char;

								delete f_Char;

								}break;

							case LMTYPE_MeasurementFLTV1:
								{
#ifdef ECOIN_SCP_RECORD_FLOAT
								float f_MeasureFloat = ac_takeMeasurementFLTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap);

								int f_IntegralFloat = (int)(f_MeasureFloat);

								if(f_IntegralFloat != f_LMeasure->m_MeasurementINTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}

								char* f_Char = ag_ClearChar(32);

								::sprintf(f_Char, "%f - %f\n", f_MeasureFloat, f_LMeasure->m_MeasurementFLTV1);

								g_ComputeText_Lowton += f_Char;

								//delete f_Char;
#endif
								}break;

							case LMTYPE_MeasurementBLTV1:
								{
								bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

								if(f_MeasureBoolean != f_LMeasure->m_MeasurementBLTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}
								else
									{
									f_CorrectCount++;
									}

								char* f_Char = ag_ClearChar(32);

								::sprintf(f_Char, "%i * %s | %i * %s\n", f_MeasureBoolean, "true", f_LMeasure->m_MeasurementBLTV1, "true");

								g_ComputeText_Lowton += f_Char;

								delete f_Char;

								}break;
							}
						}
					else
						{
						f_Element->m_OCSCP_Flag = false;
						}
					}
				}

			if(f_Success == true)
				{
				char* f_CharX = ag_ClearChar(32);

				::sprintf(f_CharX, "%i Correct Measures True\n%i Measures %i Elements\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size());

				g_ComputeText_Lowton += f_CharX;

				delete f_CharX;
				}
			else
				{
				char* f_CharX = ag_ClearChar(32);

				::sprintf(f_CharX, "%i Correct Measures False\n%i Measures %i Elements\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size());

				g_ComputeText_Lowton += f_CharX;

				delete f_CharX;
				}

			g_ComputeText_PrintMode_Lowton = ECOIN_MUTEX_MODE_PRINT;
			}
		}
	else //mainflow
		{
		if(g_ComputeText_PrintMode == ECOIN_MUTEX_MODE_OFF)
			{
			g_ComputeText_PrintMode = ECOIN_MUTEX_MODE_GATHER;
			g_ComputeText.clear();

			acPrepareLense(f_OCSCP_ThreadIndex);

			for(int f_Helly = 0; f_Helly < m_LMap->m_vec_Measure.size(); f_Helly++)
				{
#if 0
				int f_ElementIndex = m_LMap->m_vec_ElementID[f_ElementIndex];
#else
				int f_ElementIndex = acPull_gen_ElementID(0, f_Collection->m_vec_Element.size(), f_Collection->m_vec_Element.size(), 1, f_OCSCP_ThreadIndex);
#endif

				if(f_ElementIndex < f_Collection->m_vec_Element.size())
					{
					std::shared_ptr<LMeasure> f_LMeasure = m_LMap->m_vec_Measure[f_Helly];
					std::shared_ptr<classElement> f_Element = f_Collection->m_vec_Element[f_ElementIndex];

					if(f_Success == true)
						{
						switch(f_LMeasure->m_LMType)
							{
							case LMTYPE_Measurement:
								{
#if 0
								std::string f_MeasureString = ac_takeMeasurement(f_Element);

								if(f_MeasureString.compare(f_LMeasure->m_Measurement) != 0)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}
					
								g_ComputeText += f_MeasureString + " - " +  + "-" + f_LMeasure->m_Measurement + " - " + "\n";
#endif
								}break;

							case LMTYPE_MeasurementINTV1:
								{
								int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

								if(f_MeasureInteger != f_LMeasure->m_MeasurementINTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}
						
								char* f_Char = ag_ClearChar(32);

								::sprintf(f_Char, "%i - %i | %i - %i\n", f_MeasureInteger, f_LMeasure->m_EndRange, f_LMeasure->m_MeasurementINTV1, f_LMeasure->m_EndRange);

								g_ComputeText += f_Char;

								delete f_Char;

								}break;

							case LMTYPE_MeasurementFLTV1:
								{
#ifdef ECOIN_SCP_RECORD_FLOAT
								float f_MeasureFloat = ac_takeMeasurementFLTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap);

								int f_IntegralFloat = (int)(f_MeasureFloat);

								if(f_IntegralFloat != f_LMeasure->m_MeasurementINTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}

								char* f_Char = ag_ClearChar(32);

								::sprintf(f_Char, "%f - %f\n", f_MeasureFloat, f_LMeasure->m_MeasurementFLTV1);

								g_ComputeText += f_Char;

								//delete f_Char;
#endif
								}break;

							case LMTYPE_MeasurementBLTV1:
								{
								bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

								if(f_MeasureBoolean != f_LMeasure->m_MeasurementBLTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}

								char* f_Char = ag_ClearChar(32);

								::sprintf(f_Char, "%i - %s | %i - %s\n", f_MeasureBoolean, "true", f_LMeasure->m_MeasurementBLTV1, "true");

								g_ComputeText += f_Char;

								delete f_Char;

								}break;
							}
						}
					else
						{
						f_Element->m_OCSCP_Flag = false;
						}
					}
				else
					{
					f_Success = false;
					}
				}

			g_ComputeText_PrintMode = ECOIN_MUTEX_MODE_PRINT;
			}
		else
			{
			acPrepareLense(f_OCSCP_ThreadIndex);

			for(int f_Helly = 0; f_Helly < m_LMap->m_vec_Measure.size(); f_Helly++)
				{
#if 0
				int f_ElementIndex = m_LMap->m_vec_ElementID[f_Helly];
#else
				int f_ElementIndex = acPull_gen_ElementID(0, f_Collection->m_vec_Element.size(), f_Collection->m_vec_Element.size(), 1, f_OCSCP_ThreadIndex);
#endif

				if(f_ElementIndex < f_Collection->m_vec_Element.size())
					{
					std::shared_ptr<LMeasure> f_LMeasure = m_LMap->m_vec_Measure[f_Helly];
					std::shared_ptr<classElement> f_Element = f_Collection->m_vec_Element[f_ElementIndex];

					if(f_Success == true)
						{
						switch(f_LMeasure->m_LMType)
							{
							case LMTYPE_Measurement:
								{
#if 0
								std::string f_MeasureString = ac_takeMeasurement(f_Element);

								if(f_MeasureString.compare(f_LMeasure->m_Measurement) != 0)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}
#endif
								}break;

							case LMTYPE_MeasurementINTV1:
								{
								int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

								if(f_MeasureInteger != f_LMeasure->m_MeasurementINTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}
								}break;

							case LMTYPE_MeasurementFLTV1:
								{
#ifdef ECOIN_SCP_RECORD_FLOAT
								float f_MeasureFloat = ac_takeMeasurementFLTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap);

								int f_IntegralFloat = (int)(f_MeasureFloat);

								if(f_IntegralFloat != f_LMeasure->m_MeasurementINTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}
#endif
								}break;

							case LMTYPE_MeasurementBLTV1:
								{
								bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

								if(f_MeasureBoolean != f_LMeasure->m_MeasurementBLTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;
									}
								}break;
							}
						}
					else
						{
						f_Element->m_OCSCP_Flag = false;
						}
					}
				else
					{
					f_Success = false;
					}
				}
			}
		}

	return f_Success;
}

bool classTarget_ESL_Script::acCompare(std::shared_ptr<classTarget_ESL_Script> f_Target, float f_QualityRank, float f_Grade)
{

	return false;
}

bool classTarget_JScript::acCompare(std::shared_ptr<classTarget_JScript> f_Target, float f_QualityRank, float f_Grade)
{
	f_Target->m_Mark = 0.0;
	
	 /////////////////////
	// Prime Evaluation
	//for(int f_XY = 0; f_XY < m_idx_vec_Function; f_XY++)
	//	{
	//	int f_Mark = f_Function->acInterrogate(f_QualityRank);
		
		std::shared_ptr<classMark> f_Mark = acMark_Bridges();
		
		if(g_EnablePR == true)
			{
			f_Mark->acIncrement(acMark_TestICO(f_Target));
			}
		
		f_Target->m_Mark = f_Mark->acSumStuff(f_QualityRank);
	//	}
	//else
	//	{
	//	return false;
	//	}
	
	 ///////////////////////
	// Prime Conditional
	if(f_Target->m_Mark >= f_Grade)
		{
		return true;
		}
	else
		{
		return false;
		}
}

/*classTarget_JScript.prototype.acCompareStructure = function(f_Target, f_QualityRank, f_Grade, f_testVolumes)
{
	f_Target->m_Mark = 0.0;
	
	 /////////////////////
	//Prime Conditional
	if(m_CollectionScript->m_idx_vec_ElementScript < f_Target->m_Collection->m_idx_vec_ElementScript)
		{
		for(int f_Count = 0; f_Count < m_Collection->m_idx_vec_Element; f_Count++)
			{
			var f_Element = m_Collection->m_vec_Element[f_Count];
			var f_TestElement = f_Target->m_Collection->m_vec_Element[f_Count];

			f_Target->m_Mark += f_Element.acCompare(f_TestElement, f_QualityRank, f_testVolumes);
			}
		}
	else
		{
		for(int f_Count = 0; f_Count < m_Collection->m_idx_vec_Element; f_Count++)
			{
			var f_fakeMark = 0.0;

			var f_Element = m_Collection->m_vec_Element[f_Count];
			var f_TestElement = f_Target->m_Collection->m_vec_Element[0];

			var f_Mark = f_Element.acCompare(f_TestElement, f_QualityRank, f_testVolumes);
			f_fakeMark = f_Mark;

			for(int f_Cam = 0; f_Cam < f_Target->m_Collection->m_idx_vec_Element; f_Cam++)
				{
				var f_Element = m_Collection->m_vec_Element[f_Count];
				var f_TestElement = f_Target->m_Collection->m_vec_Element[f_Cam];

				var f_Mark = f_Element.acCompare(f_TestElement, f_QualityRank, f_testVolumes);
				if(f_Mark < f_fakeMark)
					{
					f_fakeMark = f_Mark;
					}
				}

			f_Target->m_Mark += f_fakeMark;
			}
		}

	if((f_Target->m_Mark <= f_Grade) && (f_Target->m_Mark != 0.0) && (f_Target->m_Mark > 1060.0))
		{
		return true;
		}
	else
		{
		return false;
		}

	/*if(Math.random() < 0.1)
		{
		console.log("CubeHESHGen(" + f_True + ")QualityRank[" + f_QualityRank + "]:Mark " + f_Target->m_Mark + " < Diff(" + f_Grade + ")tVol=" + f_testVolumes);
		}*/
//}

classInsta::classInsta(std::string f_StringC, int f_Type)
{
	m_Type = f_Type;
	m_String = f_StringC;
	
	m_Value = 0.0;
}

/*classInsta.prototype.acInterrogation = function(f_LineCount, f_InstaCount, f_Line, f_LineSize)
{	
	var f_Mark = std::make_shared<classMark();
	
	 //////////////////////
	// Calc Results
	for(int f_Count = 0; f_Count < f_LineSize; f_Count++)
		{
		if(f_Line->m_vec_Code[f_Count]->m_Type != f_Target->m_vec_CodeLineStorage[f_LineCount][f_InstaCount]->m_Type)
			{
			f_Mark->m_vec_Int[0]++;
			}
			
		if(f_Count >= 1)
			{
			for(int f_inputCount = 0; f_inputCount < f_Target->m_idx_vec_CodeInputs; f_inputCount++)
				{
				if(f_Line->m_vec_Code[f_Count]->m_String != f_Target->m_vec_CodeInput[f_inputCount])
					{
					f_Mark->m_vec_Int[3]++;
					}
				}
			}
			
		if(f_Line->m_vec_Code[f_Count]->m_String != f_Target->m_vec_CodeLineStorage[f_LineCount][f_InstaCount]->m_String)
			{
			f_Mark->m_vec_Int[1]++;
			}
		}

	return f_Mark;
}*/

classMark::classMark()
{
	m_vec_Int.clear();
	m_idx_flip = 5;
	m_idx_vec_Int = 7;
	
	for(int f_X = 0; f_X < m_idx_vec_Int; f_X++)
		{
		m_vec_Int.push_back(0);
		}
}

void classMark::acReset(void)
{
	for(int f_X = 0; f_X < m_idx_vec_Int; f_X++)
		{
		m_vec_Int[f_X] = 0;
		}
}

void classMark::acIncrement(std::shared_ptr<classMark> f_Mark)
{
	for(int f_X = 0; f_X < m_idx_vec_Int; f_X++)
		{
		m_vec_Int[f_X] += f_Mark->m_vec_Int[f_X];
		}
}

float classMark::acSumStuff(float f_QualityRank)
{
	float f_Mark = 0.0;

	   ////////////////
	  //
	 //
	// Movin to positive Marking Scheme
	for(int f_X = m_idx_flip; f_X < m_idx_vec_Int; f_X++)
		{
		f_Mark += m_vec_Int[f_X] * f_QualityRank; //adjustment
		}
	
	for(int f_X = 0; f_X < m_idx_flip; f_X++)
		{
		f_Mark -= m_vec_Int[f_X] * f_QualityRank;
		}
		
	return f_Mark;
}

classAchievement::classAchievement()
{
	m_Mark = std::make_shared<classMark>();
	m_Success = false;
	
	//m_vec_ReturnArgs = [];
	//m_idx_vec_ReturnArgs = 0;
}

classFunction::classFunction()
{
	m_vec_String = "";
	
	m_Type = 0;
	m_Status = 0;

	m_Name = "";
	m_Hash = "";
	m_String = "";

	//>?
	//m_Level = [];
	//m_vec_Code = [];
	
	m_vec_Insta.clear();
	m_idx_vec_Insta = 0;
	
	m_vec_CodeLineStorage.clear();
	m_idx_vec_CodeLineStorage = 0;
	
	m_vec_CodeLineStorageFlag.clear();
	m_idx_vec_CodeLineStorageFlag = 0;

	m_Mark = std::make_shared<classMark>();
}

void classFunction::acInsertAuthority(shared_ptr<classElement> f_Element, int f_Index)
{
	//generate mebbe linked lists of input control output data for each class name and then
	//call insertAuthority
}

std::shared_ptr<classMark> classFunction::acTestElement(shared_ptr<classElement> f_Element, int f_Index)
{
	std::shared_ptr<classMark> f_Mark = std::make_shared<classMark>();
	
	//test element and producers return results
	//if(f_Element->m_Type == 
	//}
	//var f_Input = 
	
	return f_Mark;
}

/*std::shared_ptr<classMark> classFunction::acInterrogate(float f_QualityRank)
{
	m_Mark->acReset();
	
	for(int f_XY = 0; f_XY < m_idx_vec_CodeLineStorage; f_XY++)
		{
		for(int f_Helly = 0; f_Helly < m_vec_CodeLineStorage[f_XY]->m_idx_vec_Code; f_Helly++)
			{
			std::shared_ptr<classInsta> f_Insta = m_vec_CodeLineStorage[f_XY]->m_vec_Code[f_Helly];
			
			std::shared_ptr<classMark> f_MarkAdjust = f_Insta->acInterrogation(f_XY, f_Helly, m_vec_CodeLineStorage[f_XY], m_vec_CodeLineStorage[f_XY].size());

			m_Mark.acIncrement(f_MarkAdjust);
			}
		}
		
	return m_Mark;
}*/

std::string classTarget_JScript::ac_takeMeasurement(shared_ptr<classElement> f_Vertex)
{
	if(m_SchemaTop == 0)
		{
		std::string f_CharAry;
		f_CharAry.clear();

		int f_WordCount = ac_takeMeasurementINTV1(f_Vertex, 1, 3, 0, 3, 4);
		
		for(int f_XYZ = 0; f_XYZ < f_WordCount; f_XYZ++)
			{
			int f_CharCount = ac_takeMeasurementINTV1(f_Vertex, 3, 6, 1, 3, 4);
			//

			int f_SelectCharFi = ac_takeMeasurementINTV1(f_Vertex, 0, 25, 0, 3, 3);

			if(f_SelectCharFi < 0)
				{
				f_SelectCharFi = 0;
				}

			if(f_SelectCharFi > 25)
				{
				f_SelectCharFi = 25;
				}

			char f_CharFi = g_vec_AlphaUpper.at(f_SelectCharFi);

			f_CharAry += f_CharFi;

			for(int f_Jet = 0; f_Jet < f_CharCount; f_Jet++)
				{
				int f_SelectChar = ac_takeMeasurementINTV1(f_Vertex, 0, 25, 0, 3, 3);

				if(f_SelectChar < 0)
					{
					f_SelectChar = 0;
					}

				if(f_SelectChar > 25)
					{
					f_SelectChar = 25;
					}

				char f_Char = g_vec_AlphaLower.at(f_SelectChar);

				f_CharAry += f_Char;
				}
			}

		return f_CharAry;
		}

	return "abeebc";
}

std::string classTarget_ESL_Script::ac_takeMeasurement(shared_ptr<classElement> f_Vertex)
{
	if(m_SchemaTop == 0)
		{
		std::string f_CharAry;
		f_CharAry.clear();

		int f_WordCount = ac_takeMeasurementINTV1(f_Vertex, 1, 3, 0, 3, 4);
		
		for(int f_XYZ = 0; f_XYZ < f_WordCount; f_XYZ++)
			{
			int f_CharCount = ac_takeMeasurementINTV1(f_Vertex, 3, 6, 1, 3, 4);
			//

			int f_SelectCharFi = ac_takeMeasurementINTV1(f_Vertex, 0, 26, 0, 3, 3);

			if(f_SelectCharFi < 0)
				{
				f_SelectCharFi = 0;
				}

			if(f_SelectCharFi > 25)
				{
				f_SelectCharFi = 25;
				}

			char f_CharFi = g_vec_AlphaUpper.at(f_SelectCharFi);

			f_CharAry += f_CharFi;

			for(int f_Jet = 0; f_Jet < f_CharCount; f_Jet++)
				{
				int f_SelectChar = ac_takeMeasurementINTV1(f_Vertex, 0, 26, 0, 3, 3);

				if(f_SelectChar < 0)
					{
					f_SelectChar = 0;
					}

				if(f_SelectChar > 25)
					{
					f_SelectChar = 25;
					}

				char f_Char = g_vec_AlphaLower.at(f_SelectChar);

				f_CharAry += f_Char;
				}
			}

		return f_CharAry;
		}

	return "abeebc";
}

std::string classTarget_Ecom::ac_takeMeasurement(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth)
{
	if(m_SchemaTop == 0)
		{
		std::string f_CharAry;
		f_CharAry.clear();

		int f_WordCount = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 4, 0, 3);
		
		for(int f_XYZ = 0; f_XYZ < f_WordCount; f_XYZ++)
			{
			int f_CharCount = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 7, 1, 3);
			//

			int f_SelectCharFi = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 26, 0, 3);

			if(f_SelectCharFi < 0)
				{
				f_SelectCharFi *= -1;
				}

			if(f_SelectCharFi > 25)
				{
				f_SelectCharFi = 23;
				}

			char f_CharFi = g_vec_AlphaUpper.at(f_SelectCharFi);

			f_CharAry += f_CharFi;

			for(int f_Jet = 0; f_Jet < f_CharCount; f_Jet++)
				{
				int f_SelectChar = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 26, 0, 3);

				if(f_SelectChar < 0)
					{
					f_SelectChar *= 0;
					}

				if(f_SelectChar > 25)
					{
					f_SelectChar = 23;
					}

				char f_Char = g_vec_AlphaLower.at(f_SelectChar);

				f_CharAry += f_Char;
				}
			}

		return f_CharAry;
		}

	return "abeebc";
}

std::string classLMap::ac_takeMeasurement(shared_ptr<classElement> f_Vertex)
{
	if(m_SchemaTop == 0)
		{
		std::string f_CharAry;
		f_CharAry.clear();

		int f_WordCount = ac_takeMeasurementINTV1(f_Vertex, 0, 4, 0, 3, 4, 0);
		
		for(int f_XYZ = 0; f_XYZ < f_WordCount; f_XYZ++)
			{
			int f_CharCount = ac_takeMeasurementINTV1(f_Vertex, 1, 7, 1, 3, 4, 0);
			//

			int f_SelectCharFi = ac_takeMeasurementINTV1(f_Vertex, 0, 26, 0, 3, 3, 0);

			if(f_SelectCharFi < 0)
				{
				f_SelectCharFi = 0;
				}

			if(f_SelectCharFi > 25)
				{
				f_SelectCharFi = 23;
				}

			char f_CharFi = g_vec_AlphaUpper.at(f_SelectCharFi);

			f_CharAry += f_CharFi;

			for(int f_Jet = 0; f_Jet < f_CharCount; f_Jet++)
				{
				int f_SelectChar = ac_takeMeasurementINTV1(f_Vertex, 0, 26, 0, 3, 3, 0);

				if(f_SelectChar < 0)
					{
					f_SelectChar = 0;
					}

				if(f_SelectChar > 25)
					{
					f_SelectChar = 23;
					}

				char f_Char = g_vec_AlphaLower.at(f_SelectChar);

				f_CharAry += f_Char;
				}
			}

		return f_CharAry;
		}

	return "abeebc";
}

//element level specify schema
int classTarget_JScript::ac_takeMeasurementINTV1(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	int m_Depth = f_Depth + 1;
	m_Depth--;
	
	f_Cap = 0;
	
	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt].m_X, f_Vertex->vec_Vertex[f_HighestInt].m_Y, f_Vertex->vec_Vertex[f_HighestInt].m_Z);

			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * 0.77f;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * 0.77f;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * 0.77f;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;

			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			float f_RangeVal = (f_Theta * ((int)(f_EndRange) - f_StartRange));

			if(f_RangeVal < 0.0)
				{
				f_RangeVal = f_RangeVal * -1;
				}

			float f_FloatA = f_RangeVal - (f_WeightRangetoStart / 2);

			int f_Int = (int)(f_FloatA) + f_StartRange;

			return f_Int;
			}
		else if(m_SchemaTop == 1)
			{
			
			}
		else if(m_SchemaTop == 2)
			{
			
			}
		}

	return 1;
}

//element level specify schema
int classTarget_ESL_Script::ac_takeMeasurementINTV1(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;
	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt].m_X, f_Vertex->vec_Vertex[f_HighestInt].m_Y, f_Vertex->vec_Vertex[f_HighestInt].m_Z);

			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * 0.77f;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * 0.77f;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * 0.77f;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;

			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			float f_RangeVal = (f_Theta * ((int)(f_EndRange)-f_StartRange));

			if(f_RangeVal < 0.0)
				{
				f_RangeVal = f_RangeVal * -1;
				}

			float f_FloatA = f_RangeVal - (f_WeightRangetoStart / 2);

			int f_Int = (int)(f_FloatA) + f_StartRange;

			return f_Int;
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1;
}

//element level specify schema
float classTarget_ESL_Script::ac_takeMeasurementFLTV1(shared_ptr<classElement> f_Vertex, float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;
	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt].m_X, f_Vertex->vec_Vertex[f_HighestInt].m_Y, f_Vertex->vec_Vertex[f_HighestInt].m_Z);

			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * 0.77f;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * 0.77f;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * 0.77f;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;

			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			float f_RangeVal = f_Theta * (f_EndRange - f_StartRange);

			if(f_RangeVal < 0.0)
				{
				f_RangeVal = f_RangeVal * -1;
				}

			float f_FloatA = f_RangeVal - (f_WeightRangetoStart / 2);

			float f_FloatB = f_FloatA + f_StartRange;

			int f_IntegerConv = (int)(f_FloatB);

			return f_FloatB;
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1.0f;
}

//element level specify schema
bool classTarget_ESL_Script::ac_takeMeasurementBLTV1(shared_ptr<classElement> f_Vertex, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;
	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt].m_X, f_Vertex->vec_Vertex[f_HighestInt].m_Y, f_Vertex->vec_Vertex[f_HighestInt].m_Z);

			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * 0.77f;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * 0.77f;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * 0.77f;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;
				
			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			if(f_Theta > 0.0f)
				{
				return true;
				}
			else
				{
				return false;
				}
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1.0f;
}

//element level specify schema
int classTarget_Ecom::ac_takeMeasurementINTV1(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Cap)  // scale resolution 1-3
{
	std::shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[ag_Pull_gen_Element(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_StartRange, f_EndRange, f_WeightRangetoStart)];

	//f_StartRange--;
	//f_EndRange++;
	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;
	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0f);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Element->vec_Vertex[f_HighestInt].m_X, f_Element->vec_Vertex[f_HighestInt].m_Y, f_Element->vec_Vertex[f_HighestInt].m_Z);

			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();

			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * 0.77f;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * 0.77f;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * 0.77f;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;

			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			float f_RangeVal = (f_Theta * ((float)(f_EndRange) - (float)f_StartRange));

			if(f_RangeVal < 0.0)
				{
				f_RangeVal = f_RangeVal * -1.0;
				}

			float f_FloatA = f_RangeVal - ((float)f_WeightRangetoStart / 2.0f);

			int f_Int = (int)(f_FloatA) + f_StartRange;

			return f_Int;
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1;
}

int classLMap::ac_takeMeasurementINTV1(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, int f_OCSCP_ThreadIndex)  // scale resolution 1-3
{
	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;
	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0f);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt].m_X, f_Vertex->vec_Vertex[f_HighestInt].m_Y, f_Vertex->vec_Vertex[f_HighestInt].m_Z);

			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();

			f_Vec->m_X = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_X * f_MeshVertex.m_X) * 0.77f;
			f_Vec->m_Y = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y * f_MeshVertex.m_Y) * 0.77f;
			f_Vec->m_Z = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z * f_MeshVertex.m_Z) * 0.77f;

			m_SchemaRef[f_OCSCP_ThreadIndex]->m_X = f_Vec->m_X;
			m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y = f_Vec->m_Y;
			m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z = f_Vec->m_Z;

			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			float f_RangeVal = (f_Theta * ((float)(f_EndRange) - (float)f_StartRange));

			if(f_RangeVal < 0.0f)
				{
				f_RangeVal = f_RangeVal * -1.0f;
				}

			float f_FloatA = f_RangeVal - ((float)f_WeightRangetoStart / 2.0f);

			int f_Int = (int)(f_FloatA) + f_StartRange;

			return f_Int;
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1;
}

int ag_Pull_gen_Element(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_OCSCP_ThreadIndex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart)
{
	float f_LMFactor = 1.0f / (float)g_CountLM;

	if(g_ElementDivisorFloat[f_OCSCP_ThreadIndex] >= 1.0f)
		{
		g_ElementDivisorFloat[f_OCSCP_ThreadIndex] = f_LMFactor;
		g_ElementDivisor[f_OCSCP_ThreadIndex]++;
		}
	else
		{
		g_ElementDivisorFloat[f_OCSCP_ThreadIndex] += f_LMFactor;
		}

	return g_ElementDivisor[f_OCSCP_ThreadIndex];
}

void LMeasure::acClear(void)
{
	m_LMType = -1;
	m_Measurement.clear();
	m_MeasurementINTV1 = 0;
	m_MeasurementFLTV1 = 0.0f;
	m_MeasurementBLTV1 = false;
	m_MeasurementINTS = 0;

	m_StartRange = 0;
	m_EndRange = 0;
	m_WeightRangetoStart = 0;
	m_Depth = 0;
	m_Cap = 0;
	m_RangeWidth = 0;
	m_Boundary = 0;
	m_Notable = true;
}

LMeasure::LMeasure(std::string f_Measurement)
{
	acClear();
	m_LMType = LMTYPE_Measurement;
	m_Measurement = f_Measurement;
}

LMeasure::LMeasure(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, int f_MeasurementINTV1)
{
	acClear();
	m_LMType = LMTYPE_MeasurementINTV1;
	m_MeasurementINTV1 = f_MeasurementINTV1;

	m_StartRange = f_StartRange;
	m_EndRange = f_EndRange;
	m_WeightRangetoStart = f_WeightRangetoStart;
	m_Depth = f_Depth;
	m_Cap = f_Cap;
}

LMeasure::LMeasure(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, float f_MeasurementFLTV1)
{
	acClear();
	m_LMType = LMTYPE_MeasurementFLTV1;
	m_MeasurementFLTV1 = f_MeasurementFLTV1;

	m_StartRange = f_StartRange;
	m_EndRange = f_EndRange;
	m_WeightRangetoStart = f_WeightRangetoStart;
	m_Depth = f_Depth;
	m_Cap = f_Cap;
}

LMeasure::LMeasure(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, float f_Boundary, float f_MeasurementFLTV5)
{
	acClear();
	m_LMType = LMTYPE_MeasurementFLTV5_LB;
	m_MeasurementFLTV1 = f_MeasurementFLTV5;

	m_StartRange = f_StartRange;
	m_EndRange = f_EndRange;
	m_WeightRangetoStart = f_WeightRangetoStart;
	m_Depth = f_Depth;
	m_Cap = f_Cap;
	m_Boundary = f_Boundary;
}

LMeasure::LMeasure(int f_Depth, int f_Cap, bool f_MeasurementBLTV1)
{
	acClear();
	m_LMType = LMTYPE_MeasurementBLTV1;
	m_MeasurementBLTV1 = f_MeasurementBLTV1;

	m_Depth = f_Depth;
	m_Cap = f_Cap;

	m_StartRange = -1;
	m_EndRange = -1;
	m_WeightRangetoStart = -1;
}

LMeasure::LMeasure(int f_RangeWidth, int f_WeightRangetoStart, int f_MeasurementINTS)
{
	acClear();
	m_LMType = LMTYPE_MeasurementBLTV1;
	m_MeasurementINTS = f_MeasurementINTS;

	m_RangeWidth = f_RangeWidth;
	m_WeightRangetoStart = f_WeightRangetoStart;
}

std::string classLMap::ac_recordMeasurement(std::string f_RecordResult, int f_ElementID, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	std::string f_CharAry;
	f_CharAry.clear();

	std::vector<int> f_vec_Len;
	f_vec_Len.clear();

	int f_WordCount = 0;
	int f_Carr = 0;

	for(int f_Jet = 0; f_Jet < f_RecordResult.length(); f_Jet++)
		{
		char f_c = f_RecordResult.at(f_Jet);

		f_Carr++;

		if(isupper(f_c) == true)
			{
			if(f_Jet >= (f_RecordResult.length() - 1))
				{
				f_WordCount++;
				f_WordCount++;

				f_vec_Len.push_back(f_Carr - 1);
				f_vec_Len.push_back(1);
				f_Carr = 0;
				}
			else
				{
				if(f_Carr > 1)
					{
					f_WordCount++;

					f_vec_Len.push_back(f_Carr - 1);
					f_Carr = 1;
					}
				}
			}
		else
			{
			if(f_Jet >= (f_RecordResult.length() - 1))
				{
				f_WordCount++;

				f_vec_Len.push_back(f_Carr);
				f_Carr = 0;
				}
			}
		}

	f_WordCount = ac_recordMeasurementINTV1(0, 4, 0, 3, 4, f_WordCount, f_ElementID);
		
	int f_AbsIDX = 0;
	for(int f_XYZ = 0; f_XYZ < f_WordCount; f_XYZ++)
		{
		f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_CharCount = ac_recordMeasurementINTV1(1, 7, 1, 3, 4, f_vec_Len[f_XYZ], f_ElementID);

		int f_MeasureFi = f_RecordResult.at(f_AbsIDX) - 'A';

		if(f_MeasureFi < 0)
			{
			f_MeasureFi *= -1;
			}

		if(f_MeasureFi > 25)
			{
			f_MeasureFi = 23;
			}

		f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_SelectCharFi = ac_recordMeasurementINTV1(0, 26, 0, 3, 3, f_MeasureFi, f_ElementID);

		char f_CharFi = g_vec_AlphaUpper.at(f_SelectCharFi);

		f_CharAry += f_CharFi;

		f_AbsIDX++;

		for(int f_Jet = 0; f_Jet < (f_CharCount - 1); f_Jet++)
			{
			int f_Measure = f_RecordResult.at(f_AbsIDX);

			f_Measure -= 'a';

			if(f_Measure < 0)
				{
				f_Measure *= -1;
				}

			if(f_Measure > 25)
				{
				f_Measure = 23;
				}

			f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			int f_SelectChar = ac_recordMeasurementINTV1(0, 26, 0, 3, 3, f_Measure, f_ElementID);

			char f_Char = g_vec_AlphaLower.at(f_SelectChar);

			f_CharAry += f_Char;

			f_AbsIDX++;
			}
		}

	return f_CharAry;

#if 0 //old string measure method
	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	//generate lense recording
	shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(f_RecordResult);

	//save
	m_LMap->m_vec_Measure.push_back(f_Measure);

	//return
	return f_RecordResult;
#endif
}

int classLMap::ac_recordMeasurementINTV1(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, int f_RecordResult, int f_ElementID, bool f_Notable)  // scale resolution 1-3
{
	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(f_StartRange, f_EndRange, f_WeightRangetoStart, f_Depth, f_Cap, f_RecordResult);

	f_Measure->m_Notable = f_Notable;

	//save lense recording
	m_LMap->m_vec_Measure.push_back(f_Measure);

	return f_RecordResult;
}

float classLMap::ac_recordMeasurementFLTV1(float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Depth, int f_Cap, float f_RecordResult, int f_ElementID)  // scale resolution 1-3
{
	char f_Char[150];
	::sprintf(f_Char, "%.8f", f_RecordResult);

	std::string f_ResultString = f_Char;

	bool f_Precise = false;

	int f_FixedCount = 0;

	for(int f_Jet = f_ResultString.length() - 1; f_Jet >= 0; f_Jet--)
		{
		char f_c = f_ResultString.at(f_Jet);

		if(f_c == '0')
			{
			f_ResultString.pop_back();
			}
		else if(f_c == '.')
			{
			f_Precise = true;
			f_Jet = 0;
			}
		else
			{
			f_FixedCount++;
			}
		}

	if(f_Precise != true)
		{
		f_ResultString.push_back('.');
		f_ResultString.push_back('0');
		f_FixedCount = 1;
		}

	float f_Max = FLT_MAX;

	char f_CharFM[150];

	::sprintf(f_CharFM, "%.8f", f_RecordResult);

	std::string f_MaxString = f_CharFM;

	int f_MaxLength = f_MaxString.length();

	int f_Length = ac_recordMeasurementINTV1(3, f_MaxLength, 0, 3, 1, f_ResultString.length(), f_ElementID);

	int f_FixLength = ac_recordMeasurementINTV1(0, 8, 0, 3, 1, f_FixedCount, f_ElementID);

	int f_MinChar = '0';

	std::string f_RecordedResult = "";

	for(int f_Jet = 0; f_Jet < f_Length - f_FixLength; f_Jet++)
		{
		char f_C = f_ResultString.at(f_Jet);
		
		if(f_C == '.')
			{
			throw; //add debug message float out of bounds
			}
		else
			{
			int f_CharOffset = ac_recordMeasurementINTV1(0, 9, 0, 3, 1, (f_C - f_MinChar), f_ElementID);

			f_RecordedResult.push_back(f_RecordResult + f_MinChar);
			}
		}

	f_RecordedResult.push_back('.');

	for(int f_Jet = f_Length - f_FixedCount; f_Jet < f_Length; f_Jet++)
		{
		char f_C = f_ResultString.at(f_Jet);
		
		if(f_C == '.')
			{
			throw; //add debug message float out of bounds
			}
		else
			{
			int f_CharOffset = ac_recordMeasurementINTV1(0, 9, 0, 3, 1, (f_C - f_MinChar), f_ElementID);

			f_RecordedResult.push_back(f_RecordResult + f_MinChar);
			}
		}

#if 0
	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(f_StartRange, f_EndRange, f_WeightRangetoStart, f_Depth, f_Cap, f_ResultIntegralFloat);

	//save lense recording
	m_LMap->m_vec_Measure.push_back(f_Measure);
#endif

	float f_ResultFLT = atof(f_RecordedResult.c_str());

	return f_ResultFLT;
}

void classLMap::ac_recordMeasurementFLTV5_LowBounds(float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Depth, int f_Cap, float f_Boundary, float f_RecordResult, int f_ElementID)
{
	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(f_StartRange, f_EndRange, f_WeightRangetoStart, f_Depth, f_Cap, f_Boundary, f_RecordResult);

	//save lense recording
	m_LMap->m_vec_Measure.push_back(f_Measure);
}

bool classLMap::ac_recordMeasurementBLTV1(int f_Depth, int f_Cap, bool f_RecordResult, int f_ElementID)  // scale resolution 1-3
{
	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	shared_ptr<LMeasure> f_Measure = make_shared<LMeasure>(f_Depth, f_Cap, f_RecordResult);

	//save lense recording
	m_LMap->m_vec_Measure.push_back(f_Measure);

	return f_RecordResult;
}

//element level specify schema
float classTarget_Ecom::ac_takeMeasurementFLTV1(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Cap)  // scale resolution 1-3
{
	float f_Max = FLT_MAX;

	char f_CharFM[150];
	::sprintf(f_CharFM, "%.8f", f_Max);
	std::string f_MaxString = f_CharFM;

	int f_Length = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 3, f_MaxString.length(), 0, 5);

	int f_FixLength = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 8, 0, 4);

	int f_MinChar = '0';

	std::string f_RecordedResult = "";

	for(int f_Jet = 0; f_Jet < f_Length - f_FixLength; f_Jet++)
		{
		char f_C = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 9, 0, 4) + f_MinChar;
		
		f_RecordedResult.push_back(f_C);
		}

	f_RecordedResult.push_back('.');

	for(int f_Jet = f_Length - f_FixLength; f_Jet < f_Length; f_Jet++)
		{
		char f_C = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 9, 0, 4) + f_MinChar;

		f_RecordedResult.push_back(f_C);
		}

	float f_ResultFLT = atof(f_RecordedResult.c_str());

	return f_ResultFLT;
}

float classLMap::ac_takeMeasurementFLTV1(shared_ptr<classElement> f_Vertex, float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;
	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt].m_X, f_Vertex->vec_Vertex[f_HighestInt].m_Y, f_Vertex->vec_Vertex[f_HighestInt].m_Z);

			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * 0.77f;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * 0.77f;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * 0.77f;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;

			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			float f_RangeVal = (f_Theta * (f_EndRange - f_StartRange));

			if(f_RangeVal < 0.0)
				{
				f_RangeVal = f_RangeVal * -1;
				}

			float f_FloatA = f_RangeVal - (f_WeightRangetoStart / 2);

			float f_FloatB = f_FloatA + f_StartRange;

			int f_IntegerConv = (int)(f_FloatB);

			return (float)f_IntegerConv;
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1.0f;
}

//element level specify schema
bool classTarget_Ecom::ac_takeMeasurementBLTV1(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	std::shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[ag_Pull_gen_Element(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0)];

	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;
	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Element->vec_Vertex[f_HighestInt].m_X, f_Element->vec_Vertex[f_HighestInt].m_Y, f_Element->vec_Vertex[f_HighestInt].m_Z);

			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();

			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * 0.77f;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * 0.77f;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * 0.77f;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;
				
			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);
			if(f_Theta > 0.0f)
				{
				return true;
				}
			else
				{
				return false;
				}
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1.0f;
}

bool classLMap::ac_takeMeasurementBLTV1(shared_ptr<classElement> f_Vertex, int f_Depth, int f_Cap, int f_OCSCP_ThreadIndex)  // scale resolution 1-3
{
	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;
	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt].m_X, f_Vertex->vec_Vertex[f_HighestInt].m_Y, f_Vertex->vec_Vertex[f_HighestInt].m_Z);

			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();

			f_Vec->m_X = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_X * f_MeshVertex.m_X) * 0.77f;
			f_Vec->m_Y = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y * f_MeshVertex.m_Y) * 0.77f;
			f_Vec->m_Z = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z * f_MeshVertex.m_Z) * 0.77f;

			m_SchemaRef[f_OCSCP_ThreadIndex]->m_X = f_Vec->m_X;
			m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y = f_Vec->m_Y;
			m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z = f_Vec->m_Z;
				
			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);
			if(f_Theta > 0.0f)
				{
				return true;
				}
			else
				{
				return false;
				}
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1.0f;
}

std::string ag_NameStamp(std::string f_Measurement, int f_Type, int f_BitCount)
{
	std::string f_Result;
	f_Result.clear();

	g_FunctionStamp++;

	if(f_Type == COMPONENT_TYPE_VARINSTA)
		{
		std::string f_Char;
		f_Char.clear();
		//f_Char = "Variable" + g_FunctionStamp + "-" + f_BitCount;
		f_Result += f_Char;
		}
	if(f_Type == COMPONENT_TYPE_FUNCTIONCALL)
		{
		std::string f_Char;
		f_Char.clear();
		//f_Char = "FunctionCall" + g_FunctionStamp + "-" + f_BitCount;
		f_Result += f_Char;
		}

	return f_Result;
}

};