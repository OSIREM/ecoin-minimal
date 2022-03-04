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

using namespace ecoin;

namespace ecoin
{

void classElement::acGen_fromBicycle(std::shared_ptr<CubeBicycle> f_Bicycle)
{
	for(int f_Helly = 0; f_Helly < f_Bicycle->vec_Vertex.size(); f_Helly++)
		{
		vec_Vertex.push_back(BiVector(f_Bicycle->vec_Vertex[f_Helly]->m_X, f_Bicycle->vec_Vertex[f_Helly]->m_Y, f_Bicycle->vec_Vertex[f_Helly]->m_Z));
		}

	for(int f_Helly = 0; f_Helly < f_Bicycle->vec_Color.size(); f_Helly++)
		{
		vec_Color.push_back(BiVector(f_Bicycle->vec_Color[f_Helly]->m_X, f_Bicycle->vec_Color[f_Helly]->m_Y, f_Bicycle->vec_Color[f_Helly]->m_Z));
		}

	while(vec_Color.size() < 8)
		{
		vec_Color.push_back(vec_Color[0]);
		}

	m_aabb = new aabb();
	m_aabb->empty();

	for(unsigned int f_CountVertex = 0; f_CountVertex < vec_Vertex.size(); f_CountVertex++)
		{
		*(m_aabb) += vec_Vertex[f_CountVertex];
		}

	m_Center = m_aabb->center();
	m_Volume = m_aabb->volume();
}

void classElement::acStructuredAnalysis(void)
{
	classCorner f_Corner;

	f_Corner.acSpecify(vec_Vertex[0], vec_Vertex[1], vec_Vertex[4], vec_Vertex[2]);
	m_Result.m_vec_Corner.push_back(f_Corner);

	f_Corner.acSpecify(vec_Vertex[1], vec_Vertex[0], vec_Vertex[5], vec_Vertex[3]);
	m_Result.m_vec_Corner.push_back(f_Corner);

	f_Corner.acSpecify(vec_Vertex[2], vec_Vertex[3], vec_Vertex[6], vec_Vertex[0]);
	m_Result.m_vec_Corner.push_back(f_Corner);

	f_Corner.acSpecify(vec_Vertex[3], vec_Vertex[2], vec_Vertex[7], vec_Vertex[1]);
	m_Result.m_vec_Corner.push_back(f_Corner);

	f_Corner.acSpecify(vec_Vertex[4], vec_Vertex[5], vec_Vertex[0], vec_Vertex[6]);
	m_Result.m_vec_Corner.push_back(f_Corner);

	f_Corner.acSpecify(vec_Vertex[5], vec_Vertex[4], vec_Vertex[1], vec_Vertex[7]);
	m_Result.m_vec_Corner.push_back(f_Corner);

	f_Corner.acSpecify(vec_Vertex[6], vec_Vertex[7], vec_Vertex[2], vec_Vertex[4]);
	m_Result.m_vec_Corner.push_back(f_Corner);

	f_Corner.acSpecify(vec_Vertex[7], vec_Vertex[6], vec_Vertex[3], vec_Vertex[5]);
	m_Result.m_vec_Corner.push_back(f_Corner);

	BiVector f_Vec;

	f_Vec = vec_Vertex[1] - vec_Vertex[0];
	m_Result.m_Dist01 = f_Vec.acLength();

	f_Vec = vec_Vertex[2] - vec_Vertex[3];
	m_Result.m_Dist23 = f_Vec.acLength();

	f_Vec = vec_Vertex[4] - vec_Vertex[5];
	m_Result.m_Dist45 = f_Vec.acLength();

	f_Vec = vec_Vertex[6] - vec_Vertex[7];
	m_Result.m_Dist67 = f_Vec.acLength();

	f_Vec = vec_Vertex[0] - vec_Vertex[2];
	m_Result.m_Dist02 = f_Vec.acLength();

	f_Vec = vec_Vertex[1] - vec_Vertex[3];
	m_Result.m_Dist13 = f_Vec.acLength();

	f_Vec = vec_Vertex[4] - vec_Vertex[6];
	m_Result.m_Dist46 = f_Vec.acLength();

	f_Vec = vec_Vertex[5] - vec_Vertex[7];
	m_Result.m_Dist57 = f_Vec.acLength();

	f_Vec = vec_Vertex[0] - vec_Vertex[4];
	m_Result.m_Dist04 = f_Vec.acLength();

	f_Vec = vec_Vertex[1] - vec_Vertex[5];
	m_Result.m_Dist15 = f_Vec.acLength();

	f_Vec = vec_Vertex[2] - vec_Vertex[6];
	m_Result.m_Dist26 = f_Vec.acLength();

	f_Vec = vec_Vertex[3] - vec_Vertex[7];
	m_Result.m_Dist37 = f_Vec.acLength();

	m_Result.m_Dist01234567 = (m_Result.m_Dist01 + m_Result.m_Dist23 + m_Result.m_Dist45 + m_Result.m_Dist67) / 4; //X
	m_Result.m_Dist02134657 = (m_Result.m_Dist02 + m_Result.m_Dist13 + m_Result.m_Dist46 + m_Result.m_Dist57) / 4; //Z
	m_Result.m_Dist04152637 = (m_Result.m_Dist04 + m_Result.m_Dist15 + m_Result.m_Dist26 + m_Result.m_Dist37) / 4; //Y

	m_Result.m_SurfToLegRatioX = ((m_Result.m_Dist01234567 - m_Result.m_Dist02134657) + (m_Result.m_Dist01234567 - m_Result.m_Dist04152637));
	m_Result.m_SurfToLegRatioZ = ((m_Result.m_Dist02134657 - m_Result.m_Dist01234567) + (m_Result.m_Dist02134657 - m_Result.m_Dist04152637));
	m_Result.m_SurfToLegRatioY = ((m_Result.m_Dist04152637 - m_Result.m_Dist02134657) + (m_Result.m_Dist04152637 - m_Result.m_Dist01234567));

	if((m_Result.m_SurfToLegRatioX > m_Result.m_SurfToLegRatioY) && (m_Result.m_SurfToLegRatioX > m_Result.m_SurfToLegRatioZ))
		{
		if((m_Result.m_SurfToLegRatioY < m_Result.m_SurfToLegRatioX) && (m_Result.m_SurfToLegRatioY < m_Result.m_SurfToLegRatioZ))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioY / m_Result.m_SurfToLegRatioX;
			}
		else if((m_Result.m_SurfToLegRatioZ < m_Result.m_SurfToLegRatioX) && (m_Result.m_SurfToLegRatioZ < m_Result.m_SurfToLegRatioY))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioZ / m_Result.m_SurfToLegRatioX;
			}
		}
	else if((m_Result.m_SurfToLegRatioY > m_Result.m_SurfToLegRatioX) && (m_Result.m_SurfToLegRatioY > m_Result.m_SurfToLegRatioZ))
		{
		if((m_Result.m_SurfToLegRatioX < m_Result.m_SurfToLegRatioY) && (m_Result.m_SurfToLegRatioX < m_Result.m_SurfToLegRatioZ))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioX / m_Result.m_SurfToLegRatioY;
			}
		else if((m_Result.m_SurfToLegRatioZ < m_Result.m_SurfToLegRatioX) && (m_Result.m_SurfToLegRatioZ < m_Result.m_SurfToLegRatioY))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioZ / m_Result.m_SurfToLegRatioY;
			}
		}
	else if((m_Result.m_SurfToLegRatioZ > m_Result.m_SurfToLegRatioY) && (m_Result.m_SurfToLegRatioZ > m_Result.m_SurfToLegRatioX))
		{
		if((m_Result.m_SurfToLegRatioX < m_Result.m_SurfToLegRatioY) && (m_Result.m_SurfToLegRatioX < m_Result.m_SurfToLegRatioZ))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioX / m_Result.m_SurfToLegRatioZ;
			}
		else if((m_Result.m_SurfToLegRatioY < m_Result.m_SurfToLegRatioX) && (m_Result.m_SurfToLegRatioY < m_Result.m_SurfToLegRatioZ))
			{
			m_Result.m_SurfToLegRatio = m_Result.m_SurfToLegRatioY / m_Result.m_SurfToLegRatioZ;
			}
		}

	m_Result.m_LevelParent = -1;
	m_Result.m_Parent = nullptr;
}

