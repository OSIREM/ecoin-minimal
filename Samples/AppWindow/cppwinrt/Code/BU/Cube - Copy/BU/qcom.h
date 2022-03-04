/*

qcom.h - ECOM Native Decl osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QCOM_H
#define QCOM_H

#include "Include/Cube.h"

#include <vector>
#include <map>

using namespace std;
using namespace Cube;
using namespace ecoin;

namespace Cube
{

extern float g_BossLVLMin;

extern int g_QcomMax;

extern void ag_LoadQcom(void);

class Qcom_genScript
{
public:
	Qcom_genScript() {};
	~Qcom_genScript() {};

	Qcom_genScript(int f_ID, bool f_loadall = false);
	Qcom_genScript(std::string f_Script);

	int m_ID;
	int m_ComID;
	int m_birthcomid;

	bool m_Save;

	//unused
	int m_typed;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	int m_rseed;
	std::string m_seedinfo;

	std::string m_TargetString;

	//Active code mapping
	std::vector<std::string> m_vec_InitLine;
	std::vector<int> m_vec_InitLineOrder;
	std::vector<int> m_vec_InitLineOrderID;
	std::vector<std::string> m_vec_InitLineOrdered;
	std::vector<int> m_vec_InitLineOrderedID;

	int m_QamLevel;
	int m_QamID;
};

class Qcom_eslfunction
{
public:
	Qcom_eslfunction() {};
	~Qcom_eslfunction() {};

	Qcom_eslfunction(int f_ID, bool f_loadall = false);

	// Initialize
	void Initialize(void);
	void Unload(void);

	void GenerateBuffers(void);

	static const int VOXEL_GRID_SIZE = 12;

	int m_ID;
	int m_ComID;
	int m_birthcomid;

	bool m_Save;

	//unused
	int m_typed;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	int m_rseed;
	std::string m_seedinfo;

	std::string m_TargetString;

	//Active code mapping
	std::vector<CodeLine*> m_vec_CodeLine;
	std::vector<std::string*> m_vec_InitLine;
	std::vector<int> m_vec_InitLineOrder;
	std::vector<int> m_vec_InitLineOrderID;
	std::vector<std::string*> m_vec_InitLineOrdered;
	std::vector<int> m_vec_InitLineOrderedID;

	int m_QamLevel;
	int m_QamID;
};

class QcomInput
{
public:
	QcomInput() {};
	~QcomInput() {};

	QcomInput(int f_ID, bool f_loadall = false);

	// Initialize
	void Initialize(void);
	void Unload(void);

	void GenerateBuffers(void);

	void ac_Save(void);

	static const int VOXEL_GRID_SIZE = 12;

	BiVector m_position;

	/////////////
   // GL
  //
 ///
	//GLuint mVertexPositionBuffer;
	//GLuint mVertexNormalBuffer;
	//GLuint mVertexColorBuffer;
	//GLuint mVertexTexCoordBuffer;

	// Indices
	//GLuint mIndexBuffer;

	std::vector<BiVector> m_vec_Vertex;
	std::vector<BiVector> m_vec_Normal;
	std::vector<BiColor> m_vec_Color;
	std::vector<BiTex> m_vec_Tex;
	std::vector<Index> m_vec_Index;

	bool m_rebuild;

	int m_ID;
	int m_ComID;
	int m_ICOID;
	int m_birthcomid;

	float m_parentx;
	float m_parenty;

	bool m_Save;

	//unused
	int m_typed;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	//Full Active function pointer mapping
	int m_InputfunctionID;
	int m_InputfunctionIndex;
	std::shared_ptr<Qcom_eslfunction> m_InputFunction;

	int m_QamLevel;
	int m_QamID;
};

class QcomControl
{
public:
	QcomControl() {};
	~QcomControl() {};

	QcomControl(int f_ID, bool f_loadall = false);

	// Initialize
	void Initialize(void);
	void Unload(void);

	void GenerateBuffers(void);

	void ac_Save(void);

	static const int VOXEL_GRID_SIZE = 12;

	BiVector m_position;

	/////////////
   // GL
  //
 ///
	//GLuint mVertexPositionBuffer;
	//GLuint mVertexNormalBuffer;
	//GLuint mVertexColorBuffer;
	//GLuint mVertexTexCoordBuffer;

	// Indices
	//GLuint mIndexBuffer;

	std::vector<std::shared_ptr<BiVector>> m_vec_Vertex;
	std::vector<std::shared_ptr<BiVector>> m_vec_Normal;
	std::vector<BiColor*> m_vec_Color;
	std::vector<BiTex*> m_vec_Tex;
	std::vector<Index*> m_vec_Index;

	bool m_rebuild;

	int m_ID;
	int m_ComID;
	int m_ICOID;
	int m_birthcomid;

	float m_parentx;
	float m_parenty;

	bool m_Save;

	//unused
	int m_typed;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	//Full Active function pointer mapping
	int m_InputfunctionID;
	int m_InputfunctionIndex;
	std::shared_ptr<Qcom_eslfunction> m_ControlFunction;

	int m_QamLevel;
	int m_QamID;
};

class QcomOutput
{
public:
	QcomOutput() {};
	~QcomOutput() {};

	QcomOutput(int f_ID, bool f_loadall = false);

	// Initialize
	void Initialize(void);
	void Unload(void);

	void GenerateBuffers(void);

	void ac_Save(void);

	static const int VOXEL_GRID_SIZE = 12;

	BiVector m_position;

	/////////////
   // GL
  //
 ///
	//GLuint mVertexPositionBuffer;
	//GLuint mVertexNormalBuffer;
	//GLuint mVertexColorBuffer;
	//GLuint mVertexTexCoordBuffer;

	// Indices
	// mIndexBuffer;

	std::vector<std::shared_ptr<BiVector>> m_vec_Vertex;
	std::vector<std::shared_ptr<BiVector>> m_vec_Normal;
	std::vector<BiColor*> m_vec_Color;
	std::vector<BiTex*> m_vec_Tex;
	std::vector<Index*> m_vec_Index;

	bool m_rebuild;

	int m_ID;
	int m_ComID;
	int m_ICOID;
	int m_birthcomid;

	float m_parentx;
	float m_parenty;

	bool m_Save;

	//unused
	int m_typed;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	//Full Active function pointer mapping
	int m_InputfunctionID;
	int m_InputfunctionIndex;
	std::shared_ptr<Qcom_eslfunction> m_InputFunction;

	int m_QamLevel;
	int m_QamID;
};

class Qcom
{
public:
	Qcom();
	~Qcom();

	Qcom(int f_ID, bool f_loadall = false);

	// Initialize
	void Initialize(void);
	void Unload(void);

	void GenerateBuffers(void);
	void ac_Save(void);
	void ac_Execute(void);

	BiVector m_position;

	/////////////
   // GL
  //
 ///
	//GLuint mVertexPositionBuffer;
	//GLuint mVertexNormalBuffer;
	//GLuint mVertexColorBuffer;
	//GLuint mVertexTexCoordBuffer;

	// Indices
	//GLuint mIndexBuffer;

	std::vector<BiVector> m_vec_Vertex;
	std::vector<BiVector> m_vec_Normal;
	std::vector<BiColor> m_vec_Color;
	std::vector<BiTex> m_vec_Tex;
	std::vector<Index> m_vec_Index;

	bool m_rebuild;

	int m_ID;
	int m_parentcomid;
	int m_birthcomid;

	std::vector<std::shared_ptr<Qcom> > m_vec_Qcom;
	std::vector<std::shared_ptr<Qcom> > m_vec_Execute_Chain;

	int m_Execute_Priority;

	float m_parentx;
	float m_parenty;

	bool m_Save;

	//unused
	int m_typed;

	int m_rseed;
	std::string m_seedinfo;

	std::string m_owner;
	std::string m_name;
	std::string m_overload;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	std::vector<std::shared_ptr<QcomInput> > m_vec_Input;
	std::vector<std::shared_ptr<QcomOutput> > m_vec_Output;

	int m_VoteScore;

	std::shared_ptr<Qcom_genScript> m_genScript;
	std::vector<std::shared_ptr<Qcom_eslfunction> > m_vec_Function;

	int m_QamLevel;
	int m_QamID;

	//add
	float m_Cost;
	float m_BossLVLMin;
};

class QcomWire
{
public:
	QcomWire() {};
	~QcomWire() {};

	QcomWire(int f_ID, bool f_loadall = false);

	void ac_Save(void);

	int m_ID;
	int m_parentcom_ID;
	int m_birthcomid;

	bool m_Save;

	//unused
	int m_typed;

	std::string m_NameGroup;

	int m_OutputID;
	std::shared_ptr<Qcom> m_Output;

	int m_InputID;
	std::shared_ptr<Qcom> m_Input;

	int m_QamLevel;
	int m_QamID;
};

class QcomManager
{
public:
	/* Public methods */
	QcomManager();
	~QcomManager();

	bool UpdateQcom(void);

	void acResetList(void);

	void GenerateBuffers(void);
	void GenerateBuffersGrid(void);

	//user controls
	void ac_FireLTClick(void);
	void ac_FireRTClick(void);
	bool ac_DragGrid(float f_X, float f_Y);

	//first run only! dev
	void ac_com_base_v1(bool f_memOnly = false);

	void ac_LoadAll(int f_QamID, int f_QamLevel = -5);

	void ac_PlushScripts(int f_QamID, bool f_LoadAll = false, int f_QamLevel = -5);

	void ac_Wire(int f_QamID, int f_QamLevel = -5);

	//from share build com
	bool ac_comFromHesh(float f_lensingSchemaX, float f_lensingSchemaY, float f_lensingSchemaZ);

	unMutexCC m_Qcom_Muti;

	bool m_rebuild;

	int mDrawCount;

	int m_QcomCount;

	std::vector<std::shared_ptr<Qcom>> m_vec_Qcom;
	std::vector<QcomInput*> m_vec_Input;
	std::vector<QcomOutput*> m_vec_Output;
	std::vector<std::shared_ptr<Qcom_genScript>> m_vec_GenScript;
	std::vector<std::shared_ptr<Qcom_eslfunction>> m_vec_ESLFunction;
	std::vector<QcomWire*> m_vec_ComWire;

	std::shared_ptr<Qcom_genScript> m_vec_defGenScript;
	std::shared_ptr<Qcom_eslfunction> m_vec_defESLFunction;
	
	int m_QcomNom;

	//Display
	bool m_Open;
	float m_current_X;
	float m_current_Y;
	float m_current_X_jeb;
	float m_current_Y_jeb;
	float m_current_Zoom;

	bool m_PointerCharge;

	bool m_drag_on;
	float m_drag_X;
	float m_drag_Y;

