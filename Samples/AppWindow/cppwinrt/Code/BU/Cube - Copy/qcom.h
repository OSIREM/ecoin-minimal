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

#include "Code/Work/Schedular.h"

#include "qam.h"

#include <vector>
#include <map>
#include <boost/any.hpp>

using namespace std;
using namespace Cube;
using namespace ecoin;

namespace Cube
{
extern float g_BossLVLMin;

#define COM_PAK_TYPE_INSERT 0
#define COM_PAK_TYPE_COMPLETE 1
#define COM_PAK_TYPE_DELETE 2

#define COM_PAK_UNACTIVATED 0
#define COM_PAK_ACTIVATED 1

#define COM_PAKX_STAGE_TITLE 0
#define COM_PAKX_STAGE_EQUAL 1
#define COM_PAKX_STAGE_QUOTE 2
#define COM_PAKX_STAGE_OFF 3

extern int ag_Get_ClassType(std::string f_Packet);

enum
{
	ctVariable,
	ctCClass,
	ctEClass,
	ctQcom,
	ctQcomInput,
	ctQcomOutput,
	ctComFunctionX,
	ctShare,
	ctElement,
	ctMax
};

class ComFunctionButtonSlot
{
public:
	ComFunctionButtonSlot() {};
	~ComFunctionButtonSlot() {};

	std::string m_ButtonText;
	int m_Panel;
	int m_PanelStack;
	int m_Button;
};

class Qcom_genScript
{
public:
	Qcom_genScript() { m_ID = -1551; m_QamID = g_QamID; };
	Qcom_genScript(int f_ID, bool f_loadall = false);
	~Qcom_genScript() {};

	void ac_Clear(void);

	void ac_Save(void);

	int m_ID;
	int m_ComID;
	int m_birthcomid;
	bool m_Save;
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
	Qcom_eslfunction() { ac_Clear(); m_ID = -1551; m_QamID = g_QamID; };
	~Qcom_eslfunction() {};

	Qcom_eslfunction(int f_ID, bool f_loadall = false);

	void ac_Execute(void);
	void ac_Clear(void);
	void ac_Save(void);

	void acCompile(void);

	void acFrom_predTextPanel(std::string f_Buffer);

	int m_ID;
	int m_ComID;
	int m_birthcomid;
	bool m_Save;
	int m_typed;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	int m_rseed;
	std::string m_seedinfo;
	std::string m_TargetString;
	std::string m_FunctionLine;

	std::string m_StartLine;

	//Active code mapping
	std::vector<std::string> m_vec_InitLine;
	std::vector<int> m_vec_InitLineOrder;
	std::vector<int> m_vec_InitLineOrderID;
	std::vector<std::string> m_vec_InitLineOrdered;
	std::vector<int> m_vec_InitLineOrderedID;
	std::vector<int> m_vec_ResultIDXupdateLineNumber;

	//esl contract
	std::shared_ptr<ecoin::Contract> m_Contract;

	std::shared_ptr<Variable> m_Result_Var;
	std::shared_ptr<ClassVar> m_Result_ClassVar;

	int m_QamLevel;
	int m_QamID;
};

class QcomInput
{
public:
	QcomInput()
		{
		m_ID = -1551;
		m_HighLighted = false;
		m_Selected = false;
		m_QamID = g_QamID;
		m_InputFunction = std::make_shared<Cube::Qcom_eslfunction>();
		}
	QcomInput(int f_ID, bool f_loadall = false);
	~QcomInput() {};

	void ac_Save(void);
	void acSelect(bool f_Selection);
	void acHighLight(bool f_Selection);

	/////////////
   // GL
  //
 ///
 ///
#if 0
	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;

	// Indices
	GLuint mIndexBuffer;
#endif

	BiVector m_position;

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
	int m_typed;

	bool m_Selected;
	bool m_HighLighted;

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
	QcomControl()
		{
		acClear(); m_ID = -1551;
		m_QamID = g_QamID;
		m_ControlFunction = std::make_shared<Cube::Qcom_eslfunction>();
		};
	QcomControl(int f_ID, bool f_loadall = false);
	~QcomControl() { acClear(); };

	void acClear(void)
		{
		m_vec_Vertex.clear();
		m_vec_Normal.clear();
		m_vec_Color.clear();
		m_vec_Tex.clear();
		m_vec_Index.clear();
		}

	void ac_Save(void);

	/////////////
   // GL
  //
 ///
#if 0
	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;

	// Indices
	GLuint mIndexBuffer;
#endif

	BiVector m_position;

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
	int m_typed;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	//Full Active function pointer mapping
	int m_ControlfunctionID;
	int m_ControlfunctionIndex;
	std::shared_ptr<Qcom_eslfunction> m_ControlFunction;