float classElement::acCompare(shared_ptr<classElement> f_Element, float f_QualityRank, bool f_testVolumes)
{
	float f_Mark = 0;

	if(m_vec_Element.size() < f_Element->m_vec_Element.size())
		{
		f_Mark += 37.8f;
		}
	else
		{
		if(f_testVolumes)
			{
			for(int f_Count = 0; f_Count < m_vec_Element.size(); f_Count++)
				{
				shared_ptr<classElement> f_TestElement = m_vec_Element[f_Count];

				if(f_Count < f_Element->m_vec_Element.size())
					{
					shared_ptr<classElement> f_sizeTestElement = f_Element->m_vec_Element[f_Count];

					float f_Float = (f_TestElement->m_Volume - f_sizeTestElement->m_Volume) * f_QualityRank;

#if 1
					if(f_Float >= 0)
						{
						f_Mark += f_Float;
						}
					else
						{
						f_Mark -= f_Float;
						}
#else
					f_Mark += f_Float;
#endif
					}
				}
			}
		}

	if(m_vec_Surface.size() < f_Element->m_vec_Surface.size())
		{
		f_Mark += 14.8f;
		}

	if(m_vec_Leg.size() < f_Element->m_vec_Leg.size())
		{
		f_Mark += 8.58f;
		}

	return f_Mark;
}

