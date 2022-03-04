//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

int g_Viewing = 1;
bool g_KeepShare = false;
int g_PEERCNT = 0;
int g_SHARECNT = 0;
int g_PerShareCount = 0;
bool g_RenderHesh = false;
bool g_LowtonOn = false;
picosha2::hash256_one_by_one g_hasha;
time_t  g_Currtime;
time_t  g_Storetime;
time_t  g_CurrtimeSEC;
time_t  g_StoretimeSEC;
time_t  g_CurrentTime;
time_t  g_StorageTime;
int g_StorageCounter;
int g_timeDiff = 0;
int g_timeCnt = 0;
int g_timeCntLast = 0;
int g_timeActual = 0;
time_t g_currenttime;
time_t g_storagetime;
float g_LowtonMark = FLT_MAX;
int g_OCSCP_LowtonMark = 0;
std::shared_ptr<Cube::CubeHESH> g_Lowton;
std::shared_ptr<Cube::CubeHASH_originstring> g_LowtonHash;
std::vector<int> g_vec_Bookmark;
bool g_GameOpen = false;
bool g_Editor_ON = false;
int g_Found_Share = 0;
int g_Found_Block = 0;
int g_Found_Msg = 0;
std::string g_Found_Text = "";
int g_CurrentShareOffset = 0;
int g_PEER = 0;
int g_CurrentShareOffsetMAX = 1;
int g_PEERMAX = 1;
int g_espo_ShareOffset = 0;
int g_espo_Peer = 0;
float g_espo_Score = 0;
float g_espo_Amount = 0.0f;
float g_espo_ECN_Amount = 0.0f;
std::string g_espo_Owner = "";
std::string g_espo_Date = "";
int g_CurrentComID = 0;
float g_CurrentSharePrice = 0.0f;
int g_CurrentShareID = 0;
bool g_Once = false;
int g_EventOffset = 0;
int g_codeIndex = 0;
std::string g_codeStorage[4];
std::vector<std::vector<std::string>> g_CopyStack;
int g_CopyStackPageN = 0;
float g_BoardPushHeightAdjust = 2.0f;
float g_ComPositionToPoint2fFactor = 220.0f;
float g_ComICOPositionToComPositionX = 106.0f / 40.0f; // / 8.0f
float g_ComICOPositionToComPositionY = 106.0f / 25.0f; // / 8.0f
float g_CarriageReturnX = 0.0f;
bool g_TXD_Scan = false;
bool g_ConnectedECD = false;
float g_RADX = 0.0f;
float g_RADY = 0.0f;
float g_RADZ = 0.0f;
int g_CoolDown = 0;
float g_CoolBoost = false;
int g_OCSCP_ThreadCount = 0;
int g_Divine_ThreadCount = 0;
int g_GUItimer = 4;
int g_SaveComplete_ThreadCount = 8;
int g_Diviner_ThreadCount = 6;
int g_Compressing = 0;
bool g_BoughtCom = false;
bool g_MyOwnCom = false;

#ifdef ECOIN_OSI_MEMORY
std::map<std::string, std::shared_ptr<ecom_base>> g_vec_ecomRefBase;
std::map<std::string, int> g_vec_ecomRefCount;

std::vector<std::vector<std::string>> g_vec_Path;
std::vector<std::vector<std::string>> g_vec_PathLabel;
#endif

void ag_Click(std::string f_ButtonName)
{
	if(g_WalletOpen == true)
		{
		std::vector<std::shared_ptr<BiPacket>> f_Packet = g_QcomManager->acSearch_PacketbyName(f_ButtonName);

		for(int f_XY = 0; f_XY < f_Packet.size(); f_XY++)
			{
			if(f_Packet[f_XY]->m_Name.length() > 0)
				{
				std::shared_ptr<Qcom> f_com = f_Packet[f_XY]->m_Operator_Com;

				f_com->ac_Execute();
				}
			}
		}
}

float ag_Unsign(float f_Input)
{
	float f_Result = 0;

	if(f_Input < 0)
		{
		f_Result = f_Input * -1;
		}
	else
		{
		f_Result = f_Input;
		}

	return f_Result;
}

template<typename f_A>
f_A ag_CheckBoth(f_A f_Input)
{
	std::string f_TypeName = typeid(f_A).name();

	if(f_TypeName.compare(typeid(float).name()) == 0)
		{
		char f_XY_char = ag_ClearChar(512);
		sprintf(f_XY_char, "%f", f_Input);
		std::string f_Result = f_XY_char;
		delete f_XY_char;

		return ag_CheckFloat(f_Result);
		}
	else if(f_TypeName.compare(typeid(int).name()) == 0)
		{
		char f_XY_char = ag_ClearChar(512);
		sprintf(f_XY_char, "%i", f_Input);
		std::string f_Result = f_XY_char;
		delete f_XY_char;

		return ag_CheckInteger(f_Result);
		}
	else if(f_TypeName.compare(typeid(std::string).name()) == 0)
		{
		return f_Input;
		}

#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

	return f_Input;
}

