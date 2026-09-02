#include "stdafx.h"
#include "NumberScript.h"

#include "YongEngine/Core.h"

#include "YongEngine/GameObject.h"
#include "YongEngine/Transform.h"
#include "YongEngine/MeshRender.h"

#include "YongEngine/ResMgr.h"
#include "YongEngine/EventMgr.h"

#include "UnitScript.h"

#include "UIMgr.h"
#include "ScriptMgr.h"

CNumberScript::CNumberScript()
	: m_iNum(0)
	, m_eNumberType(NUMBER_TYPE::NONE)
	, m_bHpUI(false)
	, m_bShieldUI(false)
	, m_pGameObject(nullptr)
	, m_bMineralUI(false)
	, m_bGasUI(false)
{
	for (int i = 0; i < 3; ++i)
	{
		m_pHpMtrl[i] = nullptr;
		m_pMaxHpMtrl[i] = nullptr;
		m_pShieldMtrl[i] = nullptr;
		m_pMaxShieldMtrl[i] = nullptr;
	}

	for (int i = 0; i < 5; ++i)
	{
		m_pMineralMtrl[i] = nullptr;
		m_pGasMtrl[i] = nullptr;
	}

	SetScriptType((UINT)SCRIPT_TYPE::NUMBERSCRIPT);
}


CNumberScript::~CNumberScript()
{
}

int CNumberScript::update()
{
	if (m_bMineralUI)
	{
		ShowMineral();
	}

	if (m_bGasUI)
	{
		ShowGas();
	}

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	if (pCurScene->GetCurTargetObjVec().size() > 1)
	{
		Object()->MeshRender()->SetRender(false);
		return 0;
	}

	Object()->MeshRender()->SetRender(true);

	if (m_eNumberType == NUMBER_TYPE::MINERAL)
	{
		if(!m_bMineralUI)
			Mineral();
	}

	if (m_eNumberType == NUMBER_TYPE::GAS)
	{
		if (!m_bGasUI)
			Gas();
	}

	if (m_eNumberType == NUMBER_TYPE::HP)
	{
		if(!m_bHpUI)
			Hp();
	}

	if (m_eNumberType == NUMBER_TYPE::SHIELD)
	{
		if (!m_bShieldUI)
			Shield();
	}


	if (m_bHpUI)
	{
		ShowHp();
	}

	if (m_bShieldUI)
	{
		ShowShield();
	}



	return 0;
}

int CNumberScript::lateupdate()
{
	return 0;
}