	int m_QamLevel;
	int m_QamID;
};

class QcomOutput
{
public:
	QcomOutput()
		{
		m_ID = -1551;
		m_HighLighted = false;
		m_Selected = false;
		m_QamID = g_QamID;
		m_OutputFunction = std::make_shared<Cube::Qcom_eslfunction>();
		};
	~QcomOutput() {};

	QcomOutput(int f_ID, bool f_loadall = false);

	// Initialize
#if 0
	void Initialize(void);
	void Unload(void);
	void GenerateBuffers(void);
#endif

	void ac_Save(void);
	void acSelect(bool f_Selection);
	void acHighLight(bool f_Selection);

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
	int m_typed;

	bool m_Selected;
	bool m_HighLighted;

	std::string m_owner;
	std::string m_name;
	std::string m_description;
	std::string m_vision;

	std::string m_NameGroup;

	//Full Active function pointer mapping
	int m_OutputfunctionID;
	int m_OutputfunctionIndex;
	std::shared_ptr<Qcom_eslfunction> m_OutputFunction;

	int m_QamLevel;
	int m_QamID;
};

class QcomWire;

class Qcom
{
public:
	Qcom();
	Qcom(int f_ID, bool f_loadall = false);
	~Qcom();

	void ac_Clear(void);

	// Initialize
	void Initialize(void);
	void GenerateBuffers(void);
	void Unload(void);

	void ac_Save(void);
	void ac_Execute(void);

	void acSelect(bool f_Selection);
	void acHighLight(bool f_Selection);

	/////////////
   // GL
  //
 ///
 #if 0
	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;

	// Indices
	GLuint mIndexBuffer;
#endif

	BiVector m_position;

	std::vector<BiVector> m_vec_Vertex;
	std::vector<BiVector> m_vec_Normal;
	std::vector<BiColor> m_vec_Color;
	std::vector<BiTex> m_vec_Tex;
	std::vector<Index> m_vec_Index;

	bool m_rebuild;

	int m_ID;
	int m_parentcomid;
	int m_birthcomid;

	std::shared_ptr<Qcom> m_ParentCom;

	std::vector<std::shared_ptr<Qcom>> m_vec_Qcom;
	std::vector<std::shared_ptr<Qcom>> m_vec_Execute_Chain;

	std::vector<std::shared_ptr<QcomInput>> m_vec_Input;
	std::vector<std::shared_ptr<QcomOutput>> m_vec_Output;
	std::vector<std::shared_ptr<QcomWire>> m_vec_ComWire;

	std::vector<std::shared_ptr<Qcom_genScript>> m_vec_GenScript;
	std::vector<std::shared_ptr<Qcom_eslfunction>> m_vec_ESLFunction;

	std::shared_ptr<Qcom_eslfunction> m_Frame_ESLFunction;

	int m_Execute_Priority;

	float m_parentx;
	float m_parenty;

	bool m_Save;
	int m_typed;

	bool m_Selected;
	bool m_HighLighted;

	int m_rseed;
	std::string m_seedinfo;

	std::string m_owner;
	std::string m_name;
	std::string m_overload;
	std::string m_description;
	std::string m_vision;
	std::string m_NameGroup;

	int m_VoteScore;

	std::shared_ptr<Qcom_genScript> m_genScript;
	std::vector<std::shared_ptr<Qcom_eslfunction> > m_vec_Function;

	int m_QamLevel;
	int m_QamID;

	time_t m_Trial_Length;

	//add
	float m_Cost;
	float m_BossLVLMin;
};

class QcomWire
{
public:
	QcomWire() { m_Time = 0.0f; m_ID = -1551; m_HighLighted = false; m_Selected = false; };
	~QcomWire() {};

	QcomWire(int f_ID, bool f_loadall = false);

	void ac_Save(void);

	void acSelect(bool f_Selection);
	void acHighLight(bool f_Selection);

	int m_ID;
	int m_parentcomid;
	int m_birthcomid;

	std::shared_ptr<Qcom> m_ParentCom;

	bool m_Save;
	int m_typed;

	std::string m_NameGroup;

	std::shared_ptr<QcomOutput> m_Output;
	std::shared_ptr<Qcom> m_OutputCom;

	std::shared_ptr<QcomInput> m_Input;
	std::shared_ptr<Qcom> m_InputCom;

	int m_QamLevel;
	int m_QamID;

	float m_Xmin;
	float m_Ymin;
	float m_Xmax;
	float m_Ymax;

	float m_Length;
	float m_Height;

	int m_indexCount;

	float m_Time;

	bool m_Selected;
	bool m_HighLighted;

	std::vector<BiVector> m_vec_Vertice;
	std::vector<BiVector> m_vec_Color;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_curvevertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_curveindexBuffer;
};

class WireCom
{
public:
	WireCom() { m_Time = 0.0f; m_ID = -1551; m_NameGroup.clear(); };
	WireCom(float f_X, float f_Y) { m_Time = 0.0f; m_ID = -1551; m_X = f_X, m_Y = f_Y; m_NameGroup.clear(); };
	~WireCom() { m_NameGroup.clear(); };