int ag_CheckInteger(std::string f_InputString)
{
	if(f_InputString.length() <= 0)
		{
		return -1;
		}

	for(int f_Jet = 0; f_Jet < f_InputString.length(); f_Jet++)
		{
		char f_Char = f_InputString.at(f_Jet);

		if(f_Char < '0')
			{
			if(f_Char != '-')
				{
				return -1;
				}
			}

		if(f_Char > '9')
			{
			if(f_Char != '-')
				{
				return -1;
				}
			}
		}

	return atoi(f_InputString.c_str());
}

float ag_CheckFloat(std::string f_InputString)
{
	if(f_InputString.length() <= 0)
		{
		return -1.0f;
		}

	for(int f_Jet = 0; f_Jet < f_InputString.length(); f_Jet++)
		{
		char f_Char = f_InputString.at(f_Jet);

		if(f_Char < '0')
			{
			if((f_Char != '-') && (f_Char != '.'))
				{
				return -1.0f;
				}
			}

		if(f_Char > '9')
			{
			if((f_Char != '-') && (f_Char != '.'))
				{
				return -1.0f;
				}
			}
		}

	return atof(f_InputString.c_str());
}

template<typename f_A>
void ag_FreshOn(std::vector<f_A>& f_AS, int f_IDX, f_A f_Resultance)
{
	if(f_IDX < f_AS.size())
		{
		f_AS[f_IDX] = f_Resultance;
		}
	else
		{
		while(f_IDX >= f_AS.size())
			{
			f_AS.push_back(f_Resultance);
			}
		}
}

template<typename f_B>
void ag_Freshanon(std::vector<f_B>& f_AS, int f_IDX, f_B f_Resultance)
{
	while(f_IDX >= f_AS.size())
		{
		f_AS.push_back(f_Resultance);
		}
}

template<typename f_C>
f_C ag_FreshOnly(std::vector<f_C>& f_AS, int f_IDX, f_C f_Resultance)
{
	if(f_IDX < f_AS.size())
		{
		f_AS[f_IDX] = f_Resultance;
		}
	else
		{
		while(f_IDX >= f_AS.size())
			{
			f_AS.push_back(f_Resultance);
			}
		}

	return f_Resultance;
}

template<typename f_D>
f_D ag_FreshAndOnly(std::vector<f_D>& f_AS, int f_IDX, f_D f_Resultance)
{
	f_D h_Sorda = 0;

	std::string f_StrTypeName = typeid(f_D).name();

	if(f_IDX < f_AS.size())
		{
		if(f_StrTypeName.compare(typeid(std::string).name()) == 0)
			{
			return f_AS.at(f_IDX);
			}
		else
			{
			f_D f_Hossa = f_AS.at(f_IDX);

			if(f_Hossa != 0)
				{
				h_Sorda = f_Hossa;

				return h_Sorda;
				}
			else
				{
				h_Sorda = f_Resultance;

				return h_Sorda;
				}
			}
		}
	else
		{
		while(f_IDX >= f_AS.size())
			{
			f_AS.push_back(f_Resultance);
			}

		h_Sorda = f_Resultance;

		if(f_IDX < f_AS.size())
			{
			if(f_StrTypeName.compare(typeid(std::string).name()) == 0)
				{
				return f_AS.at(f_IDX);
				}
			else
				{
				f_D f_Hossa = f_AS.at(f_IDX);

				if(f_Hossa != 0)
					{
					h_Sorda = f_Hossa;

					return h_Sorda;
					}
				else
					{
					h_Sorda = f_Resultance;

					return h_Sorda;
					}
				}
			}
		else
			{
			while(f_IDX >= f_AS.size())
				{
				f_AS.push_back(f_Resultance);
				}
			}

		h_Sorda = f_Resultance;

		if(f_StrTypeName.compare(typeid(std::string).name()) == 0)
			{
			return f_AS.at(f_IDX);
			}
		else
			{
			f_D f_Hossa = f_AS.at(f_IDX);

			if(f_Hossa != 0)
				{
				h_Sorda = f_Hossa;

				return h_Sorda;
				}
			else
				{
				h_Sorda = f_Resultance;

				return h_Sorda;
				}
			}
		}

	return h_Sorda;
}

void ag_PrepareChar(char* f_Char, int f_ArraySize)
{
	for(int f_Jet = 0; f_Jet < f_ArraySize; f_Jet++)
		{
		f_Char[f_Jet] = '\0';
		}
}

