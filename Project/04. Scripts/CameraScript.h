#pragma once
#include "YongEngine/Script.h"
class CCameraScript :
	public CScript
{
private:
	bool	m_bWheelOn;

protected:
	Vec3 m_vCamPos;
	UINT  m_iCameraDir;

public:
	virtual int update();
	virtual void awake();

public:
	const Vec3& GetCamPos() { return m_vCamPos; }
	void SetCamPos(Vec3 _vCamPos) { m_vCamPos = _vCamPos; }

	const UINT& GetCameraDir() { return m_iCameraDir; }

public:
	void RotateCam();
	void MoveCam();

public:
	CLONE(CCameraScript);

public:
	CCameraScript();
	virtual ~CCameraScript();
};