	WireCom(int f_ID, bool f_loadall = false);
	void ac_Save(void);

	int m_ID;
	bool m_Save;
	int m_typed;

	std::string m_NameGroup;

	float m_X;
	float m_Y;

	std::shared_ptr<QcomWire> m_ComWire;

	std::shared_ptr<Qcom> m_ParentCom;

	int m_QamLevel;
	int m_QamID;

	float m_Time;
};

class BiPacket
{
public:
	BiPacket()
		{
		acClear();
		}
	~BiPacket()
		{
		acClear();
		}

	void acClear(void)
		{
		m_InsertElementType = -1;
		m_ClassType = -1;
		m_ShareID = -1;
		m_Element = -1;
		m_Name.clear();
		m_DefaultValue.clear();
		m_Activate_Status = COM_PAK_UNACTIVATED;
		m_Visible = true;
		}

	std::shared_ptr<Qcom> m_Operator_Com;

	std::string m_Name;
	std::string m_DefaultValue;
	std::string m_Comment;
	int m_InsertElementType;
	int m_ClassType;
	int m_ShareID;
	int m_Element;

	int m_Activate_Status;
	bool m_Visible;

	BiVector m_Pos2D;

	std::vector<std::shared_ptr<BiPacket>> m_vec_Packet;
	std::vector<std::shared_ptr<BiPacket>> m_vec_Packet_Delete;
};

class QcomManager
{
public:
	/* Public methods */
	QcomManager();
	~QcomManager();

	void acClear(void);
	void acClearGrid(void);
	void acClearGridNew(std::shared_ptr<Qcom> f_NewCom);

	bool UpdateQcom(void);

	void GenerateBuffers(void);
	void GenerateBuffersGrid(void);

	//user controls
	void ac_FireLTClick(void);
	void ac_FireRTClick(void);
	void ac_DragGrid(float f_X, float f_Y);

	//first run only! dev
	void ac_com_base_v1(bool f_memOnly = false);

	void ac_LoadAll(int f_QamID, int f_QamLevel = -5);
	void ac_LoadAll_Append(int f_QamID, int f_QamLevel = -5);

	void ac_PlushScripts(int f_QamID, int f_QamLevel = -5);

	void ac_Wire(int f_QamID, int f_QamLevel = -5);

	void acParse_GenScript(std::shared_ptr<Qcom> f_com);

	void acSelectNone(void);
	void acHighLightNone(void);

	std::shared_ptr<Qcom> ac_Find_Com_ByID(int f_ID);
	std::shared_ptr<QcomWire> ac_Find_ComWire_ByID(int f_ID);
	std::shared_ptr<QcomInput> ac_Find_ComInput_ByID(int f_ID);
	std::shared_ptr<QcomOutput> ac_Find_ComOutput_ByID(int f_ID);
	std::shared_ptr<WireCom> ac_Find_WireCom_ByID(int f_ID);
	std::shared_ptr<Qcom_eslfunction> ac_Find_Function_ByID(int f_ID);
	std::shared_ptr<Qcom_genScript> ac_Find_GenerationScript_ByID(int f_ID);

	void acPlace_FunctionCom(void);

	void acDisplayOn(void);

	unMutexCC m_Qcom_Muti;

	bool m_DisplayOn;
	bool m_rebuild;
	int mDrawCount;
	int m_QcomCount;

	std::vector<std::shared_ptr<Qcom>> m_SaveCom;

	std::vector<std::shared_ptr<BiPacket>> acSearch_PacketbyName(std::string f_Name);

	std::vector<std::shared_ptr<BiPacket>> m_vec_Packet;

	std::shared_ptr<Qcom> mam_Qcom;
	std::shared_ptr<Qcom> m_Qcom;

	std::vector<std::shared_ptr<Qcom>> m_vec_Qcom;

	std::vector<std::shared_ptr<QcomInput>> m_vec_Input;
	std::vector<std::shared_ptr<QcomOutput>> m_vec_Output;

	std::vector<std::shared_ptr<Qcom_genScript>> m_vec_GenScript;
	std::vector<std::shared_ptr<Qcom_eslfunction>> m_vec_ESLFunction;

	std::vector<std::shared_ptr<QcomWire>> m_vec_ComWire;
	std::vector<std::shared_ptr<WireCom>> m_vec_WireCom;

	std::shared_ptr<Qcom_genScript> m_vec_defGenScript;
	std::shared_ptr<Qcom_eslfunction> m_vec_defESLFunction;

	std::vector<std::shared_ptr<QcomOutput>> m_Wiring_Output;
	std::vector<std::shared_ptr<QcomInput>> m_Wiring_Input;

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