int StringToWString(std::wstring& ws, const std::string& s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}

void FillChar(char* f_Char, int f_Max)
{
	for(int f_Count = 0; f_Count < f_Max; f_Count++)
		{
		f_Char[f_Count] = '\0';
		}
}

char acFileReadChar(std::string f_Buffer, size_t f_Count)
{
	int c = 0;
	if(f_Count < f_Buffer.length())
		{
		c = f_Buffer.at(f_Count);

		if(c == EOF)
			{
			return '\0';
			}
		else
			{
			return (char)c;
			}
		}
	else
		{
		return '\0';
		}
}

int acBufreadValueInteger(const std::string& f_Buffer, uint* f_Chk)
{
	uint fv_Chk = *(f_Chk);

	std::string f_Samp = "";
	bool f_Scan = true;

	while(f_Scan == true)
		{
		char f_c = f_Buffer.at(fv_Chk);

		if(f_c != ' ')
			{
			f_Samp.push_back(f_c);
			}
		else
			{
			f_Scan = false;
			}

		fv_Chk++;

		if(fv_Chk >= f_Buffer.length())
			{
			f_Scan = false;
			}
		}

	*(f_Chk) = fv_Chk;

	return atoi(f_Samp.c_str());
}

float acBufreadValueFloat(const std::string& f_Buffer, uint* f_Chk)
{
	uint fv_Chk = *(f_Chk);

	std::string f_Samp = "";
	bool f_Scan = true;

	while (f_Scan == true)
		{
		char f_c = f_Buffer.at(fv_Chk);

		if (f_c != ' ')
			{
			f_Samp.push_back(f_c);
			}
		else
			{
			f_Scan = false;
			}

		fv_Chk++;

		if (fv_Chk >= f_Buffer.length())
			{
			f_Scan = false;
			}
		}

	*(f_Chk) = fv_Chk;

	return atof(f_Samp.c_str());
}

double acBufreadValueDouble(const std::string& f_Buffer, uint* f_Chk)
{
	uint fv_Chk = *(f_Chk);

	std::string f_Samp = "";
	bool f_Scan = true;

	while(f_Scan == true)
		{
		char f_c = f_Buffer.at(fv_Chk);

		if(f_c != ' ')
			{
			f_Samp.push_back(f_c);
			}
		else
			{
			f_Scan = false;
			}

		fv_Chk++;

		if(fv_Chk >= f_Buffer.length())
			{
			f_Scan = false;
			}
		}

	*(f_Chk) = fv_Chk;

	return atof(f_Samp.c_str());
}

void acBufwriteValueInt(std::string* f_Buffer, int f_Int)
{
	char f_Char[512];

	FillChar(f_Char, 512);

	sprintf_s(f_Char, "%i", f_Int);
	*(f_Buffer) = *(f_Buffer)+f_Char;
}

void acBufwriteValueFloat(std::string* f_Buffer, float f_Float)
{
	char f_Char[512];

	FillChar(f_Char, 512);

	sprintf_s(f_Char, "%f ", f_Float);
	*(f_Buffer) = *(f_Buffer) + f_Char;
}

std::string acBufreadValueString(const std::string& f_Buffer, uint* f_Chk)
{
	std::string f_Result;
	char* f_TestChar = new char[4];
	bool m_End = false;
	std::string f_PushString;
	bool f_Start = true;

	uint fv_Chk = *(f_Chk);

	FillChar(f_TestChar, 4);

	if(fv_Chk + 4 >= f_Buffer.length())
		{
		*(f_Chk) = f_Buffer.length();
		return std::string("Empty");
		}
	
	f_TestChar[3] = f_Buffer.at(fv_Chk);
	fv_Chk++;
	f_TestChar[2] = f_Buffer.at(fv_Chk);
	fv_Chk++;
	f_TestChar[1] = f_Buffer.at(fv_Chk);
	fv_Chk++;
	f_TestChar[0] = f_Buffer.at(fv_Chk);
	fv_Chk++;

	if (f_TestChar[3] == ':' &&
		f_TestChar[2] == ':' &&
		f_TestChar[1] == ':' &&
		f_TestChar[0] == ':')
		{
		m_End = true;
		}
	else
		{
		if(f_TestChar[3] != ' ')
			{
			f_PushString.clear();
			f_PushString.push_back(f_TestChar[3]);
			f_Result = f_Result + f_PushString;
			}
		}

	while(m_End == false)
		{
		f_TestChar[3] = f_TestChar[2];
		f_TestChar[2] = f_TestChar[1];
		f_TestChar[1] = f_TestChar[0];
		f_TestChar[0] = f_Buffer.at(fv_Chk);
		fv_Chk++;

		if(f_TestChar[0] == '\0')
			{
			f_Result.push_back(f_TestChar[3]);
			f_Result.push_back(f_TestChar[2]);
			f_Result.push_back(f_TestChar[1]);
			m_End = true;
			}

		if((f_TestChar[3] == ':' &&
			f_TestChar[2] == ':' &&
			f_TestChar[1] == ':' &&
			f_TestChar[0] == ':'))
			{
			m_End = true;
			}

		if(fv_Chk >= f_Buffer.length())
			{
			m_End = true;
			}

		if(m_End == false)
			{
			if(f_Start)
				{
				if(f_TestChar[0] != ' ')
					{
					f_Result.push_back(f_TestChar[3]);
					f_Start = false;
					}
				}
			else
				{
				f_Result.push_back(f_TestChar[3]);
				}
			}
		}

	*(f_Chk) = fv_Chk;

	delete[] f_TestChar;

	return f_Result;
}