void CNumberScript::Hp()
{
	int iCount = 0;
	vector<int> vecNum;
	vector<int> vecMaxNum;

	int iNum = 0;

	CUnitScript* pUnitScript = nullptr;
	if (pUnitScript == nullptr)
	{
		for (size_t i = 0; i < m_pGameObject->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::UNITSCRIPT == m_pGameObject->Script()[i]->GetScriptType())
			{
				pUnitScript = (CUnitScript*)m_pGameObject->Script()[i];
			}
		}
	}

	if (pUnitScript == nullptr)
		return;

	m_iNum = pUnitScript->GetUnitHp();

	while (1)
	{
		int iInput = 0;

		if (0 == m_iNum)
			break;
		else
		{
			iInput = m_iNum % 10;
			vecNum.push_back(iInput);
			vecMaxNum.push_back(iInput);
			m_iNum = m_iNum / 10;
			++iCount;
		}
	}

	for (int i = 0; i < iCount; ++i)
	{
		CGameObject* pHp = new CGameObject;
		pHp->SetName(L"HP");
		pHp->AddComponent(new CMeshRender);

		pHp->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pHp->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		CTexture* pTexture = nullptr;

		int iOutputNumber = vecNum.back();
		if (0 == iOutputNumber){pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_00.png");}
		else  if(1 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_01.png"); }
		else  if(2 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_02.png"); }
		else  if(3 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_03.png"); }
		else  if(4 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_04.png"); }
		else  if(5 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_05.png"); }
		else  if(6 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_06.png"); }
		else  if(7 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_07.png"); }
		else  if(8 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_08.png"); }
		else  if(9 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_09.png"); }
		vecNum.pop_back();

		if (nullptr == m_pHpMtrl[0])
		{
			m_pHpMtrl[0] = pHp->MeshRender()->GetCloneMaterial();
			m_pHpMtrl[0]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		else if (nullptr == m_pHpMtrl[1])
		{
			m_pHpMtrl[1] = pHp->MeshRender()->GetCloneMaterial();
			m_pHpMtrl[1]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		else if (nullptr == m_pHpMtrl[2])
		{
			m_pHpMtrl[2] = pHp->MeshRender()->GetCloneMaterial();
			m_pHpMtrl[2]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}


		Object()->AddChild(pHp);
	}

	for (int i = 0; i < iCount; ++i)
	{
		CGameObject* pHp = new CGameObject;
		pHp->SetName(L"MaxHP");
		pHp->AddComponent(new CMeshRender);

		pHp->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pHp->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		CTexture* pTexture = nullptr;

		int iOutputNumber = vecMaxNum.back();
		if (0 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_00.png"); }
		else  if (1 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_01.png"); }
		else  if (2 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_02.png"); }
		else  if (3 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_03.png"); }
		else  if (4 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_04.png"); }
		else  if (5 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_05.png"); }
		else  if (6 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_06.png"); }
		else  if (7 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_07.png"); }
		else  if (8 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_08.png"); }
		else  if (9 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_09.png"); }
		vecMaxNum.pop_back();

		if (nullptr == m_pMaxHpMtrl[0])
		{
			m_pMaxHpMtrl[0] = pHp->MeshRender()->GetCloneMaterial();
			m_pMaxHpMtrl[0]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		else if (nullptr == m_pMaxHpMtrl[1])
		{
			m_pMaxHpMtrl[1] = pHp->MeshRender()->GetCloneMaterial();
			m_pMaxHpMtrl[1]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		else if (nullptr == m_pMaxHpMtrl[2])
		{
			m_pMaxHpMtrl[2] = pHp->MeshRender()->GetCloneMaterial();
			m_pMaxHpMtrl[2]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}

		Object()->AddChild(pHp);
	}

	m_bHpUI = true;
}

void CNumberScript::Shield()
{
	int iCount = 0;
	vector<int> vecNum;
	vector<int> vecMaxNum;

	int iNum = 0;

	CUnitScript* pUnitScript = nullptr;
	if (pUnitScript == nullptr)
	{
		for (size_t i = 0; i < m_pGameObject->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::UNITSCRIPT == m_pGameObject->Script()[i]->GetScriptType())
			{
				pUnitScript = (CUnitScript*)m_pGameObject->Script()[i];
			}
		}
	}

	if (pUnitScript == nullptr)
		return;

	m_iNum = pUnitScript->GetUnitHp();

	while (1)
	{
		int iInput = 0;

		if (0 == m_iNum)
			break;
		else
		{
			iInput = m_iNum % 10;
			vecNum.push_back(iInput);
			vecMaxNum.push_back(iInput);
			m_iNum = m_iNum / 10;
			++iCount;
		}
	}

	for (int i = 0; i < iCount; ++i)
	{
		CGameObject* pShield = new CGameObject;
		pShield->SetName(L"Shield");
		pShield->AddComponent(new CMeshRender);

		pShield->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShield->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		CTexture* pTexture = nullptr;

		int iOutputNumber = vecNum.back();
		if (0 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_00.png"); }
		else  if (1 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_01.png"); }
		else  if (2 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_02.png"); }
		else  if (3 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_03.png"); }
		else  if (4 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_04.png"); }
		else  if (5 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_05.png"); }
		else  if (6 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_06.png"); }
		else  if (7 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_07.png"); }
		else  if (8 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_08.png"); }
		else  if (9 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_09.png"); }
		vecNum.pop_back();

		if (nullptr == m_pShieldMtrl[0])
		{
			m_pShieldMtrl[0] = pShield->MeshRender()->GetCloneMaterial();
			m_pShieldMtrl[0]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		else if (nullptr == m_pShieldMtrl[1])
		{
			m_pShieldMtrl[1] = pShield->MeshRender()->GetCloneMaterial();
			m_pShieldMtrl[1]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		else if (nullptr == m_pShieldMtrl[2])
		{
			m_pShieldMtrl[2] = pShield->MeshRender()->GetCloneMaterial();
			m_pShieldMtrl[2]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		Object()->AddChild(pShield);
	}

	for (int i = 0; i < iCount; ++i)
	{
		CGameObject* pShield = new CGameObject;
		pShield->SetName(L"MaxShield");
		pShield->AddComponent(new CMeshRender);

		pShield->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pShield->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		CTexture* pTexture = nullptr;

		int iOutputNumber = vecMaxNum.back();
		if (0 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_00.png"); }
		else  if (1 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_01.png"); }
		else  if (2 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_02.png"); }
		else  if (3 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_03.png"); }
		else  if (4 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_04.png"); }
		else  if (5 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_05.png"); }
		else  if (6 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_06.png"); }
		else  if (7 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_07.png"); }
		else  if (8 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_08.png"); }
		else  if (9 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_09.png"); }
		vecMaxNum.pop_back();

		if (nullptr == m_pMaxShieldMtrl[0])
		{
			m_pMaxShieldMtrl[0] = pShield->MeshRender()->GetCloneMaterial();
			m_pMaxShieldMtrl[0]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		else if (nullptr == m_pMaxShieldMtrl[1])
		{
			m_pMaxShieldMtrl[1] = pShield->MeshRender()->GetCloneMaterial();
			m_pMaxShieldMtrl[1]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		else if (nullptr == m_pMaxShieldMtrl[2])
		{
			m_pMaxShieldMtrl[2] = pShield->MeshRender()->GetCloneMaterial();
			m_pMaxShieldMtrl[2]->SetData(SHADER_PARAM::TEX_0, pTexture);
		}
		Object()->AddChild(pShield);
	}

	m_bShieldUI = true;
}

void CNumberScript::Mineral()
{
	for (int i = 0; i < 5; ++i)
	{
		CGameObject* pMineral = new CGameObject;
		pMineral->SetName(L"Mineral");
		pMineral->AddComponent(new CMeshRender);

		pMineral->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pMineral->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		if (nullptr == m_pMineralMtrl[i])
		{
			m_pMineralMtrl[i] = pMineral->MeshRender()->GetCloneMaterial();
			m_pMineralMtrl[i]->SetData(SHADER_PARAM::TEX_0, nullptr);
		}

		Object()->AddChild(pMineral);
	}

	m_bMineralUI = true;
}

void CNumberScript::Gas()
{
	for (int i = 0; i < 5; ++i)
	{
		CGameObject* pGas = new CGameObject;
		pGas->SetName(L"Gas");
		pGas->AddComponent(new CMeshRender);

		pGas->MeshRender()->SetMesh(CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
		pGas->MeshRender()->SetMaterial(CResMgr::GetInst()->Load<CMaterial>(L"Std2DMtrl"));

		if (nullptr == m_pGasMtrl[i])
		{
			m_pGasMtrl[i] = pGas->MeshRender()->GetCloneMaterial();
			m_pGasMtrl[i]->SetData(SHADER_PARAM::TEX_0, nullptr);
		}

		Object()->AddChild(pGas);
	}

	m_bGasUI = true;
}

void CNumberScript::ShowHp()
{
	int iCount = 0;
	vector<int> vecNum;
	vector<int> vecMaxNum;

	int iNum = 0;

	CUnitScript* pUnitScript = nullptr;
	if (pUnitScript == nullptr)
	{
		for (size_t i = 0; i < m_pGameObject->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::UNITSCRIPT == m_pGameObject->Script()[i]->GetScriptType())
			{
				pUnitScript = (CUnitScript*)m_pGameObject->Script()[i];
			}
		}
	}
	if (nullptr == pUnitScript)
		return;

	m_iNum = pUnitScript->GetUnitHp();

	while (1)
	{
		int iInput = 0;

		if (0 == m_iNum)
			break;
		else
		{
			iInput = m_iNum % 10;

			if (iInput < 0)
				return;

			vecNum.push_back(iInput);
			vecMaxNum.push_back(iInput);
			m_iNum = m_iNum / 10;
			++iCount;
		}
	}

	int iMaxHpCount = 0;
	int iHpCount = 0;

	for (size_t i = 0; i < Object()->GetChild().size(); ++i)
	{
		if (L"HP" == Object()->GetChild()[i]->GetName())
		{
			CTexture* pTexture = nullptr;

			if (0 == vecNum.size())
			{
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object() ,NULL });
				return;
			}
			int iOutputNumber = vecNum.back();
			if (0 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_00.png"); }
			else  if (1 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_01.png"); }
			else  if (2 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_02.png"); }
			else  if (3 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_03.png"); }
			else  if (4 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_04.png"); }
			else  if (5 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_05.png"); }
			else  if (6 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_06.png"); }
			else  if (7 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_07.png"); }
			else  if (8 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_08.png"); }
			else  if (9 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_09.png"); }
			vecNum.pop_back();

			if(0 == iHpCount) m_pHpMtrl[0]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if(1 == iHpCount) m_pHpMtrl[1]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if(2 == iHpCount) m_pHpMtrl[2]->SetData(SHADER_PARAM::TEX_0, pTexture);
			++iHpCount;


			Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
			if (iCount == 1)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-185.f + vCamPos.x, -290.f + vCamPos.y, 0.f));
			}
			else if (iCount == 2)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-3 + 6 * i - 185.f + vCamPos.x, -345 + vCamPos.y, 0));
			}
			else if (iCount == 3)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-6 + 6 * i - 185.f + vCamPos.x, -345 + vCamPos.y, 0));
			}

			Object()->GetChild()[i]->Transform()->SetLocalScale(Vec3(pTexture->GetWidth()*1.4f, pTexture->GetHeight()*1.4f, 1.f));
		}

		if (L"MaxHP" == Object()->GetChild()[i]->GetName())
		{
			CTexture* pTexture = nullptr;

			int iOutputNumber = vecMaxNum.back();
			if (0 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_00.png"); }
			else  if (1 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_01.png"); }
			else  if (2 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_02.png"); }
			else  if (3 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_03.png"); }
			else  if (4 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_04.png"); }
			else  if (5 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_05.png"); }
			else  if (6 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_06.png"); }
			else  if (7 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_07.png"); }
			else  if (8 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_08.png"); }
			else  if (9 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_09.png"); }
			vecMaxNum.pop_back();

			if (0 == iMaxHpCount) m_pMaxHpMtrl[0]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (1 == iMaxHpCount) m_pMaxHpMtrl[1]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (2 == iMaxHpCount) m_pMaxHpMtrl[2]->SetData(SHADER_PARAM::TEX_0, pTexture);
			++iMaxHpCount;



			Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
			if (iCount == 1)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-165.f + vCamPos.x, -290.f + vCamPos.y, 0.f));
			}
			else if (iCount == 2)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-3 + 6 * i - 165.f + vCamPos.x, -345 + vCamPos.y, 0));
			}
			else if (iCount == 3)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-6 + 6 * i - 165.f + vCamPos.x, -345 + vCamPos.y, 0));
			}

			Object()->GetChild()[i]->Transform()->SetLocalScale(Vec3(pTexture->GetWidth()*1.4f, pTexture->GetHeight()*1.4f, 1.f));

		}
	}
}

void CNumberScript::ShowShield()
{
	int iCount = 0;
	vector<int> vecNum;
	vector<int> vecMaxNum;

	int iNum = 0;

	CUnitScript* pUnitScript = nullptr;
	if (pUnitScript == nullptr)
	{
		for (size_t i = 0; i < m_pGameObject->Script().size(); ++i)
		{
			if ((UINT)SCRIPT_TYPE::UNITSCRIPT == m_pGameObject->Script()[i]->GetScriptType())
			{
				pUnitScript = (CUnitScript*)m_pGameObject->Script()[i];
			}
		}
	}

	if(pUnitScript!= nullptr)
		m_iNum = pUnitScript->GetUnitHp();

	while (1)
	{
		int iInput = 0;

		if (0 == m_iNum)
			break;
		else
		{
			iInput = m_iNum % 10;

			if (iInput < 0)
				return;

			vecNum.push_back(iInput);
			vecMaxNum.push_back(iInput);
			m_iNum = m_iNum / 10;
			++iCount;
		}
	}

	int iMaxShieldCount = 0;
	int iShieldCount = 0;

	for (size_t i = 0; i < Object()->GetChild().size(); ++i)
	{
		if (L"Shield" == Object()->GetChild()[i]->GetName())
		{
			CTexture* pTexture = nullptr;

			if (0 == vecNum.size())
			{
				CEventMgr::GetInst()->AddEvent(tEvent{ EVENT_TYPE::DELETE_OBJECT,(INT_PTR)Object() ,NULL });
				return;
			}

			int iOutputNumber = vecNum.back();
			if (0 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_00.png"); }
			else  if (1 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_01.png"); }
			else  if (2 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_02.png"); }
			else  if (3 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_03.png"); }
			else  if (4 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_04.png"); }
			else  if (5 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_05.png"); }
			else  if (6 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_06.png"); }
			else  if (7 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_07.png"); }
			else  if (8 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_08.png"); }
			else  if (9 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_09.png"); }
			vecNum.pop_back();

			if (0 == iShieldCount) m_pShieldMtrl[0]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (1 == iShieldCount) m_pShieldMtrl[1]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (2 == iShieldCount) m_pShieldMtrl[2]->SetData(SHADER_PARAM::TEX_0, pTexture);
			++iShieldCount;

			Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
			if (iCount == 1)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-240.f + vCamPos.x, -290.f + vCamPos.y, 0.f));
			}
			else if (iCount == 2)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-3 + 6 * i - 240.f + vCamPos.x, -345 + vCamPos.y, 0));
			}
			else if (iCount == 3)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-6 + 6 * i - 240.f + vCamPos.x, -345 + vCamPos.y, 0));
			}

			Object()->GetChild()[i]->Transform()->SetLocalScale(Vec3(pTexture->GetWidth()*1.4f, pTexture->GetHeight()*1.4f, 1.f));
		}

		if (L"MaxShield" == Object()->GetChild()[i]->GetName())
		{
			CTexture* pTexture = nullptr;

			int iOutputNumber = vecMaxNum.back();
			if (0 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_00.png"); }
			else  if (1 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_01.png"); }
			else  if (2 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_02.png"); }
			else  if (3 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_03.png"); }
			else  if (4 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_04.png"); }
			else  if (5 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_05.png"); }
			else  if (6 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_06.png"); }
			else  if (7 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_07.png"); }
			else  if (8 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_08.png"); }
			else  if (9 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"shield_09.png"); }
			vecMaxNum.pop_back();

			if (0 == iMaxShieldCount) m_pMaxShieldMtrl[0]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (1 == iMaxShieldCount) m_pMaxShieldMtrl[1]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (2 == iMaxShieldCount) m_pMaxShieldMtrl[2]->SetData(SHADER_PARAM::TEX_0, pTexture);
			++iMaxShieldCount;

			Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
			if (iCount == 1)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-225.f + vCamPos.x, -290.f + vCamPos.y, 0.f));
			}
			else if (iCount == 2)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-3 + 6 * i - 225.f + vCamPos.x, -345 + vCamPos.y, 0));
			}
			else if (iCount == 3)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-6 + 6 * i - 225.f + vCamPos.x, -345 + vCamPos.y, 0));
			}

			Object()->GetChild()[i]->Transform()->SetLocalScale(Vec3(pTexture->GetWidth()*1.4f, pTexture->GetHeight()*1.4f, 1.f));
		}
	}
}

void CNumberScript::ShowMineral()
{
	int iCount = 0;
	vector<int> vecNum;

	int iNum = 0;

	m_iNum = CUIMgr::GetInst()->GetMineral();

	while (1)
	{
		int iInput = 0;

		if (0 == m_iNum)
			break;
		else
		{
			iInput = m_iNum % 10;
			vecNum.push_back(iInput);
			m_iNum = m_iNum / 10;
			++iCount;
		}
	}

	int iMineralCount = 0;

	for (int i = 0; i < iCount; ++i)
	{
		if (L"Mineral" == Object()->GetChild()[i]->GetName())
		{
			CTexture* pTexture = nullptr;

			int iOutputNumber = vecNum.back();
			if (0 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_00.png"); }
			else  if (1 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_01.png"); }
			else  if (2 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_02.png"); }
			else  if (3 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_03.png"); }
			else  if (4 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_04.png"); }
			else  if (5 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_05.png"); }
			else  if (6 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_06.png"); }
			else  if (7 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_07.png"); }
			else  if (8 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_08.png"); }
			else  if (9 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_09.png"); }
			vecNum.pop_back();

			if (0 == iMineralCount) m_pMineralMtrl[0]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (1 == iMineralCount) m_pMineralMtrl[1]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (2 == iMineralCount) m_pMineralMtrl[2]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (3 == iMineralCount) m_pMineralMtrl[3]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (4 == iMineralCount) m_pMineralMtrl[4]->SetData(SHADER_PARAM::TEX_0, pTexture);
			++iMineralCount;

			tResolution vResolution = CCore::GetInst()->GetResoultion();

			Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
			if (iCount == 1)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(170.f*vResolution.x/760 + vCamPos.x, 230.f*vResolution.y / 480.f + vCamPos.y, 0.f));
			}
			else if (iCount == 2)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-4 + 8 * i + 170.f*vResolution.x / 760 + vCamPos.x, 230.f*vResolution.y / 480.f + vCamPos.y, 0));
			}
			else if (iCount == 3)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-8 + 8 * i + 170.f*vResolution.x / 760 + vCamPos.x, 230.f*vResolution.y / 480.f + vCamPos.y, 0));
			}
			else if (iCount == 4)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-12 + 8 * i + 170.f*vResolution.x / 760 + vCamPos.x, 230.f*vResolution.y / 480.f + vCamPos.y, 0));
			}
			else if (iCount == 5)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-16 + 8 * i + 170.f + vCamPos.x, 230.f*vResolution.y / 480.f + vCamPos.y, 0));
			}

			Object()->GetChild()[i]->Transform()->SetLocalScale(Vec3(pTexture->GetWidth()*2.f, pTexture->GetHeight()*2.f, 1.f));
		}
	}
}

void CNumberScript::ShowGas()
{
	int iCount = 0;
	vector<int> vecNum;

	int iNum = 0;

	m_iNum = CUIMgr::GetInst()->GetGas();

	while (1)
	{
		int iInput = 0;

		if (0 == m_iNum)
			break;
		else
		{
			iInput = m_iNum % 10;
			vecNum.push_back(iInput);
			m_iNum = m_iNum / 10;
			++iCount;
		}
	}

	int iGasCount = 0;

	for (int i = 0; i < iCount; ++i)
	{
		if (L"Gas" == Object()->GetChild()[i]->GetName())
		{
			CTexture* pTexture = nullptr;

			int iOutputNumber = vecNum.back();
			if (0 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_00.png"); }
			else  if (1 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_01.png"); }
			else  if (2 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_02.png"); }
			else  if (3 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_03.png"); }
			else  if (4 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_04.png"); }
			else  if (5 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_05.png"); }
			else  if (6 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_06.png"); }
			else  if (7 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_07.png"); }
			else  if (8 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_08.png"); }
			else  if (9 == iOutputNumber) { pTexture = CResMgr::GetInst()->Load<CTexture>(L"normal_09.png"); }
			vecNum.pop_back();

			if (0 == iGasCount) m_pGasMtrl[0]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (1 == iGasCount) m_pGasMtrl[1]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (2 == iGasCount) m_pGasMtrl[2]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (3 == iGasCount) m_pGasMtrl[3]->SetData(SHADER_PARAM::TEX_0, pTexture);
			else if (4 == iGasCount) m_pGasMtrl[4]->SetData(SHADER_PARAM::TEX_0, pTexture);
			++iGasCount;

			Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
			if (iCount == 1)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(330.f + vCamPos.x, 365.f + vCamPos.y, 0.f));
			}
			else if (iCount == 2)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-4 + 8 * i + 330.f + vCamPos.x, 365.f + vCamPos.y, 0));
			}
			else if (iCount == 3)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-8 + 8 * i + 330.f + vCamPos.x, 365.f + vCamPos.y, 0));
			}
			else if (iCount == 4)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-12 + 8 * i + 330.f + vCamPos.x, 365.f + vCamPos.y, 0));
			}
			else if (iCount == 5)
			{
				Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-16 + 8 * i + 330.f + vCamPos.x, 365.f + vCamPos.y, 0));
			}

			Object()->GetChild()[i]->Transform()->SetLocalScale(Vec3(pTexture->GetWidth()*2.f, pTexture->GetHeight()*2.f, 1.f));
		}
	}
}


//Vec3 vCamPos = CUIMgr::GetInst()->GetCamPos();
//if (iCount == 1)
//{
//	Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-185.f + vCamPos.x, -290.f + vCamPos.y, 0.f));
//}
//else if (iCount == 2)
//{
//	Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-3 + 6 * i - 185.f + vCamPos.x, -345 + vCamPos.y, 0));
//}
//else if (iCount == 3)
//{
//	Object()->GetChild()[i]->Transform()->SetLocalPos(Vec3(-6 + 6 * i - 185.f + vCamPos.x, -345 + vCamPos.y, 0));
//}

//Object()->GetChild()[i]->Transform()->SetLocalScale(Vec3(pTexture->GetWidth()*1.4f, pTexture->GetHeight()*1.4f, 1.f));
