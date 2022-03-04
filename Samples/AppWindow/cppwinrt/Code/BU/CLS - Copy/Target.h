/*

qcom.h - ECOM Native Decl osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#pragma once

#include <vector>
#include <math.h>

#include "Include/Cube.h"

#include "Collection.h"

#include "Code/Cube/qcom.h"

using namespace Cube;
using namespace std;

#define INSTA_TYPE_VAR_DEF 0
#define INSTA_TYPE_VAR_CALL 1
#define INSTA_TYPE_FUNC_DEF 2
#define INSTA_TYPE_FUNC_CALL 3
#define INSTA_TYPE_CONDITIONAL 4
#define INSTA_TYPE_LOOP_DEF 5
#define INSTA_TYPE_DATA 6
#define INSTA_TYPE_COUNT 7
#define INSTA_TYPE_LM_OPER_EQUALS 7

#define ESL_INSTA_TYPE_VAR_DEF 0
#define ESL_INSTA_TYPE_SYS_DEF 1
#define ESL_INSTA_TYPE_CLASS_DEF 2
#define ESL_INSTA_TYPE_CLASSVAR_DEF 3
#define ESL_INSTA_TYPE_FUNC_DEF 4
#define ESL_INSTA_TYPE_FUNC_CALL 5
#define ESL_INSTA_TYPE_CONDITIONAL 6
#define ESL_INSTA_TYPE_LOOP_DEF 7
#define ESL_INSTA_TYPE_RETURN 8
#define ESL_INSTA_TYPE_COUNT 9
#define ESL_INSTA_TYPE_LM_OPER_EQUALS 10
#define ESL_INSTA_TYPE_VAR_CALL 100
#define ESL_INSTA_TYPE_CLASS_VAR_CALL 200    //separate var/classvar call
#define ESL_INSTA_TYPE_VAR_SYS_DEF_CALL 300

#define ESL_INSTA_TYPE_VAR_DEF_MORF_COUNT 4
#define ESL_INSTA_TYPE_VAR_DEF_OPER_MORF_COUNT 11
#define ESL_INSTA_TYPE_SYS_DEF_MORF_COUNT 4
#define ESL_INSTA_TYPE_SYS_DEF_OPER_MORF_COUNT 11
#define ESL_INSTA_TYPE_VAR_SYS_DEF_CALL_MORF_COUNT 11
#define ESL_INSTA_TYPE_FUNC_DEF_MORF_COUNT 3
#define ESL_INSTA_TYPE_FUNC_CALL_MORF_COUNT 7
#define ESL_INSTA_TYPE_CONDITIONAL_MORF_COUNT 11
#define ESL_INSTA_TYPE_LOOP_DEF_MORF_COUNT 11
#define ESL_INSTA_TYPE_CLASS_DEF_MORF_COUNT 3
#define ESL_INSTA_TYPE_CLASS_VAR_MORF_COUNT 4

#define ESL_LINE_ENDING std::string("\n")

#define VAR_DEF_TYPE_ZERO_TO_ONE 0
#define VAR_DEF_TYPE_ONE_TO_HUNDRED 1
#define VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND 2
#define VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION 3
#define VAR_DEF_TYPE_RANDOM 4
#define VAR_DEF_TYPE_SYSTEM 5

#define LINE_TYPE_START 0
#define LINE_TYPE_NORMAL 1
#define LINE_TYPE_INPUT 2
#define LINE_TYPE_CONTROL 3
#define LINE_TYPE_OUTPUT 4
#define LINE_TYPE_COUNT 5

#define CLS_TARGET_SCRIPT_TYPE_ESL 1

#define VAR_TYPE_INT 0
#define VAR_TYPE_FLT 1
#define VAR_TYPE_HEX 2
#define VAR_TYPE_BIN 3

#define ESL_MORF_TYPE_VAR 0
#define ESL_MORF_TYPE_SYS 1
#define ESL_MORF_TYPE_CLSVAR 2

   ////////////////////////////////////////////////////
  //  Uses Qcom directly and is cross compatible
 //   ECOM Native Generation Definitions
//    Generation happens in the miner

#define ECOM_FUNCTION_GEN_MAX 1
#define ECOM_COM_GEN_MIN 0
#define ECOM_COM_GEN_MAX 2
#define ECOM_COM_GEN_WEIGHT 0 
#define ECOM_DIV_ELEMENT 5
#define ECOM_ICO_MIN 0
#define ECOM_ICO_MAX 4
#define ECOM_ICO_WEIGHT 0
#define ECOM_GEN_LINES_MIN 0
#define ECOM_GEN_LINES_MAX 15
#define ECOM_GEN_LINES_WEIGHT 0

#define ECOIN_TARGET_LOWTON_STORAGE 50
#define ECOIN_TARGET_SCP_LOWTON_STORAGE 240

#define ECOIN_TARGET_MATCH_LENGTH_FACTOR 1.57f
#define ECOIN_TARGET_MATCH_COLOR_LENGTH_FACTOR 2.0f
#define ECOIN_TARGET_MATCH_MIXIN 5.57f
#define ECOIN_TARGET_MATCH_THRESH 0.3f
#define ECOIN_TARGET_MATCH_THRESH_UP 4.0f
#define ECOIN_TARGET_COMPARE_THRESH 100.0f
#define ECOIN_TARGET_SCP_COMPARE_THRESH 100.0f

#define ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_FLOAT 0
#define ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_INT 1
#define ECOIN_TARGET_CURRENT_SPECIFIC_VARTYPES_STRING 2

#define ECOIN_DATA_CHUNK_LENGTH_COUNT 7

#define ECOIN_TARGET_GLOBAL true
#define ECOIN_TARGET_LOCAL false //mining scope

#define ECOIN_MUTEX_MODE_OFF 0
#define ECOIN_MUTEX_MODE_GATHER 1
#define ECOIN_MUTEX_MODE_PRINT 2

extern bool g_EnablePR;

extern int g_SchemaTop;
extern Cube::BiVector g_SchemaRef[500];
extern int g_SchemaSize;

extern int g_ComponentStamp;

extern int g_TargetID;

namespace ecoin
{
	class classTarget
	{
	public:
		classTarget()
			{
			m_Mark = 0.0f;
			m_Collection = std::make_shared<classCollection>();
			m_Collection->acClear();
			}
		classTarget(std::shared_ptr<CubeHESH> f_Hesh);

		~classTarget()
			{
			}

		bool acSimplify(void);
		bool acEvolve(void);
		bool acAdapt(void);

		void acGen_Humanoid(void);
		void acGen_Vehicle_Ground(void);

		void acLoad_from_TargetID(int f_TargetID);

		void acPrintStats(void);

		bool acCompare(std::shared_ptr<classTarget> f_Target, float f_QualityLvl, float f_Grade, bool f_testVolumes);

		float acMatch(std::shared_ptr<classTarget> f_Target);

		void acSaveCloud(std::string f_Name);

		float m_Mark;

		std::shared_ptr<classCollection> m_Collection;
		classWorth m_Worth;
	};

	class classTargetScript
	{
	public:
		classTargetScript()
			{
			m_Collection = std::make_shared<classCollection>();
			m_Collection->acClear();

			m_CollectionScript = std::make_shared<classCollectionScript>();
			m_CollectionScript->acClear();
			}
		classTargetScript(std::shared_ptr<CubeHESH> f_Hesh);

		bool acSimplify(void);
		bool acEvolve(void);
		bool acAdapt(void);

		void acGen_Humanoid(void);
		void acGen_Vehicle_Ground(void);

		void acLoad_from_TargetID(int f_TargetID);

		void acPrintStats(void);

		bool acCompare(std::shared_ptr<classTarget> f_Target, float f_QualityLvl, float f_Grade, bool f_testVolumes);

		void acSaveCloud(std::string f_Name);

		void ag_PrintScriptHeader(void);
		void acPrint(void);

		float m_Mark;

		std::shared_ptr<classCollection> m_Collection;
		std::shared_ptr<classCollectionScript> m_CollectionScript;
		classWorth m_Worth;
	};

	class classInsta
	{
	public:
		classInsta(std::string f_StringC, int f_Type);

		int m_Type;
		std::string m_String;

		float m_Value;
	};

	class classCodeLine
	{
	public:
		classCodeLine();

		std::vector<std::shared_ptr<classInsta>> m_vec_Code;
		int m_idx_vec_Code;
	};

	class classMark
	{
	public:
		classMark();

		void acIncrement(std::shared_ptr<classMark> f_Mark);
		void acReset(void);
		float acSumStuff(float f_QualityRank);

		std::vector<int> m_vec_Int;
		int m_idx_flip;
		int m_idx_vec_Int;
	};

	class classAchievement
	{
	public:
		classAchievement();

		bool m_Success;
		std::shared_ptr<classMark> m_Mark;

		//std::vector<.m_vec_ReturnArgs = [];
		//this.m_idx_vec_ReturnArgs = 0;
	};

	class classFunction
	{
	public:
		classFunction();

		void acInsertAuthority(shared_ptr<classElement> f_Element, int f_Index);
		std::shared_ptr<classMark> acTestElement(shared_ptr<classElement> f_Element, int f_Index);
		std::shared_ptr<classMark> acInterrogate(float f_QualityRank);

		shared_ptr<Qcom_eslfunction> acConvert(void);

		std::string m_vec_String;

		int m_Type;
		bool m_Status;

		std::string m_Name;
		std::string m_Hash;
		std::string m_String;

		//>?
		//this.m_Level = [];
		//this.m_vec_Code = [];

		std::vector<std::shared_ptr<classInsta>> m_vec_Insta;
		int m_idx_vec_Insta;

		std::vector<std::shared_ptr<classCodeLine>> m_vec_CodeLineStorage;
		int m_idx_vec_CodeLineStorage;

		std::vector<int> m_vec_CodeLineStorageFlag;
		int m_idx_vec_CodeLineStorageFlag;

		std::shared_ptr<classMark> m_Mark;
	};

	class classFactor
	{
	public:
		classFactor();

		int m_Use;
	};

	class classCountLock
	{
	public:
		classCountLock(int f_Count, std::string f_StringC, int f_Type);

		int m_Count;
		std::string m_String;
		int m_Factor;
	};

	class classBridgeResult
	{
	public:
		classBridgeResult();

		std::vector<int> m_vec_LineIndex;
		std::vector<int> m_vec_Position_Equals;
		std::vector<int> m_vec_Position_Argument;
		std::vector<std::string> m_vec_String_Equal;
		int m_idx_vec;
	};

	class clsName
	{
	public:
		clsName(std::string f_Name, int f_BitCount, int f_INSTA, int f_index_Insta, int f_index_Function);

		std::string m_Name;
		int m_BitCount;
		int m_INSTA_Type;
		int m_index_Insta;
		int m_index_Function;

		std::vector<std::shared_ptr<clsName>> m_vec_Name;
		int m_idx_vec_Name;
	};

	class classTarget_JScript
	{
	public:
		classTarget_JScript();

		std::string acMakeUnison(std::shared_ptr<classTarget_JScript> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, shared_ptr<classElement> f_Element, int f_index_Insta, int f_index_Function);
		void acGatherNames(void);

		std::string ac_next_InputName(int f_Type);
		std::string ac_next_ControlName(int f_Type);
		std::string ac_next_OutputName(int f_Type);

		void acMerge_ICOtoName(void);
		void acGatherICO_default(void);

		void acResetLine(void);

		std::shared_ptr<classBridgeResult> acScan_Code_Bridges(std::shared_ptr<classFunction> f_Function, std::string f_String);
		std::shared_ptr<classMark> acMark_TestICO(std::shared_ptr<classTarget_JScript> f_Target);
		std::shared_ptr<classMark> acMark_Bridges(void);
		void acGatherICO_jscript_base(void);
		void acGatherICO_html_base(void);
		void acGatherICO_php_base(void);
		void acGen_SuperName(std::string f_GeoName);
		void acResetFactor(int f_Type);
		void acDecFactor(int f_Type);
		void acResetFactors(int f_Type);
		bool acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, shared_ptr<classElement> f_Element);
		bool acFactorStrength(int f_Type, std::shared_ptr<classFunction> f_Function, shared_ptr<classElement> f_Element);
		void acFromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_JScript> f_Target);
		void acMergeUpper(void);
		void acMergeSave(void);
		bool acCompare(std::shared_ptr<classTarget_JScript> f_Target, float f_QualityRank, float f_Grade);

		void acLoad_Biscuit(void);

		std::string ac_takeMeasurement(shared_ptr<classElement> f_Vertex);
		int ac_takeMeasurementINTV1(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap);

		void acPowerDown(void);

		std::shared_ptr<classCollection> m_Collection;

		std::vector<std::shared_ptr<classFunction> > m_vec_Function;
		int m_idx_vec_Function;
	
		float m_Mark;
	
		std::vector<std::shared_ptr<clsName>> m_vec_Name;
		int m_idx_vec_Name;
	
		int m_SchemaTop = 0;
		std::vector<std::shared_ptr<BiVector>> m_SchemaRef;

		int m_LastType;
		int m_LastTypeII;
		int m_LastTypeIII;

		std::vector<std::shared_ptr<classFactor> > m_Factor;

		int m_InstaCountMap = 0;

		std::string m_String;

		  ////////////////////////////////////
		 // LEGACY of Structured Analysis
		//
		//this.m_vec_Result = [];
		//this.m_idx_vec_Result = 0;
	
		std::vector<std::shared_ptr<classCountLock> > m_vec_CountLock;
		int m_idx_vec_CountLock;

		std::vector<int> m_GRCinput;
		std::vector<int> m_GRMinput;
		std::vector<int> m_GRCcontrol;
		std::vector<int> m_GRMcontrol;
		std::vector<int> m_GRCoutput;
		std::vector<int> m_GRMoutput;

		std::vector<std::shared_ptr<classAchievement> > m_vec_Achievement;
		int m_idx_vec_Achievement;
	};

	class classTarget_Ecom
	{
	public:
		classTarget_Ecom();
		classTarget_Ecom(bool f_Scope);
		~classTarget_Ecom();
#if 0
		void acGatherNames(void);

		std::string ac_next_InputName(int f_Type);
		std::string ac_next_ControlName(int f_Type);
		std::string ac_next_OutputName(int f_Type);

		void acMerge_ICOtoName(void);
		void acGatherICO_default(void);
#endif

		void acResetLine(void);

#if 0
		std::shared_ptr<classBridgeResult> acScan_Code_Bridges(std::shared_ptr<classFunction> f_Function, std::string f_String);
		std::shared_ptr<classMark> acMark_TestICO(std::shared_ptr<classTarget_Ecom> f_Target);
		std::shared_ptr<classMark> acMark_Bridges(void);

		void acGatherICO_jscript_base(void);
		void acGatherICO_html_base(void);
		void acGatherICO_php_base(void);
		void acGen_SuperName(std::string f_GeoName);
		void acResetFactor(int f_Type);
		void acResetFactors(int f_Type);

		void acMergeUpper(void);
		void acMergeSave(void);
#endif

		void acPrepare_Lense(void);
		void acDecFactor(int f_Type);

		std::string acMakeUnison(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, int f_index_Insta, int f_index_Function);
		std::string acMakeUnisonType(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_index_Insta, int f_index_Function, int f_TypeGiven = -100, int f_FullDefinition = false);

		void acFromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);

		bool acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth);
		bool acFactorStrength(int f_Type, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth);
		bool acFactorStrengthAff(int f_Type, std::shared_ptr<classFunction> f_Function, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth);
		bool acFactorStrengthVar(int f_Type, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth);
		bool acFactorStrengthVarString(int f_Type, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth);

		std::string acGen_Var_fromHesh(void);
		std::shared_ptr<Qcom> acGen_com_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);
		std::shared_ptr<QcomInput> acGen_com_input_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);
		std::shared_ptr<QcomOutput> acGen_com_output_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);
		std::shared_ptr<Qcom_genScript> acGen_gen_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);
		std::string acGen_genline_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);
		std::shared_ptr<Qcom_eslfunction> acGen_com_function_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target);

		std::string ac_ext_Make_VarType(int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth);

		std::string ac_takeMeasurement(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth);
		int ac_takeMeasurementINTV1(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Cap);
		float ac_takeMeasurementFLTV1(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Cap);
		bool ac_takeMeasurementBLTV1(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_Cap);
		int ac_printMeasurementINTS(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_RangeWidth, int f_WeightRangetoStart);

		bool acCompare(std::shared_ptr<classTarget_Ecom> f_Target, float f_QualityRank, float f_Grade);

		std::string m_String;

		std::shared_ptr<classCollection> m_Collection;
		std::vector<std::shared_ptr<Qcom> > m_vec_Ecom;
	
		float m_Mark;
		bool m_GlobalScope;

		std::vector<std::shared_ptr<clsName>> m_vec_Name;
		std::vector<std::shared_ptr<BiVector>> m_SchemaRef;
		std::vector<std::shared_ptr<classFactor>> m_Factor;
		std::vector<std::shared_ptr<classCountLock>> m_vec_CountLock;
		std::vector<std::shared_ptr<classAchievement>> m_vec_Achievement;

		int m_LastType;
		int m_LastTypeII;
		int m_LastTypeIII;

		std::vector<int> m_GRCinput;
		std::vector<int> m_GRMinput;
		std::vector<int> m_GRCcontrol;
		std::vector<int> m_GRMcontrol;
		std::vector<int> m_GRCoutput;
		std::vector<int> m_GRMoutput;

		int m_idx_vec_Achievement;
		int m_idx_vec_CountLock;
		int m_idx_vec_Function;
		int m_idx_vec_Name;

		int m_SchemaTop = 0;
	};

	enum LMeasure_Type
	{
		LMTYPE_Measurement,
		LMTYPE_MeasurementINTV1,
		LMTYPE_MeasurementFLTV1,
		LMTYPE_MeasurementFLTV5_LB,
		LMTYPE_MeasurementBLTV1,
		LMTYPE_MeasurementINTS,
		LMTYPE_Total
	};

	class LMeasure
	{
	public:
		LMeasure(std::string f_Measurement);
		LMeasure(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, int f_MeasurementINTV1);
		LMeasure(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, float f_MeasurementFLTV1);
		LMeasure(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, float f_Boundary, float f_MeasurementFLTV5);
		LMeasure(int f_Depth, int f_Cap, bool f_MeasurementBLTV1);
		LMeasure(int f_RangeWidth, int f_WeightRangetoStart, int f_MeasurementINTS);
		~LMeasure()
			{ acClear(); };

		void acClear(void);

		int m_LMType;

		std::string m_Measurement;
		int m_MeasurementINTV1;
		float m_MeasurementFLTV1;
		bool m_MeasurementBLTV1;
		int m_MeasurementINTS;

		int m_StartRange;
		int m_EndRange;
		int m_WeightRangetoStart;
		int m_Depth;
		int m_Cap;

		int m_RangeWidth;
		int m_Boundary;
		int m_Notable;
	};

	class LMap
	{
	public:
		LMap()
			{ acClear(); };
		~LMap()
			{ acClear(); };

		void acClear()
			{
			m_vec_Measure.clear();
			};

		std::vector<std::shared_ptr<LMeasure>> m_vec_Measure;
		std::vector<int> m_vec_ElementID;
	};

	class classLMap
	{
	public:
		classLMap();
		~classLMap();

#if 0
		std::string acMakeUnison(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, shared_ptr<classElement> f_Element, int f_index_Insta, int f_index_Function);
		void acGatherNames(void);

		std::string ac_next_InputName(int f_Type);
		std::string ac_next_ControlName(int f_Type);
		std::string ac_next_OutputName(int f_Type);

		void acMerge_ICOtoName(void);
		void acGatherICO_default(void);

		std::shared_ptr<classBridgeResult> acScan_Code_Bridges(std::shared_ptr<classFunction> f_Function, std::string f_String);
		std::shared_ptr<classMark> acMark_TestICO(std::shared_ptr<classTarget_Ecom> f_Target);
		std::shared_ptr<classMark> acMark_Bridges(void);

		void acGatherICO_jscript_base(void);
		void acGatherICO_html_base(void);
		void acGatherICO_php_base(void);

		void acGen_SuperName(std::string f_GeoName);
		void acResetFactor(int f_Type);
		void acResetFactors(int f_Type);
#endif

		void acResetLine(void);
		void acDecFactor(int f_Type);
		bool acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, shared_ptr<classElement> f_Element);

		std::string acMakeUnisonType(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, int f_index_Insta, int f_index_Function, std::string f_LineString, int f_LineStartIndex, int f_TypeGiven = -100, bool f_FullDefinition = false);

		int acPull_gen_ElementID(int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, int f_OCSCP_ThreadIndex = 0);

		void acRangeAD(void);

		  //////////////////////////////////////////////////////////////
		 // this FromTarget Collection is part of the Qcom Interface
		//  FromTarget_FromEcom
		std::string acGen_Var_fromEcom(int f_Line_Index, int f_Prec_Type, bool f_Value_Given_Bool, std::string f_Line, std::string f_Var_Type_String, std::string f_Var_Name_String, std::string f_Var_Value_String = "");
		std::shared_ptr<Qcom> acGen_com_FromEcom(std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);
		std::shared_ptr<QcomInput> acGen_com_input_FromEcom(std::shared_ptr<QcomInput> f_Save_Input, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);
		std::shared_ptr<QcomOutput> acGen_com_output_FromEcom(std::shared_ptr<QcomOutput> f_Save_Output, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);
		std::shared_ptr<Qcom_genScript> acGen_gen_FromEcom(std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);
		std::string acGen_genline_FromEcom(std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride = -5);
		std::shared_ptr<Qcom_eslfunction> acGen_com_function_FromEcom(std::shared_ptr<Qcom_eslfunction> f_Save_Com_Function, int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target);

		bool ac_ext_Typing_isEqual(int f_Var_Typing, int f_Var_Current_Code);

		std::vector<std::vector<std::string>> ac_ext_eslLine_morf_array(std::string f_LineString);

		int ac_ext_Scan_Lines_Keyword_Next(int f_LineCount, int f_morf1, int f_morf2, std::shared_ptr<Qcom_eslfunction> f_Save_Com_Function, std::string f_Keyword);

		void acMergeUpper(void);
		void acMergeSave(void);

		bool acCompare(std::shared_ptr<classTarget_Ecom> f_Target, float f_QualityRank, float f_Grade);

		void acLoad_Biscuit(void);

		//Legacy
		std::string ac_takeMeasurement(shared_ptr<classElement> f_Vertex);
		int ac_takeMeasurementINTV1(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, int f_OCSCP_ThreadIndex);
		float ac_takeMeasurementFLTV1(shared_ptr<classElement> f_Vertex, float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Depth, int f_Cap);
		bool ac_takeMeasurementBLTV1(shared_ptr<classElement> f_Vertex, int f_Depth, int f_Cap, int f_OCSCP_ThreadIndex);
		void ac_takeMeasurementFLTV5_LowBounds(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, float f_Boundary, float f_RecordResult, int f_ElementID);
		int ac_printMeasurementINTS(shared_ptr<classElement> f_Vertex, int f_RangeWidth, int f_WeightRangetoStart);

		 ///////////////////////////////////////////////////
		// RECORDing LMap is diss-connected from Element //
		std::string ac_recordMeasurement(std::string f_RecordResult, int f_ElementID, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth);
		int ac_recordMeasurementINTV1(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, int f_RecordResult, int f_ElementID, bool f_Notable = true);
		float ac_recordMeasurementFLTV1(float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Depth, int f_Cap, float f_RecordResult, int f_ElementID);
		bool ac_recordMeasurementBLTV1(int f_Depth, int f_Cap, bool f_RecordResult, int f_ElementID);
		void ac_recordMeasurementFLTV5_LowBounds(float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Depth, int f_Cap, float f_Boundary, float f_RecordResult, int f_ElementID);
		int ac_recordMeasurementINTS(int f_RangeWidth, int f_WeightRangetoStart, int f_RecordResult, int f_ElementID);

		bool acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth);
		bool acRecordStrength(int f_Type, std::string f_LineString, int f_ElementID);
		bool acRecordStrengthVar(int f_Type, std::string f_LineString, float f_RecordResult, int f_ElementID, bool f_isRandom = false);
		bool acRecordStrengthVar(int f_Type, std::string f_LineString, int f_RecordResult, int f_ElementID, bool f_isRandom = false);
		bool acRecordStrengthVarString(int f_Type, std::string f_LineString, std::string f_RecordResult, int f_ElementID);

		int acRecordLine(std::string f_LineString);

		std::string ac_ext_Make_VarType(std::string f_LineString, int f_VertexID);

		bool acCompute(std::shared_ptr<classCollection> f_Collection, int f_OCSCP_ThreadIndex = 0, bool f_Lowton = false);

		void acClear(void);
		void acClearAway(void);

		void acPrepareLense(int f_OCSCP_ThreadIndex);

	public:
		shared_ptr<LMap> m_LMap;

		std::string m_String;

		std::vector<std::shared_ptr<Qcom>> m_vec_Ecom;

		bool m_GlobalScope;
		float m_Mark;

		int m_ADMAX;
		int m_ADHIGH;
		int m_ADLOW;

#if 0
		int m_LastType;
		int m_LastTypeII;
		int m_LastTypeIII;
#endif
	
		std::vector<std::shared_ptr<clsName>> m_vec_Name;
		std::vector<std::shared_ptr<BiVector>> m_SchemaRef;
		std::vector<std::shared_ptr<classFactor>> m_Factor;
		std::vector<std::shared_ptr<classCountLock>> m_vec_CountLock;
		std::vector<std::shared_ptr<classAchievement>> m_vec_Achievement;

		std::vector<int> m_GRCinput;
		std::vector<int> m_GRMinput;
		std::vector<int> m_GRCcontrol;
		std::vector<int> m_GRMcontrol;
		std::vector<int> m_GRCoutput;
		std::vector<int> m_GRMoutput;

		int m_idx_vec_Function;
		int m_idx_vec_Achievement;
		int m_idx_vec_CountLock;
		int m_idx_vec_Name;

		int m_SchemaTop;
	};

	class classTarget_ESL_Script
	{
	public:
		classTarget_ESL_Script();

		std::string acMakeUnison(std::shared_ptr<classTarget_ESL_Script> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, shared_ptr<classElement> f_Element, int f_index_Insta, int f_index_Function);
		void acGatherNames(void);

		std::string ac_next_InputName(int f_Type);
		std::string ac_next_ControlName(int f_Type);
		std::string ac_next_OutputName(int f_Type);

		void acMerge_ICOtoName(void);
		void acGatherICO_default(void);

		void acResetLine(void);

		std::shared_ptr<classBridgeResult> acScan_Code_Bridges(std::shared_ptr<classFunction> f_Function, std::string f_String);
		std::shared_ptr<classMark> acMark_TestICO(std::shared_ptr<classTarget_ESL_Script> f_Target);
		std::shared_ptr<classMark> acMark_Bridges(void);
		void acGatherICO_jscript_base(void);
		void acGatherICO_html_base(void);
		void acGatherICO_php_base(void);
		void acGen_SuperName(std::string f_GeoName);
		void acResetFactor(int f_Type);
		void acDecFactor(int f_Type);
		void acResetFactors(int f_Type);
		bool acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, shared_ptr<classElement> f_Element);
		bool acFactorStrength(int f_Type, std::shared_ptr<classFunction> f_Function, shared_ptr<classElement> f_Element);
		bool acFactorStrengthVar(int f_Type, std::shared_ptr<classFunction> f_Function, shared_ptr<classElement> f_Element);
		void acFromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_ESL_Script> f_Target);
		void acMergeUpper(void);
		void acMergeSave(void);
		bool acCompare(std::shared_ptr<classTarget_ESL_Script> f_Target, float f_QualityRank, float f_Grade);

		void acLoad_Biscuit(void);

		std::string ac_takeMeasurement(shared_ptr<classElement> f_Vertex);
		int ac_takeMeasurementINTV1(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap);
		float ac_takeMeasurementFLTV1(shared_ptr<classElement> f_Vertex, float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Depth, int f_Cap);
		bool ac_takeMeasurementBLTV1(shared_ptr<classElement> f_Vertex, int f_Depth, int f_Cap);

		void acPowerDown(void);

		std::shared_ptr<classCollection> m_Collection;

		std::vector<std::shared_ptr<classFunction>> m_vec_Function;
		int m_idx_vec_Function;
	
		float m_Mark;
	
		std::vector<std::shared_ptr<clsName>> m_vec_Name;
		int m_idx_vec_Name;
	
		int m_SchemaTop = 0;
		std::vector<std::shared_ptr<BiVector>> m_SchemaRef;

		int m_LastType;
		int m_LastTypeII;
		int m_LastTypeIII;

		std::vector<std::shared_ptr<classFactor>> m_Factor;

		int m_InstaCountMap = 0;

		std::string m_String;

		  ////////////////////////////////////
		 // LEGACY of Structured Analysis
		//
		//this.m_vec_Result = [];
		//this.m_idx_vec_Result = 0;
	
		std::vector<std::shared_ptr<classCountLock>> m_vec_CountLock;
		int m_idx_vec_CountLock;

		std::vector<int> m_GRCinput;
		std::vector<int> m_GRMinput;
		std::vector<int> m_GRCcontrol;
		std::vector<int> m_GRMcontrol;
		std::vector<int> m_GRCoutput;
		std::vector<int> m_GRMoutput;

		std::vector<std::shared_ptr<classAchievement>> m_vec_Achievement;
		int m_idx_vec_Achievement;
	};

	class classBridge
	{
	public:
		classBridge();

		void ac_add_Path(int f_A, int f_Type, int f_LineType);

		std::vector<int> m_vec_A;
		std::vector<int> m_vec_Type;
		std::vector<int> m_vec_LineType;
		int m_idx_vec;
	};

	class classListI
	{
	public:
		classListI(int f_INSTA);

		std::vector<std::string> m_vec_List;
		int m_idx_vec_List;
	};

	class classListC
	{
	public:
		classListC(int f_INSTA);

		std::vector<std::string> m_vec_List;
		int m_idx_vec_List;
	};

	class classListO
	{
	public:
		classListO(int f_INSTA);

		std::vector<std::string> m_vec_List;
		int m_idx_vec_List;
	};

	class classList_Target_Name
	{
	public:
		classList_Target_Name(int f_INSTA, std::shared_ptr<classTarget_JScript> f_Target);
		classList_Target_Name(int f_INSTA, std::shared_ptr<classTarget_ESL_Script> f_Target);
		classList_Target_Name(int f_INSTA, std::shared_ptr<classTarget_Ecom> f_Target);

		std::vector<std::string> m_vec_List;
		int m_idx_vec_List;
	};

	class classTestArg
	{
	public:
		classTestArg();

		std::vector<std::string> build_LastNameClose;
		std::vector<int> build_LastTypeClose;
		int f_indexInsta;
		int f_indexFunction;
	};

typedef std::string(*nameFuncPtr)(std::shared_ptr<classTarget_JScript> f_Target, std::shared_ptr<classTestArg> f_testARG);
typedef std::shared_ptr<classAchievement>(*FuncPtr)(std::shared_ptr<classTarget_JScript> f_Target, std::shared_ptr<classTestArg> f_testARG);

	extern std::string ag_NameStamp(std::string f_Measurement, int f_Type, int f_BitCount);

	extern int ag_Pull_gen_Element(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_OCSCP_ThreadIndex, int f_StartRange = -1, int f_EndRange = -1, int f_WeightRangetoStart = -1);

	extern int g_FunctionStamp;
	extern std::shared_ptr<classTarget_JScript> g_MasterTarget;

	extern std::vector<std::string> g_vec_scrInputName;
	extern int g_idx_vec_scrInputName;

	extern std::vector<std::string> g_vec_scrInputHTML;
	extern int g_idx_vec_scrInputHTML;

	extern std::vector<int> g_vec_scrInputType;
	extern int g_idx_vec_scrInputType;

	extern std::vector<nameFuncPtr> g_vec_scrInputNameCuteFunc;
	extern int g_idx_vec_scrInputNameCuteFunc;

	//extern std::vector<func_ptr_t> g_vec_scrInputPlaceCuteFunc;
	//extern int g_idx_vec_scrInputPlaceCuteFunc = 0;

	extern std::vector<FuncPtr> g_vec_scrInputTestCuteFunc;
	extern int g_idx_vec_scrInputTestCuteFunc;

	extern std::vector<std::string> g_vec_scrControlName;
	extern int g_idx_vec_scrControlName;

	extern std::vector<int> g_vec_scrControlType;
	extern int g_idx_vec_scrControlType;

	extern std::vector<std::string> g_vec_scrOutputName;
	extern int g_idx_vec_scrOutputName;

	extern std::vector<int> g_vec_scrOutputType;
	extern int g_idx_vec_scrOutputType;

	extern std::vector<std::shared_ptr<classBridge>> g_vec_control_Bridge;
	extern int g_idx_vec_control_Bridge;

	extern std::vector<std::shared_ptr<classBridge>> g_vec_output_Bridge;
	extern int g_idx_vec_output_Bridge;

	extern bool g_EnablePR;
	extern std::string g_ThisName;
	extern int g_ThisType;
	extern std::shared_ptr<classInsta> g_This;

	//temp define
#define classTarget_Generation_Script classTarget_ESL_Script

	  /////////////////////////////
	 //    Supa Type Targets    //
	//
	extern std::shared_ptr<classTarget> g_Target_1;
	extern std::shared_ptr<classTarget> g_Target_2;
	extern std::shared_ptr<classTarget_Ecom> g_Target_3;
	extern std::shared_ptr<classTarget_Ecom> g_Target_4;
	extern std::shared_ptr<classTarget_ESL_Script> g_Target_5;
	extern std::shared_ptr<classTarget_ESL_Script> g_Target_6;
	extern std::shared_ptr<classTarget_Generation_Script> g_Target_7;
	extern std::shared_ptr<classTarget_Generation_Script> g_Target_8;
	extern std::shared_ptr<classTarget_JScript> g_Target_9;
	extern std::shared_ptr<classTarget_JScript> g_Target_10;

	  ////////////////////////////////
	 //    Supa Shuttle Targets    //
	//
	extern std::shared_ptr<classTarget> gf_Target_1;
	extern std::shared_ptr<classTarget> gf_Target_2;
	extern std::shared_ptr<classTarget_Ecom> gf_Target_3;
	extern std::shared_ptr<classTarget_Ecom> gf_Target_4;
	extern std::shared_ptr<classTarget_ESL_Script> gf_Target_5;
	extern std::shared_ptr<classTarget_ESL_Script> gf_Target_6;
	extern std::shared_ptr<classTarget_Generation_Script> gf_Target_7;
	extern std::shared_ptr<classTarget_Generation_Script> gf_Target_8;
	extern std::shared_ptr<classTarget_JScript> gf_Target_9;
	extern std::shared_ptr<classTarget_JScript> gf_Target_10;

	  ////////////////////////////////
	 //    Supa Shuttle Targets    //
	//
	extern std::shared_ptr<classTarget> g_LowtonTarget_1;
	extern std::shared_ptr<classTarget> g_LowtonTarget_2;
	extern std::shared_ptr<classTarget_Ecom> g_LowtonTarget_3;
	extern std::shared_ptr<classTarget_Ecom> g_LowtonTarget_4;
	extern std::shared_ptr<classTarget_ESL_Script> g_LowtonTarget_5;
	extern std::shared_ptr<classTarget_ESL_Script> g_LowtonTarget_6;
	extern std::shared_ptr<classTarget_Generation_Script> g_LowtonTarget_7;
	extern std::shared_ptr<classTarget_Generation_Script> g_LowtonTarget_8;
	extern std::shared_ptr<classTarget_JScript> g_LowtonTarget_9;
	extern std::shared_ptr<classTarget_JScript> g_LowtonTarget_10;

	extern bool g_currentLaunch;
	extern int g_currentLaunchType;
	extern std::string g_currentLaunchPrefix;
	extern std::string g_currentLaunchTypeName;

	extern std::string g_ComputeText;
	extern std::string g_ComputeText_Lowton;
	extern int g_ComputeText_PrintMode;
	extern int g_ComputeText_PrintMode_Lowton;

	extern float ag_Get_current_Target_Mark(int f_Type);

	extern bool g_Result;

	  //////////////////////////////////////////////
	 // For multiple miners add vector indexes
	//
	extern std::shared_ptr<classLMap> g_classLMap;
	extern std::shared_ptr<classCollection> g_Lowton_Collection;
	extern std::vector<int> g_ElementDivisor;
	extern std::vector<float> g_ElementDivisorFloat;
	extern int g_CountLM;
	extern std::shared_ptr<Qcom> g_ShuttleCom;
};