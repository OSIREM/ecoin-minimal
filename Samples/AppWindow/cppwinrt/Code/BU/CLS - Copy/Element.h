/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <math.h>

#include "Color.h"

#include "Include\Cube.h"

#include "../Musion/Code.h"

#define COMPONENT_CNT_BASE 2
#define VARIABLE_STATE_NORMAL 1
#define VARIABLE_STATE_POINTER 2
#define ELEMENT_SCRIPT_LANGUAGE_C 1
#define ELEMENT_SCRIPT_LANGUAGE_ESL 2
#define COMPONENT_TYPE_VARINSTA 1
#define COMPONENT_TYPE_FUNCTIONCALL 2
#define VARIABLE_TYPE_INT 1
#define COMPONENT_ELEMENT_TYPE_VARIABLE 1
#define COMPONENT_ELEMENT_TYPE_FUNCTION 2
#define COMPONENT_ELEMENT_TYPE_PROG 3
#define PROG_TYPE_OPERATOR 1
#define PROG_TYPE_BKT 2
#define PROG_TYPE_PAREN 3
#define OPERATOR_TYPE_PLUS 1

using namespace Cube;
using namespace std;

namespace ecoin
{

	enum
	{
		ELEM_Element
	};

	enum
	{
		ELEM_Status_Birth,
		ELEM_Status_Processing,
		ELEM_Status_Accepted,
		ELEM_Status_Total
	};

	class classElement;

	class classWorth
	{
	public:
		classWorth()
		{
		};
		classWorth(shared_ptr<classElement> f_Element)
		{
		};
		~classWorth() {};

		float m_USD;
		float m_BTC;
		float m_GBP;
	};

	class classCorner;
	class classSurface;
	class classLeg;

	class classJoint
	{
	public:
		classJoint()
			{
			m_Aggressor = nullptr;
			m_Saint = nullptr;
			};
		classJoint(shared_ptr<classElement> f_A, shared_ptr<classElement> f_S)
			{
			m_Aggressor = f_A;
			m_Saint = f_S;
			};
		~classJoint() {};

		shared_ptr<classElement> m_Aggressor;
		shared_ptr<classElement> m_Saint;
	};
	
	class classResult
	{
	public:
		classResult()
			{
			m_vec_Corner.clear();
			};
		~classResult()
			{
			m_vec_Corner.clear();
			};

		vector<classCorner> m_vec_Corner;

		float m_Dist01;
		float m_Dist23;
		float m_Dist45;
		float m_Dist67;

		float m_Dist02;
		float m_Dist13;
		float m_Dist46;
		float m_Dist57;

		float m_Dist04;
		float m_Dist15;
		float m_Dist26;
		float m_Dist37;

		float m_Dist01234567;
		float m_Dist02134657;
		float m_Dist04152637;

		int m_LevelParent;
		shared_ptr<classElement> m_Parent;

		float m_SurfToLegRatio;
		float m_SurfToLegRatioX;
		float m_SurfToLegRatioY;
		float m_SurfToLegRatioZ;

		BiPlane m_ProportionalPlane;
	};

	class classElement
	{
	public:
		classElement(shared_ptr<classElement> f_Element) : m_Type(f_Element->m_Type), m_Status(f_Element->m_Status)
			{
			m_R = f_Element->m_R;
			m_G = f_Element->m_G;
			m_B = f_Element->m_B;

			//m_Orten = f_Element->m_Orten;
			m_OCSCP_Flag = true;
			}
		classElement(shared_ptr<CubeBicycle> f_Bicycle) : m_Type(ELEM_Element), m_Status(ELEM_Element)
			{
			vec_Vertex.reserve(8);
			vec_Color.reserve(8);

			acGen_fromBicycle(f_Bicycle);

			//m_Orten = f_Element->m_Orten;
			m_OCSCP_Flag = true;
			}
		classElement(uint f_Type) : m_Type(f_Type), m_Status(ELEM_Status_Birth)
			{
			acColorise(0.5f, 0.5f, 0.5f, 1.0f);
			m_OCSCP_Flag = true;
			}
		classElement(uint f_Type, uint f_Status) : m_Type(f_Type), m_Status(f_Status)
			{
			acColorise(0.5f, 0.5f, 0.5f, 1.0f);
			m_OCSCP_Flag = true;
			}
		classElement(uint f_Type, uint f_Status, classColor f_Color) : m_Type(f_Type), m_Status(f_Status)
			{
			acColorise(f_Color.m_R, f_Color.m_G, f_Color.m_B, f_Color.m_A);
			m_OCSCP_Flag = true;
			}
		classElement(uint f_Type, uint f_Status, classColor* f_Color) : m_Type(f_Type), m_Status(f_Status)
			{
			acColorise(f_Color->m_R, f_Color->m_G, f_Color->m_B, f_Color->m_A);
			m_OCSCP_Flag = true;
			}
		classElement(float f_Volume) : m_Type(0), m_Status(0)
			{
			m_Volume = f_Volume;
			m_OCSCP_Flag = true;
			}
		classElement() : m_Type(0), m_Status(0)
			{
			m_OCSCP_Flag = true;
			}