	int m_ecomSelectedCount;
	int m_inputSelectedCount;
	int m_outputSelectedCount;
	int m_wireSelectedCount;

private:
	int mWindowWidth;
	int mWindowHeight;

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
};

extern std::shared_ptr<QcomManager> g_QcomManager;

extern std::shared_ptr<Qcom> g_PreCom;
extern bool g_PreComBool;
extern bool g_PreComLock;
extern int g_PreComBoughtIN;
extern bool g_PreComInclude;

extern std::shared_ptr<Qcom_genScript> gqcom_INLfromComID(int f_ComID);
extern std::shared_ptr<Qcom_genScript> gqcom_INLfromString(std::string f_String);

class SelectionPreList
{
public:
	SelectionPreList() { acClear(); }
	~SelectionPreList() { acClear(); }

	void acClear(void)
		{
		m_vec_com.clear();
		m_vec_input.clear();
		m_vec_output.clear();
		m_vec_wire.clear();
		}

	void acPush(std::shared_ptr<Qcom> f_com)
		{
		m_vec_com.push_back(f_com);
		}

	void acPush(std::shared_ptr<QcomInput> f_com)
		{
		m_vec_input.push_back(f_com);
		}

	void acPush(std::shared_ptr<QcomOutput> f_com)
		{
		m_vec_output.push_back(f_com);
		}

	void acPush(std::shared_ptr<QcomWire> f_com)
		{
		m_vec_wire.push_back(f_com);
		}

	std::shared_ptr<Qcom> acSelectionList_ByBiDistance(void);
	int acSelectionList_ByBiDistanceChase(void);

	std::vector<std::shared_ptr<Qcom>> m_vec_com;
	std::vector<std::shared_ptr<QcomInput>> m_vec_input;
	std::vector<std::shared_ptr<QcomOutput>> m_vec_output;
	std::vector<std::shared_ptr<QcomWire>> m_vec_wire;

	BiVector m_position;
};

class BiDecisionA
	{
	public:
		BiDecisionA(std::string f_TitleText, std::string f_ObjectNameOverride, time_t f_Trial_Length = -1, int f_Trial_QamID = 0)
			{
			m_TitleText.clear();
			m_TitleText = f_TitleText;
			m_ObjectNameOverride.clear();
			m_ObjectNameOverride = f_ObjectNameOverride;
			m_Trial_Length = f_Trial_Length;
			m_Trial_QamID = f_Trial_QamID;
			m_Applied = false;
			};
		~BiDecisionA() { m_TitleText.clear(); m_ObjectNameOverride.clear(); m_Trial_QamID = 0; m_Trial_Length = -1; m_Applied = false; };

		bool acApply(void);
		bool acUnApply(void);

		time_t m_Trial_Length;
		int m_Trial_QamID;
		std::string m_TitleText;
		std::string m_ObjectNameOverride;
		bool m_Applied;
	};

class BiDecisionOverride
	{
	public:
		BiDecisionOverride() { m_Existence_ID = -1; m_Existence_ShareID = -1; m_PipeChan = 0; };
		BiDecisionOverride(int f_ComID, int f_PipeChan = 0, int f_ShareID = -1) { m_Existence_ID = f_ComID; m_PipeChan = f_PipeChan; m_Existence_ShareID = f_ShareID; };
		~BiDecisionOverride() {};

#pragma message("Once::Added-g_ShareManager->acPushShareID(acLoadShare(ID))-Proceed with Existance ShareID")

		bool acScan(void)
			{
#if 1
			switch(m_PipeChan)
				{
				case ECOIN_CLS_COM:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Qcom.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Qcom[f_XY]->m_birthcomid == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_INPUT:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Input.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Input[f_XY]->m_ID == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_OUTPUT:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Output.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Output[f_XY]->m_ID == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_WIRE:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_ComWire.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_ComWire[f_XY]->m_ID == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_COM_BIRTH:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Qcom.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Qcom[f_XY]->m_birthcomid == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_INPUT_BIRTH:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Input.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Input[f_XY]->m_birthcomid == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_OUTPUT_BIRTH:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Output.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_Output[f_XY]->m_birthcomid == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;

				case ECOIN_CLS_WIRE_BIRTH:
					{
					for(int f_XY = 0; f_XY < g_QcomManager->m_vec_ComWire.size(); f_XY++)
						{
						if(g_QcomManager->m_vec_ComWire[f_XY]->m_birthcomid == m_Existence_ID)
							{
							return true;
							}
						}

					return false;
					}break;
				}
#endif

			return false;
			}

		int m_PipeChan;
		int m_Existence_ID;
		int m_Existence_ShareID;
	};

class BiDecisionQ
	{
	public:
		BiDecisionQ(int f_PipeChan = 0, int f_ComID = -1, int f_ShareID = -1)
			{
			acClear();

			m_PipeChan = f_PipeChan;
			m_Existence_ID = f_ComID;
			m_Existence_ShareID = f_ShareID;

			acStoreCount();

			if(f_ComID >= 0)
				{
				m_vec_DecisionOverride.push_back(std::make_shared<BiDecisionOverride>(f_ComID, f_PipeChan, f_ShareID));
				}
			else if(f_ShareID >= 0)
				{
				m_vec_DecisionOverride.push_back(std::make_shared<BiDecisionOverride>(f_ComID, f_PipeChan, f_ShareID));
				}
			};
		~BiDecisionQ() { acClear(); };