private:
	    /////////////
	   // GL
	  //
	 ///
	///
	/*GLuint mProgram;
	GLuint mProgramM;
	GLuint mProgramGrid;

	GLsizei mWindowWidth;
	GLsizei mWindowHeight;

	GLint mModelUniformLocation;
	GLint mViewUniformLocation;
	GLint mProjUniformLocation;

	GLint mCameraTranslationUniformLocation;

	GLint mModelUniformLocationM;
	GLint mViewUniformLocationM;
	GLint mProjUniformLocationM;

	GLint mModelUniformLocationGrid;
	GLint mViewUniformLocationGrid;
	GLint mProjUniformLocationGrid;

	GLint mPosUniformLocation;
	GLint mPosUniformLocationGrid;
	GLint mColorUniformLocationGrid;

	GLint mPositionAttribLocation;
	GLint mNormalAttribLocation;
	GLint mColorAttribLocation;
	GLint mTexCoordAttribLocation;

	GLint mPositionAttribLocationM;
	//GLint mNormalAttribLocationM;
	GLint mColorAttribLocationM;
	//GLint mTexCoordAttribLocationM;

	GLint mPositionAttribLocationGrid;
	//GLint mNormalAttribLocationM;
	GLint mColorAttribLocationGrid;
	//GLint mTexCoordAttribLocationM;

	GLint mLightPosUniformLocation;
	GLint mLightColorUniformLocation;
	GLint mLightNomUniformLocation;

	/////////////
   // GL
  //
 ///
	GLuint mVertexPositionBuffer;
	GLuint mVertexColorBuffer;
	// Indices
	GLuint mIndexBuffer;

	//Grid
	GLuint mVertexPositionBufferGrid;
	GLuint mVertexColorBufferGrid;
	// Indices
	GLuint mIndexBufferGrid;*/

	int mWindowWidth;
	int mWindowHeight;
};

extern QcomManager* g_QcomManager;

extern std::shared_ptr<Qcom> g_PreCom;
extern bool g_PreComBool;
extern bool g_PreComLock;
extern int g_PreComBoughtIN;
extern bool g_PreComInclude;

extern std::shared_ptr<Qcom_genScript> gqcom_INLfromComID(int f_ComID);
extern std::shared_ptr<Qcom_genScript> gqcom_INLfromString(std::string f_String);

};

#endif