		virtual ~classElement()
			{
#if 0
			for(int f_Jet = 0; f_Jet < m_vec_Result.size(); f_Jet++)
				{
				for(int f_Helly = 0; f_Helly < m_vec_Result[f_Jet]->m_vec_Corner.size(); f_Helly++)
					{
					if(m_vec_Result.operator[f_Jet]->m_vec_Corner[f_Helly] != NULL)
						{
						//delete m_vec_Result[f_Jet]->m_vec_Corner[f_Helly];
						//m_vec_Result[f_Jet]->m_vec_Corner[f_Helly] = NULL;
						}
					}

				m_vec_Result[f_Jet]->m_vec_Corner.clear();
				}

			for(int f_Jet = 0; f_Jet < m_vec_Surface.size(); f_Jet++)
				{
				//delete m_vec_Surface[f_Jet];
				//m_vec_Surface[f_Jet] = NULL;
				}

			for(int f_Jet = 0; f_Jet < m_vec_Leg.size(); f_Jet++)
				{
				//delete m_vec_Leg[f_Jet];
				//m_vec_Leg[f_Jet] = NULL;
				}

			for(int f_Jet = 0; f_Jet < m_vec_Joint.size(); f_Jet++)
				{
				if(m_vec_Joint[f_Jet] != NULL)
					{
					//delete m_vec_Joint[f_Jet];
					//m_vec_Joint[f_Jet] = NULL;
					}
				}

			delete m_aabb;
			m_aabb = NULL;
#endif

			m_vec_Element.clear();
			m_vec_Surface.clear();
			m_vec_Leg.clear();

			vec_Vertex.clear();
			vec_Color.clear();

			m_vec_Collission.clear();
			m_vec_IsIn.clear();

			m_vec_Joint.clear();
			};

		void acStructuredAnalysis(void);

		void acColorise(float f_R, float f_G, float f_B, float f_A)
			{
			m_R = f_R;
			m_G = f_G;
			m_B = f_B;
			m_A = f_A;
			}

		void acColorise(classColor *f_Color)
			{
			m_R = f_Color->m_R;
			m_G = f_Color->m_G;
			m_B = f_Color->m_B;
			m_A = f_Color->m_A;
			}

		void acColorise(classColor f_Color)
			{
			m_R = f_Color.m_R;
			m_G = f_Color.m_G;
			m_B = f_Color.m_B;
			m_A = f_Color.m_A;
			}

		void acGen_fromBicycle(shared_ptr<CubeBicycle> f_Bicycle);

		uint m_Type;
		uint m_Status;

		float m_R;
		float m_G;
		float m_B;
		float m_A;

		BiVector m_Center;
		//BiOrientation m_Orten;
		classWorth m_Worth;

		vector<shared_ptr<classElement> > m_vec_Element;
		vector<shared_ptr<classSurface> > m_vec_Surface;
		vector<shared_ptr<classLeg> > m_vec_Leg;

		vector<Cube::BiVector> vec_Vertex;
		vector<Cube::BiVector> vec_Color;

		aabb* m_aabb;
		float m_Volume;

		vector<int> m_vec_Collission;
		vector<int> m_vec_IsIn;

		vector<classJoint> m_vec_Joint;

		float acCompare(shared_ptr<classElement> f_Element, float f_QualityRank, bool f_testVolumes);

		  ////////////////////////////////////
		 // LEGACY of Structured Analysis
		//
		classResult m_Result;
		int m_Base;
		int m_Index;

		bool m_OCSCP_Flag;
	};

	class classComponent
	{
	public:
		classComponent(std::shared_ptr<classComponent> f_Component) : m_Type(f_Component->m_Type), m_Status(f_Component->m_Status)
			{
			m_vec_String.clear();

			for(int f_Str = 0; f_Str < f_Component->m_vec_String.size(); f_Str++)
				{
				m_vec_String.push_back(f_Component->m_vec_String[f_Str]);
				}
			};
		classComponent(uint f_Type) : m_Type(f_Type), m_Status(ELEM_Status_Birth)
			{
			m_vec_String.clear();
			};
		classComponent(uint f_Type, uint f_Status) : m_Type(f_Type), m_Status(f_Status)
			{
			m_vec_String.clear();
			};
		classComponent(uint f_Type, uint f_Status, classColor f_Color) : m_Type(f_Type), m_Status(f_Status)
			{
			m_vec_String.clear();
			};
		classComponent() : m_Type(0), m_Status(0)
			{
			m_vec_String.clear();
			};
		virtual ~classComponent() {};