		void acSelectOverrides(bool f_Clear = false);

		void acClear(void)
			{
			m_vec_DecisionOverride.clear();
			m_vec_DecisionA.clear();

			m_PipeChan = -1;
			m_Existence_ID = -1;
			m_Existence_ShareID = -1;
			m_ecomSelectedCount = -101;
			m_inputSelectedCount = -101;
			m_outputSelectedCount = -101;
			m_wireSelectedCount = -101;
			m_Visible = true;
			m_Trial_Length_Remain = -1;
			}

		void acAdd_Answer(std::shared_ptr<BiDecisionA> f_DecisionA)
			{
			m_vec_DecisionA.push_back(f_DecisionA);
			}

		bool acStoreCount(void)
			{
			m_ecomSelectedCount = -105;
			m_inputSelectedCount = -105;
			m_outputSelectedCount = -105;
			m_wireSelectedCount = -105;

			return true;
			};

		bool acCheck_Show(void)
			{
			if(m_ecomSelectedCount != -105)
				{
				if(m_ecomSelectedCount == -101)
					{
					if(g_QcomManager->m_vec_Qcom.size() >= 1)
						{
						return true;
						}
					}

				if(m_inputSelectedCount == -101)
					{
					if(g_QcomManager->m_vec_Input.size() >= 1)
						{
						return true;
						}
					}

				if(m_outputSelectedCount == -101)
					{
					if(g_QcomManager->m_vec_Output.size() >= 1)
						{
						return true;
						}
					}

				if(m_wireSelectedCount == -101)
					{
					if(g_QcomManager->m_vec_ComWire.size() >= 1)
						{
						return true;
						}
					}

				if(m_ecomSelectedCount == -100)
					{
					if(g_QcomManager->m_vec_Qcom.size() == 0)
						{
						return true;
						}
		
					}

				if(m_inputSelectedCount == -100)
					{
					if(g_QcomManager->m_vec_Input.size() == 0)
						{
						return true;
						}
					}

				if(m_outputSelectedCount == -100)
					{
					if(g_QcomManager->m_vec_Output.size() == 0)
						{
						return true;
						}
					}

				if(m_wireSelectedCount == -100)
					{
					if(g_QcomManager->m_vec_ComWire.size() == 0)
						{
						return true;
						}
					}

				if(g_QcomManager->m_ecomSelectedCount == m_ecomSelectedCount)
					{
					return true;
					}

				if(g_QcomManager->m_inputSelectedCount == m_inputSelectedCount)
					{
					return true;
					}

				if(g_QcomManager->m_outputSelectedCount == m_outputSelectedCount)
					{
					return true;
					}

				if(g_QcomManager->m_wireSelectedCount == m_wireSelectedCount)
					{
					return true;
					}
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_DecisionOverride.size(); f_XYZ++)
				{
				std::shared_ptr<BiDecisionOverride> f_Oride = m_vec_DecisionOverride[f_XYZ];

				if(f_Oride->acScan() == true)
					{
					return true;
					}
				}

			return false;
			};

		int m_ecomSelectedCount;
		int m_inputSelectedCount;
		int m_outputSelectedCount;
		int m_wireSelectedCount;

		std::vector<std::shared_ptr<BiDecisionOverride>> m_vec_DecisionOverride;
		std::vector<std::shared_ptr<BiDecisionA>> m_vec_DecisionA;

		bool m_Visible;

		time_t m_Trial_Length_Remain;

		int m_PipeChan;
		int m_Existence_ID;
		int m_Existence_ShareID;
	};

class SelectionSave;

class DecisionWheel
	{
	public:
		DecisionWheel()
			{
			acClear();

			m_position.m_X = 0.0f;
			m_position.m_Y = 0.0f;

			m_Selection_Bank.clear();

			m_SelectionIndex = 0;
			m_DecisionIndex = 0;

			m_Layer = 0;
			m_LayerPos = 0;
			}
		~DecisionWheel()
			{
			acClear();

			m_position.m_X = 0.0f;
			m_position.m_Y = 0.0f;
		
			m_Selection_Bank.clear();
			
			m_SelectionIndex = 0;
			m_DecisionIndex = 0;

			m_Layer = 0;
			m_LayerPos = 0;
			}