void classElementScript::acGen_fromElement(shared_ptr<classElement> f_Element, int f_ScriptLanguageScheme)
{
	g_SchemaTop = 0;
	g_SchemaRef[0].m_X = 0.120f;
	g_SchemaRef[0].m_Y = 0.70f;
	g_SchemaRef[0].m_Z = 0.95f;
	g_SchemaRef[1].m_X = 0.120f;
	g_SchemaRef[1].m_Y = 0.70f;
	g_SchemaRef[1].m_Z = 0.95f;
	g_SchemaRef[2].m_X = 0.120f;
	g_SchemaRef[2].m_Y = 0.70f;
	g_SchemaRef[2].m_Z = 0.95f;
	g_SchemaSize = 3;

	int f_WordCount = ag_takeMeasurementINTV0(f_Element, 1, 5, 1);

	std::vector<int> f_ProgOpen;

	for(int f_jet = 0; f_jet < f_WordCount; f_jet++)
		{
		int f_ComponentType = ag_takeMeasurementINTV0(f_Element, 1, 2);
		int f_BitCount = ag_takeMeasurementINTV0(f_Element, 1, 20, 2);

		std::shared_ptr<classComponent> f_Component = std::make_shared<classComponent>(f_ComponentType);
		f_Component->m_Name = ag_NameStamp0(ag_takeMeasurement0(f_Element), f_ComponentType, f_BitCount);

		for(int f_XYZ = 0; f_XYZ < f_BitCount; f_XYZ++)
			{
			if(f_XYZ == 0)
				{
				switch(f_ComponentType)
					{
					case COMPONENT_TYPE_VARINSTA:
						{
						int f_VariableType = ag_takeMeasurementINTV0(f_Element, 1, 1);
						int f_VariableState = ag_takeMeasurementINTV0(f_Element, 1, 2, 3);

						switch(f_VariableType)
							{
							case VARIABLE_TYPE_INT:
								{
	#pragma message("add a few more states, special or otherwise")
								if(f_VariableState == VARIABLE_STATE_NORMAL)
									{
									f_Component->m_vec_String.push_back("int ");
									}
								else
									{
									f_Component->m_vec_String.push_back("int* ");
									}
								} break;	
							}
						} break;

					case COMPONENT_TYPE_FUNCTIONCALL:
						{
						f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
						f_Component->m_vec_String.push_back("[");
						f_ProgOpen.push_back(3);
						} break;
					}

				if(f_BitCount == 1) //1
					{
					f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
					}
				else
					{
					f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
					f_Component->m_vec_String.push_back(" = ");
					}
				}
			else
				{
				if(f_BitCount == COMPONENT_CNT_BASE) //2
					{
					f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
					}
				else
					{
					f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));

					int f_AddType = ag_takeMeasurementINTV0(f_Element, 1, 3, 2);
							
					switch(f_AddType)
						{
						case COMPONENT_ELEMENT_TYPE_VARIABLE:
							{
							f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
							} break;

						case COMPONENT_ELEMENT_TYPE_FUNCTION:
							{
							f_Component->m_vec_String.push_back(ag_takeMeasurement0(f_Element));
							f_Component->m_vec_String.push_back("[");
							f_ProgOpen.push_back(3);
							} break;

						case COMPONENT_ELEMENT_TYPE_PROG:
							{
							int f_ProgType = ag_takeMeasurementINTV0(f_Element, 1, 3);

							switch(f_ProgType)
								{
								case PROG_TYPE_OPERATOR:
									{
									int f_OperatorType = ag_takeMeasurementINTV0(f_Element, 1, 1);

									switch(f_OperatorType)
										{
										case OPERATOR_TYPE_PLUS:
											{
											f_Component->m_vec_String.push_back(" + ");
											} break;
										}
									} break;
								case PROG_TYPE_BKT:
									{
									f_ProgOpen.push_back(1);
									f_Component->m_vec_String.push_back("[");
									} break;
								case PROG_TYPE_PAREN:
									{
									f_ProgOpen.push_back(2);
									f_Component->m_vec_String.push_back(" {");
									} break;
								}
							} break;
						}
					}

				if(f_ProgOpen.size() >= 1)
					{
					if((f_ProgOpen[f_ProgOpen.size() - 1] == 1) && (f_Component->m_vec_String[f_Component->m_vec_String.size() - 1].compare("[") != 0))
						{
						f_Component->m_vec_String.push_back("]");
						f_ProgOpen.pop_back();
						}

					if((f_ProgOpen[f_ProgOpen.size() - 1] == 2) && (f_Component->m_vec_String[f_Component->m_vec_String.size() - 1].compare("{") != 0))
						{
						f_Component->m_vec_String.push_back("}");
						f_ProgOpen.pop_back();
						}
					}
				}
			}

		 ////////
		//Post process events
		f_Component->m_vec_String.push_back(";");

		f_Component->m_String.clear();
		for(int f_Comb = 0; f_Comb < f_Component->m_vec_String.size(); f_Comb++)
			{
			f_Component->m_String += f_Component->m_vec_String[f_Comb];
			}

