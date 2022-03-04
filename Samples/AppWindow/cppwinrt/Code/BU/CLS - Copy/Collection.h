/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>
#include <math.h>

#include "Corner.h"
#include "Surface.h"
#include "Leg.h"

using namespace Cube;

namespace ecoin
{

	enum CollectionStyle
	{
		Ground,
		Sky,
		CollectionStyleTotal
	};

	class classCollection
	{
	public:
		classCollection(std::shared_ptr<Cube::CubeHESH> f_Hesh) : m_Type(Ground), m_Status(ELEM_Status_Birth)
			{
			m_vec_Element.clear();
			m_idx_vec_Element = 0;
			acDecryptHesh(f_Hesh);
			};
		classCollection(uint f_Type) : m_Type(f_Type), m_Status(ELEM_Status_Birth)
			{
			m_vec_Element.clear();
			m_idx_vec_Element = 0;
			};
		classCollection() : m_Type(Ground), m_Status(ELEM_Status_Birth)
			{
			m_vec_Element.clear();
			m_idx_vec_Element = 0;
			};
		~classCollection()
			{
#if 0
#if 0
			for(int f_Jet = 0; f_Jet < m_vec_Element.size(); f_Jet++)
				{
				delete m_vec_Element[f_Jet];
				}
#endif

			m_vec_Element.clear();

#if 0
			for(int f_Jet = 0; f_Jet < m_vec_Surface.size(); f_Jet++)
				{
				delete m_vec_Surface[f_Jet];
				}
#endif

			m_vec_Surface.clear();

#if 0
			for(int f_Jet = 0; f_Jet < m_vec_Leg.size(); f_Jet++)
				{
				delete m_vec_Leg[f_Jet];
				}
#endif

			m_vec_Leg.clear();
#endif

			acClear();
			};

		void acClear(void)
			{
			m_vec_Element.clear();
			m_vec_Surface.clear();
			m_vec_Leg.clear();
			m_idx_vec_Element = 0;
			}

		void acEncryptBicycle(std::shared_ptr<CubeBicycle> f_Bicycle, std::shared_ptr<CubeBicycle> f_BicyclePrev);

		void acEncryptHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<CubeHESH> f_PreviousHesh);
		void acDecryptHesh(std::shared_ptr<Cube::CubeHESH> f_Hesh);

		uint m_Type;
		uint m_Status;

		float m_Scale;

		vector<shared_ptr<classElement>> m_vec_Element;
		vector<shared_ptr<classSurface>> m_vec_Surface;
		vector<shared_ptr<classLeg>> m_vec_Leg;

		int m_idx_vec_Element;
	};

	class classCollectionScript
	{
	public:
		classCollectionScript(uint f_Type) : m_Type(f_Type), m_Status(ELEM_Status_Birth)
			{
			m_vec_ElementScript.clear();
			};
		classCollectionScript() : m_Type(Ground), m_Status(ELEM_Status_Birth)
			{
			m_vec_ElementScript.clear();
			};
		~classCollectionScript() {};

		void acClear(void)
			{
			m_vec_ElementScript.clear();
			}

		classWorth* acStructuredAnalysis(/*target*/);

		uint m_Type;
		uint m_Status;

		float m_Scale;

		vector<shared_ptr<classElementScript> > m_vec_ElementScript;
	};

};

#include "Target.h"

#endif