		void acClear(void)
			{
			for(int f_XYZ = 0; f_XYZ < m_vec_Selection_com.size(); f_XYZ++)
				{
				m_vec_Selection_com[f_XYZ]->acSelect(false);
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_Selection_input.size(); f_XYZ++)
				{
				m_vec_Selection_input[f_XYZ]->acSelect(false);
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_Selection_output.size(); f_XYZ++)
				{
				m_vec_Selection_output[f_XYZ]->acSelect(false);
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_Selection_wire.size(); f_XYZ++)
				{
				m_vec_Selection_wire[f_XYZ]->acSelect(false);
				}

			m_vec_Selection_com.clear();
			m_vec_Selection_input.clear();
			m_vec_Selection_output.clear();
			m_vec_Selection_wire.clear();
			m_Selection_base = nullptr;
			}

		void acClearHighLight(void)
			{
			if(m_LayerPos == 0)
				{
				for(int f_XYZ = 0; f_XYZ < m_vec_HighLighted_com.size(); f_XYZ++)
					{
					m_vec_HighLighted_com[f_XYZ]->acHighLight(false);
					}

				m_vec_HighLighted_com.clear();
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_HighLighted_input.size(); f_XYZ++)
				{
				m_vec_HighLighted_input[f_XYZ]->acHighLight(false);
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_HighLighted_output.size(); f_XYZ++)
				{
				m_vec_HighLighted_output[f_XYZ]->acHighLight(false);
				}

			for(int f_XYZ = 0; f_XYZ < m_vec_HighLighted_wire.size(); f_XYZ++)
				{
				m_vec_HighLighted_wire[f_XYZ]->acHighLight(false);
				}

			m_vec_HighLighted_input.clear();
			m_vec_HighLighted_output.clear();
			m_vec_HighLighted_wire.clear();
			}

		bool acSelectionGrow(BiVector f_Direction);

		bool acReposition(BiVector f_Direction, bool f_Click = false);

		std::shared_ptr<SelectionPreList> acMakeList(void);

		void acSelectBox(BiVector f_Min2D, BiVector f_Max2D)
			{
			acClearHighLight();

			std::vector<std::shared_ptr<Qcom>> f_vec_ComList_Within;

			for(int f_XY = 0; f_XY < g_QcomManager->m_vec_Qcom.size(); f_XY++)
				{
				std::shared_ptr<Qcom> f_Com = g_QcomManager->m_vec_Qcom[f_XY];

				//half check
				if(f_Com->m_position.m_X > f_Min2D.m_X &&
					f_Com->m_position.m_Y > f_Min2D.m_Y &&
					f_Com->m_position.m_X < f_Max2D.m_X &&
					f_Com->m_position.m_Y < f_Max2D.m_Y)
					{
					m_vec_Selection_com.push_back(f_Com);

					m_position.m_X = f_Com->m_position.m_X;
					m_position.m_Y = f_Com->m_position.m_Y;

					f_Com->acHighLight(true);
					}
				}
			}

		void acPressIn(void)
			{
			m_LayerPos++;

			acClearHighLight();

			if(m_LayerPos >= 2)
				{
				acClear();

				m_LayerPos = 0;

				m_Layer++;

				if(m_vec_Selection_com.size() == 1)
					{
					std::shared_ptr<Qcom> f_com = m_vec_Selection_com[0];

					g_QcomManager->m_Qcom = f_com;
					}
				else
					{
					m_LayerPos = 1;

					m_Layer--;
					}
				}
			else
				{
				if(m_vec_Selection_com.size() == 1)
					{
					std::shared_ptr<Qcom> f_com = m_vec_Selection_com[0];

					if(f_com->m_vec_Input.size() > 0)
						{
						std::shared_ptr<QcomInput> f_Input = f_com->m_vec_Input[0];

						f_Input->acHighLight(true);

						m_vec_HighLighted_input.push_back(f_Input);

						m_position = f_Input->m_position;
						}
					else if(f_com->m_vec_Output.size() > 0)
						{
						std::shared_ptr<QcomOutput> f_Output = f_com->m_vec_Output[0];

						f_Output->acHighLight(true);

						m_vec_HighLighted_output.push_back(f_Output);

						m_position = f_Output->m_position;
						}
					}
				}
			}

		void acPressOut(void)
			{
			m_LayerPos--;

			if(m_LayerPos < 0)
				{
				acClear();

				m_LayerPos = 1;

				m_Layer--;

				if(m_Layer >= 0)
					{
					std::shared_ptr<Qcom> f_com = g_QcomManager->ac_Find_Com_ByID(g_QcomManager->m_Qcom->m_parentcomid);

					g_QcomManager->m_Qcom = f_com;
					}
				else if(m_Layer >= -1)
					{
					g_QcomManager->m_Qcom = g_QcomManager->mam_Qcom;
					}
				else if(m_Layer < -5)
					{
					m_Layer = -5;
					}
				}
			else
				{
				acClearHighLight();
				}
			}

		int m_LengthPosition;
		int m_Layer;
		int m_LayerPos;

		BiVector m_SelectPosition;
		BiVector m_position;

		std::vector<std::shared_ptr<SelectionSave>> m_Selection_Bank;

		int m_SelectionIndex;
		int m_DecisionIndex;