#if 0
		m_vec_Code.push_back(new Code(m_String));
		m_CodeLine = new CodeLine(m_vec_Code);

		std::shared_ptr<CodeLine> f_CodeLine = NULL;
		int f_Chk = 0;

		f_CodeLine = new CodeLine(f_Line, m_Chk, m_System);

		m_vec_CodeLine.push_back(f_CodeLine);
#endif

		m_vec_Component.push_back(f_Component);
		}

	m_Data.clear();

	for(int f_RS = 0; f_RS < m_vec_Component.size(); f_RS++)
		{
		m_Data += m_vec_Component[f_RS]->m_String;
		}

#if 0
	//g_hasha.init(); //reset hasher state
	//g_hasha.process(m_Data.begin(), m_Data.end());
	//g_hasha.finish();
	picosha2::get_hash_hex_string(//g_hasha, m_Hash);
#endif

	m_Hash = "00000000000000000000000000000000";
}

#if 0
std::string ag_ConstructPost(void *f_Data, int startTap)
{
	unsigned char *f_DataStream = dynamic_cast<unsigned char*>(f_Data);

	if(!f_DataStream)
		{
		return 0;
		}

	for(int f_tap = startTap; f_tap < startTap + 5; f_tap++)
		{
		f_AnswerValue[0] = f_DataStream[f_Tap];
		}

	std::string f_Result;

	switch(f_Value)
		{
		case f_AnswerValue[0]:
			{
			f_Result = ag_PostAnswer(0);
			} break;

		case f_AnswerValue[1]:
			{
			f_Result = ag_PostAnswer(1);
			} break;

		case f_AnswerValue[2]:
			{
			f_Result = ag_PostAnswer(2);
			} break;

		case f_AnswerValue[3]:
			{
			f_Result = ag_PostAnswer(3);
			} break;

		case f_AnswerValue[4]:
			{
			f_Result = ag_PostAnswer(4);
			} break;
		}

	return f_Result;
}
#endif

#if 0
bool ag_genfromVar(int f_Vartype, float lower, float upper)
{
	classVar *f_Var = classVar(f_Vartype, lower, upper);

	for(int f_X = 0; f_X < 5; f_X++)
		{
		for(int f_Y = 0; f_Y < 5; f_X++)
			{
			for(int f_Z = 0; f_Z < 5; f_X++)
				{
				f_Var += ag_takeMeasurement0()
				}
			}
		}

	if(f_Var->ac_Result() > f_Var->m_lower &&)
		f_Var->ac_Result() <= f_Var->m_upper)
		{
		return true;
		}
	else
		{
		return false;
		}
}
#endif