		uint m_Type;
		uint m_Status;
		classWorth m_Worth;

		std::string m_Name;
		std::string m_Hash;
		vector<std::string> m_vec_String;
		std::string m_String;

		vector<int> m_Level;

		vector<std::shared_ptr<CodeLine>> m_vec_Code;

		float acCompare(std::shared_ptr<classComponent> f_Element, float f_QualityRank, bool f_testVolumes);
	};

	class classElementScript
	{
	public:
		classElementScript(std::shared_ptr<classElementScript> f_ElementScript) : m_Type(f_ElementScript->m_Type), m_Status(f_ElementScript->m_Status)
			{
			m_vec_Component.clear();

			for(int f_Str = 0; f_Str < f_ElementScript->m_vec_Component.size(); f_Str++)
				{
				m_vec_Component.push_back(f_ElementScript->m_vec_Component[f_Str]);
				}

			//m_Orten = f_Element->m_Orten;
			};
		classElementScript(shared_ptr<classElement> f_Element) : m_Type(f_Element->m_Type), m_Status(f_Element->m_Status)
			{
			acGen_fromElement(f_Element);

			//m_Orten = f_Element->m_Orten;
			};
		classElementScript(uint f_Type) : m_Type(f_Type), m_Status(ELEM_Status_Birth)
			{
			m_vec_Component.clear();
			};
		classElementScript(uint f_Type, uint f_Status) : m_Type(f_Type), m_Status(f_Status)
			{
			m_vec_Component.clear();
			};
		classElementScript(float f_Volume) : m_Type(0), m_Status(0)
			{
			m_Volume = f_Volume;
			};
		classElementScript() : m_Type(0), m_Status(0)
			{
			};
		virtual ~classElementScript() {};

		shared_ptr<classResult> acStructuredAnalysis(void);

		void acGen_fromElement(shared_ptr<classElement> f_Element, int f_ScriptLanguageScheme = 1);

		uint m_Type;
		uint m_Status;

		BiVector m_Center;
		//BiOrientation m_Orten;
		classWorth m_Worth;

		vector<std::shared_ptr<classElementScript>> m_vec_ElementScript;

		vector<std::shared_ptr<classComponent>> m_vec_Component;
		std::string m_Data;
		std::string m_Hash;

		aabb* m_aabb;
		float m_Volume;

		vector<int> m_vec_Collission;
		vector<int> m_vec_IsIn;

		vector<std::shared_ptr<classJoint>> m_vec_Joint;

		float acCompare(shared_ptr<classElement> f_Element, float f_QualityRank, bool f_testVolumes);

		  ////////////////////////////////////
		 // LEGACY of Structured Analysis
		//
		vector<shared_ptr<classResult>> m_vec_Result;
		int m_Base;
		int m_Index;
	};

	class classTestSchema
	{
	public:
		classTestSchema(classTestSchema* f_Schema) : m_Type(f_Schema->m_Type), m_Status(f_Schema->m_Status)
			{
			};
		classTestSchema(uint f_Type) : m_Type(f_Type), m_Status(ELEM_Status_Birth)
			{
			};
		classTestSchema(uint f_Type, uint f_Status) : m_Type(f_Type), m_Status(f_Status)
			{
			};
		classTestSchema(float f_Volume) : m_Type(0), m_Status(0)
			{
			m_Volume = f_Volume;
			};
		classTestSchema() : m_Type(0), m_Status(0)
			{
			};
		virtual ~classTestSchema() {};

		uint m_Type;
		uint m_Status;

		BiVector m_Center;
		//BiOrientation m_Orten;
		classWorth m_Worth;

		std::string m_Data;
		std::string m_Hash;

		aabb* m_aabb;
		float m_Volume;

		vector<int> m_vec_Collission;
		vector<int> m_vec_IsIn;

		std::vector<BiVector> f_ReferencePoint;
	};

	extern std::string ag_takeMeasurement0(shared_ptr<classElement> f_Vertex);
	extern int ag_takeMeasurementINTV0(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart = 0, int f_Depth = 1);
	extern std::string ag_NameStamp0(std::string f_Measurement, int f_Type, int f_BitCount);
	extern std::string ag_GenerateValue0(std::string f_Measurement);
};

#endif