void acBufwriteValueInteger(std::string* f_Buffer, int f_Int)
{
	char f_Char[512];

	FillChar(f_Char, 512);

	sprintf_s(f_Char, "%i ", f_Int);

	*(f_Buffer) = *(f_Buffer) + f_Char;
}

void acBufwriteValueDouble(std::string* f_Buffer, double f_Double)
{
	char f_Char[512];

	FillChar(f_Char, 512);

	sprintf_s(f_Char, "%.15f ", f_Double);
	*(f_Buffer) = *(f_Buffer)+f_Char;
}

std::string acBufreadCodeString(std::string f_Buffer, unsigned int f_CHK)
{
	std::string f_Result;
	char* f_TestChar = ag_ClearChar(4);
	bool m_End = false;
	std::string f_Pushstring;
	bool f_Start = true;
	unsigned int f_Chk = f_CHK;

	FillChar(f_TestChar, 4);
	
	f_TestChar[3] = acFileReadChar(f_Buffer, f_Chk);
	f_Chk++;
	f_TestChar[2] = acFileReadChar(f_Buffer, f_Chk);
	f_Chk++;
	f_TestChar[1] = acFileReadChar(f_Buffer, f_Chk);
	f_Chk++;
	f_TestChar[0] = acFileReadChar(f_Buffer, f_Chk);
	f_Chk++;

	if(f_TestChar[0] == '\0')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[0] == '\n')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '*' &&
		f_TestChar[0] == '*')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '%' &&
		f_TestChar[0] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '%' &&
		f_TestChar[0] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '#' &&
		f_TestChar[0] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '#' &&
		f_TestChar[0] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '&' &&
		f_TestChar[0] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '&' &&
		f_TestChar[0] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '&' &&
		f_TestChar[0] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '%' &&
		f_TestChar[0] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '&' &&
		f_TestChar[0] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '#' &&
		f_TestChar[0] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '&' &&
		f_TestChar[0] == '*')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '\0')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '\n')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '*' &&
		f_TestChar[1] == '*')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '%' &&
		f_TestChar[1] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '%' &&
		f_TestChar[1] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '#' &&
		f_TestChar[1] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '#' &&
		f_TestChar[1] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '&' &&
		f_TestChar[1] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '&' &&
		f_TestChar[1] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '&' &&
		f_TestChar[1] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '%' &&
		f_TestChar[1] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '&' &&
		f_TestChar[1] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '#' &&
		f_TestChar[1] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '&' &&
		f_TestChar[1] == '*')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '^' &&
		f_TestChar[0] == '^')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '$' &&
		f_TestChar[0] == '$')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	 ///////
	// End
	if(f_TestChar[3] == '#' &&
		f_TestChar[2] == '#' &&
		f_TestChar[1] == '#' &&
		f_TestChar[0] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(!m_End)
		{
		if (f_TestChar[3] == '/' &&
			f_TestChar[2] == '/' &&
			f_TestChar[1] == '/' &&
			f_TestChar[0] == '/')
			{
			f_Pushstring.push_back(f_TestChar[3]);
			f_Pushstring.push_back(f_TestChar[2]);
			f_Pushstring.push_back(f_TestChar[1]);
			f_Pushstring.push_back(f_TestChar[0]);
			f_Result = f_Result + f_Pushstring;
			m_End = true;
			}
		else
			{
			if(f_TestChar[3] != ' ')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Result = f_Result + f_Pushstring;
				}
			}

		while(!m_End)
			{
			f_TestChar[3] = f_TestChar[2];
			f_TestChar[2] = f_TestChar[1];
			f_TestChar[1] = f_TestChar[0];
			f_TestChar[0] = acFileReadChar(f_Buffer, f_Chk);
			f_Chk++;

			if(f_TestChar[0] == '\0')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[0] == '\n')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '*' &&
				f_TestChar[0] == '*')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '%' &&
				f_TestChar[0] == '%')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '%' &&
				f_TestChar[0] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '#' &&
				f_TestChar[0] == '%')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '^' &&
				f_TestChar[0] == '^')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '#' &&
				f_TestChar[0] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[3] == '#' &&
				f_TestChar[2] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[2] == '#' &&
				f_TestChar[1] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '#' &&
				f_TestChar[0] == '&')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '&' &&
				f_TestChar[0] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '&' &&
				f_TestChar[0] == '&')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '&' &&
				f_TestChar[0] == '%')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '%' &&
				f_TestChar[0] == '&')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '&' &&
				f_TestChar[0] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '#' &&
				f_TestChar[0] == '&')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[0] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '&' &&
				f_TestChar[0] == '*')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '$' &&
				f_TestChar[0] == '$')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[3] == '/' &&
				f_TestChar[2] == '/' &&
				f_TestChar[1] == '/' &&
				f_TestChar[0] == '/')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(!m_End)
				{
				if(f_Start)
					{
					if(f_TestChar[0] != ' ' &&
						f_TestChar[0] != '\n')
						{
						f_Pushstring.clear();
						f_Pushstring.push_back(f_TestChar[3]);
						f_Result = f_Result + f_Pushstring;
						f_Start = false;
						}
					}
				else
					{
					f_Pushstring.clear();
					f_Pushstring.push_back(f_TestChar[3]);
					f_Result = f_Result + f_Pushstring;
					}
				}
			}
		}

	delete f_TestChar;

	return f_Result;
}

