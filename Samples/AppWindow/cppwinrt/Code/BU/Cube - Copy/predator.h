/*

qcom.h - ECOM Native Decl osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef PREDATOR_H
#define PREDATOR_H

#include "Include/Cube.h"

#include "Code/Work/Schedular.h"

#include "Code/Cube/qcom.h"

#include <vector>
#include <map>
#include <boost/any.hpp>

using namespace std;
using namespace Cube;
using namespace ecoin;

namespace Cube
{
#define PREDATOR_ACTIONIDX_ENTER 0
#define PREDATOR_ACTIONIDX_COPYED 1
#define PREDATOR_ACTIONIDX_DELETED 2
#define PREDATOR_ACTIONIDX_PASTED 3

class predatorAction;
class predatorPanelText;

class predatorIDX
{
	predatorIDX() { acClear(); };
	~predatorIDX() { acClear(); };

	void acClear(void)
		{
		m_Start = -1;
		m_Finish = -1;
		}

	int m_Start;
	int m_Finish;

	std::shared_ptr<predatorAction> m_predatorAction;
	std::shared_ptr<predatorPanelText> m_predatorPanelText;
};

class predatorAction
{
public:
	predatorAction() { acClear(); };
	predatorAction(std::string f_ActionText, UINT8 f_ActionIDX)
		{
		acClear();
		acPush(f_ActionText, f_ActionIDX);
		};
	~predatorAction() { acClear(); };

	void acClear(void)
		{
		m_entered.clear();
		m_deleted.clear();
		m_pasted.clear();
		m_copied.clear();
		}

	void acPush(std::string f_ActionText, UINT8 f_ActionIDX)
		{
		switch(f_ActionIDX)
			{
			case PREDATOR_ACTIONIDX_ENTER:
				{
				m_entered += f_ActionText;
				}break;

			case PREDATOR_ACTIONIDX_COPYED:
				{
				m_deleted += f_ActionText;
				}break;

			case PREDATOR_ACTIONIDX_DELETED:
				{
				m_pasted += f_ActionText;
				}break;

			case PREDATOR_ACTIONIDX_PASTED:
				{
				m_copied += f_ActionText;
				}break;
			}
		}

	std::string m_entered;
	std::string m_deleted;
	std::string m_pasted;
	std::string m_copied;

	std::shared_ptr<predatorIDX> m_predatorIDX;
};

class predatorPanelText
{
public:
	predatorPanelText() { acClear(); };
	predatorPanelText(std::shared_ptr<Qcom_eslfunction> f_function)
		{
		acClear();
		acFrom_eslfunction(f_function);
		}
	~predatorPanelText() { acClear(); };

	void acClear(void)
		{
		m_Text.clear();
		m_HCX = -1;
		m_ICX = -1;
		m_ComID = -1;
		m_QamID = -1;
		}

	void acSave(void);

	void acFrom_eslfunction(std::shared_ptr<Qcom_eslfunction> f_Function)
		{
		m_ComID = f_Function->m_ComID;
		m_QamID = f_Function->m_QamID;
		m_QamLevel = f_Function->m_QamLevel;
		m_Text.clear();

		for(int f_XY = 0; f_XY < f_Function->m_vec_InitLineOrdered.size(); f_XY++)
			{
			m_Text += f_Function->m_vec_InitLineOrdered[f_XY];
			}
		}

	std::string m_Text;
	int m_HCX;
	int m_ICX;
	int m_ComID;
	int m_QamID;
	int m_QamLevel;
};

class predatorInstance
{
public:
	predatorInstance();
	predatorInstance(std::shared_ptr<Qcom> f_com);
	~predatorInstance() { ac_Clear(); };

	void ac_Clear(void);

	void acSave(void);
	void acSaveAll(void);

	winrt::hstring acOpen(int f_HDX, int f_IDX);

	void acInsertPanel(int f_HDX, int f_IDX, std::shared_ptr<Qcom_eslfunction> f_function);

	bool acPushPanel(int f_HDX, int f_IDX, std::shared_ptr<predatorPanelText> f_PushPanel);
	std::shared_ptr<predatorPanelText> acPullPanel(int f_HDX, int f_IDX);

	int m_HDX;
	int m_IDX;
	std::shared_ptr<predatorPanelText> m_Panel;
	bool m_Panel_Set;
	int m_ComID;

	//Active code mapping
protected:
	std::vector<std::shared_ptr<predatorPanelText>> m_vec_onLoad;
	std::vector<std::shared_ptr<predatorPanelText>> m_vec_Frame;
	std::vector<std::shared_ptr<predatorPanelText>> m_vec_Input;
	std::vector<std::shared_ptr<predatorPanelText>> m_vec_Output;
	std::vector<std::shared_ptr<predatorAction>> m_vec_Undo;
	std::vector<std::shared_ptr<predatorAction>> m_vec_Redo;
};

class predatorInstanceManager
{
public:
	predatorInstanceManager() { ac_Clear(); };
	~predatorInstanceManager() { ac_Clear(); };

	winrt::hstring ac_Open_Com(std::shared_ptr<Qcom> f_com)
		{
		m_vec_PredatorIns.clear();

		std::shared_ptr<predatorInstance> f_Pi = acSearchIns_byComID(f_com);

		return f_Pi->acOpen(0, 0);
		}

	winrt::hstring ac_Open_HCX(int f_I, int f_C)
		{
		return m_PredatorIns->acOpen(f_I, f_C);
		}

	std::shared_ptr<predatorInstance> acSearchIns_byComID(std::shared_ptr<Qcom> f_com);

	void ac_Clear(void)
		{
		m_vec_PredatorIns.clear();
		}

	void acSave(void);
	void acSaveAll(void);

	std::shared_ptr<predatorInstance> m_PredatorIns;

	std::vector<std::shared_ptr<predatorInstance>> m_vec_PredatorIns;
};

extern std::vector<std::shared_ptr<predatorInstanceManager>> g_vec_PredatorManager;

};

#endif