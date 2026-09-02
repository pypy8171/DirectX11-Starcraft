#pragma once
#include "Component.h"



class CCamera :
	public CComponent
{
private:
	Matrix			m_matView;
	Matrix			m_matProj;
	Matrix			m_matPrevProj;

	float			m_fFar;		// 최소 거리
	float			m_fNear;	// 최대 거리
	float			m_fFov;		// 시야각(원근 투영)
	float			m_fScale;	// 투영 크기(직교 투영) 

	tResolution		m_tResolution;
	UINT			m_iLayerMask;

	bool			m_bPerspective;

	float			m_fSpeed;
	float			m_fRatio;
	bool			m_bTransforming;

private:
	Vec3			m_vRight;
	Vec3			m_vLook;
	Vec3			m_vEye;
	Vec3			m_vUp;

	Vec3			m_vAngle;
	float			m_fMoveSpeed;


public:
	Vec3 & GetRotAngle() {return  m_vAngle; }
	Matrix& GetView() {return m_matView;}

public:
	float GetNear() { return m_fNear; }
	void SetNear(float _fNear) { m_fNear = _fNear; }

	float GetFar() { return m_fFar; }
	void SetFar(float _fFar) { m_fFar = _fFar; }

	float GetFOV() { return m_fFov; }
	void SetFOV(float _fFov) { m_fFov = _fFov; }

	float GetScale() { return m_fScale; }
	void SetScale(float _fScale) { m_fScale = _fScale; }

	bool IsPerspective() { return m_bPerspective; }
	void SetPerspective(bool _bool) {
		m_bPerspective = _bool;

		if (XMMatrixIsIdentity(m_matProj))
			return;

		if (m_bPerspective)
			m_fSpeed = 10.f;
		else
			m_fSpeed = 0.1f;

		m_matPrevProj = m_matProj;
		m_bTransforming = true;
		m_fRatio = 0.f;
	}

public:
	const bool& GetPerspective() { return m_bPerspective; }

public:
	void ChangeProjMode();

public:
	void CameraTransform();
	void CameraRotate();

public:
	void CheckLayer(UINT _iIdx);
	void CheckLayer(const wstring& _strLayerName);
	void CheckLayerAll() { m_iLayerMask = 0xffffffff; }
	void CheckLayerClear() { m_iLayerMask = 0; }
	UINT GetLayerMask() { return m_iLayerMask; }

public:
	virtual int update();
	virtual int finalupdate();

public:
	void render(CLayer** _pLayer);

public:
	CLONE(CCamera);
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	CCamera();
	virtual ~CCamera();
};

