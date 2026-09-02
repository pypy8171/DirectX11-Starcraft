#include "stdafx.h"
#include "ScriptMgr.h"

#include "Scripts\ArbiterScript.h"
#include "Scripts\ArchonEffectScript.h"
#include "Scripts\ArchonScript.h"
#include "Scripts\BuildingMgr.h"
#include "Scripts\BuildingScript.h"
#include "Scripts\BulletScript.h"
#include "Scripts\ButtonScript.h"
#include "Scripts\CameraScript.h"
#include "Scripts\CarrierScript.h"
#include "Scripts\CorsairScript.h"
#include "Scripts\DarkArchonScript.h"
#include "Scripts\DarkTemplarScript.h"
#include "Scripts\DragoonScript.h"
#include "Scripts\GasScript.h"
#include "Scripts\HighTemplarScript.h"
#include "Scripts\IconScript.h"
#include "Scripts\InterceptorScript.h"
#include "Scripts\LoadSciprtMgr.h"
#include "Scripts\MarkScript.h"
#include "Scripts\MineralScript.h"
#include "Scripts\MonsterScript.h"
#include "Scripts\MouseScript.h"
#include "Scripts\MuzzleScript.h"
#include "Scripts\NexusScript.h"
#include "Scripts\NumberMgr.h"
#include "Scripts\NumberScript.h"
#include "Scripts\ObserverScript.h"
#include "Scripts\PlanetScript.h"
#include "Scripts\PlayerScript.h"
#include "Scripts\PortraitScript.h"
#include "Scripts\ProbeScript.h"
#include "Scripts\ProduceScript.h"
#include "Scripts\ProtossUIScript.h"
#include "Scripts\ReaverScript.h"
#include "Scripts\ResourceScript.h"
#include "Scripts\ScoutScript.h"
#include "Scripts\SeclectScript.h"
#include "Scripts\ShuttleScript.h"
#include "Scripts\SkillMgr.h"
#include "Scripts\SkillScript.h"
#include "Scripts\StatusScript.h"
#include "Scripts\TileMgr.h"
#include "Scripts\TileScript.h"
#include "Scripts\UIMgr.h"
#include "Scripts\UnitEffectScript.h"
#include "Scripts\UnitMgr.h"
#include "Scripts\UnitScript.h"
#include "Scripts\UnitShadScript.h"
#include "Scripts\UpgradeMgr.h"
#include "Scripts\WireFrameScript.h"
#include "Scripts\ZealotScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"ArbiterScript");
	_vec.push_back(L"ArchonEffectScript");
	_vec.push_back(L"ArchonScript");
	_vec.push_back(L"BuildingMgr");
	_vec.push_back(L"BuildingScript");
	_vec.push_back(L"BulletScript");
	_vec.push_back(L"ButtonScript");
	_vec.push_back(L"CameraScript");
	_vec.push_back(L"CarrierScript");
	_vec.push_back(L"CorsairScript");
	_vec.push_back(L"DarkArchonScript");
	_vec.push_back(L"DarkTemplarScript");
	_vec.push_back(L"DragoonScript");
	_vec.push_back(L"GasScript");
	_vec.push_back(L"HighTemplarScript");
	_vec.push_back(L"IconScript");
	_vec.push_back(L"InterceptorScript");
	_vec.push_back(L"LoadSciprtMgr");
	_vec.push_back(L"MarkScript");
	_vec.push_back(L"MineralScript");
	_vec.push_back(L"MonsterScript");
	_vec.push_back(L"MouseScript");
	_vec.push_back(L"MuzzleScript");
	_vec.push_back(L"NexusScript");
	_vec.push_back(L"NumberMgr");
	_vec.push_back(L"NumberScript");
	_vec.push_back(L"ObserverScript");
	_vec.push_back(L"PlanetScript");
	_vec.push_back(L"PlayerScript");
	_vec.push_back(L"PortraitScript");
	_vec.push_back(L"ProbeScript");
	_vec.push_back(L"ProduceScript");
	_vec.push_back(L"ProtossUIScript");
	_vec.push_back(L"ReaverScript");
	_vec.push_back(L"ResourceScript");
	_vec.push_back(L"ScoutScript");
	_vec.push_back(L"SeclectScript");
	_vec.push_back(L"ShuttleScript");
	_vec.push_back(L"SkillMgr");
	_vec.push_back(L"SkillScript");
	_vec.push_back(L"StatusScript");
	_vec.push_back(L"TileMgr");
	_vec.push_back(L"TileScript");
	_vec.push_back(L"UIMgr");
	_vec.push_back(L"UnitEffectScript");
	_vec.push_back(L"UnitMgr");
	_vec.push_back(L"UnitScript");
	_vec.push_back(L"UnitShadScript");
	_vec.push_back(L"UpgradeMgr");
	_vec.push_back(L"WireFrameScript");
	_vec.push_back(L"ZealotScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"ArbiterScript" == _strScriptName)
		return new CArbiterScript;
	if (L"ArchonEffectScript" == _strScriptName)
		return new CArchonEffectScript;
	if (L"ArchonScript" == _strScriptName)
		return new CArchonScript;
	if (L"BuildingMgr" == _strScriptName)
		return new CBuildingMgr;
	if (L"BuildingScript" == _strScriptName)
		return new CBuildingScript;
	if (L"BulletScript" == _strScriptName)
		return new CBulletScript;
	if (L"ButtonScript" == _strScriptName)
		return new CButtonScript;
	if (L"CameraScript" == _strScriptName)
		return new CCameraScript;
	if (L"CarrierScript" == _strScriptName)
		return new CCarrierScript;
	if (L"CorsairScript" == _strScriptName)
		return new CCorsairScript;
	if (L"DarkArchonScript" == _strScriptName)
		return new CDarkArchonScript;
	if (L"DarkTemplarScript" == _strScriptName)
		return new CDarkTemplarScript;
	if (L"DragoonScript" == _strScriptName)
		return new CDragoonScript;
	if (L"GasScript" == _strScriptName)
		return new CGasScript;
	if (L"HighTemplarScript" == _strScriptName)
		return new CHighTemplarScript;
	if (L"IconScript" == _strScriptName)
		return new CIconScript;
	if (L"InterceptorScript" == _strScriptName)
		return new CInterceptorScript;
	if (L"LoadSciprtMgr" == _strScriptName)
		return new CLoadSciprtMgr;
	if (L"MarkScript" == _strScriptName)
		return new CMarkScript;
	if (L"MineralScript" == _strScriptName)
		return new CMineralScript;
	if (L"MonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"MouseScript" == _strScriptName)
		return new CMouseScript;
	if (L"MuzzleScript" == _strScriptName)
		return new CMuzzleScript;
	if (L"NexusScript" == _strScriptName)
		return new CNexusScript;
	if (L"NumberMgr" == _strScriptName)
		return new CNumberMgr;
	if (L"NumberScript" == _strScriptName)
		return new CNumberScript;
	if (L"ObserverScript" == _strScriptName)
		return new CObserverScript;
	if (L"PlanetScript" == _strScriptName)
		return new CPlanetScript;
	if (L"PlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"PortraitScript" == _strScriptName)
		return new CPortraitScript;
	if (L"ProbeScript" == _strScriptName)
		return new CProbeScript;
	if (L"ProduceScript" == _strScriptName)
		return new CProduceScript;
	if (L"ProtossUIScript" == _strScriptName)
		return new CProtossUIScript;
	if (L"ReaverScript" == _strScriptName)
		return new CReaverScript;
	if (L"ResourceScript" == _strScriptName)
		return new CResourceScript;
	if (L"ScoutScript" == _strScriptName)
		return new CScoutScript;
	if (L"SeclectScript" == _strScriptName)
		return new CSeclectScript;
	if (L"ShuttleScript" == _strScriptName)
		return new CShuttleScript;
	if (L"SkillMgr" == _strScriptName)
		return new CSkillMgr;
	if (L"SkillScript" == _strScriptName)
		return new CSkillScript;
	if (L"StatusScript" == _strScriptName)
		return new CStatusScript;
	if (L"TileMgr" == _strScriptName)
		return new CTileMgr;
	if (L"TileScript" == _strScriptName)
		return new CTileScript;
	if (L"UIMgr" == _strScriptName)
		return new CUIMgr;
	if (L"UnitEffectScript" == _strScriptName)
		return new CUnitEffectScript;
	if (L"UnitMgr" == _strScriptName)
		return new CUnitMgr;
	if (L"UnitScript" == _strScriptName)
		return new CUnitScript;
	if (L"UnitShadScript" == _strScriptName)
		return new CUnitShadScript;
	if (L"UpgradeMgr" == _strScriptName)
		return new CUpgradeMgr;
	if (L"WireFrameScript" == _strScriptName)
		return new CWireFrameScript;
	if (L"ZealotScript" == _strScriptName)
		return new CZealotScript;
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::ARBITERSCRIPT:
		return L"ArbiterScript";
		break;

	case SCRIPT_TYPE::ARCHONEFFECTSCRIPT:
		return L"ArchonEffectScript";
		break;

	case SCRIPT_TYPE::ARCHONSCRIPT:
		return L"ArchonScript";
		break;

	case SCRIPT_TYPE::BUILDINGMGR:
		return L"BuildingMgr";
		break;

	case SCRIPT_TYPE::BUILDINGSCRIPT:
		return L"BuildingScript";
		break;

	case SCRIPT_TYPE::BULLETSCRIPT:
		return L"BulletScript";
		break;

	case SCRIPT_TYPE::BUTTONSCRIPT:
		return L"ButtonScript";
		break;

	case SCRIPT_TYPE::CAMERASCRIPT:
		return L"CameraScript";
		break;

	case SCRIPT_TYPE::CARRIERSCRIPT:
		return L"CarrierScript";
		break;

	case SCRIPT_TYPE::CORSAIRSCRIPT:
		return L"CorsairScript";
		break;

	case SCRIPT_TYPE::DARKARCHONSCRIPT:
		return L"DarkArchonScript";
		break;

	case SCRIPT_TYPE::DARKTEMPLARSCRIPT:
		return L"DarkTemplarScript";
		break;

	case SCRIPT_TYPE::DRAGOONSCRIPT:
		return L"DragoonScript";
		break;

	case SCRIPT_TYPE::GASSCRIPT:
		return L"GasScript";
		break;

	case SCRIPT_TYPE::HIGHTEMPLARSCRIPT:
		return L"HighTemplarScript";
		break;

	case SCRIPT_TYPE::ICONSCRIPT:
		return L"IconScript";
		break;

	case SCRIPT_TYPE::INTERCEPTORSCRIPT:
		return L"InterceptorScript";
		break;

	case SCRIPT_TYPE::LOADSCIPRTMGR:
		return L"LoadSciprtMgr";
		break;

	case SCRIPT_TYPE::MARKSCRIPT:
		return L"MarkScript";
		break;

	case SCRIPT_TYPE::MINERALSCRIPT:
		return L"MineralScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"MonsterScript";
		break;

	case SCRIPT_TYPE::MOUSESCRIPT:
		return L"MouseScript";
		break;

	case SCRIPT_TYPE::MUZZLESCRIPT:
		return L"MuzzleScript";
		break;

	case SCRIPT_TYPE::NEXUSSCRIPT:
		return L"NexusScript";
		break;

	case SCRIPT_TYPE::NUMBERMGR:
		return L"NumberMgr";
		break;

	case SCRIPT_TYPE::NUMBERSCRIPT:
		return L"NumberScript";
		break;

	case SCRIPT_TYPE::OBSERVERSCRIPT:
		return L"ObserverScript";
		break;

	case SCRIPT_TYPE::PLANETSCRIPT:
		return L"PlanetScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"PlayerScript";
		break;

	case SCRIPT_TYPE::PORTRAITSCRIPT:
		return L"PortraitScript";
		break;

	case SCRIPT_TYPE::PROBESCRIPT:
		return L"ProbeScript";
		break;

	case SCRIPT_TYPE::PRODUCESCRIPT:
		return L"ProduceScript";
		break;

	case SCRIPT_TYPE::PROTOSSUISCRIPT:
		return L"ProtossUIScript";
		break;

	case SCRIPT_TYPE::REAVERSCRIPT:
		return L"ReaverScript";
		break;

	case SCRIPT_TYPE::RESOURCESCRIPT:
		return L"ResourceScript";
		break;

	case SCRIPT_TYPE::SCOUTSCRIPT:
		return L"ScoutScript";
		break;

	case SCRIPT_TYPE::SECLECTSCRIPT:
		return L"SeclectScript";
		break;

	case SCRIPT_TYPE::SHUTTLESCRIPT:
		return L"ShuttleScript";
		break;

	case SCRIPT_TYPE::SKILLMGR:
		return L"SkillMgr";
		break;

	case SCRIPT_TYPE::SKILLSCRIPT:
		return L"SkillScript";
		break;

	case SCRIPT_TYPE::STATUSSCRIPT:
		return L"StatusScript";
		break;

	case SCRIPT_TYPE::TILEMGR:
		return L"TileMgr";
		break;

	case SCRIPT_TYPE::TILESCRIPT:
		return L"TileScript";
		break;

	case SCRIPT_TYPE::UIMGR:
		return L"UIMgr";
		break;

	case SCRIPT_TYPE::UNITEFFECTSCRIPT:
		return L"UnitEffectScript";
		break;

	case SCRIPT_TYPE::UNITMGR:
		return L"UnitMgr";
		break;

	case SCRIPT_TYPE::UNITSCRIPT:
		return L"UnitScript";
		break;

	case SCRIPT_TYPE::UNITSHADSCRIPT:
		return L"UnitShadScript";
		break;

	case SCRIPT_TYPE::UPGRADEMGR:
		return L"UpgradeMgr";
		break;

	case SCRIPT_TYPE::WIREFRAMESCRIPT:
		return L"WireFrameScript";
		break;

	case SCRIPT_TYPE::ZEALOTSCRIPT:
		return L"ZealotScript";
		break;

	}
	return nullptr;
}