winrt::hstring StrFromChar(char char_str[])
{
	std::string s_str = std::string(char_str);
	std::wstring wid_str = std::wstring(s_str.begin(), s_str.end());
	const wchar_t* w_char = wid_str.c_str();
	winrt::hstring p_string = winrt::hstring(w_char);
	return p_string;
}

winrt::hstring StrUsingStr(std::string f_string)
{
	std::wstring wid_str = std::wstring(f_string.begin(), f_string.end());
	const wchar_t* w_char = wid_str.c_str();
	winrt::hstring p_string = winrt::hstring(w_char);
	return p_string;
}

std::string ag_StrUsingFloat(float f_Float)
{
	char* f_Char = ag_ClearChar(64);

	sprintf(f_Char, "%f", f_Float);

	std::string f_String = f_Char;

	delete f_Char;

	return f_String;
}

// Convert from wstring into a string
std::string to_string(const std::wstring & wtxt)
{
	std::string str;
	str.resize(wtxt.size() + 1);

	size_t numConverted;
	errno_t err = wcstombs_s(&numConverted, (char *)str.data(), str.size(), wtxt.data(), wtxt.size());

	str.pop_back();
	return str;
}

std::string to_string(winrt::hstring pstring)
{
	std::wstring wStr(pstring.data());
	return to_string(wStr);
}

std::string to_string(wchar_t* wstring)
{
	std::wstring ws(wstring);

	//string str(ws.begin(), ws.end());

	return to_string(ws);
}

  //////////////////////////
 // OSIREM 
// Memory Improvements
std::vector<std::vector<std::string>> g_VectorObjectName;
std::vector<int> g_Proll;

std::shared_mutex g_MemLockMutex;

void ag_LockMutex(void)
{
	g_MemLockMutex.lock();
}

void ag_UnLockMutex(void)
{
	g_MemLockMutex.unlock();
}

  ////////////////////////////////////////////////
 // Osirem reflection ///////////////////////////