std::string ag_takeMeasurement0(shared_ptr<classElement> f_Vertex)
{
#if 1
	switch(g_SchemaTop)
		{
		case 0:
			{
			float f_Float = 0.0f;
			float f_FloatMax = 0.0f;
			for(int f_helly = 0; f_helly < f_Vertex->vec_Vertex.size(); f_helly++)
				{
				g_SchemaRef[g_SchemaTop].m_X = g_SchemaRef[g_SchemaTop].m_X + (f_Vertex->vec_Vertex[f_helly].m_X * 0.3);
				g_SchemaRef[g_SchemaTop].m_Y = g_SchemaRef[g_SchemaTop].m_Y + (f_Vertex->vec_Vertex[f_helly].m_Y * 0.1);
				g_SchemaRef[g_SchemaTop].m_Z = g_SchemaRef[g_SchemaTop].m_Z + (f_Vertex->vec_Vertex[f_helly].m_Z * 0.3);

				f_Float += (g_SchemaRef[g_SchemaTop] - f_Vertex->vec_Vertex[f_helly]).acDot();

				f_FloatMax += 3.0f;
				}
			return reinterpret_cast<char*>(&f_Float);
			}break;

		case 1:
			{
			float f_Float = 0.0f;
			for(int f_helly = 0; f_helly < f_Vertex->m_vec_Element.size(); f_helly++)
				{
				g_SchemaRef[g_SchemaTop].m_X = g_SchemaRef[g_SchemaTop].m_X + (f_Vertex->vec_Vertex[f_helly].m_X * 0.3);
				g_SchemaRef[g_SchemaTop].m_Y = g_SchemaRef[g_SchemaTop].m_Y + (f_Vertex->vec_Vertex[f_helly].m_Y * 0.1);
				g_SchemaRef[g_SchemaTop].m_Z = g_SchemaRef[g_SchemaTop].m_Z + (f_Vertex->vec_Vertex[f_helly].m_Z * 0.3);

				f_Float += (g_SchemaRef[g_SchemaTop] - f_Vertex->m_vec_Element[f_helly]->vec_Vertex[ag_takeMeasurementINTV0(f_Vertex->m_vec_Element[f_helly], 0, f_Vertex->m_vec_Element[f_helly]->vec_Vertex.size(), 0)]).acDot();
				}
			return reinterpret_cast<char*>(&f_Float);
			}break;
		}
#endif

	return "abeebc";
}

