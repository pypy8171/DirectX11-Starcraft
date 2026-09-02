#include "Light.h"

#include "Transform.h"
#include "RenderMgr.h"

CLight::CLight()
{
	// 포폴때 꺼야 함
	//SetComponentType(COMPONENT_TYPE::LIGHT);
}

CLight::~CLight()
{
}

int CLight::update()
{
	return 0;
}

int CLight::finalupdate()
{
	// Transform 의 위치정보를 얻어온다.
	m_info.vPos = Vec4(Transform()->GetWolrdPos(), 0.f);

	CRenderMgr::GetInst()->RegisterLight(m_info);
	return 0;
}