// ac_Push() Overloaded Specialized Deduction //
void ecom_base::ac_Push(bool& f_Var, std::string f_MemberVarName)
{
	m_Map_Bool.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(float& f_Var, std::string f_MemberVarName)
{
	m_Map_Float.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(double& f_Var, std::string f_MemberVarName)
{
	m_Map_Double.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(int& f_Var, std::string f_MemberVarName)
{
	m_Map_Int.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(unsigned int& f_Var, std::string f_MemberVarName)
{
	m_Map_UInt.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(char& f_Var, std::string f_MemberVarName)
{
	m_Map_Char.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::string& f_Var, std::string f_MemberVarName)
{
	m_Map_String.emplace(f_MemberVarName, &f_Var);
}
//./
//./vec
//./
void ecom_base::ac_Push(std::vector<bool>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_Bool.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<float>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_Float.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<double>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_Double.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<int>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_Int.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<unsigned int>& f_Var, std::string f_MemberVarName)
{
	if (m_veclayer1 == nullptr)
	{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
	}

	m_veclayer1->m_vec_Map_UInt.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<char>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_Char.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::string>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_String.emplace(f_MemberVarName, &f_Var);
}
//./
//./vec_vec
//./
void ecom_base::ac_Push(std::vector<std::vector<bool>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_Bool.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<float>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_Float.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<double>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_Double.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<int>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_Int.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<unsigned int>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_UInt.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<char>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_Char.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::string>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_String.emplace(f_MemberVarName, &f_Var);
}
//./
//./vec_vec_vec
//./
void ecom_base::ac_Push(std::vector<std::vector<std::vector<bool>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_Bool.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<float>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_Float.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<double>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_Double.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<int>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_Int.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<unsigned int>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_UInt.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<char>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_Char.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<std::string>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_String.emplace(f_MemberVarName, &f_Var);
}
//...

  ////////////////////////////////////////////////
 // Osirem [GLOBAL] reflection //////////////////
// ac_Push() Overloaded Specialized Deduction //
void ag_Push(bool& f_Var, std::string f_GlobalVarName)
{
	g_Map_Bool.emplace(f_GlobalVarName, &f_Var);
}

void ag_Push(float& f_Var, std::string f_GlobalVarName)
{
	g_Map_Float.emplace(f_GlobalVarName, &f_Var);
}

void ag_Push(double& f_Var, std::string f_GlobalVarName)
{
	g_Map_Double.emplace(f_GlobalVarName, &f_Var);
}

void ag_Push(int& f_Var, std::string f_GlobalVarName)
{
	g_Map_Int.emplace(f_GlobalVarName, &f_Var);
}

void ag_Push(unsigned int& f_Var, std::string f_GlobalVarName)
{
	g_Map_UInt.emplace(f_GlobalVarName, &f_Var);
}

void ag_Push(char& f_Var, std::string f_GlobalVarName)
{
	g_Map_Char.emplace(f_GlobalVarName, &f_Var);
}

void ag_Push(std::string& f_Var, std::string f_GlobalVarName)
{
	g_Map_String.emplace(f_GlobalVarName, &f_Var);
}

//...

bool* ecom_base::ac_GetBLT(std::string f_MemberVarName)
{
	return m_Map_Bool[f_MemberVarName];
}

float* ecom_base::ac_GetFLT(std::string f_MemberVarName)
{
	return m_Map_Float[f_MemberVarName];
}

int* ecom_base::ac_GetINT(std::string f_MemberVarName)
{
	return m_Map_Int[f_MemberVarName];
}

std::string* ecom_base::ac_GetSTR(std::string f_MemberVarName)
{
	return m_Map_String[f_MemberVarName];
}

void ecom_base::ac_PushFunction(std::string f_NameString, ecom_base::ControllerMethod_void f_FunctionRef)
{
	m_Map_Function.emplace(f_NameString, f_FunctionRef);
}

void ecom_base::ac_Invoke(std::string f_ref_FuncStr, std::shared_ptr<FunctionBeam> f_funcBeam)
{
	std::string f_ref_CurrentPath = "ecom_base::ac_Invoke";

	if(m_Status == 1)
		{
		if(m_Map_Function.size() > 0)
			{
			if(m_Map_Function.find(f_ref_FuncStr) != m_Map_Function.end())
				{
				//prep arguments lock in
				if(m_ActiveFuncBeam == nullptr)
					{
					if(f_funcBeam == nullptr)
						{
						ag_StatusLive(f_ref_CurrentPath, "m_ActiveFuncBeam");
						m_ActiveFuncBeam = std::make_shared<FunctionBeam>();
						}
					else
						{
						m_ActiveFuncBeam = f_funcBeam;
						}
					}

				//execute the function

				auto callableAB = std::mem_fn(m_Map_Function[f_ref_FuncStr]);

				std::function<void(void)> functionAB = std::bind(callableAB, this);

				functionAB();

				m_ActiveFuncBeam = nullptr;
				}
			}
		}
}

void ag_DeleteMapObject(std::string f_MapNamePath)
{
	if(g_vec_ecomRefBase.find(f_MapNamePath) != g_vec_ecomRefBase.end())
        {
        std::shared_ptr<ecom_base> f_base = g_vec_ecomRefBase[f_MapNamePath];

        if(f_base->m_PathName.length() > 1)
            {
            f_base->m_PathName.clear();
            f_base->m_Status = 3;

			g_vec_ecomRefBase[f_MapNamePath].reset();
            }
        }
}

std::string ag_Build_Path(PathPosition f_PP)
{
	std::string f_Path = "";
	std::string f_UsualPath = "";

	for(int f_XY = 0; f_XY < g_vec_Path[f_PP.m_X].size(); f_XY++)
		{
		std::string f_String = g_vec_Path[f_PP.m_X][f_XY];

		if(f_UsualPath.compare(f_String) != 0)
			{
			f_UsualPath = f_String;

			f_Path += f_String + g_ref_Path_Div;
			}
		}

	return f_Path;
}

PathPosition ag_Find_Path_Index(std::string f_MicroPath)
{
	if(g_vec_Path.size() > 0)
		{
		for(int f_X = g_vec_Path.size() - 1; f_X >= 0; f_X--)
			{
			for(int f_Y = g_vec_Path[f_X].size() - 1; f_Y >= 0; f_Y--)
				{
				if(g_vec_Path[f_X][f_Y].compare(f_MicroPath) == 0)
					{
					return PathPosition(f_X, f_Y);
					}
				}
			}
		}

	return PathPosition(-1, -1);
}

void ag_CentraliseCull(std::string f_CullStringPath)
{
	if(g_vec_Path.size() > 0)
		{
		for(int f_Y = g_vec_Path[g_PP.m_X].size() - 1; f_Y >= 0; f_Y--)
			{
			if(g_vec_Path[g_PP.m_X][f_Y].compare(f_CullStringPath) == 0)
				{
				g_vec_Path[g_PP.m_X].pop_back();
				g_vec_PathLabel[g_PP.m_X].pop_back();

				if(g_PP.m_Y >= g_vec_Path[g_PP.m_X].size())
					{
					g_PP.m_Y = g_vec_Path[g_PP.m_X].size() - 1;
					}
				}
			}
		}
}

PathPosition g_PP;

//access osirem reflection
void ag_StatusLive(std::string f_Path, std::string f_Label, bool f_Prepare, int f_VecIndex)
{
#ifdef ECOIN_OSI_MEMORY
#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_LockMutex();
#endif

	if(f_VecIndex >= g_VectorObjectName.size())
		{
		std::vector<std::string> f_vecstr;

		g_VectorObjectName.push_back(f_vecstr);
		}

	PathPosition f_PP = ag_Find_Path_Index(f_Path);

	//check for reset
	bool f_ChkReset = false;
	bool f_PathFound = false;
	bool f_Found = false;

	if((f_PP.m_X >= 0) && (f_PP.m_Y >= 0))
		{
		f_PathFound = true;
		}

	std::string f_SavePath = "";

	if(g_vec_Path.size() > 0)
		{
		if(f_Path.at(0) == ':')
			{
			if(f_Path.at(2) == ':')
				{
				if((f_Path.at(1) == 'E') || (f_Path.at(1) == 'F') || (f_Path.at(1) == 'G')) //win conditions reset
					{
					if(f_PathFound == true)
						{
						if(f_Path.compare(g_vec_Path[f_PP.m_X][f_PP.m_Y]) == 0)
							{
							std::string f_BuildPathA = ag_Build_Path(f_PP) + f_Label;

							f_Found = true;
							f_ChkReset = true;

							g_PP.m_X = f_PP.m_X;
							g_PP.m_Y = f_PP.m_Y;

							f_SavePath = f_BuildPathA;
							}
						else
							{
							throw; //should not be here
							}
						}
					else //win conditions - new reset vector beam
						{
						std::vector<std::string> f_vec_String;
						std::vector<std::string> f_vec_String_Label;

						f_vec_String.clear();
						f_vec_String_Label.clear();

						std::string f_BuildPathA = f_Path;

						f_vec_String.push_back(f_BuildPathA);

						std::string f_BuildPathB = f_Path + g_ref_Path_Div + f_Label;

						f_vec_String_Label.push_back(f_BuildPathB);

						g_vec_Path.push_back(f_vec_String);
						g_vec_PathLabel.push_back(f_vec_String_Label);

						g_PP.m_X = g_vec_Path.size() - 1;
						g_PP.m_Y = 0;

						f_SavePath = f_BuildPathB;

						f_ChkReset = true;
						}
					}
				}
			}

		if(f_ChkReset == false)
			{
			if((f_PathFound == true) && (f_Found == false))
				{
				if(f_Path.compare(g_vec_Path[f_PP.m_X][f_PP.m_Y]) == 0)
					{
					std::string f_BuildPathA = ag_Build_Path(f_PP) + f_Label;

					if((g_PP.m_X == f_PP.m_X) && (g_PP.m_Y != f_PP.m_Y))
						{
						int f_CurrentStackMax = g_vec_Path[f_PP.m_X].size();

						if(f_PP.m_Y < g_PP.m_Y)
							{
							int f_NewStackMax = f_CurrentStackMax - f_PP.m_Y;

							for(int f_Y = 0; f_Y < f_NewStackMax; f_Y++)
								{
								g_vec_Path[g_PP.m_X].pop_back();
								g_vec_PathLabel[g_PP.m_X].pop_back();
								}

							g_PP.m_Y = f_PP.m_Y;
							}
						else if(f_PP.m_Y == g_PP.m_Y)
							{
							//... win
							}
						else if(f_PP.m_Y > g_PP.m_Y)
							{
							g_PP.m_Y = f_PP.m_Y;
							}
						else
							{
							throw;
							}

						f_SavePath = f_BuildPathA;

						f_Found = true; //win conditions on same scope x differ y
						}
					else if(g_PP.m_Y != f_PP.m_Y)
						{
						int f_CurrentStackMax = g_vec_Path[g_PP.m_X].size();

						if(f_PP.m_Y < f_CurrentStackMax)
							{
							int f_NewStackMax = f_CurrentStackMax - f_PP.m_Y;

							for(int f_Y = 0; f_Y < f_NewStackMax; f_Y++)
								{
								g_vec_Path[g_PP.m_X].pop_back();
								g_vec_PathLabel[g_PP.m_X].pop_back();
								}

							g_PP.m_X = f_PP.m_X;
							g_PP.m_Y = f_PP.m_Y;
							}
						else if(f_PP.m_Y == g_PP.m_Y)
							{
							g_PP.m_X = f_PP.m_X;

							//... win
							}
						else if(f_PP.m_Y > g_PP.m_Y)
							{
							g_PP.m_X = f_PP.m_X;
							g_PP.m_Y = f_PP.m_Y;
							}
						else
							{
							throw;
							}

						f_SavePath = f_BuildPathA;

						f_Found = true; //win conditions on same scope x differ y
						}
					else
						{
						f_SavePath = f_BuildPathA; //win same path
						}
					}
				else
					{
					throw; //unlikely
					}
				}
			else
				{
				g_vec_Path[g_PP.m_X].push_back(f_Path);

				g_PP.m_Y = g_vec_Path[g_PP.m_X].size() - 1;

				std::string f_BuildPathA = ag_Build_Path(g_PP) + f_Label;
				
				g_vec_PathLabel[g_PP.m_X].push_back(f_BuildPathA);

				f_SavePath = f_BuildPathA;
				}
			}
		}
	else
		{
		g_PP.m_X = 0;
		g_PP.m_Y = 0;

		std::vector<std::string> f_vec_String;
		std::vector<std::string> f_vec_String_Label;

		f_vec_String.clear();
		f_vec_String.push_back(f_Path);

		std::string f_BuildPathB = f_Path + g_ref_Path_Div + f_Label;

		f_vec_String_Label.clear();
		f_vec_String_Label.push_back(f_BuildPathB);

		g_vec_Path.push_back(f_vec_String);
		g_vec_PathLabel.push_back(f_vec_String_Label);

		f_SavePath = f_BuildPathB;
		}

	g_VectorObjectName[f_VecIndex].push_back(f_SavePath);

	g_Proll.push_back(f_VecIndex);

#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_UnLockMutex();
#endif
#endif
}

void ag_StatusSync(std::string f_Path, std::string f_Label, bool f_Prepare, int f_VecIndex)
{
#ifdef ECOIN_OSI_MEMORY
#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_LockMutex();
#endif

	//Call ag_SyncState

#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_UnLockMutex();
#endif
#endif
}

std::string ag_AcceptObjectName(void)
{
#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_LockMutex();
#endif

    if(g_VectorObjectName.size() > 0 && (g_Proll.size() > 0))
        {
		int f_Int = g_Proll[g_Proll.size() - 1];

		if(g_VectorObjectName[f_Int].size() > 0)
			{
			std::string f_PulledObjectName = g_VectorObjectName[f_Int][0];

			for(int f_Jet = 0; f_Jet < g_VectorObjectName[f_Int].size() - 1; f_Jet++)
				{
				g_VectorObjectName[f_Int][f_Jet] = g_VectorObjectName[f_Int][f_Jet + 1];
				}

			g_VectorObjectName[f_Int].pop_back();

			g_Proll.pop_back();

#ifdef ECOIN_DBG_BREAK
#if 0
			if(g_VectorObjectName[f_Int].size() > 1)
				{
				__debugbreak();
				}
#endif
#endif //add debug message

#ifdef ECOIN_MEMORY_FULL_MUTEX
			ag_UnLockMutex();
#endif

			return f_PulledObjectName;
			}
        }

#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_UnLockMutex();
#endif

#ifdef ECOIN_DBG_BREAK
	__debugbreak();
#endif //add debug message

#ifdef ECOIN_DEBUG_BREAKS
	__debugbreak();
#endif //add debug message

    return std::string("noname");
}