		std::shared_ptr<Cube::Qcom> m_Selection_base;
		std::vector<std::shared_ptr<Cube::Qcom>> m_vec_Selection_com;
		std::vector<std::shared_ptr<Cube::QcomInput>> m_vec_Selection_input;
		std::vector<std::shared_ptr<Cube::QcomOutput>> m_vec_Selection_output;
		std::vector<std::shared_ptr<Cube::QcomWire>> m_vec_Selection_wire;

		std::vector<std::shared_ptr<Cube::Qcom>> m_vec_HighLighted_com;
		std::vector<std::shared_ptr<Cube::QcomInput>> m_vec_HighLighted_input;
		std::vector<std::shared_ptr<Cube::QcomOutput>> m_vec_HighLighted_output;
		std::vector<std::shared_ptr<Cube::QcomWire>> m_vec_HighLighted_wire;
	};

class DecisionCom_QamInfo
	{
	public:
		DecisionCom_QamInfo() { acClear(); };
		~DecisionCom_QamInfo() { acClear(); };

		void acClear(void)
			{
			m_originalsourceqamid = -1;
			m_OriginOwner.clear();
			m_SourceOwner.clear();
			};

		std::string m_SourceOwner;
		std::string m_OriginOwner;
		int m_originalsourceqamid;
	};

class DecisionCom
	{
	public:
		DecisionCom() { acClear(); };
		DecisionCom(int f_ID, bool f_loadall = false);
		~DecisionCom() { acClear(); };

		void acClear(void)
			{
			m_typed = 1;
			m_QamID = 0;
			m_Mod_Type.clear();
			m_Mod_Target.clear();
			m_Mod_Name.clear();
			m_Selected_Mod_Index = 0;
			m_Trial_Length = -1;
			};

		void ac_Save(void);

		void acInsert_Mod_Target(int f_Type, std::string f_Mod_Target);
		void acSelect_Mod_Target(std::string f_Mod_Target, int f_Index = -5);
		void acComplete_Mod_Target(std::string f_Mod_Name, int f_Index = -5);
		void acComplete_Mod_Target(std::string f_Mod_Name, std::string f_Mod_Target);

		//cls type interop
		std::shared_ptr<BiDecisionQ> acGen_DecisionQ_fromDecisionCom(void);
		void acGen_DecisionCom_fromDecisionQ(std::shared_ptr<BiDecisionQ> f_DecisionQ);

		std::string acGet_Type(void);
		std::string acGet_Target(void);
		std::string acGet_Name(void);

		void acSet_Type(std::string f_Type_Buffer);
		void acSet_Target(std::string f_Target_Buffer);
		void acSet_Name(std::string f_Name_Buffer);

		std::vector<int> m_Mod_Type;
		std::vector<std::string> m_Mod_Target;
		std::vector<std::vector<std::string>> m_Mod_Name;
		int m_Selected_Mod_Index;

		time_t m_Trial_Length;

		int m_ID;
		int m_typed;
		int m_QamID;
		std::shared_ptr<DecisionCom_QamInfo> m_QamInfo;
	};

class DecisionManager
	{
	public:
		DecisionManager()
			{
			acClear();

			m_vec_DecisionCom.clear();

			m_Frame = std::make_shared<std::thread>(&DecisionManager::acFrame, this);
			};
		~DecisionManager()
			{
			m_vec_DecisionCom.clear();
			};

		void acClear(void)
			{
			m_vec_DecisionQ.clear();
			};

		std::string acLoadA_ContractToggle(void);
		std::string acLoadA_InsertCom(int f_CID);
		std::string acLoadA_ShareShop(std::string f_ModeString);
		std::string acLoadA_DeleteCom(std::shared_ptr<Qcom> f_com);
		std::string acLoadA_CutCom(std::shared_ptr<Qcom> f_com);
		std::string acLoadA_CopyCom(std::shared_ptr<Qcom> f_com);
		std::string acLoadA_PasteCom(std::shared_ptr<Qcom> f_com);
		std::string acLoadA_WireStandard(std::shared_ptr<Qcom> f_A, std::shared_ptr<Qcom> f_B, std::shared_ptr<QcomOutput> f_A_output, std::shared_ptr<QcomInput> f_B_input);
		std::string acLoadA_QamByID(int f_QamID, time_t f_Trial);
		std::string acLoadA_QamStabilise(void);

		void acLoad_ApplicationSpecificLegacy(void);
		void acLoad_DecisionCom(int f_QamID);
		
		void acFrame(void);

		std::shared_ptr<std::thread> m_Frame;

		std::shared_ptr<DecisionWheel> m_Wheel;
		std::vector<std::shared_ptr<BiDecisionQ>> m_vec_DecisionQ;
		std::vector<std::shared_ptr<DecisionCom>> m_vec_DecisionCom;

		std::vector<std::shared_ptr<Qcom>> m_Paste_Buffer;

