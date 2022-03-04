/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Collection.h"

using namespace ecoin;

namespace ecoin
{

	void classCollection::acEncryptHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<CubeHESH> f_PreviousHesh)
		{
		for(int f_Count = 0; f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
			{
			shared_ptr<CubeBicycle> f_CubeBicycleHesh = f_Hesh->vec_Bicycle[f_Count];
			shared_ptr<CubeBicycle> f_CubeBicyclePrevious = f_PreviousHesh->vec_Bicycle[f_Count];

			acEncryptBicycle(f_CubeBicycleHesh, f_CubeBicyclePrevious);
			}
		}

	void classCollection::acEncryptBicycle(shared_ptr<CubeBicycle> f_Bicycle, shared_ptr<CubeBicycle> f_BicyclePrev)
		{
		shared_ptr<classCorner> f_Corner;

		std::shared_ptr<Cube::BiVector> f_Vertex1 = f_Bicycle->vec_Vertex[0];
		std::shared_ptr<Cube::BiVector> f_Vertex2 = f_Bicycle->vec_Vertex[1];
		std::shared_ptr<Cube::BiVector> f_Vertex3 = f_Bicycle->vec_Vertex[2];
		std::shared_ptr<Cube::BiVector> f_Vertex4 = f_Bicycle->vec_Vertex[3];
		std::shared_ptr<Cube::BiVector> f_Vertex5 = f_Bicycle->vec_Vertex[4];
		std::shared_ptr<Cube::BiVector> f_Vertex6 = f_Bicycle->vec_Vertex[5];
		std::shared_ptr<Cube::BiVector> f_Vertex7 = f_Bicycle->vec_Vertex[6];
		std::shared_ptr<Cube::BiVector> f_Vertex8 = f_Bicycle->vec_Vertex[7];
		}
};