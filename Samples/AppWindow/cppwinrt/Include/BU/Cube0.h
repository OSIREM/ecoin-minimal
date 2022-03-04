/*

Cube.h - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#pragma once

#include "../Common/DeviceResources.h"
#include "../Content/ShaderStructures.h"

#include <vector>

namespace ecoin
{
	class Contract;
}

namespace Cube
{

#define CUBE_TRI_SHOT_A 0
#define CUBE_TRI_SHOT_B 1
#define CUBE_TRI_SHOT_C 2
#define CUBE_TRI_SHOT_TOTAL 100

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

	extern int randomFac(void);
	extern float random(void);
	extern int g_Fingat;
	extern float g_swit;

	class CubeBicycle;
	class float3;
	class float4;
	class aabb;
	class BiVector;
	class Contract;

	typedef struct Carriage
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
			BiVector* acCenter(void);

			aabb* m_aabb;
			bool m_Served;

			CubeBicycle* m_Link;

			int nom_Child;
			int nom_Parent;

			int acFindinLog(int f_Msg);
			std::vector<unsigned int> vec_Log;

			std::vector<CubeKEY*> vec_Child;
			std::vector<CubeKEY*> vec_Parent;
		};

	class CubeHESH
		{
		public:
			CubeHESH() {};
			CubeHESH(FILE* f_File);
			CubeHESH(std::string f_Buffer);

			int m_ID;
			ULONGLONG m_Timestamp;

			float m_RotateX;
			float m_RotateY;
			float m_RotateZ;

			std::vector<int> m_adIndex;

			std::vector<CubeBicycle*> vec_Bicycle;

			void acSerialise(std::string* f_String);

			float m_ValueBank;
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
				while(mFired) { /*wait*/ }
				mFired = true;
				}

			void ac_Free(void)
				{
				mFired = false;
				}
		};

	class Index
		{
		public:
			Index()
				{ m_A = 0; m_B = 0;	m_C = 0; }

			public:
				int m_A;
				int m_B;
				int m_C;
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

			void acPushRandSphere(float f_Radius, float f_Seed)
				{
				f_Radius *= 1.5;

				for (int f_Cntr = 0; f_Cntr < 7; f_Cntr++)
					{
					BiRand f_BiRand(f_Seed);
					BiVector f_Vector((f_BiRand.acGet() - 0.5) * f_Radius, (f_BiRand.acGet() - 0.5) * f_Radius, (f_BiRand.acGet() - 0.5) * f_Radius);
				
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

			void acPrepare(void)
				{
				BiVector f_Result(m_Z * -1, m_Y, m_X);
				m_X = f_Result.m_X;
				m_Y = f_Result.m_Y;
				m_Z = f_Result.m_Z;
				}

			void acStore(void)
				{
				vec_Path_X.push_back(m_X);
				vec_Path_Y.push_back(m_Y);
				vec_Path_Z.push_back(m_Z);
				}

		public:
			float m_X;
			float m_Y;
			float m_Z;

			std::vector<float> vec_Path_X;
			std::vector<float> vec_Path_Y;
			std::vector<float> vec_Path_Z;
		};

	class aabb
		{
		public:
			BiVector _min;
			BiVector _max;

			aabb();
			aabb(const BiVector &);

			bool collide(const aabb& b) const;
			bool collide(aabb* b);
			bool inside(const BiVector &) const;

			aabb &operator += (const aabb &);
			aabb &operator += (const BiVector &p);

			float width()  const { return _max.m_X - _min.m_X; }
			float height() const { return _max.m_Y - _min.m_Y; }
			float depth()  const { return _max.m_Z - _min.m_Z; }

			BiVector center();
			BiVector centered();
			void empty();

#ifdef CUBE_AABB_USE_COLOR
			BiVector _color;
			void visualization();
#endif
		};

	class CubeBicycle
		{
		public:
			CubeBicycle() { vec_Vertex.clear(); vec_Indices.clear(); m_indexCount = 0; };
			CubeBicycle(FILE* f_File);
			CubeBicycle(std::string f_Buffer);

#if 0
			void acRefresh(void);
#endif

			void avGrow(float f_Amount);
			void avTranslate(Cube::BiVector f_Vector);
			void avPushBack(int f_Step);

			void acSerialise(std::string* f_String);

			int m_indexCount;

			std::vector<Cube::BiVector> vec_Vertex;
			std::vector<Cube::BiVector> vec_Color;
			std::vector<Cube::Index> vec_Indices;

			Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
		};

	class BicycleContainer
		{
		public:
			void avStage(void);

			std::vector<CubeKEY*> vec_Key;
			int nom_Bicycle;
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

	/////////////////////////
	/// START Cubetronics ///
	/////////////////////////

	class float3
		{
		public:
			float3() { x = 0; y = 0; z = 0; r = 0; g = 0; b = 0; }
			float3(float f_V) { x = f_V; y = f_V; z = f_V; r = f_V; g = f_V; b = f_V; }
			float3(float f_X, float f_Y, float f_Z) { x = f_X; y = f_Y; z = f_Z; }
			float3(int f_Type)
				{
				x = random() - 0.5;
				y = random() - 0.5;
				z = random() - 0.5;
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
			CubeHeshExporter() { m_vec_Result.clear(); BiCount = 0; BiVectorCount = 0; }

			void acPrepare(void) { m_vec_Result.clear(); BiCount = 0; BiVectorCount = 0; }

			int BiCount;
			int BiVectorCount;
			std::vector<PixelShaderInput> m_vec_Result;
		};

	extern float frac(float f_Float);
	extern float dot(float3 f_A, float3 f_B);
	extern PixelShaderInput visualminer(VertexShaderInput input);

	extern void agSet_offsetvec(float3 f_Vector);

	extern BicycleContainer g_BicycleContainer[1];
	extern std::vector<CubeHESH*> g_HESH;

	extern void ag_AttachCube(CubeKEY* f_Target, CubeKEY* f_Subject, float f_Margin);

	extern CubeKEY* ChooseKEY(int f_Count = 1);

	extern CubeHESH* agSaveHesh(void);
	extern void agSave(CubeHESH* f_HESH);
	extern void agSave(void);

	extern bool agOpen(void);

	extern matrix g_model;
	extern matrix g_view;
	extern matrix g_projection;

	extern float3 g_RandomSeed;
	extern float3 g_offsetVec;

	extern float g_Float;

	extern BiVector g_eye;
	extern BiVector g_at;

	extern unMutexCC g_Applog_Muti;

	extern int g_BiStyleID;

	extern BiStyle* g_BiStyle;
	extern std::vector<BiStyle*> g_vec_BiStyles;
};