		std::vector<std::shared_ptr<BiDecisionA>> m_UnDo;
	};

extern std::vector<std::shared_ptr<DecisionManager>> g_vec_DecisionsManager;

class SelectionSave
{
public:
	SelectionSave()
		{
		m_vec_Selection_com.clear();
		m_vec_Selection_input.clear();
		m_vec_Selection_output.clear();
		m_vec_Selection_wire.clear();

		std::shared_ptr<DecisionWheel> f_WHL = g_vec_DecisionsManager[0]->m_Wheel;

		for(int f_Jet = 0; f_Jet < f_WHL->m_vec_Selection_com.size(); f_Jet++)
			{
			m_vec_Selection_com.push_back(f_WHL->m_vec_Selection_com[f_Jet]);
			}

		for(int f_Jet = 0; f_Jet < f_WHL->m_vec_Selection_input.size(); f_Jet++)
			{
			m_vec_Selection_input.push_back(f_WHL->m_vec_Selection_input[f_Jet]);
			}

		for(int f_Jet = 0; f_Jet < f_WHL->m_vec_Selection_output.size(); f_Jet++)
			{
			m_vec_Selection_output.push_back(f_WHL->m_vec_Selection_output[f_Jet]);
			}

		for(int f_Jet = 0; f_Jet < f_WHL->m_vec_Selection_wire.size(); f_Jet++)
			{
			m_vec_Selection_wire.push_back(f_WHL->m_vec_Selection_wire[f_Jet]);
			}
		}

	~SelectionSave()
		{
		m_vec_Selection_com.clear();
		m_vec_Selection_input.clear();
		m_vec_Selection_output.clear();
		m_vec_Selection_wire.clear();
		}

	std::vector<std::shared_ptr<Cube::Qcom>> m_vec_Selection_com;
	std::vector<std::shared_ptr<Cube::QcomInput>> m_vec_Selection_input;
	std::vector<std::shared_ptr<Cube::QcomOutput>> m_vec_Selection_output;
	std::vector<std::shared_ptr<Cube::QcomWire>> m_vec_Selection_wire;
};

#define BiCarr std::shared_ptr

class BiCheckpointDescriptor
{
public:
	BiCheckpointDescriptor(std::string f_FunctionLocation, std::string f_PositioninFunction)
		{
		acClear();
		m_FunctionLocation = f_FunctionLocation;
		m_PositioninFunction = f_PositioninFunction;
		};
	~BiCheckpointDescriptor() { acClear(); };

	void acClear(void)
		{
		m_FunctionLocation.clear();
		m_PositioninFunction.clear();
		m_AdType = -1;
		};

	bool acCheck(BiCarr<BiCheckpointDescriptor> f_DescC)
		{
		if(m_FunctionLocation.compare(f_DescC->m_FunctionLocation) == 0)
			{
			if(m_PositioninFunction.compare(f_DescC->m_PositioninFunction) == 0)
				{
				m_Qcom->ac_Execute();

				return true;
				}
			}

		return false;
		}

	std::string m_FunctionLocation;
	std::string m_PositioninFunction;

	std::shared_ptr<Qcom> m_Qcom;

	bool m_Affinity;

	int m_AdType;
	std::shared_ptr<Qcom_eslfunction> m_AdinDecisionsManager;
};

class CheckpointManager
{
public:
	CheckpointManager() { acClear(); };
	~CheckpointManager() { acClear(); };

	void acCapture(boost::any f_Object)
		{
		m_vec_CapturedObject.push_back(f_Object);
		};

	bool acCheckpoint(BiCarr<BiCheckpointDescriptor> f_CheckDesc)
		{
		for(int f_XY = 0; f_XY < m_vec_CheckPoints.size(); f_XY++)
			{
			if((m_vec_CheckPoints[f_XY]->acCheck(f_CheckDesc) == true) && (m_vec_CheckPoints[f_XY]->m_Affinity == true))
				{
				return false;
				}
			}

		return true;
		};

	bool acCheckpoint(std::string f_FunctionLocation, std::string f_PositioninFunction)
		{
		BiCarr<BiCheckpointDescriptor> f_Desc = std::make_shared<BiCheckpointDescriptor>(f_FunctionLocation, f_PositioninFunction);

		return acCheckpoint(f_Desc);
		};

	void acClear(void)
		{
		m_vec_CheckPoints.clear();

		acClearCap();
		};

	void acClearCap(void)
		{
		m_vec_CapturedObject.clear();
		};

	void acRegister_Qcom(BiCarr<Qcom> f_com, BiCarr<BiCheckpointDescriptor> f_desc)
		{
		f_desc->m_Qcom = f_com;
		m_vec_CheckPoints.push_back(f_desc);
		};

	std::vector<BiCarr<BiCheckpointDescriptor>> m_vec_CheckPoints;
	std::vector<boost::any> m_vec_CapturedObject;
};

};

#endif