//element level specify schema
int ag_takeMeasurementINTV0(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth) // scale resolution 1-3
{
#if 1
	int m_Depth = f_Depth + 1;
	m_Depth--;
	if(m_Depth >= 1)
		{
		switch(g_SchemaTop)
			{
			case 0:		//All distance test
				{
				float f_Float = 0;
				for(int f_helly = 0; f_helly < f_Vertex->vec_Vertex.size(); f_helly++)
					{
					g_SchemaRef[g_SchemaTop].m_X = g_SchemaRef[ag_takeMeasurementINTV0(f_Vertex, 0, g_SchemaSize, 3, m_Depth)].m_X + (f_Vertex->vec_Vertex[f_helly].m_X * 0.3);
					g_SchemaRef[g_SchemaTop].m_Y = g_SchemaRef[ag_takeMeasurementINTV0(f_Vertex, 0, g_SchemaSize, 3, m_Depth)].m_Y + (f_Vertex->vec_Vertex[f_helly].m_Y * 0.1);
					g_SchemaRef[g_SchemaTop].m_Z = g_SchemaRef[ag_takeMeasurementINTV0(f_Vertex, 0, g_SchemaSize, 3, m_Depth)].m_Z + (f_Vertex->vec_Vertex[f_helly].m_Z * 0.3);

					BiVector f_Vec = g_SchemaRef[g_SchemaTop] - f_Vertex->vec_Vertex[f_helly];
					f_Float += f_Vec.acDot();
					}

				float f_Theta = sin(f_Float);
				int f_Int = (f_Theta * f_EndRange) + f_StartRange;
				f_Int = f_Int - (f_WeightRangetoStart / 2);
				return f_Int;
				}break;

			case 1:
				{
				float f_Int = 0;
				float f_IntMax = 10 * 150 * 4;
				for(int f_helly = 0; f_helly < f_Vertex->m_vec_Element.size(); f_helly++)
					{
					for(int f_jet = 0; f_jet < f_Vertex->m_vec_Element.size(); f_jet++)
						{
						g_SchemaRef[g_SchemaTop].m_X = g_SchemaRef[ag_takeMeasurementINTV0(f_Vertex, 0, g_SchemaSize, 3, m_Depth)].m_X + (f_Vertex->vec_Vertex[f_helly].m_X * 0.3);
						g_SchemaRef[g_SchemaTop].m_Y = g_SchemaRef[ag_takeMeasurementINTV0(f_Vertex, 0, g_SchemaSize, 3, m_Depth)].m_Y + (f_Vertex->vec_Vertex[f_helly].m_Y * 0.1);
						g_SchemaRef[g_SchemaTop].m_Z = g_SchemaRef[ag_takeMeasurementINTV0(f_Vertex, 0, g_SchemaSize, 3, m_Depth)].m_Z + (f_Vertex->vec_Vertex[f_helly].m_Z * 0.3);

						f_Int += f_Vertex->m_vec_Element[f_helly]->m_Volume * f_helly;
						}
					}
				int f_Result = (((f_Int / f_IntMax) / (f_WeightRangetoStart + 1)) * f_EndRange) + f_StartRange;
				return f_Result;
				}break;

			case 2:
				{
				float f_Int = 0;
				float f_IntMax = 10 * 150 * 4;
				for(int f_helly = 0; f_helly < f_Vertex->m_vec_Element.size(); f_helly++)
					{
					for(int f_jet = 0; f_jet < f_Vertex->m_vec_Element.size(); f_jet++)
						{
						g_SchemaRef[g_SchemaTop].m_X = g_SchemaRef[ag_takeMeasurementINTV0(f_Vertex, 0, g_SchemaSize, 3, m_Depth)].m_X + (f_Vertex->vec_Vertex[f_helly].m_X * 0.3);
						g_SchemaRef[g_SchemaTop].m_Y = g_SchemaRef[ag_takeMeasurementINTV0(f_Vertex, 0, g_SchemaSize, 3, m_Depth)].m_Y + (f_Vertex->vec_Vertex[f_helly].m_Y * 0.1);
						g_SchemaRef[g_SchemaTop].m_Z = g_SchemaRef[ag_takeMeasurementINTV0(f_Vertex, 0, g_SchemaSize, 3, m_Depth)].m_Z + (f_Vertex->vec_Vertex[f_helly].m_Z * 0.3);

						f_Int += f_Vertex->m_vec_Element[f_helly]->m_Volume * f_helly;
						}
					}
				int f_Result = (((f_Int / f_IntMax) / (f_WeightRangetoStart + 1)) * f_EndRange) + f_StartRange;
				return f_Result;
				}break;
			}
		}
#endif

	return (rand() % f_EndRange) + f_StartRange;
}

std::string ag_NameStamp0(std::string f_Measurement, int f_Type, int f_BitCount)
{
	std::string f_Result = "";
	g_ComponentStamp++;

	switch(f_Type)
		{
		case COMPONENT_TYPE_VARINSTA:
			{
			char f_Char[150];
			FillChar(f_Char, 150);
			sprintf(f_Char, "Variable%i-%i", g_ComponentStamp, f_BitCount);
			f_Result += f_Char;
			} break;
		case COMPONENT_TYPE_FUNCTIONCALL:
			{
			char f_Char[150];
			FillChar(f_Char, 150);
			sprintf(f_Char, "FunctionCall%i-%i", g_ComponentStamp, f_BitCount);
			f_Result += f_Char;
			} break;
		}

	return f_Result;
}

std::string ag_GenerateValue0(std::string f_Measurement)
{
#pragma message("generate several methods and results for differing value types")
	char* f_ValueStream = (char*)f_Measurement.c_str();

	int *f_Int = (int*)reinterpret_cast<int*>(f_ValueStream);

	char f_Char[150];
	FillChar(f_Char, 150);
	sprintf(f_Char, "%i", *(f_Int));

	std::string f_Result = f_Char;

	return f_Result;
}

};